
#include "biu_ble_common.h"

__attribute__((weak)) bool bluetooth_init(void) { return true; }
__attribute__((weak)) bool bluetooth_init_pre(void) { return true; }
__attribute__((weak)) bool bluetooth_init_pos(void) { return true; }
__attribute__((weak)) void bluetooth_task(void) {}
__attribute__((weak)) bool bluetooth_is_connected(void) { return true; }
__attribute__((weak)) bool bluetooth_is_configured(void) { return true; }
__attribute__((weak)) void bluetooth_wakeup_once(void) {}
__attribute__((weak)) void bluetooth_unpair_all(void) {}
__attribute__((weak)) void bluetooth_unpair_one(uint8_t device_id) {}
__attribute__((weak)) void bluetooth_unpair_current(void) {}
__attribute__((weak)) void bluetooth_pair(void) {}
__attribute__((weak)) void bluetooth_clear_buf(void) {}
__attribute__((weak)) void bluetooth_switch_one(uint8_t device_id) {}
__attribute__((weak)) uint8_t bluetooth_working_state(void) { return 0; }
__attribute__((weak)) void bluetooth_power_manager(void) {};
__attribute__((weak)) void bluetooth_send_battery_level(void) { }

__attribute__((weak)) void bluetooth_send_keyboard(report_keyboard_t *report) {}

#ifdef EXTRAKEY_ENABLE
__attribute__((weak)) void bluetooth_send_extra(uint8_t report_id, uint16_t keycode) {}
#endif


#ifdef MOUSE_ENABLE
__attribute__((weak)) void bluetooth_send_mouse(report_mouse_t *report) {}
#endif

#ifdef NKRO_ENABLE
__attribute__((weak)) void bluetooth_send_keyboard_nkro(report_keyboard_t *report) {}
#endif

#ifdef JOYSTICK_ENABLE
__attribute__((weak)) void bluetooth_send_joystick(joystick_report_t *report) {}
#endif






