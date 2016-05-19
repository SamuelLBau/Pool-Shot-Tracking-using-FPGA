

#include "stdafx.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
#include "videoProcessingFuncs.h"
#include "config.h"

using namespace std;
using namespace cv;

Mat processVideo(Mat inImage,Size insize, bool averageTable, int averageCount,  VideoWriter maskVWriter, VideoWriter tableVWriter, VideoWriter circlesVWriter)
{
	static Mat tempImage1;
	static Mat tempImage2;
	static Mat tableImage; //If I need to save space, can reuse out/temp images
	static Mat outImage;
	
	//tableImage should be in the gaussian blurred image table in HSV space
	tableImage = getTable(inImage,insize,tempImage1,tempImage2,averageTable=averageTable,averageCount=averageCount);

	//TODO: detectedBallList = locateBilliardBalls(tableImage,insize,tempImage1,tempImage2);

	//TODO: reccomendedShot = reccomendShot(detectedBallList,insize);

	//NOTE: To save space, will re-use tempImage1
	//TODO: drawnBallImage = drawBilliardBalls(tableImage,insize,detectedBallList);

	//NOTE: To save space, will re-use outImage
	//TODO drawnShotAndBall = drawRecommendedShot(drawnBallImage,insize,reccomendedShot);

	//temporary line until draw code is added
	outImage = tableImage;
	
	//inImage.copyTo(outImage);
	//cvtColor(inImage, outImage, CV_RGB2HSV);
	//cout << "Num channels= " << outImage.channels() << endl;
	//cout << "outImage Size [" << outImage.rows << "," << outImage.cols << "]" << endl;



	#if DEBUG
		//imshow("tableImage", outImage);          //print image to screen
		//waitKey(33);          //delay 33ms
	#endif


	if (maskVWriter.isOpened())
	{
		//maskVWriter.write(outImage);
	}
	if (tableVWriter.isOpened())
	{
		tableVWriter.write(tableImage);
	}
	if (circlesVWriter.isOpened())
	{
		//circlesVWriter.write(circlesImage);
	}

	return outImage;
}
Mat getTable(Mat inImage,Size inSize,Mat tempImage1,Mat tempImageHSV,bool averageTable,int averageCount)
{
	//USED IN SUBTRACTIVE THRESHOLDING
	static int HIST_THRESHOLD = 30000;
	static int count = 0;
	//USED IN ADDITIVE THRESHOLDING
	//THIS IS AFFECTED BY LIGHTING ETC.
	static uchar THRESH_LOW = 0;
	static uchar THRESH_HIGH = 10;

	static Mat histogram;
	static Mat tempHistogram;
	static Mat histLUT(1, 256, CV_8U);
	static uchar generalCounter = 0;
	Mat hsv_channels[3];
	static int histSize = 180;
	static float range[] = { 0, 180 }; //the upper boundary is exclusive
	static const float* histRange = { range };
	static Mat singleChannelFrame1 = Mat(inSize.height, inSize.width, CV_8U);
	static Mat singleChannelFrame2 = Mat(inSize.height, inSize.width, CV_8U);
	static Point2f rectPoints[4] = { Point2f(0.0,0.0) };   //The bounds of the table output this frame
	static Point2f newRectPoints[4] = { Point2f(0.0,0.0) }; //the bounds of the table calculated this frame



	//singleChannelFrame1 = hsv_channels[0] > THRESHOLD;
	//singleChannelFrame2.setTo(0, singleChannelFrame1);

	/*
		inImage- the input image
		tempImage1/2 -working frames
	*/
	if (!averageTable | (averageTable & (count < averageCount)))
	{

		GaussianBlur(inImage, tempImage1, Size(3, 3), 0, 0, 0);
		cvtColor(tempImage1, tempImageHSV, CV_RGB2HSV);

		split(tempImageHSV, hsv_channels);

		//NOTE: DO NOT EDIR tempIMAGE2 after this point

		//NOTE: THIS IS THE SUBTRACTIVE METHOD OF GENERATING TABLE MASK
		//CONSIDER HARDCODING VALUE FOR THE ADDITIVE METHOD
		#if TABLE_SUBTRACTIVE_MASK
			calcHist(&hsv_channels[0], 1, 0, Mat(), histogram, 1, &histSize, &histRange, true, false);
			for (generalCounter = 0;generalCounter < histSize; generalCounter++)
			{
				if (histogram.at<float>(generalCounter, 0) > HIST_THRESHOLD)
					histLUT.at<uchar>(generalCounter) = 0;
				else
					histLUT.at<uchar>(generalCounter) = 255;
			}
			//singleChannelFrame1 should now have the masked image
			LUT(hsv_channels[0], histLUT, singleChannelFrame1);
		#endif
		#if TABLE_ADDITIVE_MASK
			threshold(hsv_channels[0], singleChannelFrame1, THRESH_LOW, 255, THRESH_TOZERO);
			threshold(hsv_channels[0], singleChannelFrame2, THRESH_HIGH, 255, THRESH_TOZERO_INV);
			singleChannelFrame2 = singleChannelFrame2 & singleChannelFrame1;
			threshold(singleChannelFrame2, singleChannelFrame1, 1, 255, THRESH_BINARY);
		#endif
		#if DEBUG
			//imshow("table mask", singleChannelFrame1);
			//waitKey(33);          //delay 33ms
		#endif
//------------------------------------------------------------------
//THIS SEGMENT FINDS THE TABLE CONTOUR
		vector<vector<Point>> contourList;
		findContours(singleChannelFrame1, contourList, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);
		double maxArea = 0;
		int maxIndex = 0;
		int numContours = contourList.size();
		double curArea = 0;

		for (int generalCounter = 0;generalCounter < numContours; generalCounter++)
		{
			curArea = contourArea(contourList[generalCounter]);
			if (curArea > maxArea)
			{
				maxArea = curArea;
				maxIndex = generalCounter;
			}
		}




		//hsv_channels[0] = bitwise_and(singleChannelFrame2, inImage);
		#if DEBUG
			drawContours(singleChannelFrame2, contourList, maxIndex, Scalar(255, 255, 255), -1);
			//imshow("table contour", singleChannelFrame2);
			//waitKey(33);          //delay 33ms
		#endif








	//THIS IS RESPONSIBLE FOR DETERMINING TABLE BOUNDS
	//------------------------------------------------------------------
	//THIS IS THE SIMPLE MINRECT METHOD
	//---------------------------------------------------
		#if RECTANGLE_SIMPLE_METHOD
			RotatedRect rect = minAreaRect(contourList[maxIndex]);
			rect.points(newRectPoints);
		#endif
		#if RECTANGLE_HOUGH_METHOD
			//TODO: USE HOUGH LINES TO FIND REAL EDGES OF TABLE
			imshow("singleChannelFrame1", singleChannelFrame1);
			waitKey(33);          //delay 33ms
			imshow("singleChannelFrame2", singleChannelFrame2);
			waitKey(33);          //delay 33ms
			singleChannelFrame2 = Scalar(0, 0, 0);
			drawContours(singleChannelFrame2, contourList, maxIndex, Scalar(255, 255, 255), -1);
			bitwise_and(singleChannelFrame2, singleChannelFrame1, singleChannelFrame1);

			//vector<Vec2f> lines;
			//HoughLinesP(singleChannelFrame1, lines,);



			imshow("masked", singleChannelFrame2);
			waitKey(33);          //delay 33ms
			imshow("maskedTable", singleChannelFrame1);
			waitKey(33);          //delay 33ms
		#endif
		//calculated rect points should be in newRectPoints now


		//if I want to average the table on init. use this
			//this either averages the table, or just used the calculated value
		if (averageTable & count < averageCount)
		{
			averageRectFunc(newRectPoints, count, rectPoints);
			count++;
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				rectPoints[i] = newRectPoints[i];
			}
		}


	} //closes find new table value
	//uses rectPoints after this point

	



	//----------------------------------------------------
	//TODO: Since we are rotating to fit, is this necessary?
	//TODO: DrawContour the rectangle, bitwise and it with the initial image (held in hsv_channels[0])
	//



	//THIS GENERATES THE AFFINE TRANSFORM FOR THE ROTATION

	int yMax = 0;
	int xMax = 0;
	int yVar = 0;
	int xVar = 0;
	for (int i = 0; i < 4;i++)
	{
		for (int j = 0;j < 4;j++)
		{
			yVar = rectPoints[i].y - rectPoints[j].y;
			xVar = rectPoints[i].x - rectPoints[j].x;
			if (xVar > xMax)
				xMax = xVar;
			if (yVar > yMax)
				yMax = yVar;

		}
	}
	if (yMax > xMax)
	{
		//TODO: check these for pointer issues
		//also check for correctness
		Point2f temp = rectPoints[0];
		rectPoints[0] = rectPoints[1];
		rectPoints[1] = rectPoints[2];
		rectPoints[2] = rectPoints[3];
		rectPoints[3] = temp;
	}
	//TODO: Check these for correctness
	Point2f affineRectCorners[3];
	affineRectCorners[0] = rectPoints[1];
	affineRectCorners[1] = rectPoints[2];
	affineRectCorners[2] = rectPoints[3];
	Point2f frameCorners[3];
	frameCorners[0] = Point2f(0, 0);
	frameCorners[1] = Point2f(inSize.width, 0);
	frameCorners[2] = Point2f(inSize.width, inSize.height);
	Mat rotMat = getAffineTransform(affineRectCorners, frameCorners);

	warpAffine(inImage, tempImage1, rotMat, inSize);


	//imshow("Rotated Table", tempImage1);
	//waitKey(33);          //delay 33ms

	return tempImage1;

	/*
		THIS MAY NOT BE NECESSARY
	//This merges all of the layers and outputs
	//TODO: affine transform each layer together
	vector<Mat> tempTable;
	tempTable.push_back(singleChannelFrame1);
	tempTable.push_back(hsv_channels[1]);
	tempTable.push_back(hsv_channels[2]);
	merge(&tempTable[0], 3, tempImage1);

	return singleChannelFrame1;
	*/

}
void averageRectFunc(Point2f inBox[4], int curCount, Point2f outBox[4])
{

	for (int i = 0; i < 4;i++)
	{
		outBox[i].x = (outBox[i].x * curCount + inBox[i].x)/(float)(curCount+1);
		outBox[i].y = (outBox[i].y * curCount + inBox[i].y) / (float)(curCount + 1);
	}

}
