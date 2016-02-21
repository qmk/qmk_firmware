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
#include "protocol/transport.c"

void signal_data_written(void) {
    mock();
}

typedef struct {
    uint32_t test;
} test_object1_t;

typedef struct {
    uint32_t test1;
    uint32_t test2;
} test_object2_t;

MASTER_TO_ALL_SLAVES_OBJECT(master_to_slave, test_object1_t);
MASTER_TO_SINGLE_SLAVE_OBJECT(master_to_single_slave, test_object1_t);
SLAVE_TO_MASTER_OBJECT(slave_to_master, test_object1_t);

remote_object_t* test_remote_objects[] = {
    REMOTE_OBJECT(master_to_slave),
    REMOTE_OBJECT(master_to_single_slave),
    REMOTE_OBJECT(slave_to_master),
};

Describe(Transport);
BeforeEach(Transport) {
    init_transport(remote_objects, sizeof(remote_objects) / sizeof(remote_object_t));
}
AfterEach(Transport) {}

Ensure(Transport, write_to_local_signals_an_event) {
    begin_write_master_to_slave();
    expect(signal_data_written);
    end_write_master_to_slave();
    begin_write_slave_to_master();
    expect(signal_data_written);
    end_write_slave_to_master();
    begin_write_master_to_single_slave(1);
    expect(signal_data_written);
    end_write_master_to_single_slave(1);
}
