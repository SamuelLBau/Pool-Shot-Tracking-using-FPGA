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
//                     Copyright(c) 2014 Avnet, Inc.
//                             All rights reserved.
//
//----------------------------------------------------------------
//
// Create Date:         Feb 26, 2014
// Design Name:         FMC-IMAGEON HDMI Video Frame Buffer
// Module Name:         fmc_imageon_hdmi_display.h
// Project Name:        FMC-IMAGEON HDMI Video Frame Buffer Program
// Target Devices:      Spartan-6, Virtex-6, Kintex-6
// Hardware Boards:     FMC-IMAGEON
// 
//
// Tool versions:       Vivado 2013.3
//
// Description:         FMC-IMAGEON HDMI Display Controller Program
//                      This application will configure the ADV7611 on the FMC-IMAGEON module
//                      - HDMI Output
//                         - ADV7511 configured for 16 bit YCbCr 4:2:2 mode
//                           with embedded syncs
//                      It will also configure the Video Timing Controller
//                      to generate the video timing.
//
// Dependencies:
//
// Revision:            Feb 26, 2014: 1.00 Initial version
//
//----------------------------------------------------------------

#ifndef __ZED_HDMI_DISPLAY_H__
#define __ZED_HDMI_DISPLAY_H__

#include "xparameters.h"
#include "sleep.h"

#include "zed_iic.h"

#include "xvtc.h"
#include "xaxivdma.h"

#include "video_resolution.h"
#include "video_generator.h"
#include "video_frame_buffer.h"

// This structure contains the context
//  for the FMC-IMAGEON HDMI Display Controller design
struct struct_zed_hdmi_display_t
{
   // IP base addresses
   Xuint32 uBaseAddr_IIC_HdmiOut;
   Xuint32 uDeviceId_VTC_HdmioGenerator;
   Xuint32 uDeviceId_VDMA_HdmiDisplay;
   Xuint32 uBaseAddr_MEM_HdmiDisplay;  // address of FB in memory
   Xuint32 uNumFrames_HdmiDisplay;

   zed_iic_t hdmi_out_iic;

   XVtc vtc_hdmio_generator;

   XAxiVdma vdma_hdmi;
   XAxiVdma_DmaSetup vdmacfg_hdmi_read;
   XAxiVdma_DmaSetup vdmacfg_hdmi_write;

   Xuint32 bVerbose;

   // HDMI Output settings
   Xuint32 hdmio_width;
   Xuint32 hdmio_height;
   Xuint32 hdmio_resolution;

};
typedef struct struct_zed_hdmi_display_t zed_hdmi_display_t;

int zed_hdmi_display_init( zed_hdmi_display_t *pDemo );

int zed_hdmi_display_clear( zed_hdmi_display_t *pDemo );
int zed_hdmi_display_cbars( zed_hdmi_display_t *pDemo, Xuint32 offset );

#endif // __ZED_HDMI_DISPLAY_H__
