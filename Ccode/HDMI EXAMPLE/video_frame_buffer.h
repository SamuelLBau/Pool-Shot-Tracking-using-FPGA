//----------------------------------------------------------------
//      _____
//     *     *
//    *____   *____
//   * *===*   *==*
//  *___*===*___**  AVNET
//       *======*
//        *====*
//----------------------------------------------------------------------------
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
// Create Date:         Dec 23, 2011
// Design Name:         Video Frame Buffer
// Module Name:         video_frame_buffer.h
// Project Name:        FMC-IMAGEON
// Target Devices:      Zynq-7000 SoC
// Hardware Boards:     ZC702 + FMC-IMAGEON
//
// Tool versions:       ISE 14.3
//
// Description:         Video Frame Buffer
//                      - use with AXI_VDMA pcore
//
// Dependencies:        
//
// Revision:            Dec 23, 2011: 1.00 Initial Version
//                      Nov 30, 2012: 1.01 Implement seperate
//
//----------------------------------------------------------------

#ifndef __VIDEO_FRAME_BUFFER_H__
#define __VIDEO_FRAME_BUFFER_H__

#include "xaxivdma.h"

int vfb_common_init( u16 uDeviceId, XAxiVdma * InstancePtr );

int vfb_rx_init( XAxiVdma *pAxiVdma, XAxiVdma_DmaSetup *pWriteCfg, Xuint32 uVideoResolution, Xuint32 uStorageResolution, Xuint32 uMemAddr, Xuint32 uNumFrames );
int vfb_rx_setup( XAxiVdma *pAxiVdma, XAxiVdma_DmaSetup *pWriteCfg, Xuint32 uVideoResolution, Xuint32 uStorageResolution, Xuint32 uMemAddr, Xuint32 uNumFrames );
int vfb_rx_start( XAxiVdma *pAxiVdma );
int vfb_rx_stop ( XAxiVdma *pAxiVdma );

int vfb_tx_init( XAxiVdma *pAxiVdma, XAxiVdma_DmaSetup *pReadCfg , Xuint32 uVideoResolution, Xuint32 uStorageResolution, Xuint32 uMemAddr, Xuint32 uNumFrames );
int vfb_tx_setup( XAxiVdma *pAxiVdma, XAxiVdma_DmaSetup *pReadCfg , Xuint32 uVideoResolution, Xuint32 uStorageResolution, Xuint32 uMemAddr, Xuint32 uNumFrames );
int vfb_tx_start( XAxiVdma *pAxiVdma );
int vfb_tx_stop ( XAxiVdma *pAxiVdma );

int vfb_dump_registers( XAxiVdma *pAxiVdma);
int vfb_check_errors( XAxiVdma *pAxiVdma, u8 bClearErrors );

#endif // __VIDEO_FRAME_BUFFER_H__

