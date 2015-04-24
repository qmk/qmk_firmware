/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef MBED_H
#define MBED_H

#define MBED_LIBRARY_VERSION 97

#include "platform.h"

// Useful C libraries
#include <math.h>
#include <time.h>

// mbed Debug libraries
#include "mbed_error.h"
#include "mbed_interface.h"

// mbed Peripheral components
#include "DigitalIn.h"
#include "DigitalOut.h"
#include "DigitalInOut.h"
#include "BusIn.h"
#include "BusOut.h"
#include "BusInOut.h"
#include "PortIn.h"
#include "PortInOut.h"
#include "PortOut.h"
#include "AnalogIn.h"
#include "AnalogOut.h"
#include "PwmOut.h"
#include "Serial.h"
#include "SPI.h"
#include "SPISlave.h"
#include "I2C.h"
#include "I2CSlave.h"
#include "Ethernet.h"
#include "CAN.h"
#include "RawSerial.h"

// mbed Internal components
#include "Timer.h"
#include "Ticker.h"
#include "Timeout.h"
#include "LocalFileSystem.h"
#include "InterruptIn.h"
#include "wait_api.h"
#include "sleep_api.h"
#include "rtc_time.h"

using namespace mbed;
using namespace std;

#endif
