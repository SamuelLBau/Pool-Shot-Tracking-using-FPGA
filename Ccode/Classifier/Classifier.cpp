// Olga Souverneva 2016
// Class to handle ball classification

#include "stdafx.h"
#include "Classifier.h"
#include "MunkresMatching.h"
#include "Value.h"
#include "ReddishHue.h"
#include "NormalHue.h"

static HSV_Pixel _ballImage[MAX_RADIUS][MAX_RADIUS] = {};

// Function for child threads to call
DWORD WINAPI MyThreadFunction(LPVOID lpParam);

Classifier::Classifier()
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

	// Compute the last available index.
	unsigned char end = size < (MAX_SIZE-start) ? start+size : MAX_SIZE;

	// Compute the max number of threads to create
	unsigned char threadCnt = end - start;
	threadCnt = threadCnt < THREAD_CNT ? threadCnt : THREAD_CNT;
	if (threadCnt == 0)
		return;

	// Save input data
	m_inputFrame = &inputFrame;
	m_radii = radii;
	m_found = found;
	m_offset = start;
	unsigned char j = start;
	for (unsigned char i=0; i < end; i++)
	{
		m_classificationData[j].center = detectedCenters[i];
		m_classificationData[j].free = false;
		j++;
	}

	// Fill in the thread data
	InputData* pInputData[THREAD_CNT];
	unsigned char step = (end - start)/threadCnt;
	if ((end - start)%threadCnt > 0)
		step++;
	unsigned char begin = 0;
	for (unsigned char i=0; i < threadCnt; i++)
	{
		pInputData[i] = (InputData*)HeapAlloc(GetProcessHeap(), 
			HEAP_ZERO_MEMORY, sizeof(InputData));
		pInputData[i]->begin = begin;
		pInputData[i]->pClassifier = this;
		if (i != threadCnt-1)
			pInputData[i]->end = begin + step;
		else
			pInputData[i]->end = end;
		begin = pInputData[i]->end;
	}

	// Create child threads
	for (unsigned char i=0; i < threadCnt; i++)
	{
		m_hThreadArray[i] = CreateThread( NULL, 0, MyThreadFunction, pInputData[i], 0, NULL);
	}

	// Wait for the threads to finish.
	WaitForMultipleObjects(threadCnt, m_hThreadArray, TRUE, INFINITE);

	// Close all handles & free all memory
	for (unsigned char i=0; i < threadCnt; i++)
	{
		CloseHandle(m_hThreadArray[i]);
		HeapFree(GetProcessHeap(), 0, pInputData[i]);
		pInputData[i] = NULL;
	}
}

void Classifier::ClassifyThread(unsigned char begin, unsigned char end)
{
	// Each thread needs its own
	Histogram<float, MAX_BINS>  histogram(NORMAL_HUE_MIN, NORMAL_HUE_MAX);
	Histogram<float, MAX_BINS>  reddishHistogram(REDDISH_HUE_MIN, REDDISH_HUE_MAX);
	float normKDE[MAX_BINS];
	float reddishKDE[MAX_BINS];
	float valueKDE[MAX_BINS];
	ThreadData data;
	data.histogram = &histogram;
	data.reddishHistogram = &reddishHistogram;
	data.normKDE = normKDE;
	data.reddishKDE = reddishKDE;
	data.valueKDE = valueKDE;
	
	// Fill in new rows of data.
	for (unsigned char i=begin; i<end; i++)
	{
		unsigned char j = i+m_offset;
		ComputeClassificationCost(j, &data, m_radii[i]);
	}

	// Mark any entries that are unlikely to be balls to be free to use in 
	// the next iteration. Output the not-found entries.
	for (unsigned char i=begin; i<end; i++)
	{
		unsigned char j = i+m_offset;
		if (ClassificationUnlikely(j))
		{
			m_found[i] = false;
			m_classificationData[j].free = true;
		}
		else
			m_found[i] = true;
	}
}

DWORD WINAPI MyThreadFunction(LPVOID lpParam)
{
	if (lpParam == NULL)
		return 1;

	Classifier::InputData* pData = (Classifier::InputData*)lpParam;
	pData->pClassifier->ClassifyThread(pData->begin, pData->end);
	return 0;
}

void Classifier::Output(Coordinates* labeledCenters, unsigned char* labels, unsigned char labelsSize)
{
	if (labeledCenters == NULL || labels == NULL || labelsSize > MAX_SIZE)
		return;
	
	// Classify the cost matrix
	ClassifyCostMatrix();
	
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

void Classifier::ClassifyCostMatrix()
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

void Classifier::ComputeClassificationCost(unsigned char id, Classifier::ThreadData* pThreadData, unsigned int radius)
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
	ComputeBallKDE(min, max, m_classificationData[id].center, newR, pThreadData);

	// Compute the cost matrix
	// Balls
	for (unsigned char i=0; i<BALL_MAX; i++)
	{
		// Cost is 1-probability
		m_costMatrix[id][i] = 1.0f + PROXIMITY_FACTOR - GetBallProbability(static_cast<BallId>(i), pThreadData);
	}
	// Not a ball
	for (unsigned char i=BALL_MAX; i<MAX_SIZE; i++)
	{
		m_costMatrix[id][i] = 1.0f + PROXIMITY_FACTOR;
	}
}

float Classifier::GetBallProbability(BallId id, Classifier::ThreadData* pThreadData)
{
	float out = 0.0f;
	float step = pThreadData->histogram->GetWidth();
	
	switch(id)
	{
	case BALL_8:
		{
			for (int i=0; i<MAX_BINS; i++)
			{
				float compare = GetValuePd(id, i);
				out += (pThreadData->valueKDE[i] < compare ? pThreadData->valueKDE[i] : compare)*step;
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
				out += (pThreadData->reddishKDE[i] < compare ? pThreadData->reddishKDE[i] : compare)*step;
			}
			break;
		}
	default:
		{
			for (int i=0; i<MAX_BINS; i++)
			{
				float compare = GetNormalHuePd(id, i);
				out += (pThreadData->normKDE[i] < compare ? pThreadData->normKDE[i] : compare)*step;
			}
			break;
		}
	}

	return out;
}

void Classifier::ComputeBallKDE(const Coordinates& min, const Coordinates& max, const Coordinates& center, int radius, 
								ThreadData* pThreadData)
{
	unsigned int r_sq = radius*radius;

	// Value
	pThreadData->histogram->Reset();
	for (unsigned int x=min.x; x<max.x; x++)
	{
		for (unsigned int y=min.y; y<max.y; y++)
		{
			if (((x-center.x)*(x-center.x) + (y-center.y)*(y-center.y) ) <= r_sq)
				pThreadData->histogram->AddSample(m_inputFrame->pixel[x][y].chanel[VALUE]);
		}
	}
	pThreadData->histogram->Output(pThreadData->valueKDE, false);
	
	// Normal hue
	pThreadData->histogram->Reset();
	for (unsigned int x=min.x; x<max.x; x++)
	{
		for (unsigned int y=min.y; y<max.y; y++)
		{
			if (((x-center.x)*(x-center.x) + (y-center.y)*(y-center.y) ) <= r_sq)
				pThreadData->histogram->AddSample(m_inputFrame->pixel[x][y].chanel[HUE]);
		}
	}
	pThreadData->histogram->Output(pThreadData->normKDE, false);

	// Reddish hue
	pThreadData->reddishHistogram->Reset();
	for (unsigned int x=min.x; x<max.x; x++)
	{
		for (unsigned int y=min.y; y<max.y; y++)
		{
			if (((x-center.x)*(x-center.x) + (y-center.y)*(y-center.y) ) <= r_sq)
				pThreadData->reddishHistogram->AddSample((m_inputFrame->pixel[x][y].chanel[HUE] > 0.5f) ? 
					m_inputFrame->pixel[x][y].chanel[HUE] - 1.0f : m_inputFrame->pixel[x][y].chanel[HUE]);
		}
	}
	pThreadData->reddishHistogram->Output(pThreadData->reddishKDE, false);
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