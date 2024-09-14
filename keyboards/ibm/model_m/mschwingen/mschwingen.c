/*
 * Copyright 2020 Michael Schwingen

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <util/delay.h>
#include "mschwingen.h"
#include "uart.h"
#include "print.h"
#include "sendchar.h"
#include "ws2812.h"
#include "sleep_led.h"

#ifdef UART_DEBUG
#    undef sendchar
static int8_t capture_sendchar(uint8_t c) {
    //  sendchar(c);
    uart_write(c);
    return 0;
}
#endif

static uint16_t blink_cycle_timer;
static bool     blink_state = false;
static uint8_t  isRecording = 0;

#ifdef KEYBOARD_ibm_model_m_mschwingen_led_ws2812
#    if RGBLIGHT_LED_COUNT < 3
#        error we need at least 3 RGB LEDs!
#    endif
static rgb_led_t led[RGBLIGHT_LED_COUNT] = {{255, 255, 255}, {255, 255, 255}, {255, 255, 255}};

#    define BRIGHT 32
#    define DIM 6

static const rgb_led_t black = {.r = 0, .g = 0, .b = 0};

static const __attribute__((unused)) rgb_led_t green  = {.r = 0, .g = BRIGHT, .b = 0};
static const __attribute__((unused)) rgb_led_t lgreen = {.r = 0, .g = DIM, .b = 0};

static const __attribute__((unused)) rgb_led_t red  = {.r = BRIGHT, .g = 0, .b = 0};
static const __attribute__((unused)) rgb_led_t lred = {.r = DIM, .g = 0, .b = 0};

static const __attribute__((unused)) rgb_led_t blue  = {.r = 0, .g = 0, .b = BRIGHT};
static const __attribute__((unused)) rgb_led_t lblue = {.r = 0, .g = 0, .b = DIM};

static const __attribute__((unused)) rgb_led_t turq  = {.r = 0, .g = BRIGHT, .b = BRIGHT};
static const __attribute__((unused)) rgb_led_t lturq = {.r = 0, .g = DIM, .b = DIM};

static const __attribute__((unused)) rgb_led_t white = {.r = BRIGHT, .g = BRIGHT, .b = BRIGHT};

static led_t   led_state;
static uint8_t layer;
static uint8_t default_layer;
#endif

// we need our own sleep_led_* implementation to get callbacks on USB
// suspend/resume in order to completely turn off WS2812 LEDs
static bool suspend_active = false;
void sleep_led_init(void) {}

void sleep_led_toggle(void) {}

void sleep_led_disable(void) {
    suspend_active = false;
    gpio_write_pin_high(MODELM_STATUS_LED);
}

void sleep_led_enable(void) {
    suspend_active = true;
    gpio_write_pin_low(MODELM_STATUS_LED);
#ifdef KEYBOARD_ibm_model_m_mschwingen_led_ws2812
    led[0] = black;
    led[1] = black;
    led[2] = black;
    ws2812_setleds(led, RGBLIGHT_LED_COUNT);
#endif
}

void keyboard_pre_init_kb(void) {
#ifdef KEYBOARD_ibm_model_m_mschwingen_led_ws2812
    ws2812_init();
    ws2812_setleds(led, RGBLIGHT_LED_COUNT);
#else
    /* Set status LEDs pins to output and Low (on) */
    gpio_set_pin_output(MODELM_LED_CAPSLOCK);
    gpio_set_pin_output(MODELM_LED_SCROLLOCK);
    gpio_set_pin_output(MODELM_LED_NUMLOCK);
    gpio_write_pin_low(MODELM_LED_CAPSLOCK);
    gpio_write_pin_low(MODELM_LED_SCROLLOCK);
    gpio_write_pin_low(MODELM_LED_NUMLOCK);
#endif
    gpio_set_pin_output(MODELM_STATUS_LED);
    gpio_write_pin_high(MODELM_STATUS_LED);
    _delay_ms(50);
#ifdef UART_DEBUG
    uart_init(115200);
    print_set_sendchar(capture_sendchar);
    uprintf("\r\nHello world!\r\n");
#endif

    gpio_set_pin_output(SR_LOAD_PIN);
    gpio_set_pin_output(SR_CLK_PIN);
    gpio_set_pin_output(SR_DOUT_PIN);  // MOSI - unused
    gpio_write_pin_low(SR_CLK_PIN);

    keyboard_pre_init_user();
}

#ifdef KEYBOARD_ibm_model_m_mschwingen_led_ws2812
static void led_update_rgb(void) {
    if (isRecording && blink_state) {
        led[0] = white;
    } else {
        switch (default_layer) {
            case 0:
                led[0] = led_state.num_lock ? blue : lblue;
                break;
            case 1:
                led[0] = led_state.num_lock ? green : black;
                break;
        }
    }

    led[1] = led_state.caps_lock ? green : black;

    switch (layer) {
        case 0:
        case 1:
        default:
            led[2] = led_state.scroll_lock ? green : black;
            break;
        case 2:
            led[2] = led_state.scroll_lock ? red : lred;
            break;
        case 3:
            led[2] = led_state.scroll_lock ? turq : lturq;
            break;
    }
    if (!suspend_active) {
	ws2812_setleds(led, RGBLIGHT_LED_COUNT);
    }
}

bool led_update_kb(led_t state) {
    dprintf("LED Update: %d %d %d", led_state.num_lock, led_state.caps_lock, led_state.scroll_lock);
    led_state = state;
    led_update_rgb();

    return true;
}

void update_layer_leds(void) {
    static uint8_t old_layer         = 255;
    static uint8_t old_default_layer = 255;

    layer         = get_highest_layer(layer_state);
    default_layer = get_highest_layer(default_layer_state);

    if (isRecording && timer_elapsed(blink_cycle_timer) > 150) {
        blink_state       = !blink_state;
        blink_cycle_timer = timer_read();
        old_layer         = 255;  // fallthrough next check
    }

    if (layer == old_layer && default_layer == old_default_layer) {
	return;
    }
    old_layer         = layer;
    old_default_layer = default_layer;
    dprintf("Layer change: %d %d", default_layer, layer);
    led_update_rgb();
}

/*****************************************************************************/
#else  // classic LEDs on GPIO
bool led_update_kb(led_t led_state) {
    dprintf("LED Update: %d %d %d", led_state.num_lock, led_state.caps_lock, led_state.scroll_lock);

    if (led_update_user(led_state)) {
        if (!isRecording) gpio_write_pin(MODELM_LED_NUMLOCK, !led_state.num_lock);
        gpio_write_pin(MODELM_LED_CAPSLOCK, !led_state.caps_lock);
        gpio_write_pin(MODELM_LED_SCROLLOCK, !led_state.scroll_lock);
    }
    return true;
}

void update_layer_leds(void) {
    if (isRecording && timer_elapsed(blink_cycle_timer) > 150) {
        blink_state = !blink_state;
        blink_cycle_timer = timer_read();
        gpio_write_pin(MODELM_LED_NUMLOCK, blink_state);
    }
}

#endif

bool dynamic_macro_record_start_kb(int8_t direction) {
    if (!dynamic_macro_record_start_user(direction)) {
        return false;
    }
    isRecording++;
    blink_cycle_timer = timer_read();
    return true;
}

bool dynamic_macro_record_end_kb(int8_t direction) {
    if (!dynamic_macro_record_end_user(direction)) {
        return false;
    }
    if (isRecording) isRecording--;
    return true;
}
