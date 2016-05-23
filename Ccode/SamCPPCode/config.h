#ifndef config_h
#define config_h


#define FRAMES_TO_RUN 400

#define DEBUG false
#define DEBUG_ALL_VIDEO false
#define WRITE_VIDEO true

#define DEBUG_IN_IMAGE false
#define DEBUG_BG_IMAGE true
#define DEBUG_TABLE_MASK false
#define DEBUG_TABLE_CONTOUR false
#define DEBUG_WARPED_TABLE true

#define DEBUG_POTENTIAL_BALLS false



//BEGIN TABLE ROI VALUES

#define TABLE_ADDITIVE_MASK true

#define TABLE_ADDITIVE_THRESH_LOW (uchar)0
#define TABLE_ADDITIVE_THRESH_HIGH (uchar)20

#define TABLE_SUBTRACTIVE_MASK !TABLE_ADDITIVE_MASK

#define RECTANGLE_SIMPLE_METHOD true
#define RECTANGLE_HOUGH_METHOD false //!RECTANGLE_SIMPLE_METHOD

#define AVERAGE_BOX_POINTS true
#define NUM_BOX_AVERAGE_FRAMES 30

#define ERODE_RECT_POINTS 0	//Set this to 0 to not erode, otherwise treat this as percent

#define AVERAGE_BG_FRAME true
#define NUM_BG_AVERAGE_FRAMES 10


//BEGIN
#define TABLE_BG_SUBTRACTION_SIMPLE false //KEEP FALSE, the true version does not make a mask and will not work with subsequent functions

#define CONTOUR_MIN_AREA 300
#define CONTOUR_MAX_AREA 2000


#define CIRCLE_RADIUS 27
#define RADIUS_MIN 30 //This should be size of ball plus wiggle room, in case contour is off center
#define RADIUS_MAX 40



#define MIN_CIRCULARITY .6 //This may be bit low
#define FOUR_PI 4*3.1415927


#endif