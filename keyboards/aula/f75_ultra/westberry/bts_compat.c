// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "bts_lib.h"
#include "westberry_bridge.h"

#include <string.h>

static bts_info_t *f75_bts_info = NULL;
static bool f75_nkro = false;

/*
 * Wireless keyboard state:
 *
 * boot report:
 *   byte 0 = modifiers
 *   byte 1 = reserved
 *   bytes 2..7 = six ordinary keys
 *
 * NKRO:
 *   bitmap indexed exactly as:
 *       byte = keycode >> 3
 *       bit  = keycode & 7
 *
 * Original BTS task sends 14 bytes for NKRO.
 */

static uint8_t boot_report[8];
static uint8_t f75_nkro_bitmap[14];

static const uint16_t f75_consumer_usages[27] = {
    0x00E2, /* 0xA8 */
    0x00E9, /* 0xA9 */
    0x00EA, /* 0xAA */
    0x00B5, /* 0xAB */
    0x00B6, /* 0xAC */
    0x00B7, /* 0xAD */
    0x00CD, /* 0xAE */
    0x0183, /* 0xAF */
    0x00CC, /* 0xB0 */
    0x018A, /* 0xB1 */
    0x0192, /* 0xB2 */
    0x0194, /* 0xB3 */
    0x0221, /* 0xB4 */
    0x0223, /* 0xB5 */
    0x0224, /* 0xB6 */
    0x0225, /* 0xB7 */
    0x0226, /* 0xB8 */
    0x0227, /* 0xB9 */
    0x022A, /* 0xBA */
    0x00B3, /* 0xBB */
    0x00B4, /* 0xBC */
    0x006F, /* 0xBD */
    0x0070, /* 0xBE */
    0x019F, /* 0xBF */
    0x01CB, /* 0xC0 */
    0x029F, /* 0xC1 */
    0x02A0  /* 0xC2 */
};


static uint8_t f75_system_report = 0;

static uint8_t f75_mouse_report[5] = {0};
static uint8_t f75_mouse_speed = 0;

/*
 * Exact proprietary movement tables.
 *
 * c_offsets controls X/Y.
 * w_offsets controls wheel.
 */
static const int16_t f75_c_offsets[4] = {
    0x0010, 0x0001, 0x0004, 0x0020
};

static const int16_t f75_w_offsets[4] = {
    0x0001, 0x0001, 0x0001, 0x0001
};

static void f75_send_mouse(void) {
    wb_bridge_mouse(f75_mouse_report);
}


static int8_t f75_signed_scale_181(int8_t value) {
    int16_t scaled = ((int16_t)value * 181) >> 8;

    /*
     * Original adjust_speed forces a zero diagonal X/Y result to +1.
     */
    if (scaled == 0) {
        scaled = 1;
    }

    return (int8_t)scaled;
}

static void f75_adjust_speed(void) {
    uint8_t index = f75_mouse_speed;

    if (index > 3) {
        index = 0;
    }

    int8_t c = (int8_t)f75_c_offsets[index];
    int8_t w = (int8_t)f75_w_offsets[index];

    /*
     * Preserve current direction while replacing magnitude.
     * This follows the proprietary adjust_speed routine.
     */
    if ((int8_t)f75_mouse_report[1] > 0) {
        f75_mouse_report[1] = (uint8_t)c;
    } else if ((int8_t)f75_mouse_report[1] < 0) {
        f75_mouse_report[1] = (uint8_t)(-c);
    }

    if ((int8_t)f75_mouse_report[2] > 0) {
        f75_mouse_report[2] = (uint8_t)c;
    } else if ((int8_t)f75_mouse_report[2] < 0) {
        f75_mouse_report[2] = (uint8_t)(-c);
    }

    if ((int8_t)f75_mouse_report[4] > 0) {
        f75_mouse_report[4] = (uint8_t)w;
    } else if ((int8_t)f75_mouse_report[4] < 0) {
        f75_mouse_report[4] = (uint8_t)(-w);
    }

    /*
     * Proprietary diagonal normalization:
     * X and Y are each multiplied by 181 and arithmetic-shifted by 8
     * when both axes are non-zero.
     */
    if ((int8_t)f75_mouse_report[1] != 0 &&
        (int8_t)f75_mouse_report[2] != 0) {

        f75_mouse_report[1] =
            (uint8_t)f75_signed_scale_181(
                (int8_t)f75_mouse_report[1]);

        f75_mouse_report[2] =
            (uint8_t)f75_signed_scale_181(
                (int8_t)f75_mouse_report[2]);
    }

    /*
     * Original also applies 181/256 scaling to non-zero wheel.
     * Unlike X/Y it does not force zero result to +1.
     */
    if ((int8_t)f75_mouse_report[4] != 0) {
        int16_t scaled =
            ((int16_t)(int8_t)f75_mouse_report[4] * 181) >> 8;

        f75_mouse_report[4] = (uint8_t)(int8_t)scaled;
    }
}

static bool boot_dirty = false;
static bool nkro_dirty = false;

static void mark_keyboard_dirty(void) {
    if (f75_nkro) {
        nkro_dirty = true;
    } else {
        boot_dirty = true;
    }
}

void bts_init(bts_info_t *info) {
    f75_bts_info = info;

    memset(boot_report, 0, sizeof(boot_report));
    memset(f75_nkro_bitmap, 0, sizeof(f75_nkro_bitmap));

    boot_dirty = false;
    nkro_dirty = false;

    if (f75_bts_info && f75_bts_info->uart_init) {
        f75_bts_info->uart_init(115200);
    }

    wb_bridge_init();
}

static void update_protocol_state(void) {
    if (!f75_bts_info) {
        return;
    }

    uint8_t event = wb_bridge_take_devctrl_event();

    switch (event) {
        case 0x21:
            f75_bts_info->bt_info.low_vol = true;
            f75_bts_info->bt_info.pvol = 10;
            break;

        case 0x22:
            f75_bts_info->bt_info.low_vol_offed = true;
            f75_bts_info->bt_info.normal_vol = false;
            f75_bts_info->bt_info.pvol = 10;
            break;

        case 0x23:
            f75_bts_info->bt_info.low_vol = false;
            f75_bts_info->bt_info.low_vol_offed = false;
            f75_bts_info->bt_info.normal_vol = true;
            wb_bridge_devctrl(0x53);
            break;

        case 0x31:
            f75_bts_info->bt_info.pairing = true;
            break;

        case 0x32:
            f75_bts_info->bt_info.pairing = false;
            f75_bts_info->bt_info.paired = true;
            break;

        case 0x33:
            f75_bts_info->bt_info.pairing = false;
            f75_bts_info->bt_info.paired = false;
            break;

        case 0x34:
            f75_bts_info->bt_info.mode_switched = true;
            break;

        case 0x35:
            f75_bts_info->bt_info.come_back = true;
            break;

        case 0x36:
            f75_bts_info->bt_info.come_back_err = true;
            break;

        case 0x42:
            f75_bts_info->bt_info.sleeped = false;
            break;

        default:
            break;
    }

    f75_bts_info->bt_info.pvol = wb_bridge_battery();
    f75_bts_info->bt_info.indictor_rgb_s = wb_bridge_indicator();
}

void bts_task(devs_t dev_state) {
    wb_bridge_task();

    update_protocol_state();

    if (dev_state == DEVS_USB) {
        return;
    }

    if (boot_dirty) {
        wb_bridge_keyboard(boot_report);
        boot_dirty = false;
    }

    if (nkro_dirty) {
        wb_bridge_nkro(f75_nkro_bitmap);
        nkro_dirty = false;
    }
}

bool bts_process_keys(uint16_t keycode,
                      bool pressed,
                      devs_t dev_state,
                      bool no_gui,
                      uint8_t num) {
    (void)dev_state;

    /*
     * Ordinary HID usages 0x04-0xA4.
     */
    if (keycode >= 4 && keycode <= 0xA4) {
        if (pressed) {
            bool already_present = false;

            for (uint8_t i = 2; i < num && i < sizeof(boot_report); i++) {
                if (boot_report[i] == keycode) {
                    already_present = true;
                    break;
                }
            }

            if (!already_present) {
                for (uint8_t i = 2; i < num && i < sizeof(boot_report); i++) {
                    if (boot_report[i] == 0) {
                        boot_report[i] = (uint8_t)keycode;
                        boot_dirty = true;
                        break;
                    }
                }
            }

            if (f75_nkro) {
                uint8_t byte_index = keycode >> 3;
                uint8_t bit_index  = keycode & 7;

                if (byte_index < sizeof(f75_nkro_bitmap)) {
                    f75_nkro_bitmap[byte_index] |=
                        (uint8_t)(1U << bit_index);
                    nkro_dirty = true;
                }
            }
        } else {
            for (uint8_t i = 2; i < num && i < sizeof(boot_report); i++) {
                if (boot_report[i] == keycode) {
                    boot_report[i] = 0;
                    boot_dirty = true;
                }
            }

            uint8_t byte_index = keycode >> 3;
            uint8_t bit_index  = keycode & 7;

            if (byte_index < sizeof(f75_nkro_bitmap)) {
                f75_nkro_bitmap[byte_index] &=
                    (uint8_t)~(1U << bit_index);
                nkro_dirty = true;
            }
        }

        /*
         * Original bts_process_keys returns false for handled keys.
         */
        return false;
    }

    /*
     * HID modifiers E0-E7.
     */
    if (keycode >= 0xE0 && keycode <= 0xE7) {
        uint8_t modifier =
            (uint8_t)(1U << (keycode - 0xE0));

        /*
         * Original no_gui suppression applies to LGUI press.
         */
        if (!(pressed && no_gui && keycode == 0xE3)) {
            if (pressed) {
                boot_report[0] |= modifier;
            } else {
                boot_report[0] &= (uint8_t)~modifier;
            }
        }

        boot_dirty = true;
        return false;
    }


    /*
     * Proprietary mouse pseudo-keycodes 0xCD-0xDF.
     *
     * report[0] = buttons
     * report[1] = X
     * report[2] = Y
     * report[4] = wheel
     *
     * 0xDD-0xDF select acceleration state 1/2/3.
     */
    if (keycode >= 0xCD && keycode <= 0xDF) {
        if (pressed) {
            int8_t xy =
                (int8_t)f75_c_offsets[f75_mouse_speed <= 3 ?
                                       f75_mouse_speed : 0];

            int8_t wheel =
                (int8_t)f75_w_offsets[f75_mouse_speed <= 3 ?
                                       f75_mouse_speed : 0];

            switch (keycode) {
                case 0xCD:
                    f75_mouse_report[2] = (uint8_t)(-xy);
                    break;

                case 0xCE:
                    f75_mouse_report[2] = (uint8_t)xy;
                    break;

                case 0xCF:
                    f75_mouse_report[1] = (uint8_t)(-xy);
                    break;

                case 0xD0:
                    f75_mouse_report[1] = (uint8_t)xy;
                    break;

                case 0xD1:
                case 0xD2:
                case 0xD3:
                case 0xD4:
                case 0xD5:
                case 0xD6:
                case 0xD7:
                case 0xD8:
                    f75_mouse_report[0] |=
                        (uint8_t)(1U << (keycode - 0xD1));
                    break;

                case 0xDB:
                    f75_mouse_report[4] = (uint8_t)(-wheel);
                    break;

                case 0xDC:
                    f75_mouse_report[4] = (uint8_t)wheel;
                    break;

                case 0xDD:
                    if (f75_mouse_speed != 1) {
                        f75_mouse_speed = 1;
                        f75_adjust_speed();
                    }
                    break;

                case 0xDE:
                    if (f75_mouse_speed != 2) {
                        f75_mouse_speed = 2;
                        f75_adjust_speed();
                    }
                    break;

                case 0xDF:
                    if (f75_mouse_speed != 3) {
                        f75_mouse_speed = 3;
                        f75_adjust_speed();
                    }
                    break;

                default:
                    break;
            }

            f75_send_mouse();
            return false;
        }

        switch (keycode) {
            case 0xCD:
                if ((int8_t)f75_mouse_report[2] < 0) {
                    f75_mouse_report[2] = 0;
                }
                break;

            case 0xCE:
                if ((int8_t)f75_mouse_report[2] > 0) {
                    f75_mouse_report[2] = 0;
                }
                break;

            case 0xCF:
                if ((int8_t)f75_mouse_report[1] < 0) {
                    f75_mouse_report[1] = 0;
                }
                break;

            case 0xD0:
                if ((int8_t)f75_mouse_report[1] > 0) {
                    f75_mouse_report[1] = 0;
                }
                break;

            case 0xD1:
            case 0xD2:
            case 0xD3:
            case 0xD4:
            case 0xD5:
            case 0xD6:
            case 0xD7:
            case 0xD8:
                f75_mouse_report[0] &=
                    (uint8_t)~(1U << (keycode - 0xD1));
                break;

            case 0xDB:
                if ((int8_t)f75_mouse_report[4] < 0) {
                    f75_mouse_report[4] = 0;
                }
                break;

            case 0xDC:
                if ((int8_t)f75_mouse_report[4] > 0) {
                    f75_mouse_report[4] = 0;
                }
                break;

            case 0xDD:
            case 0xDE:
            case 0xDF:
                if (f75_mouse_speed != 0) {
                    f75_mouse_speed = 0;
                    f75_adjust_speed();
                }
                break;

            default:
                break;
        }

        f75_send_mouse();
        return false;
    }

    /*
     * System control keys 0xA5-0xA7.
     *
     * Proprietary implementation stores these as three bits in its
     * 1-byte system_report_buf and queues report type 4.
     */
    if (keycode >= 0xA5 && keycode <= 0xA7) {
        uint8_t bit =
            (uint8_t)(1U << (keycode - 0xA5));

        if (pressed) {
            f75_system_report |= bit;
        } else {
            f75_system_report &= (uint8_t)~bit;
        }

        wb_bridge_system(f75_system_report);
        return false;
    }

    /*
     * Consumer keys 0xA8-0xC2.
     *
     * Exact 27-entry mapping recovered from proprietary
     * .rodata.CSWTCH.91.
     */
    if (keycode >= 0xA8 && keycode <= 0xC2) {
        uint16_t usage = 0;

        if (pressed) {
            usage = f75_consumer_usages[keycode - 0xA8];
        }

        wb_bridge_consumer(usage);
        return false;
    }

    /*
     * Mouse keys 0xCD-0xDF are intentionally handled in the next
     * equivalence step.
     *
     * Returning true matches the proprietary unhandled-key path.
     */
    return true;
}

bool bts_send_fn(bool pressed) {
    /*
     * Original sends 0x10 when pressed and 0x00 when released.
     */
    wb_bridge_fn(pressed); return true;
}

bool bts_send_name(devs_t host) {
    if (!f75_bts_info) {
        return false;
    }

    if (host < DEVS_HOST1 || host > DEVS_HOST5) {
        return false;
    }

    uint8_t index;

    switch (host) {
        case DEVS_HOST1: index = 0; break;
        case DEVS_HOST2: index = 1; break;
        case DEVS_HOST3: index = 2; break;
        case DEVS_HOST4: index = 3; break;
        case DEVS_HOST5: index = 4; break;
        default: return false;
    }

    const char *name = f75_bts_info->bt_name[index];

    if (!name) {
        return false;
    }

    wb_bridge_name(name); return true;
}

bool bts_send_vendor(vbs_t cmd) {
    wb_bridge_devctrl((uint8_t)cmd);
    return true;
}

bool bts_send_consumer(uint16_t usage) {
    wb_bridge_consumer(usage); return true;
}

bool bts_send_system(uint8_t usage) {
    wb_bridge_system(usage); return true;
}

bool bts_send_mouse_report(uint8_t *report) {
    if (!report) {
        return false;
    }

    wb_bridge_mouse(report); return true;
}

void bts_test_report_rate_task(void) {
}

char *bts_get_version(void) {
    return "open-westberry";
}

uint8_t bts_is_busy(void) {
    return wb_bridge_busy() ? 1 : 0;
}

void bts_set_nkro(bool enabled) {
    if (f75_nkro == enabled) {
        return;
    }

    f75_nkro = enabled;

    /*
     * Force the newly selected report representation to be sent.
     */
    mark_keyboard_dirty();
}

bool bts_get_nkro(void) {
    return f75_nkro;
}
