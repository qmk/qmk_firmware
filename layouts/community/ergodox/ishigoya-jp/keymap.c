#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "keymap_japanese.h"

static uint16_t start;

#define BASE 0 // EN layer
#define JP 1 // Japanese
#define JPXON 2 // JP + Fn
#define JPKAZARI 3 // JP + KAZARI
#define JPTOPROW 4 // JP + TOPROW
#define JPTRKZ 5 // JP + TOPROW + KAZARI
#define NUM 6 // Numbers

#define CTLSHFT 1
#define CUTCOPY 2

//kana macro definitions start here

#define JPVU 4
#define JPNU 6
#define JPKO 7
#define JPSA 8
#define JPKE 9
#define JPHE 10
#define JPSHI 11
#define JPKA 12
#define JPKI 13
#define JPSU 14
#define JPSO 15
#define JPHI 16
#define JPCHI 17
#define JPFU 18
#define JPSE 19
#define JPTSU 20
#define JPKU 21
#define JPTE 22
#define JPTA 23
#define JPTO 24
#define JPHA 25
#define JPHO 26
#define JPXKE 27
#define JPXU 28
#define JPXKA 29
#define JPXA 30
#define JPXO 31
#define JPGO 32
#define JPZA 33
#define JPGE 34
#define JPBE 35
#define JPYU 36
#define JPJI 37
#define JPGA 38
#define JPGI 39
#define JPZU 40
#define JPZO 41
#define JPBI 42
#define JPDI 43
#define JPZE 44
#define JPDU 45
#define JPGU 46
#define JPYA 47
#define JPYO 48
#define JPDE 49
#define JPDA 50
#define JPDO 51
#define JPBA 52
#define JPBO 53
#define JPRI 54
#define JPRE 55
#define JPRA 56
#define JPNA 57
#define JPNO 58
#define JPMI 59
#define JPMU 60
#define JPME 61
#define JPNE 62
#define JPMA 63
#define JPXTU 64
#define JPWA 65
#define JPRU 66
#define JPWO 67
#define JPNI 68
#define JPNN 69
#define JPMO 70
#define JPRO 71
#define JPXE 72
#define JPXI 73
#define JPXYU 74
#define JPXYA 75
#define JPXYO 76
#define JPPE 77
#define JPPU 78
#define JPPI 79
#define JPPA 80
#define JPPO 81
#define JPBU 82

// kana macro definitions end here

#define SHIFT 86
#define KAZARI 87
#define JPFN 88 //shifts to JPXON layer
#define TOJPLOUT 89
#define TOENL 90
#define TOJPL 91

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * 
 * ,----------------------------------------------------.           ,--------------------------------------------------.
 * | En / 和  |      |   ^  |   %  |      |      |Selall|           | Undo |      |   $  |   @  |   LT |  UP  |   RT   |
 * |----------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab      |   Q  |   D  |   R  |   W  |   B  | Cut  |           | PgUP |   J  |   F  |   U  |   P  |  DN  |   \    |
 * |----------+------+------+------+------+------| Copy |           |      |------+------+------+------+------+--------|
 * |   /      |   A  |   S  |   H  |   T  |   G  |------|           |------|   Y  |   N  |   E  |   O  |   I  |   ,    |
 * |----------+------+------+------+------+------|Paste |           | PgDN |------+------+------+------+------+--------|
 * | Ctl+Shft |   Z  |   X  |   M  |   C  |   V  |      |           |      | .    |   L  |   K  |  '   |   ?  | tmux   |
 * `----------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | LCtrl  | LGui |   Alt|   _  | Esc  |                                       |MouseL|MouseR|   -  |  ~   | Ctrl |
 *   `------------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |MidMs | Del  |       | VolUp| Mute |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       | VolDn|        |      |
 *                                 | Space| Shift|------|       |------| Backsp |Enter |
 *                                 |      |      | Num  |       |  Esc |        |      |
 *                                 `--------------------'       `----------------------'
 *
 * 
 * tmux prefix set to C-b
 * 
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        M(TOJPLOUT),   KC_NO,   KC_EQL, LSFT(KC_5), KC_NO,   KC_NO,   LCTL(KC_A),
        KC_TAB,        KC_Q,         KC_D,   KC_R,   KC_W,   KC_B,   M(CUTCOPY),
        KC_SLSH,       KC_A,         KC_S,   KC_H,   KC_T,   KC_G,
        M(CTLSHFT),    KC_Z,         KC_X,   KC_M,   KC_C,   KC_V,   LCTL(KC_V),
        KC_RCTL,       KC_LGUI,      KC_LALT,JP_UNDS,KC_LCTL,
                                              KC_BTN3,  KC_DEL,
                                                              KC_NO,
                                               KC_SPC,KC_LSFT,MO(NUM),
        // right hand
             LCTL(KC_Z), KC_NO, LSFT(KC_4),      JP_AT,   KC_LEFT,       KC_UP,   KC_RIGHT,
             KC_PGUP,    KC_J,       KC_F,       KC_U,       KC_P,       KC_DOWN, LSFT(KC_3),
                         KC_Y,       KC_N,       KC_E,       KC_O,       KC_I,    KC_COMMA,
             KC_PGDN, KC_DOT,     KC_L,       KC_K,       LSFT(KC_7), KC_QUES,   LCTL(KC_B),
                                  KC_BTN1,  KC_BTN2,KC_MINS,JP_TILD,          KC_RCTL,
             KC_VOLU,        KC_MUTE,
             KC_VOLD,
             KC_SPC,KC_BSLS, KC_ENT
    ),
/* Keymap 1: Japanese
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | En / 和|      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        | 　 nu |  ko  |   sa |  he  |  ke  |      |           |      |  fu  |  se  | tsu  | ku   |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   to |  shi |  ka  |  ki  |  su  |------|           |------|  a   |  ha  | te   | ta   |  u   |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   mu |  so  |  hi  |  chi |  me  |      |           |      |      |  ma  |  ho  |  i   |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 | shift|  fn  |------|       |------|      |kazari|
 *                                 |      |      | Num  |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 * 
 * 
 * 
 */
[JP] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, M(JPNU), M(JPKO), M(JPSA), M(JPHE), M(JPKE), KC_TRNS,
       KC_TRNS, M(JPTO), M(JPSHI), M(JPKA), M(JPKI), M(JPSU),
       KC_TRNS, M(JPMU), M(JPSO), M(JPHI), M(JPCHI), M(JPME), KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_NO,
                                  M(SHIFT), M(JPFN), MO(NUM),
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  M(JPFU), M(JPSE), M(JPTSU), M(JPKU), KC_TRNS, KC_TRNS,
                 KC_A, M(JPHA), M(JPTE), M(JPTA), KC_U, KC_TRNS,
       KC_TRNS,  KC_TRNS, M(JPMA), M(JPHO), KC_I, KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
             KC_TRNS,        KC_TRNS,
             KC_TRNS,
             KC_TRNS,KC_TRNS,M(KAZARI)
),
/* Keymap 2: Japanese with Fn
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        | 　    |  xe  |      |      |  xke |      |           |      |  xya |      | xtsu |  xo  |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |  xka |      |      |------|           |------|  xa  | xyo  |      |      |  xu  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |  xi  |      |        |
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
 * 
 * 
 * 
 */
[JPXON] = LAYOUT_ergodox(
	   KC_NO, KC_NO,    KC_NO,        KC_NO,    KC_NO, KC_NO, KC_NO,
	   KC_NO, KC_NO,    M(JPXE),        KC_NO,    M(JPXKE),   KC_NO, KC_NO,
       KC_NO, KC_NO,    KC_NO,          M(JPXKA),      KC_NO, KC_NO, 
       KC_NO, KC_NO,    KC_NO,        KC_NO,    KC_NO, KC_NO, KC_NO,
       KC_TRNS, KC_NO,    KC_NO,        KC_NO,    KC_NO,
                                           KC_NO, KC_NO,
                                                    KC_NO,
                                  KC_NO, KC_TRNS, KC_TRNS,
    // right hand
	   KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
       KC_NO,  M(JPXYA), KC_NO, M(JPXTU), M(JPXO), KC_NO, KC_NO,
                 M(JPXA), M(JPXYO), M(JPXYU), KC_NO, M(JPXU), KC_NO,
       KC_NO,  KC_NO,KC_NO, KC_NO, M(JPXI), KC_NO, KC_NO,
                          KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
       KC_NO, KC_NO,
       KC_NO,
       KC_NO, KC_NO, KC_NO
),
/* Keymap 3: Japanese with kazari
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        | 　    |  go  |  za  |  be  |  ge  |      |           |      |  bu  |  ze  |  du  |  gu  |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |  do  |  ji  |  ga  |  gi  |  zu  |------|           |------|      |  ba  |  de  |  da  |  vu  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |  zo  |  bi  |  di  |      |      |           |      |      |      |  bo  |      |      |        |
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
 * 
 * 
 * 
 */
[JPKAZARI] = LAYOUT_ergodox(
	   KC_NO, KC_NO,    KC_NO,        KC_NO,    KC_NO, KC_NO, KC_NO,
	   KC_NO, KC_NO,    M(JPGO),        M(JPZA),    M(JPBE), M(JPGE), KC_NO,
       KC_NO, M(JPDO),    M(JPJI),        M(JPGA),    M(JPGI), M(JPZU), 
       KC_NO, KC_NO,    M(JPZO),        M(JPBI),    M(JPDI), KC_NO, KC_NO,
       KC_TRNS, KC_NO,    KC_NO,        KC_NO,    KC_NO,
                                           KC_NO, KC_NO,
                                                    KC_NO,
                                  M(SHIFT), KC_NO, KC_TRNS,
    // right hand
	   KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
       KC_NO,  M(JPBU), M(JPZE), M(JPDU), M(JPGU), KC_NO, KC_NO,
                 KC_NO, M(JPBA), M(JPDE), M(JPDA), M(JPVU), KC_NO,
       KC_NO,  KC_NO, KC_NO, M(JPBO), KC_NO, KC_NO, KC_NO,
                          KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
       KC_NO, KC_NO,
       KC_NO,
       KC_NO, KC_NO, KC_TRNS
),
/* Keymap 4: Japanese with Toprow
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        | 　    |  e   |  -   | re   |      |      |           |      |  ya  | ne   |  ru  | o    |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | ra   |  ri  | na   | no   | mi   |------|           |------| wa   |  yo  | yu   | ni   | nn   |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      | mo   | ro   |  wo  |      |        |
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
 * 
 * 
 * 
 */
[JPTOPROW] = LAYOUT_ergodox(
	   KC_NO, KC_NO,    KC_NO,        KC_NO,    KC_NO,   KC_NO, KC_NO,
	   KC_NO, KC_NO,    KC_E,       KC_MINS,  M(JPRE), KC_NO, KC_NO,
       KC_NO, M(JPRA),  M(JPRI),       M(JPNA),  M(JPNO), M(JPMI), 
       KC_NO, KC_NO, KC_NO,    KC_NO,  KC_NO, KC_NO, KC_NO,
       KC_TRNS, KC_NO,    KC_NO,        KC_NO,    KC_NO,
                                           KC_NO, KC_NO,
                                                    KC_NO,
                                  KC_TRNS, KC_NO, KC_NO,
    // right hand
	   KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
       KC_NO,  M(JPYA), M(JPNE), M(JPRU), KC_O, KC_NO, KC_NO,
                 M(JPWA), M(JPYO), M(JPYU), M(JPNI), M(JPNN), KC_NO,
       KC_NO,  KC_NO, M(JPMO), M(JPRO), M(JPWO), KC_NO, KC_NO,
                          KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
       KC_NO, KC_NO,
       KC_NO,
       KC_NO, KC_NO, M(KAZARI)
),

/* Keymap 5: Japanese with Toprow and Kazari
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        | 　    |      |      |  pe  |      |      |           |      |  pu  |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |  pa  |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |  pi  |      |      |      |           |      |      |      |  po  |      |      |        |
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
 * 
 * 
 * 
 */
[JPTRKZ] = LAYOUT_ergodox(
	   KC_NO, KC_NO,    KC_NO,        KC_NO,    KC_NO, KC_NO, KC_NO,
	   KC_NO, KC_NO,    KC_NO,        KC_NO,    M(JPPE),KC_NO,  KC_NO,
       KC_NO, KC_NO,    KC_NO,        KC_NO,    KC_NO, KC_NO, 
       KC_NO, KC_NO,    KC_NO,        M(JPPI),    KC_NO, KC_NO, KC_NO,
       KC_TRNS, KC_NO,    KC_NO,        KC_NO,    KC_NO,
                                           KC_NO, KC_NO,
                                                    KC_NO,
                                  KC_TRNS, KC_NO, KC_NO,
    // right hand
	   KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
       KC_NO,  M(JPPU), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                 KC_NO, M(JPPA), KC_NO, KC_NO, KC_NO, KC_NO,
       KC_NO,  KC_NO, KC_NO, M(JPPO), KC_NO, KC_NO, KC_NO,
                          KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
       KC_NO, KC_NO,
       KC_NO,
       KC_NO, KC_NO, KC_TRNS
),
/* Keymap 6: Number Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |   "  |   [  |   ]  |      |           |   |  |   %  |   7  |   8  |   9  |      |   F12  |
 * |--------+------+------+------+------+------|   ;  |           |      |------+------+------+------+------+--------|
 * |        |      |   /  |   +  |   {  |   }  |------|           |------|   !  |   4  |   5  |   6  |   0  |   ,    |
 * |--------+------+------+------+------+------|   :  |           |   &  |------+------+------+------+------+--------|
 * |        |      |   *  |   -  |   (  |   )  |      |           |      |   .  |   1  |   2  |   3  |   ?  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |   #  |                                       |   <  |   =  |   >  |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------| Back |  Ent |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// Numbers
[NUM] = LAYOUT_ergodox(
       // left hand
	   KC_NO, KC_F1,      KC_F2,          KC_F3,      KC_F4,   KC_F5,   KC_NO,
	   KC_NO, KC_NO,    KC_NO,        JP_DQUO,   KC_RBRACKET,   KC_BSPC, KC_SCLN,
       KC_NO, KC_NO,    KC_SLSH,        JP_PLUS,    LSFT(KC_RBRACKET),   JP_RCBR, 
       KC_NO, KC_NO,    JP_ASTR,        KC_MINS,    LSFT(KC_8), LSFT(KC_9), JP_COLN,
       KC_TRNS, KC_NO,    KC_NO,        KC_NO,    KC_HASH,
                                           KC_NO, KC_NO,
                                                    KC_NO,
                                  KC_NO, KC_NO, KC_TRNS,
       // right hand
       KC_NO, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
       LSFT(KC_JYEN), KC_PERC,   KC_7,   KC_8,    KC_9,    KC_NO, KC_F12,
                KC_EXLM, KC_4,   KC_5,    KC_6,    KC_0, KC_COMM,
       LSFT(KC_6), KC_DOT, KC_1,   KC_2,    KC_3,    KC_QUES, KC_NO,
                         KC_LT,JP_EQL,  KC_GT,    KC_NO,  KC_NO,
       KC_NO, KC_NO,
       KC_NO,
       KC_SPC, KC_BSLS, KC_DOT
),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
	
  // MACRO only works in this function
	switch(id) {
		case 0:
			if (record->event.pressed) {
				register_code(KC_RSFT);
			} else {
				unregister_code(KC_RSFT);
			}
			break;
		case CTLSHFT:
			if (record->event.pressed) {
				return MACRO( D(LSFT), D(LCTL), END);
			} else {
				return MACRO( U(LSFT), U(LCTL), END);
			}
			break;
		case CUTCOPY:
			if (record->event.pressed) {
				start = timer_read();
			} else {
				if (timer_elapsed(start) > 150) {
					return MACRO( D(LCTL), T(X), U(LCTL), END);
				} else {
					return MACRO( D(LCTL), T(C), U(LCTL), END);
				}
			}
			break;
			
		// kana macros start here
			
		case JPVU:
			if (record->event.pressed) {
				return MACRO( I(1), T(V), T(U), END);
			}
			break;
		case JPNU:
			if (record->event.pressed) {
				return MACRO( I(1), T(N), T(U), END);
			}
			break;
		case JPKO:
			if (record->event.pressed) {
				return MACRO( I(1), T(K), T(O), END);
			}
			break;
		case JPSA:
			if (record->event.pressed) {
				return MACRO( I(1), T(S), T(A), END);
			}
			break;
		case JPKE:
			if (record->event.pressed) {
				return MACRO( I(1), T(K), T(E), END);
			}
			break;
		case JPHE:
			if (record->event.pressed) {
				return MACRO( I(1), T(H), T(E), END);
			}
			break;
		case JPSHI:
			if (record->event.pressed) {
				return MACRO( I(1), T(S), T(I), END);
			}
			break;
			case JPKA:
			if (record->event.pressed) {
				return MACRO( I(1), T(K), T(A), END);
			}
			break;
		case JPKI:
			if (record->event.pressed) {
				return MACRO( I(1), T(K), T(I), END);
			}
			break;
		case JPSU:
			if (record->event.pressed) {
				return MACRO( I(1), T(S), T(U), END);
			}
			break;
		case JPSO:
			if (record->event.pressed) {
				return MACRO( I(1), T(S), T(O), END);
			}
			break;
		case JPHI:
			if (record->event.pressed) {
				return MACRO( I(1), T(H), T(I), END);
			}
			break;
		case JPCHI:
			if (record->event.pressed) {
				return MACRO( I(1), T(T), T(I), END);
			}
			break;
		case JPFU:
			if (record->event.pressed) {
				return MACRO( I(1), T(F), T(U), END);
			}
			break;
		case JPSE:
			if (record->event.pressed) {
				return MACRO( I(1), T(S), T(E), END);
			}
			break;
		case JPTSU:
			if (record->event.pressed) {
				return MACRO( I(1), T(T), T(U), END);
			}
			break;
		case JPKU:
			if (record->event.pressed) {
				return MACRO( I(1), T(K), T(U), END);
			}
			break;
		case JPTE:
			if (record->event.pressed) {
				return MACRO( I(1), T(T), T(E), END);
			}
			break;
		case JPTA:
			if (record->event.pressed) {
				return MACRO( I(1), T(T), T(A), END);
			}
			break;
		case JPTO:
			if (record->event.pressed) {
				return MACRO( I(1), T(T), T(O), END);
			}
			break;
		case JPHA:
			if (record->event.pressed) {
				return MACRO( I(1), T(H), T(A), END);
			}
			break;
		case JPHO:
			if (record->event.pressed) {
				return MACRO( I(1), T(H), T(O), END);
			}
			break;
		case JPXKE:
			if (record->event.pressed) {
				return MACRO( I(1), T(X), T(K), T(E), END);
			}
			break;
		case JPXU:
			if (record->event.pressed) {
				return MACRO( I(1), T(X), T(U), END);
			}
			break;
		case JPXKA:
			if (record->event.pressed) {
				return MACRO( I(1), T(X), T(K), T(A), END);
			}
			break;
		case JPXA:
			if (record->event.pressed) {
				return MACRO( I(1), T(X), T(A), END);
			}
			break;
		case JPXO:
			if (record->event.pressed) {
				return MACRO( I(1), T(X), T(O), END);
			}
			break;
		case JPGO:
			if (record->event.pressed) {
				return MACRO( I(1), T(G), T(O), END);
			}
			break;
		case JPZA:
			if (record->event.pressed) {
				return MACRO( I(1), T(Z), T(A), END);
			}
			break;
		case JPGE:
			if (record->event.pressed) {
				return MACRO( I(1), T(G), T(E), END);
			}
			break;
		case JPBE:
			if (record->event.pressed) {
				return MACRO( I(1), T(B), T(E), END);
			}
			break;
		case JPYU:
			if (record->event.pressed) {
				return MACRO( I(1), T(Y), T(U), END);
			}
			break;
		case JPJI:
			if (record->event.pressed) {
				return MACRO( I(1), T(J), T(I), END);
			}
			break;
		case JPGA:
			if (record->event.pressed) {
				return MACRO( I(1), T(G), T(A), END);
			}
			break;
		case JPGI:
			if (record->event.pressed) {
				return MACRO( I(1), T(G), T(I), END);
			}
			break;
		case JPZU:
			if (record->event.pressed) {
				return MACRO( I(1), T(Z), T(U), END);
			}
			break;
		case JPZO:
			if (record->event.pressed) {
				return MACRO( I(1), T(Z), T(O), END);
			}
			break;
		case JPBI:
			if (record->event.pressed) {
				return MACRO( I(1), T(B), T(I), END);
			}
			break;
		case JPDI:
			if (record->event.pressed) {
				return MACRO( I(1), T(D), T(I), END);
			} 
			break;
		case JPZE:
			if (record->event.pressed) {
				return MACRO( I(1), T(Z), T(E), END);
			}
			break;
		case JPDU:
			if (record->event.pressed) {
				return MACRO( I(1), T(D), T(U), END);
			}
			break;
		case JPGU:
			if (record->event.pressed) {
				return MACRO( I(1), T(G), T(U), END);
			}
			break;
		case JPYA:
			if (record->event.pressed) {
				return MACRO( I(1), T(Y), T(A), END);
			}
			break;
		case JPYO:
			if (record->event.pressed) {
				return MACRO( I(1), T(Y), T(O), END);
			}
			break;
		case JPDE:
			if (record->event.pressed) {
				return MACRO( I(1), T(D), T(E), END);
			}
			break;
		case JPDA:
			if (record->event.pressed) {
				return MACRO( I(1), T(D), T(A), END);
			}
			break;
		case JPDO:
			if (record->event.pressed) {
				return MACRO( I(1), T(D), T(O), END);
			}
			break;
		case JPBA:
			if (record->event.pressed) {
				return MACRO( I(1), T(B), T(A), END);
			}
			break;
		case JPBO:
			if (record->event.pressed) {
				return MACRO( I(1), T(B), T(O), END);
			}
			break;
		case JPRI:
			if (record->event.pressed) {
				return MACRO( I(1), T(R), T(I), END);
			}
			break;
		case JPRE:
			if (record->event.pressed) {
				return MACRO( I(1), T(R), T(E), END);
			}
			break;
		case JPRA:
			if (record->event.pressed) {
				return MACRO( I(1), T(R), T(A), END);
			}
			break;
		case JPNA:
			if (record->event.pressed) {
				return MACRO( I(1), T(N), T(A), END);
			}
			break;
		case JPNO:
			if (record->event.pressed) {
				return MACRO( I(1), T(N), T(O), END);
			}
			break;
		case JPMI:
			if (record->event.pressed) {
				return MACRO( I(1), T(M), T(I), END);
			}
			break;
		case JPMU:
			if (record->event.pressed) {
				return MACRO( I(1), T(M), T(U), END);
			}
			break;
		case JPME:
			if (record->event.pressed) {
				return MACRO( I(1), T(M), T(E), END);
			}
			break;
		case JPNE:
			if (record->event.pressed) {
				return MACRO( I(1), T(N), T(E), END);
			}
			break;
		case JPMA:
			if (record->event.pressed) {
				return MACRO( I(1), T(M), T(A), END);
			}
			break;
		case JPXTU:
			if (record->event.pressed) {
				return MACRO( I(1), T(X), T(T), T(U), END);
			}
			break;
		case JPWA:
			if (record->event.pressed) {
				return MACRO( I(1), T(W), T(A), END);
			}
			break;
		case JPRU:
			if (record->event.pressed) {
				return MACRO( I(1), T(R), T(U), END);
			}
			break;
		case JPWO:
			if (record->event.pressed) {
				return MACRO( I(1), T(W), T(O), END);
			}
			break;
		case JPNI:
			if (record->event.pressed) {
				return MACRO( I(1), T(N), T(I), END);
			}
			break;
		case JPNN:
			if (record->event.pressed) {
				return MACRO( I(1), T(N), T(N), END);
			}
			break;
		case JPMO:
			if (record->event.pressed) {
				return MACRO( I(1), T(M), T(O), END);
			}
			break;
		case JPRO:
			if (record->event.pressed) {
				return MACRO( I(1), T(R), T(O), END);
			}
			break;
		case JPXE:
			if (record->event.pressed) {
				return MACRO( I(1), T(X), T(E), END);
			}
			break;
		case JPXI:
			if (record->event.pressed) {
				return MACRO( I(1), T(X), T(I), END);
			}
			break;
		case JPXYU:
			if (record->event.pressed) {
				return MACRO( I(1), T(X), T(Y), T(U), END);
			}
			break;
		case JPXYA:
			if (record->event.pressed) {
				return MACRO( I(1), T(X), T(Y), T(A), END);
			}
			break;
		case JPXYO:
			if (record->event.pressed) {
				return MACRO( I(1), T(X), T(Y), T(O), END);
			}
			break;
		case JPPE:
			if (record->event.pressed) {
				return MACRO( I(1), T(P), T(E), END);
			}
			break;
		case JPPU:
			if (record->event.pressed) {
				return MACRO( I(1), T(P), T(U), END);
			}
			break;
		case JPPI:
			if (record->event.pressed) {
				return MACRO( I(1), T(P), T(I), END);
			}
			break;
		case JPPA:
			if (record->event.pressed) {
				return MACRO( I(1), T(P), T(A), END);
			}
			break;
		case JPPO:
			if (record->event.pressed) {
				return MACRO( I(1), T(P), T(O), END);
			}
			break;
		case JPBU:
			if (record->event.pressed) {
				return MACRO( I(1), T(B), T(U), END);
			}
			break;
			
			// kana macros end here
			
			break;
		case SHIFT:
		if (record->event.pressed) {
			start = timer_read();
			if (layer_state == (1<<JPKAZARI)) {
				layer_state = (1<<JPTOPROW)| (1<<JPTRKZ);
			} else {
				layer_state = (1<<JPTOPROW);							
			} 
      } else {
			layer_state = (0<<JPTOPROW);
			clear_keyboard_but_mods();
			if (timer_elapsed(start) < 100) {
				return MACRO( I(1), T(SPC), END);
			}
      }
      break;
		case KAZARI:
		if (record->event.pressed) {
			start = timer_read();
			if (layer_state == (1<<JPTOPROW)) {
				layer_state = (1<<JPKAZARI)| (1<<JPTRKZ);
			} else {
				layer_state = (1<<JPKAZARI);							
			} 
			break;
      } else {
		  	layer_state = (0<<JPKAZARI);
			layer_state = (0<<JPTRKZ);
		if (timer_elapsed(start) < 100) {
          return MACRO( T(ENTER), END);
        }
      }
      break;  
		case JPFN:
			if (record->event.pressed) {
				start = timer_read();
				layer_state = (1<<JPXON);
			} else {
				layer_state = (0<<JPXON);
				if (timer_elapsed(start) < 100) {
					return MACRO( T(F7), END);
				}
			}
      break;
		case TOJPLOUT:
			if (record->event.pressed) {
				if (default_layer_state == (1<<JP)) {
					default_layer_state = (0<<JP);
				} else {
					default_layer_state = (1<<JP);
				}
				return MACRO( T(ZKHK), END);
			}
			break;
/*
		// TOJPL and TOENL switch keyboard language.
		// The Ctrl+[] commands here load the appropriate ibus-anthy input engine via a WM shortcut
		// The first key pressed in the new engine is missed, thus the space key
		// TOJPLOUT works in the same way but is used for switching engines on external systems.
		case TOJPL:
			if (record->event.pressed) {
				default_layer_state = (1<<JP);
				return MACRO( D(LCTL), T(END), U(LCTL), END);
				//return MACRO( D(LCTL), T(END), U(LCTL), W(250), W(250), W(250), T(SPACE), END);
			}
			break;
		case TOENL:
			if (record->event.pressed) {
				default_layer_state = (1<<BASE);
				return MACRO( D(LCTL), T(HOME), U(LCTL), END);
			//return MACRO( D(LCTL), T(HOME), U(LCTL), W(250), W(250), W(250), T(SPACE), END);
			}
			break;
*/
		}
    return MACRO_NONE;   
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

	uint8_t layer = biton32(layer_state);
   uint8_t deflayer = biton32(default_layer_state);

	ergodox_board_led_off();
	ergodox_right_led_1_off();
	ergodox_right_led_2_off();
	ergodox_right_led_3_off();
    
  
	switch (layer) {
		case 0:
			//none
			break;
//		case 1:
//			ergodox_right_led_2_on();
//			break;
		case 6:
			ergodox_right_led_3_on();
			break;
    }
    switch (deflayer) {
		 case 0:
		 ergodox_right_led_1_off();
		 break;
		 case 1:
		 ergodox_right_led_1_on();
		 break;
	}
};
