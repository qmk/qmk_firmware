#include QMK_KEYBOARD_H

#define LAYOUT_split_spacebar( \
      K00,  K01,  K02,  K03,  K04,  K05,  K06,  K07,  K08,  K09,  K0A,  K0B,  K0C,  K0D, \
      K10,  K11,  K12,  K13,  K14,  K15,  K16,  K17,  K18,  K19,  K1A,  K1B,  K1C,  K1D,  \
      K20,  K21,  K22,  K23,  K24,  K25,  K26,  K27,  K28,  K29,  K2A,  K2B,  K2C,  K2D,  \
      K30,  K31,  K32,  K33,  K34,  K35,  K36,  K37,  K38,  K39,  K3A,  K3B,  K47,  K3D,  K3C,   \
      K40,  K41,  K42,        K46,  K45,  K44,                    K4A,  K4B,  K48,  K4C,  K4D  \
) { \
    { K00,  K01,  K02,  K03,  K04,  K05,  K06,  K07,  K08,  K09,  K0A,  K0B,  K0C,  K0D }, \
    { K10,  K11,  K12,  K13,  K14,  K15,  K16,  K17,  K18,  K19,  K1A,  K1B,  K1C,  K1D }, \
    { K20,  K21,  K22,  K23,  K24,  K25,  K26,  K27,  K28,  K29,  K2A,  K2B,  K2C,  K2D }, \
    { K30,  K31,  K32,  K33,  K34,  K35,  K36,  K37,  K38,  K39,  K3A,  K3B,  K3C,  K3D }, \
    { K40,  K41,  K42, KC_NO, K44,  K45,  K46,  K47,  K48, KC_NO, K4A,  K4B,  K4C,  K4D }  \
}

// LAYERS
#define L_BASE 0
#define L_GAMING 1
#define L_ARROWS_SYMBOLS 2
#define L_EXTRA 3
#define L_GAMING_FN 4

// TAP DANCES
enum {
    TD_RIGHT_GAMINGPROFILE,
    TD_ACCENTED_A,
    TD_ACCENTED_E,
    TD_ACCENTED_I,
    TD_ACCENTED_O,
    TD_ACCENTED_U,
    TD_LEFT_SHIFT_CAPS,
    TD_RIGHT_SHIFT_CAPS
};

// CUSTOM KEYCODES
#define KC_CSF5 LCTL(LSFT(KC_F5))       // Ctrl + Shift + F5
#define KC_CSF10 LCTL(LSFT(KC_F10))     // Ctrl + Shift + F10
#define KC_CSL LCTL(LSFT(KC_L))     // Ctrl + Shift + F10

#define KC_LDSK LCTL(LGUI(KC_LEFT))     // Move to left desktop
#define KC_RDSK LCTL(LGUI(KC_RIGHT))    // Move to right desktop

#define KC_AACC TD(TD_ACCENTED_A)
#define KC_EACC TD(TD_ACCENTED_E)
#define KC_IACC TD(TD_ACCENTED_I)
#define KC_OACC TD(TD_ACCENTED_O)
#define KC_UACC TD(TD_ACCENTED_U)
#define KC_LSCAP TD(TD_LEFT_SHIFT_CAPS)
#define KC_RSCAP TD(TD_RIGHT_SHIFT_CAPS)

#define KC_TGRT TD(TD_RIGHT_GAMINGPROFILE)



void accented_letter_a(qk_tap_dance_state_t *state, void *user_data){
    switch (state->count) {
        case 1:
            send_unicode_string("à");
            break;
        case 2:
            send_unicode_string("À");
            break;
        case 3:
            send_unicode_string("á");
            break;
        case 4:
            send_unicode_string("Á");
            break;
    }
}
void accented_letter_e(qk_tap_dance_state_t *state, void *user_data){
    switch (state->count) {
        case 1:
            send_unicode_string("è");
            break;
        case 2:
            send_unicode_string("È");
            break;
        case 3:
            send_unicode_string("é");
            break;
        case 4:
            send_unicode_string("É");
            break;
    }
}
void accented_letter_i(qk_tap_dance_state_t *state, void *user_data){
    switch (state->count) {
        case 1:
            send_unicode_string("ì");
            break;
        case 2:
            send_unicode_string("Ì");
            break;
        case 3:
            send_unicode_string("í");
            break;
        case 4:
            send_unicode_string("Í");
            break;
    }
}
void accented_letter_o(qk_tap_dance_state_t *state, void *user_data){
    switch (state->count) {
        case 1:
            send_unicode_string("ò");
            break;
        case 2:
            send_unicode_string("Ò");
            break;
        case 3:
            send_unicode_string("ó");
            break;
        case 4:
            send_unicode_string("Ó");
            break;
    }
}
void accented_letter_u(qk_tap_dance_state_t *state, void *user_data){
    switch (state->count) {
        case 1:
            send_unicode_string("ù");
            break;
        case 2:
            send_unicode_string("Ù");
            break;
        case 3:
            send_unicode_string("ú");
            break;
        case 4:
            send_unicode_string("Ú");
            break;
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Right Arrow, Tap twice to toggle the gaming layer
    [TD_RIGHT_GAMINGPROFILE] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_RGHT, L_GAMING),

    [TD_ACCENTED_A] = ACTION_TAP_DANCE_FN(accented_letter_a),
    [TD_ACCENTED_E] = ACTION_TAP_DANCE_FN(accented_letter_e),
    [TD_ACCENTED_I] = ACTION_TAP_DANCE_FN(accented_letter_i),
    [TD_ACCENTED_O] = ACTION_TAP_DANCE_FN(accented_letter_o),
    [TD_ACCENTED_U] = ACTION_TAP_DANCE_FN(accented_letter_u),

    // Double tap shift to get caps. Both sides
    [TD_LEFT_SHIFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
    [TD_RIGHT_SHIFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_RSFT, KC_CAPS)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // 0: Base Layer
    LAYOUT_split_spacebar(
        KC_ESC,   KC_1,     KC_2,      KC_3,  KC_4,  KC_5,  KC_6,  KC_7,  KC_8,  KC_9,     KC_0,     KC_NO,    KC_NO,   KC_BSPC,
        KC_TAB,   KC_Q,     KC_W,      KC_E,  KC_R,  KC_T,  KC_Y,  KC_U,  KC_I,  KC_O,     KC_P,     KC_NO,    KC_NO,   KC_BSLS,
        KC_CAPS,  KC_A,     KC_S,      KC_D,  KC_F,  KC_G,  KC_H,  KC_J,  KC_K,  KC_L,     KC_SCLN,  KC_QUOT,  KC_NO,   KC_ENT,
        KC_LSFT,  KC_NO,    KC_Z,      KC_X,  KC_C,  KC_V,  KC_B,  KC_N,  KC_M,  KC_COMM,  KC_DOT,   KC_SLSH,  KC_NO,   KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LGUI,  KC_LALT,       MO(L_ARROWS_SYMBOLS),   KC_SPC,      KC_RCTL,  MO(L_EXTRA),  KC_DEL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    // 1: Gaming layer
    LAYOUT_split_spacebar(
        KC_ESC,  KC_1,    KC_2,     KC_3,  KC_4, KC_5, KC_6, KC_7, KC_8, KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,     KC_E,  KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O,    KC_P,    KC_LBRC,  KC_RBRC, KC_BSLS,
        KC_CAPS, KC_A,    KC_S,     KC_D,  KC_F, KC_G, KC_H, KC_J, KC_K, KC_L,    KC_SCLN, KC_QUOT,  KC_NO,   KC_ENT,
        KC_LSFT, KC_NO,   KC_Z,     KC_X,  KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT,  KC_SLSH,  KC_NO,   KC_RSFT, KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,         KC_SPC,    MO(L_GAMING_FN),     KC_RCTL, KC_RALT,   KC_DEL,  KC_LEFT, KC_DOWN,  KC_TGRT),

    // 2: Function Layer
    LAYOUT_split_spacebar(
        KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_BSPC,
        KC_TAB, KC_RBRC, KC_RCBR, KC_LCBR, KC_LBRC, KC_F12, KC_NO, KC_HOME, KC_UP, KC_END, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_CAPS, KC_CSL, KC_NO, KC_EQL, KC_MINS, KC_PLUS, KC_UNDS, KC_LEFT, KC_DOWN, KC_RIGHT, KC_MINS, KC_EQL, KC_NO, KC_ENT,
        KC_LSFT, KC_NO, KC_F12, KC_LDSK, KC_RDSK, KC_TRNS, KC_TRNS, KC_NO, KC_DEL, KC_NO, KC_NO, KC_NO, KC_NO, KC_RSFT, KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,       KC_TRNS, KC_SPC,         KC_RCTL, KC_NO,  KC_DEL,  KC_LEFT, KC_DOWN, KC_TGRT),

    // 3: Extra functions layer and accented letters
    LAYOUT_split_spacebar(
        QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_EACC, KC_NO, KC_NO, KC_NO, KC_UACC, KC_IACC, KC_OACC, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_AACC, KC_MUTE, KC_VOLD, KC_VOLU, KC_NO, KC_NO, KC_NO, KC_NO, KC_MUTE, KC_VOLD, KC_VOLU, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO,       KC_NO, KC_NO,         KC_NO, KC_TRNS,  KC_NO,  KC_NO, KC_NO, KC_NO),


    // 4: Function Layer but for gaming mode (no brackets, equal, dash, etc.)
    LAYOUT_split_spacebar(
        KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,     KC_E,  KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O,    KC_P,    KC_LBRC,  KC_RBRC, KC_BSLS,
        KC_CAPS, KC_A,    KC_S,     KC_D,  KC_F, KC_G, KC_H, KC_J, KC_K, KC_L,    KC_SCLN, KC_QUOT,  KC_NO,   KC_ENT,
        KC_LSFT, KC_NO,   KC_Z,     KC_X,  KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT,  KC_SLSH,  KC_NO,   KC_RSFT, KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,       KC_TRNS, KC_SPC,         KC_RCTL, KC_NO,  KC_DEL,  KC_LEFT, KC_DOWN, KC_TGRT),

    // 5: Minecraft 
    LAYOUT_split_spacebar(
        KC_ESC,  KC_1,    KC_2,     KC_F3,  KC_4, KC_5, KC_6, KC_7, KC_8, KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,     KC_E,  KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O,    KC_P,    KC_LBRC,  KC_RBRC, KC_BSLS,
        KC_CAPS, KC_A,    KC_S,     KC_D,  KC_F, KC_G, KC_H, KC_J, KC_K, KC_L,    KC_SCLN, KC_QUOT,  KC_NO,   KC_ENT,
        KC_LSFT, KC_NO,   KC_Z,     KC_X,  KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT,  KC_SLSH,  KC_NO,   KC_RSFT, KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,         KC_SPC,    MO(L_GAMING_FN),     KC_RCTL, KC_RALT,   KC_DEL,  KC_LEFT, KC_DOWN,  KC_TGRT),

    
};
