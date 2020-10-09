#include QMK_KEYBOARD_H


enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT( \
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV, \
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS, \
  KC_LCTRL, KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT, \
                        KC_LALT, KC_LGUI, FN_MO13, KC_SPC, KC_ENT, FN_MO23, KC_BSPC, KC_RGUI \
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |   -  |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |   _  |   +  |   {  |   }  |   |  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_LOWER] = LAYOUT( \
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______,_______, _______, _______,\
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, \
  KC_GRV, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILD, \
  _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
                             _______, _______, _______, _______, _______,  _______, _______, _______\
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |-------.    ,-------|      | Left | Down |  Up  |Right |      |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |  F7  |  F8  |  F9  | F10  | F11  | F12  |-------|    |-------|   +  |   -  |   =  |   [  |   ]  |   \  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_RAISE] = LAYOUT( \
  _______, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______, \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, \
  KC_F1,  KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,                       XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, \
  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,   _______, _______,  KC_PLUS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
                             _______, _______, _______,  _______, _______,  _______, _______, _______ \
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |RGB ON| HUE+ | SAT+ | VAL+ |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      | MODE | HUE- | SAT- | VAL- |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_ADJUST] = LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
                             _______, _______, _______, _______, _______,  _______, _______, _______ \
  )
};
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

int keylogs_row;
int keylogs_col;
int keylogs_keycode;
int keylogs_name;
// int keylog_str[24] = [];
int *keylogs_str = {};
int keylogs_str_idx = 0;

// const char* location_to_string[10][6] PROGMEM = {
//     {"0x0\x0", "0x1\x0", "0x2\x0", "0x3\x0", "0x4\x0", "0x5\x0"},
//     {"1x0\x0", "1x1\x0", "1x2\x0", "1x3\x0", "1x4\x0", "1x5\x0"},
//     {"2x0\x0", "2x1\x0", "2x2\x0", "2x3\x0", "2x4\x0", "2x5\x0"},
//     {"3x0\x0", "3x1\x0", "3x2\x0", "3x3\x0", "3x4\x0", "3x5\x0"},
//     {"4x0\x0", "4x1\x0", "4x2\x0", "4x3\x0", "4x4\x0", "4x5\x0"},
//     {"5x0\x0", "5x1\x0", "5x2\x0", "5x3\x0", "5x4\x0", "5x5\x0"},
//     {"6x0\x0", "6x1\x0", "6x2\x0", "6x3\x0", "6x4\x0", "6x5\x0"},
//     {"7x0\x0", "7x1\x0", "7x2\x0", "7x3\x0", "7x4\x0", "7x5\x0"},
//     {"8x0\x0", "8x1\x0", "8x2\x0", "8x3\x0", "8x4\x0", "8x5\x0"},
//     {"9x0\x0", "9x1\x0", "9x2\x0", "9x3\x0", "9x4\x0", "9x5\x0"}};

// const char code_to_number[60][2] PROGMEM = {
//     "00", "01", "02", "03", "04", "05", "06", "07", "08", "09",
//     "10", "11", "12", "13", "14", "15", "16", "17", "18", "19",
//     "20", "21", "22", "23", "24", "25", "26", "27", "28", "29",
//     "30", "31", "32", "33", "34", "35", "36", "37", "38", "39",
//     "40", "41", "42", "43", "44", "45", "46", "47", "48", "49",
//     "50", "51", "52", "53", "54", "55", "56", "57", "58", "59"};

const char code_to_name[60] PROGMEM = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ';', '\'', ' ', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
//   //char name = ' ';
//   if (keycode < 60) {
//     keylogs_name = code_to_name[keycode];
//   }
  keylogs_row = record->event.key.row;
  keylogs_col = record->event.key.col;
  keylogs_keycode = keycode;

//   // update keylog
//   printf("%dx%d, k%2d : %c\n",
//            keylogs_row, keylogs_col,
//            keylogs_keycode, keylogs_name);

//   update keylogs
  if (keylogs_str_idx == 21 - 1) {
    keylogs_str_idx = 0;
    for (int i = 0; i < 21 - 1; i++) {
      keylogs_str[i] = 0;
    }
  }

  keylogs_str[keylogs_str_idx] = keylogs_keycode;
  keylogs_str_idx++;
}

// const char *read_keylog(void) {
//   return keylog_str;
// }

// const char *read_keylogs(void) {
//   return keylogs_str;
// }

void oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    switch (layer_state)
    {
    case 0:
        oled_write_ln_P(PSTR("Layer: Default"), false);
        break;
    case (1 << 2):
        oled_write_ln_P(PSTR("Layer: Raise"), false);
        break;
    case (1 << 1):
        oled_write_ln_P(PSTR("Layer: Lower"), false);
        break;
    case (1 << 3):
    case ((1 << 3) | (1 << 2) | (1 << 1)):
        oled_write_ln_P(PSTR("Layer: Adjust"), false);
        break;
    default:
        oled_write_ln_P(PSTR("Layer: Undefined"), false);
    }

    switch (keylogs_row)
    {
        case 0:
            oled_write_P(PSTR("0x"), false);
            break;
        case 1:
            oled_write_P(PSTR("1x"), false);
            break;
        case 2:
            oled_write_P(PSTR("2x"), false);
            break;
        case 3:
            oled_write_P(PSTR("3x"), false);
            break;
        case 4:
            oled_write_P(PSTR("4x"), false);
            break;
        case 5:
            oled_write_P(PSTR("5x"), false);
            break;
        case 6:
            oled_write_P(PSTR("6x"), false);
            break;
        case 7:
            oled_write_P(PSTR("7x"), false);
            break;
        case 8:
            oled_write_P(PSTR("8x"), false);
            break;
        case 9:
            oled_write_P(PSTR("9x"), false);
            break;
    }

    switch (keylogs_col)
    {
        case 0:
            oled_write_P(PSTR("0, k"), false);
            break;
        case 1:
            oled_write_P(PSTR("1, k"), false);
            break;
        case 2:
            oled_write_P(PSTR("2, k"), false);
            break;
        case 3:
            oled_write_P(PSTR("3, k"), false);
            break;
        case 4:
            oled_write_P(PSTR("4, k"), false);
            break;
        case 5:
            oled_write_P(PSTR("5, k"), false);
            break;
    }

    switch (keylogs_keycode)
    {
        case 0:
            oled_write_ln_P(PSTR("00 : "), false);
            break;
        case 1:
            oled_write_ln_P(PSTR("01 : "), false);
            break;
        case 2:
            oled_write_ln_P(PSTR("02 : "), false);
            break;
        case 3:
            oled_write_ln_P(PSTR("03 : "), false);
            break;
        case 4:
            oled_write_ln_P(PSTR("04 : a"), false);
            break;
        case 5:
            oled_write_ln_P(PSTR("05 : b"), false);
            break;
        case 6:
            oled_write_ln_P(PSTR("06 : c"), false);
            break;
        case 7:
            oled_write_ln_P(PSTR("07 : d"), false);
            break;
        case 8:
            oled_write_ln_P(PSTR("08 : e"), false);
            break;
        case 9:
            oled_write_ln_P(PSTR("09 : f"), false);
            break;
        case 10:
            oled_write_ln_P(PSTR("10 : g"), false);
            break;
        case 11:
            oled_write_ln_P(PSTR("11 : h"), false);
            break;
        case 12:
            oled_write_ln_P(PSTR("12 : i"), false);
            break;
        case 13:
            oled_write_ln_P(PSTR("13 : j"), false);
            break;
        case 14:
            oled_write_ln_P(PSTR("14 : k"), false);
            break;
        case 15:
            oled_write_ln_P(PSTR("15 : l"), false);
            break;
        case 16:
            oled_write_ln_P(PSTR("16 : m"), false);
            break;
        case 17:
            oled_write_ln_P(PSTR("17 : n"), false);
            break;
        case 18:
            oled_write_ln_P(PSTR("18 : o"), false);
            break;
        case 19:
            oled_write_ln_P(PSTR("19 : p"), false);
            break;
        case 20:
            oled_write_ln_P(PSTR("20 : q"), false);
            break;
        case 21:
            oled_write_ln_P(PSTR("21 : r"), false);
            break;
        case 22:
            oled_write_ln_P(PSTR("22 : s"), false);
            break;
        case 23:
            oled_write_ln_P(PSTR("23 : t"), false);
            break;
        case 24:
            oled_write_ln_P(PSTR("24 : u"), false);
            break;
        case 25:
            oled_write_ln_P(PSTR("25 : v"), false);
            break;
        case 26:
            oled_write_ln_P(PSTR("26 : w"), false);
            break;
        case 27:
            oled_write_ln_P(PSTR("27 : x"), false);
            break;
        case 28:
            oled_write_ln_P(PSTR("28 : y"), false);
            break;
        case 29:
            oled_write_ln_P(PSTR("29 : z"), false);
            break;
        case 30:
            oled_write_ln_P(PSTR("30 : 1"), false);
            break;
        case 31:
            oled_write_ln_P(PSTR("31 : 2"), false);
            break;
        case 32:
            oled_write_ln_P(PSTR("32 : 3"), false);
            break;
        case 33:
            oled_write_ln_P(PSTR("33 : 4"), false);
            break;
        case 34:
            oled_write_ln_P(PSTR("34 : 5"), false);
            break;
        case 35:
            oled_write_ln_P(PSTR("35 : 6"), false);
            break;
        case 36:
            oled_write_ln_P(PSTR("36 : 7"), false);
            break;
        case 37:
            oled_write_ln_P(PSTR("37 : 8"), false);
            break;
        case 38:
            oled_write_ln_P(PSTR("38 : 9"), false);
            break;
        case 39:
            oled_write_ln_P(PSTR("39 : 0"), false);
            break;
        case 40:
            oled_write_ln_P(PSTR("40 : R"), false);
            break;
        case 41:
            oled_write_ln_P(PSTR("41 : E"), false);
            break;
        case 42:
            oled_write_ln_P(PSTR("42 : B"), false);
            break;
        case 43:
            oled_write_ln_P(PSTR("43 : T"), false);
            break;
        case 44:
            oled_write_ln_P(PSTR("44 :  "), false);
            break;
        case 45:
            oled_write_ln_P(PSTR("45 :  "), false);
            break;
        case 46:
            oled_write_ln_P(PSTR("46 :  "), false);
            break;
        case 47:
            oled_write_ln_P(PSTR("47 :  "), false);
            break;
        case 48:
            oled_write_ln_P(PSTR("48 :  "), false);
            break;
        case 49:
            oled_write_ln_P(PSTR("49 :  "), false);
            break;
        case 50:
            oled_write_ln_P(PSTR("50 :  "), false);
            break;
        case 51:
            oled_write_ln_P(PSTR("51 : ;"), false);
            break;
        case 52:
            oled_write_ln_P(PSTR("52 : \\"), false);
            break;
        case 53:
            oled_write_ln_P(PSTR("53 :  "), false);
            break;
        case 54:
            oled_write_ln_P(PSTR("54 : ,"), false);
            break;
        case 55:
            oled_write_ln_P(PSTR("55 : ."), false);
            break;
        case 56:
            oled_write_ln_P(PSTR("56 : /"), false);
            break;
        case 57:
            oled_write_ln_P(PSTR("57 :  "), false);
            break;
        case 58:
            oled_write_ln_P(PSTR("58 :  "), false);
            break;
        case 59:
            oled_write_ln_P(PSTR("59 :  "), false);
            break;
    }

    for (int i = 0; i < 21 - 1; i++) {
        switch (keylogs_str[i])
        {
            case 0:
            case 1:
            case 2:
            case 3:
                oled_write_P(PSTR(" "), false);
                break;
            case 4:
                oled_write_P(PSTR("a"), false);
                break;
            case 5:
                oled_write_P(PSTR("b"), false);
                break;
            case 6:
                oled_write_P(PSTR("c"), false);
                break;
            case 7:
                oled_write_P(PSTR("d"), false);
                break;
            case 8:
                oled_write_P(PSTR("e"), false);
                break;
            case 9:
                oled_write_P(PSTR("f"), false);
                break;
            case 10:
                oled_write_P(PSTR("g"), false);
                break;
            case 11:
                oled_write_P(PSTR("h"), false);
                break;
            case 12:
                oled_write_P(PSTR("i"), false);
                break;
            case 13:
                oled_write_P(PSTR("j"), false);
                break;
            case 14:
                oled_write_P(PSTR("k"), false);
                break;
            case 15:
                oled_write_P(PSTR("l"), false);
                break;
            case 16:
                oled_write_P(PSTR("m"), false);
                break;
            case 17:
                oled_write_P(PSTR("n"), false);
                break;
            case 18:
                oled_write_P(PSTR("o"), false);
                break;
            case 19:
                oled_write_P(PSTR("p"), false);
                break;
            case 20:
                oled_write_P(PSTR("q"), false);
                break;
            case 21:
                oled_write_P(PSTR("r"), false);
                break;
            case 22:
                oled_write_P(PSTR("s"), false);
                break;
            case 23:
                oled_write_P(PSTR("t"), false);
                break;
            case 24:
                oled_write_P(PSTR("u"), false);
                break;
            case 25:
                oled_write_P(PSTR("v"), false);
                break;
            case 26:
                oled_write_P(PSTR("w"), false);
                break;
            case 27:
                oled_write_P(PSTR("x"), false);
                break;
            case 28:
                oled_write_P(PSTR("y"), false);
                break;
            case 29:
                oled_write_P(PSTR("z"), false);
                break;
            case 30:
                oled_write_P(PSTR("1"), false);
                break;
            case 31:
                oled_write_P(PSTR("2"), false);
                break;
            case 32:
                oled_write_P(PSTR("3"), false);
                break;
            case 33:
                oled_write_P(PSTR("4"), false);
                break;
            case 34:
                oled_write_P(PSTR("5"), false);
                break;
            case 35:
                oled_write_P(PSTR("6"), false);
                break;
            case 36:
                oled_write_P(PSTR("7"), false);
                break;
            case 37:
                oled_write_P(PSTR("8"), false);
                break;
            case 38:
                oled_write_P(PSTR("9"), false);
                break;
            case 39:
                oled_write_P(PSTR("0"), false);
                break;
            case 40:
                oled_write_P(PSTR("R"), false);
                break;
            case 41:
                oled_write_P(PSTR("E"), false);
                break;
            case 42:
                oled_write_P(PSTR("B"), false);
                break;
            case 43:
                oled_write_P(PSTR("T"), false);
                break;
            case 44:
            case 45:
            case 46:
            case 47:
            case 48:
            case 49:
            case 50:
                oled_write_P(PSTR(" "), false);
                break;
            case 51:
                oled_write_P(PSTR(";"), false);
                break;
            case 52:
                oled_write_P(PSTR("\\"), false);
                break;
            case 53:
                oled_write_P(PSTR(" "), false);
                break;
            case 54:
                oled_write_P(PSTR(","), false);
                break;
            case 55:
                oled_write_P(PSTR("."), false);
                break;
            case 56:
                oled_write_P(PSTR("/"), false);
                break;
            case 57:
            case 58:
            case 59:
                oled_write_P(PSTR(" "), false);
                break;
        }
    }

                oled_write_ln_P(PSTR(" "), false);



       // oled_write_P(&location_to_string[keylogs_row][keylogs_col], false);
    // oled_write_P(PSTR(", k"), false);
    // oled_write_P((char *)pgm_read_word(&(code_to_number[keylogs_keycode])), false);
    // oled_write_P(PSTR(" : "), false);
    // if (keylogs_keycode < 60) {
    //     oled_write_ln_P(&(code_to_name[keylogs_keycode]), false);
    // }

    // oled_write_ln_P(read_keylog(), false);
    // oled_write_ln_P(read_keylogs(), false);
  } else {
    oled_write_P(PSTR("\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8a\x8b\x8c\x8d\x8e\x8f\x90\x91\x92\x93\x94\xa0\xa1\xa2\xa3\xa4\xa5\xa6\xa7\xa8\xa9\xaa\xab\xac\xad\xae\xaf\xb0\xb1\xb2\xb3\xb4\xc0\xc1\xc2\xc3\xc4\xc5\xc6\xc7\xc8\xc9\xca\xcb\xcc\xcd\xce\xcf\xd0\xd1\xd2\xd3\xd4\x0"), false);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }
  return true;
}
