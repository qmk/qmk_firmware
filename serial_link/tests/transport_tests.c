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
#include "protocol/transport.c"

typedef struct {
    uint32_t test;
} test_object1_t;

typedef struct {
    uint32_t test1;
    uint32_t test2;
} test_object2_t;

MASTER_REMOTE_OBJECT(0, test_object1_t);
SLAVE_REMOTE_OBJECT(1, test_object1_t);
MASTER_REMOTE_OBJECT(2, test_object2_t);
SLAVE_REMOTE_OBJECT(3, test_object2_t);

// We want
// master -> slave = 1 local(target all), 1 remote object
// slave -> master = 1 local(target 0), multiple remote objects
// master -> single slave (multiple local, target id), 1 remote object

remote_object_t* remote_objects[] = {
    REMOTE_OBJECT(0),
    REMOTE_OBJECT(1),
    REMOTE_OBJECT(2),
    REMOTE_OBJECT(3),
};

Describe(Transport);
BeforeEach(Transport) {
    init_transport();
}
AfterEach(Transport) {}

Ensure(Transport, packet_number_is_sequential) {
    assert_that(transport_send_frame(0, NULL, 0), is_equal_to(1));
    assert_that(transport_send_frame(0, NULL, 0), is_equal_to(2));
    // It doesn't matter if the destination changes
    assert_that(transport_send_frame(1, NULL, 0), is_equal_to(3));
}
