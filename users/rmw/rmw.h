#pragma once
#include QMK_KEYBOARD_H

#include "quantum.h"
#include "action.h"
#include "version.h"

#ifdef TAP_DANCE_ENABLE
#include "tapdances.h"
#endif

#ifdef ENCODER_ENABLE
#include "encoder_functions.h"
#endif 

enum user_layers {
    QWERTY = 0
   ,MINIMAK4
   ,NUMPAD 
   ,EDIT 
   ,FSYM 
   ,JSYM 
   ,MEDIA 
   ,ADJUST 
};


// Custom keycodes
#define SFTENT SFT_T(KC_ENT)

enum user_custom_keycodes_universal {
    VRSN = SAFE_RANGE
   ,OS_CSFT = OSM(MOD_LSFT | MOD_LCTL)
   ,OS_GSFT = OSM(MOD_LSFT | MOD_LGUI)
   ,OS_CALT = OSM(MOD_LCTL | MOD_LALT)
   ,OS_ALT  = OSM(MOD_LALT)
   ,OS_CTL  = OSM(MOD_LCTL)
   ,NEW_SAFE_RANGE
};

#ifdef MACOSX
	enum user_custom_keycodes {
	    FORM_GET = NEW_SAFE_RANGE
	   ,FORM_PUT
	   ,OS_CMD    = OSM(MOD_LGUI)
	   ,R_UNDO    = LGUI(KC_Z)
	   ,R_REDO    = LGUI(KC_Y)
	   ,R_CUT     = LGUI(KC_X)
	   ,R_COPY    = LGUI(KC_C)
	   ,R_PASTE   = LGUI(KC_V)
	   ,DEL_WRD   = LALT(KC_BACKSPACE)
	   ,MVW_LEFT  = LALT(KC_LEFT) 
	   ,MVW_RIGHT = LALT(KC_RIGHT)
	   ,SELW_LEFT = LALT(S(KC_LEFT))
	   ,SELW_RIGHT = LALT(S(KC_RIGHT))
	   ,NEW_TAB   = LGUI(KC_T)
	   ,TASK_MAN  = LGUI(LALT(KC_ESCAPE))
	   ,SEL_HOME  = S(LGUI(KC_LEFT))
	   ,SEL_END   = S(LGUI(KC_RIGHT))
	   ,R_HOME    = LGUI(KC_LEFT)
	   ,R_END     = LGUI(KC_RIGHT)
	};
#endif

#ifdef WINDOWS
	enum user_custom_keycodes {
		FORM_GET = NEW_SAFE_RANGE
	   ,FORM_PUT
	   ,OS_WIN    = OSM(MOD_LGUI)
	   ,R_UNDO    = LCTL(KC_Z)
	   ,R_REDO    = LCTL(KC_Y)
	   ,R_CUT     = LCTL(KC_X)
	   ,R_COPY    = LCTL(KC_C)
	   ,R_PASTE   = LCTL(KC_V)
	   ,DEL_WRD   = LALT(KC_BACKSPACE)
	   ,MVW_LEFT  = LCTL(KC_LEFT) 
	   ,MVW_RIGHT = LCTL(KC_RIGHT)
	   ,SELW_LEFT = LCTL(S(KC_LEFT))
	   ,SELW_RIGHT = LCTL(S(KC_RIGHT))
	   ,NEW_TAB   = LCTL(KC_T)
	   ,TASK_MAN  = LCTL(LALT(KC_ESCAPE))
	   ,SEL_HOME  = S(KC_HOME)
	   ,SEL_END   = S(KC_END)
	   ,R_HOME    = KC_HOME
	   ,R_END     = KC_END
};
#endif
