// Olga Souverneva 2016
// RGB image to HSV image conversion

#include "ClassifierTypes.h"

#ifndef _RGB_TO_HSV_H
#define _RGB_TO_HSV_H

// Convert an RGB frame to an HSV frame
// inputFrame - RGB format input
void ConvertToHSV_Frame(const RGB_Frame& inputFrame, HSV_Frame& outputFrame);

#endif