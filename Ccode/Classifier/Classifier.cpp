// Olga Souverneva 2016
// Class to handle ball classification

#include "stdafx.h"
#include "Classifier.h"
#include "MunkresMatching.h"
#include "Value.h"
#include "ReddishHue.h"
#include "NormalHue.h"

static HSV_Pixel _ballImage[MAX_RADIUS][MAX_RADIUS] = {};

Classifier::Classifier():
	m_histogram(NORMAL_HUE_MIN, NORMAL_HUE_MAX),
	m_reddishHistogram(REDDISH_HUE_MIN, REDDISH_HUE_MAX)
{
	ResetClassificationData();
}

void Classifier::Begin()
{
	ResetClassificationData();
}

void Classifier::Classify(const HSV_Frame& inputFrame, 
						  Coordinates* detectedCenters, 
						  unsigned int* radii, 
						  bool* found, 
						  unsigned int size)
{
	if (detectedCenters == NULL || radii == NULL || found == NULL)
		return;
	
	if (size == 0 || size > MAX_SIZE)
		return;

	// Clean the matrix of any empty rows. If no space, end.
	RemoveEmptyRows();
	unsigned char start = GetNextFree();
	if (start >= MAX_SIZE)
		return;

	// Fill in new rows of data.
	unsigned char end = size < (MAX_SIZE-start) ? start+size : MAX_SIZE;
	unsigned char j = 0;
	for (unsigned char i=start; i<end; i++)
	{
		m_classificationData[i].center = detectedCenters[j];
		m_classificationData[i].free = false;
		ComputeClassificationCost(i, inputFrame, radii[j]);
		j++;
	}

	// Mark any entries that are unlikely to be balls to be free to use in 
	// the next iteration. Output the not-found entries.
	j = 0;
	for (unsigned char i=start; i<end; i++)
	{
		if (ClassificationUnlikely(i))
		{
			found[j] = false;
			m_classificationData[i].free = true;
		}
		else
			found[j] = true;
		j++;
	}
}

void Classifier::Output(Coordinates* labeledCenters, unsigned char* labels, unsigned char labelsSize)
{
	if (labeledCenters == NULL || labels == NULL || labelsSize > MAX_SIZE)
		return;
	
	// Classify the cost matrix
	Classify();
	
	for (unsigned char i=0; i<labelsSize; i++)
	{
		if (m_classificationData[i].free)
		{
			labeledCenters[i].x=0;
			labeledCenters[i].y=0; 
			labels[i] = NOT_FOUND;
		}
		else
		{
			labeledCenters[i] = m_classificationData[i].center;
			labels[i] = m_classificationData[i].label;
		}
	}
}

void Classifier::Classify()
{
	static unsigned char labels[MAX_SIZE];
	unsigned char idx = GetLastFilled();
	if (idx >= MAX_SIZE)
		return;

	MunkresMatching(m_costMatrix, labels, idx+1, MAX_SIZE);

	// All matchings to BALL_MAX or greater are really "NOT_FOUNDs"
	for (unsigned char i=0; i<=idx; i++)
	{
		if (labels[i] < BALL_MAX)
			m_classificationData[i].label = labels[i];
		else
			m_classificationData[i].label = NOT_FOUND;
	}
}

unsigned char Classifier::GetNextFree()
{
	for (unsigned char i=0; i<MAX_SIZE; i++)
	{
		if (m_classificationData[i].free == true)
			return i;
	}
	return MAX_SIZE;
}

unsigned char Classifier::GetLastFilled()
{
	for (unsigned char i=MAX_SIZE-1; i>0; i--)
	{
		if (m_classificationData[i].free == false)
			return i;
	}
	return MAX_SIZE;
}

void Classifier::RemoveEmptyRows()
{
	// Empty matrix
	unsigned char lastFilled = GetLastFilled();
	if (lastFilled == MAX_SIZE)
		return;

	// Remove rows that are marked as free by moving all the filled rows up.
	unsigned char id = 0;
	while (id < MAX_SIZE-1 && lastFilled > id)
	{
		if (m_classificationData[id].free == true)
		{
			for (unsigned char i=id; i<lastFilled; i++)
			{
				m_classificationData[i]=m_classificationData[i+1];
				for (unsigned char j=0; j<MAX_SIZE; j++)
				{
					m_costMatrix[i][j] = m_costMatrix[i+1][j];
				}
			}
			lastFilled--;
		}
		id++;
	}
}

void Classifier::ResetClassificationData()
{
	for (unsigned char i=0; i<MAX_SIZE; i++)
	{
		m_classificationData[i].free = true;
		m_classificationData[i].label = NOT_FOUND;
	}
}

void Classifier::ComputeClassificationCost(unsigned char id, const HSV_Frame& inputFrame, unsigned int radius)
{	
	// Make sure R is in the allowed range
	unsigned int newR = radius > MIN_RADIUS ? MIN_RADIUS : 
		(radius < MAX_RADIUS ? radius : MAX_RADIUS);

	// Get the coordinates range
	Coordinates min;
	Coordinates max;
	min.x = m_classificationData[id].center.x > newR ? m_classificationData[id].center.x - newR : 0;
	min.y = m_classificationData[id].center.y > newR ? m_classificationData[id].center.y - newR : 0;
	max.x = m_classificationData[id].center.x < MAX_FRAME_LENGTH - newR ? m_classificationData[id].center.x + newR : MAX_FRAME_LENGTH;
	max.y = m_classificationData[id].center.y < MAX_FRAME_WIDTH - newR ? m_classificationData[id].center.y + newR : MAX_FRAME_WIDTH;

	// Compute the KDE
	ComputeBallKDE(inputFrame, min, max, m_classificationData[id].center, newR);

	// Compute the cost matrix
	// Balls
	for (unsigned char i=0; i<BALL_MAX; i++)
	{
		// Cost is 1-probability
		m_costMatrix[id][i] = 1.0f + PROXIMITY_FACTOR - GetBallProbability(static_cast<BallId>(i));
	}
	// Not a ball
	for (unsigned char i=BALL_MAX; i<MAX_SIZE; i++)
	{
		m_costMatrix[id][i] = 1.0f + PROXIMITY_FACTOR;
	}
}

float Classifier::GetBallProbability(BallId id)
{
	float out = 0.0f;
	float step = m_histogram.GetWidth();
	
	switch(id)
	{
	case BALL_8:
		{
			for (int i=0; i<MAX_BINS; i++)
			{
				float compare = GetValuePd(id, i);
				out += (m_valueKDE[i] < compare ? m_valueKDE[i] : compare)*step;
			}
			break;
		}
	case BALL_3:
	case BALL_4:
	case BALL_7:
	case BALL_11:
	case BALL_15:
		{
			for (int i=0; i<MAX_BINS; i++)
			{
				float compare = GetReddishHuePd(id, i);
				out += (m_reddishKDE[i] < compare ? m_reddishKDE[i] : compare)*step;
			}
			break;
		}
	default:
		{
			for (int i=0; i<MAX_BINS; i++)
			{
				float compare = GetNormalHuePd(id, i);
				out += (m_normKDE[i] < compare ? m_normKDE[i] : compare)*step;
			}
			break;
		}
	}

	return out;
}

void Classifier::ComputeBallKDE(const HSV_Frame& inputFrame, const Coordinates& min, const Coordinates& max, const Coordinates& center, int radius)
{
	unsigned int r_sq = radius*radius;

	// Value
	m_histogram.Reset();
	for (unsigned int x=min.x; x<max.x; x++)
	{
		for (unsigned int y=min.y; y<max.y; y++)
		{
			if (((x-center.x)*(x-center.x) + (y-center.y)*(y-center.y) ) <= r_sq)
				m_histogram.AddSample(inputFrame.pixel[x][y].chanel[VALUE]);
		}
	}
	m_histogram.Output(m_valueKDE, false);
	
	// Normal hue
	m_histogram.Reset();
	for (unsigned int x=min.x; x<max.x; x++)
	{
		for (unsigned int y=min.y; y<max.y; y++)
		{
			if (((x-center.x)*(x-center.x) + (y-center.y)*(y-center.y) ) <= r_sq)
				m_histogram.AddSample(inputFrame.pixel[x][y].chanel[HUE]);
		}
	}
	m_histogram.Output(m_normKDE, false);

	// Reddish hue
	m_reddishHistogram.Reset();
	for (unsigned int x=min.x; x<max.x; x++)
	{
		for (unsigned int y=min.y; y<max.y; y++)
		{
			if (((x-center.x)*(x-center.x) + (y-center.y)*(y-center.y) ) <= r_sq)
				m_reddishHistogram.AddSample((inputFrame.pixel[x][y].chanel[HUE] > 0.5f) ? 
					inputFrame.pixel[x][y].chanel[HUE] - 1.0f : inputFrame.pixel[x][y].chanel[HUE]);
		}
	}
	m_reddishHistogram.Output(m_reddishKDE, false);
}

bool Classifier::ClassificationUnlikely(unsigned char idx)
{
	// find the min classfication cost
	float min = 1.0f + PROXIMITY_FACTOR;
	for (unsigned char i=0; i<BALL_MAX; i++)
	{
		if (m_costMatrix[idx][i] < min)
			min = m_costMatrix[idx][i];
	}

	// If this cost is still too high, classification is unlikely
	if (min > MAX_CLASSIFICATION_COST_LIKELY)
		return true;
	else
		return false;
}