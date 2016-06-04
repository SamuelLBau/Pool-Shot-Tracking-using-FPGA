// Olga Souverneva 2016
// Header for types used throughout the classifier

#include "ClassifierConst.h"

#ifndef _CLASSIFIER_TYPES
#define _CLASSIFIER_TYPES

// The ball identifiers
enum BallId
{
	BALL_1,
	BALL_2,
	BALL_3,
	BALL_4,
	BALL_5,
	BALL_6,
	BALL_7,
	BALL_8,
	BALL_9,
	BALL_10,
	BALL_11,
	BALL_12,
	BALL_13,
	BALL_14,
	BALL_15,
	CUE,
	BALL_MAX,
};

// RGB Chanels in uint8 array
enum RGB_Chanel
{
	RED,
	GREEN,
	BLUE,
	RGB_MAX
};

// HSV Chanels in float array
enum HSV_Chanel
{
	HUE,
	SATURATION,
	VALUE,
	HSV_MAX
};

// Minimum unit of an RGB Image
struct RGB_Pixel
{
	unsigned char chanel[RGB_MAX];
};

// Minimum unit of an HLV Image
struct HSV_Pixel
{
	float chanel[HSV_MAX];
};

struct RGB_Frame
{
	RGB_Pixel pixel[MAX_FRAME_LENGTH][MAX_FRAME_WIDTH];
};

struct HSV_Frame
{
	HSV_Pixel pixel[MAX_FRAME_LENGTH][MAX_FRAME_WIDTH];
};

struct Coordinates
{
	unsigned int x;
	unsigned int y;
};

struct ManualData
{
	BallId id;
	unsigned int y;
	unsigned int x;
};

#endif