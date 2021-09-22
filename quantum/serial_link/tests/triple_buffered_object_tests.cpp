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
extern "C" {
#include "serial_link/protocol/triple_buffered_object.h"
}

struct test_object {
    uint8_t  state;
    uint32_t buffer[3];
};

test_object test_object;

class TripleBufferedObject : public testing::Test {
   public:
    TripleBufferedObject() { triple_buffer_init((triple_buffer_object_t*)&test_object); }
};

TEST_F(TripleBufferedObject, writes_and_reads_object) {
    *triple_buffer_begin_write(&test_object) = 0x3456ABCC;
    triple_buffer_end_write(&test_object);
    EXPECT_EQ(*triple_buffer_read(&test_object), 0x3456ABCC);
}

TEST_F(TripleBufferedObject, does_not_read_empty) { EXPECT_EQ(triple_buffer_read(&test_object), nullptr); }

TEST_F(TripleBufferedObject, writes_twice_and_reads_object) {
    *triple_buffer_begin_write(&test_object) = 0x3456ABCC;
    triple_buffer_end_write(&test_object);
    *triple_buffer_begin_write(&test_object) = 0x44778899;
    triple_buffer_end_write(&test_object);
    EXPECT_EQ(*triple_buffer_read(&test_object), 0x44778899);
}

TEST_F(TripleBufferedObject, performs_another_write_in_the_middle_of_read) {
    *triple_buffer_begin_write(&test_object) = 1;
    triple_buffer_end_write(&test_object);
    uint32_t* read                           = triple_buffer_read(&test_object);
    *triple_buffer_begin_write(&test_object) = 2;
    triple_buffer_end_write(&test_object);
    EXPECT_EQ(*read, 1);
    EXPECT_EQ(*triple_buffer_read(&test_object), 2);
    EXPECT_EQ(triple_buffer_read(&test_object), nullptr);
}

TEST_F(TripleBufferedObject, performs_two_writes_in_the_middle_of_read) {
    *triple_buffer_begin_write(&test_object) = 1;
    triple_buffer_end_write(&test_object);
    uint32_t* read                           = triple_buffer_read(&test_object);
    *triple_buffer_begin_write(&test_object) = 2;
    triple_buffer_end_write(&test_object);
    *triple_buffer_begin_write(&test_object) = 3;
    triple_buffer_end_write(&test_object);
    EXPECT_EQ(*read, 1);
    EXPECT_EQ(*triple_buffer_read(&test_object), 3);
    EXPECT_EQ(triple_buffer_read(&test_object), nullptr);
}
