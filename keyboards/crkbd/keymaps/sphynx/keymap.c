#include QMK_KEYBOARD_H
 
#define LAYOUT_KC( \
  L00, L01, L02, L03, L04,           R00, R01, R02, R03, R04, \
  L10, L11, L12, L13, L14,           R10, R11, R12, R13, R14, \
  L20, L21, L22, L23, L24,           R20, R21, R22, R23, R24, \
                 L30, L31, L32, R30, R31, R32 \
  ) \
  { \
    { KC_NO, KC_##L00, KC_##L01, KC_##L02, KC_##L03, KC_##L04 }, \
    { KC_NO, KC_##L10, KC_##L11, KC_##L12, KC_##L13, KC_##L14 }, \
    { KC_NO, KC_##L20, KC_##L21, KC_##L22, KC_##L23, KC_##L24 }, \
    { KC_NO, KC_NO, KC_NO, KC_##L30, KC_##L31, KC_##L32 }, \
    { KC_NO, KC_##R04, KC_##R03, KC_##R02, KC_##R01, KC_##R00 }, \
    { KC_NO, KC_##R14, KC_##R13, KC_##R12, KC_##R11, KC_##R10 }, \
    { KC_NO, KC_##R24, KC_##R23, KC_##R22, KC_##R21, KC_##R20 }, \
    { KC_NO, KC_NO, KC_NO, KC_##R32, KC_##R31, KC_##R30 } \
  }

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

enum crkbd_layers {
  _DVO
  , _NBR
  , _FCN
  , _SQL
};
 
enum crkbd_keycodes {
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
 


#define KC_RM_T RGB_M_T

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
  [_DVO] = LAYOUT_KC( \
  QUOT, COMM,  DOT,    P,    Y,                F,    G,    C,    R,    L,  
     A, AL_O, SF_E, CT_U,    I,                D, CT_H, SF_T, AL_N,    S,  
  SCLN,    Q,    J,    K,    X,                B,    M,    W,    V,    Z,  
                     ENT,  ESC,  NBR,  FCN,  TAB, BSPC  
  ),


  [_NBR] = LAYOUT_KC( \
     0,    1,    2,    3, LBRC,             RBRC, HOME,   UP,  END, RTOG,  
  TBEN, AL_4, SF_5, CT_6, SLSH,             BSLS, CT_L, SF_D, AL_R, RMOD,  
   DIT,    7,    8,    9, MINS,              EQL, UMLD, UPWD, UTAG,  SCR, 
                     CPY,  PST,     ,     ,  UND,  CUT   
  ),

  [_FCN] = LAYOUT_KC( \
  RSET,   F1,   F2,   F3, RHUI,             RHUD,   F9,   F8,   F7, MSTO, 
  FHOM, A_F4, S_F5, C_F6, RSAI,             RSAD, C_12, S_11, A_10, SLNE,  
  HTAG, DMC1, SHUT,  DEL, RVAI,             RVAD,  GRV, BOOT, FOGD, DH2I,
                    MRE2, MDA2,     ,     , MDAT, MREC  
  ),

  [_SQL] = LAYOUT_KC( \
      ,     ,     ,     ,     ,                 ,     ,     ,     ,     , 
      ,     ,     ,     ,     ,                 ,     ,     ,     ,     ,
      ,     ,     ,     ,     ,                 ,     ,     ,     ,     ,
                    RSET,  INS,     ,     ,  INS, RSET  
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
			SEND_STRING("qmk flash -kb crkbd/rev1 -km sphynx") ;
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

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_DVO 0
#define L_NBR 2
#define L_FCN 4
#define L_SQL 8


void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_DVO:
            oled_write_ln_P(PSTR(" D V O R A K "), false);
            break;
        case L_NBR:
            oled_write_ln_P(PSTR(" N U M B E R "), false);
            break;
        case L_FCN:
            oled_write_ln_P(PSTR(" F U N C T N "), false);
            break;
        case L_SQL:
            oled_write_ln_P(PSTR(" S Q U E R Y "), false);
            break;
        default:
            oled_write_ln_P(PSTR("?????"), false);
    }
}



char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_logo();
    }
    return false;
}


#endif // OLED_ENABLE
