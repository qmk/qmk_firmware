/*
Copyright 2020 Cole Smith <cole@boadsource.xyz>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#undef LAYOUT_KC

#define LAYOUT_KC(\
  k01, k02, k03, k04, k05,    k45, k44, k43, k42, k41, \
  k11, k12, k13, k14, k15,    k55, k54, k53, k52, k51, \
  k21, k22, k23, k24, k25,    k65, k64, k63, k62, k61, \
            k33, k34, k35,    k75, k74, k73            \
  ) \
  { \
    {  KC_##k01,  KC_##k02,  KC_##k03,  KC_##k04,  KC_##k05 }, \
    {  KC_##k11,  KC_##k12,  KC_##k13,  KC_##k14,  KC_##k15 }, \
    {  KC_##k21,  KC_##k22,  KC_##k23,  KC_##k24,  KC_##k25 }, \
    { KC_NO,KC_NO,  KC_##k33,  KC_##k34,  KC_##k35 }, \
    {  KC_##k41,  KC_##k42,  KC_##k43,  KC_##k44,  KC_##k45 }, \
    {  KC_##k51,  KC_##k52,  KC_##k53,  KC_##k54,  KC_##k55 }, \
    {  KC_##k61,  KC_##k62,  KC_##k63,  KC_##k64,  KC_##k65 }, \
    { KC_NO, KC_NO,  KC_##k73,  KC_##k74,  KC_##k75 } \
  }

enum microdox_layers {
    _DVO
    , _NBR
    , _FCN
    , _SQL
};

enum microdox_keycodes {
  DVO = SAFE_RANGE
  , NBR
  , FCN
  , SQL
  , DYNAMIC_MACRO_RANGE   
  , UPWD
  , UMLD
  , UTAG
  , TBEN
  , FHOM
  , SLNE
  , HTAG
  , DH2I
  , DMC1
  , FOGD
};

#define KC_BOOT LCTL(LALT(KC_DEL))
#define KC_TSKM LCTL(LSFT(KC_ESC))
#define KC_SHUT LALT(KC_F4)

#define KC_DIT  LCTL(LSFT(KC_A))
#define KC_SCR  LCTL(LSFT(KC_Z))

#define KC_RSET RESET
#define KC_MLFT OSM(MOD_LSFT)

#define LONGPRESS_DELAY 150
#define LAYER_TOGGLE_DELAY 300

#define KC_MREC DYN_REC_START1
#define KC_MDAT DYN_MACRO_PLAY1

#define KC_MRE2 DYN_REC_START2
#define KC_MDA2 DYN_MACRO_PLAY2

#define KC_MSTO DYN_REC_STOP

#define LSPO_KEY KC_9
#define RSPC_KEY KC_0
#define KC_ KC_TRNS 

#define KC_MCTL LCTL_T(KC_ENT)
#define KC_MALT RALT_T(KC_BSPC)

#define KC_RTOG RGB_TOG
#define KC_RMOD RGB_MOD

#define KC_RHUI RGB_HUI
#define KC_RHUD RGB_HUD
#define KC_RSAI RGB_SAI
#define KC_RSAD RGB_SAD
#define KC_RVAI RGB_VAI
#define KC_RVAD RGB_VAD

#define KC_CPY LCTL(KC_C)
#define KC_PST LCTL(KC_V)
#define KC_CUT LCTL(KC_X)
#define KC_UND LCTL(KC_Z)

#define KC_UMLD UMLD
#define KC_UPWD UPWD
#define KC_UTAG UTAG
#define KC_TBEN TBEN

#define KC_FHOM FHOM
#define KC_SLNE SLNE
#define KC_HTAG HTAG
#define KC_DH2I DH2I

#define KC_DMC1 DMC1
#define KC_FOGD FOGD


#define KC_CT_U MT(MOD_LCTL, KC_U)  // Tap for U, hold for Control
#define KC_CT_H MT(MOD_LCTL, KC_H)  // Tap for H, hold for Control

#define KC_SF_E MT(MOD_RSFT, KC_E)  // Tap for E, hold for Shift
#define KC_SF_T MT(MOD_RSFT, KC_T)  // Tap for T, hold for Shift

#define KC_AL_O MT(MOD_LALT, KC_O)  // Tap for O, hold for Alt
#define KC_AL_N MT(MOD_LALT, KC_N)  // Tap for N, hold for Alt


#define KC_CT_6 MT(MOD_LCTL, KC_6)	// Tap for 6, hold for Control
#define KC_CT_L MT(MOD_LCTL, KC_LEFT)	// Tap for LEFT, hold for Control

#define KC_SF_5 MT(MOD_RSFT, KC_5)	// Tap for 5, hold for Shift
#define KC_SF_D MT(MOD_RSFT, KC_DOWN)	// Tap for DOWN, hold for Shift

#define KC_AL_4 MT(MOD_LALT, KC_4)	// Tap for 4, hold for Alt
#define KC_AL_R MT(MOD_LALT, KC_RGHT)	// Tap for RGHT, hold for Alt


#define KC_C_F6 MT(MOD_LCTL, KC_F6)	// Tap for F6, hold for Control
#define KC_C_12 MT(MOD_LCTL, KC_F12)	// Tap for F12, hold for Control

#define KC_S_F5 MT(MOD_RSFT, KC_F5)	// Tap for F5, hold for Shift
#define KC_S_11 MT(MOD_RSFT, KC_F11)	// Tap for F11, hold for Shift

#define KC_A_F4 MT(MOD_LALT, KC_F4)	// Tap for F4, hold for Alt
#define KC_A_10 MT(MOD_LALT, KC_F10)	// Tap for F10, hold for Alt



#define KC_NBR LT(_NBR, KC_SPC)  // Tap for Space, hold for Number layer
#define KC_FCN LT(_FCN, KC_SPC)  // Tap for Space, hold for Function layer

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_DVO] = LAYOUT_KC(
  QUOT, COMM,  DOT,    P,    Y,                F,    G,    C,    R,    L,  
     A, AL_O, SF_E, CT_U,    I,                D, CT_H, SF_T, AL_N,    S,  
  SCLN,    Q,    J,    K,    X,                B,    M,    W,    V,    Z,  
                     ENT,  ESC,  NBR,  FCN,  TAB, BSPC                 
),

[_NBR] = LAYOUT_KC( 
     0,    1,    2,    3, LBRC,             RBRC, HOME,   UP,  END, RTOG,  
  TBEN, AL_4, SF_5, CT_6, SLSH,             BSLS, CT_L, SF_D, AL_R, RMOD,  
   DIT,    7,    8,    9, MINS,              EQL, UMLD, UPWD, UTAG,  SCR, 
                     CPY,  PST,     ,     ,  UND,  CUT               
),

[_FCN] = LAYOUT_KC( 
  RSET,   F1,   F2,   F3, RHUI,             RHUD,   F9,   F8,   F7, MSTO, 
  FHOM, A_F4, S_F5, C_F6, RSAI,             RSAD, C_12, S_11, A_10, SLNE,  
  HTAG, DMC1, SHUT,  DEL, RVAI,             RVAD,  GRV, BOOT, FOGD, DH2I,
                    MRE2, MDA2,     ,     , MDAT, MREC                        
),

[_SQL] =  LAYOUT_KC( 
      ,     ,     ,     ,     ,                 ,     ,     ,     ,     , 
      ,     ,     ,     ,     ,                 ,     ,     ,     ,     ,
      ,     ,     ,     ,     ,                 ,     ,     ,     ,     ,
                    RSET,  INS,     ,     ,  INS, RSET                    
)
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_keyboard_master())
    return OLED_ROTATION_180;
  return rotation;
}

static void render_logo(void) {
  static const char PROGMEM qmk_logo[] = {
     0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0
  };
  oled_write_P(qmk_logo, false);
}

static void render_status(void) {
   switch (get_highest_layer(layer_state)) {
    case _DVO:
      oled_write_P(PSTR("A L O H A\n"), false);
      oled_write_P(PSTR("^\n"), false);
      oled_write_P(PSTR("Layer: Dvorak\n"), false);
      break;
    case _NBR:
      oled_write_P(PSTR("N B R\n"), false);
      oled_write_P(PSTR("  ^\n"), false);
      oled_write_P(PSTR("Layer: Number\n"), false);
      break;
    case _FCN:
      oled_write_P(PSTR("F C N\n"), false);
      oled_write_P(PSTR("    ^\n"), false);
      oled_write_P(PSTR("Layer: Funky\n"), false);
      break;
    case _SQL:
      oled_write_P(PSTR("S Q L\n"), false);
      oled_write_P(PSTR("      ^\n"), false);
      oled_write_P(PSTR("Layer: sql\n"), false);
      break;
    default:
      oled_write_P(PSTR("A L O H A"), false);
      oled_write_P(PSTR("        ^\n"), false);
      oled_write_P(PSTR("Layer: Other\n"), false);
  }
}

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    render_status();
  } else {
    render_logo();
    oled_scroll_left();
  }
    return false;
}

#endif

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

	inline void tap(uint16_t keycode) {
		register_code(keycode);
		unregister_code(keycode);
	};


	static uint16_t key_timer;

  switch (keycode) {
  
    case DVO:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistant_default_layer_set(1UL<<_DVO);
      }
      return false;
      break;
      
    case NBR:  
      if (record->event.pressed) {
        layer_on(_NBR);
        update_tri_layer(_NBR, _FCN, _SQL);
      } else {
        layer_off(_NBR);
        update_tri_layer(_NBR, _FCN, _SQL);
      }
      return false;
      break;
      
    case FCN:     
      if (record->event.pressed) {
        layer_on(_FCN);
        update_tri_layer(_NBR, _FCN, _SQL);
      } else {
        layer_off(_FCN);
        update_tri_layer(_NBR, _FCN, _SQL);
      }
      return false;
      break;
      
    case SQL:
      if (record->event.pressed) {
        layer_on(_SQL);
      } else {
        layer_off(_SQL);
      }
      return false;
      break;
	  
	case UPWD: 
	if (record->event.pressed) {
		key_timer = timer_read();
	} else {
		if (timer_elapsed(key_timer) > LONGPRESS_DELAY) {
			SEND_STRING("hypnU^5}") ;
		} else {
			SEND_STRING("impaV!6;") ;
		}
	}
	break;	
	
	case UMLD: 
	if (record->event.pressed) {
		key_timer = timer_read();
	} else {
		if (timer_elapsed(key_timer) > LONGPRESS_DELAY) {
			SEND_STRING("daviala@mfcgd.com") ;
		} else {
			SEND_STRING("alexander_david@manulife.ca") ;
		}
	}
	break;	


 
	case UTAG: 
	if (record->event.pressed) {
		key_timer = timer_read();
	} else {
		if (timer_elapsed(key_timer) > LONGPRESS_DELAY) {
			SEND_STRING("qmk flash -kb boardsource/microdox -km sphynx") ;
		} else {
			SEND_STRING("daviala") ;
		}
	}
	break;
 
	case TBEN: 
	if (record->event.pressed) {
		key_timer = timer_read();
	} else {
		if (timer_elapsed(key_timer) > LONGPRESS_DELAY) {
			SEND_STRING( SS_TAP(X_TAB) SS_TAP(X_ENTER)) ;
		} else {
			SEND_STRING( SS_TAP(X_DOT) ) ;
		}
	}
	break;

 
	case FHOM: 
	if (record->event.pressed) {
		key_timer = timer_read();
	} else {
		if (timer_elapsed(key_timer) > LONGPRESS_DELAY) {
			SEND_STRING(SS_TAP(X_END)) ;
		} else {
			SEND_STRING(SS_TAP(X_HOME)) ;
		}
	}
	break;

	case SLNE: 
	if (record->event.pressed) {
		key_timer = timer_read();
	} else {
		if (timer_elapsed(key_timer) > LONGPRESS_DELAY) {
			SEND_STRING(SS_LCTRL(SS_TAP(X_A) SS_TAP(X_C))) ;
		} else {
			SEND_STRING(SS_TAP(X_HOME) SS_LSFT(SS_TAP(X_END)) SS_LCTRL(SS_TAP(X_C)));
		}
	}
	break;	

	case HTAG: 
	if (record->event.pressed) {
		key_timer = timer_read();
	} else {
		if (timer_elapsed(key_timer) > LONGPRESS_DELAY) {
			SEND_STRING(SS_TAP(X_F2) SS_TAP(X_END) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_LEFT) SS_TAP(X_DOT) SS_TAP(X_LEFT) ) ;
		} else {
			SEND_STRING(SS_TAP(X_ESCAPE) SS_TAP(X_F2) SS_LCTRL(SS_TAP(X_C))) ;
		}
	}
	break;	

	case DH2I: 
	if (record->event.pressed) {
		key_timer = timer_read();
	} else {
		if (timer_elapsed(key_timer) > LONGPRESS_DELAY) {
			SEND_STRING("5683") ;
		} else {
			SEND_STRING("S@turn" SS_TAP(X_TAB) SS_TAP(X_ENTER)) ;
		}
	}
	break;	

	case DMC1: 
	if (record->event.pressed) {
		key_timer = timer_read();
	} else {
		if (timer_elapsed(key_timer) > LONGPRESS_DELAY) {
			SEND_STRING("\\\\clswvissfglpmc3\\") ;
		} else {
			SEND_STRING("\\\\cdcwvissrndd01\\") ;
		}
	}
	break;	

	case FOGD: 
	if (record->event.pressed) {
		key_timer = timer_read();
	} else {
		if (timer_elapsed(key_timer) > LONGPRESS_DELAY) {
			SEND_STRING("http://clswvissfglpmc1:8080/") ;
		} else {
			SEND_STRING("http://cgswvissfgldmc1:8080/") ;
		}
	}
	break;	



      
  }
  
  return true;
  
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _NBR, _FCN, _SQL);
}
