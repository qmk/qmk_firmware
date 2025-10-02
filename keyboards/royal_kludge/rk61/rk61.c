#include "quantum.h"

// 3 seconds
#define FACTORY_RESET_HOLD_TIME 30

#define BLINK_CYCLE_LENGTH 4
#define BLINK_CYCLES(x) (x * BLINK_CYCLE_LENGTH)
#define BLINK_CYCLE_COUNT BLINK_CYCLES(3)

#define LOOP_10HZ_PERIOD 100

deferred_token loop10hz_token = INVALID_DEFERRED_TOKEN;
uint32_t loop_10Hz(uint32_t trigger_time, void *cb_arg);
uint8_t blink_cnt = 0;

void keyboard_post_init_kb(void) {
    keyboard_post_init_user();
    loop10hz_token = defer_exec(LOOP_10HZ_PERIOD, loop_10Hz, NULL);
}

// Listens for runtime "magic" key combos and performs LED blink
uint32_t loop_10Hz(uint32_t trigger_time, void *cb_arg) {
    extern matrix_row_t matrix[MATRIX_ROWS];
    static uint32_t reset_to_factory_tick = 0;

    // When Fn + Space held for 3 seconds:
    // Perform a factory reset
    if (
        matrix[0] == 0 &&
        matrix[1] == 0 &&
        matrix[2] == 0 && 
        matrix[3] == 0 &&
        matrix[4] == ((1 << 12) | (1 << 5))
    ) {
        if (reset_to_factory_tick > FACTORY_RESET_HOLD_TIME) {
            reset_to_factory_tick = 0;
            eeconfig_init();
            soft_reset_keyboard();
        }
        reset_to_factory_tick++;
    } else {
        reset_to_factory_tick = 0;
    }

    // When Fn + O + L pressed:
    // Perform LED test (set all to white on full blast)
    if (
        matrix[0] == 0 &&
        matrix[1] == 1 << 9 &&
        matrix[2] == 1 << 9 && 
        matrix[3] == 0 &&
        matrix[4] == 1 << 12
    ) {
            clear_keyboard();

            rgb_matrix_set_color_all(RGB_WHITE);
            extern void rgb_matrix_update_pwm_buffers(void);
            rgb_matrix_update_pwm_buffers();

            wait_ms(100);
            matrix_scan();

            // Keep LEDs on until any key is pressed
            while (!(
                matrix[0] ||
                matrix[1] ||
                matrix[2] ||
                matrix[3] ||
                matrix[4]
            )) {
                matrix_scan();
            }
    }

    if (blink_cnt) {
        switch (blink_cnt % BLINK_CYCLE_LENGTH) {
            // case 0: wait one cycle
            case 1: // LEDs off
                rgb_matrix_disable_noeeprom();
                break;
            // case 2: wait one cycle
            case 3: // LEDs on
                rgb_matrix_enable_noeeprom();
                break;
            default:
                break;
        }

        blink_cnt++;

        if (blink_cnt > BLINK_CYCLE_COUNT) {
            blink_cnt = 0;
        }
    }
    
    return LOOP_10HZ_PERIOD;
}

#ifdef RGB_MATRIX_ENABLE
#define __ NO_LED
led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        { 13, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2,  1,  0 },
        { 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27 },
        { 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, __ },
        { 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, __, __ },
        { 60, 59, 58, __, __, 57, __, __, 56, 55, 54, __, 53, __ },
    },
    {
        // LED Index to Physical Position
        { 218,   0 }, { 193,   0 }, { 177,   0 }, { 161,   0 }, { 145,   0 }, { 129,   0 }, { 113,   0 }, {  97,   0 }, {  81,   0 }, {  64,   0 }, {  48,   0 }, {  32,   0 }, {  16,   0 }, {   0,   0 },
        {   4,  16 }, {  24,  16 }, {  40,  16 }, {  56,  16 }, {  73,  16 }, {  89,  16 }, { 105,  16 }, { 121,  16 }, { 137,  16 }, { 153,  16 }, { 169,  16 }, { 185,  16 }, { 202,  16 }, { 222,  16 },
        { 216,  32 }, { 189,  32 }, { 173,  32 }, { 157,  32 }, { 141,  32 }, { 125,  32 }, { 109,  32 }, { 93,   32 }, {  77,  32 }, {  60,  32 }, {  44,  32 }, {  28,  32 }, {   6,  32 },
        {  10,  48 }, {  36,  48 }, {  52,  48 }, {  69,  48 }, {  85,  48 }, { 101,  48 }, { 117,  48 }, { 133,  48 }, { 149,  48 }, { 165,  48 }, { 181,  48 }, { 212,  48 },
        { 224,  64 }, { 204,  64 }, { 184,  64 },                             { 164,  64 },                             { 103,  64 }, {  42,  64 }, {  22,  64 },               {   2,  64 },
    },
    {
        // RGB LED Index to Flag
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1,
        1,    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1,
        1, 1, 1,          1,          1, 1, 1, 1,
    }
};


#endif // RGB_MATRIX_ENABLE

#ifdef VIA_ENABLE
#define VIA_EEPROM_RESET 0x0A
bool via_command_kb(uint8_t *data, uint8_t length) {
    uint8_t command_id = data[0];
    
    if (command_id == VIA_EEPROM_RESET) {
        eeconfig_init();
        soft_reset_keyboard();
    }

    return false;
}
#endif
