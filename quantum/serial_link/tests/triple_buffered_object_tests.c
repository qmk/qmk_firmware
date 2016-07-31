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
#include "serial_link/protocol/triple_buffered_object.c"

typedef struct {
    uint8_t state;
    uint32_t buffer[3];
}test_object_t;

test_object_t test_object;

Describe(TripleBufferedObject);
BeforeEach(TripleBufferedObject) {
    triple_buffer_init((triple_buffer_object_t*)&test_object);
}
AfterEach(TripleBufferedObject) {}


Ensure(TripleBufferedObject, writes_and_reads_object) {
    *triple_buffer_begin_write(&test_object) = 0x3456ABCC;
    triple_buffer_end_write(&test_object);
    assert_that(*triple_buffer_read(&test_object), is_equal_to(0x3456ABCC));
}

Ensure(TripleBufferedObject, does_not_read_empty) {
    assert_that(triple_buffer_read(&test_object), is_equal_to(NULL));
}

Ensure(TripleBufferedObject, writes_twice_and_reads_object) {
    *triple_buffer_begin_write(&test_object) = 0x3456ABCC;
    triple_buffer_end_write(&test_object);
    *triple_buffer_begin_write(&test_object) = 0x44778899;
    triple_buffer_end_write(&test_object);
    assert_that(*triple_buffer_read(&test_object), is_equal_to(0x44778899));
}

Ensure(TripleBufferedObject, performs_another_write_in_the_middle_of_read) {
    *triple_buffer_begin_write(&test_object) = 1;
    triple_buffer_end_write(&test_object);
    uint32_t* read = triple_buffer_read(&test_object);
    *triple_buffer_begin_write(&test_object) = 2;
    triple_buffer_end_write(&test_object);
    assert_that(*read, is_equal_to(1));
    assert_that(*triple_buffer_read(&test_object), is_equal_to(2));
    assert_that(triple_buffer_read(&test_object), is_equal_to(NULL));
}

Ensure(TripleBufferedObject, performs_two_writes_in_the_middle_of_read) {
    *triple_buffer_begin_write(&test_object) = 1;
    triple_buffer_end_write(&test_object);
    uint32_t* read = triple_buffer_read(&test_object);
    *triple_buffer_begin_write(&test_object) = 2;
    triple_buffer_end_write(&test_object);
    *triple_buffer_begin_write(&test_object) = 3;
    triple_buffer_end_write(&test_object);
    assert_that(*read, is_equal_to(1));
    assert_that(*triple_buffer_read(&test_object), is_equal_to(3));
    assert_that(triple_buffer_read(&test_object), is_equal_to(NULL));
}
