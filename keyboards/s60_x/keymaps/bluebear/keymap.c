#include QMK_KEYBOARD_H

// Keyboard Layers

enum keyboard_layers {
  BASE,        //Base Layer
  ARROWFN,     //Arrow/FN Layer
  MOUSE,       //Mouse Layer
  MIDI_BASE,   //Midi Layer
  MIDI_CHORDS, //Midi Chord Layer
  MORSE,       //Morse Code Layer
};

// Morse Code Macro Keys

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

// Custom Keys

enum custom_keys {

  // Miscellaneous Keycodes

  TFS = LCTL(LALT(KC_DEL)), // Three Finger Salute - Sends Ctl-Alt-Del
  MAGSYS = SAFE_RANGE, // Magic SysRq key - Sends Alt-PSCR
  MC_LSFT, // Morse Code Left Shift
  MC_RSFT, // Morse Code Right Shift

  // MIDI Chord Keycodes - Major

  MI_CH_C,
  MI_CH_Cs,
  MI_CH_Db = MI_CH_Cs,
  MI_CH_D,
  MI_CH_Ds,
  MI_CH_Eb = MI_CH_Ds,
  MI_CH_E,
  MI_CH_F,
  MI_CH_Fs,
  MI_CH_Gb = MI_CH_Fs,
  MI_CH_G ,
  MI_CH_Gs,
  MI_CH_Ab = MI_CH_Gs,
  MI_CH_A,
  MI_CH_As,
  MI_CH_Bb = MI_CH_As,
  MI_CH_B,

  // MIDI Chord Keycodes Minor

  MI_CH_Cm,
  MI_CH_Csm,
  MI_CH_Dbm = MI_CH_Csm,
  MI_CH_Dm,
  MI_CH_Dsm,
  MI_CH_Ebm = MI_CH_Dsm,
  MI_CH_Em,
  MI_CH_Fm,
  MI_CH_Fsm,
  MI_CH_Gbm = MI_CH_Fsm,
  MI_CH_Gm,
  MI_CH_Gsm,
  MI_CH_Abm = MI_CH_Gsm,
  MI_CH_Am,
  MI_CH_Asm,
  MI_CH_Bbm = MI_CH_Asm,
  MI_CH_Bm,

  //MIDI Chord Keycodes Dominant Seventh

  MI_CH_CDom7,
  MI_CH_CsDom7,
  MI_CH_DbDom7 = MI_CH_CsDom7,
  MI_CH_DDom7,
  MI_CH_DsDom7,
  MI_CH_EbDom7 = MI_CH_DsDom7,
  MI_CH_EDom7,
  MI_CH_FDom7,
  MI_CH_FsDom7,
  MI_CH_GbDom7 = MI_CH_FsDom7,
  MI_CH_GDom7,
  MI_CH_GsDom7,
  MI_CH_AbDom7 = MI_CH_GsDom7,
  MI_CH_ADom7,
  MI_CH_AsDom7,
  MI_CH_BbDom7 = MI_CH_AsDom7,
  MI_CH_BDom7,

  // MIDI Chord Keycodes Diminished Seventh

  MI_CH_CDim7,
  MI_CH_CsDim7,
  MI_CH_DbDim7 = MI_CH_CsDim7,
  MI_CH_DDim7,
  MI_CH_DsDim7,
  MI_CH_EbDim7 = MI_CH_DsDim7,
  MI_CH_EDim7,
  MI_CH_FDim7,
  MI_CH_FsDim7,
  MI_CH_GbDim7 = MI_CH_FsDim7,
  MI_CH_GDim7,
  MI_CH_GsDim7,
  MI_CH_AbDim7 = MI_CH_GsDim7,
  MI_CH_ADim7,
  MI_CH_AsDim7,
  MI_CH_BbDim7 = MI_CH_AsDim7,
  MI_CH_BDim7,

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

  [BASE] = LAYOUT(
				  KC_ESC,  KC_1,  KC_2,  KC_3,  KC_4,  KC_5,  KC_6,  KC_7,  KC_8,  KC_9,  KC_0,  KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_GRV, \
				  KC_TAB,  KC_QUOT, KC_COMM,  KC_DOT,  KC_P,  KC_Y,  KC_F,  KC_G,  KC_C,  KC_R,  KC_L,  KC_SLSH,  KC_EQL,  KC_BSPC,	\
				  CTL_T(KC_ESC),  KC_A,  KC_O,  KC_E,  KC_U,  KC_I,  KC_D,  KC_H,  KC_T,  KC_N,  KC_S,  KC_MINS,  KC_NO,  MT(MOD_RCTL, KC_ENT),	\
				  KC_LSPO,  KC_NO,  KC_SCLN,  KC_Q,  KC_J,  KC_K,  KC_X,  KC_B,  KC_M,  KC_W,  KC_V,  KC_Z,          KC_RSPC,  KC_NO, \
				  MO(2), KC_LGUI, KC_LALT,  LT(1, KC_SPACE),  ALGR_T(KC_APP),  KC_RGUI,  OSM(MOD_LCTL | MOD_LSFT),  OSM(MOD_LCTL | MOD_LALT)
				  ),

  /* 1: Arrow/FN Layer

	 ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
	 │     │ F1  │ F2  │ F3  │ F4  │ F5  │ F6  │ F7  │ F8  │ F9  │ F10 │ F11 │ F12 │TO(3)│TO(5)│
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

  [ARROWFN] = LAYOUT(
					 KC_TRNS,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9, KC_F10,  KC_F11,  KC_F12,  TO(3),  TO(5), \
					 KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_PGUP,  KC_UP,  KC_NO,  KC_NO,  KC_NO,  KC_INS,  KC_DEL, \
					 KC_CAPS,  KC_HOME,  KC_NO,  KC_END,  KC_NO,  KC_NO,  KC_NO,  KC_LEFT,  KC_DOWN,  KC_RIGHT,  KC_NO,          KC_NO,  KC_TRNS,  \
					 KC_TRNS,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_SPACE,  KC_PGDN,  KC_PSCR,  KC_SLCK,  KC_PAUS,  KC_NO,  KC_TRNS,  KC_NO, \
					 KC_NO,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS
					 ),

  /* 2: Mouse Keys Layer

	 ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
	 │RESET│ F13 │ F14 │ F15 │ F16 │ F17 │ F18 │ F19 │ F20 │ F21 │ F22 │ F23 │ F24 │     │     │
	 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
	 │DEBUG│     │     │     │     │     │     │BTN1 │MS_UP│BTN2 │WH_UP│     │     │     │█████│
	 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
	 │TFS  │     │     │     │     │     │     │MS_LT│MS_DN│MS_RT│WH_DN│BTN3 │▒▒▒▒▒│     │█████│
	 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
	 │MAGSYS▒▒▒▒▒│     │     │     │     │     │     │     │     │     │     │▒▒▒▒▒│     │▒▒▒▒▒│
	 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
	 │     │     │     │█████│█████│█████│ PWR │█████│█████│█████│     │     │     │     │█████│
	 └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
  */

  [MOUSE] = LAYOUT(

				   RESET,  KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21, KC_F22,  KC_F23,  KC_F24,  KC_NO,  KC_NO,  \
				   DEBUG,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_BTN1,  KC_MS_UP,  KC_BTN2,  KC_WH_U,  KC_NO,  KC_NO,  KC_NO, \
				   TFS,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_MS_LEFT,  KC_MS_DOWN,  KC_MS_RIGHT,  KC_WH_D,  KC_BTN3,  KC_NO,  KC_TRNS,  \
				   MAGSYS,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,          KC_TRNS,  KC_NO, \
				   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_POWER,  KC_TRNS, KC_TRNS,  KC_NO,  KC_NO
				   ),

  /* 3: Midi Base Layer

	 ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
	 │TO(0)│ Cmaj│ Gmaj│ Dmaj│ Amaj│ Emaj│ Bmaj│Gbmaj│Dbmaj│Abmaj│Ebmaj│Bbmaj│ Fmaj│     │TO(4)│
	 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
	 │OCT+ │     │  C# │  D# │     │  F# │  G# │  A# │     │  C# │  D# │     │     │     │█████│
	 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
	 │OCT- │  C  │  D  │  E  │  F  │  G  │  A  │  B  │  C  │  D  │  E  │  F  │▒▒▒▒▒│     │█████│
	 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
	 │ Cm  │▒▒▒▒▒│ Gm  │ Dm  │ Am  │ Em  │ Bm  │ Gbm │ Dbm │ Abm │ Ebm │ Bbm │▒▒▒▒▒│ Fm  │▒▒▒▒▒│
	 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
	 │     │     │     │█████│█████│█████│A-OFF│█████│█████│█████│     │     │     │     │█████│
	 └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
  */

  [MIDI_BASE] = LAYOUT(
					   TO(0),  MI_CH_C,  MI_CH_G,  MI_CH_D,  MI_CH_A,  MI_CH_E,  MI_CH_B,  MI_CH_Gb,  MI_CH_Db,  MI_CH_Ab, MI_CH_Eb,  MI_CH_Bb,  MI_CH_F,  KC_NO,  TO(4), \
					   MI_OCTU,  KC_NO,  MI_Cs,  MI_Ds,  KC_NO,  MI_Fs,  MI_Gs,  MI_As,  KC_NO,  MI_Cs_1,  MI_Ds_1,  KC_NO,  KC_NO,  KC_NO, \
					   MI_OCTD,  MI_C,  MI_D,  MI_E,  MI_F,  MI_G,  MI_A,  MI_B,  MI_C_1,  MI_D_1,  MI_E_1,  MI_F_1,  KC_NO,  KC_NO,  \
					   MI_CH_Cm,  KC_NO,  MI_CH_Gm,  MI_CH_Dm,  MI_CH_Am,  MI_CH_Em,  MI_CH_Bm,  MI_CH_Gbm,  MI_CH_Dbm,  MI_CH_Abm,  MI_CH_Ebm,  MI_CH_Bbm,          MI_CH_Fm,  KC_NO, \
					   KC_NO,  KC_NO,  KC_NO,  MI_ALLOFF,  KC_NO, KC_NO,  KC_NO,  KC_NO
					   ),

  /* 4: Midi Chord Layer

	 ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
	 │TO(0)│ Cmaj│ Gmaj│ Dmaj│ Amaj│ Emaj│ Bmaj│Gbmaj│Dbmaj│Abmaj│Ebmaj│Bbmaj│ Fmaj│TO(3)│     │
	 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
	 │OCT+ │  Cm │  Gm │  Dm │  Am │  Em │ Bbm │ Gbm │ Dbm │ Abm │ Ebm │ Bbm │ Fm  │     │█████│
	 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
	 │OCT- │Cdom7│Gdom7│Ddom7│Adom7│Edom7│Bdom7│Gbdo7│Dbdo7│Abdo7│Ebdo7│Bbdo7│▒▒▒▒▒│Fdom7│█████│
	 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
	 │Cdim7│▒▒▒▒▒│Gdim7│Ddim7│Adim7│Edim7│Bdim7│Gbdi7│Dbdi7│Abdi7│Ebdi7│Bbdi7│▒▒▒▒▒│Fdim7│▒▒▒▒▒│
	 ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
	 │     │     │     │█████│█████│█████│A-OFF│█████│█████│█████│     │     │     │     │█████│
	 └─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┘
  */

  [MIDI_CHORDS] = LAYOUT(
						 TO(0),  MI_CH_C,  MI_CH_G,  MI_CH_D,  MI_CH_A,  MI_CH_E,  MI_CH_B,  MI_CH_Gb,  MI_CH_Db,  MI_CH_Ab, MI_CH_Eb,  MI_CH_Bb,  MI_CH_F,  TO(3),  KC_NO, \
						 MI_OCTU,  MI_CH_Cm,  MI_CH_Gm,  MI_CH_Dm,  MI_CH_Am,  MI_CH_Em,  MI_CH_Bm,  MI_CH_Gbm,  MI_CH_Dbm,  MI_CH_Abm,  MI_CH_Ebm,  MI_CH_Bbm,  MI_CH_Fm,  KC_NO, \
						 MI_OCTD,  MI_CH_CDom7,  MI_CH_GDom7,  MI_CH_DDom7,  MI_CH_ADom7,  MI_CH_EDom7,  MI_CH_BDom7,  MI_CH_GbDom7,  MI_CH_DbDom7,  MI_CH_AbDom7,  MI_CH_EbDom7,  MI_CH_BbDom7,  KC_NO,  MI_CH_FDom7, \
						 MI_CH_CDim7,  KC_NO,  MI_CH_GDim7,  MI_CH_DDim7,  MI_CH_ADim7,  MI_CH_EDim7,  MI_CH_BDim7,  MI_CH_GbDim7,  MI_CH_DbDim7,  MI_CH_AbDim7,  MI_CH_EbDim7,  MI_CH_BbDim7,          MI_CH_FDim7,  KC_NO, \
						 KC_NO,  KC_NO,  KC_NO,  MI_ALLOFF,  KC_NO, KC_NO,  KC_NO,  KC_NO
						 ),

  /* 5: Morse Code Layer

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

  [MORSE] = LAYOUT(
				   TO(0),  MC_1,  MC_2,  MC_3,  MC_4,  MC_5,  MC_6,  MC_7,  MC_8,  MC_9,  MC_0,  KC_NO,  KC_NO,  KC_NO,  KC_NO, \
				   KC_TAB,  MC_APOS,  MC_COMM, MC_DOT,  MC_P,  MC_Y,  MC_F,  MC_G,  MC_C,  MC_R,  MC_L,  MC_SLSH,  MC_EQL,  KC_BSPC, \
				   KC_NO,  MC_A,  MC_O,  MC_E,  MC_U,  MC_I,  MC_D,  MC_H,  MC_T,  MC_N,  MC_S,  MC_MINS,  KC_NO,  KC_ENT, \
				   MC_LSFT,  KC_NO,  MC_SCLN,  MC_Q,  MC_J,  MC_K,  MC_X,  MC_B,  MC_M,  MC_W,  MC_V,  MC_Z,          MC_RSFT,  KC_NO, \
				   KC_NO, KC_NO, KC_NO,   MC_SPACE,  KC_NO,  KC_NO,  KC_NO, KC_NO
				   ),

};

// Morse Code Macros

int mc_shift_on = false; // Variable that defines whether MC_LSFT or MC_RSFT are pressed

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {

  switch(id) {

  case 0: //Number 0-)
	if (record->event.pressed) {
	  if (mc_shift_on == true) {
		return MACRO(T(MINS), T(DOT), T(MINS), T(MINS), T(DOT), T(MINS), T(SPACE), END); //-.--.-
	  }
	  else {
		return MACRO(T(MINS), T(MINS), T(MINS), T(MINS), T(MINS), T(SPACE), END); //-----
	  }
	}
	break;

  case 1: //Number 1-!
	if (record->event.pressed) {
	  if (mc_shift_on == true) {
		return MACRO(T(MINS), T(DOT), T(MINS), T(DOT), T(MINS), T(MINS), T(SPACE), END); //-.-.--
	  }
	  else {
		return MACRO(T(DOT), T(MINS), T(MINS), T(MINS), T(MINS), T(SPACE), END); //.----
	  }
	}
	break;

  case 2: //Number 2-@
	if (record->event.pressed) {
	  if (mc_shift_on == true) {
		return MACRO(T(DOT), T(MINS), T(MINS), T(DOT), T(MINS), T(DOT), T(SPACE), END); //.--.-.
	  }
	  else {
		return MACRO(T(DOT), T(DOT), T(MINS), T(MINS), T(MINS), T(SPACE), END); //..---
	  }
	}
	break;

  case 3: // Number 3
	if (record->event.pressed) {
	  return MACRO(T(DOT), T(DOT), T(DOT), T(MINS), T(MINS), T(SPACE), END); //...--
	}
	break;

  case 4: //Number 4-$
	if (record->event.pressed) {
	  if (mc_shift_on == true) {
		return MACRO(T(DOT), T(DOT), T(DOT), T(MINS), T(DOT), T(DOT), T(MINS), T(SPACE), END); //...-..-
	  }
	  else {
		return MACRO(T(DOT), T(DOT), T(DOT), T(DOT), T(MINS), T(SPACE), END); //....-
	  }
	}
	break;

  case 5: //Number 5
	if (record->event.pressed) {
	  return MACRO(T(DOT), T(DOT), T(DOT), T(DOT), T(DOT), T(SPACE), END); //.....
	}
	break;

  case 6: //Number 6
	if (record->event.pressed) {
	  return MACRO(T(MINS), T(DOT), T(DOT), T(DOT), T(DOT), T(SPACE), END); //-....
	}
	break;

  case 7: //Number 7-&
	if (record->event.pressed) {
	  if (mc_shift_on == true) {
		return MACRO(T(DOT), T(MINS), T(DOT), T(DOT), T(DOT), T(SPACE), END); //.-...
	  }
	  else {
		return MACRO(T(MINS), T(MINS), T(DOT), T(DOT), T(DOT), T(SPACE), END); //--...
	  }
	}
	break;

  case 8: //Number 8
	if (record->event.pressed) {
	  return MACRO(T(MINS), T(MINS), T(MINS), T(DOT), T(DOT), T(SPACE), END); //---..
	}
	break;

  case 9: //Number 9-(
	if (record->event.pressed) {
	  if (mc_shift_on == true) {
		return MACRO(T(MINS), T(DOT), T(MINS), T(MINS), T(DOT), T(SPACE), END); //-.--.
	  }
	  else {
		return MACRO(T(MINS), T(MINS), T(MINS), T(MINS), T(DOT), T(SPACE), END); //----.
	  }
	}
	break;

  case 10: //Letter A
	if (record->event.pressed) {
	  return MACRO(T(DOT), T(MINS), T(SPACE), END); //.-
	}
	break;

  case 11: //Letter B
	if (record->event.pressed) {
	  return MACRO(T(MINS), T(DOT), T(DOT), T(DOT), T(SPACE), END); //-...
	}
	break;

  case 12: //Letter C
	if (record->event.pressed) {
	  return MACRO(T(MINS), T(DOT), T(MINS), T(DOT), T(SPACE), END); //-.-.
	}
	break;

  case 13: //Letter D
	if (record->event.pressed) {
	  return MACRO(T(MINS), T(DOT), T(DOT), T(SPACE), END); //-..
	}
	break;

  case 14: //Letter E
	if (record->event.pressed) {
	  return MACRO(T(DOT), T(SPACE), END); //.
	}
	break;

  case 15: //Letter F
	if (record->event.pressed) {
	  return MACRO(T(DOT), T(DOT), T(MINS), T(DOT), T(SPACE), END); //..-.
	}
	break;

  case 16: //Letter G
	if (record->event.pressed) {
	  return MACRO(T(MINS), T(MINS), T(DOT), T(SPACE), END); //--.
	}
	break;

  case 17: //Letter H
	if (record->event.pressed) {
	  return MACRO(T(DOT), T(DOT), T(DOT), T(DOT), T(SPACE), END); //....
	}
	break;

  case 18: //Letter I
	if (record->event.pressed) {
	  return MACRO(T(DOT), T(DOT), T(SPACE), END); //..
	}
	break;

  case 19: //Letter J
	if (record->event.pressed) {
	  return MACRO(T(DOT), T(MINS), T(MINS), T(MINS), T(SPACE), END); //.---
	}
	break;

  case 20: //Letter K
	if (record->event.pressed) {
	  return MACRO(T(MINS), T(DOT), T(MINS), T(SPACE), END); //-.-
	}
	break;

  case 21: //Letter L
	if (record->event.pressed) {
	  return MACRO(T(DOT), T(MINS), T(DOT), T(DOT), T(SPACE), END); //.-..
	}
	break;

  case 22: //Letter M
	if (record->event.pressed) {
	  return MACRO(T(MINS), T(MINS), T(SPACE), END); //--
	}
	break;

  case 23: //Letter N
	if (record->event.pressed) {
	  return MACRO(T(MINS), T(DOT), T(SPACE), END); //-.
	}
	break;

  case 24: //Letter O
	if (record->event.pressed) {
	  return MACRO(T(MINS), T(MINS), T(MINS), T(SPACE), END); //---
	}
	break;

  case 25: //Letter P
	if (record->event.pressed) {
	  return MACRO(T(DOT), T(MINS), T(MINS), T(DOT), T(SPACE), END); //.--.
	}
	break;

  case 26: //Letter Q
	if (record->event.pressed) {
	  return MACRO(T(MINS), T(MINS), T(DOT), T(MINS), T(SPACE), END); //--.-
	}
	break;

  case 27: //Letter R
	if (record->event.pressed) {
	  return MACRO(T(DOT), T(MINS), T(DOT), T(SPACE), END); //.-.
	}
	break;

  case 28: //Letter S
	if (record->event.pressed) {
	  return MACRO(T(DOT), T(DOT), T(DOT), T(SPACE), END); //...
	}
	break;

  case 29: //Letter T
	if (record->event.pressed) {
	  return MACRO(T(MINS), T(SPACE), END); //-
	}
	break;

  case 30: //Letter U
	if (record->event.pressed) {
	  return MACRO(T(DOT), T(DOT), T(MINS), T(SPACE), END); //..-
	}
	break;

  case 31: //Letter V
	if (record->event.pressed) {
	  return MACRO(T(DOT), T(DOT), T(DOT), T(MINS), T(SPACE), END); //...-
	}
	break;

  case 32: //Letter W
	if (record->event.pressed) {
	  return MACRO(T(DOT), T(MINS), T(MINS), T(SPACE), END); //.--
	}
	break;

  case 33: //Letter X
	if (record->event.pressed) {
	  return MACRO(T(MINS), T(DOT), T(DOT), T(MINS), T(SPACE), END); //-..-
	}
	break;

  case 34: //Letter Y
	if (record->event.pressed) {
	  if (mc_shift_on == true) {
	  }
	  return MACRO(T(MINS), T(DOT), T(MINS), T(MINS), T(SPACE), END); //-.--
	}
	break;

  case 35: //Letter Z
	if (record->event.pressed) {
	  return MACRO(T(MINS), T(MINS), T(DOT), T(DOT), T(SPACE), END); //--..
	}
	break;

  case 36: //Punctuation .
	if (record->event.pressed) {
	  return MACRO(T(DOT), T(MINS), T(DOT), T(MINS), T(DOT), T(MINS), T(SPACE), END); //.-.-.-
	}
	break;

  case 37: //Punctuation ,
	if (record->event.pressed) {
	  return MACRO(T(MINS), T(MINS), T(DOT), T(DOT), T(MINS), T(MINS), T(SPACE), END); //--..--
	}
	break;

  case 38: //Punctuation '-"
	if (record->event.pressed) {
	  if (mc_shift_on == true) {
		return MACRO(T(DOT), T(MINS), T(DOT), T(DOT), T(MINS), T(DOT), T(SPACE), END); //.-..-.
	  }
	  else {
		return MACRO(T(DOT), T(MINS), T(MINS), T(MINS), T(MINS), T(DOT), T(SPACE), END); //-....-
	  }
	}
	break;

  case 39: //Punctuation /-?
	if (record->event.pressed) {
	  if (mc_shift_on == true) {
		return MACRO(T(DOT), T(DOT), T(MINS), T(MINS), T(DOT), T(DOT), T(SPACE), END); //..--..
	  }
	  else {
		return MACRO(T(MINS), T(DOT), T(DOT), T(MINS), T(DOT), T(SPACE), END); //-..-.
	  }
	}
	break;

  case 40: //Punctuation ;-:
	if (record->event.pressed) {
	  if (mc_shift_on == true) {
		return MACRO(T(MINS), T(MINS), T(MINS), T(DOT), T(DOT), T(DOT), T(SPACE), END); //---...
	  }
	  else {
		return MACRO(T(MINS), T(DOT), T(MINS), T(DOT), T(MINS), T(DOT), T(SPACE), END); //-.-.-.
	  }
	}
	break;

  case 41: //Punctuation =-+
	if (record->event.pressed) {
	  if (mc_shift_on == true) {
		return MACRO(T(DOT), T(MINS), T(DOT), T(MINS), T(DOT), T(SPACE), END); //.-.-.
	  }
	  else {
		return MACRO(T(MINS), T(DOT), T(DOT), T(DOT), T(MINS), T(SPACE), END); //-...-
	  }
	}
	break;

  case 42: //Punctuation --_
	if (record->event.pressed) {
	  if (mc_shift_on == true) {
		return MACRO(T(DOT), T(DOT), T(MINS), T(MINS), T(DOT), T(MINS), T(SPACE), END); //..--.-
	  }
	  else {
		return MACRO(T(MINS), T(DOT), T(DOT), T(DOT), T(DOT), T(MINS), T(SPACE), END); //-....-
	  }
	}
	break;

  case 43: //Morse Space
	if (record->event.pressed) {
	  return MACRO(T(BSLS), T(SPACE), END); //When pressed, this sends a slash followed by a space, making it easier to distinguish words in Morse
	}
	break;
  }
  return MACRO_NONE;
}

// Custom Keys

bool process_record_user (uint16_t keycode, keyrecord_t *record) {

  uint16_t root_note = MIDI_INVALID_NOTE; // Starting value for the root note of each chord

  switch(keycode) {

	// Miscellaneous Keycodes

  case MAGSYS: //Magic SysRq function - Toggles key on and off depending on state of LALT key
	if (record->event.pressed) {
	  if (keyboard_report->mods & (MOD_BIT(KC_LALT))) {
		unregister_code(KC_PSCR);
		unregister_code(KC_LALT);
	  } else {
		register_code(KC_LALT);
		register_code(KC_PSCR);
	  }
	}
	break;

  case MC_LSFT ... MC_RSFT:
	if (record->event.pressed) {
	  mc_shift_on = true;
	}
	else {
	  mc_shift_on = false;
	}
	break;

	// MIDI Chord Keycodes

  case MI_CH_C ... MI_CH_B: // Major Chords
	root_note = keycode - MI_CH_C + MI_C;
	process_midi(root_note, record);
	process_midi(root_note + 4, record); // Major Third Note
	process_midi(root_note + 7, record); // Fifth Note
	break;

  case MI_CH_Cm ... MI_CH_Bm: // Minor Chord
	root_note = keycode - MI_CH_Cm + MI_C;
	process_midi(root_note, record);
	process_midi(root_note + 3, record); // Minor Third Note
	process_midi(root_note + 7, record); // Fifth Note
	break;

  case MI_CH_CDom7 ... MI_CH_BDom7: // Dominant 7th Chord
	root_note = keycode - MI_CH_CDom7 + MI_C;
	process_midi(root_note, record);
	process_midi(root_note + 4, record); // Major Third Note
	process_midi(root_note + 10, record); // Minor Seventh Note
	break;

  case MI_CH_CDim7 ... MI_CH_BDim7: // Diminished 7th Chord
	root_note = keycode - MI_CH_CDim7 + MI_C;
	process_midi(root_note, record);
	process_midi(root_note + 3, record); // Minor Third Note
	process_midi(root_note - 3, record); // Diminished 7th Note
	break;
  }
  return true;
}
