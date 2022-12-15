/* Copyright 2019-2021 Konstantin Đorđević <vomindoraan@gmail.com>
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

#include "tap_dance.h"
#include "konstantin.h"

#define ACTION_TAP_DANCE_DOUBLE_MOD(mod1, mod2) {                       \
        .fn        = { td_double_mod_each, NULL, td_double_mod_reset }, \
        .user_data = &(tap_dance_pair_t){ mod1, mod2 },              \
    }

void td_double_mod_each(tap_dance_state_t *state, void *user_data) {
    tap_dance_pair_t *data = (tap_dance_pair_t *)user_data;

    // Single tap → mod1, double tap → mod2, triple tap etc. → mod1+mod2
    if (state->count == 1 || state->count == 3) {
        register_code(data->kc1);
    } else if (state->count == 2) {
        unregister_code(data->kc1);
        register_code(data->kc2);
    }
    // Prevent tap dance from sending the mods as weak mods
    state->weak_mods &= ~(MOD_BIT(data->kc1) | MOD_BIT(data->kc2));
}

void td_double_mod_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_pair_t *data = (tap_dance_pair_t *)user_data;

    if (state->count == 1 || state->count >= 3) {
        unregister_code(data->kc1);
    }
    if (state->count >= 2) {
        unregister_code(data->kc2);
    }
}

#define ACTION_TAP_DANCE_MOD_LAYER(mod, layer) {                      \
        .fn        = { td_mod_layer_each, NULL, td_mod_layer_reset }, \
        .user_data = &(tap_dance_dual_role_t){ mod, layer },       \
    }

void td_mod_layer_each(tap_dance_state_t *state, void *user_data) {
    tap_dance_dual_role_t *data = (tap_dance_dual_role_t *)user_data;

    // Single tap → mod, double tap → layer, triple tap etc. → mod+layer
    if (state->count == 1 || state->count == 3) {
        register_code(data->kc);
    } else if (state->count == 2) {
        unregister_code(data->kc);
        // Prevent tap dance from sending the mod as a weak mod
        state->weak_mods &= ~MOD_BIT(data->kc);
        layer_on(data->layer);
    }
}

void td_mod_layer_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_dual_role_t *data = (tap_dance_dual_role_t *)user_data;

    if (state->count == 1 || state->count >= 3) {
        unregister_code(data->kc);
    }
    if (state->count >= 2) {
        layer_off(data->layer);
    }
}

#define ACTION_TAP_DANCE_LAYER_MOD(layer, mod) {                      \
        .fn        = { td_layer_mod_each, NULL, td_layer_mod_reset }, \
        .user_data = &(tap_dance_layer_mod_t){ layer, mod, 0, 0 }, \
    }

typedef struct {
    uint8_t  layer;
    uint16_t kc;
    bool     layer_on;  // Layer state when tap dance started
    bool     started;
} tap_dance_layer_mod_t;

void td_layer_mod_each(tap_dance_state_t *state, void *user_data) {
    tap_dance_layer_mod_t *data = (tap_dance_layer_mod_t *)user_data;
    if (!data->started) {
        data->layer_on = IS_LAYER_ON(data->layer);
        data->started = true;
    }

    // Single tap → layer, double tap → mod, triple tap etc. → layer+mod
    if (state->count == 1 || state->count == 3) {
        layer_on(data->layer);
    } else if (state->count == 2) {
        if (!data->layer_on) {
            layer_off(data->layer);
        }
        register_code(data->kc);
    }
}

void td_layer_mod_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_layer_mod_t *data = (tap_dance_layer_mod_t *)user_data;

    if ((state->count == 1 || state->count >= 3) && !data->layer_on) {
        layer_off(data->layer);
    }
    if (state->count >= 2) {
        unregister_code(data->kc);
    }

    data->started = false;
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_DST_A_R] = ACTION_TAP_DANCE_DOUBLE(DST_ADD, DST_REM),

    [TD_RAL_RGU] = ACTION_TAP_DANCE_DOUBLE_MOD(KC_RALT, KC_RGUI),
    [TD_RCT_RSF] = ACTION_TAP_DANCE_DOUBLE_MOD(KC_RCTL, KC_RSFT),
    [TD_RSF_RCT] = ACTION_TAP_DANCE_DOUBLE_MOD(KC_RSFT, KC_RCTL),

#ifdef LAYER_FN
    [TD_LSFT_FN] = ACTION_TAP_DANCE_MOD_LAYER(KC_LSFT, L_FN),
    [TD_RCTL_FN] = ACTION_TAP_DANCE_MOD_LAYER(KC_RCTL, L_FN),
    [TD_FN_RCTL] = ACTION_TAP_DANCE_LAYER_MOD(L_FN, KC_RCTL),
#endif
};
