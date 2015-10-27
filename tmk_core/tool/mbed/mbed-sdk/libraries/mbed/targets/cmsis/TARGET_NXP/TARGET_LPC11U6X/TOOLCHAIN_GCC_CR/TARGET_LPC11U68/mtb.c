//*****************************************************************************
//   +--+       
//   | ++----+   
//   +-++    |  
//     |     |  
//   +-+--+  |   
//   | +--+--+  
//   +----+    Copyright (c) 2013 Code Red Technologies Ltd.
//
//  mtb.c 
//
// Optionally defines an array to be used as a buffer for Micro Trace
// Buffer (MTB) instruction trace on Cortex-M0+ parts
//
// Version : 130502
//
// Software License Agreement
// 
// The software is owned by Code Red Technologies and/or its suppliers, and is 
// protected under applicable copyright laws.  All rights are reserved.  Any 
// use in violation of the foregoing restrictions may subject the user to criminal 
// sanctions under applicable laws, as well as to civil liability for the breach
// of the terms and conditions of this license.
// 
// THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
// OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
// USE OF THIS SOFTWARE FOR COMMERCIAL DEVELOPMENT AND/OR EDUCATION IS SUBJECT
// TO A CURRENT END USER LICENSE AGREEMENT (COMMERCIAL OR EDUCATIONAL) WITH
// CODE RED TECHNOLOGIES LTD. 
//
//*****************************************************************************

/*******************************************************************
 * Symbols controlling behavior of this code...
 *
 * __MTB_DISABLE
 *     If this symbol is defined, then the buffer array for the MTB
 *     will not be created.
 *
 * __MTB_BUFFER_SIZE
 *     Symbol specifying the sizer of the buffer array for the MTB.
 *     This must be a power of 2 in size, and fit into the available
 *     RAM. The MTB buffer will also be aligned to its 'size' 
 *     boundary and be placed at the start of a RAM bank (which 
 *     should ensure minimal or zero padding due to alignment).
 * 
 * __MTB_RAM_BANK
 *     Allows MTB Buffer to be placed into specific RAM bank. When 
 *     this is not defined, the "default" (first if there are 
 *     several) RAM bank is used.
 *******************************************************************/

// Ignore with none Code Red tools
#if defined (__CODE_RED)

// Allow MTB to be removed by setting a define (via command line)
#if !defined (__MTB_DISABLE)

  // Allow for MTB buffer size being set by define set via command line
  // Otherwise provide small default buffer
  #if !defined (__MTB_BUFFER_SIZE)
    #define __MTB_BUFFER_SIZE 128
  #endif

  // Check that buffer size requested is >0 bytes in size
  #if (__MTB_BUFFER_SIZE > 0)
    // Pull in MTB related macros
    #include <cr_mtb_buffer.h>

    // Check if MYTB buffer is to be placed in specific RAM bank
    #if defined(__MTB_RAM_BANK)
	    // Place MTB buffer into explicit bank of RAM
	    __CR_MTB_BUFFER_EXT(__MTB_BUFFER_SIZE,__MTB_RAM_BANK);
    #else
	    // Place MTB buffer into 'default' bank of RAM
	    __CR_MTB_BUFFER(__MTB_BUFFER_SIZE);

    #endif  // defined(__MTB_RAM_BANK)

  #endif // (__MTB_BUFFER_SIZE > 0)

#endif // !defined (__MTB_DISABLE)

#endif // defined (__CODE_RED)
