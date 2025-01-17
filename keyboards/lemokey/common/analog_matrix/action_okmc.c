/* Copyright 2024 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "quantum.h"
#include "analog_matrix.h"
#include "profile.h"

// OKMC action type
enum {
    OKMC_ACTION_RELEASE  = 0b001,
    OKMC_ACTION_PRESS    = 0b010,
    OKMC_ACTION_TAP      = 0b110,
    OKMC_ACTION_RE_PRESS = 0b111,
};

enum {
    OKMC_RELEASED = AKS_REGULAR_RELEASED,
    OKMC_SHALLOW_ACTUATED,
    OKMC_DEEP_ACTUATED,
    OKMC_DEEP_DEACT_READY,
    OKMC_DEEP_DEACTUATED,
    OKMC_MAX,
};

matrix_row_t okmc_matrix[MATRIX_ROWS] = {0};

static void report_action(bool add, uint16_t keycode) {
    if (add) {
        if (IS_BASIC_KEYCODE(keycode)) {
            if (!is_key_pressed(keycode)) {
                add_key(keycode);
            }
        } else if (IS_MODIFIER_KEYCODE(keycode)) {
            add_mods(MOD_BIT(keycode));
        }
    } else {
        if (IS_BASIC_KEYCODE(keycode)) {
            if (is_key_pressed(keycode)) {
                del_key(keycode);
            }
        } else if (IS_MODIFIER_KEYCODE(keycode)) {
            del_mods(MOD_BIT(keycode));
        }
    }
}

static void release_okmc_keys(okmc_config_t *okmc) {
    // Relase all keys in the OKMC settings
    for (uint8_t i = 0; i < 4; ++i) {
        if (okmc->keycode[i]) {
            report_action(0, okmc->keycode[i]);
        }
    }
    send_keyboard_report();
}

static void inline shallow_actuate(okmc_config_t *okmc) {
    bool any_action;

    for (uint8_t bit = 0; bit < 3; bit++) {
        any_action = false;

        for (uint8_t i = 0; i < 4; ++i) {
            if (okmc->keycode[i] && (okmc->action[i].shallow_act & (0x01 << bit))) {
                report_action(bit % 2, okmc->keycode[i]);
                any_action = true;
            }
        }
        if (any_action) {
            send_keyboard_report();
            wait_ms(1);
        }
    }
}

static void inline shallow_deactuate(okmc_config_t *okmc) {
    bool any_action;

    for (uint8_t bit = 0; bit < 3; bit++) {
        any_action = false;

        for (uint8_t i = 0; i < 4; ++i) {
            if (okmc->keycode[i] && (okmc->action[i].shallow_deact & (0x01 << bit))) {
                report_action(bit % 2, okmc->keycode[i]);
                any_action = true;
            }
        }
        if (any_action) {
            send_keyboard_report();
            wait_ms(1);
        }
    }

    send_keyboard_report();
    release_okmc_keys(okmc);
}

static void inline deep_actuate(okmc_config_t *okmc) {
    bool any_action;

    for (uint8_t bit = 0; bit < 3; bit++) {
        any_action = false;

        for (uint8_t i = 0; i < 4; ++i) {
            if (okmc->keycode[i] && (okmc->action[i].deep_act & (0x01 << bit))) {
                report_action(bit % 2, okmc->keycode[i]);
                any_action = true;
            }
        }
        if (any_action) {
            send_keyboard_report();
            wait_ms(1);
        }
    }
}

static void inline deep_deactuate(okmc_config_t *okmc) {
    bool any_action;

    for (uint8_t bit = 0; bit < 3; bit++) {
        any_action = false;

        for (uint8_t i = 0; i < 4; ++i) {
            if (okmc->keycode[i] && (okmc->action[i].deep_deact & (0x01 << bit))) {
                report_action(bit % 2, okmc->keycode[i]);
                any_action = true;
            }
        }
        if (any_action) {
            send_keyboard_report();
            wait_ms(1);
        }
    }
}

bool okmc_action(analog_key_t *key) {
    bool                     changed    = false;
    analog_matrix_profile_t *cur_prof   = profile_get_current();
    okmc_traval_config_t    *travel_cfg = &cur_prof->okmc[key->okmc_idx].travel;

    switch (key->state) {
        case OKMC_RELEASED:
            // Check shallow actuation
            if (key->travel >= travel_cfg->shallow_act * TRAVEL_SCALE) {
                key->state = OKMC_SHALLOW_ACTUATED;
                shallow_actuate(&cur_prof->okmc[key->okmc_idx]);
                changed = true;
            }
            break;

        case OKMC_SHALLOW_ACTUATED:
            // Key releasing
            if (key->travel < travel_cfg->shallow_deact * TRAVEL_SCALE && key->travel < (travel_cfg->shallow_act - 1) * TRAVEL_SCALE) {
                key->state = OKMC_RELEASED;
                release_okmc_keys(&cur_prof->okmc[key->okmc_idx]);
                changed = true;
            }
            // Continue pressing
            else if (key->travel >= travel_cfg->deep_act * TRAVEL_SCALE) {
                key->state = OKMC_DEEP_ACTUATED;
                deep_actuate(&cur_prof->okmc[key->okmc_idx]);
                changed = true;
            }
            break;

        case OKMC_DEEP_ACTUATED:
            if (key->travel > travel_cfg->deep_deact * TRAVEL_SCALE) {
                key->state = OKMC_DEEP_DEACT_READY; // make su
            } else if (key->travel < travel_cfg->shallow_deact * TRAVEL_SCALE && key->travel < (travel_cfg->shallow_act - 1) * TRAVEL_SCALE) {
                key->state = OKMC_RELEASED;
                release_okmc_keys(&cur_prof->okmc[key->okmc_idx]);
                changed = true;
            }
            break;

        case OKMC_DEEP_DEACT_READY:
            if (key->travel <= travel_cfg->deep_deact * TRAVEL_SCALE) {
                key->state = OKMC_DEEP_DEACTUATED;
                deep_deactuate(&cur_prof->okmc[key->okmc_idx]);
                changed = true;
            }
            break;

        case OKMC_DEEP_DEACTUATED:
            // If we miss the deep deacuation point
            if (key->travel <= travel_cfg->shallow_deact * TRAVEL_SCALE && key->travel < (travel_cfg->shallow_act - 1) * TRAVEL_SCALE) {
                key->state = OKMC_RELEASED;
                shallow_deactuate(&cur_prof->okmc[key->okmc_idx]);
                changed = true;
            }
            break;

        default:
            break;
    }

    if (changed) {
        if (key->state >= OKMC_SHALLOW_ACTUATED && key->state <= OKMC_DEEP_DEACT_READY)
            okmc_matrix[key->r] |= 0x01 << key->c;
        else
            okmc_matrix[key->r] &= ~(0x01 << key->c);
    }

    return changed;
}
