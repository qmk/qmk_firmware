#include QMK_KEYBOARD_H
#include "print.h"
#include "base/disp_array.h"
#include "base/shift_reg.h"
#include "fonts/FreeSans12pt7b.h"

enum kb_layers { _LAYER0 = 0, _LAYER1 = 1, _LAYER2 = 2, _LAYER3 = 3, _LAYER4 = 4, _LAYER5 = 5, NUM_LAYERS = 6 };

static bool rotarySwitchPressed = false;
static bool holdShift = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_LAYER0] = LAYOUT(KC_1,    KC_2,   KC_3,      KC_4,        KC_5,       KC_6,     KC_7,         KC_8),
    [_LAYER1] = LAYOUT(KC_5,    KC_6,   KC_7,      KC_8,        KC_9,       KC_0,     KC_EQUAL,     KC_MINUS),
    [_LAYER2] = LAYOUT(KC_A,    KC_B,   KC_C,      KC_D,        KC_E,       KC_F,     KC_G,         KC_H),
    [_LAYER3] = LAYOUT(KC_I,    KC_J,   KC_K,      KC_L,        KC_M,       KC_N,     KC_O,         KC_P),
    [_LAYER4] = LAYOUT(KC_Q,    KC_R,   KC_S,      KC_T,        KC_U,       KC_V,     KC_W,         KC_X),
    [_LAYER5] = LAYOUT(KC_Y,    KC_Z,   KC_SLASH,  KC_TILDE,    KC_COMMA,   KC_DOT,   KC_LBRACKET,  KC_RBRACKET)
};

led_config_t g_led_config = {{// Key Matrix to LED Index
                              {0, 1, 2, 3}, {4, 5, 6, 7}},
                             {
                                 // LED Index to Physical Position
                                 {100, 32},
                                 {120, 32},
                                 {140, 32},
                                 {160, 32},
                                 {100, 52},
                                 {120, 52},
                                 {140, 52},
                                 {160, 52}
                             },
                             {
                                 // LED Index to Flag
                                 4, 4, 4, 4, 4, 4, 4, 4
                             }};

void process_layer_switch_user(uint16_t new_layer);

void matrix_init_user(void) {
    OLED_INIT;
}

void matrix_scan_user(void) {
    if (readPin(ENCODERS_SWITCH)) {
        if(rotarySwitchPressed) {
            if(holdShift) {
                register_code(KC_LSHIFT);
            } else {
                unregister_code(KC_LSHIFT);
            }
        }
        rotarySwitchPressed = false;
    } else if(!rotarySwitchPressed) {
        rotarySwitchPressed = true;
        holdShift = !holdShift;
        force_layer_switch();
        update_performed();
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

struct disp_status {
    uint8_t bitmask[NUM_SHIFT_REGISTERS];
};

struct disp_status key_display[] = {{.bitmask = {~0x00, ~0x01}}, {.bitmask = {~0x00, ~0x02}}, {.bitmask = {~0x00, ~0x04}}, {.bitmask = {~0x00, ~0x08}},
                                    {.bitmask = {~0x01, ~0x00}}, {.bitmask = {~0x02, ~0x00}}, {.bitmask = {~0x04, ~0x00}}, {.bitmask = {~0x08, ~0x00}}};

const char* keycode_to_disp_text(uint16_t keycode) {
    bool shift = holdShift;
    switch (keycode) {
        case KC_0:
            return shift ? ")" : "0";
        case KC_1:
            return shift ? "!" : "1";
        case KC_2:
            return shift ? "@" : "2";
        case KC_3:
            return shift ? "#" : "3";
        case KC_4:
            return shift ? "$" : "4";
        case KC_5:
            return shift ? "%" : "5";
        case KC_6:
            return shift ? "^" : "6";
        case KC_7:
            return shift ? "&" : "7";
        case KC_8:
            return shift ? "*" : "8";
        case KC_9:
            return shift ? "(" : "9";
        case KC_EQUAL:
            return shift ? "+" : "=";
        case KC_MINUS:
            return shift ? "-" : "_";
        case KC_SLASH:
            return shift ? "/" : "?";
        case KC_TILDE:
            return shift ? "`" : "~";
        case KC_COMMA:
            return shift ? "<" : ",";
        case KC_DOT:
            return shift ? ">" : ",";
        case KC_LBRACKET:
            return shift ? "{" : "[";
        case KC_RBRACKET:
            return shift ? "}" : "]";
        default: break;
    }
    shift |= host_keyboard_led_state().caps_lock;
    switch (keycode) {
        case KC_A:
            return shift ? "A" : "a";
        case KC_B:
            return shift ? "B" : "b";
        case KC_C:
            return shift ? "C" : "c";
        case KC_D:
            return shift ? "D" : "d";
        case KC_E:
            return shift ? "E" : "e";
        case KC_F:
            return shift ? "F" : "f";
        case KC_G:
            return shift ? "G" : "g";
        case KC_H:
            return shift ? "H" : "h";
        case KC_I:
            return shift ? "I" : "i";
        case KC_J:
            return shift ? "J" : "j";
        case KC_K:
            return shift ? "K" : "k";
        case KC_L:
            return shift ? "L" : "l";
        case KC_M:
            return shift ? "M" : "m";
        case KC_N:
            return shift ? "N" : "n";
        case KC_O:
            return shift ? "O" : "o";
        case KC_P:
            return shift ? "P" : "p";
        case KC_Q:
            return shift ? "Q" : "q";
        case KC_R:
            return shift ? "R" : "r";
        case KC_S:
            return shift ? "S" : "s";
        case KC_T:
            return shift ? "T" : "t";
        case KC_U:
            return shift ? "U" : "u";
        case KC_V:
            return shift ? "V" : "v";
        case KC_W:
            return shift ? "W" : "w";
        case KC_X:
            return shift ? "X" : "x";
        case KC_Y:
            return shift ? "Y" : "y";
        case KC_Z:
            return shift ? "Z" : "z";
        default:
            break;
    }
    return "?";
}

void process_layer_switch_user(uint16_t new_layer) {
    layer_move(new_layer);
    next_rgb_matrix_effect();

    // keypos_t key;
    for (uint8_t r = 0; r < MATRIX_ROWS; ++r) {
        for (uint8_t c = 0; c < MATRIX_COLS; ++c) {
            //key.col           = c;
            //key.row           = r;
            uint16_t keycode  = keymaps[new_layer][r][c];
            uint8_t  disp_idx = LAYOUT_TO_INDEX(r, c);

            if (disp_idx != 255) {
                const char* text = keycode_to_disp_text(keycode);
                sr_shift_out_buffer_latch(key_display[disp_idx].bitmask, sizeof(key_display->bitmask));
                kdisp_set_buffer(0x00);
                kdisp_write_gfx_text(&FreeSans12pt7b, 28, 18, text);
                kdisp_send_buffer();
            }
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
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

    uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u SR bitmask: 0x%02X%02X (%u, %u)\n",
        keycode, record->event.key.col, record->event.key.row, record->event.pressed,
        record->event.time, record->tap.interrupted, record->tap.count, bitmask[1], bitmask[0], ~bitmask[1], ~bitmask[0]);

   update_performed();

   return true;
};
