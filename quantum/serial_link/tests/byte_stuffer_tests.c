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

#include <cgreen/cgreen.h>
#include <cgreen/mocks.h>
#include "serial_link/protocol/byte_stuffer.h"
#include "serial_link/protocol/byte_stuffer.c"
#include "serial_link/protocol/frame_validator.h"
#include "serial_link/protocol/physical.h"

static uint8_t sent_data[MAX_FRAME_SIZE*2];
static uint16_t sent_data_size;

Describe(ByteStuffer);
BeforeEach(ByteStuffer) {
    init_byte_stuffer();
    sent_data_size = 0;
}
AfterEach(ByteStuffer) {}

void validator_recv_frame(uint8_t link, uint8_t* data, uint16_t size) {
    mock(data, size);
}

void send_data(uint8_t link, const uint8_t* data, uint16_t size) {
    memcpy(sent_data + sent_data_size, data, size);
    sent_data_size += size;
}

Ensure(ByteStuffer, receives_no_frame_for_a_single_zero_byte) {
    never_expect(validator_recv_frame);
    byte_stuffer_recv_byte(0, 0);
}

Ensure(ByteStuffer, receives_no_frame_for_a_single_FF_byte) {
    never_expect(validator_recv_frame);
    byte_stuffer_recv_byte(0, 0xFF);
}

Ensure(ByteStuffer, receives_no_frame_for_a_single_random_byte) {
    never_expect(validator_recv_frame);
    byte_stuffer_recv_byte(0, 0x4A);
}

Ensure(ByteStuffer, receives_no_frame_for_a_zero_length_frame) {
    never_expect(validator_recv_frame);
    byte_stuffer_recv_byte(0, 1);
    byte_stuffer_recv_byte(0, 0);
}

Ensure(ByteStuffer, receives_single_byte_valid_frame) {
    uint8_t expected[] = {0x37};
    expect(validator_recv_frame,
        when(size, is_equal_to(1)),
        when(data, is_equal_to_contents_of(expected, 1))
    );
    byte_stuffer_recv_byte(0, 2);
    byte_stuffer_recv_byte(0, 0x37);
    byte_stuffer_recv_byte(0, 0);
}

Ensure(ByteStuffer, receives_three_bytes_valid_frame) {
    uint8_t expected[] = {0x37, 0x99, 0xFF};
    expect(validator_recv_frame,
        when(size, is_equal_to(3)),
        when(data, is_equal_to_contents_of(expected, 3))
    );
    byte_stuffer_recv_byte(0, 4);
    byte_stuffer_recv_byte(0, 0x37);
    byte_stuffer_recv_byte(0, 0x99);
    byte_stuffer_recv_byte(0, 0xFF);
    byte_stuffer_recv_byte(0, 0);
}

Ensure(ByteStuffer, receives_single_zero_valid_frame) {
    uint8_t expected[] = {0};
    expect(validator_recv_frame,
        when(size, is_equal_to(1)),
        when(data, is_equal_to_contents_of(expected, 1))
    );
    byte_stuffer_recv_byte(0, 1);
    byte_stuffer_recv_byte(0, 1);
    byte_stuffer_recv_byte(0, 0);
}

Ensure(ByteStuffer, receives_valid_frame_with_zeroes) {
    uint8_t expected[] = {5, 0, 3, 0};
    expect(validator_recv_frame,
        when(size, is_equal_to(4)),
        when(data, is_equal_to_contents_of(expected, 4))
    );
    byte_stuffer_recv_byte(0, 2);
    byte_stuffer_recv_byte(0, 5);
    byte_stuffer_recv_byte(0, 2);
    byte_stuffer_recv_byte(0, 3);
    byte_stuffer_recv_byte(0, 1);
    byte_stuffer_recv_byte(0, 0);
}

Ensure(ByteStuffer, receives_two_valid_frames) {
    uint8_t expected1[] = {5, 0};
    uint8_t expected2[] = {3};
    expect(validator_recv_frame,
        when(size, is_equal_to(2)),
        when(data, is_equal_to_contents_of(expected1, 2))
    );
    expect(validator_recv_frame,
        when(size, is_equal_to(1)),
        when(data, is_equal_to_contents_of(expected2, 1))
    );
    byte_stuffer_recv_byte(1, 2);
    byte_stuffer_recv_byte(1, 5);
    byte_stuffer_recv_byte(1, 1);
    byte_stuffer_recv_byte(1, 0);
    byte_stuffer_recv_byte(1, 2);
    byte_stuffer_recv_byte(1, 3);
    byte_stuffer_recv_byte(1, 0);
}

Ensure(ByteStuffer, receives_valid_frame_after_unexpected_zero) {
    uint8_t expected[] = {5, 7};
    expect(validator_recv_frame,
        when(size, is_equal_to(2)),
        when(data, is_equal_to_contents_of(expected, 2))
    );
    byte_stuffer_recv_byte(1, 3);
    byte_stuffer_recv_byte(1, 1);
    byte_stuffer_recv_byte(1, 0);
    byte_stuffer_recv_byte(1, 3);
    byte_stuffer_recv_byte(1, 5);
    byte_stuffer_recv_byte(1, 7);
    byte_stuffer_recv_byte(1, 0);
}

Ensure(ByteStuffer, receives_valid_frame_after_unexpected_non_zero) {
    uint8_t expected[] = {5, 7};
    expect(validator_recv_frame,
        when(size, is_equal_to(2)),
        when(data, is_equal_to_contents_of(expected, 2))
    );
    byte_stuffer_recv_byte(0, 2);
    byte_stuffer_recv_byte(0, 9);
    byte_stuffer_recv_byte(0, 4); // This should have been zero
    byte_stuffer_recv_byte(0, 0);
    byte_stuffer_recv_byte(0, 3);
    byte_stuffer_recv_byte(0, 5);
    byte_stuffer_recv_byte(0, 7);
    byte_stuffer_recv_byte(0, 0);
}

Ensure(ByteStuffer, receives_a_valid_frame_with_over254_non_zeroes_and_then_end_of_frame) {
    uint8_t expected[254];
    int i;
    for (i=0;i<254;i++) {
        expected[i] = i + 1;
    }
    expect(validator_recv_frame,
        when(size, is_equal_to(254)),
        when(data, is_equal_to_contents_of(expected, 254))
    );
    byte_stuffer_recv_byte(0, 0xFF);
    for (i=0;i<254;i++) {
        byte_stuffer_recv_byte(0, i+1);
    }
    byte_stuffer_recv_byte(0, 0);
}

Ensure(ByteStuffer, receives_a_valid_frame_with_over254_non_zeroes_next_byte_is_non_zero) {
    uint8_t expected[255];
    int i;
    for (i=0;i<254;i++) {
        expected[i] = i + 1;
    }
    expected[254] = 7;
    expect(validator_recv_frame,
        when(size, is_equal_to(255)),
        when(data, is_equal_to_contents_of(expected, 255))
    );
    byte_stuffer_recv_byte(0, 0xFF);
    for (i=0;i<254;i++) {
        byte_stuffer_recv_byte(0, i+1);
    }
    byte_stuffer_recv_byte(0, 2);
    byte_stuffer_recv_byte(0, 7);
    byte_stuffer_recv_byte(0, 0);
}

Ensure(ByteStuffer, receives_a_valid_frame_with_over254_non_zeroes_next_byte_is_zero) {
    uint8_t expected[255];
    int i;
    for (i=0;i<254;i++) {
        expected[i] = i + 1;
    }
    expected[254] = 0;
    expect(validator_recv_frame,
        when(size, is_equal_to(255)),
        when(data, is_equal_to_contents_of(expected, 255))
    );
    byte_stuffer_recv_byte(0, 0xFF);
    for (i=0;i<254;i++) {
        byte_stuffer_recv_byte(0, i+1);
    }
    byte_stuffer_recv_byte(0, 1);
    byte_stuffer_recv_byte(0, 1);
    byte_stuffer_recv_byte(0, 0);
}

Ensure(ByteStuffer, receives_two_long_frames_and_some_more) {
    uint8_t expected[515];
    int i;
    int j;
    for (j=0;j<2;j++) {
        for (i=0;i<254;i++) {
            expected[i+254*j] = i + 1;
        }
    }
    for (i=0;i<7;i++) {
        expected[254*2+i] = i + 1;
    }
    expect(validator_recv_frame,
        when(size, is_equal_to(515)),
        when(data, is_equal_to_contents_of(expected, 510))
    );
    byte_stuffer_recv_byte(0, 0xFF);
    for (i=0;i<254;i++) {
        byte_stuffer_recv_byte(0, i+1);
    }
    byte_stuffer_recv_byte(0, 0xFF);
    for (i=0;i<254;i++) {
        byte_stuffer_recv_byte(0, i+1);
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

Ensure(ByteStuffer, receives_an_all_zeros_frame_that_is_maximum_size) {
    uint8_t expected[MAX_FRAME_SIZE] = {};
    expect(validator_recv_frame,
        when(size, is_equal_to(MAX_FRAME_SIZE)),
        when(data, is_equal_to_contents_of(expected, MAX_FRAME_SIZE))
    );
    int i;
    byte_stuffer_recv_byte(0, 1);
    for(i=0;i<MAX_FRAME_SIZE;i++) {
       byte_stuffer_recv_byte(0, 1);
    }
    byte_stuffer_recv_byte(0, 0);
}

Ensure(ByteStuffer, doesnt_recv_a_frame_thats_too_long_all_zeroes) {
    uint8_t expected[1] = {0};
    never_expect(validator_recv_frame);
    int i;
    byte_stuffer_recv_byte(0, 1);
    for(i=0;i<MAX_FRAME_SIZE;i++) {
       byte_stuffer_recv_byte(0, 1);
    }
    byte_stuffer_recv_byte(0, 1);
    byte_stuffer_recv_byte(0, 0);
}

Ensure(ByteStuffer, received_frame_is_aborted_when_its_too_long) {
    uint8_t expected[1] = {1};
    expect(validator_recv_frame,
        when(size, is_equal_to(1)),
        when(data, is_equal_to_contents_of(expected, 1))
    );
    int i;
    byte_stuffer_recv_byte(0, 1);
    for(i=0;i<MAX_FRAME_SIZE;i++) {
       byte_stuffer_recv_byte(0, 1);
    }
    byte_stuffer_recv_byte(0, 2);
    byte_stuffer_recv_byte(0, 1);
    byte_stuffer_recv_byte(0, 0);
}

Ensure(ByteStuffer, does_nothing_when_sending_zero_size_frame) {
    assert_that(sent_data_size, is_equal_to(0));
    byte_stuffer_send_frame(0, NULL, 0);
}

Ensure(ByteStuffer, send_one_byte_frame) {
    uint8_t data[] = {5};
    byte_stuffer_send_frame(1, data, 1);
    uint8_t expected[] = {2, 5, 0};
    assert_that(sent_data_size, is_equal_to(sizeof(expected)));
    assert_that(sent_data, is_equal_to_contents_of(expected, sizeof(expected)));
}

Ensure(ByteStuffer, sends_two_byte_frame) {
    uint8_t data[] = {5, 0x77};
    byte_stuffer_send_frame(0, data, 2);
    uint8_t expected[] = {3, 5, 0x77, 0};
    assert_that(sent_data_size, is_equal_to(sizeof(expected)));
    assert_that(sent_data, is_equal_to_contents_of(expected, sizeof(expected)));
}

Ensure(ByteStuffer, sends_one_byte_frame_with_zero) {
    uint8_t data[] = {0};
    byte_stuffer_send_frame(0, data, 1);
    uint8_t expected[] = {1, 1, 0};
    assert_that(sent_data_size, is_equal_to(sizeof(expected)));
    assert_that(sent_data, is_equal_to_contents_of(expected, sizeof(expected)));
}

Ensure(ByteStuffer, sends_two_byte_frame_starting_with_zero) {
    uint8_t data[] = {0, 9};
    byte_stuffer_send_frame(1, data, 2);
    uint8_t expected[] = {1, 2, 9, 0};
    assert_that(sent_data_size, is_equal_to(sizeof(expected)));
    assert_that(sent_data, is_equal_to_contents_of(expected, sizeof(expected)));
}

Ensure(ByteStuffer, sends_two_byte_frame_starting_with_non_zero) {
    uint8_t data[] = {9, 0};
    byte_stuffer_send_frame(1, data, 2);
    uint8_t expected[] = {2, 9, 1, 0};
    assert_that(sent_data_size, is_equal_to(sizeof(expected)));
    assert_that(sent_data, is_equal_to_contents_of(expected, sizeof(expected)));
}

Ensure(ByteStuffer, sends_three_byte_frame_zero_in_the_middle) {
    uint8_t data[] = {9, 0, 0x68};
    byte_stuffer_send_frame(0, data, 3);
    uint8_t expected[] = {2, 9, 2, 0x68, 0};
    assert_that(sent_data_size, is_equal_to(sizeof(expected)));
    assert_that(sent_data, is_equal_to_contents_of(expected, sizeof(expected)));
}

Ensure(ByteStuffer, sends_three_byte_frame_data_in_the_middle) {
    uint8_t data[] = {0, 0x55, 0};
    byte_stuffer_send_frame(0, data, 3);
    uint8_t expected[] = {1, 2, 0x55, 1, 0};
    assert_that(sent_data_size, is_equal_to(sizeof(expected)));
    assert_that(sent_data, is_equal_to_contents_of(expected, sizeof(expected)));
}

Ensure(ByteStuffer, sends_three_byte_frame_with_all_zeroes) {
    uint8_t data[] = {0, 0, 0};
    byte_stuffer_send_frame(0, data, 3);
    uint8_t expected[] = {1, 1, 1, 1, 0};
    assert_that(sent_data_size, is_equal_to(sizeof(expected)));
    assert_that(sent_data, is_equal_to_contents_of(expected, sizeof(expected)));
}

Ensure(ByteStuffer, sends_frame_with_254_non_zeroes) {
    uint8_t data[254];
    int i;
    for(i=0;i<254;i++) {
        data[i] = i + 1;
    }
    byte_stuffer_send_frame(0, data, 254);
    uint8_t expected[256];
    expected[0] = 0xFF;
    for(i=1;i<255;i++) {
        expected[i] = i;
    }
    expected[255] = 0;
    assert_that(sent_data_size, is_equal_to(sizeof(expected)));
    assert_that(sent_data, is_equal_to_contents_of(expected, sizeof(expected)));
}

Ensure(ByteStuffer, sends_frame_with_255_non_zeroes) {
    uint8_t data[255];
    int i;
    for(i=0;i<255;i++) {
        data[i] = i + 1;
    }
    byte_stuffer_send_frame(0, data, 255);
    uint8_t expected[258];
    expected[0] = 0xFF;
    for(i=1;i<255;i++) {
        expected[i] = i;
    }
    expected[255] = 2;
    expected[256] = 255;
    expected[257] = 0;
    assert_that(sent_data_size, is_equal_to(sizeof(expected)));
    assert_that(sent_data, is_equal_to_contents_of(expected, sizeof(expected)));
}

Ensure(ByteStuffer, sends_frame_with_254_non_zeroes_followed_by_zero) {
    uint8_t data[255];
    int i;
    for(i=0;i<254;i++) {
        data[i] = i + 1;
    }
    data[255] = 0;
    byte_stuffer_send_frame(0, data, 255);
    uint8_t expected[258];
    expected[0] = 0xFF;
    for(i=1;i<255;i++) {
        expected[i] = i;
    }
    expected[255] = 1;
    expected[256] = 1;
    expected[257] = 0;
    assert_that(sent_data_size, is_equal_to(sizeof(expected)));
    assert_that(sent_data, is_equal_to_contents_of(expected, sizeof(expected)));
}

Ensure(ByteStuffer, sends_and_receives_full_roundtrip_small_packet) {
    uint8_t original_data[] = { 1, 2, 3};
    byte_stuffer_send_frame(0, original_data, sizeof(original_data));
    expect(validator_recv_frame,
        when(size, is_equal_to(sizeof(original_data))),
        when(data, is_equal_to_contents_of(original_data, sizeof(original_data)))
    );
    int i;
    for(i=0;i<sent_data_size;i++) {
       byte_stuffer_recv_byte(1, sent_data[i]);
    }
}

Ensure(ByteStuffer, sends_and_receives_full_roundtrip_small_packet_with_zeros) {
    uint8_t original_data[] = { 1, 0, 3, 0, 0, 9};
    byte_stuffer_send_frame(1, original_data, sizeof(original_data));
    expect(validator_recv_frame,
        when(size, is_equal_to(sizeof(original_data))),
        when(data, is_equal_to_contents_of(original_data, sizeof(original_data)))
    );
    int i;
    for(i=0;i<sent_data_size;i++) {
       byte_stuffer_recv_byte(0, sent_data[i]);
    }
}

Ensure(ByteStuffer, sends_and_receives_full_roundtrip_254_bytes) {
    uint8_t original_data[254];
    int i;
    for(i=0;i<254;i++) {
        original_data[i] = i + 1;
    }
    byte_stuffer_send_frame(0, original_data, sizeof(original_data));
    expect(validator_recv_frame,
        when(size, is_equal_to(sizeof(original_data))),
        when(data, is_equal_to_contents_of(original_data, sizeof(original_data)))
    );
    for(i=0;i<sent_data_size;i++) {
       byte_stuffer_recv_byte(1, sent_data[i]);
    }
}

Ensure(ByteStuffer, sends_and_receives_full_roundtrip_256_bytes) {
    uint8_t original_data[256];
    int i;
    for(i=0;i<254;i++) {
        original_data[i] = i + 1;
    }
    original_data[254] = 22;
    original_data[255] = 23;
    byte_stuffer_send_frame(0, original_data, sizeof(original_data));
    expect(validator_recv_frame,
        when(size, is_equal_to(sizeof(original_data))),
        when(data, is_equal_to_contents_of(original_data, sizeof(original_data)))
    );
    for(i=0;i<sent_data_size;i++) {
       byte_stuffer_recv_byte(1, sent_data[i]);
    }
}

Ensure(ByteStuffer, sends_and_receives_full_roundtrip_254_bytes_and_then_zero) {
    uint8_t original_data[255];
    int i;
    for(i=0;i<254;i++) {
        original_data[i] = i + 1;
    }
    original_data[254] = 0;
    byte_stuffer_send_frame(0, original_data, sizeof(original_data));
    expect(validator_recv_frame,
        when(size, is_equal_to(sizeof(original_data))),
        when(data, is_equal_to_contents_of(original_data, sizeof(original_data)))
    );
    for(i=0;i<sent_data_size;i++) {
       byte_stuffer_recv_byte(1, sent_data[i]);
    }
}
