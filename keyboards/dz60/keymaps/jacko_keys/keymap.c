/* Copyright 2020 Simon Paul Jackson, BEng.
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

/*
make linux bootloader install via: (or use via if it's firmwared) => CHOICE
	cd qmk_firmware
	sudo make dz60:jacko_keys:dfu
	^C
	// or the following if you want to program upto 4 layers only yourself.
	sudo make dz60:via:dfu
*/

//Macro production rule for upper and lowers.
//Limit of only first 128 indirect entries may form part of a shifted pair.
//The **uint32_t** have all been allocated so no size change on edit code points.

//TODO:
//Optimize special shift mode characters.
//Maybe fiddle with LED colours on mode.
//Fill 4 extended user planes for 146 bytes left
//=> 36 extra unicode entries (10 of which can be shifty).
//=> indicators will cost bytes.

#define Z(x) XP(x##_L, x##_U)

enum unicode_names {
	//ANSI/NAV Fn shift (14)
	INT_L, INT_U,
	DIF_L, DIF_U,
	ROOT_L, ROOT_U,
	DEG_L, DEG_U,
	PND_L, PND_U,
	OM_L, OM_U,
	MIC_L, MIC_U,
	//BQN 1 (26 + 14 = 40)
	GR_L, GR_U,
	N1_L, N1_U,	N2_L, N2_U, N3_L, N3_U, N4_L, N4_U, N5_L, N5_U,
	N6_L, N6_U,	N7_L, N7_U, N8_L, N8_U, N9_L, N9_U, N0_L, N0_U,
	MIN_L, MIN_U, EQ_L, EQ_U,
	//BQN 2 (24 + 40 = 64)
	Q_L, Q_U, W_L, W_U, E_L, E_U, R_L, R_U, T_L, T_U, Y_L, Y_U,
	U_L, U_U, I_L, I_U, O_L, O_U, P_L, P_U, LBR_L, LBR_U, RBR_L, RBR_U,
	//BQN 3 (22 + 64 = 86)
	A_L, A_U, S_L, S_U, D_L, D_U, F_L, F_U, G_L, G_U, H_L, H_U,
	J_L, J_U, K_L, K_U, L_L, L_U, SEMI_L, SEMI_U, QUOT_L, QUOT_U,
	//BQN 4 (22 + 86 = 108) - X is special so XX was needed to avoid errors.
	Z_L, Z_U, XX_L, XX_U, C_L, C_U, V_L, V_U, B_L, B_U, N_L, N_U,
	M_L, M_U, LESS_L, LESS_U, GRET_L, GRET_U, DIV_L, DIV_U,
	SPC_L, SPC_U,
	//Special control
	C1_L, C1_U, C3_L, C3_U, C4_L, C4_U, C5_L, C5_U,
	C7_L, C7_U, C8_L, C8_U, C9_L, C9_U, C0_L, C0_U,
	CEQ_L, CEQ_U, CES_L, CES_U,
	//End of shiftables
	//Control literals
	TAB, LF, BS,
	//Control iconographs
	IAT, IA, IB, IC, ID, IE, IF, IG, IH, II, IJ, IK,
	IL, IM, IN, IO, IP, IQ, IR, IS, IT, IU, IV, IW,
	IX, IY, IZ, ILBR, IBSL, IRBR, ICAR, IUND,
	//Alt aplha
	AA, AB, AC, AD, AE, AF, AG, AH, AI, AJ, AK,
	AL, AM, AN, AO, AP, AQ, AR, AS, AT, AU, AV, AW,
	AX, AY, AZ,
};

// PLACE BQN layer and Unicode character code points here.
// _L is lower case
// _U is upper (shifted) case 
const uint32_t PROGMEM unicode_map[] = {
	//ANSI/NAV FN shift
	[INT_L] = U'∫',	[INT_U] = U'Σ',
	[DIF_L] = U'∂',	[DIF_U] = U'∇',
	[ROOT_L] = U'√', [ROOT_U] = U'∛',
	[DEG_L] = U'°', [DEG_U] = U'⦵',	//Plimsoil STP
	[PND_L] = U'£', [PND_U] = U'€',	
	[OM_L] = U'ω', [OM_U] = U'Ω',
	[MIC_L] = U'µ', [MIC_U] = U'ℎ',
	//BQN 1
	[GR_L] = U'˜', [GR_U] = U'¬',
	[N1_L] = U'˘', [N1_U] = U'⎉', [N2_L] = U'¨', [N2_U] = U'⚇',
	[N3_L] = U'⁼', [N3_U] = U'⍟', [N4_L] = U'⌜', [N4_U] = U'◶',
	[N5_L] = U'´', [N5_U] = U'⊘', [N6_L] = U'˝', [N6_U] = U'⎊',
	[N7_L] = U' ', [N7_U] = U' ', [N8_L] = U'∞', [N8_U] = U' ',
	[N9_L] = U'¯', [N9_U] = U'⟨', [N0_L] = U'•', [N0_U] = U'⟩',
	[MIN_L] = U'÷', [MIN_U] = U'√', [EQ_L] = U'×', [EQ_U] = U'⋆',
	//BQN 2
	[Q_L] = U'⌽', [Q_U] = U' ', [W_L] = U'𝕨', [W_U] = U'𝕎',
	[E_L] = U'∊', [E_U] = U'⍷', [R_L] = U'↑', [R_U] = U'𝕣',
	[T_L] = U'∧', [T_U] = U'⍋', [Y_L] = U' ', [Y_U] = U' ',
	[U_L] = U'⊔', [U_U] = U' ', [I_L] = U'⊏', [I_U] = U'⊑',
	[O_L] = U'⊐', [O_U] = U'⊒', [P_L] = U'π', [P_U] = U'⍳',
	[LBR_L] = U'←', [LBR_U] = U'⊣', [RBR_L] = U'→', [RBR_U] = U'⊢',
	//BQN 3
	[A_L] = U'⍉', [A_U] = U' ', [S_L] = U'𝕤', [S_U] = U'𝕊',
	[D_L] = U'↕', [D_U] = U' ', [F_L] = U'𝕗', [F_U] = U'𝔽',
	[G_L] = U'𝕘', [G_U] = U'𝔾', [H_L] = U'⊸', [H_U] = U'«',
	[J_L] = U'∘', [J_U] = U' ', [K_L] = U'○', [K_U] = U'⌾',
	[L_L] = U'⟜', [L_U] = U'»', [SEMI_L] = U'⋄', [SEMI_U] = U'·',
	[QUOT_L] = U'↩', [QUOT_U] = U'˙',
	//BQN 4
	[Z_L] = U'⥊', [Z_U] = U'⋈', [XX_L] = U'𝕩', [XX_U] = U'𝕏',
	[C_L] = U'↓', [C_U] = U' ', [V_L] = U'∨', [V_U] = U'⍒',
	[B_L] = U'⌊', [B_U] = U'⌈', [N_L] = U' ', [N_U] = U' ',
	[M_L] = U'≡', [M_U] = U'≢', [LESS_L] = U'∾', [LESS_U] = U'≤',
	[GRET_L] = U'≍', [GRET_U] = U'≥', [DIV_L] = U'≠', [DIV_U] = U'⇐',
	[SPC_L] = U'‿', [SPC_U] = U' ',
	//Special control
	[C1_L] = U' ', [C1_U] = U' ', [C3_L] = U' ', [C3_U] = U' ',
	[C4_L] = U' ', [C4_U] = U' ', [C5_L] = U' ', [C5_U] = U' ',
	[C7_L] = U' ', [C7_U] = U' ', [C8_L] = U' ', [C8_U] = U' ', 
	[C9_L] = U' ', [C9_U] = U' ', [C0_L] = U' ', [C0_U] = U' ',
	[CEQ_L] = U' ', [CEQ_U] = U' ', [CES_L] = U' ', [CES_U] = U' ',
	//Control literals
	[TAB] = U'␉', [LF] = U'␊', [BS] = U'␈',
	//Control iconographs
	[IAT] = U' ', [IA] = U' ', [IB] = U' ', [IC] = U' ',
	[ID] = U' ', [IE] = U' ', [IF] = U' ', [IG] = U' ',
	[IH] = U'⌫', [II] = U'⭾', [IJ] = U'⏎', [IK] = U'⭿',
	[IL] = U' ', [IM] = U' ', [IN] = U' ', [IO] = U' ',
	[IP] = U' ', [IQ] = U' ', [IR] = U' ', [IS] = U' ',
	[IT] = U' ', [IU] = U' ', [IV] = U' ', [IW] = U' ',
	[IX] = U'🗙', [IY] = U' ', [IZ] = U'⎌', [ILBR] = U'⎋',
	[IBSL] = U' ', [IRBR] = U' ', [ICAR] = U' ', [IUND] = U' ',
	//Alt aplha Unicode layer
	[AA] = U' ', [AB] = U' ', [AC] = U' ', [AD] = U' ',
	[AE] = U' ', [AF] = U' ', [AG] = U' ', [AH] = U' ',
	[AI] = U' ', [AJ] = U' ', [AK] = U' ', [AL] = U' ',
	[AM] = U' ', [AN] = U' ', [AO] = U' ', [AP] = U' ',
	[AQ] = U' ', [AR] = U' ', [AS] = U' ', [AT] = U' ',
	[AU] = U' ', [AV] = U' ', [AW] = U' ',
	[AX] = U' ', [AY] = U' ', [AZ] = U' '
	//ZERO BYTES FREE
	//FILL IN AS REQUIRED
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	//KEEP
	//ANSI lock mode 0 =================================================================================== ANSI lock mode 0
	// Standard ANSI 60 layout for worldwide ASCII compatibility,
	// This is the standard conformance layer and as such remain static.
	// MO(4) enters the function shift state.
	LAYOUT_60_ansi(
		KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,           KC_BSPC,
		KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
		KC_CAPS,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
		KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,
		KC_LCTL, KC_LGUI,          KC_LALT,                   KC_SPC,                             KC_RALT, KC_APP,           KC_RCTL, MO(4)),//zero index start

	//KEEP
	//Backslash enters BQN entry mode
	//Navigation lock mode 1 ============================================================================= Navigation lock mode 1
	// Removed ASCII 47 (/) and right ctrl/win/alt for cursor.
	// VirtualBox host key needs an Fn.
	// A basic easy cursor mode with easier BQN entry via \.
	LAYOUT_60_ansi(
		KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,           KC_BSPC,
		KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, OSL(2),//BQN shift
		KC_CAPS,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
		KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,            KC_RSFT,
		KC_LCTL, KC_LGUI,          KC_LALT,                   KC_SPC,                             KC_LEFT, KC_DOWN,          KC_RIGHT,MO(5)),

	//BQN Non FN Shift
	//KEEP
	//BQN lock mode 2 ================================================================================= BQN lock mode 2
	// BQN Unicode
	LAYOUT_60_ansi(
		Z(GR),   Z(N1),	  Z(N2),   Z(N3),	Z(N4),	 Z(N5),	  Z(N6),   Z(N7),   Z(N8),   Z(N9),   Z(N0),   Z(MIN),  Z(EQ),            KC_BSPC,
		KC_TAB,           Z(Q),    Z(W),    Z(E),    Z(R),    Z(T),    Z(Y),    Z(U),    Z(I),    Z(O),    Z(P), 	Z(LBR),  Z(RBR),  KC_BSLS,
		KC_CAPS,          Z(A),    Z(S),    Z(D),    Z(F),    Z(G),    Z(H),    Z(J),    Z(K),    Z(L),    Z(SEMI), Z(QUOT), KC_ENT,
		KC_LSFT,	      Z(Z),    Z(XX),   Z(C),    Z(V),    Z(B),    Z(N),    Z(M),    Z(LESS), Z(GRET), Z(DIV),           KC_RSFT,
		MO(9), 	 MO(11),           MO(10),                    Z(SPC),                 		  	  KC_LEFT, KC_RGUI,          KC_RIGHT,MO(2)),//shift

	//KEEP
	//Macro lock mode 3 ================================================================================== Macro lock mode 3
	// A single finger macro launching board producing many modifier and function keys.
	// Lots of macros and shifts with an Fn
	LAYOUT_60_ansi(
		OSM(MOD_LALT|MOD_LSFT),    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_BSPC,
		OSM(MOD_LCTL|MOD_LALT),    KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,  ALGR(KC_F24),
		OSM(MOD_LCTL|MOD_LSFT),    ALGR(KC_F1),   ALGR(KC_F2),   ALGR(KC_F3),   ALGR(KC_F4),   ALGR(KC_F5),   ALGR(KC_F6),   ALGR(KC_F7),   ALGR(KC_F8),   ALGR(KC_F9),   ALGR(KC_F10),  ALGR(KC_F11),  ALGR(KC_F12),
		OSM(MOD_LSFT),         	   ALGR(KC_F13),  ALGR(KC_F14),  ALGR(KC_F15),  ALGR(KC_F16),  ALGR(KC_F17),  ALGR(KC_F18),  ALGR(KC_F19),  ALGR(KC_F20),  ALGR(KC_F21),  ALGR(KC_F22),  ALGR(KC_F23),
		OSM(MOD_LCTL),OSM(MOD_LGUI),OSM(MOD_LALT),            KC_SPC,                          LSA(KC_TAB),OSM(MOD_RGUI), LALT(KC_TAB),  TG(6)),

	//KEEP
	//ANSI shift mode 4 ================================================================================== ANSI shift mode 4
	// ISO characters such as £ and control of RGB/backlight and cursor.
	// Fn + P is power switch for shutdown.
	// This shift layer is standard for the kind of keyboard.
	// MO(4) when released moves back to the regular ANSI layer.
	LAYOUT_60_ansi(
		KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_DEL,
		KC_TRNS,          RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_WHOM, KC_PWR,  KC_HOME, KC_END,  KC_INS,
		KC_SLCK,          KC_WSCH, Z(INT),  Z(DIF),  KC_WFAV, Z(ROOT), KC_VOLD, KC_VOLU, Z(DEG),  Z(PND),  KC_PAUS, KC_PSCR, KC_TRNS,
		KC_TRNS,          Z(OM),   KC_MUTE, BL_DEC,  BL_TOGG, BL_INC,  BL_STEP, Z(MIC),  KC_PGUP, KC_PGDN, KC_UP,            KC_TRNS,
		KC_LCTL, DF(3),            DF(1),                     KC_SPC,                             KC_LEFT, KC_DOWN,          KC_RIGHT, MO(4)),
	
	//KEEP
	//Navigation shift mode 5 ============================================================================ Navigation shift mode 5
	// All function keys, so Home and End were sacrificed.
	// Also media player launch and control.
	// No APP menu as / is on the key, as / is ? key.
	LAYOUT_60_ansi(
		KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_DEL,
		KC_TRNS,          KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,  KC_INS,
		KC_SLCK,          KC_WSCH, Z(INT),  Z(DIF),  KC_WFAV, Z(ROOT), KC_VOLD, KC_VOLU, Z(DEG),  Z(PND),  KC_PAUS, KC_PSCR, KC_ESC,
		KC_TRNS,          Z(OM),   KC_MUTE, KC_MPRV, KC_MPLY, KC_MNXT, KC_MSEL, Z(MIC),  KC_PGUP, KC_PGDN, KC_QUES,          KC_TRNS,
		DF(0),   DF(3),            KC_LALT,                   KC_SPC,                             KC_RALT, KC_SLSH,          KC_RCTL, MO(5)),

	//KEEP for extended macro layer.
	//Macro shift mode 6 ================================================================================= Macro shift mode 6
	// Same macro layer but different modifier grouping for more hot key combinations.
	LAYOUT_60_ansi(
		OSM(MOD_LGUI|MOD_LALT|MOD_LSFT),    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          OSM(MOD_LCTL|MOD_LALT|MOD_LSFT),
		OSM(MOD_LGUI|MOD_LCTL|MOD_LALT),    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		OSM(MOD_LGUI|MOD_LCTL|MOD_LSFT),    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		OSM(MOD_LGUI|MOD_LSFT),             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
		DF(0),   OSM(KC_LGUI),     DF(1),                     KC_SPC,                             TG(8),   OSM(KC_APP),TG(7),   TG(6)),

	//KEEP
	//Extended shift mode 7 ============================================================================== Extended shift mode 7
	// A utility layer for things like the mouse.
	LAYOUT_60_ansi(
		KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_LOCK, KC_PEQL,          KC_BSPC,
		KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_WH_U, KC_WH_D, RESET,
		KC_CAPS,	      KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_BTN4, KC_BTN3, KC_ENT,
		KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_PCMM, KC_BTN1, KC_MS_U,          KC_BTN2,
		KC_LCTL, KC_LGUI,          KC_LALT,                   KC_SPC,                             KC_MS_L, KC_MS_D,          KC_MS_R, TG(7)),
	
	//KEEP
	//Special shift mode 8 =============================================================================== Special shift mode 8
	// A utility layer for things not elsewhere, and slow language entry with 0 locking.
	LAYOUT_60_ansi(
		KC_ESC,  KC_P1,   KC_P2,   KC_P3,   KC_P4,   KC_P5,   KC_P6,   KC_P7,   KC_P8,   KC_P9,   KC_P0,   KC_LOCK, KC_HANJ,          KC_DEL,
		KC_TAB,           KC_RO,   KC_KANA, KC_JYEN, KC_HENK, KC_MHEN, KC_INT6, KC_INT7, KC_INT8, KC_INT9, KC_HAEN, KC_HOME, KC_END,  KC_INS,
		KC_SLCK,          KC_WSCH, Z(INT),  Z(DIF),  KC_WFAV, Z(ROOT), KC_VOLD, KC_VOLU, Z(DEG),  Z(PND),  KC_PAUS, KC_PSCR, KC_ENT,
		KC_LSFT,          KC_LANG3,KC_LANG4,KC_LANG5,KC_LANG6,KC_LANG7,KC_LANG8,KC_LANG9,KC_ACL0, KC_ACL1, KC_ACL2,          KC_RSFT,
		KC_LCTL, KC_LGUI,          KC_LALT,                   KC_SPC,                             KC_RALT, KC_APP,           KC_RCTL, TG(8)),

	//Control shift mode 9 =============================================================================== Control shift mode 9
	LAYOUT_60_ansi(
		Z(CES),  Z(C1),   X(IAT),  Z(C3),   Z(C4),   Z(C5),   X(ICAR), Z(C7),   Z(C8),   Z(C9),   Z(C0),   X(IUND), Z(CEQ),           X(BS),
		X(TAB),			  X(IQ),   X(IW),   X(IE),   X(IR),   X(IT),   X(IY),   X(IU),   X(II),   X(IO),   X(IP),   X(ILBR), X(IRBR), X(IBSL),
		KC_TRNS,  		  X(IA),   X(IS),   X(ID),   X(IF),   X(IG),   X(IH),   X(IJ),   X(IK),   X(IL),   KC_PAUS, KC_PSCR, X(LF),
		KC_TRNS,          X(IZ),   X(IX),   X(IC),   X(IV),   X(IB),   X(IN),   X(IM),   KC_PGUP, KC_PGDN, KC_UP,            KC_TRNS,
		MO(9),	 KC_TRNS,     	   KC_TRNS,                   KC_SPC,                             KC_LEFT, KC_DOWN,          KC_RIGHT, KC_TRNS),

	//Unicode shift mode 10 ============================================================================= Unicode shift mode 10
	LAYOUT_60_ansi(
		KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,	          KC_TRNS,
		KC_TRNS,		  X(AQ),   X(AW),   X(AE),   X(AR),   X(AT),   X(AY),   X(AU),   X(AI),   X(AO),   X(AP),   KC_HOME, KC_END,  KC_TRNS,
		KC_TRNS,  		  X(AA),   X(AS),   X(AD),   X(AF),   X(AG),   X(AH),   X(AJ),   X(AK),   X(AL),   KC_PAUS, KC_PSCR, KC_TRNS,
		KC_TRNS,          X(AZ),   X(AX),   X(AC),   X(AV),   X(AB),   X(AN),   X(AM),   KC_PGUP, KC_PGDN, KC_UP,            KC_TRNS,
		KC_TRNS, KC_TRNS,     	   MO(10),                    KC_SPC,                             KC_LEFT, KC_DOWN,          KC_RIGHT,KC_TRNS),

	//================================ USER PLANE (NOT YET USED) ==============================================================
	//=========================================================================================================================
	//HOT KEYS ONLY, NO EXTRA SPACE FOR EXTRA AS YET UNDEFINED CHARACTER GLYPHS.
	//Special shift mode 11 ============================================================================= Special shift mode 11
	LAYOUT_60_ansi(
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
		KC_TRNS,		  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS,  		  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
		KC_TRNS, MO(11),     	   KC_TRNS,                   KC_TRNS,                            KC_TRNS, KC_TRNS, 		 KC_TRNS, KC_TRNS)
};

const rgblight_segment_t PROGMEM my_caps[] = RGBLIGHT_LAYER_SEGMENTS(
    {8, 1, HSV_GOLD}
);

const rgblight_segment_t PROGMEM my_fn[] = RGBLIGHT_LAYER_SEGMENTS(
    {15, 1, HSV_PINK}
);

const rgblight_segment_t PROGMEM my_macro[] = RGBLIGHT_LAYER_SEGMENTS(
    {11, 1, HSV_CHARTREUSE}
);

const rgblight_segment_t PROGMEM my_nav[] = RGBLIGHT_LAYER_SEGMENTS(
    {12, 1, HSV_SPRINGGREEN}
);

const rgblight_segment_t PROGMEM my_bqn[] = RGBLIGHT_LAYER_SEGMENTS(
    {11, 2, HSV_BLUE}
);

const rgblight_segment_t PROGMEM my_scroll[] = RGBLIGHT_LAYER_SEGMENTS(
    {10, 1, HSV_PURPLE}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_caps,	// Overrides caps lock layer
	my_fn,		// Overides Fn shifted
    my_macro,    
    my_nav,
	my_bqn,// Extended mode
	my_scroll	// Scroll lock
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // Layers will light up if kb layers are active
	bool t;
	t = false;
	if(layer_state_cmp(state, 4) || layer_state_cmp(state, 7) ||
		layer_state_cmp(state, 8)) t = true;
	rgblight_set_layer_state(1, t);//shifted layer
	t = false;
	if(layer_state_cmp(state, 3) || layer_state_cmp(state, 6)) t = true;
	rgblight_set_layer_state(2, t);//macro
	t = false;
	if(layer_state_cmp(state, 1) || layer_state_cmp(state, 5)) t = true;
    rgblight_set_layer_state(3, t);//nav
	rgblight_set_layer_state(4, layer_state_cmp(state, 2));//BQN mode
    return state;
}

bool led_update_user(led_t led_state) {
	// Caps lock
    rgblight_set_layer_state(0, led_state.caps_lock);
	rgblight_set_layer_state(5, led_state.scroll_lock);
    return true;
}