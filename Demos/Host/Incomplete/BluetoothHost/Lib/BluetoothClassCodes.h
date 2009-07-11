/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/
/*
  Copyright 2009  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, and distribute this software
  and its documentation for any purpose and without fee is hereby
  granted, provided that the above copyright notice appear in all
  copies and that both that the copyright notice and this
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

#ifndef _BLUETOOTH_CLASS_CODES_H_
#define _BLUETOOTH_CLASS_CODES_H_

	/* Macros: */
		#define DEVICE_CLASS_SERVICE_POSITIONING               (1UL << 16)
		#define DEVICE_CLASS_SERVICE_NETWORKING                (1UL << 17)
		#define DEVICE_CLASS_SERVICE_RENDERING                 (1UL << 18)
		#define DEVICE_CLASS_SERVICE_CAPTURING                 (1UL << 19)
		#define DEVICE_CLASS_SERVICE_OBJECTTRANSFER            (1UL << 20)
		#define DEVICE_CLASS_SERVICE_AUDIO                     (1UL << 21)
		#define DEVICE_CLASS_SERVICE_TELEPHONY                 (1UL << 22)
		#define DEVICE_CLASS_SERVICE_INFORMATION               (1UL << 23)
		
		#define DEVICE_CLASS_MAJOR_MISC                        (0x00 << 8)
		#define DEVICE_CLASS_MAJOR_COMPUTER                    (0x01 << 8)
		#define DEVICE_CLASS_MAJOR_PHONE                       (0x02 << 8)
		#define DEVICE_CLASS_MAJOR_LAN                         (0x03 << 8)
		#define DEVICE_CLASS_MAJOR_AUDIOVIDEO                  (0x04 << 8)
		#define DEVICE_CLASS_MAJOR_PERIPHERAL                  (0x05 << 8)
		#define DEVICE_CLASS_MAJOR_IMAGING                     (0x06 << 8)
		#define DEVICE_CLASS_MAJOR_UNCLASSIFIED                (0x1F << 8)

		#define DEVICE_CLASS_MINOR_COMPUTER_UNCATEGORIZED      (0x00 << 2)
		#define DEVICE_CLASS_MINOR_COMPUTER_DESKTOP            (0x01 << 2)
		#define DEVICE_CLASS_MINOR_COMPUTER_SERVER             (0x02 << 2)
		#define DEVICE_CLASS_MINOR_COMPUTER_LAPTOP             (0x03 << 2)
		#define DEVICE_CLASS_MINOR_COMPUTER_HANDHELD           (0x04 << 2)
		#define DEVICE_CLASS_MINOR_COMPUTER_PALM               (0x05 << 2)
		#define DEVICE_CLASS_MINOR_COMPUTER_WEARABLE           (0x06 << 2)
		
		#define DEVICE_CLASS_MINOR_PHONE_UNCATEGORIZED         (0x00 << 2)
		#define DEVICE_CLASS_MINOR_PHONE_CELLULAR              (0x01 << 2)
		#define DEVICE_CLASS_MINOR_PHONE_CORDLESS              (0x02 << 2)
		#define DEVICE_CLASS_MINOR_PHONE_SMARTPHONE            (0x03 << 2)
		#define DEVICE_CLASS_MINOR_PHONE_WIREDMODEM            (0x04 << 2)
		#define DEVICE_CLASS_MINOR_PHONE_ISDN                  (0x05 << 2)

		#define DEVICE_CLASS_MINOR_LAN_FULLY_AVAILABLE         (0x00 << 5)
		#define DEVICE_CLASS_MINOR_LAN_1_TO_17_PC_UTILIZED     (0x01 << 5)
		#define DEVICE_CLASS_MINOR_LAN_17_TO_33_PC_UTILIZED    (0x02 << 5)
		#define DEVICE_CLASS_MINOR_LAN_33_TO_50_PC_UTILIZED    (0x03 << 5)
		#define DEVICE_CLASS_MINOR_LAN_50_TO_67_PC_UTILIZED    (0x04 << 5)
		#define DEVICE_CLASS_MINOR_LAN_67_TO_83_PC_UTILIZED    (0x05 << 5)
		#define DEVICE_CLASS_MINOR_LAN_83_TO_99_PC_UTILIZED    (0x06 << 5)
		#define DEVICE_CLASS_MINOR_NO_SERVICE_AVAILABLE        (0x07 << 5)
		
		#define DEVICE_CLASS_MINOR_AV_UNCATEGORIZED            (0x00 << 2)
		#define DEVICE_CLASS_MINOR_AV_HEADSET                  (0x01 << 2)
		#define DEVICE_CLASS_MINOR_AV_HANDSFREE                (0x02 << 2)
		#define DEVICE_CLASS_MINOR_AV_MICROPHONE               (0x04 << 2)
		#define DEVICE_CLASS_MINOR_AV_LOUDSPEAKER              (0x05 << 2)
		#define DEVICE_CLASS_MINOR_AV_HEADPHONES               (0x06 << 2)
		#define DEVICE_CLASS_MINOR_AV_PORTABLE_AUDIO           (0x07 << 2)
		#define DEVICE_CLASS_MINOR_AV_CARAUDIO                 (0x08 << 2)
		#define DEVICE_CLASS_MINOR_AV_SETTOP_BOX               (0x09 << 2)
		#define DEVICE_CLASS_MINOR_AV_HIFI                     (0x0A << 2)
		#define DEVICE_CLASS_MINOR_AV_VCR                      (0x0B << 2)
		#define DEVICE_CLASS_MINOR_AV_VIDEO_CAMERA             (0x0C << 2)
		#define DEVICE_CLASS_MINOR_AV_CAMCORDER                (0x0D << 2)
		#define DEVICE_CLASS_MINOR_AV_VIDEO_MONITOR            (0x0E << 2)
		#define DEVICE_CLASS_MINOR_AV_DISPLAY_AND_LOUDSPEAKER  (0x0F << 2)
		#define DEVICE_CLASS_MINOR_AV_VIDEO_CONFERENCING       (0x10 << 2)
		#define DEVICE_CLASS_MINOR_AV_GAMING_TOY               (0x12 << 2)
		
		#define DEVICE_CLASS_MINOR_PERIPHERAL_KEYBOARD         (0x01 << 6)
		#define DEVICE_CLASS_MINOR_PERIPHERAL_POINTING         (0x02 << 6)
		#define DEVICE_CLASS_MINOR_PERIPHERAL_COMBO            (0x03 << 6)
		#define DEVICE_CLASS_MINOR_PERIPHERAL_UNCATEGORIZED    (0x00 << 2)
		#define DEVICE_CLASS_MINOR_PERIPHERAL_JOYSTICK         (0x01 << 2)
		#define DEVICE_CLASS_MINOR_PERIPHERAL_GAMEPAD          (0x02 << 2)
		#define DEVICE_CLASS_MINOR_PERIPHERAL_REMOTE_CONTROL   (0x03 << 2)
		#define DEVICE_CLASS_MINOR_PERIPHERAL_SENSING_DEVICE   (0x04 << 2)
		#define DEVICE_CLASS_MINOR_PERIPHERAL_DIGITIZER        (0x05 << 2)
		#define DEVICE_CLASS_MINOR_PERIPHERAL_CARD_READER      (0x06 << 2)

		#define DEVICE_CLASS_MINOR_IMAGING_DISPLAY             (1 << 4)
		#define DEVICE_CLASS_MINOR_IMAGING_CAMERA              (1 << 5)
		#define DEVICE_CLASS_MINOR_IMAGING_SCANNER             (1 << 6)
		#define DEVICE_CLASS_MINOR_IMAGING_PRINTER             (1 << 7)

#endif
