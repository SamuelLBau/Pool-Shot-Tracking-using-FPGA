// Olga Souverneva 2016
// RGB image to HSV image conversion

#include "stdafx.h"
#include "RGB_ToHSV.h"

static  HSV_Pixel ConvertToHsv_Pixel(const RGB_Pixel& inputPixel);

void ConvertToHSV_Frame(const RGB_Frame& inputFrame, HSV_Frame& outputFrame)
{
	for (int i=0; i<MAX_FRAME_LENGTH; i++)
	{
		for (int j=0; j<MAX_FRAME_WIDTH; j++)
		{
			HSV_Pixel pixel = ConvertToHsv_Pixel(inputFrame.pixel[i][j]);
			outputFrame.pixel[i][j] = pixel;
		}
	}
}

static  HSV_Pixel ConvertToHsv_Pixel(const RGB_Pixel& inputPixel)
{
	HSV_Pixel out;
	unsigned char min = inputPixel.chanel[RED] < inputPixel.chanel[GREEN] ? 
		inputPixel.chanel[RED] : inputPixel.chanel[GREEN];
	min = min  < inputPixel.chanel[BLUE] ? min  : inputPixel.chanel[BLUE];

	unsigned char max = inputPixel.chanel[RED] > inputPixel.chanel[GREEN] ? 
		inputPixel.chanel[RED] : inputPixel.chanel[GREEN];
	max = max  > inputPixel.chanel[BLUE] ? max  : inputPixel.chanel[BLUE];

	// Compute Value
	out.chanel[VALUE] = static_cast<float>(max)/0xFF;

	// Compute Saturation
	unsigned char delta = max - min;
	if (delta < 0.00001)
	{
		out.chanel[SATURATION] = 0;
		out.chanel[HUE] = 0;
		return out;
	}
	out.chanel[SATURATION] = static_cast<float>(delta) / max;
	
	// Compute Hue
	if (inputPixel.chanel[RED] >= max)
		out.chanel[HUE] = ( static_cast<float>(inputPixel.chanel[GREEN]) - inputPixel.chanel[BLUE] ) / delta;		// between yellow & magenta
	else if (inputPixel.chanel[GREEN] >= max)
		out.chanel[HUE] = 2.0f + ( static_cast<float>(inputPixel.chanel[BLUE]) - inputPixel.chanel[RED] ) / delta;  // between cyan & yellow
	else
		out.chanel[HUE] = 4.0f + ( static_cast<float>(inputPixel.chanel[RED]) - inputPixel.chanel[GREEN] ) / delta;  // between magenta & cyan

	// Scale to be 0-1
	out.chanel[HUE] /= 6.0f;

	if( out.chanel[HUE] < 0.0 )
		out.chanel[HUE] += 1.0;

	return out;
}