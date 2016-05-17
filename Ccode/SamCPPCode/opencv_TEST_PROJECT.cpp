//#include <opencv\cv.h>   // This is the original code, but I couldn't get VideoCapture work correctly.
#include "stdafx.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>

#include "videoProcessingFuncs.h"
using namespace std;
using namespace cv;

#define INPUT_VIDEO_FOLDER "D:/Files/UCSD Undergrad/Spring 2016/CSE145/Pool video/5-5-16/"
#define OUTPUT_VIDEO_FOLDER "D:/Files/UCSD Undergrad/Spring 2016/CSE145/Pool video/result/"
#define INPUT_VIDEO_NAME "LightWhiteBalance"
#define VIDEO_EXTENSION ".mp4"

#define OUTPUT_VIDEO_MASK OUTPUT_VIDEO_FOLDER INPUT_VIDEO_NAME "_MASK" VIDEO_EXTENSION
#define OUTPUT_VIDEO_TABLE OUTPUT_VIDEO_FOLDER INPUT_VIDEO_NAME "_TABLE" VIDEO_EXTENSION
#define OUTPUT_VIDEO_FINAL OUTPUT_VIDEO_FOLDER INPUT_VIDEO_NAME "_FINAL" VIDEO_EXTENSION
#define OUTPUT_VIDEO_CIRCLES OUTPUT_VIDEO_FOLDER INPUT_VIDEO_NAME "_CIRCLES" VIDEO_EXTENSION

#define INPUT_VIDEO INPUT_VIDEO_FOLDER INPUT_VIDEO_NAME VIDEO_EXTENSION

#define FRAMES_TO_RUN 30
int main() {
	int numFrames = 0;
	Mat image;          //Create Matrix to store image
	VideoCapture cap;          //initialize capture
	cap.open(INPUT_VIDEO);
	Size inputSize = Size((int)cap.get(CV_CAP_PROP_FRAME_WIDTH),    // Acquire input size
		(int)cap.get(CV_CAP_PROP_FRAME_HEIGHT));
	int inputFourCC = static_cast<int>(cap.get(CV_CAP_PROP_FOURCC));
	int inputFrameRate = (int)cap.get(CV_CAP_PROP_FPS);
#if WRITE_VIDEO
	VideoWriter maskVWriter, tableVWriter, circlesVWriter, finalVWriter;
	cout << INPUT_VIDEO<<endl;
	cout << OUTPUT_VIDEO_FINAL << endl;

	//mask should be black and white
	maskVWriter.open(OUTPUT_VIDEO_MASK, inputFourCC, inputFrameRate, inputSize,false);
	tableVWriter.open(OUTPUT_VIDEO_TABLE, inputFourCC, inputFrameRate, inputSize,true);
	circlesVWriter.open(OUTPUT_VIDEO_CIRCLES, inputFourCC, inputFrameRate, inputSize);
	finalVWriter.open(OUTPUT_VIDEO_FINAL, inputFourCC, inputFrameRate, inputSize);
	namedWindow("window", 1);          //create window to show image
	cout << "frameRate = " << inputFrameRate << endl;
	cout << "fourCC = " << inputFourCC << endl;
	cout << "input Size = " << inputSize << endl;
	if (!cap.isOpened())
	{
		cout << "Could not open input file: " <<INPUT_VIDEO<< endl;
	}
	if (!finalVWriter.isOpened())
	{
		cout << "Could not open finalVWriter: " <<OUTPUT_VIDEO_FINAL<< endl;
	}
	if (!tableVWriter.isOpened())
	{
		cout << "Could not open tableVWriter: " <<OUTPUT_VIDEO_TABLE<< endl;
	}
	if (!circlesVWriter.isOpened())
	{
		cout << "Could not open circlesVWriter" <<OUTPUT_VIDEO_CIRCLES<< endl;
	}
	if (!maskVWriter.isOpened())
	{
		cout << "Could not open maskVWriter" << OUTPUT_VIDEO_MASK << endl;
	}
#endif
	while (numFrames < FRAMES_TO_RUN) 
	{
		cap >> image;          //stream image
		numFrames++;
		#if DEBUG
			cout << "Printing frame: " << numFrames << endl;
		#endif
		#if WRITE_VIDEO
			finalVWriter << processVideo(image,inputSize,maskVWriter,tableVWriter,circlesVWriter);
		#else
			Mat finalFrame = processVideo(image, inputSize);
			#if DEBUG
				imshow("table contour", finalFrame);
				waitKey(33);          //delay 33ms
			#endif
		#endif
	}
	#if WRITE_VIDEO
		maskVWriter.release();
		tableVWriter.release();
		circlesVWriter.release();
		finalVWriter.release();
	#endif
	return 0;
}