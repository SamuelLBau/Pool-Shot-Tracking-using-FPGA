// Olga Souverneva 2016

#include "ClassifierTypes.h"
#include "ClassifierConst.h"
#include "MunkresMatching.h"
#include "Histogram.h"
#include "Windows.h"

#ifndef _CLASSIFIER
#define _CLASSIFIER

// Class to handle ball classification that is iterative. Not a thread-safe 
// implementation. Caller is responsible for ensuring they perform 
// Begin/Classify/Output as this class does not enforce it.
class Classifier
{
public:
	// Constructor
	Classifier();

	// Must be called in the first iteration for a given frame to clear the previous data.
	void Begin();

	// Classification iteration
	// inputFrame - frame to classify in HSV format
	// detectedCenters - new centers detected in the iteration
	// radii - buffer of the radius for each center
	// found - output buffer for whether the center was successfully classifierd
	// size - size of the buffers
	void Classify(const HSV_Frame& inputFrame, Coordinates* detectedCenters, unsigned int* radii, bool* found, unsigned int size);

	// Gets the final classification from the 
	// labeledCenters - output buffer for centers that were labeled
	// labels - output buffer for the classification labels
	// labelsSize - size of output buffer
	void Output(Coordinates* labeledCenters, unsigned char* labels, unsigned char labelsSize);

	// The max number of points that can be passed
	static const unsigned int MAX_SIZE = MUNKRES_MAX_SIZE;

	// The label that will be used to indicate ball was not found
	static const unsigned char NOT_FOUND = 0xFF;

	// The number of threads to use. Must be > 1.
	static const unsigned int THREAD_CNT = 3;

	struct InputData
	{
		unsigned char begin;
		unsigned char end;
		Classifier* pClassifier;
	};

	// Breaks up the classification for multi thread parallelization. Thread cnt must be less than MAX_SIZE.
	void ClassifyThread(unsigned char begin, unsigned char end);

private:
	// Classify the entire cost matrix
	void ClassifyCostMatrix();

	HANDLE  m_hThreadArray[THREAD_CNT];
	const HSV_Frame* m_inputFrame;
	unsigned int* m_radii;
	bool* m_found;
	unsigned char m_offset;

	struct ClassificationData
	{
		Coordinates center;
		bool free;
		unsigned char label;
	};

	// Array of the current classifications. Valid if not-free.
	ClassificationData m_classificationData[MAX_SIZE];

	// Matrix for the cost associated with each ball match. Cost is 1-probability.
	float m_costMatrix[MAX_SIZE][MAX_SIZE];

	// The probability that a given image matches ball ids
	float m_probability[MAX_SIZE];

	// Helper function to get the next "free" row
	unsigned char GetNextFree();

	// Helper function to get the last "filled" row
	unsigned char GetLastFilled();

	// Helper function to remove unused rows from the cost matrix. Needs 
	// to be done before classifying.
	void RemoveEmptyRows();

	// Helper function to reset the clasification data
	void ResetClassificationData();

	static const unsigned char MAX_BINS = 0xFF;

	struct ThreadData
	{
		Histogram<float, MAX_BINS>*  histogram;
		Histogram<float, MAX_BINS>*  reddishHistogram;
		float* normKDE;
		float* reddishKDE;
		float* valueKDE;
	};
	
	// Helper function to compute the cost of a classification.
	void ComputeClassificationCost(unsigned char id, ThreadData* pThreadData, unsigned int radius);

	// Helper function to compute the probability for a given ball
	void ComputeBallKDE(const Coordinates& min, const Coordinates& max, const Coordinates& center, int radius, ThreadData* pThreadData);

	// Helper function to compute the probability for a given ball
	float GetBallProbability(BallId id, ThreadData* pThreadData);

	// Helper function to determine if the ball is most likely not a ball
	bool ClassificationUnlikely(unsigned char idx);
};

#endif