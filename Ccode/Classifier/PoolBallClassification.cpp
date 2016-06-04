// PoolBallClassification.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Classifier.h"
#include "RGB_ToHSV.h"
#include "TestFrame1.h"
#include "stdafx.h"
#include <iostream>

HSV_Frame _frame;
Classifier _classifier;
static Coordinates _coordinates[Classifier::MAX_SIZE] = {};
static unsigned int _radii[Classifier::MAX_SIZE] = {};
static bool _found[Classifier::MAX_SIZE] = {};
static unsigned int _cnt = 0;
static unsigned char _labels[Classifier::MAX_SIZE] = {};

using namespace std;

static void OutputFound()
{
	cout << "Found = \n";
	for (unsigned int i=0; i<_cnt; i++)
	{
		cout << _found[i] << "\n"; 
	}
}

static void OutputLabels()
{
	cout << "Labels = \n";
	for (unsigned int i=0; i<_cnt; i++)
	{
		cout << static_cast<int>(_labels[i]) << "\n"; 
	}
}

static void OutputAccuracy()
{
	float accuracy = 0;
	for (unsigned int i=0; i<_cnt; i++)
	{
		if (_labels[i] == static_cast<unsigned char>(MANUAL_DATA_1[i].id) ||
			(_labels[i] == Classifier::NOT_FOUND && static_cast<unsigned char>(MANUAL_DATA_1[i].id) >= BALL_MAX))
			accuracy++;
		else
			accuracy--;
	}
	cout << "Accuracy = " << accuracy/(_cnt) << "\n";
}

int _tmain(int argc, _TCHAR* argv[])
{
	// Tests the classifer object with saved frames.
	// TODO- update to use OpenCV

	// Test frame 1
	ConvertToHSV_Frame(TEST_FRAME_1, _frame);
	_cnt = MANUAL_DATA_1_SIZE <= Classifier::MAX_SIZE ? MANUAL_DATA_1_SIZE : Classifier::MAX_SIZE;
	for (unsigned int i=0; i<_cnt; i++)
	{
		_radii[i] = MIN_RADIUS;
		_coordinates[i].x = MANUAL_DATA_1[i].x;
		_coordinates[i].y = MANUAL_DATA_1[i].y;
	}

	_classifier.Begin();
	_classifier.Classify(_frame, _coordinates, _radii, _found, _cnt);
	OutputFound();
	_classifier.Output(_coordinates, _labels, _cnt);
	OutputLabels();
	OutputAccuracy();

	return 0;
}

