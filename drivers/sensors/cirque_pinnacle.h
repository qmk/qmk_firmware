// Copyright (c) 2018 Cirque Corp. Restrictions apply. See: www.cirque.com/sw-license

#pragma once

#include "cirque_pinnacle_regdefs.h"
#include <stdint.h>
#include <stdbool.h>
#include "pointing_device_internal.h"
#include "pointing_device.h"

#define CIRQUE_PINNACLE_TIMEOUT 20

typedef enum { CIRQUE_PINNACLE_RELATIVE_MODE, CIRQUE_PINNACLE_ABSOLUTE_MODE } cirque_position_mode;
typedef enum { CIRQUE_NO_TAP, CIRQUE_SINGLE_TAP, CIRQUE_DOUBLE_TAP } cirque_taps_enable;

typedef enum {
    attenuate_1x = CIRQUE_EXTREG__TRACK_ADCCONFIG__ADC_ATTENUATE_1X,
    attenuate_2x = CIRQUE_EXTREG__TRACK_ADCCONFIG__ADC_ATTENUATE_2X,
    attenuate_3x = CIRQUE_EXTREG__TRACK_ADCCONFIG__ADC_ATTENUATE_3X,
    attenuate_4x = CIRQUE_EXTREG__TRACK_ADCCONFIG__ADC_ATTENUATE_4X,
} cirque_attenuation;
typedef struct {
    cirque_position_mode position_mode; // absolute
    cirque_attenuation   attenuation;
    bool                 curved_overlay;
    uint8_t              diameter_mm;   // 40
    uint16_t             default_scale; // 1024
    bool                 scroll_enable; // absolute = circular scroll, relative - side scroll
    cirque_taps_enable   taps;
    const void*          ranges;
} cirque_init_config_t;

typedef struct {
    uint16_t x_lower; // 127
    uint16_t x_upper; // 1919
    uint16_t y_lower; // 63
    uint16_t y_upper; // 1471
    uint16_t x_range; // upper-lower
    uint16_t y_range; // upper-lower
} cirque_ranges_absolute_t;

typedef struct {
    uint16_t x_range; // 56
    uint16_t y_range; // 256
} cirque_ranges_relative_t;

#if defined(POINTING_DEVICE_DRIVER_CIRQUE_PINNACLE_I2C)
#    include "i2c_master.h"
// Cirque's 7-bit I2C Slave Address
#    ifndef CIRQUE_PINNACLE_ADDR
#        define CIRQUE_PINNACLE_ADDR 0x2A
#    endif
#endif

#if defined(POINTING_DEVICE_DRIVER_CIRQUE_PINNACLE_SPI)
#    include "spi_master.h"
#    ifndef CIRQUE_PINNACLE_CLOCK_SPEED
#        define CIRQUE_PINNACLE_CLOCK_SPEED 10000000
#    endif
#    ifndef CIRQUE_PINNACLE_SPI_MODE
#        define CIRQUE_PINNACLE_SPI_MODE 1
#    endif
#    ifndef CIRQUE_PINNACLE_SPI_DIVISOR
#        ifdef __AVR__
#            define CIRQUE_PINNACLE_SPI_DIVISOR (F_CPU / CIRQUE_PINNACLE_CLOCK_SPEED)
#        else
#            define CIRQUE_PINNACLE_SPI_DIVISOR 64
#        endif
#    endif
#endif

#define DIVIDE_UNSIGNED_ROUND(numerator, denominator) (((numerator) + ((denominator) / 2)) / (denominator))
#define CIRQUE_PINNACLE_INCH_TO_PX(inch, mm) (DIVIDE_UNSIGNED_ROUND((inch) * (uint32_t)mm * 10, 254))
#define CIRQUE_PINNACLE_PX_TO_INCH(px, mm) (DIVIDE_UNSIGNED_ROUND((px) * (uint32_t)254, mm * 10))

typedef struct {
    bool     valid; // true if valid data was read, false if no data was ready
    uint16_t xValue;
    uint16_t yValue;
    uint16_t zValue;
    uint8_t  buttonFlags;
    bool     touchDown;
} cirque_absolute_data_t;

// Convenient way to store and access measurements
typedef struct {
    bool    valid; // true if valid data was read, false if no data was ready
    int16_t xDelta;
    int16_t yDelta;
    int8_t  wheelCount;
    uint8_t buttons;
} cirque_relative_data_t;

typedef struct {
    void (*read)(const void* config, uint8_t regaddr, uint8_t* data, uint8_t length);
    void (*write)(const void* config, uint8_t regaddr, uint8_t data);
} cirque_rap_t;

void           cirque_pinnacle_init(const cirque_rap_t* cirque_rap, const cirque_init_config_t* init_config, const void* comms_config);
void           cirque_pinnacle_calibrate(const cirque_rap_t* cirque_rap, const void* comms_config);
void           cirque_pinnacle_cursor_smoothing(const cirque_rap_t* cirque_rap, const void* comms_config, bool enable);
void*          cirque_pinnacle_read_data(const cirque_rap_t* cirque_rap, const cirque_init_config_t* init_config, const void* comms_config);
void           cirque_pinnacle_scale_data(const cirque_init_config_t* init_config, void* cirque_data, uint16_t xResolution, uint16_t yResolution);
uint16_t       cirque_pinnacle_get_scale(const void* comms_config);
void           cirque_pinnacle_set_scale(const void* comms_config, uint16_t scale);
report_mouse_t cirque_pinnacle_get_report(const cirque_rap_t* cirque_rap, const cirque_init_config_t* init_config, const void* comms_config);

void cirque_read_i2c(const void* config, uint8_t regaddr, uint8_t* data, uint8_t count);
void cirque_write_i2c(const void* config, uint8_t regaddr, uint8_t data);

void cirque_read_spi(const void* config, uint8_t regaddr, uint8_t* data, uint8_t count);
void cirque_write_spi(const void* config, uint8_t regaddr, uint8_t data);

void           cirque_pinnacle_init_i2c(const void* config);
report_mouse_t cirque_pinnacle_get_report_i2c(const void* config);

void           cirque_pinnacle_init_spi(const void* config);
report_mouse_t cirque_pinnacle_get_report_spi(const void* config);

const cirque_ranges_absolute_t cirque_ranges_position_default;
const cirque_ranges_relative_t cirque_ranges_relative_default;
const cirque_init_config_t     cirque_init_config_default;

const cirque_rap_t cirque_read_write_i2c;
const cirque_rap_t cirque_read_write_spi;

const pointing_device_driver_t     cirque_driver_i2c_default;
const pointing_device_i2c_config_t cirque_config_i2c_default;

const pointing_device_driver_t cirque_driver_spi_default;
#if defined(CIRQUE_PINNACLE_SPI_CS_PIN)
const pointing_device_spi_config_t cirque_config_spi_default;
#endif