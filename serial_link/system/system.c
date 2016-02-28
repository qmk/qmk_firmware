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
#include "report.h"
#include "host_driver.h"
#include "serial_link/system/system.h"
#include "serial_link/system/driver.h"
#include "hal.h"
#include "serial_link/protocol/byte_stuffer.h"
#include "serial_link/protocol/transport.h"
#include "serial_link/protocol/frame_router.h"
#include "matrix.h"
#include <stdbool.h>
#include "print.h"

static event_source_t new_data_event;
static bool serial_link_connected;

static uint8_t keyboard_leds(void);
static void send_keyboard(report_keyboard_t *report);
static void send_mouse(report_mouse_t *report);
static void send_system(uint16_t data);
static void send_consumer(uint16_t data);

host_driver_t serial_driver = {
  keyboard_leds,
  send_keyboard,
  send_mouse,
  send_system,
  send_consumer
};


// Slow speed for testing
static SerialConfig config = {
    .sc_speed = 38400
};

static uint32_t read_from_serial(SerialDriver* driver, uint8_t link) {
    const uint32_t buffer_size = 16;
    uint8_t buffer[buffer_size];
    uint32_t bytes_read = sdAsynchronousRead(driver, buffer, buffer_size);
    uint8_t* current = buffer;
    uint8_t* end = current + bytes_read;
    while(current < end) {
        byte_stuffer_recv_byte(link, *current);
        current++;
    }
    return bytes_read;
}

// TODO: Optimize the stack size, this is probably way too big
static THD_WORKING_AREA(serialThreadStack, 1024);
static THD_FUNCTION(serialThread, arg) {
    (void)arg;
    event_listener_t new_data_listener;
    event_listener_t sd1_listener;
    event_listener_t sd2_listener;
    chEvtRegister(&new_data_event, &new_data_listener, 0);
    chEvtRegisterMaskWithFlags(chnGetEventSource(&SD1),
        &sd1_listener,
        EVENT_MASK(1),
        CHN_INPUT_AVAILABLE);
    chEvtRegisterMaskWithFlags(chnGetEventSource(&SD2),
        &sd2_listener,
        EVENT_MASK(2),
        CHN_INPUT_AVAILABLE);
    bool need_wait = false;
    while(true) {
        if (need_wait) {
            chEvtWaitAnyTimeout(ALL_EVENTS, MS2ST(1000));
        }
        bool is_master = usbGetDriverStateI(&USBD1) == USB_ACTIVE;
        router_set_master(is_master);

        need_wait = true;
        need_wait &= read_from_serial(&SD2, UP_LINK) == 0;
        need_wait &= read_from_serial(&SD1, DOWN_LINK) == 0;
        update_transport();
    }
}

void send_data(uint8_t link, const uint8_t* data, uint16_t size) {
    if (link == DOWN_LINK) {
        sdWrite(&SD1, data, size);
    }
    else {
        sdWrite(&SD2, data, size);
    }
}

static systime_t last_update = 0;

typedef struct {
    matrix_row_t rows[MATRIX_ROWS];
} matrix_object_t;

static matrix_object_t last_matrix = {};

SLAVE_TO_MASTER_OBJECT(keyboard_matrix, matrix_object_t);
MASTER_TO_ALL_SLAVES_OBJECT(serial_link_connected, bool);

remote_object_t* test_remote_objects[] = {
    REMOTE_OBJECT(serial_link_connected),
    REMOTE_OBJECT(keyboard_matrix),
};

void init_serial_link(void) {
    serial_link_connected = false;
    init_serial_link_hal();
    init_transport(test_remote_objects, sizeof(test_remote_objects)/sizeof(remote_object_t*));
    init_byte_stuffer();
    sdStart(&SD1, &config);
    sdStart(&SD2, &config);
    chEvtObjectInit(&new_data_event);
    (void)chThdCreateStatic(serialThreadStack, sizeof(serialThreadStack),
                              LOWPRIO, serialThread, NULL);
}

void matrix_set_remote(matrix_row_t* rows, uint8_t index);

void serial_link_update(void) {
    systime_t current_time = chVTGetSystemTimeX();
    if (current_time - last_update > 1000) {
        *begin_write_serial_link_connected() = true;
        end_write_serial_link_connected();
        last_update = current_time;
    }

    if (read_serial_link_connected()) {
        serial_link_connected = true;
    }

    matrix_object_t matrix;
    bool changed = false;
    for(uint8_t i=0;i<MATRIX_ROWS;i++) {
        matrix.rows[i] = matrix_get_row(i);
        changed |= matrix.rows[i] != last_matrix.rows[i];
    }
    if (changed) {
        last_matrix = matrix;
        matrix_object_t* m = begin_write_keyboard_matrix();
        for(uint8_t i=0;i<MATRIX_ROWS;i++) {
            m->rows[i] = matrix.rows[i];
        }
        end_write_keyboard_matrix();
    }

    matrix_object_t* m = read_keyboard_matrix(0);
    if (m) {
        matrix_set_remote(m->rows, 0);
    }
}

void signal_data_written(void) {
    chEvtBroadcast(&new_data_event);
}

bool is_serial_link_connected(void) {
    return serial_link_connected;
}

host_driver_t* get_serial_link_driver(void) {
    return &serial_driver;
}

// NOTE: The driver does nothing, because the master handles everything
uint8_t keyboard_leds(void) {
    return 0;
}

void send_keyboard(report_keyboard_t *report) {
    (void)report;
}

void send_mouse(report_mouse_t *report) {
    (void)report;
}

void send_system(uint16_t data) {
    (void)data;
}

void send_consumer(uint16_t data) {
    (void)data;
}

