//----------------------------------------------------------------
//      _____
//     /     \
//    /____   \____
//   / \===\   \==/
//  /___\===\___\/  AVNET
//       \======/
//        \====/
//---------------------------------------------------------------
//
// This design is the property of Avnet.  Publication of this
// design is not authorized without written consent from Avnet.
//
// Please direct any questions to:  technical.support@avnet.com
//
// Disclaimer:
//    Avnet, Inc. makes no warranty for the use of this code or design.
//    This code is provided  "As Is". Avnet, Inc assumes no responsibility for
//    any errors, which may appear in this code, nor does it make a commitment
//    to update the information contained herein. Avnet, Inc specifically
//    disclaims any implied warranties of fitness for a particular purpose.
//                     Copyright(c) 2011 Avnet, Inc.
//                             All rights reserved.
//
//----------------------------------------------------------------
//
// Create Date:         Dec 09, 2011
// Design Name:         Video Generator
// Module Name:         video_generator.h
// Project Name:        FMC-IMAGEON
// Target Devices:      Zynq-7000 SoC
// Avnet Boards:        FMC-IMAGEON
//
// Tool versions:       ISE 14.3
//
// Description:         Video Timing Generator using:
//                      - Xilinx Video Timing Controller (VTC)
//
// Dependencies:
//
// Revision:            Dec 09, 2011: 1.00 Initial version
//                      Nov 02, 2012: 1.01 Add call to XVtc_RegUpdate()
//
//----------------------------------------------------------------

#ifndef __VIDEO_GENERATOR_H__
#define __VIDEO_GENERATOR_H__

#include "xvtc.h"
#include "xparameters.h"


/*
 * Function prototypes
 */
int vgen_init(XVtc *pVtc, u16 VtcDeviceID);
int vgen_config(XVtc *pVtc, int ResolutionId, int bVerbose);

#endif // __VIDEO_GENERATOR_H__
