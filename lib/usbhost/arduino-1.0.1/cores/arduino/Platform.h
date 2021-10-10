
#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include <inttypes.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <util/delay.h>

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

#include "Arduino.h"

#if defined(USBCON)
	#include "USBDesc.h"
	#include "USBCore.h"
	#include "USBAPI.h"
#endif /* if defined(USBCON) */

#endif
