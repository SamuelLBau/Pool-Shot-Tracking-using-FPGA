#ifndef Classifier_h

#define Classifier_h

#include "stdafx.h"
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
class Classifier {
public:
	Classifier();
	void begin();
	void classify();
	void end(vector<Point2f>,vector<float>,vector<int>);

};


#endif
