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
#include <vector>
#include <algorithm>
extern "C" {
#include "serial_link/protocol/byte_stuffer.h"
#include "serial_link/protocol/frame_validator.h"
#include "serial_link/protocol/physical.h"
}

using testing::_;
using testing::Args;
using testing::ElementsAreArray;

class ByteStuffer : public ::testing::Test {
   public:
    ByteStuffer() {
        Instance = this;
        init_byte_stuffer();
    }

    ~ByteStuffer() { Instance = nullptr; }

    MOCK_METHOD3(validator_recv_frame, void(uint8_t link, uint8_t* data, uint16_t size));

    void                 send_data(uint8_t link, const uint8_t* data, uint16_t size) { std::copy(data, data + size, std::back_inserter(sent_data)); }
    std::vector<uint8_t> sent_data;

    static ByteStuffer* Instance;
};

ByteStuffer* ByteStuffer::Instance = nullptr;

extern "C" {
void validator_recv_frame(uint8_t link, uint8_t* data, uint16_t size) { ByteStuffer::Instance->validator_recv_frame(link, data, size); }

void send_data(uint8_t link, const uint8_t* data, uint16_t size) { ByteStuffer::Instance->send_data(link, data, size); }
}

TEST_F(ByteStuffer, receives_no_frame_for_a_single_zero_byte) {
    EXPECT_CALL(*this, validator_recv_frame(_, _, _)).Times(0);
    byte_stuffer_recv_byte(0, 0);
}

TEST_F(ByteStuffer, receives_no_frame_for_a_single_FF_byte) {
    EXPECT_CALL(*this, validator_recv_frame(_, _, _)).Times(0);
    byte_stuffer_recv_byte(0, 0xFF);
}

TEST_F(ByteStuffer, receives_no_frame_for_a_single_random_byte) {
    EXPECT_CALL(*this, validator_recv_frame(_, _, _)).Times(0);
    byte_stuffer_recv_byte(0, 0x4A);
}

TEST_F(ByteStuffer, receives_no_frame_for_a_zero_length_frame) {
    EXPECT_CALL(*this, validator_recv_frame(_, _, _)).Times(0);
    byte_stuffer_recv_byte(0, 1);
    byte_stuffer_recv_byte(0, 0);
}

TEST_F(ByteStuffer, receives_single_byte_valid_frame) {
    uint8_t expected[] = {0x37};
    EXPECT_CALL(*this, validator_recv_frame(_, _, _)).With(Args<1, 2>(ElementsAreArray(expected)));
    byte_stuffer_recv_byte(0, 2);
    byte_stuffer_recv_byte(0, 0x37);
    byte_stuffer_recv_byte(0, 0);
}
TEST_F(ByteStuffer, receives_three_bytes_valid_frame) {
    uint8_t expected[] = {0x37, 0x99, 0xFF};
    EXPECT_CALL(*this, validator_recv_frame(_, _, _)).With(Args<1, 2>(ElementsAreArray(expected)));
    byte_stuffer_recv_byte(0, 4);
    byte_stuffer_recv_byte(0, 0x37);
    byte_stuffer_recv_byte(0, 0x99);
    byte_stuffer_recv_byte(0, 0xFF);
    byte_stuffer_recv_byte(0, 0);
}

TEST_F(ByteStuffer, receives_single_zero_valid_frame) {
    uint8_t expected[] = {0};
    EXPECT_CALL(*this, validator_recv_frame(_, _, _)).With(Args<1, 2>(ElementsAreArray(expected)));
    byte_stuffer_recv_byte(0, 1);
    byte_stuffer_recv_byte(0, 1);
    byte_stuffer_recv_byte(0, 0);
}

TEST_F(ByteStuffer, receives_valid_frame_with_zeroes) {
    uint8_t expected[] = {5, 0, 3, 0};
    EXPECT_CALL(*this, validator_recv_frame(_, _, _)).With(Args<1, 2>(ElementsAreArray(expected)));
    byte_stuffer_recv_byte(0, 2);
    byte_stuffer_recv_byte(0, 5);
    byte_stuffer_recv_byte(0, 2);
    byte_stuffer_recv_byte(0, 3);
    byte_stuffer_recv_byte(0, 1);
    byte_stuffer_recv_byte(0, 0);
}

TEST_F(ByteStuffer, receives_two_valid_frames) {
    uint8_t expected1[] = {5, 0};
    uint8_t expected2[] = {3};
    EXPECT_CALL(*this, validator_recv_frame(_, _, _)).With(Args<1, 2>(ElementsAreArray(expected1)));
    EXPECT_CALL(*this, validator_recv_frame(_, _, _)).With(Args<1, 2>(ElementsAreArray(expected2)));
    byte_stuffer_recv_byte(1, 2);
    byte_stuffer_recv_byte(1, 5);
    byte_stuffer_recv_byte(1, 1);
    byte_stuffer_recv_byte(1, 0);
    byte_stuffer_recv_byte(1, 2);
    byte_stuffer_recv_byte(1, 3);
    byte_stuffer_recv_byte(1, 0);
}

TEST_F(ByteStuffer, receives_valid_frame_after_unexpected_zero) {
    uint8_t expected[] = {5, 7};
    EXPECT_CALL(*this, validator_recv_frame(_, _, _)).With(Args<1, 2>(ElementsAreArray(expected)));
    byte_stuffer_recv_byte(1, 3);
    byte_stuffer_recv_byte(1, 1);
    byte_stuffer_recv_byte(1, 0);
    byte_stuffer_recv_byte(1, 3);
    byte_stuffer_recv_byte(1, 5);
    byte_stuffer_recv_byte(1, 7);
    byte_stuffer_recv_byte(1, 0);
}

TEST_F(ByteStuffer, receives_valid_frame_after_unexpected_non_zero) {
    uint8_t expected[] = {5, 7};
    EXPECT_CALL(*this, validator_recv_frame(_, _, _)).With(Args<1, 2>(ElementsAreArray(expected)));
    byte_stuffer_recv_byte(0, 2);
    byte_stuffer_recv_byte(0, 9);
    byte_stuffer_recv_byte(0, 4);  // This should have been zero
    byte_stuffer_recv_byte(0, 0);
    byte_stuffer_recv_byte(0, 3);
    byte_stuffer_recv_byte(0, 5);
    byte_stuffer_recv_byte(0, 7);
    byte_stuffer_recv_byte(0, 0);
}

TEST_F(ByteStuffer, receives_a_valid_frame_with_over254_non_zeroes_and_then_end_of_frame) {
    uint8_t expected[254];
    int     i;
    for (i = 0; i < 254; i++) {
        expected[i] = i + 1;
    }
    EXPECT_CALL(*this, validator_recv_frame(_, _, _)).With(Args<1, 2>(ElementsAreArray(expected)));
    byte_stuffer_recv_byte(0, 0xFF);
    for (i = 0; i < 254; i++) {
        byte_stuffer_recv_byte(0, i + 1);
    }
    byte_stuffer_recv_byte(0, 0);
}

TEST_F(ByteStuffer, receives_a_valid_frame_with_over254_non_zeroes_next_byte_is_non_zero) {
    uint8_t expected[255];
    int     i;
    for (i = 0; i < 254; i++) {
        expected[i] = i + 1;
    }
    expected[254] = 7;
    EXPECT_CALL(*this, validator_recv_frame(_, _, _)).With(Args<1, 2>(ElementsAreArray(expected)));
    byte_stuffer_recv_byte(0, 0xFF);
    for (i = 0; i < 254; i++) {
        byte_stuffer_recv_byte(0, i + 1);
    }
    byte_stuffer_recv_byte(0, 2);
    byte_stuffer_recv_byte(0, 7);
    byte_stuffer_recv_byte(0, 0);
}

TEST_F(ByteStuffer, receives_a_valid_frame_with_over254_non_zeroes_next_byte_is_zero) {
    uint8_t expected[255];
    int     i;
    for (i = 0; i < 254; i++) {
        expected[i] = i + 1;
    }
    expected[254] = 0;
    EXPECT_CALL(*this, validator_recv_frame(_, _, _)).With(Args<1, 2>(ElementsAreArray(expected)));
    byte_stuffer_recv_byte(0, 0xFF);
    for (i = 0; i < 254; i++) {
        byte_stuffer_recv_byte(0, i + 1);
    }
    byte_stuffer_recv_byte(0, 1);
    byte_stuffer_recv_byte(0, 1);
    byte_stuffer_recv_byte(0, 0);
}

TEST_F(ByteStuffer, receives_two_long_frames_and_some_more) {
    uint8_t expected[515];
    int     i;
    int     j;
    for (j = 0; j < 2; j++) {
        for (i = 0; i < 254; i++) {
            expected[i + 254 * j] = i + 1;
        }
    }
    for (i = 0; i < 7; i++) {
        expected[254 * 2 + i] = i + 1;
    }
    EXPECT_CALL(*this, validator_recv_frame(_, _, _)).With(Args<1, 2>(ElementsAreArray(expected)));
    byte_stuffer_recv_byte(0, 0xFF);
    for (i = 0; i < 254; i++) {
        byte_stuffer_recv_byte(0, i + 1);
    }
    byte_stuffer_recv_byte(0, 0xFF);
    for (i = 0; i < 254; i++) {
        byte_stuffer_recv_byte(0, i + 1);
    }
    byte_stuffer_recv_byte(0, 8);
    byte_stuffer_recv_byte(0, 1);
    byte_stuffer_recv_byte(0, 2);
    byte_stuffer_recv_byte(0, 3);
    byte_stuffer_recv_byte(0, 4);
    byte_stuffer_recv_byte(0, 5);
    byte_stuffer_recv_byte(0, 6);
    byte_stuffer_recv_byte(0, 7);
    byte_stuffer_recv_byte(0, 0);
}

TEST_F(ByteStuffer, receives_an_all_zeros_frame_that_is_maximum_size) {
    uint8_t expected[MAX_FRAME_SIZE] = {};
    EXPECT_CALL(*this, validator_recv_frame(_, _, _)).With(Args<1, 2>(ElementsAreArray(expected)));
    int i;
    byte_stuffer_recv_byte(0, 1);
    for (i = 0; i < MAX_FRAME_SIZE; i++) {
        byte_stuffer_recv_byte(0, 1);
    }
    byte_stuffer_recv_byte(0, 0);
}

TEST_F(ByteStuffer, doesnt_recv_a_frame_thats_too_long_all_zeroes) {
    uint8_t expected[1] = {0};
    EXPECT_CALL(*this, validator_recv_frame(_, _, _)).Times(0);
    int i;
    byte_stuffer_recv_byte(0, 1);
    for (i = 0; i < MAX_FRAME_SIZE; i++) {
        byte_stuffer_recv_byte(0, 1);
    }
    byte_stuffer_recv_byte(0, 1);
    byte_stuffer_recv_byte(0, 0);
}

TEST_F(ByteStuffer, received_frame_is_aborted_when_its_too_long) {
    uint8_t expected[1] = {1};
    EXPECT_CALL(*this, validator_recv_frame(_, _, _)).With(Args<1, 2>(ElementsAreArray(expected)));
    int i;
    byte_stuffer_recv_byte(0, 1);
    for (i = 0; i < MAX_FRAME_SIZE; i++) {
        byte_stuffer_recv_byte(0, 1);
    }
    byte_stuffer_recv_byte(0, 2);
    byte_stuffer_recv_byte(0, 1);
    byte_stuffer_recv_byte(0, 0);
}

TEST_F(ByteStuffer, does_nothing_when_sending_zero_size_frame) {
    EXPECT_EQ(sent_data.size(), 0);
    byte_stuffer_send_frame(0, NULL, 0);
}

TEST_F(ByteStuffer, send_one_byte_frame) {
    uint8_t data[] = {5};
    byte_stuffer_send_frame(1, data, 1);
    uint8_t expected[] = {2, 5, 0};
    EXPECT_THAT(sent_data, ElementsAreArray(expected));
}

TEST_F(ByteStuffer, sends_two_byte_frame) {
    uint8_t data[] = {5, 0x77};
    byte_stuffer_send_frame(0, data, 2);
    uint8_t expected[] = {3, 5, 0x77, 0};
    EXPECT_THAT(sent_data, ElementsAreArray(expected));
}

TEST_F(ByteStuffer, sends_one_byte_frame_with_zero) {
    uint8_t data[] = {0};
    byte_stuffer_send_frame(0, data, 1);
    uint8_t expected[] = {1, 1, 0};
    EXPECT_THAT(sent_data, ElementsAreArray(expected));
}

TEST_F(ByteStuffer, sends_two_byte_frame_starting_with_zero) {
    uint8_t data[] = {0, 9};
    byte_stuffer_send_frame(1, data, 2);
    uint8_t expected[] = {1, 2, 9, 0};
    EXPECT_THAT(sent_data, ElementsAreArray(expected));
}

TEST_F(ByteStuffer, sends_two_byte_frame_starting_with_non_zero) {
    uint8_t data[] = {9, 0};
    byte_stuffer_send_frame(1, data, 2);
    uint8_t expected[] = {2, 9, 1, 0};
    EXPECT_THAT(sent_data, ElementsAreArray(expected));
}

TEST_F(ByteStuffer, sends_three_byte_frame_zero_in_the_middle) {
    uint8_t data[] = {9, 0, 0x68};
    byte_stuffer_send_frame(0, data, 3);
    uint8_t expected[] = {2, 9, 2, 0x68, 0};
    EXPECT_THAT(sent_data, ElementsAreArray(expected));
}

TEST_F(ByteStuffer, sends_three_byte_frame_data_in_the_middle) {
    uint8_t data[] = {0, 0x55, 0};
    byte_stuffer_send_frame(0, data, 3);
    uint8_t expected[] = {1, 2, 0x55, 1, 0};
    EXPECT_THAT(sent_data, ElementsAreArray(expected));
}

TEST_F(ByteStuffer, sends_three_byte_frame_with_all_zeroes) {
    uint8_t data[] = {0, 0, 0};
    byte_stuffer_send_frame(0, data, 3);
    uint8_t expected[] = {1, 1, 1, 1, 0};
    EXPECT_THAT(sent_data, ElementsAreArray(expected));
}

TEST_F(ByteStuffer, sends_frame_with_254_non_zeroes) {
    uint8_t data[254];
    int     i;
    for (i = 0; i < 254; i++) {
        data[i] = i + 1;
    }
    byte_stuffer_send_frame(0, data, 254);
    uint8_t expected[256];
    expected[0] = 0xFF;
    for (i = 1; i < 255; i++) {
        expected[i] = i;
    }
    expected[255] = 0;
    EXPECT_THAT(sent_data, ElementsAreArray(expected));
}

TEST_F(ByteStuffer, sends_frame_with_255_non_zeroes) {
    uint8_t data[255];
    int     i;
    for (i = 0; i < 255; i++) {
        data[i] = i + 1;
    }
    byte_stuffer_send_frame(0, data, 255);
    uint8_t expected[258];
    expected[0] = 0xFF;
    for (i = 1; i < 255; i++) {
        expected[i] = i;
    }
    expected[255] = 2;
    expected[256] = 255;
    expected[257] = 0;
    EXPECT_THAT(sent_data, ElementsAreArray(expected));
}

TEST_F(ByteStuffer, sends_frame_with_254_non_zeroes_followed_by_zero) {
    uint8_t data[255];
    int     i;
    for (i = 0; i < 254; i++) {
        data[i] = i + 1;
    }
    data[254] = 0;
    byte_stuffer_send_frame(0, data, 255);
    uint8_t expected[258];
    expected[0] = 0xFF;
    for (i = 1; i < 255; i++) {
        expected[i] = i;
    }
    expected[255] = 1;
    expected[256] = 1;
    expected[257] = 0;
    EXPECT_THAT(sent_data, ElementsAreArray(expected));
}

TEST_F(ByteStuffer, sends_and_receives_full_roundtrip_small_packet) {
    uint8_t original_data[] = {1, 2, 3};
    byte_stuffer_send_frame(0, original_data, sizeof(original_data));
    EXPECT_CALL(*this, validator_recv_frame(_, _, _)).With(Args<1, 2>(ElementsAreArray(original_data)));
    int i;
    for (auto& d : sent_data) {
        byte_stuffer_recv_byte(1, d);
    }
}

TEST_F(ByteStuffer, sends_and_receives_full_roundtrip_small_packet_with_zeros) {
    uint8_t original_data[] = {1, 0, 3, 0, 0, 9};
    byte_stuffer_send_frame(1, original_data, sizeof(original_data));
    EXPECT_CALL(*this, validator_recv_frame(_, _, _)).With(Args<1, 2>(ElementsAreArray(original_data)));
    int i;
    for (auto& d : sent_data) {
        byte_stuffer_recv_byte(1, d);
    }
}

TEST_F(ByteStuffer, sends_and_receives_full_roundtrip_254_bytes) {
    uint8_t original_data[254];
    int     i;
    for (i = 0; i < 254; i++) {
        original_data[i] = i + 1;
    }
    byte_stuffer_send_frame(0, original_data, sizeof(original_data));
    EXPECT_CALL(*this, validator_recv_frame(_, _, _)).With(Args<1, 2>(ElementsAreArray(original_data)));
    for (auto& d : sent_data) {
        byte_stuffer_recv_byte(1, d);
    }
}

TEST_F(ByteStuffer, sends_and_receives_full_roundtrip_256_bytes) {
    uint8_t original_data[256];
    int     i;
    for (i = 0; i < 254; i++) {
        original_data[i] = i + 1;
    }
    original_data[254] = 22;
    original_data[255] = 23;
    byte_stuffer_send_frame(0, original_data, sizeof(original_data));
    EXPECT_CALL(*this, validator_recv_frame(_, _, _)).With(Args<1, 2>(ElementsAreArray(original_data)));
    for (auto& d : sent_data) {
        byte_stuffer_recv_byte(1, d);
    }
}

TEST_F(ByteStuffer, sends_and_receives_full_roundtrip_254_bytes_and_then_zero) {
    uint8_t original_data[255];
    int     i;
    for (i = 0; i < 254; i++) {
        original_data[i] = i + 1;
    }
    original_data[254] = 0;
    byte_stuffer_send_frame(0, original_data, sizeof(original_data));
    EXPECT_CALL(*this, validator_recv_frame(_, _, _)).With(Args<1, 2>(ElementsAreArray(original_data)));
    for (auto& d : sent_data) {
        byte_stuffer_recv_byte(1, d);
    }
}
