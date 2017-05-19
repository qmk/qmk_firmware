#include "ergodox.h"
#include "led.h"
#include "debug.h"
#include "action_layer.h"
#include "action_util.h"

#define BASE   0 // default layer
#define SYMB   1 // symbols layer
#define MDIA   2 // media layer
#define SPEC   3 // special layer

#define NmPad 10 // left symbol-shift key
#define LMdia 11 // left media-shift key
#define LSpec 12 // left special-shift key
#define Symbl 13 // right symbol-shift key
#define RMdia 14 // right media-shift key
#define RSpec 15 // right special-shift key

#define MUL   20 // mouse up left
#define MUR   21 // mouse up right
#define MDL   22 // mouse down left
#define MDR   23 // mouse down right

#define CO_PA M(30) // hold copy, tap paste
#define CU_PA M(31) // hold cut, tap paste

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/******* Base Layer *****************************************************************************************************
 *
 * ,------------------------------------------------------.       ,------------------------------------------------------.
 * |     ESC    |   1  |   2  |   3  |   4  |   5  |   6  |       |   7  |   8  |   9  |   0  |   -  |   =  |     `~     |
 * |------------+------+------+------+------+-------------|       |------+------+------+------+------+------+------------|
 * |     TAB    |   Q  |   W  |   E  |   R  |   T  | CUT  |       | PgUp |   Y  |   U  |   I  |   O  |   P  | \|   MEDIA |
 * |------------+------+------+------+------+------| PAST |       |      |------+------+------+------+------+------------|
 * |   NUMPAD   |   A  |   S  |   D  |   F  |   G  |------|       |------|   H  |   J  |   K  |   L  |  ;   | '"  SYMBOL |
 * |------------+------+------+------+------+------| COPY |       | PgDn |------+------+------+------+------+------------|
 * |   LSHIFT   |   Z  |   X  |   C  |   V  |   B  | PAST |       |      |   N  |   M  |   ,  |   .  |  /   |   RSHIFT   |
 * `------------+------+------+------+------+-------------'       `-------------+------+------+------+------+------------'
 *      |  LCTL | DEL  | HOME | END  | LALT |                                   | RALT |  MEH | HYPR |  DEL | RCTRL |
 *      `-----------------------------------'                                   `-----------------------------------'
 *                                          ,-------------.       ,-------------.
 *                                          | Zoom-|  (   |       |   )  | Zoom+|
 *                                   ,------|------|------|       |------+------+------.
 *                                   |      |      |  [   |       |   ]  |      |      |
 *                                   | SPC  | SPEC |------|       |------|  ENT | BKSP |
 *                                   |      |  TG  |  {   |       |   }  |      |      |
 *                                   `--------------------'       `--------------------'
 */
[BASE] = KEYMAP(
// left hand
 KC_ESC  ,KC_1  ,KC_2   ,KC_3  ,KC_4  ,KC_5   ,KC_6
,KC_TAB  ,KC_Q  ,KC_W   ,KC_E  ,KC_R  ,KC_T   ,CU_PA
,M(NmPad),KC_A  ,KC_S   ,KC_D  ,KC_F  ,KC_G
,KC_LSFT ,KC_Z  ,KC_X   ,KC_C  ,KC_V  ,KC_B   ,CO_PA
,KC_LCTL ,KC_DEL,KC_HOME,KC_END,KC_LALT
                                 ,LCTL(KC_MINS) ,KC_LCBR
                                                ,KC_LPRN
                               ,KC_SPC ,F(LSpec),KC_LBRC
                                                                  // right hand
                                                                 ,KC_7    ,KC_8   ,KC_9   ,KC_0   ,KC_MINS ,KC_EQL   ,KC_GRV
                                                                 ,KC_PGUP ,KC_Y   ,KC_U   ,KC_I   ,KC_O    ,KC_P     ,F(RMdia)
                                                                          ,KC_H   ,KC_J   ,KC_K   ,KC_L    ,KC_SCLN  ,F(Symbl)
                                                                 ,KC_PGDN ,KC_N   ,KC_M   ,KC_COMM,KC_DOT  ,KC_SLSH  ,KC_RSFT
                                                                                  ,KC_RALT,KC_MEH ,KC_HYPR ,KC_DEL   ,KC_RCTL
                                                                 ,KC_RCBR ,LCTL(KC_EQL)
                                                                 ,KC_RPRN
                                                                 ,KC_RBRC ,KC_ENT ,KC_BSPC
    ),

/******* Numpad / Symbols Layer ***************************************************************************************
 *
 * ,-----------------------------------------------------.       ,-----------------------------------------------------.
 * |           |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |       |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |           |
 * |-----------+------+------+------+------+-------------|       |------+------+------+------+------+------+-----------|
 * |           |   !  |   @  |   {  |   }  |   &  |      |       |      |   |  |   7  |   8  |   9  |   /  |           |
 * |-----------+------+------+------+------+------|      |       |      |------+------+------+------+------+-----------|
 * |           |   #  |   $  |   (  |   )  |   `  |------|       |------|   /  |   4  |   5  |   6  |   *  |           |
 * |-----------+------+------+------+------+------|      |       |      |------+------+------+------+------+-----------|
 * |           |   %  |   ^  |   [  |   ]  |   ~  |      |       |      |   \  |   1  |   2  |   3  |   -  |           |
 * `-----------+------+------+------+------+-------------'       `-------------+------+------+------+------+-----------'
 *     |       |      |      |      |      |                                   |   0  |   .  |   =  |   +  |       |
 *     `-----------------------------------'                                   `-----------------------------------'
 *                                         ,-------------.       ,-------------.
 *                                         |      |      |       |      |      |
 *                                  ,------|------|------|       |------+------+------.
 *                                  |      |      |      |       |      |      |      |
 *                                  |      | SPEC |------|       |------|      |      |
 *                                  |      |  TG  |      |       |      |      |      |
 *                                  `--------------------'       `--------------------'
 */
[SYMB] = KEYMAP(
// left hand
 KC_TRNS ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_F6
,KC_TRNS ,KC_EXLM ,KC_AT   ,KC_LCBR ,KC_RCBR ,KC_AMPR ,KC_TRNS
,KC_TRNS ,KC_HASH ,KC_DLR  ,KC_LPRN ,KC_RPRN ,KC_GRV
,KC_TRNS ,KC_PERC ,KC_CIRC ,KC_LBRC ,KC_RBRC ,KC_TILD ,KC_TRNS
,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
                                             ,KC_TRNS ,KC_TRNS
                                                      ,KC_TRNS
                                    ,KC_TRNS ,F(LSpec),KC_TRNS
                                                                 // right hand
                                                                 ,KC_F7   ,KC_F8   ,KC_F9    ,KC_F10    ,KC_F11   ,KC_F12  ,KC_TRNS
                                                                 ,KC_TRNS ,KC_PIPE ,KC_KP_7  ,KC_KP_8   ,KC_KP_9  ,KC_SLSH ,KC_TRNS
                                                                          ,KC_SLSH ,KC_KP_4  ,KC_KP_5   ,KC_KP_6  ,KC_ASTR ,KC_TRNS
                                                                 ,KC_TRNS ,KC_BSLS ,KC_KP_1  ,KC_KP_2   ,KC_KP_3  ,KC_MINS ,KC_TRNS
                                                                                   ,KC_KP_0  ,KC_DOT    ,KC_EQL   ,KC_PLUS ,KC_TRNS
                                                                 ,KC_TRNS ,KC_TRNS
                                                                 ,KC_TRNS
                                                                 ,KC_TRNS ,KC_TRNS ,KC_TRNS
),

/******* Media Layer *******************************************************************************************************************
 *
 * ,---------------------------------------------------------------.    ,---------------------------------------------------------------.
 * |      |   F11   |   F12   |   F13   |   F14   |   F15   |  F16 |    | F17  |   F18   |   F19   |   F20   |         |         |      |
 * |------+---------+---------+---------+---------+----------------|    |------+---------+---------+---------+---------+---------+------|
 * |      |Shut Down|MouseUpLf|Mouse Up |MouseUpRg|Volume Up|Scroll|    |Scroll|PrintScrn|   Home  |    Up   |   PgUp  |   Mail  |      |
 * |------+---------+---------+---------+---------+---------|  Up  |    |  Up  |---------+---------+---------+---------+---------+------|
 * |      |  Sleep  |MouseLeft|MouseDown|MouseRght|Volume Dn|------|    |------| Num Lock|   Left  |   Down  |   Right | MyComp  |      |
 * |------+---------+---------+---------+---------+---------|Scroll|    |Scroll|---------+---------+---------+---------+---------+------|
 * |      |         |MouseDnLf|MouseDown|MouseDnRg|  Mute   | Down |    | Down |         |   End   |   Down  |   PgDn  |         |      |
 * `------+---------+---------+---------+---------+----------------'    `----------------+---------+---------+---------+---------+------'
 *  |     |         |  MClick | LClick  |  R Click|                                      |Cmd/Insrt|   MEH   |  HYPR   |Optn/Del |RCtrl|
 *  `---------------------------------------------'                                      `---------------------------------------------'
 *                                                   ,-------------.    ,-------------.
 *                                                   | Stop |Refrsh|    | Prev | Next |
 *                                            ,------|------|------|    |------+------+------.
 *                                            |Brwser|Brwser|Search|    |VolUp |      |      |
 *                                            |Back  | Fwd  |------|    |------| Stop | Play-|
 *                                            |      |      | Home |    |VolDn |      | Pause|
 *                                            `--------------------'    `--------------------'
 */
[MDIA] = KEYMAP(
// left hand
 KC_TRNS ,KC_F11   ,KC_F12  ,KC_F13   ,KC_F14  ,KC_F15  ,KC_F16
,KC_TRNS ,KC_POWER ,M(MUL)  ,KC_MS_U  ,M(MUR)  ,KC_VOLU ,KC_WH_U
,KC_TRNS ,KC_SLEP  ,KC_MS_L ,KC_MS_D  ,KC_MS_R ,KC_VOLD
,KC_TRNS ,KC_NO    ,M(MDL)  ,KC_MS_D  ,M(MDR)  ,KC_MUTE ,KC_WH_D
,KC_TRNS ,KC_TRNS  ,KC_BTN3 ,KC_BTN1  ,KC_BTN2
                                               ,KC_WSTP ,KC_WREF
                                                        ,KC_WSCH
                                      ,KC_WBAK ,KC_NO   ,KC_WHOM
                                                                     // right hand
                                                                     ,KC_F17   ,KC_F18  ,KC_F19       ,KC_F20       ,KC_TRNS ,KC_TRNS ,KC_TRNS
                                                                     ,KC_WH_U  ,KC_PSCR ,KC_HOME      ,KC_UP        ,KC_PGUP ,KC_MAIL ,KC_TRNS
                                                                               ,KC_NLCK ,KC_LEFT      ,KC_DOWN      ,KC_RIGHT,KC_MYCM ,KC_TRNS
                                                                     ,KC_WH_D  ,KC_NO   ,KC_END       ,KC_DOWN      ,KC_PGDN ,KC_NO   ,KC_TRNS
                                                                                        ,GUI_T(KC_INS),KC_MEH ,KC_HYPR ,ALT_T(KC_DEL)  ,KC_RCTL
                                                                     ,KC_MPRV  ,KC_MNXT
                                                                     ,KC_VOLU
                                                                     ,KC_VOLD  ,KC_MSTP ,KC_MPLY
),

/******* Special Layer *************************************************************************************************
 *
 * ,-------------------------------------------------------.    ,-------------------------------------------------------.
 * |             |MdiaLk|SymbLk|CapsLk|      |      |      |    |      |      |      |      |      |      |             |
 * |-------------+------+------+------+------+-------------|    |------+------+------+------+------+------+-------------|
 * |             |      |      |  UP  |      |CTRL+T|      |    |      |      |      |      |      |      |             |
 * |-------------+------+------+------+------+------|      |    |      |------+------+------+------+------+-------------|
 * |             |CTRL+A| LEFT | DOWN | RIGHT|CTRL+F|------|    |------|      |      |      |      |      |             |
 * |-------------+------+------+------+------+------|      |    |      |------+------+------+------+------+-------------|
 * |             |      |      |CTRL+S|CTRL+Z|      |      |    |      |      |      |      |      |      |             |
 * `-------------+------+------+------+------+-------------'    `-------------+------+------+------+------+-------------'
 *      |        |      |      |      |      |                                |      |      |      |      |        |
 *      `------------------------------------'                                `------------------------------------'
 *                                         ,-------------.     ,-------------.
 *                                         |      |      |     |      |      |
 *                                  ,------|------|------|     |------+------+------.
 *                                  |      |      |      |     |      |      |      |
 *                                  |      | SPEC |------|     |------|      |      |
 *                                  |      |  TG  |      |     |      |      |      |
 *                                  `--------------------'     `--------------------'
 */
[SPEC] = KEYMAP(
// left hand
 KC_TRNS ,F(LMdia)  ,F(NmPad),KC_CAPS    ,KC_TRNS     ,KC_TRNS    ,KC_TRNS
,KC_TRNS ,KC_TRNS   ,KC_TRNS ,KC_UP      ,KC_TRNS     ,LCTL(KC_T) ,KC_TRNS
,KC_TRNS ,LCTL(KC_A),KC_LEFT ,KC_DOWN    ,KC_RIGHT    ,LCTL(KC_F)
,KC_CAPS ,KC_TRNS   ,KC_TRNS ,LCTL(KC_S) ,LCTL(KC_Z)  ,KC_TRNS    ,KC_TRNS
,KC_TRNS ,KC_TRNS   ,KC_TRNS ,KC_TRNS    ,KC_TRNS
                                               ,KC_TRNS ,KC_TRNS
                                                        ,KC_TRNS
                                       ,KC_TRNS,KC_TRNS ,KC_TRNS
                                                             // right hand
                                                             ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
                                                             ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_LBRC ,KC_RBRC ,KC_TRNS
                                                                      ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
                                                             ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
                                                                               ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS ,KC_TRNS
                                                             ,KC_TRNS ,KC_TRNS
                                                             ,KC_TRNS
                                                             ,KC_TRNS ,KC_TRNS ,KC_TRNS
    )
};

const uint16_t PROGMEM fn_actions[] = {
     // the faux shift keys are implemented as macro taps
     [NmPad] = ACTION_MACRO_TAP(NmPad)
    ,[LMdia] = ACTION_MACRO_TAP(LMdia)
    ,[LSpec] = ACTION_MACRO_TAP(LSpec)
    ,[Symbl] = ACTION_MACRO_TAP(Symbl)
    ,[RMdia] = ACTION_MACRO_TAP(RMdia)
    ,[RSpec] = ACTION_MACRO_TAP(RSpec)
};

uint16_t symb_shift = 0;
uint16_t mdia_shift = 0;
uint16_t spec_shift = 0;

bool mdia_lock = false;
bool symb_lock = false;

static uint16_t key_timer;

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch(id) {
        // There are two shift keys for each layer so we increment a layer_shift var when one
        // is pressed and decrement when one is released. If both are pressed at the same time
        // then the layer is locked (or unlocked). The shift counts are bound between 0 and 2
        // only because sometimes rapid pressing led to irregular events; this way the states
        // are self healing during use.

        case NmPad:                                               //
        if (record->event.pressed) {                              // when the NmPad button is pressed
            if(++symb_shift > 2) mdia_shift = 2;                  // increment the symb shift count, max two
            if(spec_shift) symb_lock = !symb_lock;                // if the Special layer is on, toggle the shift lock
            layer_on(SYMB);                                       // in any case, turn on the Symbols layer
        } else {                                                  // when the NmPad button is released
            if(--symb_shift < 0) symb_shift = 0;                  // decrement the shift count, minimum zero
            if((!symb_shift) && (!symb_lock)) layer_off(SYMB);    // if both shifts are released and the lock is off, turn off the Symbols layer
        }
        break;

        case LMdia:
        if (record->event.pressed) {
           if (record->tap.count && (!mdia_shift) && (!mdia_lock) && (!spec_shift)) {
                register_code(KC_TAB);
            } else {
                if(spec_shift) mdia_lock = !mdia_lock;
                if(++mdia_shift > 2) mdia_shift = 2;
                layer_on(MDIA);
            }
        } else {
            if(record->tap.count && (!mdia_shift) && (!mdia_lock) && (!spec_shift)) {
                unregister_code(KC_TAB);
            } else {
                if(--mdia_shift < 0) mdia_shift = 0;
                if((!mdia_shift) && (!mdia_lock)) layer_off(MDIA);
            }
        }
        break;

        case LSpec:
        if (record->event.pressed) {
            if(symb_shift) symb_lock == !symb_lock;
            else if(mdia_shift) mdia_lock = !mdia_lock;
            else if (record->tap.count && !record->tap.interrupted && (!spec_shift)) {
                register_code(KC_TRNS);
            } else {
                if(++spec_shift > 2) spec_shift = 2;
                layer_on(SPEC);
            }
        } else {
            if(record->tap.count && !record->tap.interrupted && (!spec_shift)) {
                unregister_code(KC_TRNS);
            } else {
                if(--spec_shift < 0) spec_shift = 0;
                if(!spec_shift) layer_off(SPEC);
            }
        }
        break;

        case Symbl:
        if (record->event.pressed) {
            if (record->tap.count && (!symb_shift) && (!symb_lock) && (!spec_shift)) {
                register_code(KC_QUOT);
            } else {
                if(++symb_shift > 2) symb_shift = 2;
                if(spec_shift) symb_lock = !symb_lock;
                layer_on(SYMB);
            }
        } else {
            if(record->tap.count && (!symb_shift) && (!symb_lock) && (!spec_shift)) {
                unregister_code(KC_QUOT);
            } else {
                if(--symb_shift < 0) symb_shift = 0;
                if((!symb_shift) && (!symb_lock)) layer_off(SYMB);
            }
        }
        break;

        case RMdia:
        if (record->event.pressed) {
            if (record->tap.count && (!mdia_shift) && (!mdia_lock) && (!spec_shift)) {
                register_code(KC_BSLS);
            } else {
                if(++mdia_shift > 2) mdia_shift = 2;
                if(spec_shift) mdia_lock = !mdia_lock;
                layer_on(MDIA);
            }
        } else {
            if(record->tap.count && (!mdia_shift) && (!mdia_lock) && (!spec_shift)) {
                unregister_code(KC_BSLS);
            } else {
                if(--mdia_shift < 0) mdia_shift = 0;
                if((!mdia_shift) && (!mdia_lock)) layer_off(MDIA);
            }
        }
        break;

        case RSpec:
        if (record->event.pressed) {
            if(symb_shift) symb_lock = !symb_lock;
            else if(mdia_shift) mdia_lock = !mdia_lock;
            else if (record->tap.count && !record->tap.interrupted && (!spec_shift)) {
                register_code(KC_EQL);
            } else {
                if(++spec_shift > 2) spec_shift = 2;
                layer_on(SPEC);
            }
        } else {
            if(record->tap.count && !record->tap.interrupted && (!spec_shift)) {
                unregister_code(KC_EQL);
            } else {
                if(--spec_shift < 0) spec_shift = 0;
                if(!spec_shift) layer_off(SPEC);
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

        case 30: { // start copy/paste macro
            if (record->event.pressed) {
                key_timer = timer_read(); // if the key is being pressed, we start the timer.
            }
            else { // this means the key was just released, so we can figure out how long it was pressed for (tap or "held down").
                if (timer_elapsed(key_timer) > 150) { // 150 being 150ms, the threshhold we pick for counting something as a tap.
                    return MACRO( D(LCTL), T(C), U(LCTL), END  );
                }
                else {
                    return MACRO( D(LCTL), T(V), U(LCTL), END  );
                }
            }
            break;
        } // end macro

        case 31: { // start cut/paste macro
            if (record->event.pressed) {
                key_timer = timer_read(); // if the key is being pressed, we start the timer.
            }
            else { // this means the key was just released, so we can figure out how long it was pressed for (tap or "held down").
                if (timer_elapsed(key_timer) > 150) { // 150 being 150ms, the threshhold we pick for counting something as a tap.
                    return MACRO( D(LCTL), T(X), U(LCTL), END  );
                }
                else {
                    return MACRO( D(LCTL), T(V), U(LCTL), END  );
                }
            }
            break;
        } // end macro

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
    if((keyboard_report->mods & MOD_BIT(KC_LSFT))
    || (keyboard_report->mods & MOD_BIT(KC_RSFT))
    || (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK))) {
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
