/* Copyright 2020 tominabox1
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#define ____ KC_NO

#define LAYOUT_KC( \
	K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, \
	K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, \
	K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, \
	K300, K301, K302, K303, K304, K305,       K307, K308, K309, K310, K311  \
) { \
	{ KC_##K000,  KC_##K001,  KC_##K002,  KC_##K003,  KC_##K004,  KC_##K005,  KC_##K006,  KC_##K007,  KC_##K008,  KC_##K009,  KC_##K010,  KC_##K011 }, \
	{ KC_##K100,  KC_##K101,  KC_##K102,  KC_##K103,  KC_##K104,  KC_##K105,  KC_##K106,  KC_##K107,  KC_##K108,  KC_##K109,  KC_##K110,  KC_##K111 }, \
	{ KC_##K200,  KC_##K201,  KC_##K202,  KC_##K203,  KC_##K204,  KC_##K205,  KC_##K206,  KC_##K207,  KC_##K208,  KC_##K209,  KC_##K210,  KC_##K211 }, \
	{ KC_##K300,  KC_##K301,  KC_##K302,  KC_##K303,  KC_##K304,  KC_##K305,  ____,  KC_##K307,  KC_##K308,  KC_##K309,  KC_##K310,  KC_##K311 }  \
}

enum bm40hsrgb_layers {
  _DVO
  , _NBR
  , _FCN
  , _SQL
};

enum bm40hsrgb_keycodes {
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
  QUOT, COMM,  DOT,    P,    Y, LBRC, RBRC,    F,    G,    C,    R,    L,  
     A, AL_O, SF_E, CT_U,    I, SLSH, BSLS,    D, CT_H, SF_T, AL_N,    S,  
  SCLN,    Q,    J,    K,    X, MINS,  EQL,    B,    M,    W,    V,    Z,  
   CPY,  PST,  ENT,  ESC,  NBR,      SPC,    FCN,  TAB, BSPC, MDAT,  BOOT
),

[_NBR] = LAYOUT_KC( 
     0,    1,    2,    3,   F1,   F2,   F3,   F4, HOME,   UP,  END, RTOG,  
  TBEN, AL_4, SF_5, CT_6,   F5,   F6,   F7,   F8, CT_L, SF_D, AL_R, RMOD,  
   DIT,    7,    8,    9,   F9,  F10,  F11,  F12, UMLD, UPWD, UTAG,  SCR,  
  FHOM, HTAG, DMC1, MREC,     ,    RSET,        , MSTO, FOGD, DH2I, SLNE               
),

[_FCN] = LAYOUT_KC( 
  RSET,     ,     ,     , RHUI,     ,     , RHUD,     ,     ,     ,     , 
      ,     ,     ,     , RSAI,     ,     , RSAD,     ,     ,     ,     ,  
      ,     , SHUT,  DEL, RVAI,     ,     , RVAD,  GRV, BOOT,     ,     ,
      ,     , MRE2, MDA2,     ,         ,       ,  UND,  CUT,     ,      
),


[_SQL] =  LAYOUT_KC( 
      ,     ,     ,     ,     ,     ,     ,     ,     ,     ,     ,     , 
      ,     ,     ,     ,     ,     ,     ,     ,     ,     ,     ,     ,
      ,     ,     ,     ,     ,     ,     ,     ,     ,     ,     ,     ,
      ,     ,     ,     ,     ,         ,       ,     ,     ,     ,      
)
};

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
			SEND_STRING("gale#1C{") ;
		} else {
			SEND_STRING("hypnU^5}") ;
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
			SEND_STRING("qmk flash -kb kprepublic/bm40hsrgb -km sphynx") ;
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
