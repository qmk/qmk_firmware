

#ifdef COMBO_ENABLE

enum combo_events { BKT, CBRC, PAREN, LTGT, CTRLALTDEL, CMD_ENTER, ENTER, TAB, SHIFT_TAB, CTRLC, CTRLR, CUT, CPY, PST, CAL, APW, DELWD, EML, PHONE, EMW, WINDELWD, CTILD, CTILD_SHIFT, COMBO_LENGTH };
uint16_t COMBO_LEN = COMBO_LENGTH;  // remove the COMBO_COUNT define and use this instead!

const uint16_t PROGMEM asdf_combo[] = {KC_A, KC_S, KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM zxcv_combo[] = {KC_Z, KC_X, KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM uiop_combo[]         = {KC_U, KC_I, KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM jklsemi_combo[]      = {KC_J, KC_K, KC_L, KC_SCLN, COMBO_END};

const uint16_t PROGMEM zx_combo[] = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM xc_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM cv_combo[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM qr_combo[] = {KC_Q, KC_R, COMBO_END};
const uint16_t PROGMEM df_combo[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM qw_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};

const uint16_t PROGMEM cal_combo[]   = {KC_C, KC_A, KC_L, COMBO_END};
const uint16_t PROGMEM phone_combo[] = {KC_P, KC_Q, COMBO_END};
const uint16_t PROGMEM eml_combo[]   = {KC_E, KC_M, KC_L, COMBO_END};
const uint16_t PROGMEM ema_combo[]   = {KC_E, KC_A, KC_M, COMBO_END};

combo_t key_combos[] = {

    // 2 key combos
    [CUT]         = COMBO_ACTION(cv_combo),
    [CPY]         = COMBO_ACTION(xc_combo),
    [PST]         = COMBO_ACTION(cv_combo),
    [CTRLR]       = COMBO_ACTION(qr_combo),
    [DELWD]       = COMBO_ACTION(df_combo),
    [CTILD]       = COMBO_ACTION(qw_combo),
    [CTILD_SHIFT] = COMBO_ACTION(jk_combo),

    // 4 key combos
    [CMD_ENTER]  = COMBO_ACTION(asdf_combo),
    [CTRLC]      = COMBO_ACTION(zxcv_combo),
    [CTRLALTDEL] = COMBO_ACTION(jklsemi_combo),
    [APW]        = COMBO_ACTION(uiop_combo),

    // Misc
    [CAL]   = COMBO_ACTION(cal_combo),
    [EML]   = COMBO_ACTION(eml_combo),
    [PHONE] = COMBO_ACTION(phone_combo),
    [EMW]   = COMBO_ACTION(ema_combo)};
/* COMBO_ACTION(x) is same as COMBO(x, KC_NO) */

void process_combo_event(uint16_t combo_index, bool pressed) {
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
        }
    } else {
        switch (combo_index) {
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
        }
    };
    switch (combo_index) {
        case CTILD:
            if (pressed) {
                tap_code16(C(KC_GRAVE));
            }
            break;

        case CTRLC:
            if (pressed) {
                tap_code16(C(KC_C));
            }
            break;
        case CTRLR:
            if (pressed) {
                tap_code16(C(KC_R));
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
        case EMW:
            if (pressed) {
                SEND_STRING("felix@truework.com");
            }
            break;
        case PHONE:
            if (pressed) {
                SEND_STRING("4158606970");
            }
            break;
        case CTRLALTDEL:
            if (pressed) {
                tap_code16(C(A(KC_DEL)));
            }
            break;
        case CMD_ENTER:
            if (pressed) {
                tap_code16(G(KC_ENT));
            }
            break;
    }
}

#endif  // COMBO_ENABLE
