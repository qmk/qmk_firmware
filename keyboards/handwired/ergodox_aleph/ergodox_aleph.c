#include QMK_KEYBOARD_H
#include <ch.h>
#include <hal.h>
#include "serial_link/system/serial_link.h"
#ifdef VISUALIZER_ENABLE
#include "lcd_backlight.h"
#endif

#ifdef WPM_ENABLE
#   include "serial_link/protocol/transport.h"
#   include "wpm.h"

MASTER_TO_ALL_SLAVES_OBJECT(current_wpm, uint8_t);
static remote_object_t* remote_objects[] = {
    REMOTE_OBJECT(current_wpm),
};
static uint8_t last_sent_wpm = 0;
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
#ifdef WPM_ENABLE
    add_remote_objects(remote_objects, sizeof(remote_objects) / sizeof(remote_object_t*));
#endif
}

void matrix_scan_kb(void) {
    // put your looping keyboard code here
    // runs every cycle (a lot)

#ifdef WPM_ENABLE
    if (is_serial_link_master()) {
        uint8_t current_wpm = get_current_wpm();
        if (current_wpm != last_sent_wpm) {
            *begin_write_current_wpm() = current_wpm;
            end_write_current_wpm();
            last_sent_wpm = current_wpm;
        }
    } else if (is_serial_link_connected()) {
        uint8_t* new_wpm = read_current_wpm();
        if (new_wpm) {
            set_current_wpm(*new_wpm);
        }
    }
#endif
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

#ifdef SWAP_HANDS_ENABLE
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

const is31_led g_is31_leds[DRIVER_LED_TOTAL] = {
   /* Refer to IS31 manual for these locations
    *   driver
    *   |  R location
    *   |  |       G location
    *   |  |       |       B location
    *   |  |       |       | */
       {0, G_2,    H_2,    I_2}, // LED1
       {0, D_2,    E_2,    F_2}, // LED2
       {0, A_2,    B_2,    C_2}, // LED3
       {0, J_1,    K_1,    L_1}, // LED4
       {0, G_1,    H_1,    I_1}, // LED5
       {0, D_1,    E_1,    F_1}, // LED6
       {0, A_1,    B_1,    C_1}, // LED7
       {0, G_4,    H_4,    I_4}, // LED8
       {0, D_4,    E_4,    F_4}, // LED9
       {0, A_4,    B_4,    C_4}, // LED10
       {0, J_3,    K_3,    L_3}, // LED11
       {0, G_3,    H_3,    I_3}, // LED12
       {0, D_3,    E_3,    F_3}, // LED13
       {0, A_3,    B_3,    C_3}, // LED14
       {0, D_6,    E_6,    F_6}, // LED15
       {0, A_6,    B_6,    C_6}, // LED16
       {0, J_5,    K_5,    L_5}, // LED17
       {0, G_5,    H_5,    I_5}, // LED18
       {0, D_5,    E_5,    F_5}, // LED19
       {0, A_5,    B_5,    C_5}, // LED20
       {0, D_9,    E_9,    F_9}, // LED21
       {0, A_9,    B_9,    C_9}, // LED22
       {0, G_8,    H_8,    I_8}, // LED23
       {0, D_8,    E_8,    F_8}, // LED24
       {0, A_8,    B_8,    C_8}, // LED25
       {0, J_7,    K_7,    L_7}, // LED26
       {0, G_7,    H_7,    I_7}, // LED27
       {0, D_7,    E_7,    F_7}, // LED28
       {0, A_7,    B_7,    C_7}, // LED29
       {0, G_9,    H_9,    I_9}, // LED30
       {0, G_11,   H_11,   I_11}, // LED31
       {0, D_11,   E_11,   F_11}, // LED32
       {0, A_11,   B_11,   C_11}, // LED33
       {0, J_11,   K_11,   L_11}, // LED34
       {0, J_10,   K_10,   L_10}, // LED35
       {0, G_10,   H_10,   I_10}, // LED36
       {0, D_10,   E_10,   F_10}, // LED37
       {0, A_10,   B_10,   C_10}  // LED38
};
