/* Copyright 2021 Balz Guenat
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <vector>
#include <algorithm>
#include <stdio.h>

extern "C" {
#include "encoder.h"
#include "keyboard.h"
#include "encoder/tests/mock_split.h"
}

struct update {
    int8_t index;
    bool   clockwise;
};

uint8_t num_updates = 0;

bool isMaster;
bool isLeftHand;

bool is_keyboard_master(void) {
    return isMaster;
}

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!isMaster) {
        ADD_FAILURE() << "We shouldn't get here.";
    }
    num_updates++;
    return true;
}

bool setAndRead(pin_t pin, bool val) {
    setPin(pin, val);
    return encoder_task();
}

class EncoderSplitTestRole : public ::testing::Test {
   protected:
    void SetUp() override {
        num_updates = 0;
        for (int i = 0; i < 32; i++) {
            pinIsInputHigh[i] = 0;
            pins[i]           = 0;
        }
    }
};

TEST_F(EncoderSplitTestRole, TestPrimaryLeft) {
    isMaster   = true;
    isLeftHand = true;
    encoder_init();
    // send 4 pulses. with resolution 4, that's one step and we should get 1 update.
    setAndRead(0, false);
    setAndRead(1, false);
    setAndRead(0, true);
    setAndRead(1, true);

    EXPECT_EQ(num_updates, 1); // one update received
}

TEST_F(EncoderSplitTestRole, TestPrimaryRight) {
    isMaster   = true;
    isLeftHand = false;
    encoder_init();
    // send 4 pulses. with resolution 4, that's one step and we should get 1 update.
    setAndRead(6, false);
    setAndRead(7, false);
    setAndRead(6, true);
    setAndRead(7, true);

    EXPECT_EQ(num_updates, 1); // one update received
}

TEST_F(EncoderSplitTestRole, TestNotPrimaryLeft) {
    isMaster   = false;
    isLeftHand = true;
    encoder_init();
    // send 4 pulses. with resolution 4, that's one step and we should get 1 update.
    setAndRead(0, false);
    setAndRead(1, false);
    setAndRead(0, true);
    setAndRead(1, true);

    EXPECT_EQ(num_updates, 0); // zero updates received
}

TEST_F(EncoderSplitTestRole, TestNotPrimaryRight) {
    isMaster   = false;
    isLeftHand = false;
    encoder_init();
    // send 4 pulses. with resolution 4, that's one step and we should get 1 update.
    setAndRead(6, false);
    setAndRead(7, false);
    setAndRead(6, true);
    setAndRead(7, true);

    EXPECT_EQ(num_updates, 0); // zero updates received
}
