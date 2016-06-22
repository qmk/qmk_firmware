#include "ergodox_ez.h"
#include "led.h"
#include "debug.h"
#include "action_layer.h"
#include "action_util.h"
#include "mousekey.h"

#define BASE   0 // default layer
#define SYMB   1 // symbols layer
#define MDIA   2 // media layer
#define SPEC   3 // special layer

#define LCaps 10 // left caps-shift key
#define LSymb 11 // left symbol-shift key
#define LMdia 12 // left media-shift key
#define LSpec 13 // left special-shift key
#define RCaps 14 // right caps-shift key
#define RSymb 15 // right symbol-shift key
#define RMdia 16 // right media-shift key
#define RSpec 17 // right special-shift key

#define MUL   20 // mouse up left
#define MUR   21 // mouse up right
#define MDL   22 // mouse down left
#define MDR   23 // mouse down right

/*
 * The Ordinary Layout for the Ergodox EZ keyboard, v4
 * 
 * Modifications from default by Nicholas Keene ergodoxez@nicholaskeene.com
 *
 * No rights reserved. This software is in the public domain.
 * Credit me if you are friendly but if you're a jerk don't bother.
 * 
 * Details: readme.md
 *          https://github.com/nrrkeene/qmk_firmware/tree/master/keyboard/ergodox_ez/keymaps/ordinary
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/******* Base Layer ********************************************************************************************************
 *
 * ,------------------------------------------------------.           ,------------------------------------------------------.
 * | Special `~ |   1  |   2  |   3  |   4  |   5  | ESC  |           |  -   |   6  |   7  |   8  |   9  |   0  | =+ Special |
 * |------------+------+------+------+------+-------------|           |------+------+------+------+------+------+------------|
 * | Media  Tab |   Q  |   W  |   E  |   R  |   T  |   [  |           |  ]   |   Y  |   U  |   I  |   O  |   P  | \|   Media |
 * |------------+------+------+------+------+------|      |           |      |------+------+------+------+------+------------|
 * | Symbol     |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |  ;   | '"  Symbol |
 * |------------+------+------+------+------+------|Shift |           | Tab  |------+------+------+------+------+------------|
 * | Capitals   |   Z  |   X  |   C  |   V  |   B  | -Tab |           |      |   N  |   M  |   ,  |   .  |  /   |   Capitals |
 * `------------+------+------+------+------+-------------'           `-------------+------+------+------+------+------------'
 *      | LCtrl | Meh  |Hyper | LAlt | LGui |                                       | RGui | RAlt | Hyper|  Meh | RCtrl |
 *      `-----------------------------------'                                       `-----------------------------------'
 *                                          ,-------------.           ,-------------.
 *                                          | Home | End  |           | Left | Right|
 *                                   ,------|------|------|           |------+------+------.
 *                                   |      |      | PgUp |           |  Up  |      |      |
 *                                   |Backsp| Del  |------|           |------| Enter| Space|
 *                                   |      |      | PgDn |           | Down |      |      |
 *                                   `--------------------'           `--------------------'
 */
[BASE] = KEYMAP(
// left hand
 F(LSpec),KC_1,KC_2,KC_3   ,KC_4  ,KC_5  ,KC_ESC
,F(LMdia)  ,KC_Q   ,KC_W   ,KC_E   ,KC_R  ,KC_T  ,KC_LBRC
,M(LSymb)  ,KC_A   ,KC_S   ,KC_D   ,KC_F  ,KC_G
,M(LCaps)  ,KC_Z   ,KC_X   ,KC_C   ,KC_V  ,KC_B  ,LSFT(KC_TAB)
,KC_LCTL   ,KC_MEH ,KC_HYPR,KC_LALT,KC_LGUI
                                         ,KC_HOME,KC_END
                                                 ,KC_PGUP
                                 ,KC_BSPC,KC_DEL ,KC_PGDN
                                                                      // right hand
                                                                     ,KC_MINS ,KC_6   ,KC_7   ,KC_8   ,KC_9    ,KC_0     ,F(RSpec)
                                                                     ,KC_RBRC ,KC_Y   ,KC_U   ,KC_I   ,KC_O    ,KC_P     ,F(RMdia)
                                                                              ,KC_H   ,KC_J   ,KC_K   ,KC_L    ,KC_SCLN  ,F(RSymb)
                                                                     ,KC_TAB  ,KC_N   ,KC_M   ,KC_COMM,KC_DOT  ,KC_SLSH  ,M(RCaps)
                                                                                      ,KC_RGUI,KC_RALT,KC_HYPR ,KC_MEH   ,KC_RCTL
                                                                     ,KC_LEFT ,KC_RGHT
                                                                     ,KC_UP
                                                                     ,KC_DOWN ,KC_ENT ,KC_SPC
    ),

/******* Symbols Layer *****************************************************************************************************
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * |           |  F1  |  F2  |  F3  |  F4  |  F5  | Esc  |           |  -   |  F6  |  F7  |  F8  |  F9  |  F10 |           |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * |           |   !  |   @  |   {  |   }  |   &  |  <   |           |  >   |   |  |   7  |   8  |   9  |   /  |           |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |           |   #  |   $  |   (  |   )  |   `  |------|           |------|   /  |   4  |   5  |   6  |   *  |           |
 * |-----------+------+------+------+------+------| Tab  |           | Shift|------+------+------+------+------+-----------|
 * |           |   %  |   ^  |   [  |   ]  |   ~  |      |           |  -Tab|   \  |   1  |   2  |   3  |   -  |           |
 * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
 *     | LCtrl | Meh  |Hyper | LAlt | LGui |                                       |RGui/0|RAlt/.|Hypr/=|Meh/+ |RCtrl/Ent|
 *     `-----------------------------------'                                       `-------------------------------------'
 *                                         ,-------------.           ,-------------.
 *                                         | Left | Right|           | Home | End  |
 *                                  ,------|------|------|           |------+------+------.
 *                                  |      |      |  Up  |           | PgUp |      |      |
 *                                  |Space |Enter |------|           |------|BackSp| Del  |
 *                                  |      |      | Down |           | PgDn |      |      |
 *                                  `--------------------'           `--------------------'
 */
[SYMB] = KEYMAP(
// left hand
 KC_TRNS ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_ESC
,KC_TRNS ,KC_EXLM ,KC_AT   ,KC_LCBR ,KC_RCBR ,KC_AMPR ,LSFT(KC_COMM)
,KC_TRNS ,KC_HASH ,KC_DLR  ,KC_LPRN ,KC_RPRN ,KC_GRV 
,KC_TRNS ,KC_PERC ,KC_CIRC ,KC_LBRC ,KC_RBRC ,KC_TILD ,KC_TAB
,KC_LCTL   ,KC_MEH ,KC_HYPR,KC_LALT ,KC_LGUI
                                             ,KC_LEFT ,KC_RGHT
                                                      ,KC_UP
                                    ,KC_SPC  ,KC_ENT  ,KC_DOWN
                                                                     // right hand
                                                                     ,KC_MINS     ,KC_F6   ,KC_F7 ,KC_F8  ,KC_F9 ,KC_F10  ,KC_TRNS
                                                                     ,LSFT(KC_DOT),KC_PIPE ,KC_7  ,KC_8   ,KC_9  ,KC_SLSH ,KC_TRNS
                                                                                  ,KC_SLSH ,KC_4  ,KC_5   ,KC_6  ,KC_ASTR ,KC_TRNS
                                                                     ,LSFT(KC_TAB),KC_BSLS ,KC_1  ,KC_2   ,KC_3  ,KC_MINS ,KC_TRNS
                                                                                           ,GUI_T(KC_0),ALT_T(KC_DOT),ALL_T(KC_EQL),MEH_T(KC_PLUS),CTL_T(KC_ENT)
                                                                     ,KC_HOME     ,KC_END
                                                                     ,KC_PGUP
                                                                     ,KC_PGDN     ,KC_BSPC ,KC_DEL
),

/******* Media Layer *******************************************************************************************************
 *
 * ,---------------------------------------------------------------.           ,---------------------------------------------------------------.
 * |      |   F11   |   F12   |   F13   |   F14   |   F15   | Esc  |           |      |   F16   |   F17   |   F18   |   F19   |   F20   |      |
 * |------+---------+---------+---------+---------+----------------|           |------+---------+---------+---------+---------+---------+------|
 * |      |Shut Down|MouseUpLf|Mouse Up |MouseUpRg|Volume Up|Scroll|           |Scroll|PrintScrn|   Home  |    Up   |   PgUp  |   Mail  |      |
 * |------+---------+---------+---------+---------+---------|  Up  |           |  Up  |---------+---------+---------+---------+---------+------|
 * |      |  Sleep  |MouseLeft|MouseDown|MouseRght|Volume Dn|------|           |------| Num Lock|   Left  |   Down  |   Right | MyComp  |      |
 * |------+---------+---------+---------+---------+---------|Scroll|           |Scroll|---------+---------+---------+---------+---------+------|
 * |      |         |MouseDnLf|MouseDown|MouseDnRg|  Mute   | Down |           | Down |         |   End   |   Down  |   PgDn  |         |      |
 * `------+---------+---------+---------+---------+----------------'           `----------------+---------+---------+---------+---------+------'
 *  |LCtrl|   Meh   |  MClick | LClick  |  R Click|                                             |Cmd/Insrt|Optn/Del | Hyper   |  Meh    |RCtrl|
 *  `---------------------------------------------'                                             `---------------------------------------------'
 *                                                   ,-------------.           ,-------------.
 *                                                   | Stop |Refrsh|           | Prev | Next |
 *                                            ,------|------|------|           |------+------+------.
 *                                            |Brwser|Brwser|Search|           |VolUp |      |      |
 *                                            |Back  | Fwd  |------|           |------| Stop | Play-|
 *                                            |      |      | Home |           |VolDn |      | Pause|
 *                                            `--------------------'           `--------------------'
 */
[MDIA] = KEYMAP(
// left hand
 KC_TRNS ,KC_F11   ,KC_F12  ,KC_F13   ,KC_F14  ,KC_F15  ,KC_ESC
,KC_TRNS ,KC_POWER ,M(MUL)  ,KC_MS_U  ,M(MUR)  ,KC_VOLU ,KC_WH_U
,KC_TRNS ,KC_SLEP  ,KC_MS_L ,KC_MS_D  ,KC_MS_R ,KC_VOLD
,KC_TRNS ,KC_NO    ,M(MDL)  ,KC_MS_D  ,M(MDR)  ,KC_MUTE ,KC_WH_D
,KC_LCTL ,KC_MEH   ,KC_BTN3 ,KC_BTN1  ,KC_BTN2
                                               ,KC_WSTP ,KC_WREF
                                                        ,KC_WSCH
                                      ,KC_WBAK ,KC_NO   ,KC_WHOM
                                                                     // right hand
                                                                     ,KC_NO    ,KC_F16  ,KC_F17       ,KC_F18       ,KC_F19  ,KC_F20  ,KC_TRNS
                                                                     ,KC_WH_U  ,KC_PSCR ,KC_HOME      ,KC_UP        ,KC_PGUP ,KC_MAIL ,KC_TRNS
                                                                               ,KC_NLCK ,KC_LEFT      ,KC_DOWN      ,KC_RIGHT,KC_MYCM ,KC_TRNS
                                                                     ,KC_WH_D  ,KC_NO   ,KC_END       ,KC_DOWN      ,KC_PGDN ,KC_NO   ,KC_TRNS
                                                                                        ,GUI_T(KC_INS),ALT_T(KC_DEL),KC_HYPR ,KC_MEH  ,KC_RCTL
                                                                     ,KC_MPRV  ,KC_MNXT
                                                                     ,KC_VOLU
                                                                     ,KC_VOLD  ,KC_MSTP ,KC_MPLY
),

/******* Special Layer *****************************************************************************************************
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * |           |  Esc |      |      |      |      |      |           |      |      |      |      |      | Bspc |           |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * |           |      |      |      |      |      |      |           |      |      |      |      |      |      |           |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |           |      |      |      |      |      |------|           |------|      |      |      |      |      |           |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * |           |      |      |      |      |      |      |           |      |      |      |      |      |      | RShift    |
 * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
 *      |      |      |      |      |      |                                       |      |      |      |      |      |
 *      `----------------------------------'                                       `----------------------------------'
 *                                         ,-------------.           ,-------------.
 *                                         |      |      |           |      |      |
 *                                  ,------|------|------|           |------+------+------.
 *                                  |      |      |      |           |      |      |      |
 *                                  |      |      |------|           |------|      |      |
 *                                  |      |      |      |           |      |      |      |
 *                                  `--------------------'           `--------------------'
 */
[SPEC] = KEYMAP(
// left hand
 KC_TRNS ,KC_ESC  ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS

                                             ,KC_TRNS ,KC_TRNS
                                                      ,KC_TRNS
                                     ,KC_TRNS,KC_TRNS ,KC_TRNS
                                                                     // right hand
                                                                     ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_BSPC ,KC_TRNS
                                                                     ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
                                                                              ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
                                                                     ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_RSFT
                                                                                       ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS

                                                                     ,KC_TRNS ,KC_TRNS
                                                                     ,KC_TRNS
                                                                     ,KC_TRNS ,KC_TRNS ,KC_TRNS
    )
};

const uint16_t PROGMEM fn_actions[] = {
     // the faux shift keys are implemented as macro taps
     [LCaps] = ACTION_MACRO_TAP(LCaps)
    ,[LSymb] = ACTION_MACRO_TAP(LSymb)
    ,[LMdia] = ACTION_MACRO_TAP(LMdia)
    ,[LSpec] = ACTION_MACRO_TAP(LSpec)
    ,[RCaps] = ACTION_MACRO_TAP(RCaps)
    ,[RSymb] = ACTION_MACRO_TAP(RSymb)
    ,[RMdia] = ACTION_MACRO_TAP(RMdia)
    ,[RSpec] = ACTION_MACRO_TAP(RSpec)
};

uint16_t caps_shift = 0;
uint16_t symb_shift = 0;
uint16_t mdia_shift = 0;

bool symb_lock = false;
bool mdia_lock = false;

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch(id) {
        // There are two shift keys for each layer so we increment a layer_shift var when one
        // is pressed and decrement when one is released. If both are pressed at the same time
        // then the layer is locked (or unlocked). The shift counts are bound between 0 and 2
        // only because sometimes rapid pressing led to irregular events; this way the states
        // are self healing during use.

        case LCaps: // both caps-shift keys trigger Left Shift
        case RCaps: // so they don't interfere with the magic combo
        if (record->event.pressed && !record->tap.count) {
            if(++caps_shift > 2) caps_shift = 2;
            if(caps_shift == 2)  {
                register_code(KC_CAPS);
                unregister_code(KC_CAPS);
            } else if(caps_shift == 1) {
                register_code(KC_LSFT);
            }
        } else {
            if(--caps_shift < 0) caps_shift = 0;
            if(caps_shift == 0) unregister_code(KC_LSFT);
        }
        break;

        case LSymb:
        if (record->event.pressed) {
            if(++symb_shift > 2) symb_shift = 2;
            if(symb_shift == 2)  {
                symb_lock = !symb_lock;
            } else if(symb_shift == 1) {
                layer_on(SYMB);
            }
        } else {
            if(--symb_shift < 0) symb_shift = 0;
            if((symb_shift == 0) && (!symb_lock)) layer_off(SYMB);
        }
        break;

        case LMdia:
        if (record->event.pressed) {
            if (record->tap.count && (!mdia_shift) && (!mdia_lock)) {
                register_code(KC_TAB);
            } else {
                if(++mdia_shift > 2) mdia_shift = 2;
                if(mdia_shift == 2)  {
                    mdia_lock = !mdia_lock;
                } else if(mdia_shift == 1) {
                    layer_on(MDIA);
                }
            }
        } else {
            if(record->tap.count && (!mdia_shift) && (!mdia_lock)) {
                unregister_code(KC_TAB);
            } else {
                if(--mdia_shift < 0) mdia_shift = 0;
                if((!mdia_shift) && (!mdia_lock)) layer_off(MDIA);
            }
        }
        break;

        case LSpec:
        if (record->event.pressed) {
            if (record->tap.count && !record->tap.interrupted) {
                register_code(KC_GRV);
            } else {
                layer_on(SPEC);
            }
        } else {
            if(record->tap.count && !record->tap.interrupted) {
                unregister_code(KC_GRV);
            } else {
                layer_off(SPEC);
            }
        }
        break;

        case RSymb:
        if (record->event.pressed) {
            if (record->tap.count && (!symb_shift) && (!symb_lock)) {
                register_code(KC_QUOT);
            } else {
                if(++symb_shift > 2) symb_shift = 2;
                if(symb_shift == 2)  {
                    symb_lock = !symb_lock;
                } else if(symb_shift == 1) {
                    layer_on(SYMB);
                }
            }
        } else {
            if(record->tap.count && symb_shift == 0) {
                unregister_code(KC_QUOT);
            } else {
                if(--symb_shift < 0) symb_shift = 0;
                if((!symb_shift) && (!symb_lock)) layer_off(SYMB);
            }
        }
        break;

        case RMdia:
        if (record->event.pressed) {
            if (record->tap.count && (!mdia_shift) && (!mdia_lock)) {
                register_code(KC_BSLS);
            } else {
                if(++mdia_shift > 2) mdia_shift = 2;
                if(mdia_shift == 2)  {
                    mdia_lock = !mdia_lock;
                } else if(mdia_shift == 1) {
                    layer_on(MDIA);
                }
            }
        } else {
            if(record->tap.count && (!mdia_shift) && (!mdia_lock)) {
                unregister_code(KC_BSLS);
            } else {
                if(--mdia_shift < 0) mdia_shift = 0;
                if((!mdia_shift) && (!mdia_lock)) layer_off(MDIA);
            }
        }
        break;

        case RSpec:
        if (record->event.pressed) {
            if (record->tap.count && !record->tap.interrupted) {
                register_code(KC_EQL);
            } else {
                layer_on(SPEC);
            }
        } else {
            if(record->tap.count && !record->tap.interrupted) {
                unregister_code(KC_EQL);
            } else {
                layer_off(SPEC);
            }
        }
        break;

        // mouse diagonals

        case MUL: // mouse up left
        if (record->event.pressed) {
            mousekey_on(KC_MS_UP);
            mousekey_on(KC_MS_LEFT);
            mousekey_send();
        } else {
            mousekey_off(KC_MS_UP);
            mousekey_off(KC_MS_LEFT);
            mousekey_send();
        }
        break;

        case MUR: // mouse up right
        if (record->event.pressed) {
            mousekey_on(KC_MS_UP);
            mousekey_on(KC_MS_RIGHT);
            mousekey_send();
        } else {
            mousekey_off(KC_MS_UP);
            mousekey_off(KC_MS_RIGHT);
            mousekey_send();
        }
        break;

        case MDL: // mouse down left
        if (record->event.pressed) {
            mousekey_on(KC_MS_DOWN);
            mousekey_on(KC_MS_LEFT);
            mousekey_send();
        } else {
            mousekey_off(KC_MS_DOWN);
            mousekey_off(KC_MS_LEFT);
            mousekey_send();
        }
        break;

        case MDR: // mouse down right
        if (record->event.pressed) {
            mousekey_on(KC_MS_DOWN);
            mousekey_on(KC_MS_RIGHT);
            mousekey_send();
        } else {
            mousekey_off(KC_MS_DOWN);
            mousekey_off(KC_MS_RIGHT);
            mousekey_send();
        }
        break;

        default:
            // none
            break;
    }
    
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    // shift or caps lock turns on red light
    if(caps_shift || (keyboard_report->mods & MOD_BIT(KC_RSFT)) || (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK))) {
        ergodox_right_led_1_on();
    } else {
        ergodox_right_led_1_off();
    }

    // Symbol layer turns on green light
    if(layer_state & (1UL<<SYMB)) {
        ergodox_right_led_2_on();
    } else {
        ergodox_right_led_2_off();
    }

    // Media layer turns on blue light
    if(layer_state & (1UL<<MDIA)) {
        ergodox_right_led_3_on();
    } else {
        ergodox_right_led_3_off();
    }
};

