#include "ez/ez.h"
#include "ergodox.h"

#include "debug.h"
#include "action_layer.h"
#include "keymap_extras/keymap_german_ch.h"
#include "timer.h"


// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define BASE 0 // default layer
#define GAME 1 // Game Layer
#define SYMB 2 // symbols
#define NUMB 3 // Numbers and F keys
#define WORK 4 // Work keys
#define SUBL 5 // Sublime Code Shortcuts

#define CUTTIMER 500
#define COPYTIMER 150

#define COPYPASTE M(1)
#define DOUBLE0 M(2)
#define FOLD M(3)
#define UNFOLD M(4)
#define FOLDALL M(5)
#define UNFOLDALL M(6)
#define CLOSEFILE M(7)
#define COPYPATH M(8)
#define REVEAL M(9)
#define WORKINGFILES M(10)
#define MARK M(11)
#define DELETEMARK M(12)
#define SELECTOMARK M(13)
#define MAIL M(14)

// Tap Dance declarations
enum {
  TD_U_COPY = 0,
  TD_H_PASTE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | MEH §  |   1  |   2  |   3  |   4  |   5  | Esc  |           | Numb |   6  |   7  |   8  |   9  |   0  |PrintScr|
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |Tab/CODE|  ü   |   ;  |   .  |   P  |   Y  | Del  |           |WIN 1 |   F  |   G  |   C  |   T  |   Z  |code/Back|
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |Tab/SYMB|A     |   O  |   E  |   I  |   U  |------|           |------|   H  |   D  |   R  |   N  |S     | L/SYMB |
 * |--------+------+------+------+------+------| C & P|           | RUN  |------+------+------+------+------+--------|
 * | ä/Shift |  ö   |   Q  |   J  |   K  |   X  |      |           |      |   B  |   M  |   W  |   V  |-/AltG|  Shift|
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |  Ctrl| Alt  | LGui |~SYMB|AltShf\|                                       |  Up  | Down | Left | Right|CAPS/Ctrl|
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Enter| LGui |       | GAME |  App |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |  Back|      | PgUp |       | PgDn |        |      |
 *                                 |Space/| Del /|------|       |------|  Enter/|Space/|
 *                                 | NUMB | WORK |Home/MD|      | End |  WORK  | NUMB  |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = KEYMAP(  // layer 0 : default
        // left hand
        MEH(CH_PARA),         LGUI(CH_1),         LGUI(CH_2),   LGUI(CH_3),   LGUI(CH_4),   LGUI(CH_5),   KC_ESC,
        LT(SUBL,KC_TAB),        CH_UE,        CH_COMM,   KC_DOT, CH_P,   CH_Y,   KC_DELT,
        LT(SYMB, KC_TAB),        CH_A,         CH_O,   CH_E,   CH_I,   TD(TD_U_COPY),
        SFT_T(CH_AE),CH_OE,      CH_Q,   CH_J,   CH_K,   CH_X,   COPYPASTE,
        KC_LCTL,                KC_LALT,        KC_LGUI, KC_FN4, OSM(MOD_RALT | MOD_LSFT),
                                              KC_ENT,  KC_LGUI,
                                                              KC_PGUP,
                                               LT(NUMB,KC_BSPC),LT(WORK,KC_DELT),MEH_T(KC_HOME),
        // right hand
             TG(NUMB),     LGUI(CH_6),   LGUI(CH_7),   LGUI(CH_8),   LGUI(CH_9),   CH_0,             KC_PSCR,
             LGUI(CH_1),    CH_F,   CH_G,   CH_C,   CH_T,   CH_Z,             LT(SUBL,KC_BSPC),
                          TD(TD_H_PASTE),   CH_D,   CH_R,   CH_N,   CH_S,             LT(SYMB,CH_L),
             LGUI(CH_R),     CH_B,   CH_M,   CH_W,   CH_V,   KC_FN3,   KC_LSFT,
                                  KC_UP,  KC_DOWN,KC_LEFT,KC_RGHT,          KC_FN5,
             TG(GAME),        ALT_T(KC_APP),
             KC_PGDN,
             KC_END,LT(NUMB,KC_ENT), LT(WORK,KC_SPC)
 ),
/* Keymap 1: GAME layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   §    |   1  |   2  |   3  |   4  |   5  | Esc  |           |  Numb|   6  |   7  |   8  |   9  |   0  |PrintScr|
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |Tab/CODE|   Q  |   W  |   E  |   R  |   T  | Del  |           |~SYMB |   Z  |   U  |   I  |   O  |   P  | Ü /CODE|
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |CtrlShif|   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   Ö  | Ä/SYMB |
 * |--------+------+------+------+------+------| C & P|           |~LMDIA|------+------+------+------+------+--------|
 * | LShift |   Y  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |-/AltG|  Shift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |  Ctrl|  Alt |  Gui | Left | Right|                                       |  Up  | Down |  \   | ~WIND| CAPS |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | App  | LGui |       |      |Ctrl/Esc|
 *                                 ,------+------+------|       |------+--------+------.
 *                                 |      |Backsp| Home |       | PgUp |        |      |
 *                                 | Space| ace /|------|       |------|  Del   |Enter/|
 *                                 |      |      |  End |       | PgDn |        |       |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[GAME] = KEYMAP(  // layer 1 : default
        // left hand
        CH_PARA,         CH_1,           CH_2,     CH_3,     CH_4,     CH_5,   KC_ESC,
        LT(SUBL,KC_TAB),         CH_Q,           CH_W,     CH_E,     CH_R,     CH_T,   KC_DELT,
        LT(SYMB,KC_TAB),         CH_A,           CH_S,     CH_D,     CH_F,     CH_G,
        KC_LSFT,         CH_Y,           CH_X,     CH_C,     CH_V,     CH_B,   COPYPASTE,
         KC_LCTL,                KC_LALT,        KC_LGUI,  KC_LEFT,  KC_RGHT,
                                               ALT_T(KC_APP), KC_LGUI,
                                                              KC_HOME,
                                               KC_SPC,KC_BSPC,KC_END,
        // right hand
        TG(NUMB),     CH_6,   CH_7,    CH_8,    CH_9,   CH_0,             KC_PSCR,
        KC_FN1,       CH_Z,   CH_U,    CH_I,    CH_O,   CH_P,             LT(SUBL,CH_UE),
                     CH_H,   CH_J,    CH_K,    CH_L,   CH_OE,            LT(SYMB,CH_AE),
        KC_FN2,CH_N,   CH_M,    CH_COMM, CH_DOT, KC_FN3,   KC_RSFT,
                             KC_UP, KC_DOWN, CH_BSLS, KC_FN4,          KC_CAPS,
        _______,CTL_T(KC_ESC),
        KC_PGUP,
        KC_PGDN,KC_DELT, KC_ENT
),
/* Keymap 1: Symbol Layer
 * 
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   !  |   @  |   {  |   }  |   |  |      |           |      |   ç |   "  |   '  |   &   |  *   |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   #  |   $  |   (  |   )  |   `  |------|           |------|  ´   |   \  |   /  |   ?  |   +  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   §  |   <  |   >  |  =   |   =  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[SYMB] = KEYMAP(
       // left hand
       _______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  _______,
       _______,CH_EXLM,CH_AT,  CH_LCBR,CH_RCBR,CH_PIPE,_______,
       _______,CH_HASH,CH_DLR, CH_LPRN,CH_RPRN,CH_GRV,
       _______,CH_PERC,CH_CARR,CH_LBRC,CH_RBRC,CH_TILD,_______,
       _______,_______,_______,_______,_______,
                                       _______,_______,
                                               _______,
                               _______,_______,_______,
       // right hand
       _______, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
       _______, CH_CELA,   CH_DQOT,   CH_QUOT,    CH_AMPR,    CH_PAST, KC_F12,
                CH_ACUT, CH_BSLS,   CH_SLSH,    CH_QST,    KC_PPLS, _______,
       _______, CH_PARA, CH_LESS,   CH_MORE,    CH_EQL,    CH_EQL, _______,
                         _______,_______,  _______,    _______,  _______,
       _______, _______,
       _______,
       _______, _______, _______
),
/* Keymap 2: Number Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  | F10  |  F11   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   F4 |  F3  |   F2  |  F1 |   0  |      |           |      |  "   |   7  |   8  |   9  |  *   |  F12   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   F8 |   F7 |   F6 |   F5 |   5  |------|           |------|      |   4  |   5  |   6  |   +  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Shift  |  F12 | F11  |  F10 |  F9  |   1  |      |           |      |   &  |   1  |   2  |   3  |   /  |NumLock |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |   0  |  00  |   .  |   =  |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[NUMB] = KEYMAP(
       // left hand
        _______,     KC_F1,     KC_F2,      KC_F3,      KC_F4,      KC_F5,      _______,     
        _______,     KC_F4,      KC_F3,    KC_F2,    KC_F1,    CH_0,    _______,     
        _______,     KC_F8,   KC_F7,     KC_F6,    KC_F5,    CH_5,     
        KC_LSFT,     KC_F12,   KC_F11,    KC_F10,    KC_F9,    CH_1,    _______,     
        _______,     _______,   _______,    _______,    _______,     
                                                                    _______,    _______,    
                                                                                _______,     
                                                        _______,    _______,    _______,
        // right hand
        _______,    KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,  
        _______,    LSFT(CH_2), CH_7,       CH_8,       CH_9,       KC_PAST,    KC_F12,    
                    KC_DOWN,    CH_4,       CH_5,       CH_6,       KC_PPLS,    _______,    
        _______,    CH_AMPR,    CH_1,       CH_2,       CH_3,       KC_PSLS,    KC_NLCK,   
                    CH_0,       DOUBLE0,    KC_DOT,     CH_EQL,     _______,  
        _______,    _______,   
        _______,   
        _______,    _______,    _______
),
/* Keymap 3: Working
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |       |      |      |     |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        | Lock | MAIL |      |WinCls|      |      |           |      |      |  END |  Up  |  HOME|      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |WinExp|AdrBar| LGui |------|           |------|TaskVw| Left | Down | Right|      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | CrlShf |      |      |PrvTab|NexTab|      |      |           |      |NexWin| Undo | Redo |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |     |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[WORK] = KEYMAP(
       _______, _______, _______, _______, _______, _______, _______,
       _______, LGUI(CH_L), MAIL, XXXXXXX, LALT(KC_F4), XXXXXXX, _______,
       _______, XXXXXXX, XXXXXXX, KC_MYCM, LCTL(CH_L), KC_LGUI,
       OSM(MOD_LCTL | MOD_LSFT), XXXXXXX, XXXXXXX, LCTL(LSFT(KC_TAB)), LCTL(KC_TAB), XXXXXXX, _______,
       _______, _______, _______, _______, _______,
                                           _______, _______,
                                                    _______,
                                  _______, _______, _______,
    // right hand
       _______,  _______,  _______, _______, _______, _______, _______,
       _______,  MEH(CH_R), KC_HOME, KC_UP, KC_END, XXXXXXX, XXXXXXX,
                 LGUI(KC_TAB), KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX, _______,
       _______,  LALT(KC_TAB), LCTL(CH_Z), LCTL(CH_Y), XXXXXXX, XXXXXXX, _______,
                          _______, _______, _______, _______, _______,
       _______, _______,
       _______,
       _______, _______, _______
),
/* Keymap 4: SublimeText
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |      |      |  F5  |      |           |      |  F10 |  F11 |StepOt|TooBP |  F11 |   F12  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |UnfolA|FoldA |UnfolS|FoldS |CloseF|      |           |      |Coment|F_Prev| Find |F_Next|      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |SeltoM|DelMark| Mark |JFunc|------|           |------| LProj|G_Symb|G_File|LWorkF|G_Line|PeekDef |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |Reveal|CopyPh|DeLine|      |           |Format|S_Srnk|S_Expd| MCase| MWord|MRegex|        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |G_Back|G_Fowd|                                       |LineUp|LineDw|      |      | Ctrl |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 * JFun = Jump function
 * 
 */
// Sublimetext
[SUBL] = KEYMAP(
       _______,             LCTL(LSFT(CH_P)),    KC_F2,               _______,       _______,       KC_F5,               _______,
       _______,             LCTL(LSFT(LALT(KC_A))),         LCTL(LSFT(LALT(KC_O))),         LCTL(LSFT(LALT(KC_E))),   LCTL(LSFT(LALT(KC_I))),   CLOSEFILE,           _______,
       _______,             _______,             SELECTOMARK,         DELETEMARK,    MARK,          LCTL(CH_M),
       _______,             _______,             _______,             REVEAL,        COPYPATH,      LCTL(LSFT(CH_K)),    _______,
       _______,             _______,             _______,             LALT(KC_LEFT), LALT(KC_RIGHT),
                                                                      _______,       _______,
                                                                                     _______,
                                                 _______,             _______,       _______,
    // right hand
       _______,             KC_F10,              KC_F11,              LSFT(KC_F11),  KC_F9,         KC_F11,          KC_F12,
       _______,             LCTL(CH_PARA),       LSFT(KC_F3),         LCTL(CH_F),    KC_F3,         _______,         _______,
                            LCTL(LALT(CH_P)),    LCTL(CH_R),          LCTL(KC_P),    WORKINGFILES,  LCTL(KC_G),      LALT(KC_F12),
       LSFT(LALT(CH_F)),    LSFT(LALT(KC_LEFT)), LSFT(LALT(KC_RIGHT)),LALT(CH_C),    LALT(CH_W),    LALT(CH_R),      _______,
                            LCTL(LSFT(KC_UP)),   LCTL(LSFT(KC_DOWN)), _______,       _______,         KC_LCTL,
       _______,             _______,
       _______,
       _______,             _______,             _______
),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB),                // FN1 - Momentary Layer 2 (Symbols)
    [2] = ACTION_LAYER_TAP_TOGGLE(NUMB),                // FN2 - Momentary Layer 3 (Multimedia)
    [3] = ACTION_MODS_TAP_KEY(MOD_RALT, CH_MINS),       // FN3 - AltGr or -
    [4] = ACTION_LAYER_TAP_TOGGLE(SYMB),                 // FN4 - Momentary Layer 4 (Windows)
    [5] = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_CAPS)        // FN5 - Control or CAPS
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_U_COPY] = ACTION_TAP_DANCE_DOUBLE(CH_U, LCTL(CH_C)),
  [TD_H_PASTE] = ACTION_TAP_DANCE_DOUBLE(CH_H, LCTL(CH_V))
};

// void dance_copy (qk_tap_dance_state_t *state, void *user_data) {
//   register_code(KC_LCTL);
//   register_code(CH_C);
//   unregister_code(CH_C);
//   unregister_code(KC_LCTL);
// }

// void dance_paste (qk_tap_dance_state_t *state, void *user_data) {
//   register_code(KC_LCTL);
//   register_code(CH_V);
//   unregister_code(CH_V);
//   unregister_code(KC_LCTL);
// }

static uint16_t key_timer;

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
          } else {
            unregister_code(KC_RSFT);
          }
          break;
        case 1: {
          // Copy for 150 ms press
          // Cut for long press
          // Paste for tap
          if (record->event.pressed) {
            key_timer = timer_read(); // if the key is being pressed, we start the timer.
          }
          else { // this means the key was just released, so we can figure out how long it was pressed for (tap or "held down").
            if (timer_elapsed(key_timer) > CUTTIMER) { // the longest press ist a Cut
              key_timer = 0;
                return MACRO( D(LCTL), T(X), U(LCTL), END  );
            }
            else if (timer_elapsed(key_timer) > COPYTIMER) { // more than 150ms count as a short "held down", we Copy.
              key_timer = 0;
                return MACRO( D(LCTL), T(C), U(LCTL), END  );
            }
            else { // less than 150ms count as a tap and we do a paste.
              key_timer = 0;
                return MACRO( D(LCTL), T(V), U(LCTL), END  );
            }
          }
          break;
        }
        case 2: { // add 00
          if (record->event.pressed) {
            return MACRO( I(25), T(P0), T(P0), END );
          }
          break;
        }
        case 3: { // FOLD
          if (record->event.pressed){
            register_code(KC_LCTL);
            register_code(KC_K);
            unregister_code(KC_K);
            register_code(KC_QUOT);
            unregister_code(KC_QUOT);
            unregister_code(KC_LCTL);
            // return MACRO( D(LCTL), T(K), T(CH_QUOT), U(LCTL), END);
          }
          break;
        }
        case 4: { // UNFOLD
          if (record->event.pressed){
            register_code(KC_LCTL);
            register_code(KC_K);
            unregister_code(KC_K);
            register_code(KC_EQL);
            unregister_code(KC_EQL);
            unregister_code(KC_LCTL);
            // return MACRO( D(LCTL), T(K), T(CH_CARR), U(LCTL), END);
          }
          break;
        }
        case 5: { // FOLDALL
          if (record->event.pressed){
            return MACRO( D(LCTL), T(K), T(0), U(LCTL), END);
          }
          break;
        }
        case 6: { // UNFOLDALL
          if (record->event.pressed){
            return MACRO( D(LCTL), T(K), T(J), U(LCTL), END);
          }
          break;
        }
        case 7: { // CLOSEFILE
          if (record->event.pressed){
            return MACRO( D(LCTL), T(K), U(LCTL), T(W), END);
          }
          break;
        }
        case 8: { // Copy Path of Active File
          if (record->event.pressed){
            return MACRO( D(LCTL), T(K), U(LCTL), T(P), END);
          }
          break;
        }
        case 9: { // Reveal Active File in Windows
          if (record->event.pressed){
            return MACRO( D(LCTL), T(K), U(LCTL), T(R), END);
          }
          break;
        }
        case 10: { // List Working Files
          if (record->event.pressed){
            return MACRO( D(LCTL), T(K), T(P), U(LCTL), END);
          }
          break;
        }
        case 11: { // Set Mark
          if (record->event.pressed){
            return MACRO( D(LCTL), T(K), T(SPC), U(LCTL), END);
          }
          break;
        }
        case 12: { // Remove Mark
          if (record->event.pressed){
            return MACRO( D(LCTL), T(K), T(G), U(LCTL), END);
          }
          break;
        }
        case 13: { // Mark til mark
          if (record->event.pressed){
            return MACRO( D(LCTL), T(K), T(A), U(LCTL), END);
          }
          break;
        }
        case 14: {
          if (record->event.pressed)          {
            // SEND_STRING("joan.lustenberger");
            return MACRO(T(J),T(O),T(A),T(N),T(DOT),T(L),T(U),T(S),T(T),T(E),T(N),T(B),T(E),T(R),T(G),T(E),T(R),D(RALT),T(2),U(RALT),T(S),T(U),T(V),T(A),T(DOT),T(C),T(H),T(TAB),END);
          }
          break;
        }
      }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    ergodox_led_all_set (LED_BRIGHTNESS_LO);
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

  uint8_t layer = biton32(layer_state);

  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  // if we push the copy/paste we ignore the Layer Leds
  if (key_timer != 0)
  {
    if (timer_elapsed(key_timer) > COPYTIMER) {
      ergodox_right_led_2_on();
    }
    if (timer_elapsed(key_timer) > CUTTIMER) { // 800 ms, we do a Cut
      ergodox_right_led_3_on();
    }
  }
  else {
    switch (layer) {
      case NUMB:
        ergodox_right_led_1_on();
        break;
      case SYMB:
        ergodox_right_led_2_on();
        break;
      case WORK:
        ergodox_right_led_3_on();
        break;
      case GAME:
        ergodox_led_all_set (LED_BRIGHTNESS_LO);
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        break;
      case SUBL:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        break;
      default:
        // none
        break;
    }
  }
};
