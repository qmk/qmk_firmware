#include QMK_KEYBOARD_H

#if 1
void led_test_init(void) {
    static int scan_count = 0;
    if( scan_count == 2 ) {
	rgblight_enable_noeeprom();
	rgblight_mode_noeeprom(35);
    }
    if( scan_count < 3 ) scan_count ++;
}

#else
// when qmk/qmk_firmware PullRequest #3113 available.
// can use this?
void startup_user(void) {
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(35);
}
#endif
