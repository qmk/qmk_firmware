#include "quantum.h"
#include <deferred_exec.h>
#include "auto_caps_off.h"

#ifndef LED_UPDATE_AUTO_CAPS_OFF_RETURNS
#define LED_UPDATE_AUTO_CAPS_OFF_RETURNS true
#endif

#ifndef AUTO_CAPS_OFF_TIMEOUT_SECONDS
#define AUTO_CAPS_OFF_TIMEOUT_SECONDS 30
#endif

static const uint32_t auto_caps_off_timeout = AUTO_CAPS_OFF_TIMEOUT_SECONDS*1000;

static deferred_token token_auto_caps_off = INVALID_DEFERRED_TOKEN;

static uint32_t auto_caps_off_action(uint32_t trigger_time, void *cb_arg) {
	led_t led_state = (led_t)host_keyboard_leds();

#ifndef AUTO_CAPS_OFF_IGNORE_NUM
	if (led_state.num_lock) {
		dprintf("auto_caps_off_action: KC_NUM_LOCK\n");
		tap_code(KC_NUM_LOCK);
	}
#endif

#ifndef AUTO_CAPS_OFF_IGNORE_CAPS
	if (led_state.caps_lock) {
		dprintf("auto_caps_off_action: KC_CAPS_LOCK\n");
		tap_code(KC_CAPS_LOCK);
	}
#endif

#ifndef AUTO_CAPS_OFF_IGNORE_SCROLL
	if (led_state.scroll_lock) {
		dprintf("auto_caps_off_action: KC_SCROLL_LOCK\n");
		tap_code(KC_SCROLL_LOCK);
	}
#endif
	return 0;
}

bool auto_caps_off_enabled(void) {
	return token_auto_caps_off!=INVALID_DEFERRED_TOKEN;
}

void auto_caps_off_disable(void) {
	cancel_deferred_exec(token_auto_caps_off);
	token_auto_caps_off = INVALID_DEFERRED_TOKEN;
}

void auto_caps_off_enable(void) {
	if (!extend_deferred_exec(token_auto_caps_off, auto_caps_off_timeout)) {
		token_auto_caps_off = defer_exec(auto_caps_off_timeout, &auto_caps_off_action, NULL);
	}
}

bool process_record_auto_caps_off(uint16_t keycode, keyrecord_t *record) {
	if (auto_caps_off_enabled()) {
		auto_caps_off_enable();
	}
	return true;
}

bool led_update_auto_caps_off(void) {
	auto_caps_off_enable();
	return LED_UPDATE_AUTO_CAPS_OFF_RETURNS;
}
