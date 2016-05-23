#ifndef videoProcessingFuncs_h
#define videoProcessingFuncs_h

using namespace std;
using namespace cv;

#include "stdafx.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
#include "config.h"

//this should encapsulate all of the processing
//void getContour
void debugPotentialBalls(Mat, Point2f, float);
Scalar getBallColor(int);
void classifyContours(Mat, vector<Point2f>, vector<float>, vector<bool>);
void contourCircleDetails(vector<Point>, Size, Point2f &, float &,int);
bool checkContour(vector<Point>,vector<Point2f>,int);
void cropAndAppendContours(vector < vector<Point> >, vector < vector<Point>>, int, int);
Mat processVideo(Mat,Size,VideoWriter maskVWriter=VideoWriter(),VideoWriter tableVWriter=VideoWriter(),VideoWriter circlesVWriter=VideoWriter());
//TODO: Replace the int with OLGA's imageClassifier object
int identifyBalls(Mat, Size, int, vector<vector<Point>>, vector<Point2f>, vector<int>,int);
void locateBilliardBalls(Mat, Size,Mat[3],Mat,Mat,vector<Point2f>, vector<float>,vector<int>, VideoWriter);
void getTableBounds(Mat,Size,Point2f[4]);
void getTableImage(Mat, Size, Point2f[4], Mat);
void drawCurrentContours(Mat, Mat, vector<vector<Point>>);
void drawCurrentCircles(Mat, Mat, vector<Point2f>, vector<float>, vector<int>);
void tableSubtractBackground(Mat, Mat, Mat);
void getBallMask(Mat, Mat,Size, Mat[3],Mat,Mat);
void averageRectFunc(Point2f[4], int, Point2f[4]);
void averageImageFunc(Mat, float, Mat);
#endif