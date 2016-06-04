// Olga Souverneva 2016

#include "ClassifierTypes.h"
#include "ClassifierConst.h"
#include "MunkresMatching.h"
#include "Histogram.h"

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

private:
	// Private overload to classify the probability tabel
	void Classify();

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

	// Helper function to compute the cost of a classification.
	void ComputeClassificationCost(unsigned char id, const HSV_Frame& inputFrame, unsigned int radius);

	// Helper function to compute the probability for a given ball
	void ComputeBallKDE(const HSV_Frame& inputFrame, const Coordinates& min, const Coordinates& max, const Coordinates& center, int radius);

	// Helper function to compute the probability for a given ball
	float GetBallProbability(BallId id);

	// Helper function to determine if the ball is most likely not a ball
	bool ClassificationUnlikely(unsigned char idx);

	// Buffer to store probability
	static const unsigned char MAX_BINS = 0xFF;
	Histogram<float, MAX_BINS>  m_histogram;
	Histogram<float, MAX_BINS>  m_reddishHistogram;
	float m_normKDE[MAX_BINS];
	float m_reddishKDE[MAX_BINS];
	float m_valueKDE[MAX_BINS];
};

#endif