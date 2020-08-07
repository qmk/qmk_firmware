#include "gotham.h"

uint16_t clipboard_timer;

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    xprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif  // KEYLOGGER_ENABLE
    if (process_record_keymap(keycode, record)
#ifdef OLED_DRIVER_ENABLE
        && process_record_user_oled(keycode, record)
#endif
#ifdef ENCODER_ENABLE
        && process_record_user_encoder(keycode, record)
#endif
#ifdef THUMBSTICK_ENABLE
        && process_record_user_thumbstick(keycode, record)
#endif
    ) {
        switch (keycode) {
            case KC_QWERTY ... KC_NORMAN:
                if (record->event.pressed) {
                    set_single_persistent_default_layer(keycode - KC_QWERTY);
                }
                return false;

            case KC_MAKE:
                if (!record->event.pressed) {
                    SEND_STRING("make " QMK_KEYBOARD ":" QMK_KEYMAP ":flash"
#if (defined(BOOTLOADER_DFU) || defined(BOOTLOADER_LUFA_DFU) || defined(BOOTLOADER_QMK_DFU))
                                " BOOTLOADER=atmel-dfu"
#elif defined(BOOTLOADER_HALFKAY)
                                " BOOTLOADER=halfkay"
#elif defined(BOOTLOADER_CATERINA)
                                " BOOTLOADER=caterina"
#endif
                                " -j5 --output-sync\n");
                }
                break;

            case VRSN:  // Prints firmware version
                if (record->event.pressed) {
                    SEND_STRING(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION ", Built on: " QMK_BUILDDATE);
                }
                break;

            case KC_CCCV:  // One key copy/paste
                if (record->event.pressed) {
                    clipboard_timer = timer_read();
                } else {
                    if (timer_elapsed(clipboard_timer) > TAPPING_TERM) {  // Hold, copy
                        tap_code16(LCTL(KC_C));
                    } else {  // Tap, paste
                        tap_code16(LCTL(KC_V));
                    }
                }
                break;
        }
    }
    return true;
}
