#include <iostream>
#include <string>
#include <hls_opencv.h>
#include <hls_video.h>
#include "opencv2/opencv.hpp"

#define MAX_WIDTH 2047
#define MAX_HEIGHT 2047

using namespace cv;

typedef hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_8UC3> hlsMat;

int main(int, char**)
{
	VideoCapture cap("D:\\CSE145\\videoLoading\\VideoLoading\\video2.mp4");
	if (!cap.isOpened()) {  // check if we succeeded
		std::cerr << "video loading failed" << std::endl;
		return -1;
	}

	//Mat edges;
	//namedWindow("edges", 1);
	for (;;)
	{
		Mat frame(1080, 1920), convertedFrame(1080, 1920);
		hlsMat hlsFrameP(1080, 1920), hlsMatP(1080, 1920);
		hlsMat *hlsFrame = &hlsFrameP;
		hlsMat *hlsGreyScaleFrame = &hlsMatP;
		//hlsMat *hlsFrame = new hlsMat(1080, 1920);
		//hlsMat *hlsGreyScaleFrame = new hlsMat(1080, 1920);

		cap >> frame; // get a new frame from camera
		cvMat2hlsMat(frame, *hlsFrame);
		convertToGreyScale(hlsFrame, hlsGreyScaleFrame);
		hlsMat2cvMat(*hlsGreyScaleFrame, convertedFrame);
		imshow("frame", convertedFrame);
		if (waitKey(30) >= 0) break;
	}

	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}
