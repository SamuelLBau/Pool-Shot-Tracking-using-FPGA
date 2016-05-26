#include "stdafx.h"
#include "Classifier.h"
#include "config.h"
using namespace std;
using namespace cv;


//TODO: Pass extra channel frame thrugh check balls to assist with the thresholding
Classifier::Classifier()
{
}
void Classifier::begin()
{
	valueTable.clear();
	centerTable.clear();
	radiusTable.clear();
}
void Classifier::classify(Mat inImage, vector<Point2f> potentialPositions, vector<float> radii, vector<bool> &isBall)
{
	//Currently I am planning to only pass 1 at a time, but I am leaving interface open for multiple in case I change my mind
	for (int i = 0; i < potentialPositions.size();i++)
	{
		if (checkEachBall(inImage, potentialPositions, radii,i))
		{
			isBall.push_back(true);
		}
		else
		{
			isBall.push_back(false);
		}
	}
}
void Classifier::end(vector<Point2f>& ballCenters, vector<float> &ballRadii, vector<int>&ballIDs)
{
	if (valueTable.size() == 0)
		return;
	for (int i = 0; i < valueTable[0].size();i++)
	{
		static float maxVal;
		static int maxIndex;
		maxVal = 0;
		maxIndex = 0;
		for (int j = 0; j < valueTable.size();j++)
		{
			if (valueTable[j][i] > maxVal)
			{
				maxVal = valueTable[j][i];
				maxIndex = j;
			}
		}
		if (maxVal >= CLASSIFIER_MIN_POSITIVE)
		{
			ballCenters.push_back(centerTable[maxIndex]);
			ballRadii.push_back(BILLIARD_BALL_RADIUS); //May want to change this later
			ballIDs.push_back(i);
			valueTable.erase(valueTable.begin() + maxIndex); //Don't want to overlap balls
		}
	}
}
bool Classifier::checkEachBall(Mat inImage,vector<Point2f> potentialPositions, vector<float> radii,int i)
{
	static Rect ballROI;
	ballROI = Rect(potentialPositions[i].x - radii[i], potentialPositions[i].y - radii[i], 2 * radii[i], 2 * radii[i]);
	Mat croppedImage = Mat(inImage, ballROI);
	Mat maskChannel = Mat(croppedImage.rows, croppedImage.cols, CV_8U);
	static int inImageArea = radii[i] * radii[i] * 4;

	vector<float> ballImageVector = vector<float>(16);
	ballImageVector[SOLID_YELLOW_ID]= checkSolidYellow(croppedImage,maskChannel, inImageArea);
	ballImageVector[SOLID_BLUE_ID]=checkSolidBlue(croppedImage, maskChannel, inImageArea);
	ballImageVector[SOLID_RED_ID]=checkSolidRed(croppedImage, maskChannel, inImageArea);
	ballImageVector[SOLID_VIOLET_ID]=checkSolidViolet(croppedImage, maskChannel, inImageArea);
	ballImageVector[SOLID_ORANGE_ID] = checkSolidOrange(croppedImage, maskChannel, inImageArea);
	ballImageVector[SOLID_GREEN_ID] = checkSolidGreen(croppedImage, maskChannel, inImageArea);
	ballImageVector[SOLID_MAROON_ID] = checkSolidMaroon(croppedImage, maskChannel, inImageArea);
	ballImageVector[SOLID_BLACK_ID] = checkSolidBlack(croppedImage, maskChannel, inImageArea);
	ballImageVector[STRIPED_YELLOW_ID] = checkStripedYellow(croppedImage, maskChannel, inImageArea);
	ballImageVector[STRIPED_BLUE_ID] = checkStripedBlue(croppedImage, maskChannel, inImageArea);
	ballImageVector[STRIPED_RED_ID] = checkStripedRed(croppedImage, maskChannel, inImageArea);
	ballImageVector[STRIPED_VIOLET_ID] = checkStripedViolet(croppedImage, maskChannel, inImageArea);
	ballImageVector[STRIPED_ORANGE_ID] = checkStripedOrange(croppedImage, maskChannel, inImageArea);
	ballImageVector[STRIPED_GREEN_ID] = checkStripedGreen(croppedImage, maskChannel, inImageArea);
	ballImageVector[STRIPED_MAROON_ID] = checkStripedMaroon(croppedImage, maskChannel, inImageArea);
	ballImageVector[CUE_BALL_ID] = checkSolidWhite(croppedImage, maskChannel, inImageArea);

	for (int j = 0; j < 16; j++)
	{
		if (ballImageVector[j] >= CLASSIFIER_MIN_POSITIVE)
		{
			valueTable.push_back(ballImageVector);
			centerTable.push_back(potentialPositions[i]);
			radiusTable.push_back(radii[i]);
			return true;
		}
	}
	return false;
}
float Classifier::getRatioInRange(Mat inImage, Mat &maskChannel,int inImageArea,Scalar minRangeA, Scalar maxRangeA,Scalar minRangeB,Scalar maxRangeB)
{
	Mat maskChannel2;
	static float ratio;
	static Scalar channelSum;

	inRange(inImage, minRangeA, maxRangeA, maskChannel);
	threshold(maskChannel, maskChannel2, 1, 255, THRESH_BINARY);
	inRange(inImage, minRangeB, maxRangeB, maskChannel);
	bitwise_or(maskChannel, maskChannel2, maskChannel);
	channelSum = sum(maskChannel);
	ratio = (float)channelSum[0] / (255.0 * (float)inImageArea);

	return ratio;
}
float Classifier::checkSolidYellow(Mat croppedImage, Mat maskChannel,int inImageArea)
{
	float ratio= getRatioInRange(croppedImage, maskChannel, inImageArea, YELLOW_RANGE_MIN, YELLOW_RANGE_MAX);
	return ratio;
}
float Classifier::checkSolidBlue(Mat croppedImage, Mat maskChannel, int inImageArea)
{
	float ratio = getRatioInRange(croppedImage, maskChannel, inImageArea, BLUE_RANGE_MIN, BLUE_RANGE_MAX);
	return ratio;
}
float Classifier::checkSolidRed(Mat croppedImage, Mat maskChannel, int inImageArea)
{
	float ratio = getRatioInRange(croppedImage, maskChannel, inImageArea, RED_RANGE_MIN, RED_RANGE_MAX);
	return 0;
}
float Classifier::checkSolidViolet(Mat croppedImage, Mat maskChannel, int inImageArea)
{
	return 0;
}
float Classifier::checkSolidOrange(Mat croppedImage, Mat maskChannel, int inImageArea)
{
	float ratio = getRatioInRange(croppedImage, maskChannel, inImageArea, ORANGE_RANGE_MIN, ORANGE_RANGE_MAX);

	return 0;
}
float Classifier::checkSolidGreen(Mat croppedImage, Mat maskChannel, int inImageArea)
{
	float ratio = getRatioInRange(croppedImage, maskChannel, inImageArea, GREEN_RANGE_MIN, GREEN_RANGE_MAX);
	return 0;
}
float Classifier::checkSolidMaroon(Mat croppedImage, Mat maskChannel, int inImageArea)
{
	//float ratio = getRatioInRange(croppedImage, maskChannel, inImageArea, MAROON_RANGE_MIN, MAROON_RANGE_MAX);
	//return ratio;
	return 0;
}
float Classifier::checkSolidBlack(Mat croppedImage, Mat maskChannel, int inImageArea)
{
	float ratio = getRatioInRange(croppedImage, maskChannel, inImageArea, BLACK_RANGE_MIN, BLACK_RANGE_MAX);
	return 0;
}
float Classifier::checkStripedYellow(Mat croppedImage, Mat maskChannel, int inImageArea)
{
	float ratio = getRatioInRange(croppedImage, maskChannel, inImageArea, YELLOW_RANGE_MIN, YELLOW_RANGE_MAX, WHITE_RANGE_MIN, WHITE_RANGE_MAX);
	return ratio;
}
float Classifier::checkStripedBlue(Mat croppedImage, Mat maskChannel, int inImageArea)
{
	return 0;
}
float Classifier::checkStripedRed(Mat croppedImage, Mat maskChannel, int inImageArea)
{
	return 0;
}
float Classifier::checkStripedViolet(Mat croppedImage, Mat maskChannel, int inImageArea)
{
	return 0;
}
float Classifier::checkStripedOrange(Mat croppedImage, Mat maskChannel, int inImageArea)
{
	float ratio = getRatioInRange(croppedImage, maskChannel, inImageArea, ORANGE_RANGE_MIN, ORANGE_RANGE_MAX, WHITE_RANGE_MIN, WHITE_RANGE_MAX);
	return ratio;
}
float Classifier::checkStripedGreen(Mat croppedImage, Mat maskChannel, int inImageArea)
{
	return 0;
}
float Classifier::checkStripedMaroon(Mat croppedImage, Mat maskChannel, int inImageArea)
{
	return 0;
}
float Classifier::checkSolidWhite(Mat croppedImage, Mat maskChannel, int inImageArea)
{
	float ratio= getRatioInRange(croppedImage, maskChannel, inImageArea, WHITE_RANGE_MIN, WHITE_RANGE_MAX);
	return ratio;
}