// Olga Souverneva 2016
// Header for contstants used throughout the classifier that can be adjusted to finetune

#ifndef _CLASSIFIER_CONST_H
#define _CLASSIFIER_CONST_H

// The number of "no balls" or ghosts allowed
static const unsigned int NO_BALLS_MAX = 1;

// Used to compute proximity-based probability
static const float PROXIMITY_MU = 4.10418f;

// How much to adjust for proximity. 1.0 or less.
static const float PROXIMITY_FACTOR = 0.1f;

// The max input frame width
static const unsigned int MAX_FRAME_WIDTH = 330;

// The max input frame length
static const unsigned int MAX_FRAME_LENGTH = 676;

// The min radius of a ball to crop to
static const unsigned int MIN_RADIUS = 8;

// The max radius of a ball to crop to
static const unsigned int MAX_RADIUS = 13;

// The max the cost can be and a classification still be likely
static const float MAX_CLASSIFICATION_COST_LIKELY = 0.65f;

#endif