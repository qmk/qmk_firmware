/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <https://github.com/XScorpion2> wrote this file.  As long as you retain this
 * notice you can do whatever you want with this stuff. If we meet some day, and
 * you think this stuff is worth it, you can buy me a beer in return. Ryan Caltabiano
 * ----------------------------------------------------------------------------
 */

#include "i2c_master.h"
#include "keyboard.h"
#include "touch_encoder.h"
#include "print.h"
#include "wait.h"
#include "timer.h"

// for memcpy
#include <string.h>
#include <transactions.h>

#define I2C_ADDRESS 0x1C
#define CALIBRATION_BIT 0x80
#define OVERFLOW_BIT 0x40
#define SLIDER_BIT 0x02

#ifndef TOUCH_UPDATE_INTERVAL
#   define TOUCH_UPDATE_INTERVAL 33
#endif

enum {  // QT2120 registers
    QT_CHIP_ID = 0,
    QT_FIRMWARE_VERSION,
    QT_DETECTION_STATUS,
    QT_KEY_STATUS,
    QT_SLIDER_POSITION = 5,
    QT_CALIBRATE,
    QT_RESET,
    QT_LP,
    QT_TTD,
    QT_ATD,
    QT_DI,
    QT_TRD,
    QT_DHT,
    QT_SLIDER_OPTION,
    QT_CHARDE_TIME,
    QT_KEY0_DTHR,
    QT_KEY1_DTHR,
    QT_KEY2_DTHR,
    QT_KEY3_DTHR,
    QT_KEY4_DTHR,
    QT_KEY5_DTHR,
    QT_KEY6_DTHR,
    QT_KEY7_DTHR,
    QT_KEY8_DTHR,
    QT_KEY9_DTHR,
    QT_KEY10_DTHR,
    QT_KEY11_DTHR,
    QT_KEY0_CTRL,
    QT_KEY1_CTRL,
    QT_KEY2_CTRL,
    QT_KEY3_CTRL,
    QT_KEY4_CTRL,
    QT_KEY5_CTRL,
    QT_KEY6_CTRL,
    QT_KEY7_CTRL,
    QT_KEY8_CTRL,
    QT_KEY9_CTRL,
    QT_KEY10_CTRL,
    QT_KEY11_CTRL,
    QT_KEY0_PULSE_SCALE,
    QT_KEY1_PULSE_SCALE,
    QT_KEY2_PULSE_SCALE,
    QT_KEY3_PULSE_SCALE,
    QT_KEY4_PULSE_SCALE,
    QT_KEY5_PULSE_SCALE,
    QT_KEY6_PULSE_SCALE,
    QT_KEY7_PULSE_SCALE,
    QT_KEY8_PULSE_SCALE,
    QT_KEY9_PULSE_SCALE,
    QT_KEY10_PULSE_SCALE,
    QT_KEY11_PULSE_SCALE,
    QT_KEY0_SIGNAL,
    QT_KEY1_SIGNAL     = 54,
    QT_KEY2_SIGNAL     = 56,
    QT_KEY3_SIGNAL     = 58,
    QT_KEY4_SIGNAL     = 60,
    QT_KEY5_SIGNAL     = 62,
    QT_KEY6_SIGNAL     = 64,
    QT_KEY7_SIGNAL     = 66,
    QT_KEY8_SIGNAL     = 68,
    QT_KEY9_SIGNAL     = 70,
    QT_KEY10_SIGNAL    = 72,
    QT_KEY11_SIGNAL    = 74,
    QT_KEY0_REFERENCE  = 76,
    QT_KEY1_REFERENCE  = 78,
    QT_KEY2_REFERENCE  = 80,
    QT_KEY3_REFERENCE  = 82,
    QT_KEY4_REFERENCE  = 84,
    QT_KEY5_REFERENCE  = 86,
    QT_KEY6_REFERENCE  = 88,
    QT_KEY7_REFERENCE  = 90,
    QT_KEY8_REFERENCE  = 92,
    QT_KEY9_REFERENCE  = 94,
    QT_KEY10_REFERENCE = 96,
    QT_KEY11_REFERENCE = 98,
};

bool     touch_initialized  = false;
bool     touch_disabled = false;
uint8_t  touch_handness = 0;
// touch_raw & touch_processed store the Detection Status, Key Status (x2), and Slider Position values
uint8_t  touch_raw[4]       = { 0 };
uint8_t  touch_processed[4] = { 0 };

uint16_t touch_timer        = 0;
uint16_t touch_update_timer = 0;

// For split transport only
typedef struct {
    uint8_t position;
    uint8_t taps;
} slave_touch_status_t;

bool touch_slave_init = false;
slave_touch_status_t touch_slave_state = { 0, 0 };

static bool write_register8(uint8_t address, uint8_t data) {
    i2c_status_t status = i2c_writeReg((I2C_ADDRESS << 1), address, &data, sizeof(data), I2C_TIMEOUT);
    if (status != I2C_STATUS_SUCCESS) {
        xprintf("write_register8 %d failed %d\n", address, status);
    }
    return status == I2C_STATUS_SUCCESS;
}

static bool read_register(uint8_t address, uint8_t* data, uint16_t length) {
    i2c_status_t status = i2c_readReg((I2C_ADDRESS << 1), address, data, length, I2C_TIMEOUT);
    if (status != I2C_STATUS_SUCCESS) {
        xprintf("read_register %d failed %d\n", address, status);
        return false;
    }
    return true;
}

void touch_encoder_init(void) {
    i2c_init();

    touch_handness = is_keyboard_left() ? 0 : 1;

    // Set QT to slider mode
    touch_initialized = write_register8(QT_SLIDER_OPTION, 0x80);
    touch_initialized &= write_register8(QT_TTD, 4);  // Toward Drift - 20 @ 3.2s
    touch_initialized &= write_register8(QT_ATD, 1);  // Away Drift - 5 @ 0.8s
    touch_initialized &= write_register8(QT_DI, 4);   // Detection Integrator - 4
    touch_initialized &= write_register8(QT_TRD, 0);  // Touch Recall - 48
    touch_encoder_calibrate();
}

__attribute__((weak)) bool touch_encoder_tapped_kb(uint8_t index, uint8_t section) { return touch_encoder_tapped_user(index, section); }
__attribute__((weak)) bool touch_encoder_update_kb(uint8_t index, bool clockwise) { return touch_encoder_update_user(index, clockwise); }

__attribute__((weak)) bool touch_encoder_tapped_user(uint8_t index, uint8_t section) { return true; }
__attribute__((weak)) bool touch_encoder_update_user(uint8_t index, bool clockwise) { return true; }

static void touch_encoder_update_tapped(void) {
    // Started touching, being counter for TOUCH_TERM
    if (touch_processed[0] & SLIDER_BIT) {
        touch_timer = timer_read() + TOUCH_TERM;
        return;
    }

    // Touch held too long, bail
    if (timer_expired(timer_read(), touch_timer)) return;

    uint8_t section = touch_processed[3] / (UINT8_MAX / TOUCH_SEGMENTS + 1);
    xprintf("tap %d %d\n", touch_handness, section);
    if (is_keyboard_master()) {
        if (!touch_disabled) {
            touch_encoder_tapped_kb(touch_handness, section);
        }
    }
    else {
        touch_slave_state.taps ^= (1 << section);
    }
}

static void touch_encoder_update_position_common(uint8_t* position, uint8_t raw, uint8_t index) {
    int8_t delta = (*position - raw) / TOUCH_RESOLUTION;
    bool clockwise = raw > *position;
    if (delta == 0) return;

    // Don't store raw directly, as we want to ensure any remainder is kept and used next time this is called
    *position -= delta * TOUCH_RESOLUTION;
    xprintf("pos %d %d\n", index, raw);
    //uint8_t u_delta   = delta < 0 ? -delta : delta;
    if (!touch_disabled) {
        //for (uint8_t i = 0; i < u_delta; i++)
            touch_encoder_update_kb(index, clockwise);
    }
}

static void touch_encoder_update_position(void) {
    // If the user touchs and moves enough, expire touch_timer faster and do encoder position logic instead
    if (!timer_expired(timer_read(), touch_timer)) {
        if ((uint8_t)(touch_raw[3] - touch_processed[3]) <= TOUCH_DEADZONE) return;
        touch_timer = timer_read();
    }

    if (is_keyboard_master()) {
        touch_encoder_update_position_common(&touch_processed[3], touch_raw[3], touch_handness);
    }
    else {
        touch_slave_state.position = touch_raw[3];
    }
}

void touch_encoder_update_slave(slave_touch_status_t slave_state) {
    if (!touch_slave_init) {
        touch_slave_state = slave_state;
        touch_slave_init = true;
        return;
    }

    if (touch_slave_state.position != slave_state.position) {
        // Did a new slide event start?
        uint8_t mask = (1 << 7);
        if ((touch_slave_state.taps & mask) != (slave_state.taps & mask)) {
            touch_slave_state.position = slave_state.position;
        }
        touch_encoder_update_position_common(&touch_slave_state.position, slave_state.position, !touch_handness);
    }

    if (touch_slave_state.taps != slave_state.taps) {
        if (!touch_disabled) {
            for (uint8_t section = 0; section < TOUCH_SEGMENTS; section++) {
                uint8_t mask = (1 << section);
                if ((touch_slave_state.taps & mask) != (slave_state.taps & mask)) {
                    xprintf("tap %d %d\n", !touch_handness, section);
                    touch_encoder_tapped_kb(!touch_handness, section);
                }
            }
        }
        touch_slave_state.taps = slave_state.taps;
    }
}

void touch_encoder_update(int8_t transaction_id) {
#if TOUCH_UPDATE_INTERVAL > 0
    if (!timer_expired(timer_read(), touch_update_timer)) return;
    touch_update_timer = timer_read() + TOUCH_UPDATE_INTERVAL;
#endif

    if (is_keyboard_master()) {
        slave_touch_status_t slave_state;
        if (transaction_rpc_exec(transaction_id, sizeof(bool), &touch_disabled, sizeof(slave_touch_status_t), &slave_state)) {
            if (memcmp(&touch_slave_state, &slave_state, sizeof(slave_touch_status_t)))
                touch_encoder_update_slave(slave_state);
        }
    }

    if (!touch_initialized) return;

    read_register(QT_DETECTION_STATUS, &touch_raw[0], sizeof(touch_raw));
    touch_processed[1] = touch_raw[1];
    touch_processed[2] = touch_raw[2];

    if (touch_raw[0] != touch_processed[0]) {
        uint8_t delta = touch_raw[0] ^ touch_processed[0];
        touch_processed[0]  = touch_raw[0];
        // When calibrating, normal sensor behavior is supended
        if (delta & CALIBRATION_BIT) {
            xprintf("calibration %d\n", touch_processed[0] >> 7 & 1);
        }
        if (delta & OVERFLOW_BIT) {
            xprintf("overflow %d\n", touch_processed[0] >> 6 & 1);
        }
        if (delta & SLIDER_BIT) {
            touch_processed[3] = touch_raw[3];
            if (!is_keyboard_master()) {
                touch_slave_state.position = touch_raw[3];
                touch_slave_state.taps ^= (1 << 7);
            }
            touch_encoder_update_tapped();
        }
    }

    if ((touch_raw[0] & SLIDER_BIT) && touch_processed[3] != touch_raw[3]) {
        touch_encoder_update_position();
    }
}

void touch_encoder_calibrate(void) {
    if (!touch_initialized) return;
    write_register8(QT_CALIBRATE, 0x01);
}

bool touch_encoder_is_calibrating(void) {
    return touch_raw[0] & CALIBRATION_BIT;
}

void touch_encoder_toggle(void) {
    touch_disabled = !touch_disabled;
}

bool touch_encoder_is_on(void) {
    return !touch_disabled;
}

void touch_encoder_slave_sync(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    touch_disabled = *(bool*)initiator2target_buffer;
    memcpy(target2initiator_buffer, &touch_slave_state, sizeof(slave_touch_status_t));
}
