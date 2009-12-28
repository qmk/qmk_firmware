/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2009  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this 
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in 
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting 
  documentation, and that the name of the author not be used in 
  advertising or publicity pertaining to distribution of the 
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *
 *  Header containing macros for possible SCSI commands and SENSE data. Refer to
 *  the SCSI standard documentation for more information on each SCSI command and
 *  the SENSE data.
 */
 
#ifndef _SCSI_CODES_H_
#define _SCSI_CODES_H_

	/* Macros: */
		#define SCSI_CMD_INQUIRY                               0x12
		#define SCSI_CMD_REQUEST_SENSE                         0x03
		#define SCSI_CMD_TEST_UNIT_READY                       0x00
		#define SCSI_CMD_READ_CAPACITY_10                      0x25
		#define SCSI_CMD_SEND_DIAGNOSTIC                       0x1D
		#define SCSI_CMD_PREVENT_ALLOW_MEDIUM_REMOVAL          0x1E
		#define SCSI_CMD_WRITE_10                              0x2A
		#define SCSI_CMD_READ_10                               0x28
		#define SCSI_CMD_WRITE_6                               0x0A
		#define SCSI_CMD_READ_6                                0x08
		#define SCSI_CMD_VERIFY_10                             0x2F
		#define SCSI_CMD_MODE_SENSE_6                          0x1A
		#define SCSI_CMD_MODE_SENSE_10                         0x5A

		#define SCSI_SENSE_KEY_GOOD                            0x00
		#define SCSI_SENSE_KEY_RECOVERED_ERROR                 0x01
		#define SCSI_SENSE_KEY_NOT_READY                       0x02
		#define SCSI_SENSE_KEY_MEDIUM_ERROR                    0x03
		#define SCSI_SENSE_KEY_HARDWARE_ERROR                  0x04
		#define SCSI_SENSE_KEY_ILLEGAL_REQUEST                 0x05
		#define SCSI_SENSE_KEY_UNIT_ATTENTION                  0x06
		#define SCSI_SENSE_KEY_DATA_PROTECT                    0x07
		#define SCSI_SENSE_KEY_BLANK_CHECK                     0x08
		#define SCSI_SENSE_KEY_VENDOR_SPECIFIC                 0x09
		#define SCSI_SENSE_KEY_COPY_ABORTED                    0x0A
		#define SCSI_SENSE_KEY_ABORTED_COMMAND                 0x0B
		#define SCSI_SENSE_KEY_VOLUME_OVERFLOW                 0x0D
		#define SCSI_SENSE_KEY_MISCOMPARE                      0x0E

		#define SCSI_ASENSE_NO_ADDITIONAL_INFORMATION          0x00
		#define SCSI_ASENSE_LOGICAL_UNIT_NOT_READY             0x04
		#define SCSI_ASENSE_INVALID_FIELD_IN_CDB               0x24
		#define SCSI_ASENSE_WRITE_PROTECTED                    0x27
		#define SCSI_ASENSE_FORMAT_ERROR                       0x31
		#define SCSI_ASENSE_INVALID_COMMAND                    0x20
		#define SCSI_ASENSE_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE 0x21
		#define SCSI_ASENSE_MEDIUM_NOT_PRESENT                 0x3A

		#define SCSI_ASENSEQ_NO_QUALIFIER                      0x00
		#define SCSI_ASENSEQ_FORMAT_COMMAND_FAILED             0x01
		#define SCSI_ASENSEQ_INITIALIZING_COMMAND_REQUIRED     0x02
		#define SCSI_ASENSEQ_OPERATION_IN_PROGRESS             0x07

#endif
