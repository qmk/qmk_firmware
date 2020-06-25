// rmw.h

#pragma once

#include QMK_KEYBOARD_H

#ifdef TAP_DANCE_ENABLE
#    include "tapdances.h"
#endif 
#ifdef ENCODER_ENABLE
#    include "encoder_functions.h"
#endif 

#include "quantum.h"
#include "action.h"
#include "version.h"

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

#ifdef MACOSX
	enum user_custom_keycodes {
	    FORM_GET = SAFE_RANGE
	    ,FORM_PUT
	    ,VRSN
	    ,OS_GSFT = OSM(MOD_LSFT | MOD_LGUI)
	    ,OS_CALT = OSM(MOD_LCTL | MOD_LALT)
	    ,OS_ALT  = OSM(MOD_LALT)
	    ,OS_CTL  = OSM(MOD_LCTL)
	    ,OS_CMD  = OSM(MOD_LGUI)
	    ,R_UNDO  = LGUI(KC_Z)
	    ,R_REDO  = LGUI(KC_Y)
	    ,R_CUT   = LGUI(KC_X)
	    ,R_COPY  = LGUI(KC_C)
	    ,R_PASTE = LGUI(KC_V)
	    ,DEL_WRD = LALT(KC_BSPACE)
	    ,MVW_LEFT = LALT(KC_LEFT) 
	    ,MVW_RIGHT = LALT(KC_RIGHT)
	    ,SELW_LEFT = LALT(S(KC_LEFT))
	    ,SELW_RIGHT = LALT(S(KC_RIGHT))
	    ,NEW_TAB = LGUI(KC_T)
	    ,TASK_MAN = LGUI(LALT(KC_ESCAPE))
	    ,SEL_HOME = S(LGUI(KC_LEFT))
	    ,SEL_END = S(LGUI(KC_RIGHT))
	    ,R_HOME = LGUI(KC_LEFT)
	    ,R_END = LGUI(KC_RIGHT)
	};
#endif