
#pragma once

#define COMBO_ONLY_FROM_LAYER 0
#define COMBO_VARIABLE_LEN
#define COMBO_TERM 50

#define LAYER_BASE 0
#define LAYER_NAV 1
#define LAYER_SYMBOLS 2
#define LAYER_NUM 3
#define LAYER_NAV_EXT 4
#define LAYER_WASD 5
#define LAYER_MOUSE 6


// Miryoku macros
#define OLM(key) MT(MOD_LGUI, key)
#define OLI(key) MT(MOD_LALT, key)
#define OLR(key) MT(MOD_LSFT, key)
#define OLY(key) MT(MOD_LCTL, key)
#define OLO(key) MT(MOD_LGUI | MOD_LALT | MOD_LSFT | MOD_LCTL, key)

#define ORM(key) MT(MOD_RGUI, key)
#define ORI(key) MT(MOD_RALT, key)
#define ORR(key) MT(MOD_RSFT, key)
#define ORY(key) MT(MOD_RCTL, key)
#define ORO(key) MT(MOD_RCTL | MOD_RALT | MOD_RSFT | MOD_RGUI, key)


// odama626 layers
#define O_TAB LT(LAYER_NUM, KC_TAB)
#define O_SPC LT(LAYER_NAV, KC_SPC)
#define O_ENT LT(LAYER_SYMBOLS, KC_ENT)



#define ENABLE_RGB_MATRIX_SPLASH
