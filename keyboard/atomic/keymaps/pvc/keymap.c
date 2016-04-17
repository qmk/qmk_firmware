#include "atomic.h"
#include "action_layer.h"

#ifdef AUDIO_ENABLE
#include "audio.h"
#include "musical_notes.h"
#endif


#define _QW 0
#define _LW 1
#define _RS 2
#define _AD 3
#define _FN 4

#define M_QW 0
#define M_LW 1
#define M_RS 2
#define M_FN 3


#define _______ KC_TRNS
#define ___T___ KC_TRNS
#define XXXXXXX KC_NO

/*
 * .---------------------------------------------------------------------------------------------------------------------- 2u ------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      | -      | =      | XXXXXX . BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | Q      | W      | E      | R      | T      | Y      | U      | I      | O      | P      | [      | ]      | \      | DEL    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ------------+--------|
 * | CAPS   | A      | S      | D      | F      | G      | H      | J      | K      | L      | ;      | '      | XXXXXX . ENTER  | PG UP  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+- 2u ---------------------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      | N      | M      | ,      | .      | /      | XXXXXX . RSHIFT | UP     | PG DN  |
 * |--------+--------+--------+--------+--------+- 2u ------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | LCTRL  | LWIN   | FN     | LALT   | RAISED | XXXXXX . SPACE  | LOWER  | RALT   | HOME   | END    | RCTRL  | LEFT   | DOWN   | RIGHT  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 [_QW] = { /* QWERTY */
  { KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, XXXXXXX  },
  { KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL   },
  { KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  XXXXXXX, KC_PGUP  },
  { KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, XXXXXXX, KC_UP,   KC_PGDN  },
  { KC_LCTL, KC_LGUI, M(M_FN), KC_LALT, M(M_RS), KC_SPC,  XXXXXXX, M(M_LW), KC_RALT, KC_HOME, KC_END,  KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT  },
 },
 [_LW] = { /* LOWERED */
  { KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  ___T___, ___T___  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_INS   },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, ___T___, ___T___, _______  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, ___T___, ___T___, _______, _______  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  },
 },
 [_RS] = { /* RAISED */
  { KC_TILD, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  ___T___, ___T___  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_INS   },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, ___T___, ___T___, _______  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, ___T___, ___T___, _______, _______  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  },
 },
 [_FN] = { /* FUNCTION */
  { KC_NLCK, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  ___T___, ___T___  },
  { KC_SLCK, KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,  KC_PAUS, KC_PSCR  },
  { KC_CAPS, KC_BTN5, KC_BTN4, KC_BTN3, KC_BTN2, KC_ACL0, KC_ACL2, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY, _______, ___T___, ___T___, KC_WH_U  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, ___T___, ___T___, KC_MS_U, KC_WH_D  },
  { _______, _______, _______, _______, _______, KC_BTN1, KC_BTN1, _______, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R  },
 },
 [_AD] = { /* ADJUST */
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, ___T___, ___T___  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, ___T___, ___T___, _______  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, ___T___, ___T___, _______, _______  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  },
 },
};

#define IS_LAYER_ON(layer) (layer_state & (1UL << (layer)))
#define IS_LAYER_OFF(layer) (!IS_LAYER_ON(layer))

#ifdef AUDIO_ENABLE




float tone_lw[][2] = {
Q_NOTE(_C4   ) ,
Q_NOTE(_CS4  ) ,
Q_NOTE(_D4   ) ,
Q_NOTE(_DS4  ) ,
Q_NOTE(_E4   ) ,
Q_NOTE(_F4   ) ,
Q_NOTE(_FS4  ) ,
Q_NOTE(_G4   ) ,
Q_NOTE(_GS4  ) ,
Q_NOTE(_A4   ) ,
Q_NOTE(_AS4  ) ,
Q_NOTE(_B4   ) ,
};

float tone_rs[][2] = {
  {440.0*pow(2.0,(59)/12.0), 8},
  {440.0*pow(2.0,(60)/12.0), 8},
  {0, 4},
  {440.0*pow(2.0,(67)/12.0), 16},
  {0, 4},
  {440.0*pow(2.0,(71)/12.0), 16}
};

float tone_fn[][2] = {
  {440.0*pow(2.0,(59)/12.0), 8},
  {440.0*pow(2.0,(60)/12.0), 8},
  {0, 4},
  {440.0*pow(2.0,(67)/12.0), 16},
  {0, 4},
  {440.0*pow(2.0,(69)/12.0), 16},
  {0, 4},
  {440.0*pow(2.0,(67)/12.0), 16}
};
#endif


void update_tri_layer(uint8_t layer1, uint8_t layer2, uint8_t layer3)
{
	if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2))
	{
            #ifdef AUDIO_ENABLE
              println("PlayNotes FN");
              play_notes(&tone_fn, 8, false);
            #endif
		layer_on(layer3);
	}
	else
	{
	    layer_off(layer3);
	}
}

void update_quad_layer(uint8_t layer1, uint8_t layer2, uint8_t layer3, uint8_t layer4, bool order)
{
	if (order)
	{
		if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2))
		{
			layer_on(layer3);
		}
		else
		{
		    layer_off(layer3);
		    layer_off(layer4);
		}
	}
	else
	{
		if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2))
		{
			layer_on(layer4);
		}
		else
		{
			layer_off(layer3);
		    layer_off(layer4);
		}
	}
}


const uint16_t PROGMEM fn_actions[] = {
};

#define ARRAY_SIZE(x) ((sizeof x) / (sizeof *x))

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case M_LW:
          if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
              println("PlayNotes LW");
              print_val_hex32(ARRAY_SIZE(tone_lw));
              play_notes(&tone_lw, 12, false);
            #endif
            layer_on(_LW);
            update_tri_layer(_LW, _RS, _FN);
          } else {
            layer_off(_LW);
            update_tri_layer(_LW, _RS, _FN);
          }
          break;
        case M_RS:
          if (record->event.pressed) {
            #ifdef AUDIO_ENABLE
              println("PlayNotes RS");
              play_notes(&tone_rs, 6, false);
            #endif
            layer_on(_RS);
            update_tri_layer(_LW, _RS, _FN);
          } else {
            layer_off(_RS);
            update_tri_layer(_LW, _RS, _FN);
          }
          break;
		default:
        	break;
      }
    return MACRO_NONE;
};

#ifdef AUDIO_ENABLE
float start_up[][2] = {
  {440.0*pow(2.0,(67)/12.0), 12},
  {440.0*pow(2.0,(64)/12.0), 8},
  {440.0*pow(2.0,(55)/12.0), 8},
  {440.0*pow(2.0,(60)/12.0), 8},
  {440.0*pow(2.0,(64)/12.0), 20}
};
#endif

void matrix_init_user(void) {
  #ifdef AUDIO_ENABLE
    init_notes();
    play_notes(&start_up, 5, false);
    println("Matrix Init");
  #endif
}
