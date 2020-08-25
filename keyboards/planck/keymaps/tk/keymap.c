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

#define RAISE OSL(_RAISE1)
#define LOWER OSL(_LOWER1)

// Custom keycodes

enum keycodes {
    ROTARY = SAFE_RANGE,
    PANIC,                  // backspace on tap, delete on tap with any modifier

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
    TG_LBK, TG_RBK,                 // toggle left-side and right-side brackets
    LBK_P, LBK_S, LBK_C, LBK_A,     // left-side brackets
    RBK_P, RBK_S, RBK_C, RBA_A,     // right-side brackets

};

#define H(kc) HYPR(kc)

#define SH_TAB  MT(MOD_LSFT, KC_TAB)
#define SH_ESC  MT(MOD_LSFT, KC_ESC)
#define SH_QUOT MT(MOD_RSFT, KC_QUOT)

static bool lbk_mode = false;   // left-side bracket mode
static bool rbk_mode = false;   // right-side bracket mode

// Rotary encoder states

enum encoder_states {
    VOLUME,
    MEDIA,      // media next/previous, play/pause
    BRIGHTNESS,
    SCROLL_V,   // scroll up/down, middle click
    SCROLL_H,   // scroll right/left, middle click
};

enum encoder_states rotary_state = VOLUME;

// Audio songs

#ifdef AUDIO_ENABLE
    // layer toggle songs
    float base_song[][2]            = SONG(QWERTY_SOUND);
    float bk_activate_song[][2]     = SONG(BK_ACTIVATE);
    float bk_deactivate_song[][2]   = SONG(BK_DEACTIVATE);

    // special keycode songs
    float caps_on_song[][2]         = SONG(CAPS_ON_SOUND);
    float caps_off_song[][2]        = SONG(CAPS_OFF_SOUND);
    float save_song[][2]            = SONG(SAVE_SOUND);
    float copy_song[][2]            = SONG(COPY_SOUND);
    float paste_song[][2]           = SONG(PASTE_SOUND);
    float cut_song[][2]             = SONG(CUT_SOUND);
    float undo_song[][2]            = SONG(UNDO_SOUND);
    float redo_song[][2]            = SONG(REDO_SOUND);
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
        | HYPER | Super |  Meta |  Ctrl | LOWER |     Space     | RAISE |   Lt  |   Dn  |   Up  |   Rt  |
        |-----------------------------------------------------------------------------------------------|

        Left-side bracket mode:                                         Right-side bracket mode:

        |-------+-------+-------+-------+-                             -+-------+-------+-------+-------|
        |  < >  |  { }  |  [ ]  |  ( )  |             . . .             |  ( )  |  [ ]  |  { }  |  < >  |
        |---------------------------------                             ---------------------------------|

        *
        * Bracket keys:     Open bracket on tap, close bracket on tap with SHIFT held.
                            If both bracket modes active, right-side brackets are closed by default.
        * TAB:              Esc on tap, ` on tap with SHIFT or CTRL held. ***TODO
        * PANIC:            Backspace on tap, delete on tap with SHIFT held.
        * ESC and ':        SHIFT on hold.
        *

    */

    [_BASE] = LAYOUT_planck_grid(
        ROTARY,  KC_Q,    KC_W,    KC_E,   KC_R,  KC_T,     KC_Y,     KC_U,  KC_I,    KC_O,    KC_P,    PANIC,
        SH_TAB,  KC_A,    KC_S,    KC_D,   KC_F,  KC_G,     KC_H,     KC_J,  KC_K,    KC_L,    KC_SCLN, KC_ENT,
        SH_ESC,  KC_Z,    KC_X,    KC_C,   KC_V,  KC_B,     KC_N,     KC_M,  KC_COMM, KC_DOT,  KC_SLSH, SH_QUOT,
        LBK_A,   LBK_C,   LBK_S,   LBK_P,  LOWER, KC_SPACE, KC_SPACE, RAISE, RBK_P,   RBK_S,   RBK_C,   RBA_A
    ),

    /* Hyper layer

        |-----------------------------------------------------------------------------------------------|
        | Audio |       |       |       |       |       |       |       |       |       |       |       |
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
        _______, H(KC_Q), H(KC_W), H(KC_E), H(KC_R), H(KC_T), H(KC_Y), H(KC_U), H(KC_I),    H(KC_O),   H(KC_P),    KC_SLEP,
        RESET,   H(KC_A), H(KC_S), H(KC_D), H(KC_F), H(KC_G), H(KC_H), H(KC_J), H(KC_K),    H(KC_L),   H(KC_SCLN), _______,
        KC_CAPS, H(KC_Z), H(KC_X), H(KC_C), H(KC_V), H(KC_B), H(KC_N), H(KC_M), H(KC_COMM), H(KC_DOT), H(KC_SLSH), KC_CAPS,
        _______, _______, _______, _______, TG_LBK,  BASE,    BASE,    TG_RBK,  _______,    _______,   _______,    KC_SLEP
    ),

    /* Rotary - rotary encoder mode and volume

        |-----------------------------------------------------------------------------------------------|
        |       |       |       |       |       |       |       |       |       |       |       |       |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |       |       |scrll v|       |scrll h|       |       |       |       |       |       |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |       |       |       |  vol  | bright|       | media |       |       |       |       |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |       |       |       |       |      BASE     |       |       |       |       |       |
        |-----------------------------------------------------------------------------------------------|

        *
        *
        *

    */
    [_ROTOR] = LAYOUT_planck_grid(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    /* Raise I - symbols

        |-----------------------------------------------------------------------------------------------|
        |       |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   |   0   |       |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |   !   |   @   |   #   |   $   |   %   |   ^   |   &   |   *   |   (   |   )   |       |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |   \   |   |   |   `   |   ~   |   '   |   "   |   _   |   -   |   +   |   =   |       |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |       |       |       |       |      BASE     |       |       |       |       |       |
        |-----------------------------------------------------------------------------------------------|

        *
        * Each non-layer keypress moves to BASE (exception: rotary, arrow keys, numbers?)
        *

    */
    [_RAISE1] = LAYOUT_planck_grid(
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
        _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
        _______, KC_BSLS, KC_PIPE, KC_GRV,  KC_TILD, KC_QUOT, KC_DQUO, KC_UNDS, KC_MINS, KC_PLUS, KC_EQL,  _______,
        _______, _______, _______, _______, _______, BASE,    BASE,    _______, _______, _______, _______, _______
    ),

    /* Lower I - command-line macros

        |-----------------------------------------------------------------------------------------------|
        |       | wq vim|       |       |       |       |       |       |       |       | g push| clear |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       | g add | g stat|dotfile|       |       |       |       |       | g pull|       | Enter |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |       |       | g cmt |       |       |       |       |       |       |       |       |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |       |       |       | LOWER |      BASE     | RAISE |       |       |       |       |
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
        _______, _______, _______, _______, _______, BASE,    BASE,    _______, _______, _______, _______, _______
    ),

    /* Lower II - navigation

        |-----------------------------------------------------------------------------------------------|
        |       |  L Ck |  M up |  R ck |       |       |       |       | Ctrl- | S up  | Ctrl+ |       |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |  M lt |  M dn |  M rt |       |       |       |       | S lt  | S dn  | S rt  |       |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |       |       |       |       |       |       |       |       |       |       |       |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |       |       |       | LOWER |      BASE     | RAISE |       |       |       |       |
        |-----------------------------------------------------------------------------------------------|

        *
        *
        *

    */
    [_LOWER2] = LAYOUT_planck_grid(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    /* Raise II - functions and dynamic macros

        |-----------------------------------------------------------------------------------------------|
        |       |  F1   |  F2   |  F3   |  F4   |  F5   |  F6   |  F7   |  F8   |  F9   |  F10  |       |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |  Esc  |  F11  |  F12  |  F13  |  F14  |  F15  |  F16  |  F17  |  F18  |  F19  |  F20  |       |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |       |       |       |       |       |       |       |       |       |       |       |
        |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        |       |       |       |       | LOWER |      BASE     | RAISE |       |       |       |       |
        |-----------------------------------------------------------------------------------------------|

        *
        * Each non-layer keypress moves to BASE (exception: rotary)
        *
        * TODO: Add dynamic macro to this layer
        *

    */
    [_RAISE2] = LAYOUT_planck_grid(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
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
    static bool panic_del = false;     // PANIC in delete-mode

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
                if (get_mods() & (MOD_BIT(KC_LSFT))) {
                    unregister_code(KC_LSFT);
                    register_code(KC_DEL);
                    panic_del = true;
                }
                else {
                    register_code(KC_BSPACE);
                }
            }
            else {
                if (panic_del) {
                    register_code(KC_LSFT);
                    unregister_code(KC_DEL);
                    panic_del = false;
                }
                else {
                    unregister_code(KC_BSPACE);
                }
            }
            return false;
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
        case TG_LBK:
            if (record->event.pressed) {
                lbk_mode = !lbk_mode;
            }
            break;
        case TG_RBK:
            if (record->event.pressed) {
                rbk_mode = !rbk_mode;
            }
            break;
        case KC_SPACE:
            if (get_mods() && record->event.pressed) {
                unregister_code(KC_SPACE);
            }
            break;
        case KC_CAPS:
            // TODO: toggle internal state
            break;

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
        bool LCTL_MASK = (get_mods() & MOD_BIT(KC_LCTL));
        bool RCTL_MASK = (get_mods() & MOD_BIT(KC_RCTL));
        bool CTL_MASK  = LCTL_MASK || RCTL_MASK;

        switch (keycode) {
            case KC_S: // CTRL+S
                if (record->event.pressed && CTL_MASK) {
                    PLAY_SONG(save_song);
                }
                break;
            case KC_C: // CTRL+C
                if (record->event.pressed && CTL_MASK) {
                    PLAY_SONG(copy_song);
                }
                break;
            case KC_V: // CTRL+V
                if (record->event.pressed && CTL_MASK) {
                    PLAY_SONG(paste_song);
                }
                break;
            case KC_X: // CTRL+X
                if (record->event.pressed && CTL_MASK) {
                    PLAY_SONG(cut_song);
                }
                break;
            case KC_Z: // CTRL+Z
                if (record->event.pressed && CTL_MASK) {
                    PLAY_SONG(undo_song);
                }
                break;
            case KC_Y: // CTRL+Y
                if (record->event.pressed && CTL_MASK) {
                    PLAY_SONG(redo_song);
                }
                break;
            case KC_CAPS:
                if (record->event.pressed) { // TODO: sound based on internal state
                    PLAY_SONG(caps_on_song);
                }
                break;
            case TG_LBK:
                if (record->event.pressed) {
                    if (lbk_mode) {
                        PLAY_SONG(bk_activate_song);
                    }
                    else{
                        PLAY_SONG(bk_deactivate_song);
                    }
                }
                break;
            case TG_RBK:
                if (record->event.pressed) {
                    if (rbk_mode) {
                        PLAY_SONG(bk_activate_song);
                    }
                    else {
                        PLAY_SONG(bk_deactivate_song);
                    }
                }
                break;
        };
    #endif

    /*
        ██████  ██████   █████   ██████ ██   ██ ███████ ████████ ███████ 
        ██   ██ ██   ██ ██   ██ ██      ██  ██  ██         ██    ██      
        ██████  ██████  ███████ ██      █████   █████      ██    ███████ 
        ██   ██ ██   ██ ██   ██ ██      ██  ██  ██         ██         ██ 
        ██████  ██   ██ ██   ██  ██████ ██   ██ ███████    ██    ███████
    */

    bool lbk_key = (keycode == LBK_P || keycode == LBK_S || keycode == LBK_C || keycode == LBK_A);
    bool rbk_key = (keycode == RBK_P || keycode == RBK_S || keycode == RBK_C || keycode == RBA_A);

    // left-side held modifiers
    if (lbk_key && /* TODO: key is held */ false) {
        if (keycode == LBK_P) {
            keypress(record->event.pressed, KC_LCTL);
        }
        else if (keycode == LBK_S) {
            keypress(record->event.pressed, KC_LALT);
        }
        else if (keycode == LBK_C) {
            keypress(record->event.pressed, KC_LGUI);
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
        bool LSFT_MASK = (get_mods() & MOD_BIT(KC_LSFT));
        bool RSFT_MASK = (get_mods() & MOD_BIT(KC_RSFT));

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
            else if (keycode == LBK_A || keycode == RBA_A) {
                keypress(record->event.pressed, KC_RABK);
            }

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
            else if (keycode == LBK_A || keycode == RBA_A) {
                keypress(record->event.pressed, KC_LABK);
            }
        }
    }

    // left-side one-shot modifiers
    else if (lbk_key) {
        if (keycode == LBK_P) {
            if (record->event.pressed) {
                set_oneshot_mods(MOD_LCTL);
            }
            keypress(record->event.pressed, KC_LCTL);
        }
        else if (keycode == LBK_S) {
            if (record->event.pressed) {
                set_oneshot_mods(MOD_LALT);
            }
            keypress(record->event.pressed, KC_LALT);
        }
        else if (keycode == LBK_C) {
            if (record->event.pressed) {
                set_oneshot_mods(MOD_LGUI);
            }
            keypress(record->event.pressed, KC_LGUI);
        }
        else if (keycode == LBK_A) {
            if (record->event.pressed) {
                layer_on(_HYPER);           // TODO: keep HYPER on if no key pressed while held
            }
            else {
                layer_off(_HYPER);
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
        else if (keycode == RBA_A) {
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
                tap_code(KC_WH_U);
            }
            else {
                tap_code(KC_WH_D);
            }
            break;
        case SCROLL_H:
            if (clockwise) {
                tap_code(KC_WH_R);
            }
            else {
                tap_code(KC_WH_L);
            }
            break;
    }
}
#endif
