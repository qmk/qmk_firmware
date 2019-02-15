/*
Copyright 2019 Batuhan Başerdem <baserdem.batuhan@gmail.com> @bbaserdem
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
#include "tap_dances.h"

void d_num_gam_dn (qk_tap_dance_state_t *state, void *user_data) {
    layer_off(_GA);
    if (state->count == 1) {
        layer_on  (_NU);
    } else if (state->count == 2) {
        layer_off (_NU);
        layer_on  (_GA);
    } else {
        layer_off (_GA);
    }
}

void d_num_gam_up (qk_tap_dance_state_t *state, void *user_data) {
    layer_off (_NU);
}

void d_set_mou_dn (qk_tap_dance_state_t *state, void *user_data) {
    if ( userspace_config.lock_flag ) {
        userspace_config.lock_flag = false;
    } else {
        if (state->count == 1) {
            layer_off (_MO);
            layer_on  (_SE);
        } else if (state->count == 2) {
            layer_off (_SE);
            layer_on  (_MO);
        } else {
            layer_off (_MO);
        }
    }
}

void d_set_mou_up (qk_tap_dance_state_t *state, void *user_data) {
    if ( !userspace_config.lock_flag ) {
        layer_off (_SE);
        layer_off (_MO);
    }
}

void bigswitch_fin (qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1: // Send LGUI + ESC
            register_code(KC_LGUI);
            register_code(KC_ESC);
            break;
#ifdef RGBLIGHT_ENABLE
        case 2: // Change RGB mode
            rgblight_increase();
            break;
        case 3: // Change RGB hue
            rgblight_increase_hue();
            break;
        case 4: // Toggle RGB
            rgblight_toggle();
            break;
#endif
        case 5:
            register_code(KC_POWER);
            break;
    }
}

void bigswitch_res (qk_tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1: // Send LGUI + ESC
            unregister_code(KC_ESC);
            unregister_code(KC_LGUI);
            break;
        case 5:
            unregister_code(KC_POWER);
            break;
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [NUG] = ACTION_TAP_DANCE_FN_ADVANCED (d_num_gam_dn,NULL,d_num_gam_up),
  [SEM] = ACTION_TAP_DANCE_FN_ADVANCED (d_set_mou_dn,NULL,d_set_mou_up),
  [BIG] = ACTION_TAP_DANCE_FN_ADVANCED (NULL,bigswitch_fin,bigswitch_res)
};
