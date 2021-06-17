
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <vector>
#include <algorithm>
#include <stdio.h>

extern "C" {
    #include "encoder.h"
    #include "encoder/tests/mock.h"
}

struct update {
    int8_t index;
    bool clockwise;
};

uint8_t uidx = 0;
update updates[32];

void encoder_update_kb(int8_t index, bool clockwise) {
    updates[uidx % 32] = {index, clockwise};
    uidx++;
}

bool setAndRead(pin_t pin, bool val) {
    setPin(pin, val);
    return encoder_read();
}

class EncoderTest : public ::testing::Test {

};

TEST_F(EncoderTest, TestInit) {
    uidx = 0;
    encoder_init();
    EXPECT_EQ(pinIsInputHigh[0], true);
    EXPECT_EQ(pinIsInputHigh[1], true);
    EXPECT_EQ(uidx, 0);
}

TEST_F(EncoderTest, TestOneClockwise) {
    uidx = 0;
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

TEST_F(EncoderTest, TestOneCounterClockwise) {
    uidx = 0;
    encoder_init();
    setAndRead(1, false);
    setAndRead(0, false);
    setAndRead(1, true);
    setAndRead(0, true);

    EXPECT_EQ(uidx, 1);
    EXPECT_EQ(updates[0].index, 0);
    EXPECT_EQ(updates[0].clockwise, false);
}

TEST_F(EncoderTest, TestTwoClockwiseOneCC) {
    uidx = 0;
    encoder_init();
    setAndRead(0, false);
    setAndRead(1, false);
    setAndRead(0, true);
    setAndRead(1, true);
    setAndRead(0, false);
    setAndRead(1, false);
    setAndRead(0, true);
    setAndRead(1, true);
    setAndRead(1, false);
    setAndRead(0, false);
    setAndRead(1, true);
    setAndRead(0, true);

    EXPECT_EQ(uidx, 3);
    EXPECT_EQ(updates[0].index, 0);
    EXPECT_EQ(updates[0].clockwise, true);
    EXPECT_EQ(updates[1].index, 0);
    EXPECT_EQ(updates[1].clockwise, true);
    EXPECT_EQ(updates[2].index, 0);
    EXPECT_EQ(updates[2].clockwise, false);
}

TEST_F(EncoderTest, TestNoEarly) {
    uidx = 0;
    encoder_init();
    // send 3 pulses. with resolution 4, that's not enough for a step.
    setAndRead(0, false);
    setAndRead(1, false);
    setAndRead(0, true);
    EXPECT_EQ(uidx, 0);
    // now send last pulse
    setAndRead(1, true);
    EXPECT_EQ(uidx, 1);
    EXPECT_EQ(updates[0].index, 0);
    EXPECT_EQ(updates[0].clockwise, true);
}

TEST_F(EncoderTest, TestHalfway) {
    uidx = 0;
    encoder_init();
    // go halfway
    setAndRead(0, false);
    setAndRead(1, false);
    EXPECT_EQ(uidx, 0);
    // back off
    setAndRead(1, true);
    setAndRead(0, true);
    EXPECT_EQ(uidx, 0);
    // go all the way
    setAndRead(0, false);
    setAndRead(1, false);
    setAndRead(0, true);
    setAndRead(1, true);
    // should result in 1 update
    EXPECT_EQ(uidx, 1);
    EXPECT_EQ(updates[0].index, 0);
    EXPECT_EQ(updates[0].clockwise, true);
}
