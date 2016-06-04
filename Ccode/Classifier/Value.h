// Olga Souverneva 2016

#include "ClassifierTypes.h"

#ifndef _VALUE_H
#define _VALUE_H

static const float VALUE_MIN = 0.0f;
static const float VALUE_MAX = 1.0f;

// Get the training set Pd for Value. Note: Black Ball only!
float GetValuePd(BallId id, unsigned char value);

#endif