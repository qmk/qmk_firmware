#include <string.h>
#include <stddef.h>

#include "config.h"
#include "matrix.h"
#include "quantum.h"

#define ROWS_PER_HAND (MATRIX_ROWS / 2)

#ifdef RGBLIGHT_ENABLE
#    include "rgblight.h"
#endif

#ifdef RGB_MATRIX_ENABLE
#    include "rgb_matrix.h"
#endif


#ifdef BACKLIGHT_ENABLE
#    include "backlight.h"
#endif

#ifdef ENCODER_ENABLE
#    include "encoder.h"
static pin_t encoders_pad[] = ENCODERS_PAD_A;
#    define NUMBER_OF_ENCODERS (sizeof(encoders_pad) / sizeof(pin_t))
#endif

#define RGB_SHOULD_SPLIT_MATRIX  (defined(RGB_MATRIX_SPLIT) && defined(RGB_MATRIX_ENABLE))
#define RGB_SHOULD_SPLIT_LIGHT (defined(RGBLIGHT_SPLIT) && defined(RGBLIGHT_ENABLE))
#define RGB_SHOULD_SPLIT (RGB_SHOULD_SPLIT_MATRIX || RGB_SHOULD_SPLIT_LIGHT)

#if defined(USE_I2C)

#    include "i2c_master.h"
#    include "i2c_slave.h"

typedef struct _I2C_slave_buffer_t {
    uint32_t sync_time;
#    ifdef SPLIT_TRANSPORT_MIRROR
    matrix_row_t mmatrix[ROWS_PER_HAND];
#    endif
    matrix_row_t smatrix[ROWS_PER_HAND];
    uint8_t      backlight_level;
#    ifdef RGB_SHOULD_SPLIT_MATRIX
    rgb_matrix_syncinfo_t rgb_sync;
#    elif RGB_SHOULD_SPLIT_LIGHT
    rgblight_syncinfo_t rgb_sync;
#    endif
#    ifdef ENCODER_ENABLE
    uint8_t encoder_state[NUMBER_OF_ENCODERS];
#    endif
#    ifdef WPM_ENABLE
    uint8_t current_wpm;
#    endif
} I2C_slave_buffer_t;

static I2C_slave_buffer_t *const i2c_buffer = (I2C_slave_buffer_t *)i2c_slave_reg;

#    define I2C_BACKLIGHT_START offsetof(I2C_slave_buffer_t, backlight_level)
#    define I2C_RGB_START offsetof(I2C_slave_buffer_t, rgb_sync)
#    define I2C_KEYMAP_MASTER_START offsetof(I2C_slave_buffer_t, mmatrix)
#    define I2C_KEYMAP_SLAVE_START offsetof(I2C_slave_buffer_t, smatrix)
#    define I2C_SYNC_TIME_START offsetof(I2C_slave_buffer_t, sync_time)
#    define I2C_ENCODER_START offsetof(I2C_slave_buffer_t, encoder_state)
#    define I2C_WPM_START offsetof(I2C_slave_buffer_t, current_wpm)

#    define TIMEOUT 100

#    ifndef SLAVE_I2C_ADDRESS
#        define SLAVE_I2C_ADDRESS 0x32
#    endif

// Get rows from other half over i2c
bool transport_master(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    i2c_readReg(SLAVE_I2C_ADDRESS, I2C_KEYMAP_SLAVE_START, (void *)slave_matrix, sizeof(i2c_buffer->smatrix), TIMEOUT);
#ifdef SPLIT_TRANSPORT_MIRROR
    i2c_writeReg(SLAVE_I2C_ADDRESS, I2C_KEYMAP_MASTER_START, (void *)master_matrix, sizeof(i2c_buffer->mmatrix), TIMEOUT);
#endif

    // write backlight info
#    ifdef BACKLIGHT_ENABLE
    uint8_t level = is_backlight_enabled() ? get_backlight_level() : 0;
    if (level != i2c_buffer->backlight_level) {
        if (i2c_writeReg(SLAVE_I2C_ADDRESS, I2C_BACKLIGHT_START, (void *)&level, sizeof(level), TIMEOUT) >= 0) {
            i2c_buffer->backlight_level = level;
        }
    }
#    endif

#    if RGB_SHOULD_SPLIT
    if (rgblight_get_change_flags()) {
#        if defined(RGB_MATRIX_ENABLE)
        rgb_matrix_syncinfo_t rgb_sync;
#        elif defined(RGBLIGHT_ENABLE)
        rgblight_syncinfo_t rgb_sync;
#        endif
        rgblight_get_syncinfo(&rgb_sync);
        if (i2c_writeReg(SLAVE_I2C_ADDRESS, I2C_RGB_START, (void *)&rgb_sync, sizeof(rgb_sync), TIMEOUT) >= 0) {
            rgblight_clear_change_flags();
        }
    }
#    endif

#    ifdef ENCODER_ENABLE
    i2c_readReg(SLAVE_I2C_ADDRESS, I2C_ENCODER_START, (void *)i2c_buffer->encoder_state, sizeof(i2c_buffer->encoder_state), TIMEOUT);
    encoder_update_raw(i2c_buffer->encoder_state);
#    endif

#    ifdef WPM_ENABLE
    uint8_t current_wpm = get_current_wpm();
    if (current_wpm != i2c_buffer->current_wpm) {
        if (i2c_writeReg(SLAVE_I2C_ADDRESS, I2C_WPM_START, (void *)&current_wpm, sizeof(current_wpm), TIMEOUT) >= 0) {
            i2c_buffer->current_wpm = current_wpm;
        }
    }
#    endif

    i2c_buffer->sync_time = timer_read32();
    sync_timer_update(i2c_buffer->sync_time);
    i2c_writeReg(SLAVE_I2C_ADDRESS, I2C_SYNC_TIME_START, (void *)&i2c_buffer->sync_time, sizeof(i2c_buffer->sync_time), TIMEOUT);
    return true;
}

void transport_slave(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    sync_timer_update(i2c_buffer->sync_time + 1);  // 1ms offset to account for transfer speed
    // Copy matrix to I2C buffer
    memcpy((void *)i2c_buffer->smatrix, (void *)slave_matrix, sizeof(i2c_buffer->smatrix));
#ifdef SPLIT_TRANSPORT_MIRROR
    memcpy((void*)master_matrix, (void *)i2c_buffer->mmatrix, sizeof(i2c_buffer->mmatrix));
#endif


// Read Backlight Info
#    ifdef BACKLIGHT_ENABLE
    backlight_set(i2c_buffer->backlight_level);
#    endif

#    if RGB_SPLIT 
    // Update the RGB with the new data
    rgblight_update_sync(&i2c_buffer->rgb_sync, false);
#    endif

#    ifdef ENCODER_ENABLE
    encoder_state_raw(i2c_buffer->encoder_state);
#    endif

#    ifdef WPM_ENABLE
    set_current_wpm(i2c_buffer->current_wpm);
#    endif
}

void transport_master_init(void) { i2c_init(); }

void transport_slave_init(void) { i2c_slave_init(SLAVE_I2C_ADDRESS); }

#else  // USE_SERIAL

#    include "serial.h"

typedef struct _Serial_s2m_buffer_t {
    // TODO: if MATRIX_COLS > 8 change to uint8_t packed_matrix[] for pack/unpack
    matrix_row_t smatrix[ROWS_PER_HAND];

#    ifdef ENCODER_ENABLE
    uint8_t      encoder_state[NUMBER_OF_ENCODERS];
#    endif

} Serial_s2m_buffer_t;

typedef struct _Serial_m2s_buffer_t {
#ifdef SPLIT_TRANSPORT_MIRROR
    matrix_row_t mmatrix[ROWS_PER_HAND];
#endif
    uint32_t sync_timer;
#    ifdef BACKLIGHT_ENABLE
    uint8_t backlight_level;
#    endif
#    ifdef WPM_ENABLE
    uint8_t current_wpm;
#    endif
} Serial_m2s_buffer_t;

#if RGB_SHOULD_SPLIT
// When MCUs on both sides drive their respective RGB LED chains,
// it is necessary to synchronize, so it is necessary to communicate RGB
// information. In that case, define RGBLIGHT_SPLIT with info on the number
// of LEDs on each half.
//
// Otherwise, if the master side MCU drives both sides RGB LED chains,
// there is no need to communicate.

typedef struct _Serial_rgb_t {
#if defined(RGB_MATRIX_ENABLE)
    rgb_matrix_syncinfo_t rgb_matrix_sync;
#elif defined(RGBLIGHT_ENABLE)
    rgblight_syncinfo_t rgblight_sync;
#endif
} Serial_rgb_t;

volatile Serial_rgb_t serial_rgb = {};
uint8_t volatile status_rgb           = 0;
#    endif

volatile Serial_s2m_buffer_t serial_s2m_buffer = {};
volatile Serial_m2s_buffer_t serial_m2s_buffer = {};
uint8_t volatile status0                       = 0;

enum serial_transaction_id {
    GET_SLAVE_MATRIX = 0,
#    if RGB_SHOULD_SPLIT
    PUT_RGB,
#    endif
};

SSTD_t transactions[] = {
    [GET_SLAVE_MATRIX] =
        {
            (uint8_t *)&status0,
            sizeof(serial_m2s_buffer),
            (uint8_t *)&serial_m2s_buffer,
            sizeof(serial_s2m_buffer),
            (uint8_t *)&serial_s2m_buffer,
        },
#    if RGB_SHOULD_SPLIT
    [PUT_RGB] =
        {
            (uint8_t *)&status_rgb, sizeof(serial_rgb), (uint8_t *)&serial_rgb, 0, NULL  // no slave to master transfer
        },
#    endif
};

void transport_master_init(void) { soft_serial_initiator_init(transactions, TID_LIMIT(transactions)); }

void transport_slave_init(void) { soft_serial_target_init(transactions, TID_LIMIT(transactions)); }

#    if RGB_SHOULD_SPLIT

// rgblight synchronization information communication.

void transport_rgb_master(void) {
    if (rgblight_get_change_flags()) {
#if defined(RGB_MATRIX_ENABLE)
        rgb_matrix_get_syncinfo((rgb_matrix_syncinfo_t *)&serial_rgb.rgb_matrix_sync);
#elif defined(RGBLIGHT_ENABLE)
        rgblight_get_syncinfo((rgblight_syncinfo_t *)&serial_rgb.rgblight_sync);
#endif
        if (soft_serial_transaction(PUT_RGB) == TRANSACTION_END) {
            rgblight_clear_change_flags();
        }
    }
}

void transport_rgb_slave(void) {
    if (status_rgb == TRANSACTION_ACCEPTED) {
#if defined(RGB_MATRIX_ENABLE)
        rgb_matrix_update_sync((rgb_matrix_syncinfo_t *)&serial_rgb.rgb_matrix_sync);
#elif defined(RGBLIGHT_ENABLE)
        rgblight_update_sync((rgblight_syncinfo_t *)&serial_rgb.rgblight_sync, false);
#endif
        status_rgb = TRANSACTION_END;
    }
}

#    else
#        define transport_rgb_master()
#        define transport_rgb_slave()
#    endif


bool transport_master(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    sync_timer_update(timer_read32());
#    ifndef SERIAL_USE_MULTI_TRANSACTION
    if (soft_serial_transaction() != TRANSACTION_END) {
        return false;
    }
#    else
    transport_rgb_master();

    if (soft_serial_transaction(GET_SLAVE_MATRIX) != TRANSACTION_END) {
        return false;
    }
#    endif

    // TODO:  if MATRIX_COLS > 8 change to unpack()
    for (int i = 0; i < ROWS_PER_HAND; ++i) {
        slave_matrix[i] = serial_s2m_buffer.smatrix[i];
#ifdef SPLIT_TRANSPORT_MIRROR
        serial_m2s_buffer.mmatrix[i] = master_matrix[i];
#endif
    }

#    ifdef BACKLIGHT_ENABLE
    // Write backlight level for slave to read
    serial_m2s_buffer.backlight_level = is_backlight_enabled() ? get_backlight_level() : 0;
#    endif

#    ifdef ENCODER_ENABLE
    encoder_update_raw((uint8_t *)serial_s2m_buffer.encoder_state);
#    endif

#    ifdef WPM_ENABLE
    // Write wpm to slave
    serial_m2s_buffer.current_wpm = get_current_wpm();
#    endif

    sync_timer_update(timer_read32());
    serial_m2s_buffer.sync_timer = sync_timer_read32();
    return true;
}

void transport_slave(matrix_row_t master_matrix[], matrix_row_t slave_matrix[]) {
    transport_rgb_slave();

    sync_timer_update(serial_m2s_buffer.sync_timer - 100);  // 2ms offset to account for transfer speed

    // TODO: if MATRIX_COLS > 8 change to pack()
    for (int i = 0; i < ROWS_PER_HAND; ++i) {
        serial_s2m_buffer.smatrix[i] = slave_matrix[i];
#ifdef SPLIT_TRANSPORT_MIRROR
        master_matrix[i] = serial_m2s_buffer.mmatrix[i];
#endif
    }
#    ifdef BACKLIGHT_ENABLE
    backlight_set(serial_m2s_buffer.backlight_level);
#    endif

#    ifdef ENCODER_ENABLE
    encoder_state_raw((uint8_t *)serial_s2m_buffer.encoder_state);
#    endif

#    ifdef WPM_ENABLE
    set_current_wpm(serial_m2s_buffer.current_wpm);
#    endif
}

#endif

#undef RGB_SHOULD_SPLIT
#undef RGB_SHOULD_SPLIT_MATRIX
#undef RGB_SHOULD_SPLIT_LIGHT