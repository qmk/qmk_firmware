#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    LAYOUT(
        TO(1), KC_A, KC_B, KC_C, KC_D, KC_E),

    LAYOUT(
        TO(2), KC_F, KC_G, KC_H, KC_I, KC_J),

    LAYOUT(
        TO(3), KC_K, KC_L, KC_M, KC_N, KC_O),

    LAYOUT(
        TO(4), KC_P, KC_Q, KC_R, KC_S, KC_T),

    LAYOUT(
        TO(5), KC_U, KC_V, KC_W, KC_X, KC_Y),

    LAYOUT(
        TO(0), KC_Z, KC_1, KC_2, KC_3, KC_4)};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    //keyevent_t event = record->event;

    switch (id)
    {
    case 0:
        if (record->event.pressed)
        {
            return MACRO(T(T), T(G), T(L), T(H), T(F), T(ENT), END);
        }
        break;
    case 1:
        if (record->event.pressed)
        {
            return MACRO(T(T), T(G), T(G), T(ENT), END);
        }
        break;
    case 2:
        if (record->event.pressed)
        {
            return MACRO(D(NO), T(L), U(NO), END);
        }
        break;
    case 3:
        if (record->event.pressed)
        {
            return MACRO(D(LCTL), T(Z), U(LCTL), END);
        }
        break;
    case 4:
        if (record->event.pressed)
        {
            return MACRO(D(LCTL), D(LSFT), T(Z), U(LSFT), U(LCTL), END);
        }
        break;
    case 5:
        if (record->event.pressed)
        {
            return MACRO(D(LCTL), T(X), U(LCTL), END);
        }
        break;
    case 6:
        if (record->event.pressed)
        {
            return MACRO(D(LCTL), T(C), U(LCTL), END);
        }
        break;
    case 7:
        if (record->event.pressed)
        {
            return MACRO(D(LCTL), T(V), U(LCTL), END);
        }
        break;
    }
    return MACRO_NONE;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    return true;
}
