#include QMK_KEYBOARD_H
#include "ch.h"
#include "hal.h"
#include "serial_link/system/serial_link.h"
#ifdef VISUALIZER_ENABLE
#include "lcd_backlight.h"
#endif

void init_serial_link_hal(void) {
    PORTA->PCR[1] = PORTx_PCRn_PE | PORTx_PCRn_PS | PORTx_PCRn_PFE | PORTx_PCRn_MUX(2);
    PORTA->PCR[2] = PORTx_PCRn_DSE | PORTx_PCRn_SRE | PORTx_PCRn_MUX(2);
    PORTE->PCR[0] = PORTx_PCRn_PE | PORTx_PCRn_PS | PORTx_PCRn_PFE | PORTx_PCRn_MUX(3);
    PORTE->PCR[1] = PORTx_PCRn_DSE | PORTx_PCRn_SRE | PORTx_PCRn_MUX(3);
}

#define RED_PIN 1
#define GREEN_PIN 2
#define BLUE_PIN 3
#define CHANNEL_RED FTM0->CHANNEL[0]
#define CHANNEL_GREEN FTM0->CHANNEL[1]
#define CHANNEL_BLUE FTM0->CHANNEL[2]

#define RGB_PORT PORTC
#define RGB_PORT_GPIO GPIOC

// Base FTM clock selection (72 MHz system clock)
// @ 0xFFFF period, 72 MHz / (0xFFFF * 2) = Actual period
// Higher pre-scalar will use the most power (also look the best)
// Pre-scalar calculations
// 0 -      72 MHz -> 549 Hz
// 1 -      36 MHz -> 275 Hz
// 2 -      18 MHz -> 137 Hz
// 3 -       9 MHz ->  69 Hz (Slightly visible flicker)
// 4 -   4 500 kHz ->  34 Hz (Visible flickering)
// 5 -   2 250 kHz ->  17 Hz
// 6 -   1 125 kHz ->   9 Hz
// 7 - 562 500  Hz ->   4 Hz
// Using a higher pre-scalar without flicker is possible but FTM0_MOD will need to be reduced
// Which will reduce the brightness range
#define PRESCALAR_DEFINE 0
void lcd_backlight_hal_init(void) {
	// Setup Backlight
    SIM->SCGC6 |= SIM_SCGC6_FTM0;
    FTM0->CNT = 0; // Reset counter

	// PWM Period
	// 16-bit maximum
	FTM0->MOD = 0xFFFF;

	// Set FTM to PWM output - Edge Aligned, Low-true pulses
#define CNSC_MODE FTM_SC_CPWMS | FTM_SC_PS(4) | FTM_SC_CLKS(0)
	CHANNEL_RED.CnSC = CNSC_MODE;
	CHANNEL_GREEN.CnSC = CNSC_MODE;
	CHANNEL_BLUE.CnSC = CNSC_MODE;

	// System clock, /w prescalar setting
	FTM0->SC = FTM_SC_CLKS(1) | FTM_SC_PS(PRESCALAR_DEFINE);

	CHANNEL_RED.CnV = 0;
	CHANNEL_GREEN.CnV = 0;
	CHANNEL_BLUE.CnV = 0;

	RGB_PORT_GPIO->PDDR |= (1 << RED_PIN);
	RGB_PORT_GPIO->PDDR |= (1 << GREEN_PIN);
	RGB_PORT_GPIO->PDDR |= (1 << BLUE_PIN);

#define RGB_MODE PORTx_PCRn_SRE | PORTx_PCRn_DSE | PORTx_PCRn_MUX(4)
    RGB_PORT->PCR[RED_PIN] = RGB_MODE;
    RGB_PORT->PCR[GREEN_PIN] = RGB_MODE;
    RGB_PORT->PCR[BLUE_PIN] = RGB_MODE;
}

static uint16_t cie_lightness(uint16_t v) {
    // The CIE 1931 formula for lightness
    // Y = luminance (output) 0-1
    // L = lightness input 0 - 100

    // Y = (L* / 902.3)           if L* <= 8
    // Y = ((L* + 16) / 116)^3    if L* > 8

    float l =  100.0f * (v / 65535.0f);
    float y = 0.0f;
    if (l <= 8.0f) {
       y = l / 902.3;
    }
    else {
        y = ((l + 16.0f) / 116.0f);
        y = y * y * y;
        if (y > 1.0f) {
            y = 1.0f;
        }
    }
    return y * 65535.0f;
}

void lcd_backlight_hal_color(uint16_t r, uint16_t g, uint16_t b) {
	CHANNEL_RED.CnV = cie_lightness(r);
	CHANNEL_GREEN.CnV = cie_lightness(g);
	CHANNEL_BLUE.CnV = cie_lightness(b);
}

__attribute__ ((weak))
void matrix_init_user(void) {
}

__attribute__ ((weak))
void matrix_scan_user(void) {
}


void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up

	matrix_init_user();
	// The backlight always has to be initialized, otherwise it will stay lit
#ifndef VISUALIZER_ENABLE
	lcd_backlight_hal_init();
#endif
}

void matrix_scan_kb(void) {
	// put your looping keyboard code here
	// runs every cycle (a lot)

	matrix_scan_user();
}

bool is_keyboard_master(void) {
    return is_serial_link_master();
}

__attribute__ ((weak))
void ergodox_board_led_on(void){
}

__attribute__ ((weak))
void ergodox_right_led_1_on(void){
}

__attribute__ ((weak))
void ergodox_right_led_2_on(void){
}

__attribute__ ((weak))
void ergodox_right_led_3_on(void){
}

__attribute__ ((weak))
void ergodox_board_led_off(void){
}

__attribute__ ((weak))
void ergodox_right_led_1_off(void){
}

__attribute__ ((weak))
void ergodox_right_led_2_off(void){
}

__attribute__ ((weak))
void ergodox_right_led_3_off(void){
}

__attribute__ ((weak))
void ergodox_right_led_1_set(uint8_t n) {
}

__attribute__ ((weak))
void ergodox_right_led_2_set(uint8_t n) {
}

__attribute__ ((weak))
void ergodox_right_led_3_set(uint8_t n) {
}

#ifdef ONEHAND_ENABLE
__attribute__ ((weak))
const keypos_t hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
    {{0, 9}, {1, 9}, {2, 9}, {3, 9}, {4, 9}},
    {{0, 10}, {1, 10}, {2, 10}, {3, 10}, {4, 10}},
    {{0, 11}, {1, 11}, {2, 11}, {3, 11}, {4, 11}},
    {{0, 12}, {1, 12}, {2, 12}, {3, 12}, {4, 12}},
    {{0, 13}, {1, 13}, {2, 13}, {3, 13}, {4, 13}},
    {{0, 14}, {1, 14}, {2, 14}, {3, 14}, {4, 14}},
    {{0, 15}, {1, 15}, {2, 15}, {3, 15}, {4, 15}},
    {{0, 16}, {1, 16}, {2, 16}, {3, 16}, {4, 16}},
    {{0, 17}, {1, 17}, {2, 17}, {3, 17}, {4, 17}},
    {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}},
    {{0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}},
    {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}},
    {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}},
    {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}},
    {{0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}},
    {{0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}},
    {{0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}},
    {{0, 8}, {1, 8}, {2, 8}, {3, 8}, {4, 8}},
};
#endif
