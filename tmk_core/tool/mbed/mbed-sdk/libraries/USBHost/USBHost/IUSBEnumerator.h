/* mbed USBHost Library
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

#ifndef IUSBENUMERATOR_H_
#define IUSBENUMERATOR_H_

#include "stdint.h"
#include "USBEndpoint.h"

/*
Generic interface to implement for "smart" USB enumeration
*/

class IUSBEnumerator
{
public:
    virtual void setVidPid(uint16_t vid, uint16_t pid) = 0;
    virtual bool parseInterface(uint8_t intf_nb, uint8_t intf_class, uint8_t intf_subclass, uint8_t intf_protocol) = 0; //Must return true if the interface should be parsed
    virtual bool useEndpoint(uint8_t intf_nb, ENDPOINT_TYPE type, ENDPOINT_DIRECTION dir) = 0; //Must return true if the endpoint will be used
};

#endif /*IUSBENUMERATOR_H_*/

