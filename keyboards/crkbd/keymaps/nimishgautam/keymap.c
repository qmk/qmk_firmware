// Copyright 2022 Nimish Gåtam (@nimishgautam)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum custom_key_codes {
    SHOW_WIN_LEFT = SAFE_RANGE, // show windows on tap, move active window left on hold
    NUMERIC_WIN_RIGHT, // lock to numeric layer on press, move active window right on hold
    DEL_WORD, //delete a word
    SELECT_LEFT_WD, // select word left of cursor
    SELECT_RIGHT_WD, // select word right of cursor
    SELECT_LEFT_LINE, // select all from left of cursor to beginning of line
    SELECT_RIGHT_LINE, // select all from right of cursor to end of line
    MOVE_LEFT_WD, // move one word to the left
    MOVE_RIGHT_WD, // move one word to the right
    MOVE_LEFT_LINE, // move to beginning of line
    MOVE_RIGHT_LINE, // move to end of line
    PASTE_NOSTYLE, // paste without formatting
    MOVE_BEGIN_LINE_TERMINAL, // move to the beginning of the line in the terminal
    MOVE_END_LINE_TERMINAL, // move to the end of the line in the terminal
    /* macros */
    PASTE_VIM, // paste in vim from system register
    ACIRCLE, // å 
    ADOT, // ä
    ODOT, // ö
    COMPOSE_MACRO, // compose key for mac or linux
    SCREENSHOT, // This is theoretically reprogrammable on Linux, but Gui(Shift(4)) or Gui(4) is reserved for '4th item on favorite menu' and doesn't remap so well
};

//Tap Dance Declarations
enum {
  TD_MOVE_BEGIN_LINE = 0, // tap-dance, on single press move to beginning of the line, on double, output ^(vim character for beginning of line nonwhitespace char)
  TD_MOVE_END_LINE, // tap-dance, on single press move to end of the line, on double, output $ (vim character for last nonblank char on a line)
  TD_PERIOD_COMMA, // period on single press, comma on second press
};

// Mac-specific definitions of these functions
// I've changed Linux to accept these defaults

#define FINDER          LGUI(LALT(KC_SPACE)) //open the search bar for finding apps, docs in-computer, etc
#define COMPOSE_KEY    KC_SCRL //manually set on linux, to create chars via .Xcompose ()
#define COMPOSE_MAC     KC_F13 //manually set on mac using some tricks
#define X_COMPOSE_KEY    X_SCROLL_LOCK //for use with macros
#define SHOW_WINDOWS    LCTL(KC_UP) //'Expose' on Mac, overview on linux. Just all the windows
#define WINDOW_LEFT LCTL(LGUI(LSFT(KC_LEFT))) //custom shortcut for this feature -- make window take up 50% left screen (using gui and ctl to make it os agnostic)
#define WINDOW_RIGHT LCTL(LGUI(LSFT(KC_RIGHT))) //custom shortcut for this feature -- make window take up 50% right screen (using gui and ctl to make it os agnostic)/fully custom shortcut, using ctl and gui keys so will need them both irrespective of os
#define SHOW_APP_WINDOWS LCTL(KC_DOWN) 
#define LOCK_SCREEN     LCTL(LGUI(KC_Q)) //manually set this on linux to match osx default
#define EURO            LALT(LSFT(KC_2))
#define EMOJI_KBD       LCTL(LGUI(KC_SPACE)) //manually set this on linux to match osx default, with 'emote' on linux and a custom shortcut (probably better to use compose feature)
#define APP_LEFT		LGUI(KC_TAB)
#define APP_RIGHT		RSFT(LGUI(KC_TAB))
#define CALCULATOR      RSFT(LGUI(LCTL(KC_SLASH))) // arbitrary shortcut

#define MOVE_LEFT_TERMINAL LALT(KC_LEFT) //move cursor one word left on the terminal... does not work if .inputrc is set to use vim bindings!
#define MOVE_RIGHT_TERMINAL LALT(KC_RIGHT) //move cursor one word left on the terminal... does not work if .inputrc is set to use vim bindings!
#define DEL_WORD_TERMINAL LALT(KC_BSPC) // delete one word back on terminal ... does not work if .inputrc is set to use vim bindings!

enum custom_layers {
    _BASE,
    _NUMS,
    _NUM_MASK,
    _TEXT_NAV,
    _ADJUST,
    _FN_KEYS,
};

// combo - press space and backspace together to get 'scroll lock', used as the compose key on my custom linux
const uint16_t PROGMEM compose_combo[] = {KC_BSPC, KC_SPACE, COMBO_END};

// combo - press the 2 larger keys on the inner part of the corne to get the search window ('finder' as I'm calling it)
const uint16_t PROGMEM search_combo[] = {LT(_FN_KEYS, KC_ENTER),LT(_TEXT_NAV, KC_PAST), COMBO_END};

// combo - press ,. to paste in vim
const uint16_t PROGMEM vim_paste_combo[] = {KC_COMM, KC_DOT, COMBO_END};

// combo - press () to launch calculator
const uint16_t PROGMEM calculator_combo[] = {LT(_NUMS,KC_LPRN),  LT(_NUMS,KC_RPRN), COMBO_END};

// combo - press combo+ a to get å
const uint16_t PROGMEM acircle_combo[] = { KC_BSPC, KC_SPACE, MT(MOD_LCTL, KC_A),COMBO_END};

// combo - press combo+ l to get ä
const uint16_t PROGMEM adot_combo[] = {KC_BSPC, KC_SPACE, MT(MOD_RALT,KC_L), COMBO_END};

// combo - press combo+ ; to get ö
const uint16_t PROGMEM odot_combo[] = {KC_BSPC, KC_SPACE, MT(MOD_LCTL,KC_SCLN),COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(compose_combo, COMPOSE_MACRO),
    COMBO(search_combo, FINDER),
    COMBO(calculator_combo, CALCULATOR),
    /* macros */
    COMBO(vim_paste_combo, PASTE_VIM),
    COMBO(acircle_combo, ACIRCLE),
    COMBO(adot_combo, ADOT),
    COMBO(odot_combo, ODOT)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_split_3x6_3(  //basic
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                    KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,     KC_MINUS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_ESCAPE, MT(MOD_LCTL, KC_A),    MT(MOD_LALT,KC_S),    MT(MOD_RSFT,KC_D),    MT(MOD_LGUI, KC_F),    KC_G,                    KC_H,    MT(MOD_RGUI,KC_J),    MT(MOD_RSFT,KC_K),    MT(MOD_RALT,KC_L), MT(MOD_LCTL,KC_SCLN), KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      LT(0, SHOW_WIN_LEFT), KC_Z, KC_X,  KC_C, KC_V,  KC_B,   KC_N,                  KC_M,  KC_COMM, KC_DOT,  KC_SLASH,  LT(0, NUMERIC_WIN_RIGHT),
  //|--------+--------+--------+--------+--------+--------+--------|                 |--------+--------+--------+--------+--------+--------+--------|
                                         LT(_NUMS,KC_LPRN),   KC_BSPC,  LT(_FN_KEYS, KC_ENTER),     LT(_TEXT_NAV, KC_PAST),   KC_SPACE, LT(_NUMS,KC_RPRN)
                                      //`--------------------------'                    `--------------------------'

  ),

  [_NUMS] = LAYOUT_split_3x6_3( //numbers
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     SCREENSHOT,   KC_EXCLAIM,KC_AT, KC_HASH, KC_DOLLAR,KC_PERCENT,            KC_CIRCUMFLEX,    KC_7,    KC_8,    KC_9,    KC_TRANSPARENT, KC_PIPE, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      TO(_BASE), KC_LCTL, KC_LALT, KC_RSFT, KC_LGUI,KC_PLUS,                    KC_EQL, KC_4,  KC_5,  KC_6,  KC_BSLS, KC_TRANSPARENT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCBR, KC_LBRC, KC_GRAVE, KC_TILD, PASTE_NOSTYLE, KC_AMPERSAND,      TD(TD_PERIOD_COMMA), KC_1,  KC_2,  KC_3, KC_RBRC, KC_RCBR,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+-C```-------+--------+--------|
                                          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT , KC_TRANSPARENT  ,  KC_UNDS, KC_0
                                      //`--------------------------'  `--------------------------'
  ),

     [_NUM_MASK] = LAYOUT_split_3x6_3( //NUM MASK, so I can still have backspace/enter/tab etc but with the nums, arrows and formatters too
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     KC_TRANSPARENT, KC_TRANSPARENT,KC_TRANSPARENT, KC_UP, KC_TRANSPARENT,KC_TRANSPARENT,      KC_TRANSPARENT, KC_7,    KC_8,    KC_9, KC_TRANSPARENT, KC_TRANSPARENT, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      TO(_BASE), KC_TRANSPARENT, KC_LEFT, KC_DOWN, KC_RIGHT,KC_TRANSPARENT,         KC_TRANSPARENT, KC_4,  KC_5,  KC_6, KC_TRANSPARENT, KC_TRANSPARENT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     KC_TRANSPARENT, KC_TRANSPARENT,KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,      TD(TD_PERIOD_COMMA), KC_1,  KC_2,  KC_3,KC_TRANSPARENT, KC_NUM,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT , KC_TRANSPARENT  ,  KC_TRANSPARENT, KC_0
                                      //`--------------------------'  `--------------------------'
  ),

  [_TEXT_NAV] = LAYOUT_split_3x6_3( //text nav and special navigation (lock screen, adjust layer, etc)
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      LOCK_SCREEN, KC_PSCR, SELECT_LEFT_LINE, KC_UP, SELECT_RIGHT_LINE, TD(TD_MOVE_BEGIN_LINE),                    TD(TD_MOVE_END_LINE), KC_MS_WH_UP, EMOJI_KBD, KC_TRANSPARENT, KC_TRANSPARENT, QK_BOOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      TO(_BASE), SELECT_LEFT_WD, KC_LEFT, KC_DOWN, KC_RIGHT,SELECT_RIGHT_WD,              KC_MS_WH_LEFT, KC_RGUI, KC_RSFT, KC_RALT,KC_RCTL, KC_CAPS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_INSERT, KC_TRANSPARENT, MOVE_LEFT_WD,KC_PAGE_DOWN,MOVE_RIGHT_WD, KC_PAGE_UP,                    KC_MS_WH_RIGHT, KC_MS_WH_DOWN, KC_HOME, KC_END,KC_TRANSPARENT, TO(_ADJUST),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_DELETE,  DEL_WORD, KC_TRANSPARENT , KC_TRANSPARENT  ,  KC_TRANSPARENT, KC_TRANSPARENT
                                      //`--------------------------'  `--------------------------'
  ),

    [_ADJUST] = LAYOUT_split_3x6_3( // adjust things
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      TO(_BASE), RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          CG_TOGG, XXXXXXX, XXXXXXX ,     XXXXXXX, XXXXXXX, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ), // CG_TOGG toggles gui and Ctrl (switching from mac to windows/linux)
    // the RGB buttons go backwards if shift is held when they're pressed, so shift is included
    // RGB MOD changes the mode, it's the most important one
    // right side mostly no-op so I can play with the visualization

   [_FN_KEYS] = LAYOUT_split_3x6_3( //fn keys, terminal text navigation keys
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
     KC_TRANSPARENT, KC_LCBR,KC_LBRC, KC_RBRC, KC_RCBR, MOVE_BEGIN_LINE_TERMINAL,                           MOVE_END_LINE_TERMINAL, KC_F7,    KC_F8,    KC_F9,    KC_F11, KC_TRANSPARENT, 
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      TO(_BASE), KC_LCTL, KC_LALT, KC_RSFT, KC_LGUI, KC_TRANSPARENT,                                               KC_TRANSPARENT, KC_F4,  KC_F5,  KC_F6,  KC_F12, KC_TRANSPARENT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TRANSPARENT, KC_TRANSPARENT, MOVE_LEFT_TERMINAL, DEL_WORD_TERMINAL, MOVE_RIGHT_TERMINAL, KC_TRANSPARENT,                           KC_TRANSPARENT, KC_F1,  KC_F2,  KC_F3, KC_TRANSPARENT, KC_TRANSPARENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT , KC_HASH  ,  KC_TRANSPARENT, KC_F10
                                      //`--------------------------'  `--------------------------'
  )
  
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {


  switch (keycode) {

    // as of this writing, you can't do a layer tap (LT)
    // and also send a shifted code, like left parens
    // If you call such a function, it'll do the layer shift but 
    // it'll ignore the key code on tap... this is the workaround
 
    case LT(_NUMS,KC_LPRN): // Shift to _NUMS layer on hold, but send left paren on press
        if (record->tap.count && record->event.pressed) {
            tap_code16(KC_LPRN); 
            return false; 
        }
    break;
    case LT(_NUMS,KC_RPRN): // Shift to _NUMS on hold, send right parens on press
        if (record->tap.count && record->event.pressed) {
            tap_code16(KC_RPRN); 
            return false; 
        }
    break;

    case LT(0,SHOW_WIN_LEFT):
            if (record->tap.count && record->event.pressed) {
                tap_code16(SHOW_WINDOWS); // Intercept tap function
            } else if (record->event.pressed) {
                tap_code16(WINDOW_LEFT); // Intercept hold function 
            }
        return false;
        break;
    
    case LT(0, NUMERIC_WIN_RIGHT):
            if (record->tap.count && record->event.pressed) {
                layer_on(_NUM_MASK);// Intercept tap function
            } else if (record->event.pressed) {
                tap_code16(WINDOW_RIGHT); // Intercept hold function 
            }
        return false;
        break;
    
    case PASTE_VIM:
        if (record->event.pressed){
            SEND_STRING(SS_TAP(X_ESCAPE)"\"+pi");
        }
        return false;
        break;

    //only read the keymap config if it's one of the below cases (instead of every time)
    case DEL_WORD: 
    case SELECT_LEFT_WD:
    case SELECT_RIGHT_WD:
    case SELECT_LEFT_LINE:
    case SELECT_RIGHT_LINE:
    case MOVE_LEFT_WD:
    case MOVE_RIGHT_WD:
    case MOVE_LEFT_LINE:
    case MOVE_RIGHT_LINE:
    case PASTE_NOSTYLE:
    case MOVE_BEGIN_LINE_TERMINAL:     
    case MOVE_END_LINE_TERMINAL:
    case ACIRCLE:
    case ADOT:
    case ODOT:
    case COMPOSE_MACRO:
    case SCREENSHOT:

        if(record->event.pressed) {
            keymap_config.raw = eeconfig_read_keymap();
            switch (keycode){
                case DEL_WORD:
                    if(keymap_config.swap_lctl_lgui){ //Linux
                        tap_code16(LCTL(KC_BSPC));
                    } else { //osx
                        tap_code16(LALT(KC_BSPC));
                    }
                break;
                case SELECT_LEFT_WD:
                    if(keymap_config.swap_lctl_lgui){ //Linux
                        tap_code16(RSFT(LCTL(KC_LEFT)));
                    } else { //osx
                        tap_code16(RSFT(LALT(KC_LEFT)));
                    }
                break;
                case SELECT_RIGHT_WD:
                    if(keymap_config.swap_lctl_lgui){ //Linux
                        tap_code16(RSFT(LCTL(KC_RIGHT)));
                    } else { //osx
                        tap_code16(RSFT(LALT(KC_RIGHT)));
                    }
                break;
                case SELECT_LEFT_LINE:
                    if(keymap_config.swap_lctl_lgui){ //Linux
                        tap_code16(RSFT(KC_HOME));
                    } else { //osx
                        tap_code16(RSFT(LCTL(KC_LEFT)));
                    }
                break;
                case SELECT_RIGHT_LINE:
                    if(keymap_config.swap_lctl_lgui){ //Linux
                        tap_code16(RSFT(KC_END));
                    } else { //osx
                        tap_code16(RSFT(LCTL(KC_RIGHT)));
                    }
                break;
                case MOVE_LEFT_WD:
                    if(keymap_config.swap_lctl_lgui){ //Linux
                        tap_code16(LCTL(KC_LEFT));
                    } else { //osx
                        tap_code16(LALT(KC_LEFT));
                    }
                break;
                case MOVE_RIGHT_WD:
                    if(keymap_config.swap_lctl_lgui){ //Linux
                        tap_code16(LCTL(KC_RIGHT));
                    } else { //osx
                        tap_code16(LALT(KC_RIGHT));
                    }
                break;
                case MOVE_LEFT_LINE:
                    if(keymap_config.swap_lctl_lgui){ //Linux
                        tap_code16(KC_HOME);
                    } else { //osx
                        tap_code16(LGUI(KC_LEFT)); //GUI for move, shift-ctl for highlight... thanks mac!
                    }
                break;
                case MOVE_RIGHT_LINE:
                    if(keymap_config.swap_lctl_lgui){ //Linux
                        tap_code16(KC_END);
                    } else { //osx
                        tap_code16(LGUI(KC_RIGHT)); //GUI for move, shift-ctl for highlight... thanks mac!
                    }
                break;
                case PASTE_NOSTYLE:
                    if(keymap_config.swap_lctl_lgui){ //Linux
                        tap_code16(LCTL(RSFT(KC_V)));
                    } else { //osx
                        tap_code16(LGUI(LALT(LSFT(KC_V)))); 
                    }
                break;
                case MOVE_BEGIN_LINE_TERMINAL:
                    if(keymap_config.swap_lctl_lgui){ //Linux
                        tap_code16(KC_HOME);
                    } else { //osx
                        tap_code16(LSFT(KC_HOME)); 
                    }
                break;
                case MOVE_END_LINE_TERMINAL:
                    if(keymap_config.swap_lctl_lgui){ //Linux
                        tap_code16(KC_END);
                    } else { //osx
                        tap_code16(LSFT(KC_END)); 
                    }
                break;
                case ACIRCLE: // å
                    if(keymap_config.swap_lctl_lgui){ //Linux
                        SEND_STRING(SS_TAP(X_COMPOSE_KEY)"aa");
                    } else { //osx
                        tap_code16(LALT(KC_A)); 
                    }
                break;
                case ADOT: // ä
                    if(keymap_config.swap_lctl_lgui){ //Linux
                        SEND_STRING(SS_TAP(X_COMPOSE_KEY)"a\"");
                    } else { //osx
                        SEND_STRING(SS_LALT("u")"a");
                    }
                break;
                case ODOT: // ö
                    if(keymap_config.swap_lctl_lgui){ //Linux
                        SEND_STRING(SS_TAP(X_COMPOSE_KEY)"o\"");
                    } else { //osx
                        SEND_STRING(SS_LALT("u")"o");
                    }
                break;
                case COMPOSE_MACRO: 
                    if(keymap_config.swap_lctl_lgui){ //Linux
                        tap_code16(COMPOSE_KEY);
                    } else { //osx
                        tap_code16(COMPOSE_MAC);
                    }
                break;
                case SCREENSHOT: 
                    if(keymap_config.swap_lctl_lgui){ //Linux
                        tap_code16(KC_PSCR);
                    } else { //osx
                        tap_code16(LGUI(LSFT(KC_4)));
                    }
                break;
            }
        }

    return false;
    break;

  }
  return true;
}

void dance_left_finished (tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) { //1 tap, move to line left
    keymap_config.raw = eeconfig_read_keymap();
    if(keymap_config.swap_lctl_lgui){ //Linux
        tap_code16(KC_HOME);
    } else { //osx
    tap_code16(LGUI(KC_LEFT));              
    }
  } else { //2 taps, make a circumflex
    tap_code16(KC_CIRC);
  }
}

void dance_right_finished (tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) { // 1 tap, move line right
       keymap_config.raw = eeconfig_read_keymap();
    if(keymap_config.swap_lctl_lgui){ //Linux
        tap_code16(KC_END);
    } else { //osx
    tap_code16(LGUI(KC_RIGHT));              
    }
  } else { //2 taps, dollar
    tap_code16(KC_DOLLAR);
  }
}

//Tap Dance Definitions
tap_dance_action_t tap_dance_actions[] = {
  [TD_MOVE_BEGIN_LINE]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_left_finished, NULL),
  [TD_MOVE_END_LINE]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_right_finished, NULL),
  [TD_PERIOD_COMMA] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_COMMA),
};

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MT(MOD_RSFT,KC_D): // for modtap shift, otherwise lots of mis-firings
        case MT(MOD_RSFT,KC_K):
            // Immediately select the hold action when another key is tapped.
            return true;
        default:
            // Do not select the hold action when another key is tapped.
            return false;
    }
}

// yeah, should be layer_state_set_user but that one doesn't update the mods
void set_lighting_user(void) {
    uint8_t layer = get_highest_layer(layer_state);
    switch(layer){
        case _BASE:
            rgblight_sethsv_noeeprom(HSV_WHITE);
            led_t led_state = host_keyboard_led_state();
            if(led_state.caps_lock){
                rgblight_sethsv_noeeprom(HSV_RED);
            } 
            //rgblight_sethsv(HSV_OFF);
        break;
        case _NUMS:
            rgblight_sethsv_noeeprom(HSV_GREEN);
        break;
        case _NUM_MASK:
            rgblight_sethsv_noeeprom(HSV_PINK);
        break;
        case _TEXT_NAV:
            rgblight_sethsv_noeeprom(HSV_BLUE);
        break;
        case _ADJUST:
            rgblight_sethsv_noeeprom(HSV_ORANGE);
        break;
        case _FN_KEYS:
            rgblight_sethsv_noeeprom(HSV_PURPLE);
        break;
        default:
        break;
    }
    // override color with mods

    if(get_mods() & MOD_MASK_SHIFT){
        rgblight_sethsv_noeeprom(HSV_RED);
    }
    if(get_mods() & MOD_MASK_CTRL){
        rgblight_sethsv_noeeprom(HSV_MAGENTA);
    }
    if(get_mods() & MOD_MASK_ALT){
        rgblight_sethsv_noeeprom(HSV_YELLOW);
    }
    if(get_mods() & MOD_MASK_GUI){
        rgblight_sethsv_noeeprom(HSV_TEAL);
    }
    // return state;
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return OLED_ROTATION_270;
}

void oled_render_general_state(void){
    set_lighting_user();

    keymap_config.raw = eeconfig_read_keymap();
    if(keymap_config.swap_lctl_lgui){
        oled_write_ln_P(PSTR("Linux"), false);
    }
    else {
        oled_write_ln_P(PSTR("OSX"), false);
    }
    
    //oled_write_ln(get_u8_str(get_current_wpm(), '0'), false);
    /*
    led_t led_state = host_keyboard_led_state();
    if(led_state.caps_lock){
        rgblight_sethsv(HSV_RED);
    }*/
    //Layer color has to be handled by master


    // led state doesn't have to be handled by master, but 
    // the keyboard will freeze if you type too fast
    // and have this handled on the slave side

    led_t led_state = host_keyboard_led_state();
    if(led_state.caps_lock){
        oled_write_ln_P(PSTR("CAPS"), false);
    } else {
        oled_write_ln_P(PSTR(" "), false);
    }
    if(led_state.num_lock){
        oled_write_ln_P(PSTR("NumLk"), false);
    } else {
        oled_write_ln_P(PSTR(" "), false);
    }
    if(led_state.scroll_lock){
        oled_write_ln_P(PSTR("Scrol"), false);
    } else {
        oled_write_ln_P(PSTR(" "), false);
    }
    if(led_state.compose){
        oled_write_ln_P(PSTR("comp"), false);
    } else {
        oled_write_ln_P(PSTR(" "), false);
    }
}

void oled_render_layer_mod_state(void) {
    //Layer
    uint8_t layer = get_highest_layer(layer_state);
    switch (layer) {
        case _BASE:
            oled_write_ln_P(PSTR("Base"), false);
            //rgblight_sethsv(HSV_OFF);
            break;
        case _NUMS:
            oled_write_ln_P(PSTR("Symb"), false);
            break;
        case _NUM_MASK:
            oled_write_ln_P(PSTR("NumX"), false);
            break;
        case _TEXT_NAV:
            oled_write_ln_P(PSTR("Text"), false);
            break;
        case _ADJUST:
            oled_write_ln_P(PSTR("Adj"), false);
            break;
        case _FN_KEYS:
            oled_write_ln_P(PSTR("Fn"), false);
            break;   
        default:
            break;
    }
    oled_write_ln_P(PSTR(" "), false);
    // mods
    if(get_mods() & MOD_MASK_SHIFT){
        oled_write_ln_P(PSTR("SHIFT"), false);
    }
    if(get_mods() & MOD_MASK_CTRL){
        oled_write_ln_P(PSTR("ctrl"), false);
    }
    if(get_mods() & MOD_MASK_ALT){
        oled_write_ln_P(PSTR("alt"), false);
    }
    if(get_mods() & MOD_MASK_GUI){
        oled_write_ln_P(PSTR("GUI"), false);
    }
    if(!get_mods()){
        oled_write_ln_P(PSTR(" "), false);
        oled_write_ln_P(PSTR(" "), false);
        oled_write_ln_P(PSTR(" "), false);
        oled_write_ln_P(PSTR(" "), false);
    }
}


/* https://joric.github.io/qle/  - font */


// render general state on master, a little bit of info on slave side
bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_general_state();
    }  
    else {
        oled_render_layer_mod_state();
    }
    return false;
}

#endif
