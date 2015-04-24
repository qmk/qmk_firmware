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
#include "CAN.h"

#if DEVICE_CAN

#include "cmsis.h"

namespace mbed {

CAN::CAN(PinName rd, PinName td) : _can(), _irq() {
    can_init(&_can, rd, td);
    can_irq_init(&_can, (&CAN::_irq_handler), (uint32_t)this);
}

CAN::~CAN() {
    can_irq_free(&_can);
    can_free(&_can);
}

int CAN::frequency(int f) {
    return can_frequency(&_can, f);
}

int CAN::write(CANMessage msg) {
    return can_write(&_can, msg, 0);
}

int CAN::read(CANMessage &msg, int handle) {
    return can_read(&_can, &msg, handle);
}

void CAN::reset() {
    can_reset(&_can);
}

unsigned char CAN::rderror() {
    return can_rderror(&_can);
}

unsigned char CAN::tderror() {
    return can_tderror(&_can);
}

void CAN::monitor(bool silent) {
    can_monitor(&_can, (silent) ? 1 : 0);
}

int CAN::mode(Mode mode) {
    return can_mode(&_can, (CanMode)mode);
}

int CAN::filter(unsigned int id, unsigned int mask, CANFormat format, int handle) {
    return can_filter(&_can, id, mask, format, handle);
}

void CAN::attach(void (*fptr)(void), IrqType type) {
    if (fptr) {
        _irq[(CanIrqType)type].attach(fptr);
        can_irq_set(&_can, (CanIrqType)type, 1);
    } else {
        can_irq_set(&_can, (CanIrqType)type, 0);
    }
}

void CAN::_irq_handler(uint32_t id, CanIrqType type) {
    CAN *handler = (CAN*)id;
    handler->_irq[type].call();
}

} // namespace mbed

#endif
