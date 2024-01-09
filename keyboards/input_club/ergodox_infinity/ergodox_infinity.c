#include "ergodox_infinity.h"
#include <ch.h>
#include <hal.h>
#include <string.h>
#include "eeconfig.h"

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
    FTM0->CNT = 0;  // Reset counter

    // PWM Period
    // 16-bit maximum
    FTM0->MOD = 0xFFFF;

    // Set FTM to PWM output - Edge Aligned, Low-true pulses
#define CNSC_MODE FTM_SC_CPWMS | FTM_SC_PS(4) | FTM_SC_CLKS(0)
    CHANNEL_RED.CnSC   = CNSC_MODE;
    CHANNEL_GREEN.CnSC = CNSC_MODE;
    CHANNEL_BLUE.CnSC  = CNSC_MODE;

    // System clock, /w prescalar setting
    FTM0->SC = FTM_SC_CLKS(1) | FTM_SC_PS(PRESCALAR_DEFINE);

    CHANNEL_RED.CnV   = 0;
    CHANNEL_GREEN.CnV = 0;
    CHANNEL_BLUE.CnV  = 0;

    RGB_PORT_GPIO->PDDR |= (1 << RED_PIN);
    RGB_PORT_GPIO->PDDR |= (1 << GREEN_PIN);
    RGB_PORT_GPIO->PDDR |= (1 << BLUE_PIN);

#define RGB_MODE PORTx_PCRn_SRE | PORTx_PCRn_DSE | PORTx_PCRn_MUX(4)
    RGB_PORT->PCR[RED_PIN]   = RGB_MODE;
    RGB_PORT->PCR[GREEN_PIN] = RGB_MODE;
    RGB_PORT->PCR[BLUE_PIN]  = RGB_MODE;
}

static uint16_t cie_lightness(uint16_t v) {
    // The CIE 1931 formula for lightness
    // Y = luminance (output) 0-1
    // L = lightness input 0 - 100

    // Y = (L* / 902.3)           if L* <= 8
    // Y = ((L* + 16) / 116)^3    if L* > 8

    float l = 100.0f * (v / 65535.0f);
    float y = 0.0f;
    if (l <= 8.0f) {
        y = l / 902.3;
    } else {
        y = ((l + 16.0f) / 116.0f);
        y = y * y * y;
        if (y > 1.0f) {
            y = 1.0f;
        }
    }
    return y * 65535.0f;
}

void ergodox_infinity_lcd_color(uint16_t r, uint16_t g, uint16_t b) {
    CHANNEL_RED.CnV   = cie_lightness(r);
    CHANNEL_GREEN.CnV = cie_lightness(g);
    CHANNEL_BLUE.CnV  = cie_lightness(b);
}

__attribute__ ((weak)) void matrix_init_user(void) {}

__attribute__ ((weak)) void matrix_scan_user(void) {}


void keyboard_pre_init_kb(void) {
#ifdef LED_MATRIX_ENABLE
    // Turn on LED controller
    setPinOutput(B16);
    writePinHigh(B16);
#endif
    // The backlight always has to be initialized, otherwise it will stay lit
    lcd_backlight_hal_init();
#ifdef ST7565_ENABLE
    ergodox_infinity_lcd_color(UINT16_MAX / 2, UINT16_MAX / 2, UINT16_MAX / 2);
#endif
    keyboard_pre_init_user();
}

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up

#ifdef LED_MATRIX_ENABLE
    /*
     * Since K20x is stuck with a 32 byte EEPROM (see tmk_core/common/chibios/eeprom_teensy.c),
     * and neither led_matrix_eeconfig.speed or .flags fit in this boundary, just force their values to default on boot.
     */
    led_matrix_set_speed(LED_MATRIX_DEFAULT_SPD);
    led_matrix_set_flags(LED_FLAG_ALL);
#endif

    matrix_init_user();
}

__attribute__ ((weak)) void ergodox_board_led_on(void) {}

__attribute__ ((weak)) void ergodox_right_led_1_on(void) {}

__attribute__ ((weak)) void ergodox_right_led_2_on(void) {}

__attribute__ ((weak)) void ergodox_right_led_3_on(void) {}

__attribute__ ((weak)) void ergodox_board_led_off(void) {}

__attribute__ ((weak)) void ergodox_right_led_1_off(void) {}

__attribute__ ((weak)) void ergodox_right_led_2_off(void) {}

__attribute__ ((weak)) void ergodox_right_led_3_off(void) {}

__attribute__ ((weak)) void ergodox_right_led_1_set(uint8_t n) {}

__attribute__ ((weak)) void ergodox_right_led_2_set(uint8_t n) {}

__attribute__ ((weak)) void ergodox_right_led_3_set(uint8_t n) {}

#ifdef SWAP_HANDS_ENABLE
__attribute__ ((weak))
const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
    {{0,  9}, {1,  9}, {2,  9}, {3,  9}, {4,  9}},
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

#ifdef LED_MATRIX_ENABLE
const is31fl3731_led_t PROGMEM g_is31fl3731_leds[IS31FL3731_LED_COUNT] = {
// The numbers in the comments are the led numbers DXX on the PCB
/* Refer to IS31 manual for these locations
 *  driver
 *  |   LED address
 *  |   | */
// Left half
//      45           44           43           42           41           40           39
   { 0, C2_2 }, { 0, C1_2 }, { 0, C5_1 }, { 0, C4_1 }, { 0, C3_1 }, { 0, C2_1 }, { 0, C1_1 },
//      52           51           50           49           48           47           46
   { 0, C4_3 }, { 0, C3_3 }, { 0, C2_3 }, { 0, C1_3 }, { 0, C5_2 }, { 0, C4_2 }, { 0, C3_2 },
//      58           57           56           55           54           53
   { 0, C5_4 }, { 0, C4_4 }, { 0, C3_4 }, { 0, C2_4 }, { 0, C1_4 }, { 0, C5_3 },
//      67           66           65           64           63           62           61
   { 0, C4_6 }, { 0, C3_6 }, { 0, C2_6 }, { 0, C1_6 }, { 0, C5_5 }, { 0, C4_5 }, { 0, C3_5 },
//      76           75           74           73           72
   { 0, C4_8 }, { 0, C3_8 }, { 0, C2_8 }, { 0, C1_8 }, { 0, C4_7 },
//                                                                                    60           59
                                                                                 { 0, C2_5 }, { 0, C1_5 },
//                                                                                                 68
                                                                                              { 0, C5_6 },
//                                                                       71           70           69
                                                                    { 0, C3_7 }, { 0, C2_7 }, { 0, C1_7 },
// Right half (mirrored)
// Due to how LED_MATRIX_SPLIT is implemented, only the first half of g_is31fl3731_leds is actually used.
// Luckily, the right half has the same LED pinouts, just mirrored.
//      45           44           43           42           41           40           39
   { 0, C2_2 }, { 0, C1_2 }, { 0, C5_1 }, { 0, C4_1 }, { 0, C3_1 }, { 0, C2_1 }, { 0, C1_1 },
//      52           51           50           49           48           47           46
   { 0, C4_3 }, { 0, C3_3 }, { 0, C2_3 }, { 0, C1_3 }, { 0, C5_2 }, { 0, C4_2 }, { 0, C3_2 },
//      58           57           56           55           54           53
   { 0, C5_4 }, { 0, C4_4 }, { 0, C3_4 }, { 0, C2_4 }, { 0, C1_4 }, { 0, C5_3 },
//      67           66           65           64           63           62           61
   { 0, C4_6 }, { 0, C3_6 }, { 0, C2_6 }, { 0, C1_6 }, { 0, C5_5 }, { 0, C4_5 }, { 0, C3_5 },
//      76           75           74           73           72
   { 0, C4_8 }, { 0, C3_8 }, { 0, C2_8 }, { 0, C1_8 }, { 0, C4_7 },
//                                                                                    60           59
                                                                                 { 0, C2_5 }, { 0, C1_5 },
//                                                                                                 68
                                                                                              { 0, C5_6 },
//                                                                       71           70           69
                                                                    { 0, C3_7 }, { 0, C2_7 }, { 0, C1_7 },
};

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        // Left half
        { NO_LED, NO_LED, NO_LED,     33,     34 },
        { NO_LED, NO_LED, NO_LED,     32,     37 },
        {      6,     13, NO_LED,     26,     36 },
        {      5,     12,     19,     25,     35 },
        {      4,     11,     18,     24,     31 },
        {      3,     10,     17,     23,     30 },
        {      2,      9,     16,     22,     29 },
        {      1,      8,     15,     21,     28 },
        {      0,      7,     14,     20,     27 },
        // Right half
        { NO_LED, NO_LED, NO_LED,     71,     72 },
        { NO_LED, NO_LED, NO_LED,     70,     75 },
        {     44,     51, NO_LED,     64,     74 },
        {     43,     50,     57,     63,     73 },
        {     42,     49,     56,     62,     69 },
        {     41,     48,     55,     61,     68 },
        {     40,     47,     54,     60,     67 },
        {     39,     46,     53,     59,     66 },
        {     38,     45,     52,     58,     65 },
    }, {
        // LED Index to Physical Position (assumes a reasonable gap between halves)
	// Left half
        {   0,  3 }, {  15,  3 }, {  27,  1 }, {  39,  0 }, {  51,  1 }, {  63,  2 }, {  75,  2 },
        {   0, 13 }, {  15, 13 }, {  27, 11 }, {  39, 10 }, {  51, 11 }, {  63, 12 }, {  78, 17 },
        {   0, 23 }, {  15, 23 }, {  27, 21 }, {  39, 20 }, {  51, 21 }, {  63, 22 },
        {   0, 33 }, {  15, 33 }, {  27, 31 }, {  39, 30 }, {  51, 31 }, {  63, 32 }, {  78, 32 },
        {   4, 43 }, {  15, 43 }, {  27, 41 }, {  39, 40 }, {  51, 41 },
                                                                                      {  89, 41 }, { 100, 46 },
                                                                                                   {  95, 55 },
                                                                         {  72, 54 }, {  83, 59 }, {  90, 64 },
        // Right half (mirrored)
        { 224,  3 }, { 209,  3 }, { 197,  1 }, { 185,  0 }, { 173,  1 }, { 161,  2 }, { 149,  2 },
        { 224, 13 }, { 209, 13 }, { 197, 11 }, { 185, 10 }, { 173, 11 }, { 161, 12 }, { 146, 17 },
        { 224, 23 }, { 209, 23 }, { 197, 21 }, { 185, 20 }, { 173, 21 }, { 161, 22 },
        { 224, 33 }, { 209, 33 }, { 197, 31 }, { 185, 30 }, { 173, 31 }, { 161, 32 }, { 146, 32 },
        { 220, 43 }, { 209, 43 }, { 197, 41 }, { 185, 40 }, { 173, 41 },
                                                                                      { 135, 41 }, { 124, 46 },
                                                                                                   { 129, 55 },
                                                                         { 152, 54 }, { 141, 59 }, { 134, 64 },
    }, {
        // LED Index to Flag
        // Left half
        1, 4, 4, 4, 4, 4, 1,
        1, 4, 4, 4, 4, 4, 1,
        1, 4, 4, 4, 4, 4,
        1, 4, 4, 4, 4, 4, 1,
        1, 1, 1, 1, 1,
                          1, 1,
                             1,
                       1, 1, 1,
        // Right half (mirrored)
        1, 4, 4, 4, 4, 4, 1,
        1, 4, 4, 4, 4, 4, 1,
        1, 4, 4, 4, 4, 4,
        1, 4, 4, 4, 4, 4, 1,
        1, 1, 1, 1, 1,
                          1, 1,
                             1,
                       1, 1, 1,
    }
};
#endif

#ifdef ST7565_ENABLE
__attribute__((weak)) void st7565_on_user(void) {
    ergodox_infinity_lcd_color(UINT16_MAX / 2, UINT16_MAX / 2, UINT16_MAX / 2);
}

__attribute__((weak)) void st7565_off_user(void) {
    ergodox_infinity_lcd_color(0, 0, 0);
}

static void format_layer_bitmap_string(char* buffer, uint8_t offset) {
    for (int i = 0; i < 16 && i + offset < MAX_LAYER; i++) {
        if (i == 0 || i == 4 || i == 8 || i == 12) {
            *buffer = ' ';
            ++buffer;
        }

        uint8_t layer = i + offset;
        if (layer_state_cmp(default_layer_state, layer)) {
            *buffer = 'D';
        } else if (layer_state_is(layer)) {
            *buffer = '1';
        } else {
            *buffer = '_';
        }
        ++buffer;
    }
    *buffer = 0;
}

__attribute__((weak)) void st7565_task_user(void) {
    if (is_keyboard_master()) {
        // Draw led and layer status
        led_t leds = host_keyboard_led_state();
        if(leds.num_lock) { st7565_write("Num ", false); }
        if(leds.caps_lock) { st7565_write("Cap ", false); }
        if(leds.scroll_lock) { st7565_write("Scrl ", false); }
        if(leds.compose) { st7565_write("Com ", false); }
        if(leds.kana) { st7565_write("Kana", false); }
        st7565_advance_page(true);

        char layer_buffer[16 + 5];  // 3 spaces and one null terminator
        st7565_set_cursor(0, 1);
        format_layer_bitmap_string(layer_buffer, 0);
        st7565_write_ln(layer_buffer, false);
        format_layer_bitmap_string(layer_buffer, 16);
        st7565_write_ln(layer_buffer, false);
        st7565_write_ln("  1=On    D=Default", false);
    } else {
        // Draw logo
        static const char qmk_logo[] = {
            0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
            0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
            0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
        };

        st7565_write(qmk_logo, false);
        st7565_write("  Infinity  Ergodox  ", false);
    }
}
#endif

#if defined(SPLIT_KEYBOARD)
void usart_master_init(SerialDriver **driver) {
    PORTA->PCR[1] = PORTx_PCRn_PE | PORTx_PCRn_PS | PORTx_PCRn_PFE | PORTx_PCRn_MUX(2);
    PORTA->PCR[2] = PORTx_PCRn_DSE | PORTx_PCRn_SRE | PORTx_PCRn_MUX(2);

    // driver is set to SD1 in config.h
}

void usart_slave_init(SerialDriver **driver) {
    PORTE->PCR[0] = PORTx_PCRn_PE | PORTx_PCRn_PS | PORTx_PCRn_PFE | PORTx_PCRn_MUX(3);
    PORTE->PCR[1] = PORTx_PCRn_DSE | PORTx_PCRn_SRE | PORTx_PCRn_MUX(3);

    *driver = &SD2;
}
#endif
