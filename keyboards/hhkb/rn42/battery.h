#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    FULL_CHARGED,
    CHARGING,
    DISCHARGING,
    LOW_VOLTAGE,
    UNKNOWN,
} battery_status_t;

typedef enum {
    LED_CHARGER = 0,
    LED_ON,
    LED_OFF,
    LED_TOGGLE,
} battery_led_t;

/* Battery API */
void battery_init(void);
void battery_led(battery_led_t val);
bool battery_charging(void);
uint16_t battery_voltage(void);
battery_status_t battery_status(void);

#define BATTERY_VOLTAGE_LOW_LIMIT       3500
#define BATTERY_VOLTAGE_LOW_RECOVERY    3700
// ADC offset:16, resolution:5mV
#define BATTERY_ADC_OFFSET              16
#define BATTERY_ADC_RESOLUTION          5
