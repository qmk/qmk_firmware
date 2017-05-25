#include "s60_x.h"

// Keyboard Layers

enum keyboard_layers {
  BASE,     //Base Layer
  ARROWFN,  //Arrow/FN Layer
  MOUSE,    //Mouse Layer
  MIDI,     //Midi Layer
  MORSE,    //Morse Code Layer
};

// Midi Chords

enum midi_chord_modes { //ACTION_FUNCTION id
  major,
  minor,
};

enum midi_chord_root { //ACTION_FUNCTION opt
  C,
  Cs,
  Db = Cs,
  D,
  Ds,
  Eb = Ds,
  E,
  F,
  Fs,
  Gb = Fs,
  G,
  Gs,
  Ab = Gs,
  A,
  As,
  Bb = As,
  B,
};
  
enum midi_chord_keycodes {

  //Major Chords

  MI_CH_C = ACTION_FUNCTION_OPT(major,C),
  MI_CH_Cs = ACTION_FUNCTION_OPT(major,Cs),
  MI_CH_Db = MI_CH_Cs,
  MI_CH_D = ACTION_FUNCTION_OPT(major,D),
  MI_CH_Ds = ACTION_FUNCTION_OPT(major,Ds),
  MI_CH_Eb = MI_CH_Ds,
  MI_CH_E = ACTION_FUNCTION_OPT(major,E),
  MI_CH_F = ACTION_FUNCTION_OPT(major,F),
  MI_CH_Fs = ACTION_FUNCTION_OPT(major,Fs),
  MI_CH_Gb = MI_CH_Fs,
  MI_CH_G = ACTION_FUNCTION_OPT(major,G),
  MI_CH_Gs = ACTION_FUNCTION_OPT(major,Gs),
  MI_CH_Ab = MI_CH_Gs,
  MI_CH_A = ACTION_FUNCTION_OPT(major,A),
  MI_CH_As = ACTION_FUNCTION_OPT(major,As),
  MI_CH_Bb = MI_CH_As,
  MI_CH_B = ACTION_FUNCTION_OPT(major,B),

  //Minor Chords

  MI_CH_Cm = ACTION_FUNCTION_OPT(minor,C),
  MI_CH_Csm = ACTION_FUNCTION_OPT(minor,Cs),
  MI_CH_Dbm = MI_CH_Csm,
  MI_CH_Dm = ACTION_FUNCTION_OPT(minor,D),
  MI_CH_Dsm = ACTION_FUNCTION_OPT(minor,Ds),
  MI_CH_Ebm = MI_CH_Dsm,
  MI_CH_Em = ACTION_FUNCTION_OPT(minor,E),
  MI_CH_Fm = ACTION_FUNCTION_OPT(minor,F),
  MI_CH_Fsm = ACTION_FUNCTION_OPT(minor,Fs),
  MI_CH_Gbm = MI_CH_Fsm,
  MI_CH_Gm = ACTION_FUNCTION_OPT(minor,G),
  MI_CH_Gsm= ACTION_FUNCTION_OPT(minor,Gs),
  MI_CH_Abm = MI_CH_Gsm,
  MI_CH_Am = ACTION_FUNCTION_OPT(minor,A),
  MI_CH_Asm = ACTION_FUNCTION_OPT(minor,As),
  MI_CH_Bbm = MI_CH_Asm,
  MI_CH_Bm = ACTION_FUNCTION_OPT(minor,B),
};

//Morse Code Macro Keys

enum morse_macros {
  MC_0 = M(0),
  MC_1 = M(1),
  MC_2 = M(2),
  MC_3 = M(3),
  MC_4 = M(4),
  MC_5 = M(5),
  MC_6 = M(6),
  MC_7 = M(7),
  MC_8 = M(8),
  MC_9 = M(9),
  MC_A = M(10),
  MC_B = M(11),
  MC_C = M(12),
  MC_D = M(13),
  MC_E = M(14),
  MC_F = M(15),
  MC_G = M(16),
  MC_H = M(17),
  MC_I = M(18),
  MC_J = M(19),
  MC_K = M(20),
  MC_L = M(21),
  MC_M = M(22),
  MC_N = M(23),
  MC_O = M(24),
  MC_P = M(25),
  MC_Q = M(26),
  MC_R = M(27),
  MC_S = M(28),
  MC_T = M(29),
  MC_U = M(30),
  MC_V = M(31),
  MC_W = M(32),
  MC_X = M(33),
  MC_Y = M(34),
  MC_Z = M(35),
  MC_DOT = M(36),
  MC_COMM = M(37),
  MC_APOS = M(38),
  MC_SLSH = M(39),
  MC_SCLN = M(40),
  MC_EQL = M(41),
  MC_MINS = M(42),
  MC_SPACE = M(43),
};

//Keymaps
  
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* 0: Custom Dvorak/HHKBish Base Layer
	 
	 ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
	 │ ESC │  1  │  2  │  3  │  4  │  5  │  6  │  7  │  8  │  9  │  0  │  [  │  ]  │  \  │  `  │
	 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
	 │ TAB │  '  │  ,  │  .  │  P  │  Y  │  F  │  G  │  C  │  R  │  L  │  /  │  =  │BSPC │█████│
	 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
	 │CT/ES│  A  │  O  │  E  │  U  │  I  │  D  │  H  │  T  │  N  │  S  │  -  │▒▒▒▒▒│CT/EN│█████│
	 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
	 │LSPO │▒▒▒▒▒│  ;  │  Q  │  J  │  K  │  X  │  B  │  M  │  W  │  V  │  Z  │▒▒▒▒▒│RSPC │▒▒▒▒▒│
	 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
	 │MO(2)│L_GUI│L_ALT│█████│█████│█████│SPFN1│█████│█████│█████│AG/AP│R_GUI│CT|S │CT|AL│█████│
	 └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
  */
  
  [BASE] = KEYMAP(
				  KC_ESC,  KC_1,  KC_2,  KC_3,  KC_4,  KC_5,  KC_6,  KC_7,  KC_8,  KC_9,  KC_0,  KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_GRV, \
				  KC_TAB,  KC_QUOT, KC_COMM,  KC_DOT,  KC_P,  KC_Y,  KC_F,  KC_G,  KC_C,  KC_R,  KC_L,  KC_SLSH,  KC_EQL,  KC_BSPC,	\
				  CTL_T(KC_ESC),  KC_A,  KC_O,  KC_E,  KC_U,  KC_I,  KC_D,  KC_H,  KC_T,  KC_N,  KC_S,  KC_MINS,  KC_NO,  MT(MOD_RCTL, KC_ENT),	\
				  KC_LSPO,  KC_NO,  KC_SCLN,  KC_Q,  KC_J,  KC_K,  KC_X,  KC_B,  KC_M,  KC_W,  KC_V,  KC_Z,  KC_NO,  KC_RSPC,  KC_NO, \
				  MO(2), KC_LGUI, KC_LALT,  LT(1, KC_SPACE),  ALGR_T(KC_APP),  KC_RGUI,  OSM(MOD_LCTL | MOD_LSFT),  OSM(MOD_LCTL | MOD_LALT)
				  ),

  /* 1: Arrow/FN Layer

	 ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
	 │     │ F1  │ F2  │ F3  │ F4  │ F5  │ F6  │ F7  │ F8  │ F9  │ F10 │ F11 │ F12 │TO(3)│TO(4)│
	 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
	 │     │     │     │     │     │     │     │PGUP │  UP │     │     │     │ INS │ DEL │█████│
	 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
	 │CAPS │HOME │     │ END │     │     │     │LEFT │DOWN │RIGHT│     │     │▒▒▒▒▒│     │█████│
	 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
	 │     │▒▒▒▒▒│     │     │     │     │     │SPACE│PGDN │PSCR │SLCK │PAUSE│▒▒▒▒▒│     │▒▒▒▒▒│
	 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
	 │     │     │     │█████│█████│█████│     │█████│█████│█████│     │     │     │     │█████│
	 └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
  */

  [ARROWFN] = KEYMAP(
					 KC_TRNS,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9, KC_F10,  KC_F11,  KC_F12,  TO(3),  TO(4), \
					 KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_PGUP,  KC_UP,  KC_NO,  KC_NO,  KC_NO,  KC_INS,  KC_DEL, \
					 KC_CAPS,  KC_HOME,  KC_NO,  KC_END,  KC_NO,  KC_NO,  KC_NO,  KC_LEFT,  KC_DOWN,  KC_RIGHT,  KC_NO,  KC_NO,  KC_NO,  KC_TRNS,  \
					 KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_SPACE,  KC_PGDN,  KC_PSCR,  KC_SLCK,  KC_PAUS,  KC_NO,  KC_NO,  KC_NO, \
					 KC_NO,  KC_NO,  KC_NO,  KC_TRNS,  KC_NO, KC_NO,  KC_NO,  KC_TRNS
					 ),

  /* 2: Mouse Keys Layer

	 ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
	 │RESET│ F1  │ F2  │ F3  │ F4  │ F5  │ F6  │ F7  │ F8  │ F9  │ F10 │ F11 │ F12 │     │     │
	 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
	 │     │     │     │     │     │     │     │BTN1 │MS_UP│BTN2 │WH_UP│     │     │     │█████│
	 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
	 │     │     │     │     │     │     │     │MS_LT│MS_DN│MS_RT│WH_DN│BTN3 │▒▒▒▒▒│     │█████│
	 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
	 │     │▒▒▒▒▒│     │     │     │     │     │     │     │     │     │     │▒▒▒▒▒│     │▒▒▒▒▒│
	 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
	 │     │     │     │█████│█████│█████│ PWR │█████│█████│█████│     │     │     │     │█████│
	 └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
  */

  [MOUSE] = KEYMAP(
					 
				   RESET,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9, KC_F10,  KC_F11,  KC_F12,  KC_NO,  KC_NO,  \
				   KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_BTN1,  KC_MS_UP,  KC_BTN2,  KC_WH_U,  KC_NO,  KC_NO,  KC_NO,  \
				   KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_MS_LEFT,  KC_MS_DOWN,  KC_MS_RIGHT,  KC_WH_D,  KC_BTN3,  KC_NO,  KC_NO,  \
				   KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO, \
				   KC_TRNS,  KC_NO,  KC_NO,  KC_POWER,  KC_NO, KC_NO,  KC_NO,  KC_NO
				   ),

  /* 3: Midi Layer

	 ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
	 │TO(0)│ Cmaj│ Gmaj│ Dmaj│ Amaj│ Emaj│ Bmaj│Gbmaj│Dbmaj│Abmaj│Ebmaj│Bbmaj│ Fmaj│     │     │
	 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
	 │     │     │  C# │  D# │     │  F# │  G# │  A# │     │  C# │  D# │     │     │     │█████│
	 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
	 │OCT- │  C  │  D  │  E  │  F  │  G  │  A  │  B  │  C  │  D  │  E  │  F  │▒▒▒▒▒│OCT+ │█████│
	 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
	 │ Am  │▒▒▒▒▒│ Em  │ Bm  │ F#m │ C#m │ G#m │ D#m │ Bbm │ Fm  │ Cm  │ Gm  │▒▒▒▒▒│ Dm  │▒▒▒▒▒│
	 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
	 │     │     │     │█████│█████│█████│A-OFF│█████│█████│█████│     │     │     │     │█████│
	 └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
  */
	
  [MIDI] = KEYMAP(
				  TO(0),  MI_CH_C,  MI_CH_G,  MI_CH_D,  MI_CH_A,  MI_CH_E,  MI_CH_B,  MI_CH_Gb,  MI_CH_Db,  MI_CH_Ab, MI_CH_Eb,  MI_CH_Bb,  MI_CH_F,  KC_NO,  KC_NO, \
				  KC_NO,  KC_NO,  MI_Cs,  MI_Ds,  KC_NO,  MI_Fs,  MI_Gs,  MI_As,  KC_NO,  MI_Cs_1,  MI_Ds_1,  KC_NO,  KC_NO,  KC_NO, \
				  MI_OCTD,  MI_C,  MI_D,  MI_E,  MI_F,  MI_G,  MI_A,  MI_B,  MI_C_1,  MI_D_1,  MI_E_1,  MI_F_1,  KC_NO,  MI_OCTU,  \
				  MI_CH_Am,  KC_NO,  MI_CH_Em,  MI_CH_Bm,  MI_CH_Fsm,  MI_CH_Csm,  MI_CH_Gsm,  MI_CH_Dsm,  MI_CH_Bbm,  MI_CH_Fm,  MI_CH_Cm,  MI_CH_Gm,  KC_NO,  MI_CH_Dm,  KC_NO, \
				  KC_NO,  KC_NO,  KC_NO,  MI_ALLOFF,  KC_NO, KC_NO,  KC_NO,  KC_NO
				  ),

  /* 4: Morse Code Layer
	 
	 ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
	 │TO(0)│  1  │  2  │  3  │  4  │  5  │  6  │  7  │  8  │  9  │  0  │     │     │     │     │
	 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
	 │     │  '  │  ,  │  .  │  P  │  Y  │  F  │  G  │  C  │  R  │  L  │  /  │  =  │BSPC │█████│
	 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
	 │     │  A  │  O  │  E  │  U  │  I  │  D  │  H  │  T  │  N  │  S  │  -  │▒▒▒▒▒│ENTER│█████│
	 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
	 │SHIFT│▒▒▒▒▒│  ;  │  Q  │  J  │  K  │  X  │  B  │  M  │  W  │  V  │  Z  │▒▒▒▒▒│SHIFT│▒▒▒▒▒│
	 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
	 │     │     │     │█████│█████│█████│SPACE│█████│█████│█████│     │     │     │     │█████│
	 └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
  */
  
  [MORSE] = KEYMAP(
				   TO(0),  MC_1,  MC_2,  MC_3,  MC_4,  MC_5,  MC_6,  MC_7,  MC_8,  MC_9,  MC_0,  KC_NO,  KC_NO,  KC_NO,  KC_NO, \
				   KC_TAB,  MC_APOS,  MC_COMM, MC_DOT,  MC_P,  MC_Y,  MC_F,  MC_G,  MC_C,  MC_R,  MC_L,  MC_SLSH,  MC_EQL,  KC_BSPC, \
				   KC_NO,  MC_A,  MC_O,  MC_E,  MC_U,  MC_I,  MC_D,  MC_H,  MC_T,  MC_N,  MC_S,  MC_MINS,  KC_NO,  KC_ENT, \
				   KC_LSFT,  KC_NO,  MC_SCLN,  MC_Q,  MC_J,  MC_K,  MC_X,  MC_B,  MC_M,  MC_W,  MC_V,  MC_Z,  KC_NO,  KC_RSFT,  KC_NO, \
				   KC_NO, KC_NO, KC_NO,   MC_SPACE,  KC_NO,  KC_NO,  KC_NO, KC_NO
				   ),

};

// Morse Code Macros

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  switch(id) {
  case 0: //Number 0-)
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
		return MACRO(T(MINS), T(DOT), T(MINS), T(MINS), T(DOT), T(MINS), T(SPACE), END); //-.--.-
	  }
	  else {
		return MACRO(T(MINS), T(MINS), T(MINS), T(MINS), T(MINS), T(SPACE), END); //-----
	  }
	}
	break;
  case 1: //Number 1-!
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
		return MACRO(T(MINS), T(DOT), T(MINS), T(DOT), T(MINS), T(MINS), T(SPACE), END); //-.-.--
	  }
	  else {
		return MACRO(T(DOT), T(MINS), T(MINS), T(MINS), T(MINS), T(SPACE), END); //.----
	  }
	}
	break;
  case 2: //Number 2-@
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
		return MACRO(T(DOT), T(MINS), T(MINS), T(DOT), T(MINS), T(DOT), T(SPACE), END); //.--.-.
	  }
	  else {
		return MACRO(T(DOT), T(DOT), T(MINS), T(MINS), T(MINS), T(SPACE), END); //..---
	  }
	}
	break;
  case 3: // Number 3
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
	  }
	  return MACRO(T(DOT), T(DOT), T(DOT), T(MINS), T(MINS), T(SPACE), END); //...--
	}
	break;
  case 4: //Number 4-$
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
		return MACRO(T(DOT), T(DOT), T(DOT), T(MINS), T(DOT), T(DOT), T(MINS), T(SPACE), END); //...-..-
	  }
	  else {
		return MACRO(T(DOT), T(DOT), T(DOT), T(DOT), T(MINS), T(SPACE), END); //....-
	  }
	}
	break;
  case 5: //Number 5
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
	  }
	  return MACRO(T(DOT), T(DOT), T(DOT), T(DOT), T(DOT), T(SPACE), END); //.....
	}
	break;
  case 6: //Number 6
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
	  }
	  return MACRO(T(MINS), T(DOT), T(DOT), T(DOT), T(DOT), T(SPACE), END); //-....
	}
	break;
  case 7: //Number 7-&
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
		return MACRO(T(DOT), T(MINS), T(DOT), T(DOT), T(DOT), T(SPACE), END); //.-...
	  }
	  else {
		return MACRO(T(MINS), T(MINS), T(DOT), T(DOT), T(DOT), T(SPACE), END); //--...
	  }
	}
	break;
  case 8: //Number 8
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
	  }
	  return MACRO(T(MINS), T(MINS), T(MINS), T(DOT), T(DOT), T(SPACE), END); //---..
	}
	break;
  case 9: //Number 9-(
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
		return MACRO(T(MINS), T(DOT), T(MINS), T(MINS), T(DOT), T(SPACE), END); //-.--.
	  }
	  else {
		return MACRO(T(MINS), T(MINS), T(MINS), T(MINS), T(DOT), T(SPACE), END); //----.
	  }
	}
	break;
  case 10: //Letter A
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
	  }
	  return MACRO(T(DOT), T(MINS), T(SPACE), END); //.-
	}
	break;
  case 11: //Letter B
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
	  }
	  return MACRO(T(MINS), T(DOT), T(DOT), T(DOT), T(SPACE), END); //-...
	}
	break;
  case 12: //Letter C
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
	  }
	  return MACRO(T(MINS), T(DOT), T(MINS), T(DOT), T(SPACE), END); //-.-.
	}
	break;
  case 13: //Letter D
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
	  }
	  return MACRO(T(MINS), T(DOT), T(DOT), T(SPACE), END); //-..
	}
	break;
  case 14: //Letter E
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
	  }
	  return MACRO(T(DOT), T(SPACE), END); //.
	}
	break;
  case 15: //Letter F
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
	  }
	  return MACRO(T(DOT), T(DOT), T(MINS), T(DOT), T(SPACE), END); //..-.
	}
	break;
  case 16: //Letter G
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
	  }
	  return MACRO(T(MINS), T(MINS), T(DOT), T(SPACE), END); //--.
	}
	break;
  case 17: //Letter H
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
	  }
	  return MACRO(T(DOT), T(DOT), T(DOT), T(DOT), T(SPACE), END); //....
	}
	break; 
  case 18: //Letter I
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
	  }
	  return MACRO(T(DOT), T(DOT), T(SPACE), END); //..
	}
	break;
  case 19: //Letter J
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
	  }
	  return MACRO(T(DOT), T(MINS), T(MINS), T(MINS), T(SPACE), END); //.---
	}
	break;
  case 20: //Letter K
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
	  }
	  return MACRO(T(MINS), T(DOT), T(MINS), T(SPACE), END); //-.-
	}
	break;
  case 21: //Letter L
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
	  }
	  return MACRO(T(DOT), T(MINS), T(DOT), T(DOT), T(SPACE), END); //.-..
	}
	break;
  case 22: //Letter M
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
	  }
	  return MACRO(T(MINS), T(MINS), T(SPACE), END); //--
	}
	break;
  case 23: //Letter N
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
	  }
	  return MACRO(T(MINS), T(DOT), T(SPACE), END); //-.
	}
	break;
  case 24: //Letter O
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
	  }
	  return MACRO(T(MINS), T(MINS), T(MINS), T(SPACE), END); //---
	}
	break;
  case 25: //Letter P
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
	  }
	  return MACRO(T(DOT), T(MINS), T(MINS), T(DOT), T(SPACE), END); //.--.
	}
	break;
  case 26: //Letter Q
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
	  }
	  return MACRO(T(MINS), T(MINS), T(DOT), T(MINS), T(SPACE), END); //--.-
	}
	break;
  case 27: //Letter R
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
	  }
	  return MACRO(T(DOT), T(MINS), T(DOT), T(SPACE), END); //.-.
	}
	break;
  case 28: //Letter S
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
	  }
	  return MACRO(T(DOT), T(DOT), T(DOT), T(SPACE), END); //...
	}
	break;
  case 29: //Letter T
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
	  }
	  return MACRO(T(MINS), T(SPACE), END); //-
	}
	break;
  case 30: //Letter U
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
	  }
	  return MACRO(T(DOT), T(DOT), T(MINS), T(SPACE), END); //..-
	}
	break;
  case 31: //Letter V
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
	  }
	  return MACRO(T(DOT), T(DOT), T(DOT), T(MINS), T(SPACE), END); //...-
	}
	break;
  case 32: //Letter W
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
	  }
	  return MACRO(T(DOT), T(MINS), T(MINS), T(SPACE), END); //.--
	}
	break;
  case 33: //Letter X
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
	  }
	  return MACRO(T(MINS), T(DOT), T(DOT), T(MINS), T(SPACE), END); //-..-
	}
	break;
  case 34: //Letter Y
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
	  }
	  return MACRO(T(MINS), T(DOT), T(MINS), T(MINS), T(SPACE), END); //-.--
	}
	break;
  case 35: //Letter Z
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
	  }
	  return MACRO(T(MINS), T(MINS), T(DOT), T(DOT), T(SPACE), END); //--..
	}
	break;
  case 36: //Punctuation .
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
	  }
	  return MACRO(T(DOT), T(MINS), T(DOT), T(MINS), T(DOT), T(MINS), T(SPACE), END); //.-.-.-
	}
	break;
  case 37: //Punctuation ,
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
	  }
	  return MACRO(T(MINS), T(MINS), T(DOT), T(DOT), T(MINS), T(MINS), T(SPACE), END); //--..--
	}
	break;
  case 38: //Punctuation '-"
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
		return MACRO(T(DOT), T(MINS), T(DOT), T(DOT), T(MINS), T(DOT), T(SPACE), END); //.-..-.
	  }
	  else {
		return MACRO(T(DOT), T(MINS), T(MINS), T(MINS), T(MINS), T(DOT), T(SPACE), END); //-....-
	  }
	}
	break;
  case 39: //Punctuation /-?
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
		return MACRO(T(DOT), T(DOT), T(MINS), T(MINS), T(DOT), T(DOT), T(SPACE), END); //..--..
	  }
	  else {
		return MACRO(T(MINS), T(DOT), T(DOT), T(MINS), T(DOT), T(SPACE), END); //-..-.
	  }
	}
	break;
  case 40: //Punctuation ;-:
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
		return MACRO(T(MINS), T(MINS), T(MINS), T(DOT), T(DOT), T(DOT), T(SPACE), END); //---...
	  }
	  else {
		return MACRO(T(MINS), T(DOT), T(MINS), T(DOT), T(MINS), T(DOT), T(SPACE), END); //-.-.-.
	  }
	}
	break;
  case 41: //Punctuation =-+
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
		return MACRO(T(DOT), T(MINS), T(DOT), T(MINS), T(DOT), T(SPACE), END); //.-.-.
	  }
	  else {
		return MACRO(T(MINS), T(DOT), T(DOT), T(DOT), T(MINS), T(SPACE), END); //-...-
	  }
	}
	break;
  case 42: //Punctuation --_
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
		return MACRO(T(DOT), T(DOT), T(MINS), T(MINS), T(DOT), T(MINS), T(SPACE), END); //..--.-
	  }
	  else {
		return MACRO(T(MINS), T(DOT), T(DOT), T(DOT), T(DOT), T(MINS), T(SPACE), END); //-....-
	  }
	}
	break;
  case 43: //Morse Space
	if (record->event.pressed) {
	  if (keyboard_report->mods & MOD_BIT(KC_LSFT) || MOD_BIT(KC_RSFT)) {
		unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
	  }
	  return MACRO(T(BSLS), T(SPACE), END); //When pressed, this sends a slash followed by a space, making it easier to distinguish words in Morse
	}
	break;
  }
  return MACRO_NONE;
};

// Midi Chord Function

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  uint16_t root_note;
  uint8_t channel = midi_config.channel;
  uint8_t velocity = compute_velocity(midi_config.velocity);
  switch (opt) {
  case 0: //Root note C
	root_note = MI_C;
  case 1: //Root note C#/Db
	root_note = MI_Cs;
  case 2: // Root note D
	root_note = MI_D;
  case 3: // Root note D#/Eb
	root_note = MI_Ds;
  case 4: // Root note E
	root_note = MI_E;
  case 5: // Root note F
	root_note = MI_F;
  case 6: // Root note F#/Gb
	root_note = MI_Fs;
  case 7: // Root note G
	root_note = MI_G;
  case 8: // Root note G#/Ab
	root_note = MI_Gs;
  case 9: // Root note A
	root_note = MI_A;
  case 10: // Root note A#/Bb
	root_note = MI_As;
  case 11: // Root note B
	root_note = MI_B;
	switch (id) {
	  uint8_t root = midi_compute_note(root_note);
	  uint8_t major_third = midi_compute_note(root_note) + 4;
	  uint8_t minor_third = midi_compute_note(root_note) + 3;
	  uint8_t fifth = midi_compute_note(root_note) + 7;
	case 0: //Major chord
	  if (record->event.pressed) {
		midi_send_noteon(&midi_device, channel, root, velocity);
		midi_send_noteon(&midi_device, channel, major_third, velocity);
		midi_send_noteon(&midi_device, channel, fifth, velocity);
	  }
	  else {
		midi_send_noteoff(&midi_device, channel, root, velocity);
		midi_send_noteoff(&midi_device, channel, major_third, velocity);
		midi_send_noteoff(&midi_device, channel, fifth, velocity);		
	  }
	case 1: //Minor chord
	  if (record->event.pressed) {
		midi_send_noteon(&midi_device, channel, root_note, velocity);
		midi_send_noteon(&midi_device, channel, minor_third, velocity);
		midi_send_noteon(&midi_device, channel, fifth, velocity);
	  }
	  else {
		midi_send_noteoff(&midi_device, channel, root, velocity);
		midi_send_noteoff(&midi_device, channel, minor_third, velocity);
		midi_send_noteoff(&midi_device, channel, fifth, velocity);
	  }
	}
  }
}
