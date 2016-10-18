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

#include "serial_link/protocol/frame_router.h"
#include "serial_link/protocol/transport.h"
#include "serial_link/protocol/frame_validator.h"

static bool is_master;

void router_set_master(bool master) {
   is_master = master;
}

void route_incoming_frame(uint8_t link, uint8_t* data, uint16_t size){
    if (is_master) {
        if (link == DOWN_LINK) {
            transport_recv_frame(data[size-1], data, size - 1);
        }
    }
    else {
        if (link == UP_LINK) {
            if (data[size-1] & 1) {
                transport_recv_frame(0, data, size - 1);
            }
            data[size-1] >>= 1;
            validator_send_frame(DOWN_LINK, data, size);
        }
        else {
            data[size-1]++;
            validator_send_frame(UP_LINK, data, size);
        }
    }
}

void router_send_frame(uint8_t destination, uint8_t* data, uint16_t size) {
    if (destination == 0) {
        if (!is_master) {
            data[size] = 1;
            validator_send_frame(UP_LINK, data, size + 1);
        }
    }
    else {
        if (is_master) {
            data[size] = destination;
            validator_send_frame(DOWN_LINK, data, size + 1);
        }
    }
}
