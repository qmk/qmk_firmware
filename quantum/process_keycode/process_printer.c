/* Copyright 2016 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "process_printer.h"
#include "action_util.h"

bool    printing_enabled = false;
uint8_t character_shift  = 0;

void enable_printing(void) {
    printing_enabled = true;
    serial_init();
}

void disable_printing(void) { printing_enabled = false; }

uint8_t shifted_numbers[10] = {0x21, 0x40, 0x23, 0x24, 0x25, 0x5E, 0x26, 0x2A, 0x28, 0x29};

// uint8_t keycode_to_ascii[0xFF][2];

// keycode_to_ascii[KC_MINS] = {0x2D, 0x5F};

void print_char(char c) {
    USB_Disable();
    serial_send(c);
    USB_Init();
}

void print_string(char c[]) {
    for (uint8_t i = 0; i < strlen(c); i++) print_char(c[i]);
}

void print_box_string(const char text[]) {
    size_t len = strlen(text);
    char   out[len * 3 + 8];
    out[0] = 0xDA;
    for (uint8_t i = 0; i < len; i++) {
        out[i + 1] = 0xC4;
    }
    out[len + 1] = 0xBF;
    out[len + 2] = '\n';

    out[len + 3] = 0xB3;
    for (uint8_t i = 0; i < len; i++) {
        out[len + 4 + i] = text[i];
    }
    out[len * 2 + 4] = 0xB3;
    out[len * 2 + 5] = '\n';

    out[len * 2 + 6] = 0xC0;
    for (uint8_t i = 0; i < len; i++) {
        out[len * 2 + 7 + i] = 0xC4;
    }
    out[len * 3 + 7] = 0xD9;
    out[len * 3 + 8] = '\n';

    print_string(out);
}

bool process_printer(uint16_t keycode, keyrecord_t *record) {
    if (keycode == PRINT_ON) {
        enable_printing();
        return false;
    }
    if (keycode == PRINT_OFF) {
        disable_printing();
        return false;
    }

    if (printing_enabled) {
        switch (keycode) {
            case KC_EXLM ... KC_RPRN:
            case KC_UNDS:
            case KC_PLUS:
            case KC_LCBR:
            case KC_RCBR:
            case KC_PIPE:
            case KC_TILD:
                keycode &= 0xFF;
            case KC_LSFT:
            case KC_RSFT:
                if (record->event.pressed) {
                    character_shift++;
                } else {
                    character_shift--;
                }
                return false;
                break;
        }

        switch (keycode) {
            case KC_F1:
                if (record->event.pressed) {
                    print_box_string("This is a line of text!");
                }
                return false;
            case KC_ESC:
                if (record->event.pressed) {
                    print_char(0x1B);
                }
                return false;
                break;
            case KC_SPC:
                if (record->event.pressed) {
                    print_char(0x20);
                }
                return false;
                break;
            case KC_A ... KC_Z:
                if (record->event.pressed) {
                    if (character_shift) {
                        print_char(0x41 + (keycode - KC_A));
                    } else {
                        print_char(0x61 + (keycode - KC_A));
                    }
                }
                return false;
                break;
            case KC_1 ... KC_0:
                if (record->event.pressed) {
                    if (character_shift) {
                        print_char(shifted_numbers[keycode - KC_1]);
                    } else {
                        print_char(0x30 + ((keycode - KC_1 + 1) % 10));
                    }
                }
                return false;
                break;
            case KC_ENT:
                if (record->event.pressed) {
                    if (character_shift) {
                        print_char(0x0C);
                    } else {
                        print_char(0x0A);
                    }
                }
                return false;
                break;
            case KC_BSPC:
                if (record->event.pressed) {
                    if (character_shift) {
                        print_char(0x18);
                    } else {
                        print_char(0x1A);
                    }
                }
                return false;
                break;
            case KC_DOT:
                if (record->event.pressed) {
                    if (character_shift) {
                        print_char(0x3E);
                    } else {
                        print_char(0x2E);
                    }
                }
                return false;
                break;
            case KC_COMM:
                if (record->event.pressed) {
                    if (character_shift) {
                        print_char(0x3C);
                    } else {
                        print_char(0x2C);
                    }
                }
                return false;
                break;
            case KC_SLSH:
                if (record->event.pressed) {
                    if (character_shift) {
                        print_char(0x3F);
                    } else {
                        print_char(0x2F);
                    }
                }
                return false;
                break;
            case KC_QUOT:
                if (record->event.pressed) {
                    if (character_shift) {
                        print_char(0x22);
                    } else {
                        print_char(0x27);
                    }
                }
                return false;
                break;
            case KC_GRV:
                if (record->event.pressed) {
                    if (character_shift) {
                        print_char(0x7E);
                    } else {
                        print_char(0x60);
                    }
                }
                return false;
                break;
            case KC_MINS:
                if (record->event.pressed) {
                    if (character_shift) {
                        print_char(0x5F);
                    } else {
                        print_char(0x2D);
                    }
                }
                return false;
                break;
            case KC_EQL:
                if (record->event.pressed) {
                    if (character_shift) {
                        print_char(0x2B);
                    } else {
                        print_char(0x3D);
                    }
                }
                return false;
                break;
            case KC_LBRC:
                if (record->event.pressed) {
                    if (character_shift) {
                        print_char(0x7B);
                    } else {
                        print_char(0x5B);
                    }
                }
                return false;
                break;
            case KC_RBRC:
                if (record->event.pressed) {
                    if (character_shift) {
                        print_char(0x7D);
                    } else {
                        print_char(0x5D);
                    }
                }
                return false;
                break;
            case KC_BSLS:
                if (record->event.pressed) {
                    if (character_shift) {
                        print_char(0x7C);
                    } else {
                        print_char(0x5C);
                    }
                }
                return false;
                break;
        }
    }
    return true;
}
