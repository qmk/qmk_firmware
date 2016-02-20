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
#include "protocol/triple_buffered_object.c"

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
    uint32_t src = 0x3456ABCC;
    uint32_t dst;
    triple_buffer_write(4, (triple_buffer_object_t*)&test_object, &src);
    triple_buffer_read(4, (triple_buffer_object_t*)&test_object, &dst);
    assert_that(dst, is_equal_to(src));
}

Ensure(TripleBufferedObject, does_not_read_empty) {
    uint32_t dst;
    bool res = triple_buffer_read(4, (triple_buffer_object_t*)&test_object, &dst);
    assert_that(res, is_equal_to(false));
}

Ensure(TripleBufferedObject, writes_and_reads_object_decomposed) {
    uint32_t src = 0x3456ABCC;
    uint32_t dst;
    triple_buffer_write(4, (triple_buffer_object_t*)&test_object, &src);
    triple_buffer_begin_read(4, (triple_buffer_object_t*)&test_object);
    triple_buffer_actual_read(4, (triple_buffer_object_t*)&test_object, &dst);
    triple_buffer_end_read(4, (triple_buffer_object_t*)&test_object);
    assert_that(dst, is_equal_to(src));
}

Ensure(TripleBufferedObject, writes_twice_and_reads_object) {
    uint32_t src = 0x3456ABCC;
    uint32_t dst;
    triple_buffer_write(4, (triple_buffer_object_t*)&test_object, &src);
    src = 0x44778899;
    triple_buffer_write(4, (triple_buffer_object_t*)&test_object, &src);
    triple_buffer_read(4, (triple_buffer_object_t*)&test_object, &dst);
    assert_that(dst, is_equal_to(src));
}

Ensure(TripleBufferedObject, performs_another_write_in_the_middle_of_read) {
    uint32_t src = 1;
    uint32_t dst;
    triple_buffer_write(4, (triple_buffer_object_t*)&test_object, &src);
    src = 2;
    triple_buffer_begin_read(4, (triple_buffer_object_t*)&test_object);
    triple_buffer_write(4, (triple_buffer_object_t*)&test_object, &src);
    triple_buffer_actual_read(4, (triple_buffer_object_t*)&test_object, &dst);
    triple_buffer_end_read(4, (triple_buffer_object_t*)&test_object);
    assert_that(dst, is_equal_to(1));
    triple_buffer_read(4, (triple_buffer_object_t*)&test_object, &dst);
    assert_that(dst, is_equal_to(2));
    assert_that(triple_buffer_read(4, (triple_buffer_object_t*)&test_object, &dst), is_equal_to(false));
}

Ensure(TripleBufferedObject, performs_two_writes_in_the_middle_of_read) {
    uint32_t src = 1;
    uint32_t dst;
    triple_buffer_write(4, (triple_buffer_object_t*)&test_object, &src);
    triple_buffer_begin_read(4, (triple_buffer_object_t*)&test_object);
    src = 2;
    triple_buffer_write(4, (triple_buffer_object_t*)&test_object, &src);
    src = 3;
    triple_buffer_write(4, (triple_buffer_object_t*)&test_object, &src);
    triple_buffer_actual_read(4, (triple_buffer_object_t*)&test_object, &dst);
    triple_buffer_end_read(4, (triple_buffer_object_t*)&test_object);
    assert_that(dst, is_equal_to(1));
    triple_buffer_read(4, (triple_buffer_object_t*)&test_object, &dst);
    assert_that(dst, is_equal_to(3));
    assert_that(triple_buffer_read(4, (triple_buffer_object_t*)&test_object, &dst), is_equal_to(false));
}
