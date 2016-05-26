#ifndef config_h
#define config_h

#include "stdafx.h"

#define FRAMES_TO_RUN 500

#define STATE_INIT 0
#define STATE_AVERAGE_TABLE 1
#define STATE_AVERAGE_BACKGROUND 2
#define STATE_NORMAL_RUN 3

#define DEBUG false
#define DEBUG_ALL_VIDEO false
#define WRITE_VIDEO true

#define WRITE_VIDEO_CIRCLES true

#define DEBUG_IN_IMAGE false
#define DEBUG_BG_IMAGE false
#define DEBUG_TABLE_MASK false
#define DEBUG_TABLE_CONTOUR false
#define DEBUG_WARPED_TABLE false
#define DEBUG_INITIAL_BALL_MASK false
#define DEBUG_TABLE_BALL_INITIAL_MASK true
#define DEBUG_ERODED_MASKS false
#define DEBUG_FINAL_IMAGE true

#define DEBUG_POTENTIAL_BALLS false
#define DEBUG_POTENTIAL_BALLS_SHOW false
#define MANUAL_INPUT_ISBALL false



//BEGIN TABLE ROI VALUES

#define TABLE_ADDITIVE_MASK true

#define TABLE_ADDITIVE_THRESH_LOW (uchar)0
#define TABLE_ADDITIVE_THRESH_HIGH (uchar)20

#define TABLE_SUBTRACTIVE_MASK !TABLE_ADDITIVE_MASK

#define RECTANGLE_SIMPLE_METHOD true
#define RECTANGLE_HOUGH_METHOD false //!RECTANGLE_SIMPLE_METHOD

#define AVERAGE_BOX_POINTS true
#define NUM_BOX_AVERAGE_FRAMES 30

#define ERODE_RECT_POINTS 1	//Set this to 0 to not erode, otherwise treat this as percent

#define AVERAGE_BG_FRAME true
#define NUM_BG_AVERAGE_FRAMES 10


//BEGIN
#define TABLE_BG_SUBTRACTION_SIMPLE false //KEEP FALSE, the true version does not make a mask and will not work with subsequent functions

#define CONTOUR_MIN_AREA 250
#define CONTOUR_MAX_AREA 1000


#define BILLIARD_BALL_RADIUS 25
#define RADIUS_MIN 30 //This should be size of ball plus wiggle room, in case contour is off center
#define RADIUS_MAX 40

#define NUM_EROSION_LOOP_ITERATIONS 4
#define INIT_EROSION_SIZE 3
#define INIT_EROSION_ITERATIONS 1
#define LOOP_EROSION_SIZE 7
#define LOOP_EROSION_ITERATIONS 1
#define LOOP_DILATION_SIZE 0
#define LOOP_DILATION_ITERATIONS 2
#define INIT_DILATION_SIZE 3
#define INIT_DILATION_ITERATIONS 1

#define EXCLUDE_NEAR_BALLS true
#define BLOB_MIN_SEPARATION 0		//This is minimum distance from a blob to center of existing circle

#define EXCLUDE_CIRCULARITY false
#define MIN_CIRCULARITY .6 //This may be bit low
#define FOUR_PI 4*3.1415927

///---+_+_+_+_+_+_+_+_+_ NOTE: If these are changed, Sams classifier must change order
//it checks for each ball in
#define SOLID_YELLOW_ID 0
#define SOLID_BLUE_ID 1
#define SOLID_RED_ID 2
#define SOLID_VIOLET_ID 3
#define SOLID_ORANGE_ID 4
#define SOLID_GREEN_ID 5
#define SOLID_MAROON_ID 6
#define SOLID_BLACK_ID 7
#define STRIPED_YELLOW_ID 8
#define STRIPED_BLUE_ID 9
#define STRIPED_RED_ID 10
#define STRIPED_VIOLET_ID 11
#define STRIPED_ORANGE_ID 12
#define STRIPED_GREEN_ID 13
#define STRIPED_MAROON_ID 14
#define CUE_BALL_ID 15
#define MAX_BALLS_IDENTIFIED 32


//BEGIN SAM'S CLASSIFIER VALUES
#define USE_SAMS_CLASSIFIER true
#define CLASSIFY_ON_HSV true

#define CLASSIFIER_MIN_POSITIVE .1

#define YELLOW_RANGE_MIN Scalar(90,180,0)
#define YELLOW_RANGE_MAX Scalar(100,255,255)

#define RED_RANGE_MIN Scalar(110,40,0)
#define RED_RANGE_MAX Scalar(130,255,255)

#define BLUE_RANGE_MIN Scalar(7,100,50)
#define BLUE_RANGE_MAX Scalar(30,200,210)

#define WHITE_RANGE_MIN Scalar(80,20,100)
#define WHITE_RANGE_MAX Scalar(100,160,255)

#define VIOLET_RANGE_MIN Scalar(60,120,180)
#define VIOLET_RANGE_MAX Scalar(180,180,190)

//Consider using RGB space for this one
//It really doesn't pop anywhere
#define BLACK_RANGE_MIN Scalar(25,0,0)
#define BLACK_RANGE_MAX Scalar(50,255,255)

#define ORANGE_RANGE_MIN Scalar(100,180,220)
#define ORANGE_RANGE_MAX Scalar(120,255,255)

#define GREEN_RANGE_MIN Scalar(40,0,0)
#define GREEN_RANGE_MAX Scalar(90,255,255)

#define MAROON_RANGE_MIN Scalar(0,0,0) //TODO: Add values for maroon
#define MAROON_RANGE_MAX Scalar(1,1,1)


///OTHER CONSTANTS
#define M_PI 3.14159265358979323846

#endif