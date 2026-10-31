// SPDX-License-Identifier: GPL-2.0-or-later

#include "westberry_bridge.h"
#include "module.h"
#include "smsg.h"

static volatile uint8_t wb_last_devctrl_event = 0;

bool md_receive_process_user(uint8_t *pdata, uint8_t len) {
    if (pdata && len >= 2 && pdata[0] == 0x5B) {
        wb_last_devctrl_event = pdata[1];
    }

    return true;
}

uint8_t wb_bridge_take_devctrl_event(void) {
    uint8_t event = wb_last_devctrl_event;
    wb_last_devctrl_event = 0;
    return event;
}


void wb_bridge_init(void) {
    md_init();
}

void wb_bridge_task(void) {
    md_main_task();
}

void wb_bridge_keyboard(uint8_t *data) {
    md_send_kb(data);
}

void wb_bridge_nkro(uint8_t *data) {
    md_send_nkro(data);
}

void wb_bridge_consumer(uint16_t usage) {
    md_send_consumer((uint8_t *)&usage);
}

void wb_bridge_system(uint8_t usage) {
    md_send_system(&usage);
}

void wb_bridge_fn(bool pressed) {
    /*
     * The wireless controller uses 0x10 for pressed, 0x00 for released.
     */
    uint8_t data = pressed ? 0x10 : 0x00;
    md_send_fn(&data);
}

void wb_bridge_mouse(uint8_t *report) {
    md_send_mouse(report);
}

void wb_bridge_name(const char *name) {
    if (name) {
        md_send_devinfo(name);
    }
}

void wb_bridge_devctrl(uint8_t cmd) {
    md_send_devctrl(cmd);
}

uint8_t wb_bridge_state(void) {
    return *md_getp_state();
}

uint8_t wb_bridge_battery(void) {
    return *md_getp_bat();
}

uint8_t wb_bridge_indicator(void) {
    return *md_getp_indicator();
}

bool wb_bridge_busy(void) {
    return smsg_is_busy();
}
