#include "quantum.h"
#include "jbanaszczyk.h"
#include "do_not_sleep.h"

void keyboard_post_init_user(void) {
#ifndef NO_DEBUG
  debug_enable = true;
#endif
#ifdef DO_NOT_SLEEP
#ifdef DO_NOT_SLEEP_START_LOCKED
  do_not_sleep_lock();
#else
  do_not_sleep_enable();
#endif
#endif
}

void matrix_scan_user(void) {
#ifdef DO_NOT_SLEEP
  do_not_sleep_scan();
#endif
}

void startup_user() {
#ifndef NO_DEBUG
  debug_enable = true;
#endif
}

void shutdown_user() {
#ifdef DO_NOT_SLEEP
  do_not_sleep_disable();
#endif
}

void suspend_power_down_user(void) {
#ifdef DO_NOT_SLEEP
  do_not_sleep_disable();
#endif
}

void suspend_wakeup_init_user(void) {
#ifdef DO_NOT_SLEEP
  do_not_sleep_enable();
#endif
}

__attribute__ ((weak)) void keyboard_pre_init_user(void) {
}

__attribute__ ((weak)) void housekeeping_task_user(void) {
}

__attribute__ ((weak)) void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
}

__attribute__ ((weak)) layer_state_t default_layer_state_set_user(layer_state_t state) {
  return state;
}

__attribute__ ((weak)) void oneshot_locked_mods_changed_user(uint8_t mods) {
}

__attribute__ ((weak)) void oneshot_mods_changed_user(uint8_t mods) {
}

__attribute__ ((weak)) void oneshot_layer_changed_user(uint8_t layer) {
}

__attribute__ ((weak)) void eeconfig_init_user(void) {
  eeconfig_update_user(0);
}
