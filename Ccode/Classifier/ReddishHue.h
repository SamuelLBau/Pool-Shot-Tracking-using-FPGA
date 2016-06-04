// Olga Souverneva 2016

#include "ClassifierTypes.h"

#ifndef _REDDISH_HUE_H
#define _REDDISH_HUE_H

// Nore - Hue "wrapped" around to be centered on Reddish Hues
static const float REDDISH_HUE_MIN = -0.5f;
static const float REDDISH_HUE_MAX = 0.5f;

// Get the training set Pd for Reddish Hues
float GetReddishHuePd(BallId id, unsigned char tHue);

#endif