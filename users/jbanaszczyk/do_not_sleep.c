
#include "quantum.h"
#include <deferred_exec.h>
#include "do_not_sleep.h"

#ifndef DO_NOT_SLEEP_SECONDS
#define DO_NOT_SLEEP_SECONDS (5*60UL)
#endif

#ifndef DO_NOT_SLEEP_ACTION_KEY
#define DO_NOT_SLEEP_ACTION_KEY KC_WAKE
#endif

static uint32_t do_not_sleep_timeout = DO_NOT_SLEEP_SECONDS*1000UL;

static deferred_token token_do_not_sleep = INVALID_DEFERRED_TOKEN;

__attribute__((weak)) uint32_t do_not_sleep_action(uint32_t trigger_time, void *cb_arg) {
	dprintf("do_not_sleep action: %u\n", DO_NOT_SLEEP_ACTION_KEY);
	tap_code(DO_NOT_SLEEP_ACTION_KEY);
	return do_not_sleep_timeout;
}

bool is_do_not_sleep_enabled(void) {
	return token_do_not_sleep!=INVALID_DEFERRED_TOKEN;
}

void do_not_sleep_disable(void) {
	cancel_deferred_exec(token_do_not_sleep);
	token_do_not_sleep = INVALID_DEFERRED_TOKEN;
}

void do_not_sleep_enable(void) {
	if (!extend_deferred_exec(token_do_not_sleep, do_not_sleep_timeout)) {
		token_do_not_sleep = defer_exec(do_not_sleep_timeout, &do_not_sleep_action, NULL);
	}
}

uint32_t get_do_not_sleep_timeout(void) {
	return do_not_sleep_timeout/1000U;
}

void set_do_not_sleep_timeout(uint32_t time_in_seconds) {
	do_not_sleep_disable();
	do_not_sleep_timeout = time_in_seconds*1000U;
	do_not_sleep_enable();
}

bool process_record_do_not_sleep(uint16_t keycode, keyrecord_t *record) {
	if (is_do_not_sleep_enabled()) {
		do_not_sleep_enable();
	}

	if (record->event.pressed) {
		switch (keycode) {
			case KC_DO_NOT_SLEEP_START: {
				do_not_sleep_enable();
				return false;
			}

			case KC_DO_NOT_SLEEP_STOP: {
				do_not_sleep_disable();
				return false;
			}

			default: {
				break;
			}
		}
	} else {
		switch (keycode) {
			case KC_DO_NOT_SLEEP_START:
			case KC_DO_NOT_SLEEP_STOP: {
				return false;
			}
			default: {
				break;
			}
		}
	}

	return
		true;
}

uint8_t do_not_sleep_serialize(void) {
	return (uint8_t)is_do_not_sleep_enabled();
}

void do_not_sleep_deserialize(uint8_t value) {
	if ((bool)(value)!=is_do_not_sleep_enabled()) {
		if ((bool)(value)) {
			do_not_sleep_enable();
		} else {
			do_not_sleep_disable();
		}
	}
}

