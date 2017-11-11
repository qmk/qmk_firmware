#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define USB_MAX_POWER_CONSUMPTION 100
#define ONESHOT_TAP_TOGGLE        2
#define ONESHOT_TIMEOUT           3000

#define MOUSEKEY_INTERVAL         20
#define MOUSEKEY_DELAY            0
#define MOUSEKEY_TIME_TO_MAX      40
#define MOUSEKEY_MAX_SPEED        7
#define MOUSEKEY_WHEEL_DELAY      0

// dynamic macro keys
#define DM_PLAY DYN_MACRO_PLAY1
#define DM_STRT DYN_REC_START1
#define DM_STOP DYN_REC_STOP

// one-shot layer keys
#define OSL_RSE OSL(RSE)
#define OSL_LWR OSL(LWR)
#define OSL_FUN OSL(FUN)

// one-shot modifier keys
#define OSM_CTL OSM(MOD_LCTL)
#define OSM_ALT OSM(MOD_LALT)
#define OSM_SFT OSM(MOD_LSFT)

// tap dance keys
#define TD_SCLN TD(TDK_SCLN)
#define TD_COMM TD(TDK_COMM)
#define TD_DOT  TD(TDK_DOT)
#define TD_SLSH TD(TDK_SLSH)

// macros
#define ACTION_TAP_DANCE_FN_KEYCODE(user_fn, kc) {  \
    .fn = { NULL, user_fn, NULL }, \
    .user_data = (void *)&((qk_tap_dance_pair_t) { kc, 0 }) \
}

#define ACTION_TAP_DANCE_FN_KEYCODE2(user_fn, kc1, kc2) {  \
    .fn = { NULL, user_fn, NULL }, \
    .user_data = (void *)&((qk_tap_dance_pair_t) { kc1, kc2 }) \
}

#define TAP(keycode) register_code16(keycode); unregister_code16(keycode)

#endif

