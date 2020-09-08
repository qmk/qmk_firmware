#include QMK_KEYBOARD_H
#include "muse.h"


/*
    ██████╗ ███████╗███████╗██╗███╗   ██╗██╗████████╗██╗ ██████╗ ███╗   ██╗███████╗
    ██╔══██╗██╔════╝██╔════╝██║████╗  ██║██║╚══██╔══╝██║██╔═══██╗████╗  ██║██╔════╝
    ██║  ██║█████╗  █████╗  ██║██╔██╗ ██║██║   ██║   ██║██║   ██║██╔██╗ ██║███████╗
    ██║  ██║██╔══╝  ██╔══╝  ██║██║╚██╗██║██║   ██║   ██║██║   ██║██║╚██╗██║╚════██║
    ██████╔╝███████╗██║     ██║██║ ╚████║██║   ██║   ██║╚██████╔╝██║ ╚████║███████║
    ╚═════╝ ╚══════╝╚═╝     ╚═╝╚═╝  ╚═══╝╚═╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝
*/

#define LCTL_MASK (get_mods() & MOD_BIT(KC_LCTL))
#define RCTL_MASK (get_mods() & MOD_BIT(KC_RCTL))
#define CTL_MASK  (LCTL_MASK || RCTL_MASK)
#define LSFT_MASK (get_mods() & MOD_BIT(KC_LSFT))
#define RSFT_MASK (get_mods() & MOD_BIT(KC_RSFT))
#define SFT_MASK  (LSFT_MASK || RSFT_MASK)

// Layers

enum planck_layers {
    _BASE,
    _LOWER1,
    _RAISE1,
    _LOWER2,
    _RAISE2,
    _HYPER,
    _ROTOR,
};

#define BASE TO(_BASE)
#define R_MODES OSL(_ROTOR)

#define LOWER1 OSL(_LOWER1)
#define RAISE1 OSL(_RAISE1)
#define LOWER2 OSL(_LOWER2)
#define RAISE2 OSL(_RAISE2)

// Rotary encoder states

enum encoder_states {
    VOLUME,     // volume up/down, toggle mute
    MEDIA,      // media next/previous, play/pause
    BRIGHTNESS, // brightness up/down
    SCROLL_V,   // scroll up/down, middle click
    SCROLL_H,   // scroll right/left, middle click
    ARROW_V,    // arrow up/down
    ARROW_H,    // arrow left/right
};

enum encoder_states rotary_state = VOLUME;

// Custom keycodes

enum keycodes {
    ROTARY = SAFE_RANGE,
    PANIC,                  // backspace on tap, delete on tap with any modifier

    // rotary adjustment
    R_VOL, R_MEDIA, R_BRI, R_SC_V, R_SC_H, R_AR_V, R_AR_H,

    // command-line macros
    CLEAR,      // [clear terminal line]
    DOTFILE,    // dotfiles
    GT_ADD,     // git add
    GT_STAT,    // git status
    GT_CMT,     // git commit
    GT_PULL,    // git pull
    GT_PUSH,    // git push
    VIM_WQ,     // [ESC]:wq

    // bracket mode
    LBK_TG, RBK_TG,                 // toggle left-side and right-side brackets
    LBK_P, LBK_S, LBK_C, LBK_A,     // left-side brackets
    RBK_P, RBK_S, RBK_C, RBK_A,     // right-side brackets

};

#define H(kc) HYPR(kc)

#define CT_TAB  MT(MOD_LCTL, KC_TAB)
#define SH_ESC  MT(MOD_LSFT, KC_ESC)
#define SH_QUOT MT(MOD_RSFT, KC_QUOT)

static bool lbk_mode = false;   // left-side bracket mode
static bool rbk_mode = false;   // right-side bracket mode

// Audio songs

#ifdef AUDIO_ENABLE
    // layer toggle songs
    float base_song[][2]            = SONG(QWERTY_SOUND);
    float bk_activate_song[][2]     = SONG(MARIO_JUMP_SMALL);
    float bk_deactivate_song[][2]   = SONG(MARIO_JUMP_SMALL);

    // keycode songs
    float valid_rotary_song[][2]    = SONG(COIN);
    float invalid_rotary_song[][2]  = SONG(BUZZ);

    // shortcut songs
    float caps_on_song[][2]         = SONG(MARIO_CAVE_1);
    float caps_off_song[][2]        = SONG(MARIO_CAVE_2);
    float save_song[][2]            = SONG(MARIO_ONEUP);
    float copy_song[][2]            = SONG(MARIO_POWERUP);
    float paste_song[][2]           = SONG(MARIO_BUMP);
    float cut_song[][2]             = SONG(MARIO_FIREBALL);
    float undo_song[][2]            = SONG(MARIO_KICK);
    float redo_song[][2]            = SONG(MARIO_COIN);
#endif


/*
██╗  ██╗███████╗██╗   ██╗███╗   ███╗ █████╗ ██████╗ ███████╗
██║ ██╔╝██╔════╝╚██╗ ██╔╝████╗ ████║██╔══██╗██╔══██╗██╔════╝
█████╔╝ █████╗   ╚████╔╝ ██╔████╔██║███████║██████╔╝███████╗
██╔═██╗ ██╔══╝    ╚██╔╝  ██║╚██╔╝██║██╔══██║██╔═══╝ ╚════██║
██║  ██╗███████╗   ██║   ██║ ╚═╝ ██║██║  ██║██║     ███████║
╚═╝  ╚═╝╚══════╝   ╚═╝   ╚═╝     ╚═╝╚═╝  ╚═╝╚═╝     ╚══════╝
*/


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Base layer

        |-----------------------------------------------------------------------------------------------|
        | Rotary|   Q   |   W   |   E   |   R   |   T   |   Y   |   U   |   I   |   O   |   P   | Panic |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |  Tab  |   A   |   S   |   D   |   F   |   G   |   H   |   J   |   K   |   L   |   ;   | Enter |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |  Esc  |   Z   |   X   |   C   |   V   |   B   |   N   |   M   |   ,   |   .   |   /   |   '   |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        | HYPER |  Ctrl |  Meta | Super | LOWER1|     Space     | RAISE1|   Lt  |   Dn  |   Up  |   Rt  |
        |-----------------------------------------------------------------------------------------------|

        Left-side bracket mode:                                         Right-side bracket mode:

        |-------+-------+-------+-------+-                             -+-------+-------+-------+-------|
        |  < >  |  { }  |  [ ]  |  ( )  |             . . .             |  ( )  |  [ ]  |  { }  |  < >  |
        |---------------------------------                             ---------------------------------|

        *
        * Bracket keys:     Open bracket on tap, close bracket on tap with SHIFT held.
                            If both bracket modes active, right-side brackets are closed by default.
        * TAB:              Esc on tap, CTRL on hold, ` on tap with SHIFT or CTRL held. ***TODO
        * PANIC:            Backspace on tap, delete on tap with SHIFT held.
        * ESC and ':        SHIFT on hold.
        *

    */

    [_BASE] = LAYOUT_planck_grid(
        ROTARY,  KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,     KC_Y,     KC_U,   KC_I,    KC_O,    KC_P,    PANIC,
        CT_TAB,  KC_A,    KC_S,    KC_D,   KC_F,   KC_G,     KC_H,     KC_J,   KC_K,    KC_L,    KC_SCLN, KC_ENT,
        SH_ESC,  KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,     KC_N,     KC_M,   KC_COMM, KC_DOT,  KC_SLSH, SH_QUOT,
        LBK_A,   LBK_C,   LBK_S,   LBK_P,  LOWER1, KC_SPACE, KC_SPACE, RAISE1, RBK_P,   RBK_S,   RBK_C,   RBK_A
    ),

    /* Hyper layer

        |-----------------------------------------------------------------------------------------------|
        | ROTARY|       |       |       |       |       |       |       |       |       |       | Sleep |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        | Reset |       |       |       |       |       |       |       |       |       |       |       |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |  Caps |       |       |       |       |       |       |       |       |       |       |  Caps |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |       |       |       | Tg LBK|      BASE     | Tg RBK|       |       |       | Sleep |
        |-----------------------------------------------------------------------------------------------|

        *
        * Alphabet keys:    Mod-tap with HYPER; left for software implementation.
        * Tg LBK:           Toggle left-side bracket mode.
        * Tg RBK:           Toggle right-side bracket mode.
        *

    */
    [_HYPER] = LAYOUT_planck_grid(
        R_MODES, H(KC_Q), H(KC_W), H(KC_E), H(KC_R), H(KC_T), H(KC_Y), H(KC_U), H(KC_I),    H(KC_O),   H(KC_P),    KC_SLEP,
        RESET,   H(KC_A), H(KC_S), H(KC_D), H(KC_F), H(KC_G), H(KC_H), H(KC_J), H(KC_K),    H(KC_L),   H(KC_SCLN), _______,
        KC_CAPS, H(KC_Z), H(KC_X), H(KC_C), H(KC_V), H(KC_B), H(KC_N), H(KC_M), H(KC_COMM), H(KC_DOT), H(KC_SLSH), KC_CAPS,
        _______, _______, _______, _______, LBK_TG,  BASE,    BASE,    RBK_TG,  _______,    _______,   _______,    KC_SLEP
    ),

    /* Rotary - rotary encoder mode

        |-----------------------------------------------------------------------------------------------|
        |       |       |       |       |       |       |       |       |       |       |       |       |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |       |       |       |       |       |       |       |       |       |       |       |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |       |       |       |  vol  | bright|       | media |       |       |       |       |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |       |       |       |       |      BASE     |       |scrll h|scrll v|arrow v|arrow h|
        |-----------------------------------------------------------------------------------------------|

        *
        *
        *

    */
    [_ROTOR] = LAYOUT_planck_grid(
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, R_VOL,   R_BRI,   XXXXXXX, R_MEDIA, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, _______, _______, _______, _______, BASE,    BASE,    _______, R_SC_H,  R_SC_V,  R_AR_V,  R_AR_H
    ),

    /* Lower I - command-line macros

        |-----------------------------------------------------------------------------------------------|
        |       | wq vim|       |       |       |       |       |       |       |       | g push| clear |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       | g add | g stat|dotfile|       |       |       |       |       | g pull|       |       |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |       |       | g cmt |       |       |       |       |       |       |       |       |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |       |       |       | LOWER2|      BASE     | RAISE1|       |       |       |       |
        |-----------------------------------------------------------------------------------------------|

        *
        * DO NOT INCLUDE DESTRUCTIVE COMMANDS
        * Stand-alone non-destructive commands are executed instantly (e.g. git status)
        * Each non-layer keypress moves to BASE (exception: rotary, arrow keys, enter)
        * Held modifiers temporarily move to BASE
        *

    */
    [_LOWER1] = LAYOUT_planck_grid(
        _______, VIM_WQ,  _______, _______, _______, _______, _______, _______, _______, _______, GT_PUSH,   CLEAR,
        _______, GT_ADD,  GT_STAT, DOTFILE, _______, _______, _______, _______, _______, GT_PULL, _______, _______,
        _______, _______, _______,  GT_CMT, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, LOWER2,  BASE,    BASE,    RAISE1,  _______, _______, _______, _______
    ),

    /* Raise I - symbols

        |-----------------------------------------------------------------------------------------------|
        |       |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |   0   |       |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |   !   |   @   |   #   |   $   |   %   |   ^   |   &   |   *   |   (   |   )   |       |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |   \   |   |   |   `   |   ~   |   '   |   "   |   _   |   -   |   +   |   =   |       |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |       |       |       | LOWER1|      BASE     | RAISE2|       |       |       |       |
        |-----------------------------------------------------------------------------------------------|

        *
        * Each non-layer keypress moves to BASE (exception: rotary, arrow keys, numbers?)
        *

    */
    [_RAISE1] = LAYOUT_planck_grid(
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
        _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
        _______, KC_BSLS, KC_PIPE, KC_GRV,  KC_TILD, KC_QUOT, KC_DQUO, KC_UNDS, KC_MINS, KC_PLUS, KC_EQL,  _______,
        _______, _______, _______, _______, LOWER1,  BASE,    BASE,    RAISE2,   _______, _______, _______, _______
    ),

    /* Lower II - navigation

        |-----------------------------------------------------------------------------------------------|
        |       |  L Ck |  M up |  R ck |       |       |       |       | Ctrl- | S up  | Ctrl+ |       |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |  M lt |  M dn |  M rt |       |       |       |       | S lt  | S dn  | S rt  |       |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |       |       |       |       |       |       |       |       |       |       |       |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |       |       |       |       |      BASE     | RAISE1|       |       |       |       |
        |-----------------------------------------------------------------------------------------------|

        *
        *
        *

    */
    [_LOWER2] = LAYOUT_planck_grid(
        _______, KC_BTN1, KC_MS_U, KC_BTN2, _______, _______, _______, _______, _______, KC_WH_U, _______, _______,
        _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, _______, _______, KC_WH_L, KC_WH_D, KC_WH_R, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, BASE,    BASE,    RAISE1,  _______, _______, _______, _______
    ),

    /* Raise II - arrow keys and function layer

        |-----------------------------------------------------------------------------------------------|
        |       |  F1   |  F2   |  F3   |  F4   |  F5   |  F6   |  F7   |  F8   |  F9   |  F10  |       |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |  Esc  |  F11  |  F12  |  F13  |  F14  |  F15  |       | Left  | Down  |  Up   | Right |       |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |  F16  |  F17  |  F18  |  F19  |  F20  |       |       |       |       |       |       |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |       |       |       | LOWER1|      BASE     |       |       |       |       |       |
        |-----------------------------------------------------------------------------------------------|

        *
        *
        *

    */
    [_RAISE2] = LAYOUT_planck_grid(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,
        _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,
        _______, _______, _______, _______, LOWER1,  BASE,    BASE,    _______, _______, _______, _______,  _______
    ),

};


/*
 ██████╗██╗   ██╗███████╗████████╗ ██████╗ ███╗   ███╗    ██╗      ██████╗  ██████╗ ██╗ ██████╗
██╔════╝██║   ██║██╔════╝╚══██╔══╝██╔═══██╗████╗ ████║    ██║     ██╔═══██╗██╔════╝ ██║██╔════╝
██║     ██║   ██║███████╗   ██║   ██║   ██║██╔████╔██║    ██║     ██║   ██║██║  ███╗██║██║
██║     ██║   ██║╚════██║   ██║   ██║   ██║██║╚██╔╝██║    ██║     ██║   ██║██║   ██║██║██║
╚██████╗╚██████╔╝███████║   ██║   ╚██████╔╝██║ ╚═╝ ██║    ███████╗╚██████╔╝╚██████╔╝██║╚██████╗
 ╚═════╝ ╚═════╝ ╚══════╝   ╚═╝    ╚═════╝ ╚═╝     ╚═╝    ╚══════╝ ╚═════╝  ╚═════╝ ╚═╝ ╚═════╝
*/

void keypress(bool pressed, uint16_t keycode) {
    if (pressed) {
        register_code16(keycode);
    }
    else {
        unregister_code16(keycode);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static bool panic_del = false;      // PANIC in delete-mode
    static bool caps_active = false;

    switch (keycode) {

        /*
        ██   ██ ███████ ██    ██  ██████  ██████  ██████  ███████ ███████ 
        ██  ██  ██       ██  ██  ██      ██    ██ ██   ██ ██      ██      
        █████   █████     ████   ██      ██    ██ ██   ██ █████   ███████ 
        ██  ██  ██         ██    ██      ██    ██ ██   ██ ██           ██ 
        ██   ██ ███████    ██     ██████  ██████  ██████  ███████ ███████
        */

        case PANIC:
            if (record->event.pressed) {
                if (CTL_MASK) {
                    unregister_code(KC_LCTL);
                    register_code(KC_DEL);
                    panic_del = true;
                }
                else {
                    register_code(KC_BSPACE);
                }
            }
            else {
                if (panic_del) {
                    register_code(KC_LCTL);
                    unregister_code(KC_DEL);
                    panic_del = false;
                }
                else {
                    unregister_code(KC_BSPACE);
                }
            }
            return false;
        case LBK_TG:
            if (record->event.pressed) {
                lbk_mode = !lbk_mode;
            }
            break;
        case RBK_TG:
            if (record->event.pressed) {
                rbk_mode = !rbk_mode;
            }
            break;
        case KC_CAPS:
            if (record->event.pressed) {
                caps_active = !caps_active;
            }
            break;

        // rotary encoder

        case R_VOL:
            if (record->event.pressed) {
                rotary_state = VOLUME;
            }
            break;
        case R_MEDIA:
            if (record->event.pressed) {
                rotary_state = MEDIA;
            }
            break;
        case R_BRI:
            if (record->event.pressed) {
                rotary_state = BRIGHTNESS;
            }
            break;
        case R_SC_V:
            if (record->event.pressed) {
                rotary_state = SCROLL_V;
            }
            break;
        case R_SC_H:
            if (record->event.pressed) {
                rotary_state = SCROLL_H;
            }
            break;
        case R_AR_V:
            if (record->event.pressed) {
                rotary_state = ARROW_V;
            }
            break;
        case R_AR_H:
            if (record->event.pressed) {
                rotary_state = ARROW_H;
            }
            break;
        case ROTARY:
            if (record->event.pressed) {
                if (rotary_state == VOLUME) {
                    tap_code(KC_MUTE);  // toggle mute
                }
                else if (rotary_state == MEDIA) {
                    tap_code(KC_MPLY);  // play/pause media
                }
                else if (rotary_state == SCROLL_V || rotary_state == SCROLL_H) {
                    tap_code(KC_BTN3);  // middle mouse button
                }
            }
            return false;

        /*
        ███    ███  █████   ██████ ██████   ██████  ███████ 
        ████  ████ ██   ██ ██      ██   ██ ██    ██ ██      
        ██ ████ ██ ███████ ██      ██████  ██    ██ ███████ 
        ██  ██  ██ ██   ██ ██      ██   ██ ██    ██      ██ 
        ██      ██ ██   ██  ██████ ██   ██  ██████  ███████
        */

        case CLEAR:
            if (record->event.pressed) {
                tap_code16(LCTL(KC_E)); // go to start of line
                tap_code16(LCTL(KC_U)); // clear to beginning of line
            }
            break;
        case DOTFILE:
            if (record->event.pressed) {
                SEND_STRING("dotfiles ");
            }
            break;
        case GT_ADD:
            if (record->event.pressed) {
                SEND_STRING("git add ");
            }
            break;
        case GT_STAT:
            if (record->event.pressed) {
                SEND_STRING("git status ");
            }
            break;
        case GT_CMT:
            if (record->event.pressed) {
                SEND_STRING("git commit -m ''");
                tap_code(KC_LEFT);
            }
            break;
        case GT_PULL:
            if (record->event.pressed) {
                SEND_STRING("git pull ");
            }
            break;
        case GT_PUSH:
            if (record->event.pressed) {
                SEND_STRING("git push ");
            }
            break;
        case VIM_WQ:
            if (record->event.pressed) {
                tap_code(KC_ESC);
                SEND_STRING(":wq");
            }
            break;
    };

    /*
         █████  ██    ██ ██████  ██  ██████ 
        ██   ██ ██    ██ ██   ██ ██ ██    ██ 
        ███████ ██    ██ ██   ██ ██ ██    ██ 
        ██   ██ ██    ██ ██   ██ ██ ██    ██ 
        ██   ██  ██████  ██████  ██  ██████
    */

    #ifdef AUDIO_ENABLE
        if (record->event.pressed) {
            switch (keycode) {
                case KC_S: // CTRL+S
                    if (CTL_MASK) {
                        PLAY_SONG(save_song);
                    }
                    break;
                case KC_C: // CTRL+C
                    if (CTL_MASK) {
                        PLAY_SONG(copy_song);
                    }
                    break;
                case KC_V: // CTRL+V
                    if (CTL_MASK) {
                        PLAY_SONG(paste_song);
                    }
                    break;
                case KC_X: // CTRL+X
                    if (CTL_MASK) {
                        PLAY_SONG(cut_song);
                    }
                    break;
                case KC_Z: // CTRL+Z
                    if (CTL_MASK) {
                        PLAY_SONG(undo_song);
                    }
                    break;
                case KC_Y: // CTRL+Y
                    if (CTL_MASK) {
                        PLAY_SONG(redo_song);
                    }
                    break;
                case KC_CAPS:
                    if (caps_active) {
                        PLAY_SONG(caps_on_song);
                    }
                    else {
                        PLAY_SONG(caps_off_song);
                    }
                    break;
                case LBK_TG:
                    if (lbk_mode) {
                        PLAY_SONG(bk_activate_song);
                    }
                    else{
                        PLAY_SONG(bk_deactivate_song);
                    }
                    break;
                case RBK_TG:
                    if (rbk_mode) {
                        PLAY_SONG(bk_activate_song);
                    }
                    else {
                        PLAY_SONG(bk_deactivate_song);
                    }
                    break;

                // rotary encoder

                case R_VOL:
                case R_MEDIA:
                case R_BRI:
                case R_SC_V:
                case R_SC_H:
                case R_AR_V:
                case R_AR_H:
                    PLAY_SONG(valid_rotary_song);
                    break;

                default:
                    if (IS_LAYER_ON(_ROTOR)) {
                        PLAY_SONG(invalid_rotary_song);
                    }
            };
        }
    #endif

    /*
        ██████  ██████   █████   ██████ ██   ██ ███████ ████████ ███████ 
        ██   ██ ██   ██ ██   ██ ██      ██  ██  ██         ██    ██      
        ██████  ██████  ███████ ██      █████   █████      ██    ███████ 
        ██   ██ ██   ██ ██   ██ ██      ██  ██  ██         ██         ██ 
        ██████  ██   ██ ██   ██  ██████ ██   ██ ███████    ██    ███████
    */

    bool lbk_key = (keycode == LBK_P || keycode == LBK_S || keycode == LBK_C || keycode == LBK_A);
    bool rbk_key = (keycode == RBK_P || keycode == RBK_S || keycode == RBK_C || keycode == RBK_A);

    // left-side held modifiers
    if (lbk_key && /* TODO: key is held */ false) {
        if (keycode == LBK_P) {
            keypress(record->event.pressed, KC_LGUI);
        }
        else if (keycode == LBK_S) {
            keypress(record->event.pressed, KC_LALT);
        }
        else if (keycode == LBK_C) {
            keypress(record->event.pressed, KC_LCTL);
        }
        else if (keycode == LBK_A) {
            if (record->event.pressed) {
                layer_on(_HYPER);
            }
            else {
                layer_off(_HYPER);
            }
        }
    }

    // brackets mode
    else if ((lbk_key && lbk_mode) || (rbk_key && rbk_mode)) {
        // closed brackets
        if ((rbk_key && rbk_mode && lbk_mode) || LSFT_MASK || RSFT_MASK) {
            if (LSFT_MASK) {
                unregister_code(KC_LSFT);
            }
            if (RSFT_MASK) {
                unregister_code(KC_RSFT);
            }

            if (keycode == LBK_P || keycode == RBK_P) {
                keypress(record->event.pressed, KC_RPRN);
            }
            else if (keycode == LBK_S || keycode == RBK_S) {
                keypress(record->event.pressed, KC_RBRC);
            }
            else if (keycode == LBK_C || keycode == RBK_C) {
                keypress(record->event.pressed, KC_RCBR);
            }
            else if (keycode == LBK_A || keycode == RBK_A) {
                keypress(record->event.pressed, KC_RABK);
            }

            //TODO: persistent modifier memory using linked list
            if (LSFT_MASK) {
                register_code(KC_LSFT);
            }
            if (RSFT_MASK) {
                register_code(KC_RSFT);
            }
        }
        // open brackets
        else {
            if (keycode == LBK_P || keycode == RBK_P) {
                keypress(record->event.pressed, KC_LPRN);
            }
            else if (keycode == LBK_S || keycode == RBK_S) {
                keypress(record->event.pressed, KC_LBRC);
            }
            else if (keycode == LBK_C || keycode == RBK_C) {
                keypress(record->event.pressed, KC_LCBR);
            }
            else if (keycode == LBK_A || keycode == RBK_A) {
                keypress(record->event.pressed, KC_LABK);
            }
        }
    }

    // left-side one-shot modifiers
    else if (lbk_key) {
        if (keycode == LBK_P) {
            if (record->event.pressed) {
                set_oneshot_mods(MOD_LGUI);
            }
            keypress(record->event.pressed, KC_LGUI);
        }
        else if (keycode == LBK_S) {
            if (record->event.pressed) {
                set_oneshot_mods(MOD_LALT);
            }
            keypress(record->event.pressed, KC_LALT);
        }
        else if (keycode == LBK_C) {
            if (record->event.pressed) {
                set_oneshot_mods(MOD_LCTL);
            }
            keypress(record->event.pressed, KC_LCTL);
        }
        else if (keycode == LBK_A) {
            if (record->event.pressed) {
                layer_on(_HYPER);           // TODO: keep HYPER on if no key pressed while held (i.e. OSL)
                //set_oneshot_layer(_HYPER, ONESHOT_START);
            }
            else {
                layer_off(_HYPER);
                //clear_oneshot_layer_state(ONESHOT_PRESSED);
            }
        }
    }

    // right-side arrows keys
    else if (rbk_key) {
        if (keycode == RBK_P) {
            keypress(record->event.pressed, KC_LEFT);
        }
        else if (keycode == RBK_S) {
            keypress(record->event.pressed, KC_DOWN);
        }
        else if (keycode == RBK_C) {
            keypress(record->event.pressed, KC_UP);
        }
        else if (keycode == RBK_A) {
            keypress(record->event.pressed, KC_RIGHT);
        }
    }

    return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    //if (keycode != LBK_A && IS_LAYER_ON(_HYPER)) {
    //    layer_off(_HYPER);
    //}
}


/*
██████╗  ██████╗ ████████╗ █████╗ ██████╗ ██╗   ██╗    ███████╗███╗   ██╗ ██████╗ ██████╗ ██████╗ ███████╗██████╗
██╔══██╗██╔═══██╗╚══██╔══╝██╔══██╗██╔══██╗╚██╗ ██╔╝    ██╔════╝████╗  ██║██╔════╝██╔═══██╗██╔══██╗██╔════╝██╔══██╗
██████╔╝██║   ██║   ██║   ███████║██████╔╝ ╚████╔╝     █████╗  ██╔██╗ ██║██║     ██║   ██║██║  ██║█████╗  ██████╔╝
██╔══██╗██║   ██║   ██║   ██╔══██║██╔══██╗  ╚██╔╝      ██╔══╝  ██║╚██╗██║██║     ██║   ██║██║  ██║██╔══╝  ██╔══██╗
██║  ██║╚██████╔╝   ██║   ██║  ██║██║  ██║   ██║       ███████╗██║ ╚████║╚██████╗╚██████╔╝██████╔╝███████╗██║  ██║
╚═╝  ╚═╝ ╚═════╝    ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝       ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚══════╝╚═╝  ╚═╝
*/


#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    switch (rotary_state) {
        case VOLUME:
            if (clockwise) {
                tap_code(KC_VOLU);
            }
            else {
                tap_code(KC_VOLD);
            }
            break;
        case MEDIA:
            if (clockwise) {
                tap_code(KC_MNXT);
            }
            else {
                tap_code(KC_MPRV);
            }
            break;
        case BRIGHTNESS:
            if (clockwise) {
                tap_code(KC_BRIU);
            }
            else {
                tap_code(KC_BRID);
            }
            break;
        case SCROLL_V:
            if (clockwise) {
                tap_code(KC_PGDN);
            }
            else {
                tap_code(KC_PGUP);
            }
            break;
        case SCROLL_H:
            if (clockwise) {
                for (int i=0; i<5; i++) {
                    tap_code(KC_WH_R);
                }
            }
            else {
                for (int i=0; i<5; i++) {
                    tap_code(KC_WH_L);
                }
            }
            break;
        case ARROW_V:
            if (clockwise) {
                tap_code(KC_DOWN);
            }
            else {
                tap_code(KC_UP);
            }
            break;
        case ARROW_H:
            if (clockwise) {
                tap_code(KC_RIGHT);
            }
            else {
                tap_code(KC_LEFT);
            }
            break;
    }
}
#endif
