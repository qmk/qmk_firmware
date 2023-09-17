/* Copyright 2015-2017 Jack Humbert
 *           2020 Niclas Meyer
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

#include QMK_KEYBOARD_H

#define K(kc) (1ull<<((kc) - ALPHA))

#define KALPHA   K(ALPHA)
#define KBETA    K(BETA)
#define KGAMMA   K(GAMMA)
#define KDELTA   K(DELTA)
#define KEPSILON K(EPSILON)
#define KZETA    K(ZETA)
#define KTHETA   K(THETA)
#define KIOTA    K(IOTA)
#define KKAPPA   K(KAPPA)

enum keys {
    ALPHA = SAFE_RANGE,
    BETA,
    GAMMA,
    DELTA,
    EPSILON,
    ZETA,
    THETA,
    IOTA,
    KAPPA,
    LOCK,
    NONE,
};

enum layers {
    NORMAL,
    QWERTY,
    GAME,
    LOWER,
    RAISE,
    PHI,
    FN,
};

#define XXXX KC_NO
#define ____ KC_TRNS

#define CQWER LM(QWERTY, MOD_LCTL)
#define AQWER LM(QWERTY, MOD_LALT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [NORMAL] = LAYOUT_planck_grid(
        ALPHA,   BETA,  GAMMA, DELTA,  ____,  ____, ____, ____,  DELTA,  GAMMA, BETA, ALPHA,
        EPSILON, ZETA,  THETA, IOTA,   ____,  ____, ____, ____,  IOTA,   THETA, ZETA, EPSILON,
        ____,    ____,  ____,  ____,   ____,  ____, ____, ____,  ____,   ____, ____,  ____,
        MO(PHI), CQWER, AQWER, MO(FN), KAPPA, ____, XXXX, KAPPA, MO(FN), ____, ____,  MO(PHI)
    ),
    [QWERTY] = LAYOUT_planck_grid(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,      KC_T,   KC_Y, KC_U,      KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,      KC_G,   KC_H, KC_J,      KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,      KC_B,   KC_N, KC_M,      KC_COMM, KC_DOT,  KC_SLSH, SC_SENT,
        MO(PHI), KC_LCTL, KC_LALT, KC_LGUI, MO(LOWER), KC_SPC, XXXX, MO(RAISE), KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT
    ),
    [GAME] = LAYOUT_planck_grid(
        KC_ESC,  KC_1, KC_2, KC_3, KC_4,   KC_5, KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_BSPC,
        KC_TAB,  KC_Q, KC_W, KC_E, KC_R,   KC_T, KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_QUOT,
        KC_LSFT, KC_A, KC_S, KC_D, KC_F,   KC_G, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_ENT,
        KC_LCTL, KC_Z, KC_X, KC_C, KC_SPC, ____, XXXX, ____, KC_V,    KC_B,   ____,    MO(PHI)
    ),
    [LOWER] = LAYOUT_planck_grid(
        KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
        KC_DEL,  ____,    ____,   ____,    ____,  ____,    ____,    KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
        ____,    ____,    ____,   ____,    ____,  ____,    ____,    KC_PGUP, KC_PGDN, KC_HOME, KC_END,  ____,
        ____,    ____,    ____,   ____,    ____,  ____,    XXXX,    ____,    KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
    ),
    [RAISE] = LAYOUT_planck_grid(
        KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
        KC_DEL, ____, ____, ____, ____, ____, ____, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
        ____,   ____, ____, ____, ____, ____, ____, KC_PGUP,  KC_PGDN, KC_HOME, KC_END, ____,
        ____,   ____, ____, ____, ____, ____, XXXX, ____,    KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
    ),
    [PHI] = LAYOUT_planck_grid(
        QK_BOOT, KC_F1,   KC_F2,   KC_F3,  KC_F4,  ____, ____, ____,       ____,       ____,     ____,    KC_DEL,
        ____,  KC_F5,   KC_F6,   KC_F7,  KC_F8,  ____, ____, DF(QWERTY), DF(NORMAL), DF(GAME), ____,    KC_F13,
        ____,  KC_F9,   KC_F10,  KC_F11, KC_F12, ____, ____, ____,       ____,       ____,     ____,    ____,
        ____,  RGB_TOG, RGB_MOD, ____,   ____,   ____, XXXX, ____,       KC_MNXT,    KC_VOLD,  KC_VOLU, KC_MPLY
    ),
    [FN] = LAYOUT_planck_grid(
        ____,    ____,    KC_UP,   ____,     ____, ____, ____, ____, ____,    KC_UP,   ____,     ____,
        KC_DEL,  KC_LEFT, KC_DOWN, KC_RIGHT, ____, ____, ____, ____, KC_LEFT, KC_DOWN, KC_RIGHT, KC_DEL,
        KC_HOME, KC_END,  KC_PGUP, KC_PGDN,  ____, ____, ____, ____, KC_PGDN, KC_PGUP, KC_HOME,  KC_END,
        ____,    ____,    ____,    ____,     ____, ____, XXXX, ____, ____,    ____,    ____,     ____
    ),
};

static uint16_t left_chord = 0;
static uint16_t right_chord = 0;

static bool locking = false;
static bool locked = false;
static uint16_t mods = 0;

#define PROCESS_MOD(mod)                                 \
    do {                                                 \
        if ((mods & MOD_##mod) && !(keys & MOD_##mod)) { \
            unregister_code16(KC_##mod);                 \
        }                                                \
        if (!(mods & MOD_##mod) && (keys & MOD_##mod)) { \
            register_code16(KC_##mod);                   \
        }                                                \
    } while (0)

static void process_keys(uint16_t keys) {
    if (keys == NONE) {
        return;
    }

    if (keys == LOCK) {
        locking = !locking;
        return;
    }

    if ((keys & QK_ONE_SHOT_MOD) == QK_ONE_SHOT_MOD) {
        PROCESS_MOD(LCTL);
        PROCESS_MOD(LSFT);
        PROCESS_MOD(LALT);
        PROCESS_MOD(LGUI);

        mods = keys & ~QK_ONE_SHOT_MOD;
        locked = false;

        if (locking) {
            locking = false;
            locked  = true;
        }

        return;
    }

    // Normal key
    tap_code16(keys);
    locking = false;

    if (mods && !locked) {
        if (mods & MOD_LCTL) {
            unregister_code16(KC_LCTL);
        }

        if (mods & MOD_LSFT) {
            unregister_code16(KC_LSFT);
        }

        if (mods & MOD_LALT) {
            unregister_code16(KC_LALT);
        }

        if (mods & MOD_LGUI) {
            unregister_code16(KC_LGUI);
        }

        mods = 0;
    }
}

static uint16_t chord_to_keys(uint16_t chord) {
    switch (chord) {
        // Unshifted Extra
        case KKAPPA:                            return KC_SPC;
        case KEPSILON | KZETA | KTHETA | KIOTA: return KC_ENT;
        case KEPSILON | KZETA | KGAMMA | KIOTA: return KC_TAB;
        case KEPSILON | KIOTA:                  return KC_BSPC;
        case KKAPPA | KEPSILON:                 return KC_ESC;

        // Shifted Extra
        case KKAPPA | KEPSILON | KZETA | KTHETA | KIOTA: return S(KC_ENT);
        case KKAPPA | KEPSILON | KZETA | KGAMMA | KIOTA: return S(KC_TAB);
        case KKAPPA | KEPSILON | KIOTA:                  return S(KC_BSPC);

        // Lowercase Letters
        case KBETA:                   return KC_A;
        case KZETA | KDELTA:          return KC_B;
        case KBETA | KGAMMA | KDELTA: return KC_C;
        case KZETA | KTHETA | KIOTA:  return KC_D;
        case KDELTA:                  return KC_E;
        case KGAMMA | KIOTA:          return KC_F;
        case KBETA | KTHETA:          return KC_G;
        case KZETA | KTHETA:          return KC_H;
        case KGAMMA:                  return KC_I;
        case KBETA | KGAMMA | KIOTA:  return KC_J;
        case KBETA | KTHETA | KIOTA:  return KC_K;
        case KBETA | KGAMMA:          return KC_L;
        case KBETA | KDELTA:          return KC_M;
        case KZETA:                   return KC_N;
        case KTHETA:                  return KC_O;
        case KZETA | KGAMMA:          return KC_P;
        case KBETA | KTHETA | KDELTA: return KC_Q;
        case KGAMMA | KDELTA:         return KC_R;
        case KTHETA | KIOTA:          return KC_S;
        case KIOTA:                   return KC_T;
        case KZETA | KIOTA:           return KC_U;
        case KTHETA | KDELTA:         return KC_V;
        case KZETA | KGAMMA | KIOTA:  return KC_W;
        case KZETA | KTHETA | KDELTA: return KC_X;
        case KBETA | KIOTA:           return KC_Y;
        case KZETA | KGAMMA | KDELTA: return KC_Z;

        // Uppercase Letters
        case KKAPPA | KBETA:                   return S(KC_A);
        case KKAPPA | KZETA | KDELTA:          return S(KC_B);
        case KKAPPA | KBETA | KGAMMA | KDELTA: return S(KC_C);
        case KKAPPA | KZETA | KTHETA | KIOTA:  return S(KC_D);
        case KKAPPA | KDELTA:                  return S(KC_E);
        case KKAPPA | KGAMMA | KIOTA:          return S(KC_F);
        case KKAPPA | KBETA | KTHETA:          return S(KC_G);
        case KKAPPA | KZETA | KTHETA:          return S(KC_H);
        case KKAPPA | KGAMMA:                  return S(KC_I);
        case KKAPPA | KBETA | KGAMMA | KIOTA:  return S(KC_J);
        case KKAPPA | KBETA | KTHETA | KIOTA:  return S(KC_K);
        case KKAPPA | KBETA | KGAMMA:          return S(KC_L);
        case KKAPPA | KBETA | KDELTA:          return S(KC_M);
        case KKAPPA | KZETA:                   return S(KC_N);
        case KKAPPA | KTHETA:                  return S(KC_O);
        case KKAPPA | KZETA | KGAMMA:          return S(KC_P);
        case KKAPPA | KBETA | KTHETA | KDELTA: return S(KC_Q);
        case KKAPPA | KGAMMA | KDELTA:         return S(KC_R);
        case KKAPPA | KTHETA | KIOTA:          return S(KC_S);
        case KKAPPA | KIOTA:                   return S(KC_T);
        case KKAPPA | KZETA | KIOTA:           return S(KC_U);
        case KKAPPA | KTHETA | KDELTA:         return S(KC_V);
        case KKAPPA | KZETA | KGAMMA | KIOTA:  return S(KC_W);
        case KKAPPA | KZETA | KTHETA | KDELTA: return S(KC_X);
        case KKAPPA | KBETA | KIOTA:           return S(KC_Y);
        case KKAPPA | KZETA | KGAMMA | KDELTA: return S(KC_Z);

        // Unshifted Numbers
        case KEPSILON | KZETA:                  return KC_0;
        case KEPSILON | KZETA | KIOTA:          return KC_1;
        case KEPSILON | KZETA | KTHETA:         return KC_2;
        case KEPSILON | KBETA:                  return KC_3;
        case KEPSILON | KBETA | KDELTA:         return KC_4;
        case KEPSILON | KBETA | KGAMMA:         return KC_5;
        case KEPSILON | KBETA | KIOTA:          return KC_6;
        case KEPSILON | KTHETA:                 return KC_7;
        case KEPSILON | KBETA | KGAMMA | KIOTA: return KC_8;
        case KEPSILON | KGAMMA | KDELTA:        return KC_9;

        // Shifted Numbers
        case KKAPPA | KEPSILON | KZETA | KIOTA:          return KC_EXLM;
        case KKAPPA | KEPSILON | KZETA | KTHETA:         return KC_AT;
        case KKAPPA | KEPSILON | KBETA:                  return KC_HASH;
        case KKAPPA | KEPSILON | KBETA | KDELTA:         return KC_DLR;
        case KKAPPA | KEPSILON | KBETA | KGAMMA:         return KC_PERC;
        case KKAPPA | KEPSILON | KBETA | KIOTA:          return KC_CIRC;
        case KKAPPA | KEPSILON | KTHETA:                 return KC_AMPR;
        case KKAPPA | KEPSILON | KBETA | KGAMMA | KIOTA: return KC_ASTR;
        case KKAPPA | KEPSILON | KGAMMA | KDELTA:        return KC_LPRN;
        case KKAPPA | KEPSILON | KZETA:                  return KC_RPRN;

        // Unshifted Symbols
        case KEPSILON | KBETA | KTHETA | KIOTA:  return KC_MINS;
        case KEPSILON | KZETA | KTHETA | KDELTA: return KC_EQL;
        case KEPSILON | KZETA | KGAMMA:          return KC_LBRC;
        case KEPSILON | KGAMMA | KIOTA:          return KC_RBRC;
        case KEPSILON | KBETA | KTHETA:          return KC_BSLS;
        case KEPSILON | KBETA | KGAMMA | KDELTA: return KC_SCLN;
        case KEPSILON | KZETA | KDELTA:          return KC_QUOT;
        case KEPSILON | KTHETA | KIOTA:          return KC_COMM;
        case KEPSILON | KZETA | KGAMMA | KDELTA: return KC_DOT;
        case KEPSILON | KGAMMA:                  return KC_SLSH;
        case KEPSILON | KDELTA:                  return KC_GRV;

        // Shifted Symbols
        case KKAPPA | KEPSILON | KBETA | KTHETA | KIOTA:  return KC_UNDS;
        case KKAPPA | KEPSILON | KZETA | KTHETA | KDELTA: return KC_PLUS;
        case KKAPPA | KEPSILON | KZETA | KGAMMA:          return KC_LCBR;
        case KKAPPA | KEPSILON | KGAMMA | KIOTA:          return KC_RCBR;
        case KKAPPA | KEPSILON | KBETA | KTHETA:          return KC_PIPE;
        case KKAPPA | KEPSILON | KBETA | KGAMMA | KDELTA: return KC_COLN;
        case KKAPPA | KEPSILON | KZETA | KDELTA:          return KC_DQT;
        case KKAPPA | KEPSILON | KTHETA | KIOTA:          return KC_LT;
        case KKAPPA | KEPSILON | KZETA | KGAMMA | KDELTA: return KC_GT;
        case KKAPPA | KEPSILON | KGAMMA:                  return KC_QUES;
        case KKAPPA | KEPSILON | KDELTA:                  return KC_TILD;

        // Modifiers
        case KALPHA | KIOTA: return LOCK;

        case KALPHA: return QK_ONE_SHOT_MOD; // Release all

        case KALPHA | KBETA:  return OSM(MOD_LCTL);
        case KALPHA | KGAMMA: return OSM(MOD_LSFT);
        case KALPHA | KDELTA: return OSM(MOD_LALT);
        case KALPHA | KKAPPA: return OSM(MOD_LGUI);

        case KALPHA | KBETA | KGAMMA:  return OSM(MOD_LCTL | MOD_LSFT);
        case KALPHA | KBETA | KDELTA:  return OSM(MOD_LCTL | MOD_LALT);
        case KALPHA | KBETA | KKAPPA:  return OSM(MOD_LCTL | MOD_LGUI);
        case KALPHA | KGAMMA | KDELTA: return OSM(MOD_LSFT | MOD_LALT);
        case KALPHA | KGAMMA | KKAPPA: return OSM(MOD_LSFT | MOD_LGUI);
        case KALPHA | KDELTA | KKAPPA: return OSM(MOD_LALT | MOD_LGUI);

        case KALPHA | KBETA | KGAMMA | KDELTA:  return OSM(MOD_LCTL | MOD_LSFT | MOD_LALT);
        case KALPHA | KBETA | KGAMMA | KKAPPA:  return OSM(MOD_LCTL | MOD_LSFT | MOD_LGUI);
        case KALPHA | KBETA | KDELTA | KKAPPA:  return OSM(MOD_LCTL | MOD_LALT | MOD_LGUI);
        case KALPHA | KGAMMA | KDELTA | KKAPPA: return OSM(MOD_LSFT | MOD_LALT | MOD_LGUI);

        case KALPHA | KBETA | KGAMMA | KDELTA | KKAPPA: return OSM(MOD_LCTL | MOD_LSFT | MOD_LALT | MOD_LGUI);
    }

    return NONE;
}

static uint16_t *get_hand(keypos_t *key) {
    if (key->row <= 3) {
        return &left_chord;
    }

    if (key->row <= 6) {
        return &right_chord;
    }

    // row 7
    if (key->col <= 2) {
        return &right_chord;
    } else {
        return &left_chord;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode < ALPHA) {
        return true;
    }

    uint16_t *chord = get_hand(&record->event.key);

    if (record->event.pressed) {
        *chord |= K(keycode);
        return false;
    }

    if (*chord != 0) {
        process_keys(chord_to_keys(*chord));
        *chord = 0;
    }

    return false;
}

#ifdef KEYBOARD_planck_ez

#define LED_BRIGHTNESS 50

layer_state_t default_layer_state_set_user(layer_state_t state) {
    switch (state) {
        case 1U << NORMAL:
            planck_ez_left_led_off();
            planck_ez_right_led_off();
            break;
        case 1U << QWERTY:
            planck_ez_left_led_level(LED_BRIGHTNESS);
            planck_ez_right_led_off();
            break;
        case 1U << GAME:
            planck_ez_left_led_off();
            planck_ez_right_led_level(LED_BRIGHTNESS);
            break;
    }

    return state;
}

#endif /* KEYBOARD_planck_ez */
