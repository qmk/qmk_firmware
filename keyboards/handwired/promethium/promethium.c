#include "promethium.h"
#include "analog.h"
#include "timer.h"
#include "matrix.h"
#include "musical_notes.h"
#include "adafruit_ble.h"

float fauxclicky_pressed_note[2] = MUSICAL_NOTE(_A4, 0.0625);
float fauxclicky_released_note[2] = MUSICAL_NOTE(_A4, 0.0625);
float fauxclicky_beep_note[2] = MUSICAL_NOTE(_C6, 0.25);

// cubic fit {3.3, 0}, {3.5, 2.9}, {3.6, 5}, {3.7, 8.6}, {3.8, 36},  {3.9, 62}, {4.0, 73}, {4.05, 83}, {4.1, 89}, {4.15, 94}, {4.2, 100}

uint8_t battery_level(void) {
    float voltage = adafruit_ble_read_battery_voltage() * 2 * 3.3 / 1024;
    if (voltage < MIN_VOLTAGE) return 0;
    if (voltage > MAX_VOLTAGE) return 255;
    return (voltage - MIN_VOLTAGE) / (MAX_VOLTAGE - MIN_VOLTAGE) * 255;
}

__attribute__ ((weak))
void battery_poll(uint8_t level) {
}

void matrix_init_kb(void) {
	matrix_init_user();
}

void matrix_scan_kb(void) {
    static uint16_t counter = BATTERY_POLL;
    counter++;

    if (counter > BATTERY_POLL) {
        counter = 0;
        battery_poll(battery_level());
    }

    matrix_scan_user();
}

void led_set_kb(uint8_t usb_led) {
    led_set_user(usb_led);
}

__attribute__ ((weak))
void led_set_user(uint8_t usb_led) {
}

