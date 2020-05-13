/**************************************************************************/
/*!
    Modified from the original Adafruit_BLEBatterry.h which was released under
    the BSD License (below).

    Software License Agreement (BSD License)

    Copyright (c) 2020, Joshua Rubin
    Copyright (c) 2016, Adafruit Industries (adafruit.com)
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holders nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/**************************************************************************/

#include "BLEBattery.h"
#include "timer.h"

/******************************************************************************/
/*!
    @brief Constructor
*/
/******************************************************************************/
BLEBattery::BLEBattery(BLE& ble) : _ble(ble) {}

/******************************************************************************/
/*!
    @brief Enable Battery service if not already enabled
    @param reset true will reset Bluefruit
*/
/******************************************************************************/
bool BLEBattery::begin(bool reset) {
    int32_t enabled = 0;
    VERIFY_(_ble.atcommandIntReply(F("AT+BLEBATTEN"), &enabled));
    if (enabled) return true;

    VERIFY_(_ble.atcommand(F("AT+BLEBATTEN=1")));

    // Perform Bluefruit reset if needed
    if (reset) _ble.reset();

    return true;
}

/******************************************************************************/
/*!
    @brief Stop Battery service if it is enabled
    @param reset true will reset Bluefruit
*/
/******************************************************************************/
bool BLEBattery::stop(bool reset) {
    int32_t enabled = 0;
    VERIFY_(_ble.atcommandIntReply(F("AT+BLEBATTEN"), &enabled));
    if (!enabled) return true;

    VERIFY_(_ble.atcommand(F("AT+BLEBATTEN=0")));

    // Perform Bluefruit reset if needed
    if (reset) _ble.reset();

    return true;
}

static inline bool is_within(uint32_t lower, uint32_t value, uint32_t upper) { return (lower <= value) && (value <= upper); }

/******************************************************************************/
/*!
    @brief Update Battery level value
    @param percent Battery value in percentage 0-100
*/
/******************************************************************************/
bool BLEBattery::update(uint8_t percent, uint32_t period_ms) {
    static uint32_t tt = 0;

    VERIFY_(is_within(0, percent, 100));

    if (!period_ms || timer_elapsed32(tt) > period_ms) {
        if (period_ms) tt = timer_read32();
        return _ble.atcommand(F("AT+BLEBATTVAL"), percent);
    }

    return false;
}
