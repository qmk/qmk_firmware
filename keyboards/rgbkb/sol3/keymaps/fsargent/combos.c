
enum combo_events { RST, TOGWIN, TOGGAME, MUTE, SEL_WORD, SEL_LINE, WINTGSYM, TGSYM, RBU, RBL, CTRLALTDEL, CTRLC, CTRLR, CUT, CPY, PST, CAL, DELWD, QIN, QNM, EML,WRK, QP, WINDELWD, THUMBS, OUTER_THUMB, JK, COMBO_LENGTH };
uint16_t COMBO_LEN		= COMBO_LENGTH;  // remove the COMBO_COUNT define and use this instead!

const uint16_t PROGMEM asdf_combo[]		= {KC_A, KC_S, KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM zxcv_combo[]		= {KC_Z, KC_X, KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM uiop_combo[]		= {KC_U, KC_I, KC_O, KC_P, COMBO_END};
// const uint16_t PROGMEM jklsemi_combo[]		= {KC_J, KC_K, KC_L, KC_SCLN, COMBO_END};
const uint16_t PROGMEM thumbs_combo[]		= {LTHUMB1, LTHUMB2, COMBO_END};
const uint16_t PROGMEM mute_combo[]		= {KC_VOLU,KC_VOLD, COMBO_END};

const uint16_t PROGMEM zx_combo[]		= {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM jk_combo[]		= {MT_J, MT_K, COMBO_END};
const uint16_t PROGMEM xc_combo[]		= {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM cv_combo[]		= {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM qr_combo[]		= {KC_Q, KC_R, COMBO_END};
const uint16_t PROGMEM df_combo[]		= {LGUI_T(KC_D),	LSFT_T(KC_F), COMBO_END};
const uint16_t PROGMEM gravminus_combo[]	= {KC_GRV, KC_MINS, COMBO_END};

const uint16_t PROGMEM xcv_combo[]		= {KC_X, KC_C, KC_V, COMBO_END};

const uint16_t PROGMEM cal_combo[]		= {KC_C, KC_A, MT(MOD_LALT, KC_L), COMBO_END};
const uint16_t PROGMEM phone_combo[]		= {KC_P, KC_Q, COMBO_END};
const uint16_t PROGMEM qnm_combo[]		= {KC_Q, KC_N, KC_M, COMBO_END};
const uint16_t PROGMEM qin_combo[]		= {KC_Q, KC_I, KC_N, COMBO_END};
const uint16_t PROGMEM eml_combo[]		= {KC_E, KC_M, MT(MOD_LALT, KC_L), COMBO_END};
const uint16_t PROGMEM wrk_combo[]		= {KC_W, KC_R, MT(MOD_LGUI, KC_K), COMBO_END};
const uint16_t PROGMEM rbu_combo[]		= {KC_R, KC_B, KC_U, COMBO_END};
const uint16_t PROGMEM rbl_combo[]		= {KC_R, KC_B, MT(MOD_LALT, KC_L), COMBO_END};

const uint16_t PROGMEM togwin_combo[]		= {KC_9, KC_2, COMBO_END};
const uint16_t PROGMEM toggame_combo[]		= {KC_0, KC_1, COMBO_END};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
	   case MT(MOD_LALT, KC_BSLS):
		  return TAPPING_TERM + 500;
	   default:
		  return TAPPING_TERM;
	}
}

combo_t key_combos[]	= {

	// 2 key combos
	[CUT]		= COMBO_ACTION(zx_combo),
	[CPY]		= COMBO_ACTION(xc_combo),
	[PST]		= COMBO_ACTION(cv_combo),
	[CTRLR]		= COMBO_ACTION(qr_combo),
	[DELWD]		= COMBO_ACTION(df_combo),
	[JK]		= COMBO_ACTION(jk_combo),
	// [TGSYM]		= COMBO_ACTION(thumbs_combo),
	// [WINTGSYM]		= COMBO_ACTION(win_thumbs_combo),
	[RST]		= COMBO_ACTION(gravminus_combo),
	[MUTE]		= COMBO_ACTION(mute_combo),

	[TOGGAME]	= COMBO_ACTION(toggame_combo),
	[TOGWIN]	= COMBO_ACTION(togwin_combo),

	// 3 key combos
	[SEL_WORD]	= COMBO_ACTION(xcv_combo),

	// 4 key combos
	//     [CMD_ENTER]		= COMBO_ACTION(asdf_combo),
	[SEL_LINE]	= COMBO_ACTION(zxcv_combo),
	// [CTRLALTDEL]	= COMBO_ACTION(jklsemi_combo),

	// Misc
	[CAL]		= COMBO_ACTION(cal_combo),
	[RBU]		= COMBO_ACTION(rbu_combo),
	[RBL]		= COMBO_ACTION(rbl_combo),
	[EML]		= COMBO_ACTION(eml_combo),
	[WRK]		= COMBO_ACTION(wrk_combo),
	[QP]		= COMBO_ACTION(phone_combo),
	[QIN]		= COMBO_ACTION(qin_combo),
	[QNM]		= COMBO_ACTION(qnm_combo),
	[THUMBS]	= COMBO_ACTION(thumbs_combo)};
/* COMBO_ACTION(x) is same as COMBO(x, KC_NO) */

void process_combo_event(uint16_t combo_index, bool pressed) {
	if (layer_state_is(0)) {
	   switch (combo_index) {
		case OUTER_THUMB:
			if (pressed) {
				tap_code(KC_ENT);
			}
		case DELWD:
			if (pressed) {
			tap_code16(A(KC_BSPC));
			}
			break;
		case CUT:
			if (pressed) {
			tap_code16(G(KC_X));
			}
			break;
		case CPY:
			if (pressed) {
			tap_code16(G(KC_C));
			}
			break;
		case PST:
			if (pressed) {
			tap_code16(G(KC_V));
			}
			break;
		case SEL_LINE:
			if (pressed) {
			SEND_STRING(SS_DOWN(X_LGUI) SS_TAP(X_LEFT) SS_DOWN(X_LSFT) SS_TAP(X_RIGHT) SS_UP(X_LSFT) SS_UP(X_LGUI));
			}
			break;
		case SEL_WORD:
			if (pressed) {
			SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_LEFT) SS_DOWN(X_LSFT) SS_TAP(X_RIGHT) SS_UP(X_LSFT) SS_UP(X_LALT));
			}
	   }
	}
	if (layer_state_is(1)) {
	   switch (combo_index) {
		case DELWD:
			if (pressed) {
				tap_code16(C(KC_BSPC));
			}
			break;
		case CUT:
			if (pressed) {
				tap_code16(C(KC_X));
				}
			break;
		case CPY:
			if (pressed) {
				tap_code16(C(KC_C));
			}
			break;
		case PST:
			if (pressed) {
				tap_code16(C(KC_V));
			}
			break;
			// case WINTGSYM:
			//  if (pressed) {
			//	layer_invert(_NUM);
			//  }
			//  break;
		case SEL_LINE:
			if (pressed) {
				SEND_STRING( SS_TAP(X_HOME) SS_DOWN(X_LSFT) SS_TAP(X_END) SS_UP(X_LSFT));
			}
			break;
		case SEL_WORD:
			if (pressed) {
				SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_LEFT) SS_DOWN(X_LSFT) SS_TAP(X_RIGHT) SS_UP(X_LSFT) SS_UP(X_LCTL));
			}
		}
	}
    switch (combo_index) {
	case JK:
		if (pressed) {
			tap_code(KC_ENT);
		}
		break;
	case THUMBS:
		if (pressed) {
			layer_on(_NUM);
		} else {
			layer_off(_NUM);
		}
		break;
	case MUTE:
		if (pressed) {
			tap_code(KC_MUTE);
		}
		break;
	// case TGSYM:
	//	if (pressed) {layer_invert(_NUM);}
	//	break;
	case RST:
		  if (pressed) {
		reset_keyboard();
		  }
		  break;
	case QNM:
		  if (pressed) {
			 SEND_STRING("Felix Sargent");
		  }
		  break;
	case QIN:
		if (pressed) {
			SEND_STRING("https://linkedin.com/in/felixsargent");
		}
		break;
	case CAL:
		  if (pressed) {
			 SEND_STRING("https://felixsargent.com/calendar");
		  }
		  break;
	case EML:
		if (pressed) {
			SEND_STRING("felix.sargent@gmail.com");
		}
	break;
	case WRK:
		if (pressed) {
			SEND_STRING("fsargent@recruitbot.com");
		}
		break;
	case RBU:
		if (pressed) {
			SEND_STRING("RecruitBot");
		}
		break;
	case RBL:
		if (pressed) {
			SEND_STRING("recruitbot");
		}
		break;
	case QP:
		if (pressed) {
			SEND_STRING("4158606970");
		}
		break;
	case CTRLALTDEL:
		if (pressed) {
			tap_code16(C(A(KC_DEL)));
		}
		break;
	}
}


