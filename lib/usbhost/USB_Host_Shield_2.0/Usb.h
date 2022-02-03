/* Copyright (C) 2011 Circuits At Home, LTD. All rights reserved.

This software may be distributed and modified under the terms of the GNU
General Public License version 2 (GPL2) as published by the Free Software
Foundation and appearing in the file GPL2.TXT included in the packaging of
this file. Please note that GPL2 Section 2[b] requires that all works based
on this software must also be made publicly available under the terms of
the GPL2 ("Copyleft").

Contact information
-------------------

Circuits At Home, LTD
Web      :  http://www.circuitsathome.com
e-mail   :  support@circuitsathome.com
 */
/* USB functions */
#ifndef _usb_h_
#define _usb_h_

// WARNING: Do not change the order of includes, or stuff will break!
#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>

// None of these should ever be included by a driver, or a user's sketch.
#include "settings.h"
#include "printhex.h"
#include "message.h"
#include "hexdump.h"
#include "sink_parser.h"
#include "max3421e.h"
#include "address.h"
#include "avrpins.h"
#include "usb_ch9.h"
#include "usbhost.h"
#include "UsbCore.h"
#include "parsetools.h"
#include "confdescparser.h"

#endif //_usb_h_
