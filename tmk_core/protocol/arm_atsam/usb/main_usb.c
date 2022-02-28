/*
Copyright 2018 Massdrop Inc.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "samd51j18a.h"
#include "conf_usb.h"
#include "udd.h"

#ifdef RAW_ENABLE
#    include "raw_hid.h"
#endif

uint8_t keyboard_protocol = 1;

void main_suspend_action(void) {
    ui_powerdown();
}

void main_resume_action(void) {
    ui_wakeup();
}

void main_sof_action(void) {
    ui_process(udd_get_frame_number());
}

void main_remotewakeup_enable(void) {
    ui_wakeup_enable();
}

void main_remotewakeup_disable(void) {
    ui_wakeup_disable();
}

volatile bool main_b_kbd_enable = false;
bool          main_kbd_enable(void) {
    main_b_kbd_enable = true;
    return true;
}

void main_kbd_disable(void) {
    main_b_kbd_enable = false;
}

#ifdef NKRO_ENABLE
volatile bool main_b_nkro_enable = false;
bool          main_nkro_enable(void) {
    main_b_nkro_enable = true;
    return true;
}

void main_nkro_disable(void) {
    main_b_nkro_enable = false;
}
#endif

#ifdef EXTRAKEY_ENABLE
volatile bool main_b_exk_enable = false;
bool          main_exk_enable(void) {
    main_b_exk_enable = true;
    return true;
}

void main_exk_disable(void) {
    main_b_exk_enable = false;
}
#endif

#ifdef CONSOLE_ENABLE
volatile bool main_b_con_enable = false;
bool          main_con_enable(void) {
    main_b_con_enable = true;
    return true;
}

void main_con_disable(void) {
    main_b_con_enable = false;
}
#endif

#ifdef MOUSE_ENABLE
volatile bool main_b_mou_enable = false;
bool          main_mou_enable(void) {
    main_b_mou_enable = true;
    return true;
}

void main_mou_disable(void) {
    main_b_mou_enable = false;
}
#endif

#ifdef RAW_ENABLE
volatile bool main_b_raw_enable = false;
bool          main_raw_enable(void) {
    main_b_raw_enable = true;
    return true;
}

void main_raw_disable(void) {
    main_b_raw_enable = false;
}

void main_raw_receive(uint8_t *buffer, uint8_t len) {
    raw_hid_receive(buffer, len);
}
#endif
