#include QMK_KEYBOARD_H

enum {
    LAYER_NORM_BASE,
    LAYER_NORM_EXTENTION,
    LAYER_RACE_BASE,
    LAYER_RACE_EXTENTION,
    LAYER_LEGACY_BASE,
    LAYER_LEGACY_EXTENTION,
    LAYER_CONTROL,
    LAYER_WINDOW,
    NUMBER_OR_LAYERS,
};

const bool temporary[NUMBER_OR_LAYERS] = {
    [LAYER_NORM_BASE] = false,
    [LAYER_NORM_EXTENTION] = true,
    [LAYER_RACE_BASE] = false,
    [LAYER_RACE_EXTENTION] = true,
    [LAYER_LEGACY_BASE] = false,
    [LAYER_LEGACY_EXTENTION] = true,
    [LAYER_CONTROL] = false,
    [LAYER_WINDOW] = true,
};

#define KEY_FORWARD(a) SAFE_RANGE+a

enum{
    DANCE_PGDN_BOTTOM,
    DANCE_PGUP_TOP,
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [DANCE_PGDN_BOTTOM] = ACTION_TAP_DANCE_DOUBLE(KC_PGDN, LGUI(KC_DOWN)),
    [DANCE_PGUP_TOP] = ACTION_TAP_DANCE_DOUBLE(KC_PGUP, LGUI(KC_UP)),
};

#define KEY_DANCE(a) TD(a)

enum custom_keycodes {
    KEY_BACK = SAFE_RANGE + NUMBER_OR_LAYERS,
    KEY_DELETE_WORD,
    KEY_DELETE_LINE,
    KEY_CUT_SELECTION,
    KEY_CREATE_LINE_BEFORE,
    KEY_CREATE_LINE_AFTER,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_NORM_BASE] = LAYOUT_default_splitspace(
        KC_GRAVE, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KEY_DANCE(DANCE_PGDN_BOTTOM), KEY_DANCE(DANCE_PGUP_TOP), KC_NO, KEY_DELETE_LINE, KEY_FORWARD(LAYER_RACE_BASE),
        KC_TAB, KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_LCBR, KC_RCBR, KC_BSLS, KEY_FORWARD(LAYER_LEGACY_BASE),
        KC_CAPS, KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E, KC_I, KC_O, KC_QUOT, KC_ENT, LCTL(KC_UP),
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_K, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_NO, LCTL(KC_LEFT),
        KC_LCTL, KC_LGUI, KC_LALT, KEY_FORWARD(LAYER_NORM_EXTENTION), KC_NO, KC_SPC, KC_RALT, KC_RGUI, KC_NO, KC_NO, LCTL(KC_RIGHT)),
    [LAYER_NORM_EXTENTION] = LAYOUT_default_splitspace(
        KC_NO, KC_NO, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_MPLY, KC_MUTE, KC_VOLD, KC_VOLU, KC_NO, LCTL(KC_C), KEY_FORWARD(LAYER_RACE_BASE),
        KC_NO, LGUI(KC_SPC), LCTL(KC_SPC), KC_ESC, KC_TILD, KC_EXLM, KC_PEQL, KC_PLUS, KC_MINUS, KC_PIPE, KC_COLN, KC_LCBR, KC_RCBR, KEY_CREATE_LINE_BEFORE, KEY_FORWARD(LAYER_LEGACY_BASE),
        KEY_DELETE_WORD, LALT(KC_LEFT), LALT(KC_RIGHT), KC_BSPC, LGUI(KC_LEFT), LGUI(KC_RIGHT), KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, LGUI(KC_V), KC_DQUO, KEY_CREATE_LINE_AFTER, LCTL(KC_UP),
        KC_LSFT, LGUI(KC_Z), KEY_CUT_SELECTION, KC_LPRN, KC_RPRN, KC_UNDS, KC_LBRC, KC_RBRC, KC_LT, KC_GT, KC_QUES, KC_RSFT, KC_NO, LCTL(KC_LEFT),
        KC_LCTL, KC_LGUI, KC_LALT, KC_NO, KC_NO, KC_SPC, KC_RALT, KC_RGUI, KC_NO, KC_NO, LCTL(KC_RIGHT)),
    [LAYER_RACE_BASE] = LAYOUT_default_splitspace(
        KC_NO, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_NO, KC_NO, KC_NO, KEY_DELETE_LINE, KEY_BACK,
        KC_NO, KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_LCBR, KC_RCBR, KC_BSLS, KC_NO,
        KC_CAPS, KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E, KC_I, KC_O, KC_QUOT, KC_ENT, KC_NO,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_K, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KEY_FORWARD(LAYER_RACE_EXTENTION), KC_NO, KC_SPC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),
    [LAYER_RACE_EXTENTION] = LAYOUT_default_splitspace(
        KC_NO, KC_NO, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KEY_DELETE_LINE, KEY_BACK,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_TILD, KC_EXLM, KC_PEQL, KC_PLUS, KC_MINUS, KC_PIPE, KC_COLN, KC_LCBR, KC_RCBR, KC_NO, KC_NO,
        KEY_DELETE_WORD, KC_NO, KC_NO, KC_BSPC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_DQUO, KC_ENT, KC_NO,
        KC_LSFT, LGUI(KC_Z), KEY_CUT_SELECTION, KC_LPRN, KC_RPRN, KC_UNDS, KC_LBRC, KC_RBRC, KC_LT, KC_GT, KC_QUES, KC_RSFT, KC_NO, KC_NO,
        KC_LCTL, KC_LGUI, KC_LALT, KC_NO, KC_NO, KC_SPC, KC_RALT, KC_RGUI, KC_NO, KC_NO, KC_NO),
    [LAYER_LEGACY_BASE] = LAYOUT_default_splitspace(
        KC_GRAVE, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KEY_DANCE(DANCE_PGDN_BOTTOM), KEY_DANCE(DANCE_PGUP_TOP), KC_NO, KEY_DELETE_LINE, KC_NO,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LCBR, KC_RCBR, KC_BSLS, KEY_BACK,
        KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, LCTL(KC_UP),
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_NO, LCTL(KC_LEFT),
        KC_LCTL, KC_LGUI, KC_LALT, KEY_FORWARD(LAYER_LEGACY_EXTENTION), KC_NO, KC_SPC, KC_RALT, KC_RGUI, KC_NO, KC_NO, LCTL(KC_RIGHT)),
    [LAYER_LEGACY_EXTENTION] = LAYOUT_default_splitspace(
        KC_NO, KC_NO, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_MPLY, KC_MUTE, KC_VOLD, KC_VOLU, KC_NO, LCTL(KC_C), KC_NO,
        KC_NO, LGUI(KC_SPC), LCTL(KC_SPC), KC_ESC, KC_TILD, KC_EXLM, KC_PEQL, KC_PLUS, KC_MINUS, KC_PIPE, KC_COLN, KC_LCBR, KC_RCBR, KEY_CREATE_LINE_BEFORE, KEY_BACK,
        KEY_DELETE_WORD, LALT(KC_LEFT), LALT(KC_RIGHT), KC_BSPC, LGUI(KC_LEFT), LGUI(KC_RIGHT), KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, LGUI(KC_V), KC_DQUO, KEY_CREATE_LINE_AFTER, LCTL(KC_UP),
        KC_LSFT, LGUI(KC_Z), KEY_CUT_SELECTION, KC_LPRN, KC_RPRN, KC_UNDS, KC_LBRC, KC_RBRC, KC_LT, KC_GT, KC_QUES, KC_RSFT, KC_NO, LCTL(KC_LEFT),
        KC_LCTL, KC_LGUI, KC_LALT, KC_NO, KC_NO, KC_SPC, KC_RALT, KC_RGUI, KC_NO, KC_NO, LCTL(KC_RIGHT)),
    [LAYER_CONTROL] = LAYOUT_default_splitspace(
        KC_GRAVE, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KEY_DANCE(DANCE_PGDN_BOTTOM), KEY_DANCE(DANCE_PGUP_TOP), KC_NO, KEY_DELETE_LINE, KEY_FORWARD(LAYER_RACE_BASE),
        KC_TAB, KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_LCBR, KC_RCBR, KC_BSLS, KEY_FORWARD(LAYER_LEGACY_BASE),
        KC_CAPS, KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E, KC_I, KC_O, KC_QUOT, KC_ENT, LCTL(KC_UP),
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_K, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_NO, LCTL(KC_LEFT),
        KC_LCTL, KC_LGUI, KC_LALT, KC_NO, KEY_BACK, KC_SPC, KC_RALT, KC_RGUI, KC_NO, KC_NO, LCTL(KC_RIGHT)),
    [LAYER_WINDOW] = LAYOUT_default_splitspace(
        KC_GRAVE, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KEY_DANCE(DANCE_PGDN_BOTTOM), KEY_DANCE(DANCE_PGUP_TOP), KC_NO, KEY_DELETE_LINE, KEY_FORWARD(LAYER_RACE_BASE),
        KC_TAB, KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_LCBR, KC_RCBR, KC_BSLS, KEY_FORWARD(LAYER_LEGACY_BASE),
        KC_CAPS, KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E, KC_I, KC_O, KC_QUOT, KC_ENT, LCTL(KC_UP),
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_K, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_NO, LCTL(KC_LEFT),
        KC_LCTL, KC_LGUI, KC_LALT, KC_NO, KEY_BACK, KC_SPC, KC_RALT, KC_RGUI, KC_NO, KC_NO, LCTL(KC_RIGHT)),
};

bool handle_common_key(uint16_t key, keyrecord_t *record){
    if(key == KEY_DELETE_WORD){
        if (record->event.pressed) {
            SEND_STRING(SS_LALT(SS_TAP(X_LEFT) SS_TAP(X_RIGHT)));
            register_code(KC_LSHIFT);
            SEND_STRING(SS_LALT(SS_TAP(X_LEFT)));
            unregister_code(KC_LSHIFT);
            SEND_STRING(SS_LGUI(SS_TAP(X_X)));
        }
        return false;
    }else if(key == KEY_DELETE_LINE){
        if (record->event.pressed) {
            register_code(KC_LSHIFT);
            SEND_STRING(SS_LGUI(SS_TAP(X_LEFT)));
            unregister_code(KC_LSHIFT);
            SEND_STRING(SS_LGUI(SS_TAP(X_X)));
        }
        return false;
    }else if(key == KEY_CREATE_LINE_BEFORE){
        if (record->event.pressed) {
            SEND_STRING(SS_LGUI(SS_TAP(X_LEFT)) SS_TAP(X_ENTER) SS_TAP(X_UP));
        }
        return false;
    }else if(key == KEY_CREATE_LINE_AFTER){
        if (record->event.pressed) {
            SEND_STRING(SS_LGUI(SS_TAP(X_RIGHT)) SS_TAP(X_ENTER));
        }
        return false;
    }else if(key == KEY_CUT_SELECTION){
        if (record->event.pressed) {
            if (get_mods() & MOD_MASK_SHIFT) {
                unregister_code(KC_LSHIFT);
                SEND_STRING(SS_LGUI(SS_TAP(X_X)));
                register_code(KC_LSHIFT);
            } else
                SEND_STRING(SS_LGUI(SS_TAP(X_X)));
        }
        return false;
    }else
        return true;
}

int layers[16];

void update_layer(void){
    layer_clear();
    layer_on(layers[layers[0] + 1]);
}

bool handle_call_key(uint16_t key, keyrecord_t* record) {
    if (key == KEY_BACK) {
        if (record->event.pressed) {
            if (layers[0]) {
                --layers[0];
                if (temporary[layers[layers[0] + 1]])
                    --layers[0];
                update_layer();
            }
        }
        return false;
    } else if (key >= SAFE_RANGE && key < SAFE_RANGE + NUMBER_OR_LAYERS) {
        int new_layer = key - SAFE_RANGE;
        if (record->event.pressed) {
            if (layers[layers[0] + 1] != new_layer) {
                if (temporary[layers[layers[0] + 1]])
                    layers[layers[0] + 1] = new_layer;
                else
                    layers[++layers[0] + 1] = new_layer;
                update_layer();
            }
        } else {
            if (layers[layers[0] + 1] == new_layer && temporary[layers[layers[0] + 1]]) {
                --layers[0];
                update_layer();
            }
        }
        return false;
    } else
        return true;
}

bool process_record_kb(uint16_t key, keyrecord_t *record) {
    if (layers[layers[0] + 1] == LAYER_NORM_BASE) {
    } else if (layers[layers[0] + 1] == LAYER_NORM_EXTENTION) {
    }
    if (!handle_call_key(key, record)) return false;
    return handle_common_key(key, record);
}

void keyboard_post_init_user() {
    rgblight_disable();
    rgb_matrix_disable();
}
