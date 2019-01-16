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
    userspace_config.lock_flag = false;
    if (state->count == 1) {
        layer_on  (_NU);
    } else if (state->count == 2) {
        layer_off (_NU);
        layer_on  (_GA);
        userspace_config.lock_flag = true;
    } else {
        layer_off (_GA);
        userspace_config.lock_flag = false;
    }
}

void d_num_gam_up (qk_tap_dance_state_t *state, void *user_data) {
    if ( userspace_config.lock_flag ) {
        userspace_config.lock_flag = false;
    } else {
        layer_off (_NU);
        layer_off (_GA);
    }
}

void d_set_mou_dn (qk_tap_dance_state_t *state, void *user_data) {
    userspace_config.lock_flag = false;
    if (state->count == 1) {
        layer_on  (_SE);
    } else if (state->count == 2) {
        layer_off (_SE);
        layer_on  (_MO);
    } else {
        layer_off (_MO);
    }
}

void d_set_mou_up (qk_tap_dance_state_t *state, void *user_data) {
    if ( userspace_config.lock_flag ) {
        userspace_config.lock_flag = false;
    } else {
        if (state->count == 1) {
            layer_off (_SE);
        } else if (state->count == 2) {
            layer_off (_MO);
        }
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [NUG] = ACTION_TAP_DANCE_FN_ADVANCED (d_num_gam_dn,NULL,d_num_gam_up),
  [SEM] = ACTION_TAP_DANCE_FN_ADVANCED (d_set_mou_dn,NULL,d_set_mou_up)
};
