/*
	Transform a BÉPO keyboard into a standart AZERTY keyboard based on a iso layoutPO
	
	Use only when you cannot install the native BÉPO driver
	as for instance if you are not allowed to install program / drivers on a business computer
	Your windows has to be set with a French AZERTY input method (laptop keyboard will stay in azerty for instance)
	
	NOTES:
	* All special code are specific to Windows (ALT+wincode input method)
	* Many dead letters are not implemented (lack of alt-code for that) - only the one available on an azerty (~, ^, ¨)
	* fine insecable input a "standard" insecable space, to adapt to Word corectly. Easy to adapt (ALT+8239 instead of AL+255)
	* Compile with the the option "LTO_ENABLE = yes" in your rules.mk, to reduce the size of the hex
	
	At any time, swith possible between bépo and AZERTY:
	* Shift + AltGr + "^ (azerty)/z (bépo)" key = AZERTY layout
	* Shift + AltGr + "$ (azerty)/w (bépo)" key = BÉPO emulation layout
	Last mode is not persistent on the Hasu converter (lack of persistent memory?). Default keyboard is bépo at power-on
	
*/
#include QMK_KEYBOARD_H
#include <keymap_french.h>

#define WINALT1(A) {SEND_STRING(SS_LALT(SS_TAP(X_KP_ ## A))); return false;}
#define WINALT2(A, B) {SEND_STRING(SS_LALT(SS_TAP(X_KP_ ## A) SS_TAP(X_KP_ ## B))); return false;}
#define WINALT3(A, B, C) {SEND_STRING(SS_LALT(SS_TAP(X_KP_ ## A) SS_TAP(X_KP_ ## B) SS_TAP(X_KP_ ## C))); return false;}
#define WINALT4(A, B, C,D) {SEND_STRING(SS_LALT(SS_TAP(X_KP_ ## A) SS_TAP(X_KP_ ## B) SS_TAP(X_KP_ ## C) SS_TAP(X_KP_ ## D))); return false;}

enum custom_keycodes {
	M1_3 = SAFE_RANGE,
	M2_20, 	M2_94, 	M2_96, 	M3_126,	M3_128,	M3_136,	M3_144,	M3_145,
	M3_146,	M3_158,	M3_167,	M3_168,	M3_169,	M3_170,	M3_171,	M3_172,
	M3_173,	M3_174,	M3_175,	M3_183,	M3_184,	M3_210,	M3_212,	M3_225,
	M3_235,	M3_239,	M3_241,	M3_243,	M3_246,	M3_250,	M3_255,	M4_0130,
	M4_0132,	M4_0133,	M4_0134,	M4_0135,	M4_0137,	M4_0140,
	M4_0145,	M4_0146,	M4_0147,	M4_0148,	M4_0150,	M4_0151,
	M4_0153,	M4_0156,	M4_8209,	M4_8239,	M4_8242,	M4_8243,
	M4_8722,	M4_8734,	M4_8800,	M4_8804,	M4_8805,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	if (record->event.pressed) {
		switch(keycode) {
			case M1_3: WINALT1(3); break;
			case M2_20: WINALT2(2,0); break;
			case M2_94: WINALT2(9,4); break;
			case M2_96: WINALT2(9,6); break;
			case M3_126: WINALT3(1,2,6); break;
			case M3_128: WINALT3(1,2,8); break;
			case M3_136: WINALT3(1,3,6); break;
			case M3_144: WINALT3(1,4,4); break;
			case M3_145: WINALT3(1,4,5); break;
			case M3_146: WINALT3(1,4,6); break;
			case M3_158: WINALT3(1,5,8); break;
			case M3_167: WINALT3(1,6,7); break;
			case M3_168: WINALT3(1,6,8); break;
			case M3_169: WINALT3(1,6,9); break;
			case M3_170: WINALT3(1,7,0); break;
			case M3_171: WINALT3(1,7,1); break;
			case M3_172: WINALT3(1,7,2); break;
			case M3_173: WINALT3(1,7,3); break;
			case M3_174: WINALT3(1,7,4); break;
			case M3_175: WINALT3(1,7,5); break;
			case M3_183: WINALT3(1,8,3); break;
			case M3_184: WINALT3(1,8,4); break;
			case M3_210: WINALT3(2,1,0); break;
			case M3_212: WINALT3(2,1,2); break;
			case M3_225: WINALT3(2,2,5); break;
			case M3_235: WINALT3(2,3,5); break;
			case M3_239: WINALT3(2,3,9); break;
			case M3_241: WINALT3(2,4,1); break;
			case M3_243: WINALT3(2,4,3); break;
			case M3_246: WINALT3(2,4,6); break;
			case M3_250: WINALT3(2,5,0); break;
			case M3_255: WINALT3(2,5,5); break;
			case M4_0130: WINALT4(0,1,3,0); break;
			case M4_0132: WINALT4(0,1,3,2); break;
			case M4_0133: WINALT4(0,1,3,3); break;
			case M4_0134: WINALT4(0,1,3,4); break;
			case M4_0135: WINALT4(0,1,3,5); break;
			case M4_0137: WINALT4(0,1,3,7); break;
			case M4_0140: WINALT4(0,1,4,0); break;
			case M4_0145: WINALT4(0,1,4,5); break;
			case M4_0146: WINALT4(0,1,4,6); break;
			case M4_0147: WINALT4(0,1,4,7); break;
			case M4_0148: WINALT4(0,1,4,8); break;
			case M4_0150: WINALT4(0,1,5,0); break;
			case M4_0151: WINALT4(0,1,5,1); break;
			case M4_0153: WINALT4(0,1,5,3); break;
			case M4_0156: WINALT4(0,1,5,6); break;
			case M4_8209: WINALT4(8,2,0,9); break;
			case M4_8239: WINALT4(8,2,3,9); break;
			case M4_8242: WINALT4(8,2,4,2); break;
			case M4_8243: WINALT4(8,2,4,3); break;
			case M4_8722: WINALT4(8,7,2,2); break;
			case M4_8734: WINALT4(8,7,3,4); break;
			case M4_8800: WINALT4(8,8,0,0); break;
			case M4_8804: WINALT4(8,8,0,4); break;
			case M4_8805: WINALT4(8,8,0,5); break;
			//switch to AZERTY Shift + AltGR + KC_LBRC = ^ key on an azerty // Z on bépo
			case KC_LBRC: 
				if (record->event.pressed && (keyboard_report->mods & MOD_BIT(KC_RSFT)) && (keyboard_report->mods & MOD_BIT(KC_RALT))) {
					//default_layer_set(0);
					set_single_persistent_default_layer(4);
					return true;
				} break;
				
			//SWITCH to BEPO Shift + AltGR + KC_RBRC = $ key on an azerty // W on bépo
			case KC_RBRC: 
				if (record->event.pressed && (keyboard_report->mods & MOD_BIT(KC_RSFT)) && (keyboard_report->mods & MOD_BIT(KC_RALT))) {
					set_single_persistent_default_layer(0);
					return true;
				} break;
		}
	}
	return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ $ │ " │ « │ » │ ( │ ) │ @ │ + │ - │ / │ * │ = │ % │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ b │ é │ p │ o │ è │ ^ │ v │ d │ l │ j │ z │ w │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ a │ u │ i │ e │ , │ c │ t │ s │ r │ n │ m │ ç │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ ê │ à │ y │ x │ . │ k │ ’ │ q │ g │ h │ f │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │                        │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
 
	[0] = LAYOUT_iso(
		KC_ESC,	KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,KC_F6,KC_F7,KC_F8,KC_F9,KC_F10,KC_F11,KC_F12,KC_PSCR,KC_SLCK,KC_BRK,
		FR_DLR,FR_DQUO,M3_174,M3_175,FR_LPRN,FR_RPRN,FR_AT,FR_PLUS,FR_MINS,FR_SLSH,FR_ASTR,FR_EQL,FR_PERC,KC_BSPC,KC_INS,KC_HOME,KC_PGUP,KC_NLCK,KC_PSLS,KC_PAST,KC_PMNS,
		KC_TAB,FR_B,FR_EACU,FR_P,FR_O,FR_EGRV,FR_CIRC,FR_V,FR_D,FR_L,FR_J,FR_Z,FR_W,KC_ENT,KC_DEL,KC_END,KC_PGDN,KC_P7,KC_P8,KC_P9,KC_PPLS,
		KC_LCTL,FR_A,FR_U,FR_I,FR_E,FR_COMM,FR_C,FR_T,FR_S,FR_R,FR_N,FR_M,FR_CCED,KC_P4,KC_P5,KC_P6,
		MO(1),M3_136,FR_AGRV,FR_Y,FR_X,FR_DOT,FR_K,M4_0146,FR_Q,FR_G,FR_H,FR_F,MO(1),KC_UP,KC_P1,KC_P2,KC_P3,KC_PENT,
		KC_LCTL,KC_LGUI,KC_LALT,KC_SPC,MO(2),KC_RGUI,KC_APP,KC_RCTL,KC_LEFT,KC_DOWN,KC_RGHT,KC_P0,KC_PDOT
	),
/*
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ # │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ ° │ ` │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ B │ É │ P │ O │ È │ ! │ V │ D │ L │ J │ Z │ W │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ A │ U │ I │ E │ ; │ C │ T │ S │ R │ N │ M │ Ç │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ Ê │ À │ Y │ X │ : │ K │ ? │ Q │ G │ H │ F │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │        insec           │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */
	[1] = LAYOUT_iso(
		S(KC_ESC),S(KC_F1),S(KC_F2),S(KC_F3),S(KC_F4),S(KC_F5),S(KC_F6),S(KC_F7),S(KC_F8),S(KC_F9),S(KC_F10),S(KC_F11),S(KC_F12),S(KC_PSCR),S(KC_SLCK),S(KC_BRK),
		FR_HASH,FR_1,FR_2,FR_3,FR_4,FR_5,FR_6,FR_7,FR_8,FR_9,FR_0,FR_DEG,M2_96,S(KC_BSPC),S(KC_INS),S(KC_HOME),S(KC_PGUP),S(KC_NLCK),S(KC_PSLS),S(KC_PAST),S(KC_PMNS),
		S(KC_TAB),S(FR_B),M3_144,S(FR_P),S(FR_O),M3_212,FR_EXLM,S(FR_V),S(FR_D),S(FR_L),S(FR_J),S(FR_Z),S(FR_W),S(KC_ENT),S(KC_DEL),S(KC_END),S(KC_PGDN),S(KC_P7),S(KC_P8),S(KC_P9),S(KC_PPLS),
		S(KC_LCTL),S(FR_A),S(FR_U),S(FR_I),S(FR_E),FR_SCLN,S(FR_C),S(FR_T),S(FR_S),S(FR_R),S(FR_N),S(FR_M),M3_128,S(KC_P4),S(KC_P5),S(KC_P6),
		KC_NO,M3_210,M3_183,S(FR_Y),S(FR_X),FR_COLN,S(FR_K),FR_QUES,S(FR_Q),S(FR_G),S(FR_H),S(FR_F),KC_NO,S(KC_UP),S(KC_P1),S(KC_P2),S(KC_P3),S(KC_PENT),
		S(KC_LCTL),S(KC_LGUI),S(KC_LALT),M3_255,MO(3),S(KC_RGUI),S(KC_APP),S(KC_RCTL),S(KC_LEFT),S(KC_DOWN),S(KC_RGHT),S(KC_P0),S(KC_PDOT)
	),

/*
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ – │ — │ < │ > │ [ │ ] │ ^ │ ± │ - │ ÷ │ × │ ` │ " │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ | │ ´ │ & │ œ │ ` │ ¡ │   │   │   │   │   │   │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ æ │ ù │ ¨ │ € │ ' │   │ e │ ß │   │ ~ │   │   │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ / │ \ │ { │ } │ … │ ~ │ ¿ │ º │ µ │   │   │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │           _            │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */	
	[2] = LAYOUT_iso(
		ALGR(KC_ESC),ALGR(KC_F1),ALGR(KC_F2),ALGR(KC_F3),ALGR(KC_F4),ALGR(KC_F5),ALGR(KC_F6),ALGR(KC_F7),ALGR(KC_F8),ALGR(KC_F9),ALGR(KC_F10),ALGR(KC_F11),ALGR(KC_F12),ALGR(KC_PSCR),ALGR(KC_SLCK),ALGR(KC_BRK),
		M4_0150,M4_0151,FR_LABK,FR_RABK,FR_LBRC,FR_RBRC,M2_94,M3_241,M4_8722,M3_246,M3_158,M4_8800,M4_0137,ALGR(KC_BSPC),ALGR(KC_INS),ALGR(KC_HOME),ALGR(KC_PGUP),ALGR(KC_NLCK),ALGR(KC_PSLS),ALGR(KC_PAST),ALGR(KC_PMNS),
		ALGR(KC_TAB),FR_PIPE,M3_239,FR_AMPR,M4_0156,FR_GRV,M3_173,KC_NO,M4_8734,KC_NO,KC_NO,KC_NO,KC_NO,ALGR(KC_ENT),ALGR(KC_DEL),ALGR(KC_END),ALGR(KC_PGDN),ALGR(KC_P7),ALGR(KC_P8),ALGR(KC_P9),ALGR(KC_PPLS),
		ALGR(KC_LCTL),M3_145,FR_UGRV,FR_DIAE,FR_EURO,FR_QUOT,KC_NO,FR_E,M3_225,KC_NO,FR_TILD,KC_NO,KC_NO,ALGR(KC_P4),ALGR(KC_P5),ALGR(KC_P6),
		MO(3),FR_SLSH,FR_BSLS,FR_LCBR,FR_RCBR,M4_0133,M3_126,M3_168,M3_167,FR_MICR,KC_NO,KC_NO,MO(3),ALGR(KC_UP),ALGR(KC_P1),ALGR(KC_P2),ALGR(KC_P3),ALGR(KC_PENT),
		ALGR(KC_LCTL),ALGR(KC_LGUI),ALGR(KC_LALT),FR_UNDS,KC_NO,ALGR(KC_RGUI),ALGR(KC_APP),ALGR(KC_RCTL),ALGR(KC_LEFT),ALGR(KC_DOWN),ALGR(KC_RGHT),ALGR(KC_P0),ALGR(KC_PDOT)
	),

/*
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
 * │ ¶ │ „ │ “ │ ” │   │   │   │ ¬ │ ¼ │ ½ │ ¾ │   │   │       │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │     │ _ │ ♥ │ § │ Œ │   │   │   │   │ £ │   │AZE│   │     │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    │
 * │      │ Æ │ Ù │   │ ¤ │   │ © │ ™ │   │ ® │   │   │   │    │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴────┤
 * │    │ ^ │ ‚ │ ‘ │ ’ │ · │   │   │ º │ † │ ‡ │   │          │
 * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤
 * │    │    │    │         insec          │    │    │    │    │
 * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 */	
	[3] = LAYOUT_iso(
		ALGR(S(KC_ESC)),ALGR(S(KC_F1)),ALGR(S(KC_F2)),ALGR(S(KC_F3)),ALGR(S(KC_F4)),ALGR(S(KC_F5)),ALGR(S(KC_F6)),ALGR(S(KC_F7)),ALGR(S(KC_F8)),ALGR(S(KC_F9)),ALGR(S(KC_F10)),ALGR(S(KC_F11)),ALGR(S(KC_F12)),ALGR(S(KC_PSCR)),ALGR(S(KC_SLCK)),ALGR(S(KC_BRK)),
		M2_20,M4_0132,M4_0147,M4_0148,M4_8804,M4_8805,KC_NO,M3_170,M3_172,M3_171,M3_243,M4_8242,M4_8243,ALGR(S(KC_BSPC)),ALGR(S(KC_INS)),ALGR(S(KC_HOME)),ALGR(S(KC_PGUP)),ALGR(S(KC_NLCK)),ALGR(S(KC_PSLS)),ALGR(S(KC_PAST)),ALGR(S(KC_PMNS)),
		ALGR(S(KC_TAB)),FR_UNDS,M1_3,FR_SECT,M4_0140,M2_96,KC_NO,KC_NO,KC_NO,FR_PND,KC_NO,/*azerty*/DF(4),KC_NO,ALGR(S(KC_ENT)),ALGR(S(KC_DEL)),ALGR(S(KC_END)),ALGR(S(KC_PGDN)),ALGR(S(KC_P7)),ALGR(S(KC_P8)),ALGR(S(KC_P9)),ALGR(S(KC_PPLS)),
		ALGR(S(KC_LCTL)),M3_146,M3_235,KC_NO,FR_CURR,KC_NO,M3_184,M4_0153,KC_NO,M3_169,KC_NO,KC_NO,KC_NO,ALGR(S(KC_P4)),ALGR(S(KC_P5)),ALGR(S(KC_P6)),
		KC_NO,M2_94,M4_0130,M4_0145,M4_0146,M3_250,M4_8209,KC_NO,KC_NO,M4_0134,M4_0135,/*DF(4)*/KC_NO,KC_NO,ALGR(S(KC_UP)),ALGR(S(KC_P1)),ALGR(S(KC_P2)),ALGR(S(KC_P3)),ALGR(S(KC_PENT)),
		ALGR(S(KC_LCTL)),ALGR(S(KC_LGUI)),ALGR(S(KC_LALT)),/*M4_8239*/M3_255,KC_NO,ALGR(S(KC_RGUI)),ALGR(S(KC_APP)),ALGR(S(KC_RCTL)),ALGR(S(KC_LEFT)),ALGR(S(KC_DOWN)),ALGR(S(KC_RGHT)),ALGR(S(KC_P0)),ALGR(S(KC_PDOT))
	),
	
	
	[4] = LAYOUT_iso(
		KC_ESC,KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,KC_F6,KC_F7,KC_F8,KC_F9,KC_F10,KC_F11,KC_F12,KC_PSCR,KC_SLCK,KC_BRK,
		KC_GRV,KC_1,KC_2,KC_3,KC_4,KC_5,KC_6,KC_7,KC_8,KC_9,KC_0,KC_MINS,KC_EQL,KC_BSPC,KC_INS,KC_HOME,KC_PGUP,KC_NLCK,KC_PSLS,KC_PAST,KC_PMNS,
		KC_TAB,KC_Q,KC_W,KC_E,KC_R,KC_T,KC_Y,KC_U,KC_I,KC_O,KC_P,KC_LBRC,KC_RBRC,KC_ENT,KC_DEL,KC_END,KC_PGDN,KC_P7,KC_P8,KC_P9,KC_PPLS,
		KC_LCTL,KC_A,KC_S,KC_D,KC_F,KC_G,KC_H,KC_J,KC_K,KC_L,KC_SCLN,KC_QUOT,KC_NUHS,KC_P4,KC_P5,KC_P6,
		KC_LSFT,KC_NUBS,KC_Z,KC_X,KC_C,KC_V,KC_B,KC_N,KC_M,KC_COMM,KC_DOT,KC_SLSH,KC_RSFT,KC_UP,KC_P1,KC_P2,KC_P3,KC_PENT,
		KC_LCTL,KC_LGUI,KC_LALT,KC_SPC,KC_RALT,KC_RGUI,KC_APP,KC_RCTL,KC_LEFT,KC_DOWN,KC_RGHT,KC_P0,KC_PDOT
	)
};
