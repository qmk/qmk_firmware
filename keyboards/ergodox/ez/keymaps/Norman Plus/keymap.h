#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"

//Tap Dance Declarations
enum {
  TD_CTL_CAPS = 0,
  TD_ESC_GRV = 1,
  TD_UNDO_REDO = 2,
  TD_BRACKETS_L = 3,
  TD_BRACKETS_R = 4
};

#define BASE  0 // default layer
#define FN1   1 // mouse layer
#define FN2   2 // numpad / symbol layer
#define FN3   3 // fn layer

#define SELECT_ALL	LCTL(KC_A)
#define UNDO		    LCTL(KC_Z)
#define REDO        LCTL(LSFT(KC_Z))
#define COPY     	  LCTL(KC_C)   
#define PASTE    	  LCTL(KC_V) 

#define LSPO_KEY KC_9
#define RSPC_KEY KC_0

#define DISABLE_SPACE_CADET_ROLLOVER
#define PREVENT_STUCK_MODIFIERS

#define TAPPING_TERM 200
#define LEADER_TIMEOUT 300