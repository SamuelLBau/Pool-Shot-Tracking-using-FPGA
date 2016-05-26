#include "stdafx.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
#include "videoProcessingFuncs.h"
#include "BilliardGame.h"
#include "Classifier.h"
#include "config.h"

using namespace std;
using namespace cv;

Mat processVideo(Mat inImage,Size inSize, VideoWriter maskVWriter, VideoWriter tableVWriter, VideoWriter circlesVWriter,VideoWriter maskedTableWriter)
{
	#if DEBUG_IN_IMAGE
		imshow("inImage", inImage);          //print image to screen
		//waitKey(33);          //delay 33ms
	#endif
	static Mat tempImage1 = Mat();//(inSize.height, inSize.width, inImage.type());
	static Mat tempImage2 = Mat();//(inSize.height, inSize.width, inImage.type());
	static Mat HSVImage = Mat();//(inSize.height, inSize.width, inImage.type());
	static Mat tableImage = Mat(inSize.height,inSize.width, inImage.type()); //If I need to save space, can reuse out/temp images
	static Mat outImage = Mat();//Mat(inSize.height, inSize.width, inImage.type());
	static Mat tempChannels[3];
	static Mat ballMask = Mat(inSize.height, inSize.width, CV_8U);
	static Mat ballMaskImage = Mat(inSize.height, inSize.width, inImage.type());
	static Point2f tableBounds[4];
	vector<Point2f> ballPoints;
	vector<float> ballRadii;
	vector<int> ballIDs;

	//In case system doesn't correctly set an output, should output something in all states
	inImage.copyTo(outImage);

	#if AVERAGE_BOX_POINTS
		static Point2f tempTableBounds[4];
		static int boxAverageFrameCount = 0;
	#endif

	#if AVERAGE_BG_FRAME
		static Mat BGImage = Mat(inSize.height, inSize.width, inImage.type(),Scalar(0,0,0)); //averaged image of the background
		static int BGAverageFrameCount = 0;
	#endif

	static int STATE = STATE_INIT;
	cout << "STATE = " << STATE << endl;

	if (STATE == STATE_INIT)
	{
		boxAverageFrameCount = 0;
		BGAverageFrameCount = 0;
		STATE = STATE_AVERAGE_TABLE;
	}

	inImage.copyTo(tempImage1);
	//GaussianBlur(inImage, tempImage1, Size(3, 3), 0, 0, 0);
	cvtColor(tempImage1, HSVImage, CV_RGB2HSV);

	#if AVERAGE_BOX_POINTS
		if (STATE == STATE_AVERAGE_TABLE)
		{
			if (boxAverageFrameCount < NUM_BOX_AVERAGE_FRAMES)
			{
				getTableBounds(HSVImage, inSize, tempTableBounds);
				averageRectFunc(tempTableBounds, boxAverageFrameCount, tableBounds);
				boxAverageFrameCount++;
			}
			if (boxAverageFrameCount == NUM_BOX_AVERAGE_FRAMES)
			{
				STATE = STATE_AVERAGE_BACKGROUND;
			}
		}
		getTableImage(inImage, inSize, tableBounds, tableImage);
	#else
		//if not averaging table, needs to be done every frame
		getTableBounds(HSVImage, inSize, tableBounds);
		getTableImage(inImage, inSize, tableBounds, tableImage);
		if (STATE == STATE_AVERAGE_TABLE)
		{
			STATE = STATE_AVERAGE_BACKGROUND;
		}
	#endif
	#if DEBUG_WARPED_TABLE
		imshow("Warped Table", tableImage);
	#endif
	#if AVERAGE_BG_FRAME
		#if !AVERAGE_BOX_POINTS
			int boxAverageFrameCount = 1000000;
		#endif
		if (STATE == STATE_AVERAGE_BACKGROUND)
		{
			if (BGAverageFrameCount < NUM_BG_AVERAGE_FRAMES)
			{
				averageImageFunc(tableImage, (float)BGAverageFrameCount, BGImage);
				BGAverageFrameCount++;
			}
			if (BGAverageFrameCount == NUM_BG_AVERAGE_FRAMES)
			{
				STATE = STATE_NORMAL_RUN;
			}
			#if WRITE_VIDEO 
				if (tableVWriter.isOpened())
				{
					tableVWriter.write(tableImage);
				}
			#endif
		}
	#else
		if (STATE == STATE_AVERAGE_BACKGROUND)
			STATE = STATE_NORMAL_RUN;
	#endif
#if DEBUG_BG_IMAGE && AVERAGE_BG_FRAME
	imshow("BG Image", BGImage);
#endif

		//NOTE: May want to update this to make a mask, then add BGImage back with the mask
		//This will prevent color distortion of our balls
	if (STATE == STATE_NORMAL_RUN)
	{
		//This likely no longer works
		#if TABLE_BG_SUBTRACTION_SIMPLE
			tableBackgroundSubtraction(tempImage1, BGImage, tableImage);
			cvtColor(tableImage, tableImage, CV_HSV2RGB);
		#else
			getBallMask(tableImage, BGImage, inSize, tempChannels, tempImage2, ballMask);
			#if DEBUG_INITIAL_BALL_MASK
				imshow("BALLMASK", ballMask);          //print image to screen
			#endif				  //tempImage1.copyTo(tableImage);
			#if DEBUG_TABLE_BALL_INITIAL_MASK
				tableImage.copyTo(tempImage1);
				bitwise_not(ballMask, tempChannels[0]);
				bitwise_and(tableImage, Scalar(0), tempImage1, tempChannels[0]);

				//cvtColor(tableImage, tableImage, CV_HSV2RGB);

				imshow("ballMaskedTableImage", tempImage1);          //print image to screen
				#if WRITE_VIDEO
					if (maskedTableWriter.isOpened())
					{
						maskedTableWriter.write(tempImage1);
					}
				#endif
				//waitKey(33);          //delay 33ms
			#endif
		#endif
		#if WRITE_VIDEO 
			if (maskVWriter.isOpened())
			{
				maskVWriter.write(ballMask);
			}
		#endif
	//NOTE: If I want tableimage to be in RGBspace, I should change HSVImage to inImage for getTableImage call


		ballPoints.clear();
		ballRadii.clear();
		ballIDs.clear();
		#if CLASSIFY_ON_HSV
			cvtColor(tableImage, HSVImage, CV_RGB2HSV);
			locateBilliardBalls(ballMask, inSize,tempChannels, HSVImage,tempImage1,ballPoints, ballRadii,ballIDs, maskVWriter,circlesVWriter);
		#else
			locateBilliardBalls(ballMask, inSize, tempChannels, tableImage, tempImage1, ballPoints, ballRadii, ballIDs, maskVWriter, circlesVWriter);
		#endif

		//NOTE: To save space, will re-use tempImage1
			//tableImage.copyTo(outImage);
		drawBilliardBalls(tableImage,outImage,ballPoints,ballRadii,ballIDs);

		vector<Point2f> shotLines;
		vector<Point2f> collisionCircles;
		vector<float> collisionRadii;
		getRecommendedShot(ballPoints,ballIDs,ballRadii,inSize,collisionCircles,collisionRadii,shotLines);

		drawRecommendedShot(outImage, collisionCircles, collisionRadii, shotLines);
		//temporary line until draw code is added
		//outImage = tableImage;
	}
	return outImage;
}
Scalar getBallColor(int ballID)
{
	switch (ballID)
	{
		//NOTE: THESE SHOULD BE BGR COLOR, not RGB
	case CUE_BALL_ID: return Scalar(255, 255, 255); //Cue Ball
	case SOLID_YELLOW_ID: return Scalar(0, 255, 255); //Solid Yellow Ball
	case SOLID_BLUE_ID: return Scalar(255, 0, 0); //Solid Blue Ball
	case SOLID_RED_ID: return Scalar(0, 0, 255); //Solid Red Ball
	case SOLID_VIOLET_ID: return Scalar(255, 0, 255); //Solid Violet Ball
	case SOLID_ORANGE_ID: return Scalar(0, 100, 255); //Solid Orange Ball
	case SOLID_GREEN_ID: return Scalar(0, 255, 0); //Solid Green Ball
	case SOLID_MAROON_ID: return Scalar(0, 50, 120); //Solid Maroon Ball
	case SOLID_BLACK_ID: return Scalar(0, 0, 0); //Solid Black Ball
	case STRIPED_YELLOW_ID: return Scalar(0, 255, 255); //Striped Yellow Ball
	case STRIPED_BLUE_ID: return Scalar(255, 0, 0); //Striped Blue Ball
	case STRIPED_RED_ID: return Scalar(0, 0, 255); //Striped Red Ball
	case STRIPED_VIOLET_ID: return Scalar(255, 0, 255); //Striped Violet Ball
	case STRIPED_ORANGE_ID: return Scalar(0, 100, 255); //Striped Orange Ball
	case STRIPED_GREEN_ID: return Scalar(0, 255, 0); //Striped Green Ball
	case STRIPED_MAROON_ID: return Scalar(0, 50, 120); //Striped Maroon Ball
	default: return Scalar(-1, -1, -1);//Invalid ID
	}
}
void getRecommendedShot(vector<Point2f> ballPoints, vector<int> ballIDs, vector<float> ballRadii,Size inSize,vector<Point2f> &collisionCircles,vector<float>&collisionRadii,vector<Point2f>&shotLines)
{
	BilliardGame BG = BilliardGame(ballPoints,ballIDs,ballRadii,inSize,&collisionCircles,&collisionRadii,&shotLines);

	return;
}
void drawRecommendedShot(Mat outImage, vector<Point2f>circlePoints, vector<float>circleRadii, vector<Point2f>linePoints)
{
	for (int i = 0; i < circlePoints.size();i++)
	{
		circle(outImage, circlePoints[i], circleRadii[i], Scalar(0, 0, 255), 2);
	}
	for (int i = 0; i < ((int)linePoints.size()-1);i+=2)
	{
		line(outImage, linePoints[i], linePoints[i + 1], Scalar(0, 0, 255), 2);
	}
}
void locateBilliardBalls(Mat ballMask, Size inSize,Mat tempChannel[3],Mat tableImage,Mat tempImage,vector<Point2f> &ballPoints, vector<float> &ballRadii,vector<int> &ballIDs,VideoWriter maskWriter,VideoWriter circlesWriter)
{
	int largeErosionSize = INIT_EROSION_SIZE;
	int largeErosionType = MORPH_ELLIPSE;
	Mat initErosionElement = getStructuringElement(largeErosionType,
		Size(2 * largeErosionSize + 1, 2 * largeErosionSize + 1));

	int smallErosionSize = LOOP_EROSION_SIZE;
	int smallErosionType = MORPH_ELLIPSE;
	Mat loopErosionElement = getStructuringElement(smallErosionType,
		Size(2 * smallErosionSize + 1, 2 * smallErosionSize + 1));

	int initDilationSize = INIT_DILATION_SIZE;
	int dilationType = MORPH_ELLIPSE;
	Mat initDilationElement = getStructuringElement(dilationType,
		Size(2 * initDilationSize + 1, 2 * initDilationSize + 1));

	int loopDilationSize = LOOP_DILATION_SIZE;
	Mat loopDilationElement = getStructuringElement(dilationType,
		Size(2 * loopDilationSize + 1, 2 * loopDilationSize + 1));


	vector<vector<Point>> contourList;
	vector<vector<Point>> potentialBallContours;
	vector<Point2f> validBallList;
	vector<int> validBallIDs;
	erode(ballMask, tempChannel[1],initErosionElement,Point(-1,-1),INIT_EROSION_ITERATIONS);
	dilate(tempChannel[1], tempChannel[0], initDilationElement, Point(-1, -1), INIT_DILATION_ITERATIONS);
	//imshow("ERDI images", tempChannel[1]);
	int sourceIndex;
	int dstIndex;
	Classifier imageClassifier;//placeholder for olga's object
	imageClassifier.begin();
	for (int i = 0; i < NUM_EROSION_LOOP_ITERATIONS; i++)
	{
		potentialBallContours.clear();
		contourList.clear();
		//if (i == 3)
		{
			maskWriter.write(tempChannel[0]);
		}
		tempChannel[0].copyTo(tempChannel[2]);
		#if DEBUG_ERODED_MASKS
			imshow(to_string(i), tempChannel[0]);
		#endif
		findContours(tempChannel[0], contourList, CV_RETR_LIST, CHAIN_APPROX_SIMPLE);
		//no more contours, no reason to do the difficult calculations
		if (contourList.size() == 0)
			break;
		int addedCount = 0;
		for (int j = 0; j < contourList.size(); j++)
		{
			if (checkContour(contourList[j], validBallList,j))
			{
				addedCount++;
				potentialBallContours.push_back(contourList[j]);
			}
		}
		identifyBalls(tableImage, inSize, imageClassifier, potentialBallContours, validBallList, validBallIDs, i, circlesWriter);
		erode(tempChannel[2], tempChannel[1], loopErosionElement,Point(-1,-1),LOOP_EROSION_ITERATIONS);
		dilate(tempChannel[1], tempChannel[0], loopDilationElement, Point(-1, -1), LOOP_DILATION_ITERATIONS);
	}
	#if USE_SAMS_CLASSIFIER
		imageClassifier.end(ballPoints,ballRadii,ballIDs);
	#else
		for (int i = 0; i < validBallList.size(); i++)
		{
			ballPoints.push_back(validBallList[i]);
			ballRadii.push_back(BILLIARD_BALL_RADIUS);
			ballIDs.push_back(validBallIDs[i]);
		}
	#endif
	
	cout << "Finished finding balls this frame" << endl;
}
int identifyBalls(Mat inImage,Size inSize,Classifier &imageClassifier, vector<vector<Point>>potentialBallContours,vector<Point2f> &validBallList, vector<int>&validBallIDs,int iteration,VideoWriter circleWriter)
{
	//PotentialBallContours are all contours that may be a ball
	//Iterate through each of them, create a center list, radii list and then send to Olga's cost
	static vector<Point2f> circleCenters;
	static vector<float> circleRadii;
	static vector<bool> isBallList;
	static vector<int> ballIDList;
	Point2f curCircle;
	float radius;
	circleCenters.clear();
	circleRadii.clear();
	isBallList.clear();
	ballIDList.clear();
	for (int i = 0; i < potentialBallContours.size();i++)
	{
		contourCircleDetails(potentialBallContours[i],inSize,curCircle,radius,iteration);
		circleCenters.push_back(curCircle);
		circleRadii.push_back(radius);
		#if DEBUG_POTENTIAL_BALLS
			debugPotentialBalls(inImage, curCircle, radius, circleWriter);
		#endif
	}
	#if USE_SAMS_CLASSIFIER
		imageClassifier.classify(inImage, circleCenters, circleRadii, isBallList);
	#else
		classifyContours(inImage, circleCenters, circleRadii, isBallList, ballIDList,iteration);
	#endif

	for (int i = 0; i < isBallList.size(); i++)
	{
		if (isBallList[i])
		{
			//cout << ballIDList[i] << endl;
			validBallList.push_back(circleCenters[i]);
			#if !USE_SAMS_CLASSIFIER
				validBallIDs.push_back(ballIDList[i]);
			#endif
		}
	}
	return 0;
}
void debugPotentialBalls(Mat inImage, Point2f circleCenter, float radius,VideoWriter circleWriter)
{
	static int writtenCount = 0;
	//cout << circleCenter.x + radius << "|" << circleCenter.y + radius << endl;
	
	Rect ballROI = Rect(circleCenter.x - radius, circleCenter.y - radius, 2 * radius, 2 * radius);
	Mat curBallImage = Mat(inImage, ballROI);
	#if DEBUG_POTENTIAL_BALLS_SHOW
		imshow("Potential Ball:", curBallImage);
	#endif
	#if WRITE_VIDEO_CIRCLES
		Rect ballROITOVID = Rect(circleCenter.x - RADIUS_MIN, circleCenter.y - RADIUS_MIN, 2 * RADIUS_MIN, 2 * RADIUS_MIN);
		Mat curBallImageTOVID = Mat(inImage, ballROITOVID);
		circleWriter.write(curBallImageTOVID);
	#endif
	int returnChar = 0;
	#if MANUAL_INPUT_ISBALL
		returnChar = waitKey(0);
	#endif
		//TODO: CHANGE Q
	//121==y
	//110 ==n
	char outFile[80] = "./ballIdentification/";
	switch (returnChar)
	{
	case 49:strcat_s(outFile, "CueBall/");
		break;
	case 50:strcat_s(outFile, "SolidYellow/");
		break;
	case 51:strcat_s(outFile, "SolidBlue/");
		break;
	case 52:strcat_s(outFile, "SolidRed/");
		break;
	case 53:strcat_s(outFile, "SolidViolet/");
		break;
	case 54:strcat_s(outFile, "SolidOrange/");
		break;
	case 55:strcat_s(outFile, "SolidGreen/");
		break;
	case 56:strcat_s(outFile, "SolidMaroon/");
		break;
	case 57:strcat_s(outFile, "SolidBlack/");
		break;
	case 48:strcat_s(outFile, "StripedYellow/");
		break;
	case 113:strcat_s(outFile, "StripedBlue/");
		break;
	case 119:strcat_s(outFile, "StripedRed/");
		break;
	case 101:strcat_s(outFile, "StripedViolet/");
		break;
	case 114:strcat_s(outFile, "StripedOrange/");
		break;
	case 116:strcat_s(outFile, "StripedGreen/");
		break;
	case 121:strcat_s(outFile, "StripedMaroon/");
		break;
	case 117:strcat_s(outFile, "NotABall/");
		break;
	case 105:strcat_s(outFile, "OccludedOrMixed/");
		break;
	case 110://Do not add to folders
		break;
	default:
		returnChar = 110;
		break;
	}
	
#if !MANUAL_INPUT_ISBALL
	returnChar = 110;
#endif

	if (returnChar != 110)
	{
		vector<int> compression_params;
		compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
		compression_params.push_back(9);
		strcat_s(outFile,to_string(writtenCount).c_str());
		strcat_s(outFile, ".png");
		imwrite(outFile, curBallImage, compression_params);
		writtenCount++;
	}
}
void classifyContours(Mat inImage,vector<Point2f> &circleCenters,vector<float>&circleRadii,vector<bool>&isBall,vector<int> &ballIDs,int iteration)
{
	//Placeholder for olga's code, just say all are balls
	for (int i = 0; i < circleCenters.size();i++)
	{
		//For this test, just say all contours are cur balls
		isBall.push_back(true);
		ballIDs.push_back((iteration*5)%2+14);
		
	}
}
void contourCircleDetails(vector<Point> contour, Size inSize,Point2f &curCircle, float &radius, int iteration)
{
	int minRadius = RADIUS_MIN;// -iteration * 10;
	if (minRadius < 0)
		minRadius = 0;
	int maxRadius = RADIUS_MAX;
	minEnclosingCircle(contour, curCircle, radius);
	//cout << "RADIUS:" << radius << endl;
	if (radius < minRadius)
		radius = minRadius;
	if (radius > maxRadius)
		radius = maxRadius;
	//cout << "Adjusted RADIUS:" << radius << endl;
	//cout << curCircle.x << "|" << curCircle.y << endl;
	if (curCircle.y + radius > inSize.height)
		curCircle.y = inSize.height - radius;
	else if (curCircle.y - radius < 0)
		curCircle.y = radius;

	if (curCircle.x + radius > inSize.width)
		curCircle.x = inSize.width - radius;
	else if (curCircle.x - radius < 0)
		curCircle.x = radius;
}
bool checkContour(vector<Point> contour, vector<Point2f> validBallList,int iteration)
{
	//Use check contour to eliminate contours
	int minArea;
	if (iteration > 1)
		minArea = 10;
	else
		minArea= CONTOUR_MIN_AREA - 30 * iteration;

	int maxArea = CONTOUR_MAX_AREA;
	static int writtenCount = 0;
	double area = contourArea(contour);
	if (area < minArea || area > maxArea)
	{
		return false;
	}
	float perimeter = arcLength(contour,true);
	#if EXCLUDE_CIRCULARITY
		double eccentricity = FOUR_PI * area / (perimeter * perimeter);
		if (eccentricity < MIN_CIRCULARITY)
			return false;
	#endif
	#if EXCLUDE_NEAR_BALLS
		Point2f curCenter;
		float radius;
		minEnclosingCircle(contour, curCenter, radius);
		float dist;
		for (int i = 0; i < validBallList.size();i++)
		{
			double dist = norm(curCenter - validBallList[i]);
			if (dist < BLOB_MIN_SEPARATION + BILLIARD_BALL_RADIUS)
				return false;
		}
	#endif
	//TODO: Check if contour contains a valid ball contour
	//if so, return true
	return true;
}
void cropAndAppendContours(vector < vector<Point> >newContours, vector < vector<Point>> allContours, int minArea, int maxArea)
{
	double curArea;
	for (int i = 0; i < newContours.size();i++)
	{
		curArea = contourArea(allContours[i]);
		if (curArea > minArea && curArea < maxArea)
		{
			allContours.push_back(allContours[i]);
		}
	}
}
void drawBilliardBalls(Mat inImage, Mat outImage, vector<Point2f> circleCenterList, vector<float> circleRadiiList,vector<int> ballIDs)
{
	inImage.copyTo(outImage);
	for (int i = 0; i < circleCenterList.size(); i++)
	{
		Scalar color = getBallColor(ballIDs[i]);
		circle(outImage, circleCenterList[i], circleRadiiList[i], color, -1);
		if (ballIDs[i] > 8)
		{
			//These balls are striped, add an inner circle
			circle(outImage, circleCenterList[i], circleRadiiList[i] * .5, Scalar(255, 255, 255), -1);
		}
	}
}
void drawCurrentContours(Mat inImage, Mat outImage, vector<vector<Point>> contourList)
{
	inImage.copyTo(outImage);
	for (int i = 0; i < contourList.size();i++)
	{
		drawContours(outImage, contourList, i, Scalar((i * 30 % 255), (i * 30 % 255), (i * 30 % 255)),-1);
	}
}
void getTableBounds(Mat inImage,Size inSize,Point2f tableBounds[4])
{
	//ASSUME inImage is already HSV

	//USED IN SUBTRACTIVE THRESHOLDING
	static int HIST_THRESHOLD = 30000;
	static int boxAverageFrameCount = 0;
	static int BGAverageFrameCount = 0;
	//USED IN ADDITIVE THRESHOLDING
	//THIS IS AFFECTED BY LIGHTING ETC.

	static Mat histogram;
	static Mat tempHistogram;
	static Mat histLUT(1, 256, CV_8U);
	static uchar generalCounter = 0;
	static Mat hsv_channels[3];
	static int histSize = 180;
	static float range[] = { 0, 180 }; //the upper boundary is exclusive
	static const float* histRange = { range };
	static Mat singleChannelFrame1;
	static Mat singleChannelFrame2;
	static Point2f rectPoints[4] = { Point2f(0.0,0.0) };   //The bounds of the table output this frame
	static Point2f newRectPoints[4] = { Point2f(0.0,0.0) }; //the bounds of the table calculated this frame

	split(inImage, hsv_channels);

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
			threshold(hsv_channels[0], singleChannelFrame1, TABLE_ADDITIVE_THRESH_LOW, 255, THRESH_TOZERO);
			threshold(hsv_channels[0], singleChannelFrame2, TABLE_ADDITIVE_THRESH_HIGH, 255, THRESH_TOZERO_INV);
			singleChannelFrame2 = singleChannelFrame2 & singleChannelFrame1;
			threshold(singleChannelFrame2, singleChannelFrame1, 1, 255, THRESH_BINARY);
		#endif
		#if DEBUG_TABLE_MASK
			imshow("table mask", singleChannelFrame1);
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
		#if DEBUG_TABLE_CONTOUR
			drawContours(singleChannelFrame2, contourList, maxIndex, Scalar(255, 255, 255), -1);
			imshow("table contour", singleChannelFrame2);
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
			//waitKey(33);          //delay 33ms
			imshow("singleChannelFrame2", singleChannelFrame2);
			//waitKey(33);          //delay 33ms
			singleChannelFrame2 = Scalar(0, 0, 0);
			drawContours(singleChannelFrame2, contourList, maxIndex, Scalar(255, 255, 255), -1);
			bitwise_and(singleChannelFrame2, singleChannelFrame1, singleChannelFrame1);

			//vector<Vec2f> lines;
			//HoughLinesP(singleChannelFrame1, lines,);



			imshow("masked", singleChannelFrame2);
			//waitKey(33);          //delay 33ms
			imshow("maskedTable", singleChannelFrame1);
			//waitKey(33);          //delay 33ms
		#endif
		//calculated rect points should be in newRectPoints now


		//if I want to average the table on init. use this
			//this either averages the table, or just used the calculated value
		#if ERODE_RECT_POINTS
		
			static Point2f erodedNewRectPoints[4];
			erodedNewRectPoints[0] = (newRectPoints[2] - newRectPoints[0])*((float)ERODE_RECT_POINTS / 100.) + newRectPoints[0];
			erodedNewRectPoints[1] = (newRectPoints[3] - newRectPoints[1])*((float)ERODE_RECT_POINTS / 100.) + newRectPoints[1];
			erodedNewRectPoints[2] = (newRectPoints[0] - newRectPoints[2])*((float)ERODE_RECT_POINTS / 100.) + newRectPoints[2];
			erodedNewRectPoints[3] = (newRectPoints[1] - newRectPoints[3])*((float)ERODE_RECT_POINTS / 100.) + newRectPoints[3];

			for (int i = 0; i < 4; i++)
			{
				newRectPoints[i] = erodedNewRectPoints[i];
			}
		#endif
			for (int i = 0; i < 4; i++)
			{
				rectPoints[i] = newRectPoints[i];
			}	
	for (int i = 0; i < 4; i++)
	{
		tableBounds[i] = rectPoints[i];
	}
	return;
}
void getBallMask(Mat inImage, Mat background,Size inSize,Mat tempChannels[3],Mat tempImage,Mat outMask)
{
#define SIMPLE_METHOD false
#if !SIMPLE_METHOD
	static Mat singleChannel;
	tempImage = inImage - background;
	split(tempImage, tempChannels);
	addWeighted(tempChannels[0], 1, tempChannels[1], 1, 0, singleChannel,CV_8U);
	addWeighted(singleChannel, 1, tempChannels[2], 1, 0, tempChannels[0], CV_8U);
	
	threshold(tempChannels[0],outMask, 30, 255, THRESH_BINARY);


	//I draw circles on the holes to decrease the number of contours found
	//Also lessens noise
	//img,Center,Radius,Color,Thickness
	circle(outMask, Point(0, 0)							, 80, Scalar(0), -1);
	circle(outMask, Point(0, inSize.height)				, 80, Scalar(0), -1);
	circle(outMask, Point(inSize.width/2, 0)			, 40, Scalar(0), -1);
	circle(outMask, Point(inSize.width/2, inSize.height), 40, Scalar(0), -1);
	circle(outMask, Point(inSize.width, 0)				, 80, Scalar(0), -1);
	circle(outMask, Point(inSize.width, inSize.height)	, 80, Scalar(0), -1);

#else
	//TODO: SEE if I should just hardcode another frame in here, or input a temp channel image (see if split reallocates)
	//absdiff(inImage, background, tempImage);
	subtract(inImage, background, tempImage);
	split(tempImage, tempChannels);
	threshold(tempChannels[2], outMask, 7, 255, THRESH_BINARY_INV);
	/*
	//split(outImage, tempChannels);
	//bitwise_or(tempChannels[0], tempChannels[2], tempChannels[1]);
	//bitwise_not(tempChannels[2], tempChannels[0]);
	inImage.copyTo(outImage);
	static Mat singleChannel;
	bitwise_not(tempChannels[0], singleChannel);
	imshow("ball mask", singleChannel);
	//waitKey(33);
	bitwise_and(inImage, Scalar(0), outImage,tempChannels[0]);
	*/
#endif
	
}
void tableSubtractBackground(Mat inImage, Mat background, Mat outImage)
{
	outImage = inImage - background;
}
void getTableImage(Mat inImage,Size inSize, Point2f tableBounds[4], Mat outImage)
{
	//THIS GENERATES THE AFFINE TRANSFORM FOR THE ROTATION

	int yMax = 0;
	int xMax = 0;
	int yVar = 0;
	int xVar = 0;
	for (int i = 0; i < 4;i++)
	{
		for (int j = 0;j < 4;j++)
		{
			yVar = tableBounds[i].y - tableBounds[j].y;
			xVar = tableBounds[i].x - tableBounds[j].x;
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
		Point2f temp = tableBounds[0];
		tableBounds[0] = tableBounds[1];
		tableBounds[1] = tableBounds[2];
		tableBounds[2] = tableBounds[3];
		tableBounds[3] = temp;
	}
	//TODO: Check these for correctness
	Point2f affineRectCorners[3];
	affineRectCorners[0] = tableBounds[1];
	affineRectCorners[1] = tableBounds[2];
	affineRectCorners[2] = tableBounds[3];
	Point2f frameCorners[3];
	frameCorners[0] = Point2f(0, 0);
	frameCorners[1] = Point2f(inSize.width, 0);
	frameCorners[2] = Point2f(inSize.width, inSize.height);
	Mat rotMat = getAffineTransform(affineRectCorners, frameCorners);

	warpAffine(inImage, outImage, rotMat, inSize);
}
void averageRectFunc(Point2f inBox[4], int curCount, Point2f outBox[4])
{

	for (int i = 0; i < 4;i++)
	{
		outBox[i].x = (outBox[i].x * curCount + inBox[i].x)/(float)(curCount+1);
		outBox[i].y = (outBox[i].y * curCount + inBox[i].y) / (float)(curCount + 1);
	}

}
void averageImageFunc(Mat inFrame, float curCount, Mat outFrame)
{
	addWeighted(inFrame, (curCount / (curCount + 1)), outFrame, 1 / (curCount + 1), 1, outFrame);
}
