#pragma once

#include "jbanaszczyk_keycodes.h"

//==[ DO_NOT_SLEEP configuration begins ]=============

// 5 minutes
#define DO_NOT_SLEEP_SECONDS (60U * 5U)

// KC_LCTL or KC_WAKE are good candidates
#define DO_NOT_SLEEP_ACTION_KEY KC_LCTL
#ifndef DO_NOT_SLEEP_ACTION_KEY
#define DO_NOT_SLEEP_ACTION_KEY KC_WAKE
#endif

// uncomment according to your needs
//#define DO_NOT_SLEEP_AUTOSTART

//==[ DO_NOT_SLEEP configuration ends ]===============

bool is_do_not_sleep_enabled(void);
void do_not_sleep_enable(void);
void do_not_sleep_disable(void);
uint32_t get_do_not_sleep_timeout(void);
void set_do_not_sleep_timeout(uint32_t timeout_in_seconds);
bool process_record_do_not_sleep(uint16_t keycode, keyrecord_t *record);
uint32_t do_not_sleep_action(uint32_t trigger_time, void *cb_arg); // weak, can be redefined
uint8_t do_not_sleep_serialize(void);
void do_not_sleep_deserialize(uint8_t value);
