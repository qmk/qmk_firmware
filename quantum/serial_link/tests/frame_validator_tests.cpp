/*
The MIT License (MIT)

Copyright (c) 2016 Fred Sundvik

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "gtest/gtest.h"
#include "gmock/gmock.h"
extern "C" {
#include "serial_link/protocol/frame_validator.h"
}

using testing::_;
using testing::ElementsAreArray;
using testing::Args;

class FrameValidator : public testing::Test {
public:
    FrameValidator() {
        Instance = this;
    }

    ~FrameValidator() {
        Instance = nullptr;
    }

    MOCK_METHOD3(route_incoming_frame, void (uint8_t link, uint8_t* data, uint16_t size));
    MOCK_METHOD3(byte_stuffer_send_frame, void (uint8_t link, uint8_t* data, uint16_t size));

    static FrameValidator* Instance;
};

FrameValidator* FrameValidator::Instance = nullptr;

extern "C" {
void route_incoming_frame(uint8_t link, uint8_t* data, uint16_t size) {
    FrameValidator::Instance->route_incoming_frame(link, data, size);
}

void byte_stuffer_send_frame(uint8_t link, uint8_t* data, uint16_t size) {
    FrameValidator::Instance->byte_stuffer_send_frame(link, data, size);
}
}

TEST_F(FrameValidator, doesnt_validate_frames_under_5_bytes) {
    EXPECT_CALL(*this, route_incoming_frame(_, _, _))
        .Times(0);
    uint8_t data[] = {1, 2};
    validator_recv_frame(0, 0, 1);
    validator_recv_frame(0, data, 2);
    validator_recv_frame(0, data, 3);
    validator_recv_frame(0, data, 4);
}

TEST_F(FrameValidator, validates_one_byte_frame_with_correct_crc) {
    uint8_t data[] = {0x44, 0x04, 0x6A, 0xB3, 0xA3};
    EXPECT_CALL(*this, route_incoming_frame(_, _, _))
        .With(Args<1, 2>(ElementsAreArray(data, 1)));
    validator_recv_frame(0, data, 5);
}

TEST_F(FrameValidator, does_not_validate_one_byte_frame_with_incorrect_crc) {
    uint8_t data[] = {0x44, 0, 0, 0, 0};
    EXPECT_CALL(*this, route_incoming_frame(_, _, _))
        .Times(0);
    validator_recv_frame(1, data, 5);
}

TEST_F(FrameValidator, validates_four_byte_frame_with_correct_crc) {
    uint8_t data[] = {0x44, 0x10, 0xFF, 0x00, 0x74, 0x4E, 0x30, 0xBA};
    EXPECT_CALL(*this, route_incoming_frame(_, _, _))
        .With(Args<1, 2>(ElementsAreArray(data, 4)));
    validator_recv_frame(1, data, 8);
}

TEST_F(FrameValidator, validates_five_byte_frame_with_correct_crc) {
    uint8_t data[] = {1, 2, 3, 4, 5, 0xF4, 0x99, 0x0B, 0x47};
    EXPECT_CALL(*this, route_incoming_frame(_, _, _))
        .With(Args<1, 2>(ElementsAreArray(data, 5)));
    validator_recv_frame(0, data, 9);
}

TEST_F(FrameValidator, sends_one_byte_with_correct_crc) {
    uint8_t original[] = {0x44, 0, 0, 0, 0};
    uint8_t expected[] = {0x44, 0x04, 0x6A, 0xB3, 0xA3};
    EXPECT_CALL(*this, byte_stuffer_send_frame(_, _, _))
        .With(Args<1, 2>(ElementsAreArray(expected)));
    validator_send_frame(0, original, 1);
}

TEST_F(FrameValidator, sends_five_bytes_with_correct_crc) {
    uint8_t original[] = {1, 2, 3, 4, 5, 0, 0, 0, 0};
    uint8_t expected[] = {1, 2, 3, 4, 5, 0xF4, 0x99, 0x0B, 0x47};
    EXPECT_CALL(*this, byte_stuffer_send_frame(_, _, _))
        .With(Args<1, 2>(ElementsAreArray(expected)));
    validator_send_frame(0, original, 5);
}
