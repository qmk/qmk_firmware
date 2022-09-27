#include QMK_KEYBOARD_H

#include "polyatom.h"
#include "print.h"
#include "base/disp_array.h"
#include "base/shift_reg.h"
#include "fonts/gfx_used_fonts.h"

#include "quantum/quantum_keycodes.h"

enum kb_layers { _LAYER0 = 0, _LAYER1 = 1, _LAYER2 = 2, _LAYER3 = 3, _LAYER4 = 4, _LAYER5 = 5, _LAYER6 = 6, _LAYER7 = 7, NUM_LAYERS = 8 };

enum my_keycodes {
  KC_NEXT_LAYER = SAFE_RANGE,
  RGB_TOGGLE,
  RGB_NEXT,
  RGB_PREV,
  KC_HANGEUL_KIYEOK          =0x1100,
  KC_HANGEUL_SSANGKIYEOK     =0x1101,
  KC_HANGEUL_NIEUN           =0x1102,
  KC_HANGEUL_TIKEUT          =0x1103,
  KC_HANGEUL_SSANGTIKEUT     =0x1104,
  KC_HANGEUL_RIEUL           =0x1105,
  KC_HANGEUL_MIEUM           =0x1106,
  KC_HANGEUL_PIEUP           =0x1107,
  KC_HANGEUL_SSANGPIEUP      =0x1108,
  KC_HANGEUL_SIOS            =0x1109,
  KC_HANGEUL_SSANGSIOS       =0x110A,
  KC_HANGEUL_IEUNG           =0x110B,
  KC_HANGEUL_CIEUC           =0x110C,
  KC_HANGEUL_SSANGCIEUC      =0x110D,
  KC_HANGEUL_CHIEUCH         =0x110E,
  KC_HANGEUL_KHIEUKH         =0x110F,
  KC_HANGEUL_THIEUTH         =0x1110,
  KC_HANGEUL_PHIEUPH         =0x1111,
  KC_HANGEUL_HIEUH           =0x1112,
  KC_HANGEUL_A               =0x1161,
  KC_HANGEUL_AE              =0x1162,
  KC_HANGEUL_YA              =0x1163,
  KC_HANGEUL_YAE             =0x1164,
  KC_HANGEUL_EO              =0x1165,
  KC_HANGEUL_E               =0x1166,
  KC_HANGEUL_YEO             =0x1167,
  KC_HANGEUL_YE              =0x1168,
  KC_HANGEUL_O               =0x1169,
  KC_HANGEUL_YO              =0x116D,
  KC_HANGEUL_U               =0x116E,
  KC_HANGEUL_YU              =0x1172,
  KC_HANGEUL_EU              =0x1173,
  KC_HANGEUL_I               =0x1175
};

static bool rotarySwitchPressed = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_LAYER0] = LAYOUT( KC_NUM_LOCK,        KC_KP_SLASH,        KC_KP_ASTERISK,     KC_KP_MINUS,
                        KC_KP_7,            KC_KP_8,            KC_KP_9,            KC_KP_PLUS,
                        KC_KP_4,            KC_KP_5,            KC_KP_6,            KC_KP_EQUAL,
                        KC_KP_1,            KC_KP_2,            KC_KP_3,            KC_KP_ENTER,
                        KC_KP_0,            KC_KP_DOT,          KC_RIGHT_SHIFT,     KC_NEXT_LAYER
                        ),
    [_LAYER1] = LAYOUT( KC_A,               KC_B,               KC_C,               KC_D,
                        KC_E,               KC_F,               KC_G,               KC_H,
                        KC_I,               KC_J,               KC_K,               KC_L,
                        KC_M,               KC_N,               KC_O,               KC_P,
                        KC_Q,               KC_R,               KC_RIGHT_SHIFT,     KC_NEXT_LAYER
                        ),
    [_LAYER2] = LAYOUT( KC_S,               KC_T,               KC_U,               KC_V,
                        KC_W,               KC_X,               KC_Y,               KC_Z,
                        KC_0,               KC_1,               KC_2,               KC_3,
                        KC_4,               KC_5,               KC_6,               KC_7,
                        KC_8,               KC_9,               KC_RIGHT_SHIFT,     KC_NEXT_LAYER
                        ),
    [_LAYER3] = LAYOUT( KC_HANGEUL_KIYEOK,  KC_HANGEUL_NIEUN,   KC_HANGEUL_TIKEUT,  KC_HANGEUL_RIEUL,
                        KC_HANGEUL_MIEUM,   KC_HANGEUL_PIEUP,   KC_HANGEUL_SIOS,    KC_HANGEUL_IEUNG,
                        KC_HANGEUL_CIEUC,   KC_HANGEUL_CHIEUCH, KC_HANGEUL_KHIEUKH, KC_HANGEUL_THIEUTH,
                        KC_HANGEUL_PHIEUPH, KC_HANGEUL_HIEUH,   KC_SPACE,           KC_BACKSPACE,
                        KC_SLASH,           KC_KP_DOT,          KC_RIGHT_SHIFT,     KC_NEXT_LAYER
                        ),
    [_LAYER4] = LAYOUT( KC_HANGEUL_A,       KC_HANGEUL_AE,      KC_HANGEUL_YAE,     KC_HANGEUL_YA,
                        KC_HANGEUL_EO,      KC_HANGEUL_E,       KC_HANGEUL_YE,      KC_HANGEUL_YEO,
                        KC_HANGEUL_O,       KC_HANGEUL_YO,      KC_HANGEUL_U,       KC_HANGEUL_YU,
                        KC_HANGEUL_EU,      KC_HANGEUL_I,       KC_SPACE,           KC_BACKSPACE,
                        KC_SLASH,           KC_KP_DOT,          KC_RIGHT_SHIFT,     KC_NEXT_LAYER
                        ),
    [_LAYER5] = LAYOUT( KC_PRINT_SCREEN,    KC_SCROLL_LOCK,     KC_PAUSE,           KC_BACKSPACE,
                        KC_INSERT,          KC_HOME,            KC_PAGE_UP,         KC_BACKSLASH,
                        KC_DELETE,          KC_END,             KC_PAGE_DOWN,       KC_SLASH,
                        KC_LEFT_BRACKET,    KC_RIGHT_BRACKET,   KC_GRAVE,           KC_MINUS,
                        KC_COMMA,           KC_DOT,             KC_RIGHT_SHIFT,     KC_NEXT_LAYER
                        ),
    [_LAYER6] = LAYOUT( KC_F1,              KC_F2,              KC_F3,              KC_F4,
                        KC_F5,              KC_F6,              KC_F7,              KC_F8,
                        KC_F9,              KC_F10,             KC_F11,             KC_F12,
                        KC_MEDIA_PREV_TRACK,KC_MEDIA_PLAY_PAUSE,KC_MEDIA_STOP,      KC_MEDIA_NEXT_TRACK,
                        KC_LEFT_CTRL,       KC_LEFT_ALT,        KC_RIGHT_SHIFT,     KC_NEXT_LAYER
                        ),
    [_LAYER7] = LAYOUT( QK_BOOTLOADER,      QK_DEBUG_TOGGLE,    QK_CLEAR_EEPROM,    RGB_PREV,
                        KC_MS_BTN1,         KC_MS_UP,           KC_MS_BTN2,         RGB_TOGGLE,
                        KC_MS_LEFT,         KC_MS_BTN3,         KC_MS_RIGHT,        RGB_NEXT,
                        KC_AUDIO_VOL_DOWN,  KC_MS_DOWN,         KC_AUDIO_VOL_UP,    KC_AUDIO_MUTE,
                        KC_MS_ACCEL0,       KC_MS_ACCEL1,       KC_MS_ACCEL2,       KC_NEXT_LAYER
                        )
};

led_config_t g_led_config = {{// Key Matrix to LED Index
                              {0, 1, 2, 3},
                              {4, 5, 6, 7},
                              {8, 9, 10, 11},
                              {12, 13, 14, 15},
                              {16, 17, 18, 19}
                             },
                             {
                                 // LED Index to Physical Position
                                 {100, 40}, {120, 40}, {140, 40}, {160, 40},
                                 {100, 60}, {120, 60}, {140, 60}, {160, 60},
                                 {100, 80}, {120, 80}, {140, 80}, {160, 80},
                                 {100, 100}, {120, 100}, {140, 100}, {160, 100},
                                 {100, 120}, {120, 120}, {140, 120}, {160, 120}
                             },
                             {
                                 // LED Index to Flag
                                 4, 4, 4, 4,
                                 4, 4, 4, 4,
                                 4, 4, 4, 4,
                                 4, 4, 4, 4,
                                 4, 4, 4, 4
                             }};

void process_layer_switch_user(uint16_t new_layer);

void matrix_init_user(void) {
    setPinInputHigh(ENCODERS_SWITCH);
#ifdef OLED_ENABLE
    OLED_INIT;
    #endif
}

void matrix_scan_user(void) {
    if (readPin(ENCODERS_SWITCH)==0) {
        if(rotarySwitchPressed) {
            register_code(KC_CAPS_LOCK);
            unregister_code(KC_CAPS_LOCK);
        }
        rotarySwitchPressed = false;
    } else if(!rotarySwitchPressed) {
        rotarySwitchPressed = true;
    }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (!clockwise) {
        prev_layer(NUM_LAYERS);
    } else {
        next_layer(NUM_LAYERS);
    }

    update_performed();
    return true;
}

/*struct keycap_text {
    const char* lower;
    const char* upper;
    const char* num_lock;
};*/

struct diplay_info {
    uint8_t bitmask[NUM_SHIFT_REGISTERS];
};

#define BITMASK1(x) .bitmask = {~0, ~0, ~0, ~0, ~(1<<x)}
#define BITMASK2(x) .bitmask = {~0, ~0, ~0, ~(1<<x), ~0}
#define BITMASK3(x) .bitmask = {~0, ~0, ~(1<<x), ~0, ~0}
#define BITMASK4(x) .bitmask = {~0, ~(1<<x), ~0, ~0, ~0}
#define BITMASK5(x) .bitmask = {~(1<<x), ~0, ~0, ~0, ~0}

struct diplay_info key_display[] = {
        {BITMASK1(0)}, {BITMASK1(1)}, {BITMASK1(2)}, {BITMASK1(3)},
        {BITMASK2(0)}, {BITMASK2(1)}, {BITMASK2(2)}, {BITMASK2(3)},
        {BITMASK3(0)}, {BITMASK3(1)}, {BITMASK3(2)}, {BITMASK3(3)},
        {BITMASK4(0)}, {BITMASK4(1)}, {BITMASK4(2)}, {BITMASK4(3)},
        {BITMASK5(0)}, {BITMASK5(1)}, {BITMASK5(2)}, {BITMASK5(3)}
    };


const uint16_t* keycode_to_disp_text(uint16_t keycode, led_t state) {
    bool shift = ((get_mods() & MOD_MASK_SHIFT)!=0) || state.caps_lock;
    switch (keycode) {
        case KC_HANGEUL_NIEUN:
            return HANGEUL_NIEUN;
        case KC_HANGEUL_RIEUL:
            return HANGEUL_RIEUL;
        case KC_HANGEUL_MIEUM:
            return HANGEUL_MIEUM;
        case KC_HANGEUL_IEUNG:
            return HANGEUL_IEUNG;
        case KC_HANGEUL_CHIEUCH:
            return HANGEUL_CHIEUCH;
        case KC_HANGEUL_KHIEUKH:
            return HANGEUL_KHIEUKH;
        case KC_HANGEUL_THIEUTH:
            return HANGEUL_THIEUTH;
        case KC_HANGEUL_PHIEUPH:
            return HANGEUL_PHIEUPH;
        case KC_HANGEUL_HIEUH:
            return HANGEUL_HIEUH;
        case KC_HANGEUL_A:
            return HANGEUL_A;
        case KC_HANGEUL_AE:
            return HANGEUL_AE;
        case KC_HANGEUL_YA:
            return HANGEUL_YA;
        case KC_HANGEUL_YAE:
            return HANGEUL_YAE;
        case KC_HANGEUL_EO:
            return HANGEUL_EO;
        case KC_HANGEUL_E:
            return HANGEUL_E;
        case KC_HANGEUL_YEO:
            return HANGEUL_YEO;
        case KC_HANGEUL_YE:
            return HANGEUL_YE;
        case KC_HANGEUL_O:
            return HANGEUL_O;
        case KC_HANGEUL_YO:
            return HANGEUL_YO;
        case KC_HANGEUL_U:
            return HANGEUL_U;
        case KC_HANGEUL_YU:
            return HANGEUL_YU;
        case KC_HANGEUL_EU:
            return HANGEUL_EU;
        case KC_HANGEUL_I:
            return HANGEUL_I;
        case KC_HANGEUL_KIYEOK:
            return shift ? HANGEUL_SSANGKIYEOK : HANGEUL_KIYEOK;
        case KC_HANGEUL_TIKEUT:
            return shift ? HANGEUL_SSANGTIKEUT : HANGEUL_TIKEUT;
        case KC_HANGEUL_PIEUP:
            return shift ? HANGEUL_SSANGPIEUP : HANGEUL_PIEUP;
        case KC_HANGEUL_SIOS:
            return shift ? HANGEUL_SSANGSIOS : HANGEUL_SIOS;
        case KC_HANGEUL_CIEUC:
            return shift ? HANGEUL_SSANGCIEUC : HANGEUL_CIEUC;
        case KC_0:
            return shift ? u")" : u"0";
        case KC_1:
            return shift ? u"!" : u"1";
        case KC_2:
            return shift ? u"@" : u"2";
        case KC_3:
            return shift ? u"#" : u"3";
        case KC_4:
            return shift ? u"$" : u"4";
        case KC_5:
            return shift ? u"%" : u"5";
        case KC_6:
            return shift ? u"^" : u"6";
        case KC_7:
            return shift ? u"&" : u"7";
        case KC_8:
            return shift ? u"*" : u"8";
        case KC_9:
            return shift ? u"(" : u"9";
        case KC_EQUAL:
            return shift ? u"+" : u"=";
        case KC_MINUS:
            return shift ? u"_" : u"-";
        case KC_GRAVE:
            return shift ? u"~" : u"`";
        case KC_COMMA:
            return shift ? u"<" : u",";
        case KC_DOT:
            return shift ? u">" : u",";
        case KC_LBRACKET:
            return shift ? u"{" : u"[";
        case KC_RBRACKET:
            return shift ? u"}" : u"]";
        case KC_SPACE:
            return u"  " ICON_SPACE;
        case KC_BACKSPACE:
            return u" " ICON_BACKSPACE;
        case KC_A:
            return shift ? u"A" : u"a";
        case KC_B:
            return shift ? u"B" : u"b";
        case KC_C:
            return shift ? u"C" : u"c";
        case KC_D:
            return shift ? u"D" : u"d";
        case KC_E:
            return shift ? u"E" : u"e";
        case KC_F:
            return shift ? u"F" : u"f";
        case KC_G:
            return shift ? u"G" : u"g";
        case KC_H:
            return shift ? u"H" : u"h";
        case KC_I:
            return shift ? u"I" : u"i";
        case KC_J:
            return shift ? u"J" : u"j";
        case KC_K:
            return shift ? u"K" : u"k";
        case KC_L:
            return shift ? u"L" : u"l";
        case KC_M:
            return shift ? u"M" : u"m";
        case KC_N:
            return shift ? u"N" : u"n";
        case KC_O:
            return shift ? u"O" : u"o";
        case KC_P:
            return shift ? u"P" : u"p";
        case KC_Q:
            return shift ? u"Q" : u"q";
        case KC_R:
            return shift ? u"R" : u"r";
        case KC_S:
            return shift ? u"S" : u"s";
        case KC_T:
            return shift ? u"T" : u"t";
        case KC_U:
            return shift ? u"U" : u"u";
        case KC_V:
            return shift ? u"V" : u"v";
        case KC_W:
            return shift ? u"W" : u"w";
        case KC_X:
            return shift ? u"X" : u"x";
        case KC_Y:
            return shift ? u"Y" : u"y";
        case KC_Z:
            return shift ? u"Z" : u"z";
        case KC_NUM_LOCK:
            return !state.num_lock ? u"Num" ICON_NUMLOCK_OFF : u"Num" ICON_NUMLOCK_ON;
        case KC_KP_SLASH:
            return u"/";
        case KC_KP_ASTERISK:
            return u"*";
        case KC_KP_MINUS:
            return u"-";
        case KC_KP_7:
            return !state.num_lock ? u"Home" : u"7";
        case KC_KP_8:
            return !state.num_lock ? u"   " ICON_UP : u"8";
        case KC_KP_9:
            return !state.num_lock ? u"PgUp" : u"9";
        case KC_KP_PLUS:
            return u"+";
        case KC_KP_4:
            return !state.num_lock ? u"  " ICON_LEFT : u"4";
        case KC_KP_5:
            return !state.num_lock ? u"" : u"5";
        case KC_KP_6:
            return !state.num_lock ? u"  " ICON_RIGHT : u"6";
        case KC_KP_EQUAL:
            return u"=";
        case KC_KP_1:
            return !state.num_lock ? u"End" : u"1";
        case KC_KP_2:
            return !state.num_lock ? u"   " ICON_DOWN : u"2";
        case KC_KP_3:
            return !state.num_lock ? u"PgDn" : u"3";
        case KC_CALCULATOR:
            return u"Calc";
        case KC_KP_0:
            return !state.num_lock ? u"Ins" : u"0";
        case KC_KP_DOT:
            return !state.num_lock ? u"Del" : u".";
        case KC_KP_ENTER:
            return u"Enter";
        case QK_BOOTLOADER:
            return u"BootL";
        case QK_DEBUG_TOGGLE:
            return u"Debug";
        case QK_CLEAR_EEPROM:
            return u"Clr EE";
        case RGB_PREV:
            return u"R  " ICON_LEFT;
        case RGB_TOGGLE:
            return rgb_matrix_is_enabled() ? u"G " ICON_SWITCH_ON : u"G " ICON_SWITCH_OFF;
        case RGB_NEXT:
            return u"B  " ICON_RIGHT;
        case KC_MEDIA_NEXT_TRACK:
            return ICON_RIGHT ICON_RIGHT;
        case KC_MEDIA_PLAY_PAUSE:
            return u"  " ICON_RIGHT;
        case KC_MEDIA_STOP:
            return u"Stop";
        case KC_MEDIA_PREV_TRACK:
            return ICON_LEFT ICON_LEFT;
        case KC_MS_ACCEL0:
            return u">>";
        case KC_MS_ACCEL1:
            return u">>>";
        case KC_MS_ACCEL2:
            return u">>>>";
        case KC_MS_BTN1:
            return u"  " ICON_LMB;
        case KC_MS_BTN2:
            return u"  " ICON_RMB;
        case KC_MS_BTN3:
            return u"  " ICON_MMB;
        case KC_MS_UP:
            return u"  " ICON_UP;
        case KC_MS_DOWN:
            return u"  " ICON_DOWN;
        case KC_MS_LEFT:
            return u"  " ICON_LEFT;
        case KC_MS_RIGHT:
            return u"  " ICON_RIGHT;
        case KC_AUDIO_MUTE:
            return u"Mute";
        case KC_AUDIO_VOL_DOWN:
            return u"  " ICON_VOL_DOWN;
        case KC_AUDIO_VOL_UP:
            return u"  " ICON_VOL_UP;
        case KC_NEXT_LAYER:
            return u"Next " ICON_LAYER;
        case KC_PRINT_SCREEN:
            return u"PrtScn";
        case KC_SCROLL_LOCK:
            return u"SclLck";
        case KC_PAUSE:
            return u"Pause";
        case KC_INSERT:
            return u"Insert";
        case KC_HOME:
            return u"Home";
        case KC_PAGE_UP:
            return u"PgUp";
        case KC_PAGE_DOWN:
            return u"PgDn";
        case KC_BACKSLASH:
            return shift ? u"|" : u"\\";
        case KC_DELETE:
            return u"Delete";
        case KC_END:
            return u"End";
        case KC_SLASH:
            return shift ? u"?" : u"/";
        case KC_ESC:
            return u"ESC";
        case KC_RIGHT_SHIFT:
            return state.caps_lock ? u" " ICON_SHIFT u"  " ICON_CAPSLOCK_ON : u" " ICON_SHIFT u"  " ICON_CAPSLOCK_OFF;
        case KC_F1:
            return u"F1";
        case KC_F2:
            return u"F2";
        case KC_F3:
            return u"F3";
        case KC_F4:
            return u"F4";
        case KC_F5:
            return u"F5";
        case KC_F6:
            return u"F6";
        case KC_F7:
            return u"F7";
        case KC_F8:
            return u"F8";
        case KC_F9:
            return u"F9";
        case KC_F10:
            return u"F10";
        case KC_F11:
            return u"F11";
        case KC_F12:
            return u"F12";
        case KC_LEFT_CTRL:
            return u"L Ctrl";
        case KC_LEFT_ALT:
            return u"L Alt";
        default:
            break;
    }
    return u"[?]";
}

const GFXfont* ALL_FONTS [] = {&AsciiFont, &IconsFont, &HangulJamoFont};
const uint8_t NUM_FONTS = sizeof(ALL_FONTS) / sizeof(GFXfont*);


void process_layer_switch_user(uint16_t new_layer) {
    layer_move(new_layer);
    led_t state = host_keyboard_led_state();

    // keypos_t key;
    for (uint8_t r = 0; r < MATRIX_ROWS; ++r) {
        for (uint8_t c = 0; c < MATRIX_COLS; ++c) {
            //key.col           = c;
            //key.row           = r;
            uint16_t keycode  = keymaps[new_layer][r][c];
            uint8_t  disp_idx = LAYOUT_TO_INDEX(r, c);

            if (disp_idx != 255) {
                const uint16_t* text = keycode_to_disp_text(keycode, state);
                sr_shift_out_buffer_latch(key_display[disp_idx].bitmask, sizeof(key_display->bitmask));
                kdisp_set_buffer(0x00);
                kdisp_write_gfx_text(ALL_FONTS, NUM_FONTS, 28, 18, text);
                kdisp_send_buffer();
            }
        }
    }
}

void post_process_record_user(uint16_t keycode, keyrecord_t* record) {
    uint8_t disp_idx = LAYOUT_TO_INDEX(record->event.key.row, record->event.key.col);
    const uint8_t* bitmask = key_display[disp_idx].bitmask;
    sr_shift_out_buffer_latch(bitmask, sizeof(key_display->bitmask));
    if (record->event.pressed) {
        set_last_key(keycode);
        if (disp_idx != 255) {
            kdisp_invert(true);
        }
    } else {
        if (disp_idx != 255) {
            kdisp_invert(false);
        }
    }

    if(!record->event.pressed) {
        switch(keycode) {
            case RGB_TOGGLE:
                rgb_matrix_toggle_noeeprom();
                force_layer_switch();
                break;
            case KC_RIGHT_SHIFT:
                force_layer_switch();
                break;
            case KC_NEXT_LAYER:
                next_layer(NUM_LAYERS);
                break;
            case RGB_NEXT:
                rgb_matrix_step_noeeprom();
                break;
            case RGB_PREV:
                rgb_matrix_step_reverse_noeeprom();
                break;
            default:
                break;
        }
    } else {
        switch (keycode)
        {
        case KC_RIGHT_SHIFT:
            force_layer_switch();
            break;
        default:
            break;
        }
    }

    uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u display: %d SR bitmask: 0x%02X%02X%02X%02X%02X\n",
        keycode, record->event.key.col, record->event.key.row, record->event.pressed,
        record->event.time, record->tap.interrupted, record->tap.count, disp_idx, bitmask[4], bitmask[3], bitmask[2], bitmask[1], bitmask[0]);

   update_performed();
};

bool led_update_user(led_t led_state) {
    force_layer_switch();
    return true;
}
