/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  IMGLIB-2  DSP Image/Video Processing Library                            */
/*                                                                          */
/*      Release:        Revision 2.0.1                                      */
/*      Snapshot date:  6-May-2008                                          */
/*                                                                          */
/*  This library contains proprietary intellectual property of Texas        */
/*  Instruments, Inc.  The library and its source code are protected by     */
/*  various copyrights, and portions may also be protected by patents or    */
/*  other legal protections.                                                */
/*                                                                          */
/*  This software is licensed for use with Texas Instruments TMS320         */
/*  family DSPs.  This license was provided to you prior to installing      */
/*  the software.  You may review this license by consulting the file       */
/*  TI_license.PDF which accompanies the files in this library.             */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2008 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      IMG_yc_demux_be16_8 -- De-interleave a 4:2:2 BIG ENDIAN video       */
/*                 stream into three separate LITTLE ENDIAN 16-bit planes   */
/*                                                                          */
/*  USAGE                                                                   */
/*      This function is C callable, and is called as follows:              */
/*                                                                          */
/*      void IMG_yc_demux_be16_8                                            */
/*      (                                                                   */
/*          int n,                       // Number of luma pixels    //     */
/*          const unsigned char * yc,    // Interleaved luma/chroma  //     */
/*          short *restrict y,           // Luma plane (16-bit)      //     */
/*          short *restrict cr,          // Cr chroma plane (16-bit) //     */
/*          short *restrict cb           // Cb chroma plane (16-bit) //     */
/*      );                                                                  */
/*                                                                          */
/*      The input array 'yc' is expected to be an interleaved 4:2:2         */
/*      video stream.  The input is expected in BIG ENDIAN byte order       */
/*      within each 4-byte word.  This is consistent with reading the       */
/*      video stream from a word-oriented BIG ENDIAN device while the       */
/*      C6000 device is in a LITTLE ENDIAN configuration.                   */
/*                                                                          */
/*      In other words, the expected pixel order is:                        */
/*                                                                          */
/*                  Word 0           Word 1          Word 2                 */
/*             +---------------+---------------+---------------+--          */
/*       Byte# | 0   1   2   3 | 4   5   6   7 | 8   9  10  11 |...         */
/*             |cb0 y1  cr0 y0 |cb2 y3  cr2 y2 |cb4 y5  cr4 y4 |...         */
/*             +---------------+---------------+---------------+--          */
/*                                                                          */
/*      The output arrays 'y', 'cr', and 'cb' are expected to not           */
/*      overlap.  The de-interleaved pixels are written as half-words       */
/*      in LITTLE ENDIAN order.                                             */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      This function reads the byte-oriented pixel data, zero-extends      */
/*      it, and then writes it to the appropriate result array.  Both       */
/*      the luma and chroma values are expected to be unsigned.             */
/*                                                                          */
/*      The data is expected to be in an order consistent with reading      */
/*      byte oriented data from a word-oriented peripheral that is          */
/*      operating in BIG ENDIAN mode, while the CPU is in LITTLE ENDIAN     */
/*      mode.  This results in a pixel ordering which is not                */
/*      immediately obvious.  This function correctly reorders the          */
/*      pixel values so that further processing may proceed in LITTLE       */
/*      ENDIAN mode.                                                        */
/*                                                                          */
/*  ASSUMPTIONS                                                             */
/*      Input and output arrays are double-word aligned.                    */
/*      The input must be a multiple of 16 luma pixels long.                */
/*                                                                          */
/*  TECHNIQUES                                                              */
/*      The loop has been unrolled a total of 16 times to allow for         */
/*      processing 8 pixels in each datapath.                               */
/*                                                                          */
/*      Double-word loads and stores maximize memory bandwidth              */
/*      utilization.                                                        */
/*                                                                          */
/*      This code uses _gmpy4() to ease the L/S/D unit bottleneck on        */
/*      ANDs.  The _gmpy4(value, 0x00010001) is equivalent to               */
/*      value & 0x00FF00FF, as long as the size field of GFPGFR is          */
/*      equal to 7.  (The polynomial does not matter.)                      */
/*                                                                          */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
#ifndef YC_DEMUX_BE16_I_H_
#define YC_DEMUX_BE16_I_H_ 1

void IMG_yc_demux_be16_8
(
    int n,                               /* Number of luma pixels    */
    const unsigned char *restrict yc,    /* Interbeaved luma/chroma  */
    short         *restrict y,           /* Luma plane (8-bit)       */
    short         *restrict cr,          /* Cr chroma plane (8-bit)  */
    short         *restrict cb           /* Cb chroma plane (8-bit)  */
);

#endif
/* ======================================================================== */
/*  End of file:  IMG_yc_demux_be16_8_i.h                                   */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2008 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
