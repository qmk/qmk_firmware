#include "mike1808.h"
#include "print.h"

uint16_t copy_paste_timer;

__attribute__((weak)) bool process_record_secrets(uint16_t keycode, keyrecord_t *record) {
    return true;
}
__attribute__((weak)) bool process_record_encoder(uint16_t keycode, keyrecord_t *record) {
    return true;
}
__attribute__((weak)) bool process_record_fun(uint16_t keycode, keyrecord_t *record) {
    return true;
}

static const char *git_commands[] = {
    "git init ",     "git clone ", "git config --global ", "git add ",
    "git diff ",     "git reset ", "git rebase ",          "git branch -b \"",
    "git checkout ", "git merge ", "git remote add ",      "git fetch ",
    "git pull ",     "git push ",  "git commit ",          "git status ",
    "git log ",
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef KEYLOGGER_ENABLE
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %b, time: %5u, int: %b, count: %u\n",
            keycode, record->event.key.col, record->event.key.row, record->event.pressed,
            record->event.time, record->tap.interrupted, record->tap.count);
#endif  // KEYLOGGER_ENABLE
    switch (keycode) {
        case KC_LINUX ... KC_WIN:
            if (record->event.pressed) {
                dprintf("set_single_persistent_default_layer %d\n", keycode - KC_LINUX + LINUX);
                set_single_persistent_default_layer(keycode - KC_LINUX + LINUX);
                return false;
            }

            break;

        case KC_CCCV:  // One key copy/paste
            if (record->event.pressed) {
                copy_paste_timer = timer_read();
            } else {
                if (timer_elapsed(copy_paste_timer) > TAPPING_TERM) {  // Hold, copy
                    if (layer_state_is(MACOS)) {
                        tap_code16(LGUI(KC_C));
                    } else {
                        tap_code16(LCTL(KC_C));
                    }
                } else {  // Tap, paste
                    if (layer_state_is(MACOS)) {
                        tap_code16(LGUI(KC_V));
                    } else {
                        tap_code16(LCTL(KC_V));
                    }
                }
            }
            break;

        case G_INIT ... G_LOG:
            if (record->event.pressed) {
                clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
                send_string_with_delay(git_commands[keycode - G_INIT], MACRO_TIMER);
                return false;
            }
            break;
#ifdef RGB_MATRIX_ENABLE
        case RGB_TOG:
            if (record->event.pressed) {
                switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL: {
                        rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER);
                        rgb_matrix_set_color_all(0, 0, 0);
                    } break;
                    case LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER: {
                        rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                        rgb_matrix_set_color_all(0, 0, 0);
                    } break;
                    case LED_FLAG_UNDERGLOW: {
                        // This line is for LED idle timer. It disables the toggle so you can turn
                        // off LED completely if you like
                        rgb_matrix_set_flags(LED_FLAG_NONE);
                        rgb_matrix_disable();
                    } break;
                    default: {
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                        rgb_matrix_enable();
                    } break;
                }
            }
            return false;
#endif  // RGB_MATRIX_ENABLE
    }

    return process_record_encoder(keycode, record) && process_record_secrets(keycode, record) &&
           process_record_fun(keycode, record);
}
