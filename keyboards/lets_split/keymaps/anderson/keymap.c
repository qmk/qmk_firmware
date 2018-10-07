// Six-Seven - minimal layout for Let's Split.
#include "lets_split.h"
#include "action_layer.h"
#include "eeconfig.h"
#include "keys.h"
#include "pro_micro.h"
#include "pointing_device.h"
#include "knob_v2.h"
#include "taphold.h"
#include "audio.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _MAIN 0
#define _ALPHA 1
#define _BETA 2

float ALPHA_SND[][2] = {
    S__NOTE(_C5), S__NOTE(_G4), S__NOTE(_C4)
};
float BETA_SND[][2] = {
    S__NOTE(_C5), S__NOTE(_G5), S__NOTE(_C6)
};

enum custom_keycodes {
  KC_MAIN = SAFE_RANGE,
  KC_ALPHA,
  KC_BETA
};

float foo[][2] = {
    S__NOTE(_C5), S__NOTE(_G4), S__NOTE(_C4)
};

#define TAPHOLD_CONFIG_SIZE 3
taphold_t taphold_config[TAPHOLD_CONFIG_SIZE] = {
    {.key=KC_ALPHA, .mode=TAPHOLD_LAYER, .shortAction=KC_ESC, .longAction=_ALPHA},
    {.key=KC_BETA, .mode=TAPHOLD_LAYER, .shortAction=KC_EQL, .longAction=_BETA},
    {.key=KC_LCTRL, .mode=TAPHOLD_MOD, .shortAction=KC_MINS, .longAction=KC_LCTRL}
};
uint16_t taphold_config_size = TAPHOLD_CONFIG_SIZE;
uint32_t taphold_timeout = 90;

uint32_t layer_colors[3] = {
    [_MAIN] = 0xFF0010,
    /*[_ALPHA] = 0xFF0040,*/
    [_ALPHA] = 0x4000FF,
    [_BETA] = 0x40FF80,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Main layer
       ┏━━━━━┳━━━━━┯━━━━━┯━━━━━┯━━━━━┯━━━━━┓      ┏━━━━━┯━━━━━┯━━━━━┯━━━━━┯━━━━━┳━━━━━┓
       ┃ TAB ┃  Q  │  W  │  E  │  R  │  T  ┃      ┃  Y  │  U  │  I  │  O  │  P  ┃ BSP ┃
       ┣━━━━━╉─────┼─────┼─────┼─────┼─────┨      ┠─────┼─────┼─────┼─────┼─────╊━━━━━┫
       ┃α/ESC┃  A  │  S  │  D  │  F  │  G  ┃      ┃  H  │  J  │  K  │  L  │  ;  ┃ RET ┃
       ┣━━━━━╉─────┼─────┼─────┼─────┼─────┨      ┠─────┼─────┼─────┼─────┼─────╊━━━━━┫
       ┃SHIFT┃  Z  │  X  │  C  │  V  │  B  ┃      ┃  N  │  M  │  ,  │  .  │  /  ┃CTL/-┃
       ┗━━━━━┻━━━━━┷━━━━━╈━━━━━╈━━━━━╈━━━━━┫      ┣━━━━━╈━━━━━╈━━━━━╈━━━━━┷━━━━━┻━━━━━┛
                         ┃ ALT ┃     ┃ MOD ┃      ┃SPACE┃ β/= ┃  '  ┃
                         ┗━━━━━┻━━━━━┻━━━━━┛      ┗━━━━━┻━━━━━┻━━━━━┛
       */
    [_MAIN] = LAYOUT_kc( \
        TAB,  Q,    W,    E,    R,    T,           Y,    U,    I,    O,    P,    BSPC, \
        ALPHA,A,    S,    D,    F,    G,           H,    J,    K,    L,    SCLN, ENT,  \
        LSFT, Z,    X,    C,    V,    B,           N,    M,    COMM, DOT,  SLSH, LCTRL,\
        _____,_____,_____,LALT, _____,LGUI,        SPC,  BETA, QUOT, _____,_____,_____ \
    ),

    /* Alpha layer (α)
       ┏━━━━━┳━━━━━┯━━━━━┯━━━━━┯━━━━━┯━━━━━┓      ┏━━━━━┯━━━━━┯━━━━━┯━━━━━┯━━━━━┳━━━━━┓
       ┃     ┃PREV │PLAY │NEXT │     │     ┃      ┃     │ ^^^ │  ^  │ vvv │  ~  ┃ DEL ┃
       ┣━━━━━╉─────┼─────┼─────┼─────┼─────┨      ┠─────┼─────┼─────┼─────┼─────╊━━━━━┫
       ┃     ┃     │VOL -│VOL +│     │     ┃      ┃HOME │ <-- │  v  │ --> │  `  ┃  \  ┃
       ┣━━━━━╉─────┼─────┼─────┼─────┼─────┨      ┠─────┼─────┼─────┼─────┼─────╊━━━━━┫
       ┃     ┃     │     │     │     │     ┃      ┃ END │ INS │  [  │  ]  │  (  ┃  )  ┃
       ┗━━━━━┻━━━━━┷━━━━━╈━━━━━╈━━━━━╈━━━━━┫      ┠━━━━━╈━━━━━╈━━━━━╈━━━━━┷━━━━━┻━━━━━┛
                         ┃     ┃     ┃     ┃      ┃     ┃     ┃     ┃
                         ┗━━━━━┻━━━━━┻━━━━━┛      ┗━━━━━┻━━━━━┻━━━━━┛
       */
    [_ALPHA] = LAYOUT_kc( \
        _____,MPRV, MPLY, MNXT, _____,_____,       _____,PGUP, UP,   PGDN, TILD, DEL,  \
        _____,_____,VOLD, VOLU, _____,_____,       HOME, LEFT, DOWN, RIGHT,GRV,  BSLS, \
        _____,_____,_____,_____,_____,_____,       END,  INS,  LBRC, RBRC, SH(9),SH(0),\
        _____,_____,_____,_____,_____,_____,       BTN1, _____,BTN2, _____,_____,_____ \
    ),

    /* Beta layer (β)
       ┏━━━━━┳━━━━━┯━━━━━┯━━━━━┯━━━━━┯━━━━━┓      ┏━━━━━┯━━━━━┯━━━━━┯━━━━━┯━━━━━┳━━━━━┓
       ┃  `  ┃  1  │  2  │  3  │  4  │  5  ┃      ┃  6  │  7  │  8  │  9  │  0  ┃ del ┃
       ┣━━━━━╉─────┼─────┼─────┼─────┼─────┨      ┠─────┼─────┼─────┼─────┼─────╊━━━━━┫
       ┃     ┃ F1  │ F2  │ F3  │ F4  │ F5  ┃      ┃ F6  │ F7  │ F8  │ F9  │ F10 ┃  |  ┃
       ┣━━━━━╉─────┼─────┼─────┼─────┼─────┨      ┠─────┼─────┼─────┼─────┼─────╊━━━━━┫
       ┃     ┃RESET│DEBUG│     │ F11 │ F12 ┃      ┃SND +│SND -│  {  │  }  │  -  ┃  =  ┃
       ┗━━━━━┻━━━━━┷━━━━━╈━━━━━╈━━━━━╈━━━━━┫      ┣━━━━━╈━━━━━╈━━━━━╈━━━━━┷━━━━━┻━━━━━┛
                         ┃     ┃     ┃     ┃      ┃     ┃     ┃     ┃
                         ┗━━━━━┻━━━━━┻━━━━━┛      ┗━━━━━┻━━━━━┻━━━━━┛
       */
    [_BETA] = LAYOUT_kc( \
        _____,K1,   K2,   K3,   K4,   K5,          K6,   K7,   K8,   K9,   K0,   DEL,  \
        _____,F1,   F2,   F3,   F4,   F5,          F6,   F7,   F8,   F9,   F10,  PIPE, \
        _____,RESET,DEBUG,_____,F11,  F12,         AON,  AOFF, LCBR, RCBR, MINS, RCTRL,  \
        _____,_____,_____,_____,_____,_____,       _____,_____,_____,_____,_____,_____ \
    )
};

void matrix_init_user(void) {
    /*smoothled_set(0, 0, 32);*/
    knob_init();
    /*rgblight_setrgb(255, 0, 255);*/
}

void matrix_scan_user(void) {

    knob_report_t knob_report = knob_report_read();
    knob_report_reset();
    if (knob_report.phase) { // I check for phase to avoid handling the rotation twice (on 90 and 270 degrees).
        while (knob_report.dir > 0) {
            // CCW
            if (layer_state_is(_MAIN)) {
                register_code(KC_VOLD);
                unregister_code(KC_VOLD);
            } else if (layer_state_is(_ALPHA)) {
                register_code(KC_LEFT);
                unregister_code(KC_LEFT);
            }
            knob_report.dir--;
        }
        while (knob_report.dir < 0) {
            // CW
            if (layer_state_is(_MAIN)) {
                register_code(KC_VOLU);
                unregister_code(KC_VOLU);
            } else if (layer_state_is(_ALPHA)) {
                register_code(KC_RIGHT);
                unregister_code(KC_RIGHT);
            }
            knob_report.dir++;
        }
    }
}

void matrix_slave_scan_user(void) {
}