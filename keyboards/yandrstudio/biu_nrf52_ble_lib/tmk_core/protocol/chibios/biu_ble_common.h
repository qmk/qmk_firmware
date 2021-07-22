#pragma once

#include "report.h"
#include <stdint.h>

enum bluetooth_state {
    WORKING,
    SLEEPING,
    WAITING,
    STOPWORK
};

#ifdef __cplusplus
extern "C" {
#endif

bool bluetooth_init(void);
bool bluetooth_init_pre(void);
bool bluetooth_init_pos(void);
void bluetooth_task(void);
bool bluetooth_is_connected(void);
bool bluetooth_is_configured(void);
void bluetooth_wakeup_once(void);
void bluetooth_unpair_all(void);
void bluetooth_unpair_one(uint8_t device_id);
void bluetooth_unpair_current(void);
void bluetooth_pair(void);
void bluetooth_clear_buf(void);
void bluetooth_switch_one(uint8_t device_id);
uint8_t bluetooth_working_state(void);
void bluetooth_power_manager(void);
void bluetooth_send_battery_level(void);

void bluetooth_send_keyboard(report_keyboard_t *report);

#ifdef EXTRAKEY_ENABLE
void bluetooth_send_extra(uint8_t report_id, uint16_t keycode);
#endif

#ifdef MOUSE_ENABLE
void bluetooth_send_mouse(report_mouse_t *report);
#endif

#ifdef NKRO_ENABLE
void bluetooth_send_keyboard_nkro(report_keyboard_t *report);
#endif

#ifdef JOYSTICK_ENABLE
void bluetooth_send_joystick(joystick_report_t *report);
#endif


#ifdef __cplusplus
}
#endif
