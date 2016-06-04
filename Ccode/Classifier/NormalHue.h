// Olga Souverneva 2016

#include "ClassifierTypes.h"

#ifndef _NORMAL_HUE_H
#define _NORMAL_HUE_H

static const float NORMAL_HUE_MIN = 0.0f;
static const float NORMAL_HUE_MAX = 1.0f;

// Get the training set Pd for Normal Hues
float GetNormalHuePd(BallId id, unsigned char hue);

#endif