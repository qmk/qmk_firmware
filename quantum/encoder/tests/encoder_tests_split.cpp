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
#include "encoder/tests/mock_split.h"
}

struct update {
    int8_t index;
    bool   clockwise;
};

uint8_t uidx = 0;
update  updates[32];

bool isLeftHand;

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!isLeftHand) {
        // this method has no effect on slave half
        printf("ignoring update on right hand (%d,%s)\n", index, clockwise ? "CW" : "CC");
        return true;
    }
    updates[uidx % 32] = {index, clockwise};
    uidx++;
    return true;
}

bool setAndRead(pin_t pin, bool val) {
    setPin(pin, val);
    return encoder_read();
}

class EncoderTest : public ::testing::Test {
   protected:
    void SetUp() override {
        uidx = 0;
        for (int i = 0; i < 32; i++) {
            pinIsInputHigh[i] = 0;
            pins[i]           = 0;
        }
    }
};

TEST_F(EncoderTest, TestInitLeft) {
    isLeftHand = true;
    encoder_init();
    EXPECT_EQ(pinIsInputHigh[0], true);
    EXPECT_EQ(pinIsInputHigh[1], true);
    EXPECT_EQ(pinIsInputHigh[2], false);
    EXPECT_EQ(pinIsInputHigh[3], false);
    EXPECT_EQ(uidx, 0);
}

TEST_F(EncoderTest, TestInitRight) {
    isLeftHand = false;
    encoder_init();
    EXPECT_EQ(pinIsInputHigh[0], false);
    EXPECT_EQ(pinIsInputHigh[1], false);
    EXPECT_EQ(pinIsInputHigh[2], true);
    EXPECT_EQ(pinIsInputHigh[3], true);
    EXPECT_EQ(uidx, 0);
}

TEST_F(EncoderTest, TestOneClockwiseLeft) {
    isLeftHand = true;
    encoder_init();
    // send 4 pulses. with resolution 4, that's one step and we should get 1 update.
    setAndRead(0, false);
    setAndRead(1, false);
    setAndRead(0, true);
    setAndRead(1, true);

    EXPECT_EQ(uidx, 1);
    EXPECT_EQ(updates[0].index, 0);
    EXPECT_EQ(updates[0].clockwise, true);
}

TEST_F(EncoderTest, TestOneClockwiseRightSent) {
    isLeftHand = false;
    encoder_init();
    // send 4 pulses. with resolution 4, that's one step and we should get 1 update.
    setAndRead(2, false);
    setAndRead(3, false);
    setAndRead(2, true);
    setAndRead(3, true);

    uint8_t slave_state[2] = {0};
    encoder_state_raw(slave_state);

    EXPECT_EQ((int8_t)slave_state[0], -1);
}

/* this test will not work after the previous test.
 * this is due to encoder_value[1] already being set to -1 when simulating the right half.
 * When we now receive this update acting as the left half, there is no change.
 * This is hard to mock, as the static values inside encoder.c normally exist twice, once on each half,
 * but here, they only exist once.
 */

// TEST_F(EncoderTest, TestOneClockwiseRightReceived) {
//     isLeftHand = true;
//     encoder_init();

//     uint8_t slave_state[2] = {255, 0};
//     encoder_update_raw(slave_state);

//     EXPECT_EQ(uidx, 1);
//     EXPECT_EQ(updates[0].index, 1);
//     EXPECT_EQ(updates[0].clockwise, true);
// }

TEST_F(EncoderTest, TestOneCounterClockwiseRightReceived) {
    isLeftHand = true;
    encoder_init();

    uint8_t slave_state[2] = {0, 0};
    encoder_update_raw(slave_state);

    EXPECT_EQ(uidx, 1);
    EXPECT_EQ(updates[0].index, 1);
    EXPECT_EQ(updates[0].clockwise, false);
}
