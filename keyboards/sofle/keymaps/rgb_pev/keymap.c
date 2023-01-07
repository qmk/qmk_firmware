
 /* Copyright 2021 Dane Evans
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 2 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See thDan
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */
  // SOFLE RGB
#include <stdio.h>
#include <string.h>
//#include <stdlib.h>

//#define PRINT_DB

#ifdef PRINT_DB
#   include <print.h>
#endif
#include "transactions.h"

#include QMK_KEYBOARD_H

#define INDICATOR_BRIGHTNESS 20

#define HSV_OVERRIDE_HELP(h, s, v, Override) h, s , Override
#define HSV_OVERRIDE(hsv, Override) HSV_OVERRIDE_HELP(hsv,Override)

// Light combinations
#define SET_INDICATORS(hsv) \
	{0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
    {LEDS_HF+0, 1, hsv}
#define SET_UNDERGLOW(hsv) \
	{1, 6, hsv}, \
    {LEDS_HF+1, 6,hsv}
#define SET_NUMPAD(hsv)     \
	{LEDS_HF+15, 5, hsv},\
	  {LEDS_HF+22, 3, hsv},\
	  {LEDS_HF+27, 3, hsv}
#define SET_NUMROW(hsv) \
	{10, 2, hsv}, \
		{20, 2, hsv}, \
		{30, 2, hsv}, \
	  {LEDS_HF+ 10, 2, hsv}, \
	  {LEDS_HF+ 20, 2, hsv}, \
	  {LEDS_HF+ 30, 2, hsv}
#define SET_INNER_COL(hsv)	\
	{33, 4, hsv}, \
	  {LEDS_HF+ 33, 4, hsv}

#define SET_OUTER_COL(hsv) \
	{7, 4, hsv}, \
	  {LEDS_HF+ 7, 4, hsv}
#define SET_COL_0(hsv) \
	  {8, 4, hsv}, \
	  {8+LEDS_HF, 4, hsv}
#define SET_COL_1(hsv) \
	  {12, 4, hsv}, \
	  {12+LEDS_HF, 4, hsv}
#define SET_COL_2(hsv) \
	  {18, 4, hsv}, \
	  {18+LEDS_HF, 4, hsv}
#define SET_COL_3(hsv) \
	  {22, 4, hsv}, \
	  {22+LEDS_HF, 4, hsv}
#define SET_COL_4(hsv) \
	  {28, 4, hsv}, \
	  {28+LEDS_HF, 4, hsv}
#define SET_COL_5(hsv) \
	  {32, 4, hsv}, \
	  {32+LEDS_HF, 4, hsv}
#define SET_THUMB_CLUSTER(hsv) 	\
	{25, 2, hsv}, \
	  {LEDS_HF+ 25, 2, hsv}
#define SET_UNDERGLOW_INDICAT(hsv) 	\
	{0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
    {LEDS_HF+0, 1, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
		{1, 6, hsv}, \
    {LEDS_HF+1, 6, hsv}

//		{7, 4, hsv}, 
//	  {LEDS_HF+ 7, 4, hsv}, 
//		{25, 2, hsv}, 
//	  {LEDS_HF+ 25, 2, hsv}

// https://www.reddit.com/r/olkb/comments/5rk64g/press_both_shift_keys_for_capslock_in_qmk/
//bool process_record_user(uint16_t keycode, keyrecord_t *record)
//{ 
//    // Detect the activation of both Shifts 
//    if ((get_mods() & MOD_MASK_SHIFT) == MOD_MASK_SHIFT) 
//    { 
//        // Toggle Caps_lock value 
//        tap_code(KC_CAPS); 
//    }
//
//    // Keep processing like normal, don't do anything to prevent that
//    return true;
//};


enum sofle_layers {
    _QWERTY = 0,

    _ALT,
    _NUM,
    _FN,
    _KB,
    _LCK
};



#ifdef BSPC_BACKSLASH_SWAP
#  define KC_BSPC_ KC_BACKSLASH
#  define KC_BACKSLASH_ KC_BSPC
#else
#  define KC_BSPC_ KC_BSPC
#  define KC_BACKSLASH_ KC_BACKSLASH
#endif

#ifdef ALT_WIN_SWAP
#  define LALT_T_ LWIN_T
#  define LWIN_T_ LALT_T
#else
#  define LALT_T_ LALT_T
#  define LWIN_T_ LWIN_T
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC~ |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | BKSP |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |TAB |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |   \  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------| MUTE  |    |PLAY   |------+------+------+------+------+------|
 * |Shift |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  | Shift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LWIN | LALT |LCTRL | SPACE| /       /       \ ENTR \  |      |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
  [_QWERTY] = LAYOUT(
         //,------------------------------------------------.                         ,---------------------------------------------------.
  QK_GESC,          KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_BSPC_,
         //|------+-------+--------+--------+--------+------|                        |--------+-------+--------+--------+--------+---------|
LT(_FN,KC_TAB),KC_Q,    KC_W,    KC_E,     KC_R,    KC_T,                         KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    LT(_FN, KC_BACKSLASH_),
         //|------+-------+--------+--------+--------+------|                         |--------+-------+--------+--------+--------+---------|
LT(_ALT, KC_ESC),  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN, LT(_NUM, KC_QUOT), //LALT_T_(KC_QUOT),
         //|------+-------+--------+--------+--------+------|  ===  |                 |  ===  |--------+-------+--------+--------+--------+---------|
  KC_LSFT,       KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,  KC_MUTE,       KC_MPLY ,KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_UNDS),
         //|------+-------+--------+--------+--------+------|  ===  |             |  ===  |--------+-------+--------+--------+--------+---------|
  KC_LWIN, KC_LALT, KC_LCTL, KC_SPC, LT(_NUM,KC_ENT),                    KC_ENT, LT(_ALT, KC_SPC), RCTL_T(KC_BSPC_), RALT_T(KC_DEL), RWIN_T(KC_GRV)
  //                     \--------+--------+--------+---------+-------|      |--------+---------+--------+---------+-------/
),
[_ALT] = LAYOUT(
  //-------------------------------------------------.                          ----------------------------------------------------.
  TG(_ALT),   KC_NO,  KC_NO, KC_UP, KC_INS,  KC_NO,                             KC_NO,   KC_NO,     KC_NO,    KC_NO,  KC_NO,  KC_DEL,
  //|------+-------+--------+--------+--------+------|                         |--------+-------+--------+--------+--------+---------|
  KC_TAB,  KC_PGUP,   KC_UP, KC_PGDN,  KC_DEL, KC_TILD,                            KC_HOME, KC_PGDN, KC_PGUP, KC_END ,  KC_UNDS,  KC_PLUS ,
  //|------+-------+--------+--------+--------+------|                         |--------+-------+--------+--------+--------+---------|
 KC_GRV,  KC_LEFT, KC_DOWN, KC_RIGHT, KC_BSPC_, KC_GRV,                            KC_LEFT, KC_DOWN,   KC_UP,  KC_RGHT, KC_MINUS, KC_EQL,
  //|------+-------+--------+--------+--------+------        |  ===  |  |  ===  |--------+-------+--------+--------+--------+---------|
 KC_LSFT,   KC_HOME, KC_RALT,  KC_END,  KC_NO, MO(_LCK),   KC_TRNS,      RGB_TOG,  KC_LBRC, KC_RBRC, KC_LCBR,  KC_RCBR,  KC_SLSH  , KC_TRNS,
  //|------+-------+--------+--------+--------+------|  ===  |              |  ===  |--------+-------+--------+--------+--------+---------|
                   KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS
  //            \--------+--------+--------+---------+-------|             |--------+---------+--------+---------+-------/
),
[_NUM] = LAYOUT(
  //,------------------------------------------------.                    ,---------------------------------------------------.
  TG(_NUM),  KC_SLASH,  KC_ASTR, KC_MINUS,   KC_PLUS, KC_BSPC_,                      KC_NO,    KC_NO,   KC_NO,    KC_NO,    KC_NO,  KC_BSPC_,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  KC_TAB, KC_EXLM, KC_AT, KC_HASH, KC_DLR , KC_PERC,                  KC_CIRC,  KC_AMPR,   KC_ASTR,    KC_LPRN, KC_RPRN,  KC_PLUS,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  KC_DOT,  KC_1 ,    KC_2 ,    KC_3,    KC_4,   KC_5,                         KC_6  ,   KC_7 ,   KC_8 , KC_9 ,   KC_0,  KC_EQL,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
  KC_COMM,  KC_6,    KC_7,     KC_8,    KC_9 , KC_0 ,  KC_TRNS,    KC_TRNS,  KC_NO,    KC_NO,   KC_COMM, KC_DOT, KC_SLSH, KC_TRNS,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                   KC_TRNS,  KC_TRNS,    KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS
  //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
),
[_FN] = LAYOUT(
  //,------------------------------------------------.                    ,---------------------------------------------------.
  MO(_LCK),  KC_F1,  KC_F2,   KC_F3,     KC_F4,   KC_F5,                      KC_F6,    KC_F7,   KC_F8,    KC_F9,   KC_F10,  KC_F11,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  MO(_LCK),  KC_F11,   KC_F12,    KC_F13,  KC_F14, KC_F15,                   KC_F16,    KC_F17,   KC_F18,  KC_F11,  KC_F12,  MO(_LCK) ,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  KC_CAPS,  KC_NO,  KC_NO,   KC_NO,  KC_SCRL,   KC_NUM,               KC_NO,  KC_NO,   KC_NO,    KC_NO,   KC_NO ,  KC_NO ,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
  KC_TRNS,  KC_PSCR, KC_SCRL,  KC_PAUSE,  KC_NO, MO(_LCK),  RGB_TOG,  KC_TRNS, KC_NO,  KC_NO,   KC_NO,   KC_NO,    KC_NO,  KC_TRNS  ,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(_KB),  MO(_KB),    KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS
  //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
),
[_KB] = LAYOUT(
  //,------------------------------------------------.                    ,---------------------------------------------------.
  TG(_KB), RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN,                    RGB_M_K, RGB_M_X,  RGB_M_G, RGB_M_T,  RGB_TOG,  RGB_TOG,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  KC_NO,  KC_NO,  KC_NO,    KC_NO,   KC_NO, KC_NO,                        KC_NO ,   KC_NO,   KC_NO,    KC_NO,    KC_NO,  KC_NO ,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  KC_NO,  KC_NO,   KC_NO,   KC_NO,  RGB_HUI, RGB_SAI,                     KC_NO,  KC_NO,   KC_NO,    KC_NO,    KC_NO,  KC_NO,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
 KC_TRNS, RGB_MOD,  KC_NO,  KC_NO,  RGB_HUD, RGB_SAD,  RGB_M_G,  RGB_M_SW, KC_NO,    KC_NO,   KC_NO,   KC_NO,    KC_NO,  KC_TRNS  ,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                   KC_TRNS,    KC_TRNS,    KC_TRNS,    SH_TG,      SH_TG,  KC_TRNS,    KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS
  //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
),
[_LCK] = LAYOUT(
  //,------------------------------------------------.                    ,---------------------------------------------------.
  TG(_LCK),  KC_NO,  KC_NO,    KC_NO,   KC_NO, KC_NO,                        KC_NO ,   KC_NO,   KC_NO,    KC_NO,    KC_NO,  KC_NO ,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  TG(_FN),  KC_NO,  KC_NO,    KC_NO,   KC_NO, KC_NO,                        KC_NO ,   KC_NO,   KC_NO,    KC_NO,    KC_NO,  TG(_FN) ,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  TG(_ALT),  KC_NO,  KC_NO,   KC_NO,   KC_NO, KC_NO,                     KC_NO,  KC_NO,   KC_NO,    KC_NO,    KC_NO,  TG(_NUM),
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
  KC_CAPS, KC_NO,  KC_NO,  KC_NO,  KC_NO, KC_NO,  TG(_KB),  KC_TRNS, KC_NO,    KC_NO,   KC_NO,   KC_NO,    KC_NO,  KC_CAPS  ,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                 TG(_KB), KC_TRNS, KC_TRNS, KC_TRNS,TG(_NUM),     KC_TRNS, TG(_ALT),    KC_TRNS,  KC_TRNS,   KC_TRNS
  //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
),
};

#ifdef RGBLIGHT_ENABLE

// Now define the array of layers. Later layers take precedence

// QWERTY,
// Light on inner column and underglow
const uint8_t PROGMEM RGBLED_RAINBOW_SWIRL_INTERVALS[] = {255, 255, 255};

const rgblight_segment_t PROGMEM layer_qwerty_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_UNDERGLOW_INDICAT(HSV_BLUE)

);
const rgblight_segment_t PROGMEM layer_colemakdh_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_UNDERGLOW_INDICAT(HSV_PINK)
);

const rgblight_segment_t PROGMEM layer_alt_lights[] = RGBLIGHT_LAYER_SEGMENTS(
	SET_UNDERGLOW_INDICAT(HSV_TEAL)
    );

const rgblight_segment_t PROGMEM layer_fn_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_UNDERGLOW_INDICAT(HSV_PURPLE)
);

const rgblight_segment_t PROGMEM layer_lck_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_UNDERGLOW_INDICAT(HSV_RED)
);
const rgblight_segment_t PROGMEM layer_kb_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_UNDERGLOW_INDICAT(HSV_YELLOW)
);

const rgblight_segment_t PROGMEM indi_caps_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_COL_0(HSV_WHITE)
);
const rgblight_segment_t PROGMEM indi_compose_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_COL_1(HSV_WHITE)
);
const rgblight_segment_t PROGMEM indi_kana_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_COL_2(HSV_WHITE)
);
const rgblight_segment_t PROGMEM indi_scroll_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_COL_4(HSV_WHITE)
);
const rgblight_segment_t PROGMEM indi_num_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_COL_5(HSV_WHITE)
);

//_NUMPAD
const rgblight_segment_t PROGMEM layer_numpad_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_UNDERGLOW_INDICAT(HSV_GREEN)
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    
    layer_qwerty_lights,
	layer_alt_lights,
	layer_numpad_lights,
    layer_fn_lights,
    layer_kb_lights,
    layer_lck_lights,
    indi_caps_lights,
    indi_compose_lights,
    indi_scroll_lights,
    indi_num_lights,
    indi_kana_lights
);


layer_state_t layer_state_set_user(layer_state_t state) {

	rgblight_set_layer_state(0, layer_state_cmp(state, _QWERTY));

	rgblight_set_layer_state(1, layer_state_cmp(state, _ALT));
	rgblight_set_layer_state(2, layer_state_cmp(state, _NUM));
	rgblight_set_layer_state(3, layer_state_cmp(state, _FN));
	rgblight_set_layer_state(4, layer_state_cmp(state, _KB));
	rgblight_set_layer_state(5, layer_state_cmp(state, _LCK));
    return state;
}

//led_t g_led_state;

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(6, led_state.caps_lock);
    rgblight_set_layer_state(7, led_state.compose);
    rgblight_set_layer_state(8, led_state.scroll_lock);
    rgblight_set_layer_state(9, led_state.num_lock);
    rgblight_set_layer_state(10, led_state.kana);
    return true;
}

#endif

#ifdef OLED_ENABLE

uint16_t keyCntr = 0;
#define OLED_SUGAR_HEIGHT 128

#define OLED_SUGAR_WIDTH  32

bool pixelInvert = false;
void setPixel(char * pixels, uint8_t h, uint8_t w, bool pix) {
//    oled_write_pixel(w, h, pix);
    uint16_t byteIdx = w + (h/8)*OLED_SUGAR_WIDTH;
    int8_t byteMask = 1<<(h%8);
    if(pixelInvert) pix = !pix;
    if(pix) {
        pixels[byteIdx] |= byteMask;
    } else {
        pixels[byteIdx] &= ~byteMask;
    }
}

bool getPixel(char * pixels, uint8_t h, uint8_t w) {
    uint16_t byteIdx = w + (h/8)*OLED_SUGAR_WIDTH;
    int8_t byteMask = 1<<(h%8);
    bool pix =  (pixels[byteIdx] & byteMask) != 0;
    if(pixelInvert) pix = !pix;
    return pix;
}

uint32_t rand_basic(void) {
    static uint32_t seed = 0;
    seed = 1664525*seed + 1013904223;
    return seed;
}

#define OLED_SUGAR_WITH_DOWN 1

#define OLED_SUGAR_PIXELS (OLED_SUGAR_HEIGHT*OLED_SUGAR_WIDTH)
#define OLED_SUGAR_BYTES (OLED_SUGAR_PIXELS/8)
typedef signed char lineIdx_t;
lineIdx_t* activeSugar = NULL;

char* pixels = NULL;


void oled_sugar(void) {
    //return;

    if (activeSugar == NULL) {
        activeSugar = malloc(OLED_SUGAR_HEIGHT);
        if (activeSugar != NULL) {
            memset( activeSugar, -1, OLED_SUGAR_HEIGHT );
        } else {
#ifdef PRINT_DB
            uprintf("activeSugar %X failed to inialise\n", activeSugar);
#endif
            return;
        }
    }

    if (pixels == NULL) {
        pixels = malloc(OLED_SUGAR_BYTES);
        if (pixels != NULL) {
            memset( pixels, 0, OLED_SUGAR_BYTES );
        } else {
#ifdef PRINT_DB
            uprintf("pixels %X failed to inialise\n", pixels);
#endif
            return;
        }

    }

    static uint8_t sugarCntr = 0;

   for(int16_t h = OLED_SUGAR_HEIGHT-2; h >= 0; h--) {
        lineIdx_t w = activeSugar[h];

        if(w < 0 || w >= OLED_SUGAR_WIDTH) {
            continue;
        }
        lineIdx_t wn = -1;
        bool left;
        bool right;
#ifdef OLED_SUGAR_WITH_DOWN 
        uint32_t r = rand_basic();
        const uint32_t thresh1 = UINT32_MAX/3;
        const uint32_t thresh2 = UINT32_MAX-thresh1;
        left  = r < thresh1;
        right = r > thresh2;
#else
        left = ((int32_t) rand_basic())<0;
        right = !left;
#endif
        if ( left ) {
            if( w > 0 ) {
                if(!getPixel(pixels, h+1, w-1)) {
                    wn = w - 1;
                }
            }
        } else if (right) {
            if ( w < OLED_SUGAR_WIDTH-1) {
                if(!getPixel(pixels, h+1, w+1)) {
                    wn = w + 1;
                }
            }
        } else { //centre
            if(!getPixel(pixels, h+1, w)) {
                wn = w ;
            }
        }
        if(wn == -1) {
            if(!getPixel(pixels, h+1, w)) {
                wn = w;
            }
        }
        if(wn != -1) {
            setPixel(pixels, h+1, wn, true);
            activeSugar[h+1] = wn;
            setPixel(pixels, h, w, false);
        }

        activeSugar[h] = -1;
    }
    if(sugarCntr != (keyCntr&0xFF)) {

        sugarCntr++;
        lineIdx_t w = OLED_SUGAR_WIDTH/2;
        bool left = false;
        if( ((int32_t) rand_basic())<0 ) {
            w--;
            left = true;
        }
        bool full = false;
        while(getPixel(pixels,0, w)) {
            if(left) {
                if (w == 0) {
                    w = OLED_SUGAR_WIDTH-1;
                } else if ( w == OLED_SUGAR_WIDTH/2) {
                    full = true;
                    break;
                } else {
                    w--;
                }
            } else {
                if (w == OLED_SUGAR_WIDTH-1) {
                    w = 0;
                } else if ( w == OLED_SUGAR_WIDTH/2-1) {
                    full = true;
                    break;
                } else {
                    w++;
                }
            }
        }

        if(!full) {
//        if(!getPixel(pixels, 0, w)) {
            setPixel(pixels, 0, w, true);
            activeSugar[0] = w;
        } else {
            pixelInvert = !pixelInvert;
            // we where not able to add a pixel (we where full so add one now that we have inverted)
            sugarCntr--;
            oled_sugar();
        }
    }
    rand_basic(); //just here to rotate the seed
    if(!is_oled_on()) {
        //OLED timedout so we will clear everything and start fresh
        memset( pixels, 0, OLED_SUGAR_BYTES );
        memset( activeSugar, -1, OLED_SUGAR_HEIGHT );
        oled_clear();
        pixelInvert = false;
    } else {
        oled_write_raw(pixels, OLED_SUGAR_BYTES);
    }
    
}


oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (true) { //is_keyboard_master()) {
        return OLED_ROTATION_270;
    } 
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        //leftOled();
        oled_sugar();
    } else {
        oled_sugar();
       // render_logo();
    }
    return false;
}

void user_sync_a_update_keyCntr_on_other_board(uint8_t in_buflen, const void* in_data, uint8_t
        out_buflen, void* out_data) { keyCntr = *((const uint16_t *)in_data); }

#endif


void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
#ifdef OLED_ENABLE
    transaction_register_rpc(USER_SYNC_KEY_CNTR, user_sync_a_update_keyCntr_on_other_board);
#endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if(record->event.pressed) {
#ifdef OLED_ENABLE
        keyCntr++;
        transaction_rpc_send(USER_SYNC_KEY_CNTR, sizeof(keyCntr), &keyCntr);
#endif
    }
    return true;
}

#ifdef ENCODER_ENABLE

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_QWERTY] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV , KC_MNXT)   },
    [_NUM]    = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV , KC_MNXT)   },
    [_ALT]    = { ENCODER_CCW_CW(KC_BRID, KC_BRIU), ENCODER_CCW_CW(RGB_VAD , RGB_VAI)  },
    [_FN]     = { ENCODER_CCW_CW(RGB_HUD, RGB_HUI), ENCODER_CCW_CW(RGB_SAD , RGB_SAI)  },
    [_KB]     = { ENCODER_CCW_CW(RGB_SPD, RGB_SPI), ENCODER_CCW_CW(RGB_RMOD, RGB_MOD)  },
    [_LCK]    = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV , KC_MNXT)   },
};
#endif

#endif
