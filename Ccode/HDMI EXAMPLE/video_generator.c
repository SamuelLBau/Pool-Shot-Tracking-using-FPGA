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
// Module Name:         video_generator.c
// Project Name:        FMC-IMAGEON
// Target Devices:      Zynq-7000 SoC
// Avnet Boards:        FMC-IMAGEON
//
// Tool versions:       Vivado 2013.4
//
// Description:         Video Timing Generator using:
//                      - Xilinx Video Timing Controller (VTC)
//
// Dependencies:
//
// Revision:            Dec 09, 2011: 1.00 Initial version
//                      Nov 02, 2012: 1.01 Add call to XVtc_RegUpdate()
//                      Jun 05, 2014: 1.02 Update for Vivado 2013.4
//
//----------------------------------------------------------------

#include "video_generator.h"
#include "video_resolution.h"


/*****************************************************************************/
/**
*
* vgen_init
* - initializes the VTC generator
*
* @param	VtcDeviceID is the device ID of the Video Timing Controller core.
*           pVtc is a pointer to a VTC instance

*
* @return	0 if all tests pass, 1 otherwise.
*
* @note		None.
*
******************************************************************************/
int vgen_init(XVtc *pVtc, u16 VtcDeviceID)
{
	XVtc_Config *VtcCfgPtr;
	int Status;

	/* Look for the device configuration info for the Video Timing
	 * Controller.
	 */
	VtcCfgPtr = XVtc_LookupConfig( VtcDeviceID );
	if (VtcCfgPtr == NULL) {
		return 1;
	}

	/* Initialize the Video Timing Controller instance */

	Status = XVtc_CfgInitialize(pVtc, VtcCfgPtr,
		VtcCfgPtr->BaseAddress);
	if (Status != XST_SUCCESS) {
		return 1;
	}

	return 0;
}


/*****************************************************************************/
/**
*
* vgen_config
* - configures the generator to generate missing syncs
*
* @param	pVtc is a pointer to an initialized VTC instance
*           ResolutionId identified a video resolution
*           vVerbose = 0 no verbose, 1 minimal verbose, 2 most verbose
*
* @return	0 if all tests pass, 1 otherwise.
*
* @note		None.
*
******************************************************************************/
int vgen_config(XVtc *pVtc, int ResolutionId, int bVerbose)
{
	vres_timing_t VideoTiming;
	int HFrontPorch;
	int HSyncWidth;
	int HSyncPol;
	int HBackPorch;
	int VFrontPorch;
	int VSyncWidth;
	int VSyncPol;
	int VBackPorch;
	int LineWidth;
	int FrameHeight;

	XVtc_Signal Signal;		/* VTC Signal configuration */
	XVtc_Polarity Polarity;		/* Polarity configuration */
	XVtc_SourceSelect SourceSelect;	/* Source Selection configuration */


	/* Get Video Resolution timing */
    if ( bVerbose )
    {
		xil_printf( "\tVideo Resolution = %s\n\r", vres_get_name(ResolutionId) );
	}
	vres_get_timing(ResolutionId, &VideoTiming);
	HFrontPorch = VideoTiming.HFrontPorch;
	HSyncWidth  = VideoTiming.HSyncWidth;
	HSyncPol    = VideoTiming.HSyncPolarity;
	HBackPorch  = VideoTiming.HBackPorch;
	VFrontPorch = VideoTiming.VFrontPorch;
	VSyncWidth  = VideoTiming.VSyncWidth;
	VSyncPol    = VideoTiming.VSyncPolarity;
	VBackPorch  = VideoTiming.VBackPorch;
	LineWidth   = VideoTiming.HActiveVideo;
	FrameHeight = VideoTiming.VActiveVideo;
	
	/* Disable/Reset VTC */
	XVtc_DisableGenerator(pVtc);
	XVtc_Reset(pVtc);	

    /* Set up Polarity of all outputs */
	memset((void *)&Polarity, 0, sizeof(Polarity));
	Polarity.ActiveChromaPol = 1;
	Polarity.ActiveVideoPol = 1;
	Polarity.FieldIdPol = 0;
	Polarity.VBlankPol = 1;
	Polarity.VSyncPol = VSyncPol;
	Polarity.HBlankPol = 1;
	Polarity.HSyncPol = HSyncPol;

	/* Set up Generator */
	memset((void *)&Signal, 0, sizeof(XVtc_Signal));
	Signal.OriginMode = 1; //Set Frame Origin to Start of Active Video
	Signal.HTotal = HFrontPorch + HSyncWidth + HBackPorch + LineWidth;
	Signal.HActiveStart     = 0;
	Signal.HFrontPorchStart = LineWidth;
	Signal.HSyncStart       = LineWidth + HFrontPorch;
	Signal.HBackPorchStart  = LineWidth + HFrontPorch + HSyncWidth;
	Signal.V0Total = FrameHeight + VFrontPorch + VSyncWidth + VBackPorch;
	Signal.V0ChromaStart     = 0;
	Signal.V0ActiveStart     = 0;
	Signal.V0FrontPorchStart = FrameHeight;
	Signal.V0SyncStart       = FrameHeight + VFrontPorch;
	Signal.V0BackPorchStart  = FrameHeight + VFrontPorch + VSyncWidth;

	/* Set up source select */
	memset((void *)&SourceSelect, 0, sizeof(SourceSelect));
	SourceSelect.VBlankPolSrc = 1;
	SourceSelect.VSyncPolSrc = 1;
	SourceSelect.HBlankPolSrc = 1;
	SourceSelect.HSyncPolSrc = 1;
	SourceSelect.ActiveVideoPolSrc = 1;
	SourceSelect.ActiveChromaPolSrc= 1;
	SourceSelect.VChromaSrc = 1;
	SourceSelect.VActiveSrc = 1;
	SourceSelect.VBackPorchSrc = 1;
	SourceSelect.VSyncSrc = 1;
	SourceSelect.VFrontPorchSrc = 1;
	SourceSelect.VTotalSrc = 1;
	SourceSelect.HActiveSrc = 1;
	SourceSelect.HBackPorchSrc = 1;
	SourceSelect.HSyncSrc = 1;
	SourceSelect.HFrontPorchSrc = 1;
	SourceSelect.HTotalSrc = 1;

	if ( bVerbose == 2 )
	{
		xil_printf("\tVTC Generator Configuration\n\r" );
		xil_printf("\t\tHorizontal Timing:\n\r" );
		xil_printf("\t\t\tHActiveStart = %d\r\n", Signal.HActiveStart);
		xil_printf("\t\t\tHFrontPorchStart %d\r\n", Signal.HFrontPorchStart);
		xil_printf("\t\t\tHSyncStart %d\r\n", Signal.HSyncStart);
		xil_printf("\t\t\tHBackPorchStart %d\r\n", Signal.HBackPorchStart);
		xil_printf("\t\t\tHTotal = %d\r\n", Signal.HTotal);
		xil_printf("\t\tVertical Timing:\n\r" );
		xil_printf("\t\t\tV0ActiveStart %d\r\n", Signal.V0ActiveStart);
		xil_printf("\t\t\tV0FrontPorchStart %d\r\n", Signal.V0FrontPorchStart);
		xil_printf("\t\t\tV0SyncStart %d\r\n", Signal.V0SyncStart);
		xil_printf("\t\t\tV0BackPorchStart %d\r\n", Signal.V0BackPorchStart);
		xil_printf("\t\t\tV0Total %d\r\n", Signal.V0Total);
	}

	/* Write configuration to hardware */
	XVtc_SetPolarity(pVtc, &Polarity);
	XVtc_SetGenerator(pVtc, &Signal);
	XVtc_SetSource(pVtc, &SourceSelect);

	/* Enable the generator module */
	XVtc_DisableSync(pVtc);
	//XVtc_SetFSync(pVtc, 0, Signal.V0SyncStart, 1);
	XVtc_EnableGenerator(pVtc);

	XVtc_RegUpdate(pVtc);

	/* Return success */

	return 0;
}
