#ifndef Classifier_h

#define Classifier_h

#include "stdafx.h"
#include "config.h"
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>




using namespace std;
using namespace cv;
class Classifier {
public:
	Classifier();
	void begin();
	void classify(Mat, vector<Point2f>, vector<float>, vector<bool>&);
	void end(vector<Point2f>&,vector<float>&,vector<int>&);

private: 
	vector<vector<float>> valueTable;
	vector<Point2f> centerTable;
	vector<float>radiusTable;

	bool checkEachBall(Mat,vector<Point2f>,vector<float>,int);
	float getRatioInRange(Mat, Mat &,int,Scalar, Scalar,Scalar=Scalar(0,0,0),Scalar=Scalar(0,0,0));

	float checkSolidYellow(Mat,Mat,int);
	float checkSolidBlue(Mat, Mat, int);
	float checkSolidRed(Mat, Mat, int);
	float checkSolidViolet(Mat, Mat, int);
	float checkSolidOrange(Mat, Mat, int);
	float checkSolidGreen(Mat, Mat, int);
	float checkSolidMaroon(Mat, Mat, int);
	float checkSolidBlack(Mat, Mat, int);
	float checkStripedYellow(Mat, Mat, int);
	float checkStripedBlue(Mat, Mat, int);
	float checkStripedRed(Mat, Mat, int);
	float checkStripedViolet(Mat, Mat, int);
	float checkStripedOrange(Mat, Mat, int);
	float checkStripedGreen(Mat, Mat, int);
	float checkStripedMaroon(Mat, Mat, int);
	float checkSolidWhite(Mat, Mat, int);

};

#endif
