

#ifdef COMBO_ENABLE

enum combo_events { RST, SEL_WORD, SEL_LINE, WINTGSYM, TGSYM, CTRLALTDEL, CTRLC, CTRLR, CUT, CPY, PST, CAL, DELWD, EML, PHONE, EMW, WINDELWD, COMBO_LENGTH };
uint16_t COMBO_LEN = COMBO_LENGTH;  // remove the COMBO_COUNT define and use this instead!

const uint16_t PROGMEM asdf_combo[]       = {KC_A, KC_S, KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM zxcv_combo[]       = {KC_Z, KC_X, KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM uiop_combo[]       = {KC_U, KC_I, KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM jklsemi_combo[]    = {KC_J, KC_K, KC_L, KC_SCLN, COMBO_END};
const uint16_t PROGMEM thumbs_combo[]     = {MO(4), LT(3, KC_ENT), COMBO_END};
const uint16_t PROGMEM win_thumbs_combo[] = {MO(5), LT(3, KC_ENT), COMBO_END};

const uint16_t PROGMEM zx_combo[] = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM xc_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM cv_combo[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM qr_combo[] = {KC_Q, KC_R, COMBO_END};
const uint16_t PROGMEM df_combo[] = {KC_D, KC_F, COMBO_END};
// const uint16_t PROGMEM qw_combo[] = {KC_Q, KC_W, COMBO_END};
// const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM gravminus_combo[] = {KC_GRV, KC_MINUS, COMBO_END};

const uint16_t PROGMEM xcv_combo[] = {KC_X, KC_C, KC_V, COMBO_END};

const uint16_t PROGMEM cal_combo[]   = {KC_C, KC_A, KC_L, COMBO_END};
const uint16_t PROGMEM phone_combo[] = {KC_P, KC_Q, COMBO_END};
const uint16_t PROGMEM eml_combo[]   = {KC_E, KC_M, KC_L, COMBO_END};
const uint16_t PROGMEM emw_combo[]   = {KC_E, KC_W, KC_M, COMBO_END};

combo_t key_combos[] = {

    // 2 key combos
    [CUT]      = COMBO_ACTION(zx_combo),
    [CPY]      = COMBO_ACTION(xc_combo),
    [PST]      = COMBO_ACTION(cv_combo),
    [CTRLR]    = COMBO_ACTION(qr_combo),
    [DELWD]    = COMBO_ACTION(df_combo),
    [TGSYM]    = COMBO_ACTION(thumbs_combo),
    [WINTGSYM] = COMBO_ACTION(win_thumbs_combo),
    [RST]      = COMBO_ACTION(gravminus_combo),

    // 3 key combos
    [SEL_WORD] = COMBO_ACTION(xcv_combo),

    // 4 key combos
    //     [CMD_ENTER]  = COMBO_ACTION(asdf_combo),
    [SEL_LINE]   = COMBO_ACTION(zxcv_combo),
    [CTRLALTDEL] = COMBO_ACTION(jklsemi_combo),

    // Misc
    [CAL]   = COMBO_ACTION(cal_combo),
    [EML]   = COMBO_ACTION(eml_combo),
    [PHONE] = COMBO_ACTION(phone_combo),
    [EMW]   = COMBO_ACTION(efmw_combo)};
/* COMBO_ACTION(x) is same as COMBO(x, KC_NO) */


#endif  // COMBO_ENABLE
