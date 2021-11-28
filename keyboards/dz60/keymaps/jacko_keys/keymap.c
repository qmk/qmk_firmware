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

/* UPDATE:
	New build process requires: qmk compile

THIS METHOD IS NOW DEFUNCT.
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
	TAB, CR, LBS,
	//Control iconographs
	IAT, IA, IB, IC, ID, IE, IF, IG, IH, II, IJ, IK,
	IL, IM, IN, IO, IP, IQ, IR, IS, IT, IU, IV, IW,
	IX, IY, IZ, ILBR, IBSL, IRBR, ICAR, IUND,
	//Alt aplha
	A1, A2, A3, A4, A5, A6, A7, A8, A9, A0, AMIN, AEQ,
	AGR, ACOM, ADOT, ALBR, ARBR, ASEM, AAPO,
	AA, AB, AC, AD, AE, AF, AG, AH, AI, AJ, AK,
	AL, AM, AN, AO, AP, AQ, AR, AS, AT, AU, AV, AW,
	AX, AY, AZ, ABSL,
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
	//ANSI Extended Shift
	//Special control (OSI and emojicons)
	[C1_L] = U'♥', [C1_U] = U'🕫', [C3_L] = U'👪', [C3_U] = U'🖃',
	[C4_L] = U'🏠', [C4_U] = U'🖅', [C5_L] = U'⛤', [C5_U] = U'🖆',
	[C7_L] = U'😈', [C7_U] = U'🗏', [C8_L] = U'📐', [C8_U] = U'🕮',
	[C9_L] = U'😇', [C9_U] = U'📚', [C0_L] = U'☠', [C0_U] = U'🏫',
	[CEQ_L] = U'⚖', [CEQ_U] = U'🖩', [CES_L] = U'🏃', [CES_U] = U'💁',
	//Control literals - (next commit rollback)
	[TAB] = U'⎘', [CR] = U'⎆', [LBS] = U'⛔',
	//Control iconographs (ANSI 32 lowest codes)
	[IAT] = U'⚠', [IA] = U'⟁', [IB] = U'🗚', [IC] = U'🗐',
	[ID] = U'🔖', [IE] = U'🔎', [IF] = U'👍', [IG] = U'🔔',
	[IH] = U'⌫', [II] = U'⭾', [IJ] = U'⏎', [IK] = U'⭿',
	[IL] = U'📇', [IM] = U'✓', [IN] = U'🗋', [IO] = U'🗁',
	[IP] = U'🐧', [IQ] = U'📤', [IR] = U'📥', [IS] = U'💾',
	[IT] = U'🌱', [IU] = U'👎', [IV] = U'📋', [IW] = U'🔑',
	[IX] = U'🗙', [IY] = U'🗜', [IZ] = U'⎌', [ILBR] = U'⎋',
	[IBSL] = U'🌍', [IRBR] = U'☣', [ICAR] = U'⌬', [IUND] = U'☢',
	//BQN Fn Shift
	//Unicode layer
	//============================================================================
	// FILL IN AS REQUIRED
	//============================================================================
	[A1] = U'𝟙', [A2] = U'𝟚', [A3] = U'𝟛', [A4] = U'𝟜',
	[A5] = U'𝟝', [A6] = U'𝟞', [A7] = U'𝟟', [A8] = U'𝟠',
	[A9] = U'𝟡', [A0] = U'𝟘', [AMIN] = 0x2224, [AEQ] = U'∣',//incongruence
	[ACOM] = U',', [ADOT] = U'.', [ALBR] = U'“',
	[ARBR] = U'”', [ASEM] = U';', [AAPO] = U'\'',
	[AA] = U'A', [AB] = U'Ạ', [AC] = U'Ṅ', [AD] = U'Ṫ',
	[AE] = U'E', [AF] = U'Ṡ', [AG] = U'Ẹ', [AH] = U'H',
	[AI] = U'I', [AJ] = U'Ṣ', [AK] = U'Ṇ', [AL] = U'Ȧ',
	[AM] = U'Ȯ', [AN] = U'N', [AO] = U'O', [AP] = U'Ṭ',
	[AQ] = U'Ọ', [AR] = U'Ė', [AS] = U'S', [AT] = U'T',
	[AU] = U'İ', [AV] = U'Ị', [AW] = U'Ḣ',
	[AX] = U'Ḥ', [AY] = U'˙', [AZ] = U'·',
	[ABSL] = U'\\'
	//4060 bytes free - as space is allocated "quite literally" as ASCII 32 in a 32-bit field.
	//2021-11-28
};

//Some say the above should be converted to allow more in device shift states,
//but that would be less compact (needing 4 NUL per key) so kind of works for free.

//The Navigation CYAN mode macro key system
//keycode name definitions

enum custom_keycodes {
    QMKLAST = SAFE_RANGE - 1,//ready for define
		KM_1,    KM_2,    KM_3,    KM_4,    KM_5,
		KM_6,    KM_7,    KM_8,    KM_9,    KM_0,
		KM_Q,    KM_W,    KM_E,    KM_R,    KM_T,
		KM_Y,    KM_U,    KM_I,    KM_O,    KM_P,
		KM_A,    KM_S,    KM_D,    KM_F,    KM_G,
		KM_H,    KM_J,    KM_K,    KM_L,
		KM_Z,    KM_X,    KM_C,    KM_V,
		KM_B,    KM_N,    KM_M,
};

//The Navigation CYAN mode macro key system for UTF-8 emission.
//fill in the four sections of each string KEEPING the NUL byte spacers.
//Backslash is reserved as an escape and so needs a "\\" literal.
//Unless the backslash is in the final print until string end.
//An estimate of 35 characters per key action set 2021-11-24
//A quirk in C does allow less space used by concatenation of This
//data structure if control key acceptably indexes the "next letter" OK.
const char* const PROGMEM macro_unicode[] = {
	//============================================================================
	// FILL IN AS REQUIRED
	//============================================================================
	// in (x, sx, cx, csx) modifier format with NUL terminal characters
	// can add (wx, wsx, wcx, wcsx) extra on end with \0 inbetween each
	// for more use of WIN modifier. ALT being used to hold layer.
	"ℤₚ\0F₄(q)\0\0",//		 KM_1
	"Aₙ\0G₂(p)\0\0",//    KM_2
	"Aₙ(q)\0²Aₙ(q²)\0\0",//    KM_3
	"Bₙ(q)\0²Dₙ(q²)\0\0",//    KM_4
	"Cₙ(q)\0²E₆(q²)\0\0",//    KM_5
	"Dₙ(q)\0³D₄(q³)\0\0",//		 KM_6
	"E₆(q)\0²B₂(2²ⁿ⁺¹)\0\0",//    KM_7
	"E₇(q)\0²F₄(2²ⁿ⁺¹)\0\0",//    KM_8
	"E₈(q)\0²G₂(3²ⁿ⁺¹)\0\0",//    KM_9
	"∅\0²F₄(2)′\0\0",//    KM_0
	"\0Fi₂₂\0\0",//		 KM_Q
	"\0J₄\0\0",//    KM_W
	"\0J₂\0\0",//    KM_E
	"\0HN\0\0",//    KM_R
	"\0Th\0\0",//    KM_T
	"\0B\0\0",//		 KM_Y
	"\0Fi₂₃\0\0",//    KM_U
	"\0M₂₄\0\0",//    KM_I
	"\0Co₃\0\0",//    KM_O
	"\0Co₂\0\0",//    KM_P
	"\0M₁₁\0\0",//		 KM_A
	"\0Ly\0\0",//    KM_S
	"\0M₂₂\0\0",//    KM_D
	"\0M₂₃\0\0",//    KM_F
	"\0HS\0\0",//    KM_G
	"\0J₃\0\0",//		 KM_H
	"\0McL\0\0",//    KM_J
	"\0He\0\0",//    KM_K
	"\0Ru\0\0",//    KM_L
	"\0M\0\0",//		 KM_Z
	"\0Fi₂₄\0\0",//    KM_X
	"\0J₁\0\0",//    KM_C
	"\0Co₁\0\0",//    KM_V
	"\0M₁₂\0\0",//		 KM_B
	"\0O'N\0\0",//    KM_N
	"\0Suz\0\0",//    KM_M
};

const uint16_t PROGMEM macro_keycode[] = {
	//index at A
	//only use alpha A-Z (26) escape sequences "\\A" etc. in macro strings
	KC_LEFT,//\\A
};

const char* const PROGMEM macro_subs[] = {
	//index at a
	//only use alpha a-z (26) escape sequences "\\a" etc. in macro strings
	"",//\\a
};

const char* modify_step(const char* ip) {
	while(*(ip++) != 0);
	return ip;
}

const char* modify_step2(const char* ip) {
	return modify_step(modify_step(ip));
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	if(keycode < KM_1 || keycode > KM_M) return true;//protection better
	if (record->event.pressed) {
		//press
		const char* ip = macro_unicode[keycode - KM_1];
		if(get_mods() & MOD_MASK_SHIFT) ip = modify_step(ip);
		if(get_mods() & MOD_MASK_CTRL) {//jump 2
			ip = modify_step2(ip);
		}
		if(get_mods() & MOD_MASK_GUI) {//jump 4 -- currently next macro key
			ip = modify_step2(modify_step2(ip));
		}
		while(*ip == '\\') {
			//process backslash macro effect, otherwise literal until end of string
			ip++;
			uint8_t idx = *ip - 'A';
			if(idx < 26) {//only use alphas
				tap_code16(macro_keycode[idx]);//16 for allow full moded codes
				ip++;
				continue;
			}
			idx = idx + 'A' - '0';//numbers
			if(idx < 10) {
				const char* ip_save = ip++;
				for(uint8_t i = 0; i < idx + 1; i++) {
					//so one step by default and numbers higher than 0 leave that may gaps in the skip.
					ip = modify_step(ip);//skip number of codes
				}
				send_unicode_string(ip);//should UTF-8
				ip = ip_save;//restore (only one level deep!!!!)
				continue;
			}
			idx = idx + '0' - 'a';//lower case subroutines
			if(idx < 26) {//only use alphas
				send_unicode_string(macro_subs[idx]);
				ip++;
				continue;
			}
			switch(*(ip++)) {
				//other cases of macro effects
				//======================================================================
				// FILL IN AS REQUIRED
				//======================================================================

			case('\\'):
				SEND_STRING("\\");//literal emit
				continue;
			default:
				break;//uknown escape
			}
			break;//bad escape sequence so ignore and literal
		}
		send_unicode_string(ip);//should UTF-8
	} else {
		//release
	}
  return true;
};

#define F_CTRL KC_OUT
#define F_SHFT KC_OPER
#define F_ALT KC_CLEAR_AGAIN
#define F_GUI KC_CRSEL
#define F_BOOM KC_EXSEL
//a great C4 joke about adding 32 to the modifiers

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//=========================================================
// PRIMARY UNSHIFTED MODES
//=========================================================

	//ANSI lock mode 0 =================================================================================== ANSI lock mode 0
	// Standard ANSI 60 layout for worldwide ASCII compatibility,
	// This is the standard conformance layer and as such remain static.
	// MO(4) enters the function shift state.
	LAYOUT_60_ansi(
		KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,           KC_BSPC,
		KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
		KC_CAPS,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
		KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,
		KC_LCTL, KC_LGUI,          KC_LALT,                   KC_SPC,                             KC_RALT, KC_RGUI,          KC_RCTL, MO(4)),//zero index start

	//Navigation lock mode 1 ======================================================================== Navigation lock mode 1
	// Removed ASCII 47 (/) and right ctrl/win/alt for cursor.
	// Backslash enters BQN entry mode
	// VirtualBox host key needs an Fn.
	// A basic easy cursor mode with easier BQN entry via \.
	LAYOUT_60_ansi(
		KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,           KC_BSPC,
		KC_TAB,           KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, OSL(3),//BQN shift
		KC_CAPS,          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
		KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,            KC_RSFT,
		KC_LCTL, KC_LGUI,          KC_LALT,                   KC_SPC,                             KC_LEFT, KC_DOWN,          KC_RIGHT,MO(5)),

	//Macro lock mode 3 ================================================================================== Macro lock mode 2
	// A single finger macro launching board producing many modifier and function keys.
	// Lots of macros and shifts with an Fn
	LAYOUT_60_ansi(
		OSM(MOD_LCTL|MOD_LSFT),    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,OSM(MOD_LSFT|MOD_LCTL|MOD_LALT),
		OSM(MOD_LSFT|MOD_LALT),    KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,  ALGR(KC_F24),
		OSM(MOD_LCTL|MOD_LALT),    ALGR(KC_F1),   ALGR(KC_F2),   ALGR(KC_F3),   ALGR(KC_F4),   ALGR(KC_F5),   ALGR(KC_F6),   ALGR(KC_F7),   ALGR(KC_F8),   ALGR(KC_F9),   ALGR(KC_F10),  ALGR(KC_F11),  ALGR(KC_F12),
		OSM(MOD_LSFT),         	   ALGR(KC_F13),  ALGR(KC_F14),  ALGR(KC_F15),  ALGR(KC_F16),  ALGR(KC_F17),  ALGR(KC_F18),  ALGR(KC_F19),  ALGR(KC_F20),  ALGR(KC_F21),  ALGR(KC_F22),  ALGR(KC_F23),
		OSM(MOD_LCTL),OSM(MOD_LGUI),OSM(MOD_LALT),            KC_SPC,                          LSA(KC_TAB),OSM(MOD_RGUI), LALT(KC_TAB),MO(6)),

	//BQN lock mode 4 ====================================================================================== BQN lock mode 3
	// BQN Unicode
	LAYOUT_60_ansi(
		Z(GR),   Z(N1),	  Z(N2),   Z(N3), 	Z(N4),	 Z(N5),	  Z(N6),   Z(N7),   Z(N8),   Z(N9),   Z(N0),   Z(MIN),  Z(EQ),          	TO(1),//escape
		KC_TAB,           Z(Q),    Z(W),    Z(E),    Z(R),    Z(T),    Z(Y),    Z(U),    Z(I),    Z(O),    Z(P), 		Z(LBR),  Z(RBR),  KC_BSLS,
		KC_CAPS,          Z(A),    Z(S),    Z(D),    Z(F),    Z(G),    Z(H),    Z(J),    Z(K),    Z(L),    Z(SEMI), Z(QUOT), KC_ENT,
		KC_LSFT,		      Z(Z),    Z(XX),   Z(C),    Z(V),    Z(B),    Z(N),    Z(M),    Z(LESS), Z(GRET), Z(DIV),           KC_RSFT,
		F_CTRL,  F_GUI,          	 F_ALT,                   	Z(SPC),                 		  	 		F_ALT,	 F_GUI,		         F_CTRL,	TO(7)),//shift sticky

//=========================================================
// SECONDARY Fn SHIFTED MODES
//=========================================================

	//ANSI shift mode 4 ================================================================================== ANSI shift mode 4
	// ISO characters such as £ and control of RGB/backlight and cursor.
	// Fn + P is power switch for shutdown.
	// This shift layer is standard for the kind of keyboard plus a few extensions.
	LAYOUT_60_ansi(
		KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_DEL,
		LCA(KC_DEL),      RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_WHOM, KC_PWR,  KC_HOME, KC_END,  KC_INS,
		KC_SLCK,          KC_WSCH, Z(INT),  Z(DIF),  KC_WFAV, Z(ROOT), KC_VOLD, KC_VOLU, Z(DEG),  Z(PND),  KC_PAUS, KC_PSCR, KC_APP,
		KC_TRNS,          Z(OM),   KC_MUTE, BL_DEC,  BL_TOGG, BL_INC,  BL_STEP, Z(MIC),  KC_PGUP, KC_PGDN, KC_UP,            KC_TRNS,
		MO(8),	 DF(2),            DF(1),                     KC_SPC,                             KC_LEFT, KC_DOWN,          KC_RIGHT,KC_TRNS),

	//Navigation shift mode 5 ====================================================================== Navigation shift mode 5
	// All function keys, so Home and End were sacrificed.
	// Also media player launch and control.
	// No APP menu as / is on the key, as / is ? key.
	LAYOUT_60_ansi(
		KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_DEL,
		LCA(KC_DEL),      KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,  KC_INS,
		KC_SLCK,          KC_WSCH, Z(INT),  Z(DIF),  KC_WFAV, Z(ROOT), KC_VOLD, KC_VOLU, Z(DEG),  Z(PND),  KC_PAUS, KC_PSCR, KC_APP,
		KC_TRNS,          Z(OM),   KC_MUTE, KC_MPRV, KC_MPLY, KC_MNXT, KC_MSEL, Z(MIC),  KC_PGUP, KC_PGDN, KC_QUES,          KC_TRNS,
		DF(0),   DF(2),            MO(9),		                  KC_SPC,                             KC_RALT, MT(MOD_RGUI,KC_SLSH),KC_RCTL, KC_TRNS),

	//Macro shift mode 6 ================================================================================ Macro shift mode 6
	// Same macro layer but different modifier grouping for more hot key combinations.
	LAYOUT_60_ansi(
		KC_ESC,  KC_P1,   KC_P2,   KC_P3,   KC_P4,   KC_P5,   KC_P6,   KC_P7,   KC_P8,   KC_P9,   KC_P0,   KC_HAEN, KC_HANJ,          KC_DEL,
		KC_TAB,           KC_RO,   KC_KANA, KC_JYEN, KC_HENK, KC_MHEN, KC_INT6, KC_INT7, KC_INT8, KC_INT9, KC_PWR,	KC_HOME, KC_END,  KC_INS,
		KC_NLCK,          KC_WSCH, Z(INT),  Z(DIF),  KC_WFAV, Z(ROOT), KC_VOLD, KC_VOLU, Z(DEG),  Z(PND),  KC_PAUS, KC_PSCR, KC_ENT,
		OSM(MOD_LGUI|MOD_RGUI),KC_LANG3,KC_LANG4,KC_LANG5,KC_LANG6,KC_LANG7,KC_LANG8,KC_LANG9,KC_ACL0, KC_ACL1, KC_ACL2,          OSM(MOD_RSFT),
		DF(0),OSM(MOD_LSFT|MOD_LGUI),DF(1),                   ALGR(KC_SPC),                       KC_TRNS, OSM(MOD_LSFT|MOD_RGUI),KC_TRNS, KC_TRNS),

	//BQN shift mode 7 ==================================================================================== BQN shift mode 7
	LAYOUT_60_ansi(
		KC_ESC,  X(A1),   X(A2),   X(A3),   X(A4),   X(A5),   X(A6),   X(A7),   X(A8),   X(A9),   X(A0),   X(AMIN), X(AEQ),	          KC_BSPC,//allow backspace
		KC_TAB,						X(AQ),   X(AW),   X(AE),   X(AR),   X(AT),   X(AY),   X(AU),   X(AI),   X(AO),   X(AP),   X(ALBR), X(ARBR), X(ABSL),
		KC_SLCK,  		  	X(AA),   X(AS),   X(AD),   X(AF),   X(AG),   X(AH),   X(AJ),   X(AK),   X(AL),   X(ASEM), X(AAPO), KC_ENT,
		F_SHFT,	          X(AZ),   X(AX),   X(AC),   X(AV),   X(AB),   X(AN),   X(AM),   X(ACOM), X(ADOT), KC_UP,				     F_SHFT,
		F_CTRL,  F_GUI,          	 F_ALT,		                  KC_SPC,                             KC_LEFT, KC_DOWN,          KC_RIGHT,TO(5)),//latching escape

//=========================================================
// EXTENDED Fn, MOD, Release Fn SHIFTED MODES
//=========================================================

	//Control shift mode 8 ============================================================================ Control shift mode 8
	LAYOUT_60_ansi(
		Z(CES),  Z(C1),   X(IAT),  Z(C3),   Z(C4),   Z(C5),   X(ICAR), Z(C7),   Z(C8),   Z(C9),   Z(C0),   X(IUND), Z(CEQ),           X(LBS),
		X(TAB),			  		X(IQ),   X(IW),   X(IE),   X(IR),   X(IT),   X(IY),   X(IU),   X(II),   X(IO),   X(IP),   X(ILBR), X(IRBR), X(IBSL),
		KC_TRNS,  		  	X(IA),   X(IS),   X(ID),   X(IF),   X(IG),   X(IH),   X(IJ),   X(IK),   X(IL),   LCTL(KC_PAUS),LCTL(KC_PSCR),X(CR),
		KC_LSFT,			    X(IZ),   X(IX),   X(IC),   X(IV),   X(IB),   X(IN),   X(IM),   LCTL(KC_PGUP),LCTL(KC_PGDN),LCTL(KC_UP),     KC_TRNS,
		KC_TRNS, LCTL(KC_LGUI),	   LCTL(KC_LALT),             X(IAT),                             LCTL(KC_LEFT), LCTL(KC_DOWN),LCTL(KC_RIGHT),KC_TRNS),

	//Mouse shift mode 9 ================================================================================ Mouse shift mode 9
	// A utility layer for things like the mouse.
	LAYOUT_60_ansi(
		RESET,	 KM_1,    KM_2,    KM_3,    KM_4,    KM_5,    KM_6,    KM_7,    KM_8,    KM_9,    KM_0,		 KC_BTN4, KC_BTN5,          KC_DEL,
		KC_TAB,           KM_Q,    KM_W,    KM_E,    KM_R,    KM_T,    KM_Y,    KM_U,    KM_I,    KM_O,    KM_P,	  KC_HOME, KC_END,	KC_SYSREQ,
		KC_LALT,		      KM_A,    KM_S,    KM_D,    KM_F,    KM_G,    KM_H,    KM_J,    KM_K,    KM_L,    KC_BTN3, KC_BTN2, KC_ENT,
		KC_LSFT,          KM_Z,    KM_X,    KM_C,    KM_V,    KM_B,    KM_N,    KM_M,	   KC_WH_U, KC_WH_D, KC_MS_U,          KC_RSFT,
		KC_LCTL, KC_LGUI, KC_TRNS,	                  				KC_BTN1,                            KC_MS_L, KC_MS_D,          KC_MS_R, KC_TRNS),

	//============================================================================
	// FILL IN AS REQUIRED (FOR EXTRA LAYAERS IF NEEDED)
	//============================================================================
};

const rgblight_segment_t PROGMEM my_ansi[] = RGBLIGHT_LAYER_SEGMENTS(
    {11, 2, HSV_RED}
);

const rgblight_segment_t PROGMEM my_nav[] = RGBLIGHT_LAYER_SEGMENTS(
    {11, 2, HSV_GREEN}
);

const rgblight_segment_t PROGMEM my_macro[] = RGBLIGHT_LAYER_SEGMENTS(
    {11, 2, HSV_YELLOW}
);

const rgblight_segment_t PROGMEM my_bqn[] = RGBLIGHT_LAYER_SEGMENTS(
    {11, 2, HSV_BLUE}
);

const rgblight_segment_t PROGMEM my_losh[] = RGBLIGHT_LAYER_SEGMENTS(
    {11, 2, HSV_MAGENTA}
);

const rgblight_segment_t PROGMEM my_hish[] = RGBLIGHT_LAYER_SEGMENTS(
    {11, 2, HSV_CYAN}
);

const rgblight_segment_t PROGMEM my_caps[] = RGBLIGHT_LAYER_SEGMENTS(
    {8, 1, HSV_WHITE}
);

const rgblight_segment_t PROGMEM my_num[] = RGBLIGHT_LAYER_SEGMENTS(
    {15, 1, HSV_WHITE}
);

//MAX 8 LAYERS ====== NO MORE SAPCE. USE A NO COLOR MODE
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
		my_ansi,
    my_nav,
    my_macro,
		my_bqn,// Extended mode
		my_losh,
		my_hish,
		my_caps,	// Overrides caps lock layer
		my_num
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  // Layers will light up if kb layers are active
	for(uint8_t i = 0; i < 4; i++)
		rgblight_set_layer_state(i, layer_state_cmp(state, i));//ANSI
	//rgblight_set_layer_state(2, layer_state_cmp(state, 1));//NAV
	//rgblight_set_layer_state(3, layer_state_cmp(state, 2));//Macro
	//rgblight_set_layer_state(4, layer_state_cmp(state, 3));//BQN
	rgblight_set_layer_state(4, layer_state_cmp(state, 4) || layer_state_cmp(state, 5) ||
 		layer_state_cmp(state, 6) || layer_state_cmp(state, 7));//LO Shift
	rgblight_set_layer_state(5, layer_state_cmp(state, 8) ||
		layer_state_cmp(state, 9));//HI Shift
  return state;
}

bool led_update_user(led_t led_state) {
	// Caps lock etc
  rgblight_set_layer_state(6, led_state.caps_lock);
	// MULTI LOCK WITH INVERTED NUMLOCK
	rgblight_set_layer_state(7, led_state.scroll_lock || !led_state.num_lock ||
		led_state.compose || led_state.kana);
  return true;
}
