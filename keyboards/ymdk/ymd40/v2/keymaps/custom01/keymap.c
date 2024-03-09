/* 
 * Customización teclado YMD40 por Santiago Intxausti <intxausti@gmail.com>
 */

#include QMK_KEYBOARD_H




//Unicode Keys
enum unicode_names {
    ORDINAL_MALE,
	ORDINAL_FEMALE,
    SMAILING,
    GRINNING,
    BEAMING,
    ROLLING,
    WINKING,
    HALO,
    HEARTS,
    HEARTEYES,
    KISS,
    ZANY,
    OPENHANDS,
    HANDMOUTH,
    PEEKINGEYE,
    SHUSHING,
    THINKING,
    SALUTING,
    EYEBROW,
    SPLODING,
    SUNGLASES,
    YAWNING,
    ANGRY,
    ASTONISHED,
    SAD,
    CHESS,
    HAMMER_SICKLE,
    CUP
    
    
};




//Custom Macro Keys
enum custom_keycodes {
  ALTTAB = SAFE_RANGE,
  WINTAB,
  DEL_LWORD,
  DEL_RWORD,
  DEL_LINE,
  DEL_END_LINE,
  UP_NEW_LINE,
  DOWN_NEW_LINE,
  LENS_UP,
  LENS_DOWN,
  LENS_CLOSE,
  ONOFFBOT
};

bool alttab_token;
bool altwin_token;




//TapDance Functions
enum {
    TD_SIFT_CAPSLOCK,
    TD_RHAND_LAYER,
    TD_WIN_MENU,
    TD_MNXT,
    TD_PLAY,
    TD_VOLD,
    TD_VOLU,
    TD_ESC,
	TD_SFT_MOV,
	TD_CTL_MOV,
    TD_TAB

};




//Layers
enum layer_names {
  _QWERTY,
  _LOWER,
  _RAISE,
  _OTHERS,
  _MOV,
  _MOV2,
  _NUM_PAD,
  _RNUM_PAD,
  _MOUSE,
  _FUNCTION_KEYS,
  _FUNCTION2_KEYS,
  _QWERTY2
};




const uint32_t PROGMEM unicode_map[] = {
    
    [ORDINAL_MALE] = 0xBA, //
    [ORDINAL_FEMALE]  = 0xAA,  // 
 	[SMAILING] = 0x1F642, // 🙂
    [GRINNING]  = 0x1F600,  // 😀
    [BEAMING] = 0x1F601,  // 😁
    [ROLLING]  = 0x1F923, // 🤣
    [WINKING] = 0x1F609, // 😉
    [HALO] = 0x1F607, // 😇
    [HEARTS] = 0x1F970, // 🥰
    [HEARTEYES] = 0x1F60D, // 😍
    [KISS] = 0x1F618, // 😘
    [ZANY] = 0x1F92A, // 🤪
    [OPENHANDS] = 0x1F917, // 🤗
    [HANDMOUTH] = 0x1FAE2, // 🫢
    [PEEKINGEYE] = 0x1FAE3, // 🫣
    [SHUSHING] = 0x1F92B, // 🤫
    [THINKING] = 0x1F914, // 🤔
    [SALUTING] = 0x1FAE1, // 🫡
    [EYEBROW] = 0x1F928, // 🤨
    [SPLODING] = 0x1F92F, //  🤯
    [SUNGLASES] = 0x1F60E, // 😎
    [YAWNING] = 0x1F971, // 🥱
    [ANGRY] = 0x1F621, // 😡
    [ASTONISHED] = 0x1F632, // 😲	
    [SAD] = 0x1F625, // 😥
    [CHESS] = 0x265F, // ♟
    [HAMMER_SICKLE] = 0x262D, // ☭
    [CUP] = 0x2615, // ☕  
          
};




static void handleBoot(void);
static uint32_t key_timer_boot = 0;
uint32_t tiempo_boot = 0;
bool is_boot_active = false;





const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
  {{11, 0}, {10, 0}, {9, 0}, {8, 0}, {7, 0}, {6, 0}, {5, 0}, {4, 0}, {3, 0}, {2, 0}, {1, 0}, {0, 0}},
  {{11, 1}, {10, 1}, {9, 1}, {8, 1}, {7, 1}, {6, 1}, {5, 1}, {4, 1}, {3, 1}, {2, 1}, {1, 1}, {0, 1}},
  {{11, 2}, {10, 2}, {9, 2}, {8, 2}, {7, 2}, {6, 2}, {5, 2}, {4, 2}, {3, 2}, {2, 2}, {1, 2}, {0, 2}},
  {{11, 3}, {10, 3}, {9, 3}, {8, 3}, {7, 3}, {6, 3}, {5, 3}, {4, 3}, {3, 3}, {2, 3}, {1, 3}, {0, 3}},
};




const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_QWERTY]=LAYOUT_ortho_4x12(
			TD(TD_RHAND_LAYER),		LGUI_T(KC_Q),		RALT_T(KC_W),		LT(_MOUSE,KC_E),		LT(_MOV2,KC_R),		KC_T,			KC_Y,			KC_U,				KC_I,					KC_O,			KC_P,						KC_BSPC,
			TD(TD_ESC),				LT(_MOV,KC_A),		LALT_T(KC_S),		LCTL_T(KC_D),			LSFT_T(KC_F),		KC_G,			KC_H,			RSFT_T(KC_J),		RCTL_T(KC_K),			RALT_T(KC_L),	LT(_FUNCTION_KEYS,KC_SCLN),	LT(_FUNCTION2_KEYS,KC_QUOT),
			OSM(MOD_LCTL),			LGUI_T(KC_Z),		KC_X,				TD(TD_CTL_MOV),			TD(TD_SFT_MOV),		KC_B,			KC_N,			KC_M,				KC_COMM,				KC_DOT,			RGUI_T(KC_SLSH),			QK_LEAD,
			OSM(MOD_LGUI),			OSM(MOD_LALT),		OSM(MOD_RALT),		TD(TD_SIFT_CAPSLOCK),	TD(TD_TAB),			SH_T(KC_SPACE),	SH_T(KC_SPACE),	LT(_RAISE,KC_ENT),	TD(TD_SIFT_CAPSLOCK),	TD(TD_PLAY),	TD(TD_VOLU),				TD(TD_VOLD)
	),
    
	[_RAISE]=LAYOUT_ortho_4x12(
		X(HAMMER_SICKLE),	X(SMAILING),	X(GRINNING),	X(BEAMING),		X(ROLLING),		KC_NO,			KC_NO,			KC_NO,	X(EYEBROW),		X(SAD),			X(ANGRY),		KC_NO,
		X(CHESS),			X(WINKING),		X(KISS),		X(HEARTS),		X(HEARTEYES),	KC_NO,			KC_NO,			KC_NO,	X(ASTONISHED),	X(HANDMOUTH),	X(PEEKINGEYE),	KC_NO,
		X(CUP),				X(SUNGLASES),	X(HALO),		X(ZANY),		X(SPLODING),	KC_NO,			KC_NO,			KC_NO,	X(OPENHANDS),	KC_NO,			KC_NO,			KC_NO,
		X(SALUTING),		X(THINKING),	X(SHUSHING),	X(YAWNING),		MO(_OTHERS),	SH_T(KC_SPACE),	SH_T(KC_SPACE),	KC_NO,	KC_NO,			KC_NO,			KC_NO,			KC_NO
	),
    
    [_LOWER]=LAYOUT_ortho_4x12(
			KC_DEL,     KC_NO,		LENS_CLOSE,		LENS_DOWN,		LENS_UP,            DM_PLY1,	RALT(KC_1),		 					KC_EXLM,		KC_AT,		    KC_HASH,	    	KC_DLR,			KC_PERC,
			KC_NO,		WINTAB,		ALTTAB,	    	C(G(KC_LEFT)),	C(G(KC_RIGHT)),		DM_PLY2,	KC_GRV,								KC_CIRC,		KC_AMPR,	    KC_ASTR,	        KC_LPRN,	    KC_RPRN,
			KC_NO,		KC_NO,		KC_NO,			G(S(KC_S)),		G(KC_V),		    KC_NO,		XP(ORDINAL_MALE,ORDINAL_FEMALE),	KC_MINS,		KC_EQL,		    KC_BSLS,		    KC_LCBR,		KC_RCBR,
			KC_NO,		KC_TRNS,	KC_TRNS,		KC_TRNS,		KC_TRNS,	        KC_NO,		KC_NO,		 						MO(_OTHERS),	RALT(KC_5),		KC_NO,				KC_LBRC,		KC_RBRC
	),
    
   	[_FUNCTION_KEYS]=LAYOUT_ortho_4x12(
			KC_PSCR,	KC_F1,		KC_F2,		KC_F3,		KC_F4,		KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,
			KC_SCRL,	KC_F5,		KC_F6,		KC_F7,		KC_F8,		KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,
			KC_PAUS,	KC_F9,		KC_F10,		KC_F11,		KC_F12,		KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,
			KC_NO,		KC_NO,		KC_NO,		KC_NO, 		KC_TRNS,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO
	),
		
	[_FUNCTION2_KEYS]=LAYOUT_ortho_4x12(
			KC_PSCR,	KC_F13,		KC_F14,		KC_F15,		KC_F16,		KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,
			KC_SCRL,	KC_F17,		KC_F18,		KC_F19,		KC_F20,		KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,
			KC_PAUS,	KC_F21,		KC_F22,		KC_F23,		KC_F24,		KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,
			KC_NO,		KC_NO,		KC_NO,		KC_NO, 		KC_TRNS,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO 
	),
	
	[_OTHERS]=LAYOUT_ortho_4x12(
			QK_BOOT,	KC_NO,		KC_NO,		KC_NO,		KC_NO,		DM_REC1,	KC_NO,	ONOFFBOT,	KC_NO,		KC_PWR,		KC_SLEP,	KC_WAKE,
			QK_RBT,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		DM_REC2,	KC_NO,	KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,
			QK_MAKE,	KC_NO,		KC_NO,		KC_BRID,	KC_BRIU,	DM_RSTP,	KC_NO,	DT_DOWN,	DT_PRNT,	DT_UP,		KC_NO,		KC_NO,
			KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_NO,		KC_NO,	KC_TRNS,	KC_NO,		KC_NO,		KC_NO,		KC_NO
	),

	[_MOV]=LAYOUT_ortho_4x12(
			KC_NO,			KC_NO,			KC_NO,			KC_NO,			KC_NO,		KC_NO,		KC_PAUS,	KC_HOME,	KC_INS,		KC_PGUP,		KC_NO,			KC_BSPC,
			KC_NO,			KC_TRNS,		KC_LALT,		KC_LCTL,		KC_LSFT,	KC_LGUI,	KC_LEFT,	KC_DOWN,	KC_UP,		KC_RGHT,		KC_NO,			KC_NO,
			KC_NO,			KC_NO,			KC_NO,			KC_TRNS,		KC_TRNS,	KC_NO,		KC_NO,		KC_END,		KC_DEL,		KC_PGDN,		KC_NO,			KC_NO,
			KC_NO,			KC_NO,			KC_NO,			KC_NO,			KC_TAB,		KC_SPACE,	KC_SPACE,	KC_ENT,		DEL_LINE,	DEL_LWORD,		DEL_END_LINE,	KC_NO
	),

	[_MOV2]=LAYOUT_ortho_4x12(
			KC_NO,			KC_NO,			KC_NO,			KC_NO,			KC_TRNS,	KC_NO,		KC_NO,		KC_NO,			KC_NO,		KC_NO,			KC_NO,	KC_NO,
			KC_NO,			KC_NO,			KC_NO,			KC_NO,			KC_NO,		KC_NO,		DEL_LWORD,	DEL_END_LINE,	DEL_LINE,	DEL_RWORD,		KC_NO,	KC_NO,
			KC_NO,			KC_NO,			KC_NO,			KC_NO,			KC_NO,		KC_NO,		KC_NO,		UP_NEW_LINE,	KC_NO,		KC_NO,			KC_NO,	KC_NO,
			KC_NO,			KC_NO,			KC_NO,			KC_NO,			KC_TAB,		KC_SPACE,	KC_SPACE,	DOWN_NEW_LINE,	KC_NO,		KC_NO,			KC_NO,	KC_NO
	),
	
	
	[_RNUM_PAD]=LAYOUT_ortho_4x12(
			KC_TRNS,						KC_PMNS,	KC_PAST,	KC_PSLS,	KC_NUM,		KC_ESC,				KC_ESC,			KC_P7,	KC_P8,	KC_P9,		KC_PPLS,	KC_BSPC,
			LM(_QWERTY2,MOD_LALT),			KC_NO,		KC_NO,		KC_NO,		KC_AT,		KC_TAB,				KC_TAB,			KC_P4,	KC_P5,	KC_P6,		KC_PPLS,	KC_DEL,
			LM(_QWERTY2,MOD_LCTL),			KC_NO,		KC_NO,		KC_NO,		KC_PERC,	KC_COMM,			KC_COMM,		KC_P1,	KC_P2,	KC_P3,		KC_PENT,	KC_PEQL,
			LM(_QWERTY2,MOD_LCTL|MOD_LALT),	KC_NO,		KC_NO,		KC_NO,		KC_ENT,		SH_T(KC_SPACE),		SH_T(KC_SPACE),	KC_P0,	KC_P0,	KC_PDOT,	KC_PENT,	KC_PEQL
	),

	[_NUM_PAD]=LAYOUT_ortho_4x12(
			KC_TRNS,						KC_DEL,	KC_7,		KC_8,	KC_9,		KC_ESC,		KC_ESC,		KC_7,	KC_8,	KC_9,	KC_DEL,	KC_BSPC,
			LM(_QWERTY2,MOD_LALT),			KC_NO,	KC_4,		KC_5,	KC_6,		KC_TAB,		KC_TAB,		KC_4,	KC_5,	KC_6,	KC_ENT,	KC_NO,
			LM(_QWERTY2,MOD_LCTL),			KC_ENT,	KC_1,		KC_2,	KC_3,		KC_COMM,	KC_COMM,	KC_1,	KC_2,	KC_3,	KC_ENT,	KC_NO,
			LM(_QWERTY2,MOD_LCTL|MOD_LALT),	KC_ENT,	KC_DOT,		KC_0,	KC_0,		KC_SPACE,	KC_SPACE,	KC_0,	KC_0,	KC_DOT,	KC_ENT,	KC_NO
	),

	[_MOUSE]=LAYOUT_ortho_4x12(
			KC_TRNS,	KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_MS_BTN1,		KC_MS_UP,	KC_MS_BTN2,		KC_MS_WH_UP,	KC_MS_ACCEL0,
			KC_TRNS,	KC_TRNS,	KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_MS_LEFT,		KC_MS_DOWN,	KC_MS_RIGHT,	KC_MS_WH_DOWN,	KC_MS_ACCEL1,
			KC_TRNS,	KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_MS_WH_LEFT,	KC_MS_BTN3,	KC_MS_WH_RIGHT,	KC_NO,			KC_MS_ACCEL2,
			KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,		KC_TRNS,	KC_TRNS,		KC_TRNS,		KC_TRNS
	),
	

	[_QWERTY2]=LAYOUT_ortho_4x12(
		KC_TRNS,	KC_Q,		KC_W,		KC_E,		KC_R,		KC_T,		KC_Y,		KC_U,		KC_I,		KC_O,		KC_P,			KC_BSPC,
		KC_TRNS,	KC_A,		KC_S,		KC_D,		KC_F,		KC_G,		KC_H,		KC_J,		KC_K,		KC_L,		KC_SCLN,		KC_QUOT,
		KC_TRNS,	KC_Z,		KC_X,		KC_C,		KC_V,		KC_B,		KC_N,		KC_M,		KC_COMM,	KC_DOT,		KC_SLSH,		QK_LEAD,
		KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TAB,		KC_SPACE,	KC_SPACE,	KC_ENT,		KC_TRNS,	KC_TRNS,	KC_TRNS,		KC_TRNS
	)
};




bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    
	switch (keycode) {

		case ALTTAB: 

			if (record->event.pressed){

				SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_TAB));
				alttab_token = true;
			}

			break;


		case WINTAB:

			if (record->event.pressed){

				SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_TAB));
				altwin_token = true;
			}

			break;

		case DEL_LWORD: 

			if (record->event.pressed){

				SEND_STRING(SS_DOWN(X_LSFT) SS_DOWN(X_LCTL) SS_TAP(X_LEFT) SS_UP(X_LCTL) SS_UP(X_LSFT) SS_TAP(X_DEL));
				
			}

			break;

		case DEL_RWORD: 

			if (record->event.pressed){

				SEND_STRING(SS_DOWN(X_LSFT) SS_DOWN(X_LCTL) SS_TAP(X_RIGHT) SS_UP(X_LCTL) SS_UP(X_LSFT) SS_TAP(X_DEL));
				
			}

			break;
			
		case DEL_LINE: 

			if (record->event.pressed){
				
				SEND_STRING(SS_DOWN(X_LSFT) SS_TAP(X_HOME) SS_UP(X_LSFT) SS_TAP(X_DEL));
				
			}

			break;

		case DEL_END_LINE:

			if (record->event.pressed){
				
				SEND_STRING(SS_DOWN(X_LSFT) SS_TAP(X_END) SS_UP(X_LSFT) SS_TAP(X_DEL));
				
			}

			break;
			
		case DOWN_NEW_LINE:

			if (record->event.pressed){

				SEND_STRING(SS_TAP(X_END) SS_TAP(X_ENTER));
				
			}

			break;
			
		
		case UP_NEW_LINE:

			if (record->event.pressed){

				SEND_STRING(SS_TAP(X_HOME) SS_TAP(X_ENTER) SS_TAP(X_UP));
				
			}

			break;
			
		case LENS_UP:
			
			if (record->event.pressed){

				SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_EQL) SS_UP(X_LGUI));
				
			}	

			break;
		
		case LENS_DOWN:
			
			if (record->event.pressed){

				SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_MINS) SS_UP(X_LGUI));
				
			}	

			break;


		case LENS_CLOSE:
			
			if (record->event.pressed){

				SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_ESC) SS_UP(X_LGUI));
				
			}	

			break;
							

		case ONOFFBOT:
			
			if (record->event.pressed){
			
				handleBoot();
			}
			break;


	}	

	return true;
  
};


void macrokeys_reset_tokens(void){

	if (layer_state_is(_QWERTY) && alttab_token) {
		
		SEND_STRING(SS_UP(X_LALT));
		alttab_token = false;
		
		} 

	if (layer_state_is(_QWERTY) && altwin_token) {
		
		SEND_STRING(SS_UP(X_LGUI));
		altwin_token = false;
		
		} 
}




// FUNCION TECLA LEADER

void leader_start_user(void) {
	
	layer_on(_QWERTY2);
}

void leader_end_user(void) {
		
		// ScreenShoot
		if (leader_sequence_one_key(KC_S)) {
			SEND_STRING(SS_LGUI(SS_LSFT(SS_TAP(X_S))));
		}
		
		// Terminal
		else if (leader_sequence_one_key(KC_T)) {
			SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_T))));
		}
		
		// Notepad
		else if (leader_sequence_one_key(KC_N)) {
			SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_N))));
		}
		
		// Explorador Archivos
		else if (leader_sequence_one_key(KC_E)) {
			SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_E))));
		}
		  
		// Chrome home page
		else if (leader_sequence_one_key(KC_H)) {
			SEND_STRING(SS_LALT(SS_TAP(X_HOME)));
			SEND_STRING(SS_LALT(SS_TAP(X_0)));
		}

		//windows calculator
		 else if (leader_sequence_one_key(KC_K)) {
			SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_C))));
		}
		
		// ctr + alt + spr 
		else if (leader_sequence_three_keys(KC_C, KC_A, KC_D)) {
			SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_DELETE))));
		}

		// ctr + alt + backspace 
		else if (leader_sequence_three_keys(KC_C, KC_A, KC_B) ){
			SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_BSPC))));
		}
		
		// Capslock
		else if (leader_sequence_three_keys(KC_C, KC_A, KC_P)) {
	  		tap_code(KC_CAPS);
		}

		// caps lock / num lock / scroll lock OFF
		else if (leader_sequence_three_keys(KC_O, KC_F, KC_F)) {
	  	
		  	if (host_keyboard_led_state().num_lock) {
				tap_code(KC_NUM);
		  	}
		  	
		  	if (host_keyboard_led_state().scroll_lock) {
				tap_code(KC_SCROLL_LOCK); 
			}
		  	
		  	if (host_keyboard_led_state().caps_lock) {
				tap_code(KC_CAPS_LOCK); 
			}   
		
		}
		
		// Close active windows
		else if (leader_sequence_three_keys(KC_C, KC_L, KC_S)) {
			SEND_STRING(SS_LALT(SS_TAP(X_F4)));
		}
	
		layer_clear();
}




// FUNCIONES TAP DANCE

// Define a type for as many tap dance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {

    bool is_press_action;
    td_state_t state;
    
} td_tap_t;

// Declare the functions to be used with your tap dance key(s)

// Function associated with all tap dances
td_state_t cur_dance(tap_dance_state_t *state);

// Functions associated with individual tap dances
void numpad_finished(tap_dance_state_t *state, void *user_data);
void numpad_reset(tap_dance_state_t *state, void *user_data);
void scape_finished(tap_dance_state_t *state, void *user_data);
void scape_reset(tap_dance_state_t *state, void *user_data);
void play_finished(tap_dance_state_t *state, void *user_data);
void capslock_finished(tap_dance_state_t *state, void *user_data);
void capslock_reset(tap_dance_state_t *state, void *user_data);
void dance_exclam_finished(tap_dance_state_t *state, void *user_data);
void dance_exclam_reset(tap_dance_state_t *state, void *user_data);
void vold_finished(tap_dance_state_t *state, void *user_data);
void vold_reset(tap_dance_state_t *state, void *user_data);
void volu_finished(tap_dance_state_t *state, void *user_data);
void volu_reset(tap_dance_state_t *state, void *user_data);
void lctl_finished(tap_dance_state_t *state, void *user_data);
void lctl_reset(tap_dance_state_t *state, void *user_data);
void functionkeys_finished(tap_dance_state_t *state, void *user_data);
void functionkeys_reset(tap_dance_state_t *state, void *user_data);
void tab_finished(tap_dance_state_t *state, void *user_data);
void tab_reset(tap_dance_state_t *state, void *user_data);
void sftmov_finished(tap_dance_state_t *state, void *user_data);
void sftmov_reset(tap_dance_state_t *state, void *user_data);
void ctlmov_finished(tap_dance_state_t *state, void *user_data);
void ctlmov_reset(tap_dance_state_t *state, void *user_data);



// Tap Dance DEFINICIONES
tap_dance_action_t tap_dance_actions[] = {

	[TD_SIFT_CAPSLOCK]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, capslock_finished, capslock_reset),
	[TD_RHAND_LAYER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, numpad_finished, numpad_reset),
	[TD_WIN_MENU]  = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, KC_APP),
	[TD_MNXT]  = ACTION_TAP_DANCE_DOUBLE(KC_MPLY, KC_MNXT),
	[TD_PLAY]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, play_finished, NULL),
	[TD_ESC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, scape_finished, scape_reset),	
	[TD_VOLD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, vold_finished, vold_reset),
	[TD_VOLU] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, volu_finished, volu_reset),
	[TD_TAB]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tab_finished, tab_reset),
	[TD_SFT_MOV]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sftmov_finished, sftmov_reset),
	[TD_CTL_MOV]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctlmov_finished, ctlmov_reset),
    
};







// Determine the current tap dance state
td_state_t cur_dance(tap_dance_state_t *state) {
    
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;	
    } 
    
    else if (state->count == 2) {
    	if (!state->pressed) return TD_DOUBLE_TAP;
    	else return TD_DOUBLE_HOLD;	
    } 
    
    else if (state->count == 3) {
    	if (!state->pressed) return TD_TRIPLE_TAP;
    	else return TD_TRIPLE_HOLD;	
    }
    
    else return TD_UNKNOWN;
    
}

// Initialize tap structure associated with example tap dance key
static td_tap_t numpad_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};




void numpad_finished(tap_dance_state_t *state, void *user_data) {
    
    numpad_tap_state.state = cur_dance(state);
    
    switch (numpad_tap_state.state) {
        
		case TD_SINGLE_TAP:
			
			if (layer_state_is(_QWERTY)) {
				layer_on(_NUM_PAD);
			}   
			
			else if (layer_state_is(_RNUM_PAD) || (layer_state_is(_NUM_PAD))){
				layer_clear();
			}    		
			
			break;

		
		case TD_SINGLE_HOLD:
			
			layer_on(_NUM_PAD);
			break;

			
		case TD_DOUBLE_TAP:
			
			if (layer_state_is(_RNUM_PAD)) { 
			
				layer_off(_RNUM_PAD);
			} 
			
			else {
			
				layer_on(_RNUM_PAD);
				
				if (!(host_keyboard_led_state().num_lock)) {
					tap_code(KC_NUM);
				}	
			}
			break;

		case TD_DOUBLE_HOLD:
			
			layer_on(_RNUM_PAD);
			
			if (!(host_keyboard_led_state().num_lock)) {
				tap_code(KC_NUM);
			}
			
			break;

		default:
			break;
		
    }
}


void numpad_reset(tap_dance_state_t *state, void *user_data) {

    if ((numpad_tap_state.state == TD_SINGLE_HOLD) || (numpad_tap_state.state == TD_DOUBLE_HOLD)) {
		
		layer_clear();
		
	}

    numpad_tap_state.state = TD_NONE;
}




void capslock_finished(tap_dance_state_t *state, void *user_data) {
    
    numpad_tap_state.state = cur_dance(state);
    
    switch (numpad_tap_state.state) {
        
        case TD_SINGLE_TAP:
        	
        	if (layer_state_is(_QWERTY)) {
				tap_code(KC_CAPS);
			}
			
            break;
        
        case TD_SINGLE_HOLD:
			
			SEND_STRING(SS_DOWN(X_LSFT));
			
            break;
        
        default:
            break;
    }
}


void capslock_reset(tap_dance_state_t *state, void *user_data) {

	SEND_STRING(SS_UP(X_LSFT));
    numpad_tap_state.state = TD_NONE;
    
}




void scape_finished(tap_dance_state_t *state, void *user_data) {
    
    numpad_tap_state.state = cur_dance(state);
    
	switch (numpad_tap_state.state) {
		
		case TD_SINGLE_TAP:
				
			tap_code(KC_ESC);


			if (host_keyboard_led_state().caps_lock) {
				
				tap_code(KC_CAPS);
			}

			break;

		case TD_SINGLE_HOLD:
			
			register_code16(KC_LCTL);
			
			break;

		case TD_DOUBLE_TAP:
			
			tap_code(KC_ESC);
			tap_code(KC_ESC);
			break;
				  
		case TD_DOUBLE_HOLD:
			
			register_code16(KC_ESC);
			
			break;

		default:
			break;
	}
}


void scape_reset(tap_dance_state_t *state, void *user_data) {
		
		unregister_code16(KC_LCTL);
		unregister_code16(KC_ESC);
		numpad_tap_state.state = TD_NONE;
		
}

void vold_finished(tap_dance_state_t *state, void *user_data) {
    
    numpad_tap_state.state = cur_dance(state);
    
    switch (numpad_tap_state.state) {
        
        case TD_SINGLE_TAP:
			
			register_code16(KC_VOLD);
            break;
        
        case TD_SINGLE_HOLD:
        	
        	tap_code(KC_MNXT);
            break;
        
        case TD_DOUBLE_HOLD:
        	
        	register_code16(KC_VOLD);
            break;
        
        case TD_DOUBLE_TAP:
    		
    		SEND_STRING(SS_TAP(X_VOLD) SS_TAP(X_VOLD));
        	break;            
        
        case TD_TRIPLE_TAP:
    		
    		SEND_STRING(SS_TAP(X_VOLD) SS_TAP(X_VOLD) SS_TAP(X_VOLD));
        	break;
        
        default:
        	break;
    }
}


void vold_reset(tap_dance_state_t *state, void *user_data) {
    
    if (state->count == 1) {
        
        unregister_code16(KC_VOLD);
    }
    
    numpad_tap_state.state = TD_NONE;
    
}





void volu_finished(tap_dance_state_t *state, void *user_data) {
    
    numpad_tap_state.state = cur_dance(state);
    
    switch (numpad_tap_state.state) {
        
        case TD_SINGLE_TAP:
			
			register_code16(KC_VOLU);
            break;
       
        case TD_SINGLE_HOLD:
        	
        	tap_code(KC_MPRV);
            break;
        
        case TD_DOUBLE_TAP:
    		
    		SEND_STRING(SS_TAP(X_VOLU) SS_TAP(X_VOLU));
        	break; 
        
        case TD_DOUBLE_HOLD:
        	
        	register_code16(KC_VOLU);
            break;           
        
        case TD_TRIPLE_TAP:
    		
    		SEND_STRING(SS_TAP(X_VOLU) SS_TAP(X_VOLU) SS_TAP(X_VOLU));
        	break;
        	
        default:
            break;
    }
}


void volu_reset(tap_dance_state_t *state, void *user_data) {

    unregister_code16(KC_VOLU);
    
    numpad_tap_state.state = TD_NONE;
    
}





void play_finished(tap_dance_state_t *state, void *user_data) {
    
    numpad_tap_state.state = cur_dance(state);
    
    switch (numpad_tap_state.state) {
        
        case TD_SINGLE_TAP:
			
			tap_code(KC_MPLY);
            break;
        
        case TD_DOUBLE_TAP:
        	
        	tap_code(KC_MUTE);
            break;
        
        default:
            break;
    }
    
}


void play_reset(tap_dance_state_t *state, void *user_data) {
	
	numpad_tap_state.state = TD_NONE;
	
}




void tab_finished(tap_dance_state_t *state, void *user_data) {
    
    numpad_tap_state.state = cur_dance(state);
    
    switch (numpad_tap_state.state) {
        
		case TD_SINGLE_TAP:
			
			tap_code(KC_TAB);   		
			
			break;

		
		case TD_SINGLE_HOLD:
			
			layer_on(_LOWER);
			break;

			
		case TD_DOUBLE_HOLD:
			
			layer_on(_FUNCTION_KEYS);
			
			break;

		case TD_TRIPLE_HOLD:
			
			layer_on(_FUNCTION2_KEYS);
			
			break;
			
		default:
			break;
		
    }
}


void tab_reset(tap_dance_state_t *state, void *user_data) {

	layer_clear();
    numpad_tap_state.state = TD_NONE;
    
}




void sftmov_finished(tap_dance_state_t *state, void *user_data) {
    
    numpad_tap_state.state = cur_dance(state);
    
    switch (numpad_tap_state.state) {
        
		case TD_SINGLE_TAP:
			
			tap_code(KC_V);  		
			break;

		
		case TD_SINGLE_HOLD:
			
			layer_on(_MOV);
			register_code16(KC_LSFT);
			
			break;

			
		case TD_DOUBLE_TAP:
			
			tap_code(KC_V);
			tap_code(KC_V);
			break;

		case TD_DOUBLE_HOLD:
			
			register_code16(KC_V);
			
			break;

		default:
			break;
		
    }
}


void sftmov_reset(tap_dance_state_t *state, void *user_data) {


	unregister_code16(KC_V);
	unregister_code16(KC_LSFT);
	layer_clear();
	
    numpad_tap_state.state = TD_NONE;
}



void ctlmov_finished(tap_dance_state_t *state, void *user_data) {
    
    numpad_tap_state.state = cur_dance(state);
    
    switch (numpad_tap_state.state) {
        
		case TD_SINGLE_TAP:
			
			tap_code(KC_C);  		
			break;

		
		case TD_SINGLE_HOLD:
			
			layer_on(_MOV);
			register_code16(KC_LCTL);
			break;

			
		case TD_DOUBLE_TAP:
			
			tap_code(KC_C);
			tap_code(KC_C);
			break;

		case TD_DOUBLE_HOLD:
			
			register_code16(KC_C);
			
			break;

		default:
			break;
		
    }
}


void ctlmov_reset(tap_dance_state_t *state, void *user_data) {

    if ((numpad_tap_state.state == TD_SINGLE_HOLD) || (numpad_tap_state.state == TD_DOUBLE_HOLD)) {
		
		unregister_code16(KC_C);
		unregister_code16(KC_LCTL);
		layer_clear();
		
		
	}

    numpad_tap_state.state = TD_NONE;
}



void running_boot(void){

	if (timer_elapsed32(key_timer_boot) > tiempo_boot) {
	
	key_timer_boot = timer_read32();
		if(is_boot_active){
		  //SEND_STRING(SS_TAP(X_F13));
		  // SEND_STRING(SS_TAP(X_WH_U)); //Rueda del ratón hacia arriba
		  // SEND_STRING(SS_TAP(X_WH_D)); //Rueda del ratón hacia abajo
		  SEND_STRING(SS_TAP(X_MS_U)); //Mueve el ratón hacia arriba
		  SEND_STRING(SS_TAP(X_MS_D)); //Mueve el ratón hacia abajo
		  SEND_STRING(SS_TAP(X_MS_R)); //Mueve el ratón hacia derecha
		  SEND_STRING(SS_TAP(X_MS_L)); //Mueve el ratón hacia izquierda
		  // SEND_STRING(SS_TAP(X_BTN1)); //Pulsa el botón 1 del ratón
		  // SEND_STRING(SS_TAP(X_BTN2)); //Pulsa el botón 2 del ratón
		  // SEND_STRING(SS_TAP(X_BTN3)); //Pulsa el botón 3 del ratón
		}
	} 
	
}	


void handleBoot(){
	
	is_boot_active = !is_boot_active;
	
	if(is_boot_active){
		
		tiempo_boot = 600000; //10 minutos
		SEND_STRING("Boot Actived\n");
	}
	else{


		tiempo_boot = 0;
		SEND_STRING("Boot Unactived\n");
	}  
}



void matrix_scan_user(void) {
  
	macrokeys_reset_tokens();
	running_boot();
		
}
