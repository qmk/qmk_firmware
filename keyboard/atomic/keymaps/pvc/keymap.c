#include "atomic.h"
#include "action_layer.h"
#include "eeconfig.h"
#include "led.h"

#ifdef AUDIO_ENABLE
    #include "audio.h"
    #include "song_list.h"
#endif

#define LAYER_QWERTY                     0
#define LAYER_COLEMAK                    1
#define LAYER_DVORAK                     2
#define LAYER_UPPER                      3
#define LAYER_LOWER                      4
#define LAYER_FUNCTION                   5
#define LAYER_MOUSE                      6
#define LAYER_ADJUST                     7

#define MACRO_QWERTY                     0
#define MACRO_COLEMAK                    1
#define MACRO_DVORAK                     2
#define MACRO_UPPER                      3
#define MACRO_LOWER                      4
#define MACRO_FUNCTION                   5
#define MACRO_MOUSE                      6
#define MACRO_TIMBRE_1                   7
#define MACRO_TIMBRE_2                   8
#define MACRO_TIMBRE_3                   9
#define MACRO_TIMBRE_4                  10
#define MACRO_TEMPO_U                   11
#define MACRO_TEMPO_D                   12
#define MACRO_TONE_DEFAULT              13
#define MACRO_MUSIC_TOGGLE              14
#define MACRO_AUDIO_TOGGLE              16
#define MACRO_INC_VOICE                 18
#define MACRO_DEC_VOICE                 19
#define MACRO_BACKLIGHT                 20
#define MACRO_BREATH_TOGGLE             21
#define MACRO_BREATH_SPEED_INC          23
#define MACRO_BREATH_SPEED_DEC          24
#define MACRO_BREATH_DEFAULT            25

#define M_QWRTY             M(MACRO_QWERTY)
#define M_COLMK             M(MACRO_COLEMAK)
#define M_DVORK             M(MACRO_DVORAK)
#define M_UPPER             M(MACRO_UPPER)
#define M_LOWER             M(MACRO_LOWER)
#define M_FUNCT             M(MACRO_FUNCTION)
#define M_MOUSE             M(MACRO_MOUSE)
#define TIMBR_1             M(MACRO_TIMBRE_1)
#define TIMBR_2             M(MACRO_TIMBRE_2)
#define TIMBR_3             M(MACRO_TIMBRE_3)
#define TIMBR_4             M(MACRO_TIMBRE_4)
#define TMPO_UP             M(MACRO_TEMPO_U)
#define TMPO_DN             M(MACRO_TEMPO_D)
#define TMPO_DF             M(MACRO_TONE_DEFAULT)
#define M_BACKL             M(MACRO_BACKLIGHT)
#define M_BRTOG             M(MACRO_BREATH_TOGGLE)
#define M_BSPDU             M(MACRO_BREATH_SPEED_INC)
#define M_BSPDD             M(MACRO_BREATH_SPEED_DEC)
#define M_BDFLT             M(MACRO_BREATH_DEFAULT)


#define VC_UP               M(MACRO_INC_VOICE)
#define VC_DOWN             M(MACRO_DEC_VOICE)


#define SC_UNDO             LCTL(KC_Z)
#define SC_REDO             LCTL(KC_Y)
#define SC_CUT              LCTL(KC_X)
#define SC_COPY             LCTL(KC_C)
#define SC_PSTE             LCTL(KC_V)
#define SC_SELA             LCTL(KC_A)
#define SC_SAVE             LCTL(KC_S)
#define SC_OPEN             LCTL(KC_O)
#define SC_ACLS             LALT(KC_F4)
#define SC_CCLS             LCTL(KC_F4)

#define OS_SHFT             KC_FN0

#define _______             KC_TRNS
#define XXXXXXX             KC_NO
#define ________________    _______, _______
#define XXXXXXXXXXXXXXXX    XXXXXXX, XXXXXXX

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * .---------------------------------------------------------------------------------------------------------------------- 2u ------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      | -      | =      | XXXXXX . BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | Q      | W      | E      | R      | T      | Y      | U      | I      | O      | P      | [      | ]      | \      | DEL    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ------------+--------|
 * | CAPS   | A      | S      | D      | F      | G      | H      | J      | K      | L      | ;      | '      | XXXXXX . ENTER  | PG UP  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ---------------------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      | N      | M      | ,      | .      | /      | XXXXXX . RSHIFT | UP     | PG DN  |
 * |--------+--------+--------+--------+--------+- 2u ------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | LCTRL  | LWIN   | FN     | LALT   | UPPER  | XXXXXX . SPACE  | LOWER  | SHIFT  | RALT   | APP    | RCTRL  | LEFT   | DOWN   | RIGHT  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [LAYER_QWERTY]       = { // QWERTY
  { KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC  },
  { KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL   },
  { KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_ENT,  KC_PGUP  },
  { KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_RSFT, KC_UP,   KC_PGDN  },
  { KC_LCTL, KC_LGUI, M_FUNCT, KC_LALT, M_UPPER, KC_SPC,  KC_SPC,  M_LOWER, OS_SHFT, KC_RALT, KC_APP,  KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT  },
 },

 /* COLEMAK
 * .---------------------------------------------------------------------------------------------------------------------- 2u ------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      | -      | =      | XXXXXX . BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | Q      | W      | F      | P      | G      | J      | L      | U      | Y      | ;      | [      | ]      | \      | DEL    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ------------+--------|
 * | BACKSP | A      | R      | S      | T      | D      | H      | N      | E      | I      | O      | '      | XXXXXX . ENTER  | PG UP  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ---------------------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      | K      | M      | ,      | .      | /      | XXXXXX . RSHIFT | UP     | PG DN  |
 * |--------+--------+--------+--------+--------+- 2u ------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | LCTRL  | LWIN   | FN     | LALT   | UPPER  | XXXXXX . SPACE  | LOWER  | SHIFT  | RALT   | APP    | RCTRL  | LEFT   | DOWN   | RIGHT  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [LAYER_COLEMAK]      = { // COLEMAK
  { KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC  },
  { KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL   },
  { KC_BSPC, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT, KC_ENT,  KC_ENT,  KC_PGUP  },
  { KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_RSFT, KC_UP,   KC_PGDN  },
  { KC_LCTL, KC_LGUI, M_FUNCT, KC_LALT, M_UPPER, KC_SPC,  KC_SPC,  M_LOWER, OS_SHFT, KC_RALT, KC_APP,  KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT  },
},

/* DVORAK
 * .---------------------------------------------------------------------------------------------------------------------- 2u ------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      | [      | ]      | XXXXXX . BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | '      | ,      | .      | P      | Y      | F      | G      | C      | R      | L      | /      | =      | \      | DEL    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ------------+--------|
 * | CAPS   | A      | O      | E      | U      | I      | D      | H      | T      | N      | S      | -      | XXXXXX . ENTER  | PG UP  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ---------------------+--------|
 * | LSHIFT | ;      | Q      | J      | K      | X      | B      | M      | W      | V      | Z      | XXXXXX . RSHIFT | UP     | PG DN  |
 * |--------+--------+--------+--------+--------+- 2u ------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | LCTRL  | LWIN   | FN     | LALT   | UPPER  | XXXXXX . SPACE  | LOWER  | SHIFT  | RALT   | APP    | RCTRL  | LEFT   | DOWN   | RIGHT  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [LAYER_DVORAK]       = { // DVORAK
  { KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_LBRC, KC_RBRC, KC_BSPC, KC_BSPC  },
  { KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH, KC_EQL,  KC_BSLS, KC_DEL   },
  { KC_CAPS, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS, KC_ENT,  KC_ENT,  KC_PGUP  },
  { KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT, KC_RSFT, KC_UP,   KC_PGDN  },
  { KC_LCTL, KC_LGUI, M_FUNCT, KC_LALT, M_UPPER, KC_SPC,  KC_SPC,  M_LOWER, OS_SHFT, KC_RALT, KC_APP,  KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT  },
 },

/* UPPER
 * .---------------------------------------------------------------------------------------------------------------------- 2u ------------.
 * | PRINT  | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | XXXXXX | NUM LK | /      | *      |        | NUM LK | SCR LK | XXXXXX . PAUSE  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * |        | F1     | F2     | F3     | F4     |        |        | 7      | 8      | 9      | -      |        |        |        | INS    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ------------+--------|
 * | CAP LK | F5     | F6     | F7     | F8     |        |        | 4      | 5      | 6      | +      |        | XXXXXX .        | HOME   |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ---------------------+--------|
 * |        | F9     | F10    | F11    | F12    |        |        | 1      | 2      | 3      | ENTER  | XXXXXX .        |        | END    |
 * |--------+--------+--------+--------+--------+- 2u ------------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        |        | 0               |        | RALT   | .      | ENTER  |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [LAYER_UPPER]        = { // UPPER
  { KC_PSCR, M_BRTOG, M_BSPDU, M_BSPDD, M_BDFLT, XXXXXXX, XXXXXXX, KC_NLCK, KC_PSLS, KC_PAST, XXXXXXX, XXXXXXX, KC_SLCK, KC_PAUS, KC_PAUS  },
  { _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   XXXXXXX, XXXXXXX, KC_KP_7, KC_KP_8, KC_KP_9, KC_PMNS, _______, _______, _______, KC_INS   },
  { KC_CAPS, KC_F5,   KC_F6,   KC_F7,   KC_F8,   XXXXXXX, XXXXXXX, KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS, _______, ________________, KC_HOME  },
  { _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX, XXXXXXX, KC_KP_1, KC_KP_2, KC_KP_3, KC_PENT, ________________, _______, KC_END   },
  { _______, _______, _______, _______, _______, KC_KP_0, KC_KP_0, _______, KC_RALT, KC_PDOT, KC_PENT, _______, _______, _______, _______  },
 },

/* LOWER
 * .---------------------------------------------------------------------------------------------------------------------- 2u ------------.
 * |        | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    | F11    | F12    | XXXXXX . BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * |        | $      | {      | [      | (      | %      | #      | )      | ]      | }      | @      |        |        |        | INS    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ------------+--------|
 * |        | ^      | *      | +      | -      | ;      | :      | _      | '      | "      | `      |        | XXXXXX .        | HOME   |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ---------------------+--------|
 * |        | |      | &      | !      | ~      | /      | \      | =      | <      | >      | ?      | XXXXXX .        |        | END    |
 * |--------+--------+--------+--------+--------+- 2u ------------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        |        |                 |        |        |        |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [LAYER_LOWER]        = { // LOWER
  { _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  ________________  },
  { _______, KC_DLR,  KC_LCBR, KC_LBRC, KC_LPRN, KC_PERC, KC_HASH, KC_RPRN, KC_RBRC, KC_RCBR, KC_AT,   _______, _______, _______, KC_INS   },
  { _______, KC_CIRC, KC_ASTR, KC_PPLS, KC_PMNS, KC_SCLN, KC_COLN, KC_UNDS, KC_QUOT, KC_DQT,  KC_GRV,  _______, ________________, KC_HOME  },
  { _______, KC_PIPE, KC_AMPR, KC_EXLM, KC_TILD, KC_SLSH, KC_BSLS, KC_EQL,  KC_LT,   KC_GT,   KC_QUES, ________________, _______, KC_END   },
  { _______, _______, _______, _______, _______, ________________, _______, _______, _______, _______, _______, _______, _______, _______  },
 },

 [LAYER_FUNCTION]     = { // FUNCTION
  { KC_NLCK, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  ________________  },
  { KC_SLCK, KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,  _______, KC_PAUS  },
  { KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, ________________, KC_PSCR  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, ________________, KC_VOLU, KC_MUTE  },
  { _______, _______, _______, _______, _______, KC_MPLY, KC_MPLY, _______, _______, _______, _______, _______, KC_MPRV, KC_VOLD, KC_MNXT  },
 },

#ifdef MOUSEKEY_ENABLE

 [LAYER_MOUSE]        = { // MOUSE
  { _______, KC_ACL0, KC_ACL1, KC_ACL2, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXXXXXXXXXXX  },
  { XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX  },
  { XXXXXXX, KC_BTN5, KC_BTN4, KC_BTN3, KC_BTN2, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXXXXXXXXXXX, KC_WH_U  },
  { _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, ________________, KC_MS_U, KC_WH_D  },
  { _______, _______, _______, _______, _______, KC_BTN1, KC_BTN1, _______, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R  },
 },

#endif

 [LAYER_ADJUST]       = { // ADJUST
  { _______, TIMBR_1, TIMBR_2, TIMBR_3, TIMBR_4, TMPO_UP, TMPO_DN, TMPO_DF, _______, _______, _______, MU_TOG,  AU_TOG,  ________________  },
  { _______, M_QWRTY, M_COLMK, M_DVORK, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, ________________, _______  },
  { _______, _______, _______, _______, M_BACKL, RESET,   _______, M_MOUSE, _______, _______, _______, ________________, MUV_IN,  _______  },
  { _______, _______, _______, _______, _______, ________________, _______, _______, _______, _______, _______, _______, MUV_DE,  _______  },
 },


/*
 [LAYER_EMPTY]        = { // LAYER
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, ________________  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, ________________, _______  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, ________________, _______, _______  },
  { _______, _______, _______, _______, _______, ________________, _______, _______, _______, _______, _______, _______, _______, _______  },
 },
*/

};

#ifdef AUDIO_ENABLE

float tone_my_startup[][2] = SONG(ODE_TO_JOY);
float tone_my_goodbye[][2] = SONG(ROCK_A_BYE_BABY);

float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);

float tone_audio_on[][2]   = SONG(CLOSE_ENCOUNTERS_5_NOTE);
float tone_music_on[][2]   = SONG(DOE_A_DEER);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);

float tone_caps_on[][2]    = SONG(CAPS_LOCK_ON_SOUND);
float tone_caps_off[][2]   = SONG(CAPS_LOCK_OFF_SOUND);
float tone_numlk_on[][2]   = SONG(NUM_LOCK_ON_SOUND);
float tone_numlk_off[][2]  = SONG(NUM_LOCK_OFF_SOUND);
float tone_scroll_on[][2]  = SONG(SCROLL_LOCK_ON_SOUND);
float tone_scroll_off[][2] = SONG(SCROLL_LOCK_OFF_SOUND);

#endif /* AUDIO_ENABLE */

void persistant_default_layer_set(uint16_t default_layer)
{
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_MODS_ONESHOT(MOD_LSFT),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{

    // MACRODOWN only works in this function
    switch(id)
    {

        case MACRO_BREATH_TOGGLE:
            if (record->event.pressed)
            {
                breathing_toggle();
            }
            break;

        case MACRO_BREATH_SPEED_INC:
            if (record->event.pressed)
            {
                breathing_speed_inc(1);
            }
            break;

        case MACRO_BREATH_SPEED_DEC:
            if (record->event.pressed)
            {
                breathing_speed_dec(1);
            }
            break;

        case MACRO_BREATH_DEFAULT:
            if (record->event.pressed)
            {
                breathing_defaults();
            }
            break;

        case MACRO_QWERTY:
            if (record->event.pressed)
            {
                persistant_default_layer_set(1UL<<LAYER_QWERTY);
                #ifdef AUDIO_ENABLE
                    PLAY_NOTE_ARRAY(tone_qwerty, false, STACCATO);
                #endif /* AUDIO_ENABLE */
            }
            break;

        case MACRO_COLEMAK:
            if (record->event.pressed)
            {
                persistant_default_layer_set(1UL<<LAYER_COLEMAK);
                #ifdef AUDIO_ENABLE
                    PLAY_NOTE_ARRAY(tone_colemak, false, STACCATO);
                #endif /* AUDIO_ENABLE */
            }
            break;

        case MACRO_DVORAK:
            if (record->event.pressed)
            {
                persistant_default_layer_set(1UL<<LAYER_DVORAK);
                #ifdef AUDIO_ENABLE
                    PLAY_NOTE_ARRAY(tone_dvorak, false, STACCATO);
                #endif /* AUDIO_ENABLE */
            }
            break;

        case MACRO_UPPER:
            if (record->event.pressed)
            {
                layer_on(LAYER_UPPER);
                breathing_speed_set(2);
                breathing_pulse();
                update_tri_layer(LAYER_LOWER, LAYER_UPPER, LAYER_ADJUST);
            }
            else
            {
                layer_off(LAYER_UPPER);
                update_tri_layer(LAYER_LOWER, LAYER_UPPER, LAYER_ADJUST);
            }
            break;

        case MACRO_LOWER:
            if (record->event.pressed)
            {
                layer_on(LAYER_LOWER);
                breathing_speed_set(2);
                breathing_pulse();
                update_tri_layer(LAYER_LOWER, LAYER_UPPER, LAYER_ADJUST);
            }
            else
            {
                layer_off(LAYER_LOWER);
                update_tri_layer(LAYER_LOWER, LAYER_UPPER, LAYER_ADJUST);
            }
            break;

        case MACRO_FUNCTION:
            if (record->event.pressed)
            {
                breathing_speed_set(3);
                breathing_enable();
                layer_on(LAYER_FUNCTION);
            }
            else
            {
                breathing_speed_set(1);
                breathing_self_disable();
                layer_off(LAYER_FUNCTION);
            }
            break;

#ifdef MOUSEKEY_ENABLE

        case MACRO_MOUSE:
            if (record->event.pressed)
            {
                layer_invert(LAYER_MOUSE);
            }
            break;

#endif /* MOUSEKEY_ENABLE */

#ifdef AUDIO_ENABLE

        case MACRO_TIMBRE_1:
            if (record->event.pressed) set_timbre(TIMBRE_12);
            break;

        case MACRO_TIMBRE_2:
            if (record->event.pressed) set_timbre(TIMBRE_25);
            break;

        case MACRO_TIMBRE_3:
            if (record->event.pressed) set_timbre(TIMBRE_50);
            break;

        case MACRO_TIMBRE_4:
            if (record->event.pressed) set_timbre(TIMBRE_75);
            break;

        case MACRO_TEMPO_U:
            if (record->event.pressed) increase_tempo(10);
            break;

        case MACRO_TEMPO_D:
            if (record->event.pressed) decrease_tempo(10);
            break;

        case MACRO_TONE_DEFAULT:
            if (record->event.pressed)
            {
                set_timbre(TIMBRE_DEFAULT);
                set_tempo(TEMPO_DEFAULT);
            }
            break;

/*
        case MACRO_AUDIO_TOGGLE:
            if (record->event.pressed)
            {
                    if (is_audio_on())
                    {
                        audio_off();
                    }
                    else
                    {
                        audio_on();
                        PLAY_NOTE_ARRAY(tone_audio_on, false, STACCATO);
                    }
            }
            break;

        case MACRO_MUSIC_TOGGLE:
            if (record->event.pressed)
            {
                    if (IS_LAYER_ON(LAYER_MUSIC))
                    {
                        layer_off(LAYER_MUSIC);
                        stop_all_notes();
                    }
                    else
                    {
                    PLAY_NOTE_ARRAY(tone_music_on, false, STACCATO);
                    layer_on(LAYER_MUSIC);
                    }
            }
            break;
        case MACRO_INC_VOICE:
            if (record->event.pressed)
            {
                #ifdef AUDIO_ENABLE
                    voice_iterate();
                    PLAY_NOTE_ARRAY(music_scale, false, STACCATO);
                #endif
            }
            break;

        case MACRO_DEC_VOICE:
            if (record->event.pressed)
            {
                #ifdef AUDIO_ENABLE
                    voice_deiterate();
                    PLAY_NOTE_ARRAY(music_scale, false, STACCATO);
                #endif
            }
            break;
*/

#endif /* AUDIO_ENABLE */

#ifdef BACKLIGHT_ENABLE
        case MACRO_BACKLIGHT:
            if (record->event.pressed)
            {
                backlight_step();
            }
#endif

        default:
            break;

    }
    return MACRO_NONE;
};


#ifdef AUDIO_ENABLE

void matrix_init_user(void)
{
    set_voice(default_voice);
    startup_user();
    println("Matrix Init");
}

void led_set_user(uint8_t usb_led)
{
    static uint8_t old_usb_led = 0;

    _delay_ms(10); // gets rid of tick

    if (!is_playing_notes())
    {
        if ((usb_led & (1<<USB_LED_CAPS_LOCK)) && !(old_usb_led & (1<<USB_LED_CAPS_LOCK)))
        {
                // If CAPS LK LED is turning on...
                PLAY_NOTE_ARRAY(tone_caps_on,  false, LEGATO);
        }
        else if (!(usb_led & (1<<USB_LED_CAPS_LOCK)) && (old_usb_led & (1<<USB_LED_CAPS_LOCK)))
        {
                // If CAPS LK LED is turning off...
                PLAY_NOTE_ARRAY(tone_caps_off, false, LEGATO);
        }
        else if ((usb_led & (1<<USB_LED_NUM_LOCK)) && !(old_usb_led & (1<<USB_LED_NUM_LOCK)))
        {
                // If NUM LK LED is turning on...
                PLAY_NOTE_ARRAY(tone_numlk_on,  false, LEGATO);
        }
        else if (!(usb_led & (1<<USB_LED_NUM_LOCK)) && (old_usb_led & (1<<USB_LED_NUM_LOCK)))
        {
                // If NUM LED is turning off...
                PLAY_NOTE_ARRAY(tone_numlk_off, false, LEGATO);
        }
        else if ((usb_led & (1<<USB_LED_SCROLL_LOCK)) && !(old_usb_led & (1<<USB_LED_SCROLL_LOCK)))
        {
                // If SCROLL LK LED is turning on...
                PLAY_NOTE_ARRAY(tone_scroll_on,  false, LEGATO);
        }
        else if (!(usb_led & (1<<USB_LED_SCROLL_LOCK)) && (old_usb_led & (1<<USB_LED_SCROLL_LOCK)))
        {
                // If SCROLL LED is turning off...
                PLAY_NOTE_ARRAY(tone_scroll_off, false, LEGATO);
        }
    }

    old_usb_led = usb_led;
}


void startup_user()
{
    _delay_ms(10); // gets rid of tick
    PLAY_NOTE_ARRAY(tone_my_startup, false, STACCATO);
}

void shutdown_user()
{
    PLAY_NOTE_ARRAY(tone_my_goodbye, false, STACCATO);
    _delay_ms(2000);
    stop_all_notes();
}

void audio_on_user(void)
{
	PLAY_NOTE_ARRAY(tone_audio_on, false, STACCATO);
}

void music_on_user(void)
{
	PLAY_NOTE_ARRAY(tone_music_on, false, STACCATO);
}

void music_scale_user(void)
{
	PLAY_NOTE_ARRAY(music_scale, false, STACCATO);
}

#endif /* AUDIO_ENABLE */