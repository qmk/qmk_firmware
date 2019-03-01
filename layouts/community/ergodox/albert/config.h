#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include QMK_KEYBOARD_CONFIG_H

/* using UK layout for space-cadet-shift */
#define KC_LSPO_KEYS SC_KEY(KC_LSFT, KC_LSFT, KC_9)
#define KC_RSPC_KEYS SC_KEY(KC_RSFT, KC_RSFT, KC_0)

#define LEADER_TIMEOUT 800 // leader key sequence timeout in millis

#endif
