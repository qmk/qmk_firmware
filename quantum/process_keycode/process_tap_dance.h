/* Copyright 2016 Jack Humbert
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

#pragma once

#ifdef TAP_DANCE_ENABLE

#    include <stdbool.h>
#    include <inttypes.h>

typedef struct {
    uint16_t interrupting_keycode;
    uint8_t  count;
    uint8_t  weak_mods;
#    ifndef NO_ACTION_ONESHOT
    uint8_t oneshot_mods;
#    endif
    bool pressed : 1;
    bool finished : 1;
    bool interrupted : 1;
} tap_dance_state_t;

typedef void (*tap_dance_user_fn_t)(tap_dance_state_t *state, void *user_data);

typedef struct {
    tap_dance_state_t state;
    struct {
        tap_dance_user_fn_t on_each_tap;
        tap_dance_user_fn_t on_dance_finished;
        tap_dance_user_fn_t on_reset;
    } fn;
    void *user_data;
} tap_dance_action_t;

typedef struct {
    uint16_t kc1;
    uint16_t kc2;
} tap_dance_pair_t;

typedef struct {
    uint16_t kc;
    uint8_t  layer;
    void (*layer_function)(uint8_t);
} tap_dance_dual_role_t;

#    define ACTION_TAP_DANCE_DOUBLE(kc1, kc2) \
        { .fn = {tap_dance_pair_on_each_tap, tap_dance_pair_finished, tap_dance_pair_reset}, .user_data = (void *)&((tap_dance_pair_t){kc1, kc2}), }

#    define ACTION_TAP_DANCE_LAYER_MOVE(kc, layer) \
        { .fn = {tap_dance_dual_role_on_each_tap, tap_dance_dual_role_finished, tap_dance_dual_role_reset}, .user_data = (void *)&((tap_dance_dual_role_t){kc, layer, layer_move}), }

#    define ACTION_TAP_DANCE_LAYER_TOGGLE(kc, layer) \
        { .fn = {NULL, tap_dance_dual_role_finished, tap_dance_dual_role_reset}, .user_data = (void *)&((tap_dance_dual_role_t){kc, layer, layer_invert}), }

#    define ACTION_TAP_DANCE_FN(user_fn) \
        { .fn = {NULL, user_fn, NULL}, .user_data = NULL, }

#    define ACTION_TAP_DANCE_FN_ADVANCED(user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset) \
        { .fn = {user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset}, .user_data = NULL, }

#    define TD(n) (QK_TAP_DANCE | TD_INDEX(n))
#    define TD_INDEX(code) ((code)&0xFF)
#    define TAP_DANCE_KEYCODE(state) TD(((tap_dance_action_t *)state) - tap_dance_actions)

extern tap_dance_action_t tap_dance_actions[];

void reset_tap_dance(tap_dance_state_t *state);

/* To be used internally */

bool preprocess_tap_dance(uint16_t keycode, keyrecord_t *record);
bool process_tap_dance(uint16_t keycode, keyrecord_t *record);
void tap_dance_task(void);

void tap_dance_pair_on_each_tap(tap_dance_state_t *state, void *user_data);
void tap_dance_pair_finished(tap_dance_state_t *state, void *user_data);
void tap_dance_pair_reset(tap_dance_state_t *state, void *user_data);

void tap_dance_dual_role_on_each_tap(tap_dance_state_t *state, void *user_data);
void tap_dance_dual_role_finished(tap_dance_state_t *state, void *user_data);
void tap_dance_dual_role_reset(tap_dance_state_t *state, void *user_data);

#else

#    define TD(n) KC_NO

#endif
