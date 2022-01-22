#pragma once

#include "jbanaszczyk_keycodes.h"

//==[ DO_NOT_SLEEP configuration begins ]=============

// 5 minutes
#define DO_NOT_SLEEP_TIMEOUT 60U * 5U

// KC_LCTL or KC_WAKE are good candidates
#define DO_NOT_SLEEP_ACTION_KEY KC_LCTL
#ifndef DO_NOT_SLEEP_ACTION_KEY
#define DO_NOT_SLEEP_ACTION_KEY KC_WAKE
#endif

// uncomment according to your needs
//#define DO_NOT_SLEEP_START_LOCKED

//==[ DO_NOT_SLEEP configuration ends ]===============

bool is_do_not_sleep_enabled(void);
bool is_do_not_sleep_locked(void);
bool do_not_sleep_enable(void);
bool do_not_sleep_disable(void);
void do_not_sleep_lock(void);
void do_not_sleep_unlock(void);
void do_not_sleep_scan(void);
bool do_not_sleep_process(uint16_t keycode, keyrecord_t *record);
void do_not_sleep_action(void); // weak, can be redefined
uint8_t do_not_sleep_serialize(void);
void do_not_sleep_deserialize(uint8_t value);
