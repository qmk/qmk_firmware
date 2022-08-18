#include QMK_KEYBOARD_H

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  RICK,
  ERDNUSSBUTTER,
  BRIEF,
  SATZ3
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case RICK:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING(SS_TAP(X_LGUI) SS_DELAY(500) "run" SS_DELAY(500) SS_TAP(X_ENT)SS_DELAY(500)"https://www.youtube.com/watch?v=dQw4w9WgXcQ"SS_TAP(X_ENT));
        } else {
            // when keycode QMKBEST is released
        }
        break;

    case ERDNUSSBUTTER:
    if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING(SS_TAP(X_LGUI) SS_DELAY(500) "run" SS_DELAY(500) SS_TAP(X_ENT)SS_DELAY(500)"https://youtu.be/2nH2HoVa6Jg"SS_TAP(X_ENT));
        } else {
            // when keycode QMKBEST is released
        }
        break;

    case BRIEF:
    if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING(SS_TAP(X_LGUI) SS_DELAY(500) "run" SS_DELAY(1000) SS_TAP(X_ENT)SS_DELAY(500)"notepad"SS_TAP(X_ENT)SS_DELAY(2000)"-. .- / -.. ..- / -... .- -. .- -. . --..-- / -... .. ... - / .--- . - --.. - / .--- .- / ... -.-. .... --- -. / ..--- ..--- / .--- .- .... .-. . / --. . .-. . .. ..-. - .-.-.- / -.. .- / -.- --- -- -- . -. / .--- .- / -... .- .-.. -.. / -.. .. . / -... .-. .- ..- -. . -. / ..-. .-.. . -.-. -.- . -. .-.-.- / .- -... . .-. / -.- . .. -. . / .- -. --. ... - --..-- / .--- . / .-.- .-.. - . .-. / -.. .. . / -... .- -. .- -. . --..-- / -.. . ... - --- / ... ..-- ... ... . .-. / ... -.-. .... -- . -.-. -.- - / ... .. . / ---... -.--.- / .-.-.- / .... --- ..-. ..-. . -. / .-- .. .-. / -- .- .-.. --..-- / -.. .- ... ... / -.. ..- / -. --- -.-. .... / .-.. .- -. --. . / ...- --- .-. / -.. .. -.-. .... / .... .. -. / --. .- -- -- . .-.. -. / -.- .- -. -. ... - / ..- -. -.. / -. .. . -- .- -. -.. / .- ..- ..-. / -.. .. .-. / .- ..- ... .-. ..- - ... -.-. .... - .-.-.- / ...- .. . .-.. . / ... --- -. -. . -. - .- --. . / .-- ..-- -. ... -.-. .... . -. / -- -.-. .-.. --- .-. .- / ..- -. -.. / ... .--. . -... -... --- .-.-.- / -... .. ... / -.. . -. -. . / .- -. - . -. -. . .-.-.-");
        } else {
            // when keycode QMKBEST is released
        }
        break;

    case SATZ3:
    if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING("Leertext");
        } else {
            // when keycode QMKBEST is released
        }
        break;
    }
    return true;
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        LT(1,KC_1), LT(2,KC_2),LT(3,KC_3), LT(4,KC_4),LT(5,KC_5), LT(6,KC_6),LT(7,KC_7), LT(8,KC_8)
    ),
   
    [1] = LAYOUT(
         KC_1, ERDNUSSBUTTER, BRIEF, RICK, KC_5, KC_6, KC_7, QK_BOOTLOADER
    ),
    [2] = LAYOUT(
         KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8
    ),
    [3] = LAYOUT(
         KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8
    ),
    [4] = LAYOUT(
         KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8
    ),
    [5] = LAYOUT(
         KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8
    ),
    [6] = LAYOUT(
         KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8
    ),
    [7] = LAYOUT(
         KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8
    ),
    [8] = LAYOUT(
         KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8
    ),
    
};





