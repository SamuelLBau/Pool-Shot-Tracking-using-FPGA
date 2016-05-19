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
Mat processVideo(Mat,Size,bool averageTable=false,int averageCount=30,VideoWriter maskVWriter=VideoWriter(),VideoWriter tableVWriter=VideoWriter(),VideoWriter circlesVWriter=VideoWriter());
Mat getTable(Mat,Size,Mat,Mat,bool averageTable =false,int averageCount=30);
void averageRectFunc(Point2f[4], int, Point2f[4]);
#endif