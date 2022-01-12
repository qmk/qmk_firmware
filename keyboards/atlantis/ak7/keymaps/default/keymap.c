#include "ak7.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[0] = LAYOUT(
		KC_VOLD, MO(1), KC_VOLU,
		LCTL(KC_C), LCTL(KC_X), LCTL(KC_V),
		KC_F1, KC_F2, KC_RSFT),

	[1] = LAYOUT(
		KC_A, KC_TRNS, KC_B,
		RGB_TOG, RGB_MOD, KC_TRNS,
		KC_TRNS,KC_TRNS,KC_TRNS)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {


	switch (id) {

	}
	return MACRO_NONE;
}

void matrix_init_user(void) {
}

bool is_alt_tab_active = false; // ALT_TAB激活状态。
uint16_t alt_tab_timer = 0;     // ALT_TAB状态计时器。

void matrix_scan_user(void)
{
    if (is_alt_tab_active)
    {
        if (timer_elapsed(alt_tab_timer) > 1000) // ALT_TAB释放KC_LALT延迟，1000ms。
        {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }
}

bool is_rshift_pressed = false; // RSHIFT按下状态。


bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    switch (keycode)
    {
    case KC_RSFT:
        if (record->event.pressed)
        {
            is_rshift_pressed = true;
        }
        else
        {
            is_rshift_pressed = false;
        } //检测RSHIFT是否按下，返回给is_rshift_pressed。
        return true;

    default:
        return true;
    }
}



bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
		if (!is_rshift_pressed){

        	if (clockwise) {
        	action_exec((keyevent_t){
        					.key = (keypos_t){.row = 0, .col = 0}, .pressed = true, .time = (timer_read() | 1)  /* time should not be 0 */
                       });
        	action_exec((keyevent_t){
        					.key = (keypos_t){.row = 0, .col = 0}, .pressed = false, .time = (timer_read() | 1)  /* time should not be 0 */
                       });
           } else {
        	action_exec((keyevent_t){
        					.key = (keypos_t){.row = 0, .col = 2}, .pressed = true, .time = (timer_read() | 1)  /* time should not be 0 */
                       });
        	action_exec((keyevent_t){
        					.key = (keypos_t){.row = 0, .col = 2}, .pressed = false, .time = (timer_read() | 1)  /* time should not be 0 */
                       });
           }
           							}
		else{

            if (!clockwise) //反转以实现旋钮顺时针旋转向后切换，逆时针旋转向前切换。
            {
                if (!is_alt_tab_active)
                {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                tap_code16(KC_TAB);
            }
            else
            {
                if (!is_alt_tab_active)
                {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                tap_code16(S(KC_TAB));
            } //旋钮默认进行ALT_TAB任务切换。

			}

    }
    return true;
}

void led_set_user(uint8_t usb_led) {

	if (usb_led & (1 << USB_LED_NUM_LOCK)) {
		DDRD |= (1 << 0); PORTD &= ~(1 << 0);
	} else {
		DDRD &= ~(1 << 0); PORTD &= ~(1 << 0);
	}

	if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
		DDRD |= (1 << 5); PORTD &= ~(1 << 5);
	} else {
		DDRD &= ~(1 << 5); PORTD &= ~(1 << 5);
	}

	if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {
		DDRD |= (1 << 4); PORTD &= ~(1 << 4);
	} else {
		DDRD &= ~(1 << 4); PORTD &= ~(1 << 4);
	}

	if (usb_led & (1 << USB_LED_COMPOSE)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_KANA)) {

	} else {

	}

}
