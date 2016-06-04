// Olga Souverneva 2016
// Performs min const matching using the munkres algorithm

#ifndef _MUNKRES_MATCHING_H
#define _MUNKRES_MATCHING_H

#include "ClassifierTypes.h"

static const unsigned char MUNKRES_MAX_SIZE = BALL_MAX + NO_BALLS_MAX;
void MunkresMatching(float costMatrix[][MUNKRES_MAX_SIZE], unsigned char* results, unsigned char costLength, unsigned char costWidth);

#endif