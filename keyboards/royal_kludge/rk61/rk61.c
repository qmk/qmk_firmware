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
