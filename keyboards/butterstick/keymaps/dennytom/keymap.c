#include QMK_KEYBOARD_H

#define CHORD_TIMEOUT 100
#define DANCE_TIMEOUT 200
#define LEADER_TIMEOUT 750
#define TAP_TIMEOUT 50
#define LONG_PRESS_MULTIPLIER 3
#define DYNAMIC_MACRO_MAX_LENGTH 20
#define COMMAND_MAX_LENGTH 5
#define LEADER_MAX_LENGTH 5
#define HASH_TYPE uint32_t
#define NUMBER_OF_KEYS 20
#define DEFAULT_PSEUDOLAYER QWERTY

#define H_TOP1 ((HASH_TYPE) 1 << 0)
#define H_TOP2 ((HASH_TYPE) 1 << 1)
#define H_TOP3 ((HASH_TYPE) 1 << 2)
#define H_TOP4 ((HASH_TYPE) 1 << 3)
#define H_TOP5 ((HASH_TYPE) 1 << 4)
#define H_TOP6 ((HASH_TYPE) 1 << 5)
#define H_TOP7 ((HASH_TYPE) 1 << 6)
#define H_TOP8 ((HASH_TYPE) 1 << 7)
#define H_TOP9 ((HASH_TYPE) 1 << 8)
#define H_TOP0 ((HASH_TYPE) 1 << 9)
#define H_BOT1 ((HASH_TYPE) 1 << 10)
#define H_BOT2 ((HASH_TYPE) 1 << 11)
#define H_BOT3 ((HASH_TYPE) 1 << 12)
#define H_BOT4 ((HASH_TYPE) 1 << 13)
#define H_BOT5 ((HASH_TYPE) 1 << 14)
#define H_BOT6 ((HASH_TYPE) 1 << 15)
#define H_BOT7 ((HASH_TYPE) 1 << 16)
#define H_BOT8 ((HASH_TYPE) 1 << 17)
#define H_BOT9 ((HASH_TYPE) 1 << 18)
#define H_BOT0 ((HASH_TYPE) 1 << 19)

enum internal_keycodes {
    TOP1 = SAFE_RANGE,
    TOP2, TOP3, TOP4, TOP5, TOP6, TOP7, TOP8, TOP9, TOP0, BOT1, BOT2, BOT3, BOT4, BOT5, BOT6, BOT7, BOT8, BOT9, BOT0,
    FIRST_INTERNAL_KEYCODE = TOP1,
    LAST_INTERNAL_KEYCODE = BOT0
};

enum pseudolayers {
    ALWAYS_ON, QWERTY, NUM, MOV, MOUSE, ASETNIOP, ASETNIOP_123, ASETNIOP_FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_butter(TOP1, TOP2, TOP3, TOP4, TOP5, TOP6, TOP7, TOP8, TOP9, TOP0, BOT1, BOT2, BOT3, BOT4, BOT5, BOT6, BOT7, BOT8, BOT9, BOT0),
};
size_t keymapsCount = 1;

uint8_t keycodes_buffer_array[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

uint8_t command_buffer[] = {
    0, 0, 0, 0, 0
};

uint16_t leader_buffer[] = {
    0, 0, 0, 0, 0
};

uint8_t dynamic_macro_buffer[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

enum chord_states {
    IDLE,
    READY,
    ACTIVATED,
    DEACTIVATED,
    PRESS_FROM_ACTIVE,
    FINISHED_FROM_ACTIVE,
    IDLE_IN_DANCE,
    READY_IN_DANCE,
    FINISHED,
    LOCKED,
    READY_LOCKED,
    RESTART,
    IN_ONE_SHOT
};

struct Chord {
    uint32_t keycodes_hash;
    uint8_t pseudolayer;
    uint8_t* state;
    uint8_t* counter;
    uint16_t value1;
    uint8_t value2;
    void (*function) (const struct Chord*);
};

uint8_t current_pseudolayer = DEFAULT_PSEUDOLAYER;
bool lock_next = false;
uint16_t chord_timer = 0;
uint16_t dance_timer = 0;
bool autoshift_mode = true;
uint8_t keycode_index = 0;
uint8_t command_mode = 0;
uint8_t command_ind = 0;
bool in_leader_mode = false;
uint8_t leader_ind = 0;
uint16_t leader_timer = 0;
uint8_t dynamic_macro_mode = false;
uint8_t dynamic_macro_ind = 0;
bool a_key_went_through = false;
struct Chord* last_chord = NULL;

bool handle_US_ANSI_shifted_keys(int16_t keycode, bool in) {
    bool is_US_ANSI_shifted = true;
    
    int16_t regular_keycode = KC_NO;
    switch (keycode) {
        case KC_TILDE:
            regular_keycode = KC_GRAVE;
            break;
        case KC_EXCLAIM:
            regular_keycode = KC_1;
            break;
        case KC_AT:
            regular_keycode = KC_2;
            break;
        case KC_HASH:
            regular_keycode = KC_3;
            break;
        case KC_DOLLAR:
            regular_keycode = KC_4;
            break;
        case KC_PERCENT:
            regular_keycode = KC_5;
            break;
        case KC_CIRCUMFLEX:
            regular_keycode = KC_6;
            break;
        case KC_AMPERSAND:
            regular_keycode = KC_7;
            break;
        case KC_ASTERISK:
            regular_keycode = KC_8;
            break;
        case KC_LEFT_PAREN:
            regular_keycode = KC_9;
            break;
        case KC_RIGHT_PAREN:
            regular_keycode = KC_0;
            break;
        case KC_UNDERSCORE:
            regular_keycode = KC_MINUS;
            break;
        case KC_PLUS:
            regular_keycode = KC_EQUAL;
            break;
        case KC_LEFT_CURLY_BRACE:
            regular_keycode = KC_LBRACKET;
            break;
        case KC_RIGHT_CURLY_BRACE:
            regular_keycode = KC_RBRACKET;
            break;
        case KC_PIPE:
            regular_keycode = KC_BSLASH;
            break;
        case KC_COLON:
            regular_keycode = KC_SCOLON;
            break;
        case KC_DOUBLE_QUOTE:
            regular_keycode = KC_QUOTE;
            break;
        case KC_LEFT_ANGLE_BRACKET:
            regular_keycode = KC_COMMA;
            break;
        case KC_RIGHT_ANGLE_BRACKET:
            regular_keycode = KC_DOT;
            break;
        case KC_QUESTION:
            regular_keycode = KC_SLASH;
            break;
        default:
            is_US_ANSI_shifted = false;
    }
    if (is_US_ANSI_shifted) {
        if (in) {
            register_code(KC_LSFT);
            register_code(regular_keycode);
        } else {
            unregister_code(regular_keycode);
            unregister_code(KC_LSFT);
        }
    }
    return is_US_ANSI_shifted;
}

void key_in(int16_t keycode) {
    if (command_mode == 1 && command_ind < COMMAND_MAX_LENGTH) {
        command_buffer[command_ind] = keycode;
        command_ind++;
        a_key_went_through = true;
    } else if (in_leader_mode && leader_ind < LEADER_MAX_LENGTH) {
        leader_buffer[leader_ind] = keycode;
        leader_ind++;
        a_key_went_through = true;
    } else if (dynamic_macro_mode && dynamic_macro_ind < DYNAMIC_MACRO_MAX_LENGTH) {
        dynamic_macro_buffer[dynamic_macro_ind] = keycode;
        dynamic_macro_ind++;
        a_key_went_through = true;
    } else {
        if (!handle_US_ANSI_shifted_keys(keycode, true)) {
            register_code(keycode);
        }
        send_keyboard_report();
        a_key_went_through = true;
    }
}

void key_out(int16_t keycode) {
    if (command_mode == 0) {
        if (!handle_US_ANSI_shifted_keys(keycode, false)) {
            if (command_mode == 0 && in_leader_mode == false && dynamic_macro_mode == false) {
                unregister_code(keycode);
            }
        }
        send_keyboard_report();
    }
}

void tap_key(int16_t keycode) {
    key_in(keycode);
    wait_ms(TAP_TIMEOUT);
    key_out(keycode);
}
void single_dance(const struct Chord* self) {
    switch (*self->state) {
        case ACTIVATED:
            key_in(self->value1);
            break;
        case DEACTIVATED:
            key_out(self->value1);
            *self->state = IDLE;
            break;
        case RESTART:
            key_out(self->value1);
            break;
        default:
            break;
    }
}

void key_layer_dance(const struct Chord* self) {
    switch (*self->state) {
        case ACTIVATED:
            current_pseudolayer = self->value2;
            a_key_went_through = false;
            break;
        case DEACTIVATED:
        case RESTART:
            if (!a_key_went_through) {
                tap_key(self->value1);
            }
            current_pseudolayer = self->pseudolayer;
            *self->state = IDLE; // does not have effect if the state was RESTART
            break;
        default:
            break;
    }
}

void key_mod_dance(const struct Chord* self) {
    switch (*self->state) {
        case ACTIVATED:
            key_in(self->value2);
            a_key_went_through = false;
            break;
        case DEACTIVATED:
        case RESTART:
            key_out(self->value2);
            if (!a_key_went_through) {
                tap_key(self->value1);
            }
            *self->state = IDLE; // does not have effect if the state was RESTART
            break;
        default:
            break;
    }
}

void key_key_dance(const struct Chord* self) {
    switch (*self->state) {
        case ACTIVATED:
            break;
        case DEACTIVATED:
            tap_key(self->value1);
            *self->state = IDLE;
            break;
        case FINISHED:
        case PRESS_FROM_ACTIVE:
            key_in(self->value2);
            break;
        case RESTART:
            key_out(self->value2);
            break;
        default:
            break;
    }
}

void autoshift_dance_impl(const struct Chord* self) {
    switch (*self->state) {
        case ACTIVATED:
            *self->counter = 0;
            break;
        case DEACTIVATED:
        case RESTART:
            tap_key(self->value1);
            *self->state = IDLE;
            break;
        case FINISHED_FROM_ACTIVE:
            if (*self->counter == (LONG_PRESS_MULTIPLIER - 2)) {
                key_in(KC_LSFT);
                tap_key(self->value1);
                key_out(KC_LSFT);
                *self->state = IDLE;
                // the skip to IDLE is usually just a lag optimization,
                // in this case it has a logic function, on a short
                // press (still longer than a tap) the key does not get shifted
            } else {
                *self->counter += 1;
                *self->state = PRESS_FROM_ACTIVE;
                dance_timer = timer_read();
            }
            break;
        default:
            break;
    }
}

void autoshift_dance(const struct Chord* self) {
    if (autoshift_mode) {
        autoshift_dance_impl(self);
    } else {
        single_dance(self);
    }
}

void autoshift_toggle(const struct Chord* self){
    if (*self->state == ACTIVATED) {
        autoshift_mode = !autoshift_mode;
        *self->state = IDLE;
    }
}

void temp_pseudolayer(const struct Chord* self) {
    switch (*self->state) {
        case ACTIVATED:
            current_pseudolayer = self->value1;
            break;
        case DEACTIVATED:
            current_pseudolayer = self->pseudolayer;
            *self->state = IDLE;
            break;
        case RESTART:
            current_pseudolayer = self->pseudolayer;
            break;
        default:
            break;
    }
}

void perm_pseudolayer(const struct Chord* self) {
    if (*self->state == ACTIVATED) {
        current_pseudolayer = self->value1;
        *self->state = IDLE;
    }
}

void switch_layer(const struct Chord* self) {
    if (*self->state == ACTIVATED) {
        layer_move(self->value1);
        *self->state = IDLE;
    }
}

void lock(const struct Chord* self) {
    if (*self->state == ACTIVATED) {
        lock_next = true;
        *self->state = IDLE;
    }
}

void one_shot_key(const struct Chord* self) {
    switch (*self->state) {
        case ACTIVATED:
            break;
        case DEACTIVATED:
            key_in(self->value1);
            *self->state = IN_ONE_SHOT;
            break;
        case FINISHED:
        case PRESS_FROM_ACTIVE:
            key_in(self->value1);
            a_key_went_through = false;
            break;
        case RESTART:
            if (a_key_went_through) {
                key_out(self->value1);
            } else {
                *self->state = IN_ONE_SHOT;
            }
        default:
            break;
    }
}

void one_shot_layer(const struct Chord* self) {
    switch (*self->state) {
        case ACTIVATED:
            break;
        case DEACTIVATED:
            current_pseudolayer = self->value1;
            *self->state = IN_ONE_SHOT;
            break;
        case FINISHED:
        case PRESS_FROM_ACTIVE:
            current_pseudolayer = self->value1;
            a_key_went_through = false;
            break;
        case RESTART:
            if (a_key_went_through) {
                current_pseudolayer = self->pseudolayer;
            } else {
                *self->state = IN_ONE_SHOT;
            }
        default:
            break;
    }
}

void command(const struct Chord* self) {
    if (*self->state == ACTIVATED) {
        command_mode++;
        *self->state = IDLE;
    }
}

bool identical(uint16_t* buffer1, uint16_t* buffer2) {
    bool same = true;
    for (int i = 0; i < LEADER_MAX_LENGTH; i++) {
        same = same && (buffer1[i] == buffer2[i]);
    }
    return same;
}

void leader(const struct Chord* self) {
    if (*self->state == ACTIVATED) {
        in_leader_mode = true;
        *self->state = IDLE;
    }
}

void dynamic_macro_record(const struct Chord* self) {
    if (*self->state == ACTIVATED) {
        for (int i = 0; i < DYNAMIC_MACRO_MAX_LENGTH; i++) {
            dynamic_macro_buffer[i] = 0;
        }
        dynamic_macro_mode = true;
        *self->state = IDLE;
    }
}

void dynamic_macro_next(const struct Chord* self) {
    if (*self->state == ACTIVATED) {
        if (dynamic_macro_mode && dynamic_macro_ind < DYNAMIC_MACRO_MAX_LENGTH) {
            dynamic_macro_buffer[dynamic_macro_ind] = 0;
            dynamic_macro_ind++;
        }
        *self->state = IDLE;
    }
}

void dynamic_macro_end(const struct Chord* self) {
    if (*self->state == ACTIVATED) {
        if (dynamic_macro_mode) {
            dynamic_macro_mode = false;
        }
        *self->state = IDLE;
    }
}

void dynamic_macro_play(const struct Chord* self) {
    if (*self->state == ACTIVATED) {
        int ind_start = 0;
        while (ind_start < DYNAMIC_MACRO_MAX_LENGTH) {
            for (int i = ind_start; i < DYNAMIC_MACRO_MAX_LENGTH; i++) {
                if (dynamic_macro_buffer[i] == 0) {
                    break;
                }
                register_code(dynamic_macro_buffer[i]);
            }
            send_keyboard_report();
            wait_ms(TAP_TIMEOUT);
            for (int i = ind_start; i < DYNAMIC_MACRO_MAX_LENGTH; i++) {
                if (dynamic_macro_buffer[i] == 0) {
                    ind_start = i + 1;
                    break;
                }
                unregister_code(dynamic_macro_buffer[i]);
            }
            send_keyboard_report();
        }
        *self->state = IDLE;
    }
}

void clear(const struct Chord* self);

void reset_keyboard_kb(void){
#ifdef WATCHDOG_ENABLE
    MCUSR = 0;
    wdt_disable();
    wdt_reset();
#endif
    reset_keyboard();
}

void reset(const struct Chord* self) {
    if (*self->state == ACTIVATED) {
        reset_keyboard_kb();
    }
}

uint8_t state_0 = IDLE;
const struct Chord chord_0 PROGMEM = {H_TOP1 + H_TOP2 + H_BOT1 + H_BOT2, ALWAYS_ON, &state_0, NULL, 0, 0, lock};
uint8_t state_1 = IDLE;
const struct Chord chord_1 PROGMEM = {H_TOP2 + H_TOP3 + H_BOT2 + H_BOT3, ALWAYS_ON, &state_1, NULL, 0, 0, autoshift_toggle};
uint8_t state_2 = IDLE;
const struct Chord chord_2 PROGMEM = {H_TOP5 + H_TOP6 + H_BOT5 + H_BOT6, ALWAYS_ON, &state_2, NULL, 0, 0, command};
uint8_t state_3 = IDLE;
const struct Chord chord_3 PROGMEM = {H_TOP1 + H_TOP2 + H_TOP9 + H_TOP0 + H_BOT1 + H_BOT2 + H_BOT9 + H_BOT0, ALWAYS_ON, &state_3, NULL, 0, 0, clear};
uint8_t state_4 = IDLE;
uint8_t counter_4 = 0;
const struct Chord chord_4 PROGMEM = {H_TOP1, QWERTY, &state_4, &counter_4, KC_Q, 0, autoshift_dance};
uint8_t state_5 = IDLE;
uint8_t counter_5 = 0;
const struct Chord chord_5 PROGMEM = {H_TOP2, QWERTY, &state_5, &counter_5, KC_W, 0, autoshift_dance};
uint8_t state_6 = IDLE;
uint8_t counter_6 = 0;
const struct Chord chord_6 PROGMEM = {H_TOP3, QWERTY, &state_6, &counter_6, KC_E, 0, autoshift_dance};
uint8_t state_7 = IDLE;
uint8_t counter_7 = 0;
const struct Chord chord_7 PROGMEM = {H_TOP4, QWERTY, &state_7, &counter_7, KC_R, 0, autoshift_dance};
uint8_t state_8 = IDLE;
uint8_t counter_8 = 0;
const struct Chord chord_8 PROGMEM = {H_TOP5, QWERTY, &state_8, &counter_8, KC_T, 0, autoshift_dance};
uint8_t state_9 = IDLE;
uint8_t counter_9 = 0;
const struct Chord chord_9 PROGMEM = {H_TOP6, QWERTY, &state_9, &counter_9, KC_Y, 0, autoshift_dance};
uint8_t state_10 = IDLE;
uint8_t counter_10 = 0;
const struct Chord chord_10 PROGMEM = {H_TOP7, QWERTY, &state_10, &counter_10, KC_U, 0, autoshift_dance};
uint8_t state_11 = IDLE;
uint8_t counter_11 = 0;
const struct Chord chord_11 PROGMEM = {H_TOP8, QWERTY, &state_11, &counter_11, KC_I, 0, autoshift_dance};
uint8_t state_12 = IDLE;
uint8_t counter_12 = 0;
const struct Chord chord_12 PROGMEM = {H_TOP9, QWERTY, &state_12, &counter_12, KC_O, 0, autoshift_dance};
uint8_t state_13 = IDLE;
uint8_t counter_13 = 0;
const struct Chord chord_13 PROGMEM = {H_TOP0, QWERTY, &state_13, &counter_13, KC_P, 0, autoshift_dance};
uint8_t state_14 = IDLE;
uint8_t counter_14 = 0;
const struct Chord chord_14 PROGMEM = {H_TOP1 + H_BOT1, QWERTY, &state_14, &counter_14, KC_A, 0, autoshift_dance};
uint8_t state_15 = IDLE;
uint8_t counter_15 = 0;
const struct Chord chord_15 PROGMEM = {H_TOP2 + H_BOT2, QWERTY, &state_15, &counter_15, KC_S, 0, autoshift_dance};
uint8_t state_16 = IDLE;
uint8_t counter_16 = 0;
const struct Chord chord_16 PROGMEM = {H_TOP3 + H_BOT3, QWERTY, &state_16, &counter_16, KC_D, 0, autoshift_dance};
uint8_t state_17 = IDLE;
uint8_t counter_17 = 0;
const struct Chord chord_17 PROGMEM = {H_TOP4 + H_BOT4, QWERTY, &state_17, &counter_17, KC_F, 0, autoshift_dance};
uint8_t state_18 = IDLE;
uint8_t counter_18 = 0;
const struct Chord chord_18 PROGMEM = {H_TOP5 + H_BOT5, QWERTY, &state_18, &counter_18, KC_G, 0, autoshift_dance};
uint8_t state_19 = IDLE;
uint8_t counter_19 = 0;
const struct Chord chord_19 PROGMEM = {H_TOP6 + H_BOT6, QWERTY, &state_19, &counter_19, KC_H, 0, autoshift_dance};
uint8_t state_20 = IDLE;
uint8_t counter_20 = 0;
const struct Chord chord_20 PROGMEM = {H_TOP7 + H_BOT7, QWERTY, &state_20, &counter_20, KC_J, 0, autoshift_dance};
uint8_t state_21 = IDLE;
uint8_t counter_21 = 0;
const struct Chord chord_21 PROGMEM = {H_TOP8 + H_BOT8, QWERTY, &state_21, &counter_21, KC_K, 0, autoshift_dance};
uint8_t state_22 = IDLE;
uint8_t counter_22 = 0;
const struct Chord chord_22 PROGMEM = {H_TOP9 + H_BOT9, QWERTY, &state_22, &counter_22, KC_L, 0, autoshift_dance};
uint8_t state_23 = IDLE;
uint8_t counter_23 = 0;
const struct Chord chord_23 PROGMEM = {H_TOP0 + H_BOT0, QWERTY, &state_23, &counter_23, KC_SCOLON, 0, autoshift_dance};
uint8_t state_24 = IDLE;
uint8_t counter_24 = 0;
const struct Chord chord_24 PROGMEM = {H_BOT1, QWERTY, &state_24, &counter_24, KC_Z, 0, autoshift_dance};
uint8_t state_25 = IDLE;
uint8_t counter_25 = 0;
const struct Chord chord_25 PROGMEM = {H_BOT2, QWERTY, &state_25, &counter_25, KC_X, 0, autoshift_dance};
uint8_t state_26 = IDLE;
uint8_t counter_26 = 0;
const struct Chord chord_26 PROGMEM = {H_BOT3, QWERTY, &state_26, &counter_26, KC_C, 0, autoshift_dance};
uint8_t state_27 = IDLE;
uint8_t counter_27 = 0;
const struct Chord chord_27 PROGMEM = {H_BOT4, QWERTY, &state_27, &counter_27, KC_V, 0, autoshift_dance};
uint8_t state_28 = IDLE;
uint8_t counter_28 = 0;
const struct Chord chord_28 PROGMEM = {H_BOT5, QWERTY, &state_28, &counter_28, KC_B, 0, autoshift_dance};
uint8_t state_29 = IDLE;
uint8_t counter_29 = 0;
const struct Chord chord_29 PROGMEM = {H_BOT6, QWERTY, &state_29, &counter_29, KC_N, 0, autoshift_dance};
uint8_t state_30 = IDLE;
uint8_t counter_30 = 0;
const struct Chord chord_30 PROGMEM = {H_BOT7, QWERTY, &state_30, &counter_30, KC_M, 0, autoshift_dance};
uint8_t state_31 = IDLE;
uint8_t counter_31 = 0;
const struct Chord chord_31 PROGMEM = {H_BOT8, QWERTY, &state_31, &counter_31, KC_COMMA, 0, autoshift_dance};
uint8_t state_32 = IDLE;
uint8_t counter_32 = 0;
const struct Chord chord_32 PROGMEM = {H_BOT9, QWERTY, &state_32, &counter_32, KC_DOT, 0, autoshift_dance};
uint8_t state_33 = IDLE;
uint8_t counter_33 = 0;
const struct Chord chord_33 PROGMEM = {H_BOT0, QWERTY, &state_33, &counter_33, KC_SLASH, 0, autoshift_dance};
uint8_t state_34 = IDLE;
const struct Chord chord_34 PROGMEM = {H_TOP1 + H_TOP2, QWERTY, &state_34, NULL, KC_ESC, 0, single_dance};
uint8_t state_35 = IDLE;
const struct Chord chord_35 PROGMEM = {H_TOP2 + H_TOP3, QWERTY, &state_35, NULL, MOV, 0, temp_pseudolayer};
uint8_t state_36 = IDLE;
const struct Chord chord_36 PROGMEM = {H_TOP3 + H_TOP4, QWERTY, &state_36, NULL, KC_TAB, 0, single_dance};
uint8_t state_37 = IDLE;
const struct Chord chord_37 PROGMEM = {H_TOP5 + H_TOP6, QWERTY, &state_37, NULL, KC_RGUI, 0, one_shot_key};
uint8_t state_38 = IDLE;
const struct Chord chord_38 PROGMEM = {H_TOP7 + H_TOP8, QWERTY, &state_38, NULL, KC_INS, 0, single_dance};
uint8_t state_39 = IDLE;
const struct Chord chord_39 PROGMEM = {H_TOP8 + H_TOP9, QWERTY, &state_39, NULL, KC_DEL, 0, single_dance};
uint8_t state_40 = IDLE;
const struct Chord chord_40 PROGMEM = {H_TOP9 + H_TOP0, QWERTY, &state_40, NULL, KC_BSPC, 0, single_dance};
uint8_t state_41 = IDLE;
const struct Chord chord_41 PROGMEM = {H_TOP9 + H_TOP0 + H_BOT9 + H_BOT0, QWERTY, &state_41, NULL, KC_ENTER, 0, single_dance};
uint8_t state_42 = IDLE;
const struct Chord chord_42 PROGMEM = {H_BOT1 + H_BOT2, QWERTY, &state_42, NULL, KC_LSFT, 0, one_shot_key};
uint8_t state_43 = IDLE;
const struct Chord chord_43 PROGMEM = {H_BOT2 + H_BOT3, QWERTY, &state_43, NULL, KC_LCTL, 0, one_shot_key};
uint8_t state_44 = IDLE;
const struct Chord chord_44 PROGMEM = {H_BOT3 + H_BOT4, QWERTY, &state_44, NULL, KC_LALT, 0, one_shot_key};
uint8_t state_45 = IDLE;
const struct Chord chord_45 PROGMEM = {H_BOT4 + H_BOT5, QWERTY, &state_45, NULL, NUM, 0, one_shot_layer};
uint8_t state_46 = IDLE;
const struct Chord chord_46 PROGMEM = {H_BOT5 + H_BOT6, QWERTY, &state_46, NULL, KC_LGUI, 0, one_shot_key};
uint8_t state_47 = IDLE;
const struct Chord chord_47 PROGMEM = {H_BOT6 + H_BOT7, QWERTY, &state_47, NULL, NUM, 0, one_shot_layer};
uint8_t state_48 = IDLE;
const struct Chord chord_48 PROGMEM = {H_BOT7 + H_BOT8, QWERTY, &state_48, NULL, KC_RALT, 0, one_shot_key};
uint8_t state_49 = IDLE;
const struct Chord chord_49 PROGMEM = {H_BOT8 + H_BOT9, QWERTY, &state_49, NULL, KC_RCTL, 0, one_shot_key};
uint8_t state_50 = IDLE;
const struct Chord chord_50 PROGMEM = {H_BOT9 + H_BOT0, QWERTY, &state_50, NULL, KC_RSFT, 0, one_shot_key};
uint8_t state_51 = IDLE;
const struct Chord chord_51 PROGMEM = {H_BOT1 + H_BOT0, QWERTY, &state_51, NULL, KC_SPACE, 0, single_dance};
uint8_t state_52 = IDLE;
const struct Chord chord_52 PROGMEM = {H_TOP1 + H_TOP2 + H_TOP3 + H_TOP4, QWERTY, &state_52, NULL, MOUSE, 0, temp_pseudolayer};
uint8_t state_53 = IDLE;
const struct Chord chord_53 PROGMEM = {H_TOP1 + H_TOP2 + H_TOP3 + H_TOP4, QWERTY, &state_53, NULL, ASETNIOP, 0, perm_pseudolayer};
uint8_t state_54 = IDLE;
uint8_t counter_54 = 0;
const struct Chord chord_54 PROGMEM = {H_TOP1, NUM, &state_54, &counter_54, KC_1, 0, autoshift_dance};
uint8_t state_55 = IDLE;
uint8_t counter_55 = 0;
const struct Chord chord_55 PROGMEM = {H_TOP2, NUM, &state_55, &counter_55, KC_2, 0, autoshift_dance};
uint8_t state_56 = IDLE;
uint8_t counter_56 = 0;
const struct Chord chord_56 PROGMEM = {H_TOP3, NUM, &state_56, &counter_56, KC_3, 0, autoshift_dance};
uint8_t state_57 = IDLE;
uint8_t counter_57 = 0;
const struct Chord chord_57 PROGMEM = {H_TOP4, NUM, &state_57, &counter_57, KC_4, 0, autoshift_dance};
uint8_t state_58 = IDLE;
uint8_t counter_58 = 0;
const struct Chord chord_58 PROGMEM = {H_TOP5, NUM, &state_58, &counter_58, KC_5, 0, autoshift_dance};
uint8_t state_59 = IDLE;
uint8_t counter_59 = 0;
const struct Chord chord_59 PROGMEM = {H_TOP6, NUM, &state_59, &counter_59, KC_6, 0, autoshift_dance};
uint8_t state_60 = IDLE;
uint8_t counter_60 = 0;
const struct Chord chord_60 PROGMEM = {H_TOP7, NUM, &state_60, &counter_60, KC_7, 0, autoshift_dance};
uint8_t state_61 = IDLE;
uint8_t counter_61 = 0;
const struct Chord chord_61 PROGMEM = {H_TOP8, NUM, &state_61, &counter_61, KC_8, 0, autoshift_dance};
uint8_t state_62 = IDLE;
uint8_t counter_62 = 0;
const struct Chord chord_62 PROGMEM = {H_TOP9, NUM, &state_62, &counter_62, KC_9, 0, autoshift_dance};
uint8_t state_63 = IDLE;
uint8_t counter_63 = 0;
const struct Chord chord_63 PROGMEM = {H_TOP0, NUM, &state_63, &counter_63, KC_0, 0, autoshift_dance};
uint8_t state_64 = IDLE;
const struct Chord chord_64 PROGMEM = {H_TOP1 + H_BOT1, NUM, &state_64, NULL, KC_F1, 0, single_dance};
uint8_t state_65 = IDLE;
const struct Chord chord_65 PROGMEM = {H_TOP2 + H_BOT2, NUM, &state_65, NULL, KC_F2, 0, single_dance};
uint8_t state_66 = IDLE;
const struct Chord chord_66 PROGMEM = {H_TOP3 + H_BOT3, NUM, &state_66, NULL, KC_F3, 0, single_dance};
uint8_t state_67 = IDLE;
const struct Chord chord_67 PROGMEM = {H_TOP4 + H_BOT4, NUM, &state_67, NULL, KC_F4, 0, single_dance};
uint8_t state_68 = IDLE;
const struct Chord chord_68 PROGMEM = {H_TOP5 + H_BOT5, NUM, &state_68, NULL, KC_F5, 0, single_dance};
uint8_t state_69 = IDLE;
const struct Chord chord_69 PROGMEM = {H_TOP6 + H_BOT6, NUM, &state_69, NULL, KC_F6, 0, single_dance};
uint8_t state_70 = IDLE;
const struct Chord chord_70 PROGMEM = {H_TOP7 + H_BOT7, NUM, &state_70, NULL, KC_F7, 0, single_dance};
uint8_t state_71 = IDLE;
const struct Chord chord_71 PROGMEM = {H_TOP8 + H_BOT8, NUM, &state_71, NULL, KC_F8, 0, single_dance};
uint8_t state_72 = IDLE;
const struct Chord chord_72 PROGMEM = {H_TOP9 + H_BOT9, NUM, &state_72, NULL, KC_F9, 0, single_dance};
uint8_t state_73 = IDLE;
const struct Chord chord_73 PROGMEM = {H_TOP0 + H_BOT0, NUM, &state_73, NULL, KC_F10, 0, single_dance};
uint8_t state_74 = IDLE;
uint8_t counter_74 = 0;
const struct Chord chord_74 PROGMEM = {H_BOT1, NUM, &state_74, &counter_74, KC_GRAVE, 0, autoshift_dance};
uint8_t state_75 = IDLE;
uint8_t counter_75 = 0;
const struct Chord chord_75 PROGMEM = {H_BOT2, NUM, &state_75, &counter_75, KC_MINUS, 0, autoshift_dance};
uint8_t state_76 = IDLE;
uint8_t counter_76 = 0;
const struct Chord chord_76 PROGMEM = {H_BOT3, NUM, &state_76, &counter_76, KC_EQUAL, 0, autoshift_dance};
uint8_t state_77 = IDLE;
uint8_t counter_77 = 0;
const struct Chord chord_77 PROGMEM = {H_BOT4, NUM, &state_77, &counter_77, KC_LBRACKET, 0, autoshift_dance};
uint8_t state_78 = IDLE;
uint8_t counter_78 = 0;
const struct Chord chord_78 PROGMEM = {H_BOT5, NUM, &state_78, &counter_78, KC_RBRACKET, 0, autoshift_dance};
uint8_t state_79 = IDLE;
uint8_t counter_79 = 0;
const struct Chord chord_79 PROGMEM = {H_BOT6, NUM, &state_79, &counter_79, KC_BSLASH, 0, autoshift_dance};
uint8_t state_80 = IDLE;
uint8_t counter_80 = 0;
const struct Chord chord_80 PROGMEM = {H_BOT7, NUM, &state_80, &counter_80, KC_QUOTE, 0, autoshift_dance};
uint8_t state_81 = IDLE;
const struct Chord chord_81 PROGMEM = {H_BOT9, NUM, &state_81, NULL, KC_F11, 0, single_dance};
uint8_t state_82 = IDLE;
const struct Chord chord_82 PROGMEM = {H_BOT0, NUM, &state_82, NULL, KC_F12, 0, single_dance};
uint8_t state_83 = IDLE;
const struct Chord chord_83 PROGMEM = {H_TOP1 + H_TOP2, NUM, &state_83, NULL, KC_ESC, 0, single_dance};
uint8_t state_84 = IDLE;
const struct Chord chord_84 PROGMEM = {H_TOP3 + H_TOP4, NUM, &state_84, NULL, KC_TAB, 0, single_dance};
uint8_t state_85 = IDLE;
const struct Chord chord_85 PROGMEM = {H_TOP5 + H_TOP6, NUM, &state_85, NULL, KC_RGUI, 0, one_shot_key};
uint8_t state_86 = IDLE;
const struct Chord chord_86 PROGMEM = {H_TOP7 + H_TOP8, NUM, &state_86, NULL, KC_INS, 0, single_dance};
uint8_t state_87 = IDLE;
const struct Chord chord_87 PROGMEM = {H_TOP8 + H_TOP9, NUM, &state_87, NULL, KC_DEL, 0, single_dance};
uint8_t state_88 = IDLE;
const struct Chord chord_88 PROGMEM = {H_TOP9 + H_TOP0, NUM, &state_88, NULL, KC_BSPC, 0, single_dance};
uint8_t state_89 = IDLE;
const struct Chord chord_89 PROGMEM = {H_TOP9 + H_TOP0 + H_BOT9 + H_BOT0, NUM, &state_89, NULL, KC_ENTER, 0, single_dance};
uint8_t state_90 = IDLE;
const struct Chord chord_90 PROGMEM = {H_BOT1 + H_BOT2, NUM, &state_90, NULL, KC_LSFT, 0, one_shot_key};
uint8_t state_91 = IDLE;
const struct Chord chord_91 PROGMEM = {H_BOT2 + H_BOT3, NUM, &state_91, NULL, KC_LCTL, 0, one_shot_key};
uint8_t state_92 = IDLE;
const struct Chord chord_92 PROGMEM = {H_BOT3 + H_BOT4, NUM, &state_92, NULL, KC_LALT, 0, one_shot_key};
uint8_t state_93 = IDLE;
const struct Chord chord_93 PROGMEM = {H_BOT5 + H_BOT6, NUM, &state_93, NULL, KC_LGUI, 0, one_shot_key};
uint8_t state_94 = IDLE;
const struct Chord chord_94 PROGMEM = {H_BOT7 + H_BOT8, NUM, &state_94, NULL, KC_RALT, 0, one_shot_key};
uint8_t state_95 = IDLE;
const struct Chord chord_95 PROGMEM = {H_BOT8 + H_BOT9, NUM, &state_95, NULL, KC_RCTL, 0, one_shot_key};
uint8_t state_96 = IDLE;
const struct Chord chord_96 PROGMEM = {H_BOT9 + H_BOT0, NUM, &state_96, NULL, KC_RSFT, 0, one_shot_key};
uint8_t state_97 = IDLE;
const struct Chord chord_97 PROGMEM = {H_BOT1 + H_BOT0, NUM, &state_97, NULL, KC_SPACE, 0, single_dance};
uint8_t state_98 = IDLE;
const struct Chord chord_98 PROGMEM = {H_TOP7, MOV, &state_98, NULL, KC_HOME, 0, single_dance};
uint8_t state_99 = IDLE;
const struct Chord chord_99 PROGMEM = {H_TOP8, MOV, &state_99, NULL, KC_UP, 0, single_dance};
uint8_t state_100 = IDLE;
const struct Chord chord_100 PROGMEM = {H_TOP9, MOV, &state_100, NULL, KC_END, 0, single_dance};
uint8_t state_101 = IDLE;
const struct Chord chord_101 PROGMEM = {H_TOP0, MOV, &state_101, NULL, KC_PGUP, 0, single_dance};
uint8_t state_102 = IDLE;
const struct Chord chord_102 PROGMEM = {H_BOT3, MOV, &state_102, NULL, KC_LSFT, 0, single_dance};
uint8_t state_103 = IDLE;
const struct Chord chord_103 PROGMEM = {H_BOT4, MOV, &state_103, NULL, KC_LCTL, 0, single_dance};
uint8_t state_104 = IDLE;
const struct Chord chord_104 PROGMEM = {H_BOT5, MOV, &state_104, NULL, KC_LALT, 0, single_dance};
uint8_t state_105 = IDLE;
const struct Chord chord_105 PROGMEM = {H_BOT6, MOV, &state_105, NULL, KC_LGUI, 0, single_dance};
uint8_t state_106 = IDLE;
const struct Chord chord_106 PROGMEM = {H_BOT7, MOV, &state_106, NULL, KC_LEFT, 0, single_dance};
uint8_t state_107 = IDLE;
const struct Chord chord_107 PROGMEM = {H_BOT8, MOV, &state_107, NULL, KC_DOWN, 0, single_dance};
uint8_t state_108 = IDLE;
const struct Chord chord_108 PROGMEM = {H_BOT9, MOV, &state_108, NULL, KC_RIGHT, 0, single_dance};
uint8_t state_109 = IDLE;
const struct Chord chord_109 PROGMEM = {H_BOT0, MOV, &state_109, NULL, KC_PGDN, 0, single_dance};
uint8_t state_110 = IDLE;
const struct Chord chord_110 PROGMEM = {H_TOP7, MOUSE, &state_110, NULL, KC_BTN1, 0, single_dance};
uint8_t state_111 = IDLE;
const struct Chord chord_111 PROGMEM = {H_TOP8, MOUSE, &state_111, NULL, KC_MS_U, 0, single_dance};
uint8_t state_112 = IDLE;
const struct Chord chord_112 PROGMEM = {H_TOP9, MOUSE, &state_112, NULL, KC_BTN2, 0, single_dance};
uint8_t state_113 = IDLE;
const struct Chord chord_113 PROGMEM = {H_TOP0, MOUSE, &state_113, NULL, KC_WH_U, 0, single_dance};
uint8_t state_114 = IDLE;
const struct Chord chord_114 PROGMEM = {H_BOT3, MOUSE, &state_114, NULL, KC_LSFT, 0, single_dance};
uint8_t state_115 = IDLE;
const struct Chord chord_115 PROGMEM = {H_BOT4, MOUSE, &state_115, NULL, KC_LCTL, 0, single_dance};
uint8_t state_116 = IDLE;
const struct Chord chord_116 PROGMEM = {H_BOT5, MOUSE, &state_116, NULL, KC_LALT, 0, single_dance};
uint8_t state_117 = IDLE;
const struct Chord chord_117 PROGMEM = {H_BOT6, MOUSE, &state_117, NULL, KC_LGUI, 0, single_dance};
uint8_t state_118 = IDLE;
const struct Chord chord_118 PROGMEM = {H_BOT7, MOUSE, &state_118, NULL, KC_MS_L, 0, single_dance};
uint8_t state_119 = IDLE;
const struct Chord chord_119 PROGMEM = {H_BOT8, MOUSE, &state_119, NULL, KC_MS_D, 0, single_dance};
uint8_t state_120 = IDLE;
const struct Chord chord_120 PROGMEM = {H_BOT9, MOUSE, &state_120, NULL, KC_MS_R, 0, single_dance};
uint8_t state_121 = IDLE;
const struct Chord chord_121 PROGMEM = {H_BOT0, MOUSE, &state_121, NULL, KC_WH_D, 0, single_dance};
uint8_t state_122 = IDLE;
const struct Chord chord_122 PROGMEM = {H_TOP1, ASETNIOP, &state_122, NULL, KC_A, 0, single_dance};
uint8_t state_123 = IDLE;
const struct Chord chord_123 PROGMEM = {H_TOP2, ASETNIOP, &state_123, NULL, KC_S, 0, single_dance};
uint8_t state_124 = IDLE;
const struct Chord chord_124 PROGMEM = {H_TOP3, ASETNIOP, &state_124, NULL, KC_E, 0, single_dance};
uint8_t state_125 = IDLE;
const struct Chord chord_125 PROGMEM = {H_TOP4, ASETNIOP, &state_125, NULL, KC_T, 0, single_dance};
uint8_t state_126 = IDLE;
const struct Chord chord_126 PROGMEM = {H_TOP7, ASETNIOP, &state_126, NULL, KC_N, 0, single_dance};
uint8_t state_127 = IDLE;
const struct Chord chord_127 PROGMEM = {H_TOP8, ASETNIOP, &state_127, NULL, KC_I, 0, single_dance};
uint8_t state_128 = IDLE;
const struct Chord chord_128 PROGMEM = {H_TOP9, ASETNIOP, &state_128, NULL, KC_O, 0, single_dance};
uint8_t state_129 = IDLE;
const struct Chord chord_129 PROGMEM = {H_TOP0, ASETNIOP, &state_129, NULL, KC_P, 0, single_dance};
uint8_t state_130 = IDLE;
const struct Chord chord_130 PROGMEM = {H_TOP1 + H_TOP2, ASETNIOP, &state_130, NULL, KC_W, 0, single_dance};
uint8_t state_131 = IDLE;
const struct Chord chord_131 PROGMEM = {H_TOP2 + H_TOP3, ASETNIOP, &state_131, NULL, KC_D, 0, single_dance};
uint8_t state_132 = IDLE;
const struct Chord chord_132 PROGMEM = {H_TOP3 + H_TOP4, ASETNIOP, &state_132, NULL, KC_R, 0, single_dance};
uint8_t state_133 = IDLE;
const struct Chord chord_133 PROGMEM = {H_TOP4 + H_TOP7, ASETNIOP, &state_133, NULL, KC_B, 0, single_dance};
uint8_t state_134 = IDLE;
const struct Chord chord_134 PROGMEM = {H_TOP7 + H_TOP8, ASETNIOP, &state_134, NULL, KC_H, 0, single_dance};
uint8_t state_135 = IDLE;
const struct Chord chord_135 PROGMEM = {H_TOP8 + H_TOP9, ASETNIOP, &state_135, NULL, KC_L, 0, single_dance};
uint8_t state_136 = IDLE;
const struct Chord chord_136 PROGMEM = {H_TOP9 + H_TOP0, ASETNIOP, &state_136, NULL, KC_SCOLON, 0, single_dance};
uint8_t state_137 = IDLE;
const struct Chord chord_137 PROGMEM = {H_TOP1 + H_TOP3, ASETNIOP, &state_137, NULL, KC_X, 0, single_dance};
uint8_t state_138 = IDLE;
const struct Chord chord_138 PROGMEM = {H_TOP2 + H_TOP4, ASETNIOP, &state_138, NULL, KC_C, 0, single_dance};
uint8_t state_139 = IDLE;
const struct Chord chord_139 PROGMEM = {H_TOP3 + H_TOP7, ASETNIOP, &state_139, NULL, KC_Y, 0, single_dance};
uint8_t state_140 = IDLE;
const struct Chord chord_140 PROGMEM = {H_TOP4 + H_TOP8, ASETNIOP, &state_140, NULL, KC_V, 0, single_dance};
uint8_t state_141 = IDLE;
const struct Chord chord_141 PROGMEM = {H_TOP7 + H_TOP9, ASETNIOP, &state_141, NULL, KC_U, 0, single_dance};
uint8_t state_142 = IDLE;
const struct Chord chord_142 PROGMEM = {H_TOP1 + H_TOP4, ASETNIOP, &state_142, NULL, KC_F, 0, single_dance};
uint8_t state_143 = IDLE;
const struct Chord chord_143 PROGMEM = {H_TOP2 + H_TOP7, ASETNIOP, &state_143, NULL, KC_J, 0, single_dance};
uint8_t state_144 = IDLE;
const struct Chord chord_144 PROGMEM = {H_TOP3 + H_TOP8, ASETNIOP, &state_144, NULL, KC_COMMA, 0, single_dance};
uint8_t state_145 = IDLE;
const struct Chord chord_145 PROGMEM = {H_TOP4 + H_TOP9, ASETNIOP, &state_145, NULL, KC_G, 0, single_dance};
uint8_t state_146 = IDLE;
const struct Chord chord_146 PROGMEM = {H_TOP7 + H_TOP0, ASETNIOP, &state_146, NULL, KC_M, 0, single_dance};
uint8_t state_147 = IDLE;
const struct Chord chord_147 PROGMEM = {H_TOP1 + H_TOP7, ASETNIOP, &state_147, NULL, KC_Q, 0, single_dance};
uint8_t state_148 = IDLE;
const struct Chord chord_148 PROGMEM = {H_TOP2 + H_TOP8, ASETNIOP, &state_148, NULL, KC_K, 0, single_dance};
uint8_t state_149 = IDLE;
const struct Chord chord_149 PROGMEM = {H_TOP3 + H_TOP9, ASETNIOP, &state_149, NULL, KC_MINUS, 0, single_dance};
uint8_t state_150 = IDLE;
const struct Chord chord_150 PROGMEM = {H_TOP4 + H_TOP0, ASETNIOP, &state_150, NULL, KC_BSPC, 0, single_dance};
uint8_t state_151 = IDLE;
const struct Chord chord_151 PROGMEM = {H_TOP1 + H_TOP8, ASETNIOP, &state_151, NULL, KC_Z, 0, single_dance};
uint8_t state_152 = IDLE;
const struct Chord chord_152 PROGMEM = {H_TOP2 + H_TOP9, ASETNIOP, &state_152, NULL, KC_DOT, 0, single_dance};
uint8_t state_153 = IDLE;
const struct Chord chord_153 PROGMEM = {H_TOP3 + H_TOP0, ASETNIOP, &state_153, NULL, KC_QUOTE, 0, single_dance};
uint8_t state_154 = IDLE;
const struct Chord chord_154 PROGMEM = {H_TOP1 + H_TOP9, ASETNIOP, &state_154, NULL, KC_LBRACKET, 0, single_dance};
uint8_t state_155 = IDLE;
const struct Chord chord_155 PROGMEM = {H_TOP2 + H_TOP0, ASETNIOP, &state_155, NULL, KC_RBRACKET, 0, single_dance};
uint8_t state_156 = IDLE;
const struct Chord chord_156 PROGMEM = {H_TOP1 + H_TOP0, ASETNIOP, &state_156, NULL, KC_SLASH, 0, single_dance};
uint8_t state_157 = IDLE;
const struct Chord chord_157 PROGMEM = {H_TOP5, ASETNIOP, &state_157, NULL, KC_ESC, 0, single_dance};
uint8_t state_158 = IDLE;
const struct Chord chord_158 PROGMEM = {H_TOP6, ASETNIOP, &state_158, NULL, KC_DEL, 0, single_dance};
uint8_t state_159 = IDLE;
const struct Chord chord_159 PROGMEM = {H_BOT4, ASETNIOP, &state_159, NULL, KC_LSFT, 0, single_dance};
uint8_t state_160 = IDLE;
const struct Chord chord_160 PROGMEM = {H_BOT5, ASETNIOP, &state_160, NULL, KC_LCTL, 0, single_dance};
uint8_t state_161 = IDLE;
const struct Chord chord_161 PROGMEM = {H_BOT6, ASETNIOP, &state_161, NULL, KC_LALT, 0, single_dance};
uint8_t state_162 = IDLE;
uint8_t counter_162 = 0;
const struct Chord chord_162 PROGMEM = {H_BOT7, ASETNIOP, &state_162, &counter_162, KC_SPACE, ASETNIOP_123, key_layer_dance};
uint8_t state_163 = IDLE;
const struct Chord chord_163 PROGMEM = {H_TOP5 + H_TOP6, ASETNIOP, &state_163, NULL, KC_LGUI, 0, single_dance};
uint8_t state_164 = IDLE;
const struct Chord chord_164 PROGMEM = {H_TOP1 + H_TOP2 + H_TOP3 + H_TOP4, ASETNIOP, &state_164, NULL, QWERTY, 0, perm_pseudolayer};
uint8_t state_165 = IDLE;
const struct Chord chord_165 PROGMEM = {H_BOT4 + H_BOT7, ASETNIOP, &state_165, NULL, ASETNIOP_FN, 0, temp_pseudolayer};
uint8_t state_166 = IDLE;
const struct Chord chord_166 PROGMEM = {H_TOP1, ASETNIOP_123, &state_166, NULL, KC_1, 0, single_dance};
uint8_t state_167 = IDLE;
const struct Chord chord_167 PROGMEM = {H_TOP2, ASETNIOP_123, &state_167, NULL, KC_2, 0, single_dance};
uint8_t state_168 = IDLE;
const struct Chord chord_168 PROGMEM = {H_TOP3, ASETNIOP_123, &state_168, NULL, KC_3, 0, single_dance};
uint8_t state_169 = IDLE;
const struct Chord chord_169 PROGMEM = {H_TOP4, ASETNIOP_123, &state_169, NULL, KC_4, 0, single_dance};
uint8_t state_170 = IDLE;
const struct Chord chord_170 PROGMEM = {H_TOP7, ASETNIOP_123, &state_170, NULL, KC_7, 0, single_dance};
uint8_t state_171 = IDLE;
const struct Chord chord_171 PROGMEM = {H_TOP8, ASETNIOP_123, &state_171, NULL, KC_8, 0, single_dance};
uint8_t state_172 = IDLE;
const struct Chord chord_172 PROGMEM = {H_TOP9, ASETNIOP_123, &state_172, NULL, KC_9, 0, single_dance};
uint8_t state_173 = IDLE;
const struct Chord chord_173 PROGMEM = {H_TOP0, ASETNIOP_123, &state_173, NULL, KC_0, 0, single_dance};
uint8_t state_174 = IDLE;
const struct Chord chord_174 PROGMEM = {H_TOP3 + H_TOP4, ASETNIOP_123, &state_174, NULL, KC_5, 0, single_dance};
uint8_t state_175 = IDLE;
const struct Chord chord_175 PROGMEM = {H_TOP4 + H_TOP7, ASETNIOP_123, &state_175, NULL, KC_EQUAL, 0, single_dance};
uint8_t state_176 = IDLE;
const struct Chord chord_176 PROGMEM = {H_TOP7 + H_TOP8, ASETNIOP_123, &state_176, NULL, KC_6, 0, single_dance};
uint8_t state_177 = IDLE;
const struct Chord chord_177 PROGMEM = {H_TOP8 + H_TOP9, ASETNIOP_123, &state_177, NULL, KC_BSLASH, 0, single_dance};
uint8_t state_178 = IDLE;
const struct Chord chord_178 PROGMEM = {H_TOP9 + H_TOP0, ASETNIOP_123, &state_178, NULL, KC_SCOLON, 0, single_dance};
uint8_t state_179 = IDLE;
const struct Chord chord_179 PROGMEM = {H_TOP4 + H_TOP0, ASETNIOP_123, &state_179, NULL, KC_BSPC, 0, single_dance};
uint8_t state_180 = IDLE;
const struct Chord chord_180 PROGMEM = {H_TOP5, ASETNIOP_123, &state_180, NULL, KC_ESC, 0, single_dance};
uint8_t state_181 = IDLE;
const struct Chord chord_181 PROGMEM = {H_TOP6, ASETNIOP_123, &state_181, NULL, KC_DEL, 0, single_dance};
uint8_t state_182 = IDLE;
const struct Chord chord_182 PROGMEM = {H_BOT4, ASETNIOP_123, &state_182, NULL, KC_LSFT, 0, single_dance};
uint8_t state_183 = IDLE;
const struct Chord chord_183 PROGMEM = {H_BOT5, ASETNIOP_123, &state_183, NULL, KC_LCTL, 0, single_dance};
uint8_t state_184 = IDLE;
const struct Chord chord_184 PROGMEM = {H_BOT6, ASETNIOP_123, &state_184, NULL, KC_LALT, 0, single_dance};
uint8_t state_185 = IDLE;
const struct Chord chord_185 PROGMEM = {H_TOP5 + H_TOP6, ASETNIOP_123, &state_185, NULL, KC_LGUI, 0, single_dance};
uint8_t state_186 = IDLE;
const struct Chord chord_186 PROGMEM = {H_TOP1, ASETNIOP_FN, &state_186, NULL, KC_HOME, 0, single_dance};
uint8_t state_187 = IDLE;
const struct Chord chord_187 PROGMEM = {H_TOP2, ASETNIOP_FN, &state_187, NULL, KC_PGDN, 0, single_dance};
uint8_t state_188 = IDLE;
const struct Chord chord_188 PROGMEM = {H_TOP3, ASETNIOP_FN, &state_188, NULL, KC_PGUP, 0, single_dance};
uint8_t state_189 = IDLE;
const struct Chord chord_189 PROGMEM = {H_TOP4, ASETNIOP_FN, &state_189, NULL, KC_END, 0, single_dance};
uint8_t state_190 = IDLE;
const struct Chord chord_190 PROGMEM = {H_TOP7, ASETNIOP_FN, &state_190, NULL, KC_LEFT, 0, single_dance};
uint8_t state_191 = IDLE;
const struct Chord chord_191 PROGMEM = {H_TOP8, ASETNIOP_FN, &state_191, NULL, KC_DOWN, 0, single_dance};
uint8_t state_192 = IDLE;
const struct Chord chord_192 PROGMEM = {H_TOP9, ASETNIOP_FN, &state_192, NULL, KC_UP, 0, single_dance};
uint8_t state_193 = IDLE;
const struct Chord chord_193 PROGMEM = {H_TOP0, ASETNIOP_FN, &state_193, NULL, KC_RIGHT, 0, single_dance};
uint8_t state_194 = IDLE;
const struct Chord chord_194 PROGMEM = {H_TOP1 + H_TOP2, ASETNIOP_FN, &state_194, NULL, KC_F1, 0, single_dance};
uint8_t state_195 = IDLE;
const struct Chord chord_195 PROGMEM = {H_TOP2 + H_TOP3, ASETNIOP_FN, &state_195, NULL, KC_F2, 0, single_dance};
uint8_t state_196 = IDLE;
const struct Chord chord_196 PROGMEM = {H_TOP3 + H_TOP4, ASETNIOP_FN, &state_196, NULL, KC_F3, 0, single_dance};
uint8_t state_197 = IDLE;
const struct Chord chord_197 PROGMEM = {H_TOP4 + H_TOP7, ASETNIOP_FN, &state_197, NULL, KC_F4, 0, single_dance};
uint8_t state_198 = IDLE;
const struct Chord chord_198 PROGMEM = {H_TOP7 + H_TOP8, ASETNIOP_FN, &state_198, NULL, KC_F5, 0, single_dance};
uint8_t state_199 = IDLE;
const struct Chord chord_199 PROGMEM = {H_TOP8 + H_TOP9, ASETNIOP_FN, &state_199, NULL, KC_F6, 0, single_dance};
uint8_t state_200 = IDLE;
const struct Chord chord_200 PROGMEM = {H_TOP9 + H_TOP0, ASETNIOP_FN, &state_200, NULL, KC_F7, 0, single_dance};
uint8_t state_201 = IDLE;
const struct Chord chord_201 PROGMEM = {H_TOP1 + H_TOP3, ASETNIOP_FN, &state_201, NULL, KC_F10, 0, single_dance};
uint8_t state_202 = IDLE;
const struct Chord chord_202 PROGMEM = {H_TOP8 + H_TOP0, ASETNIOP_FN, &state_202, NULL, KC_F8, 0, single_dance};
uint8_t state_203 = IDLE;
const struct Chord chord_203 PROGMEM = {H_TOP1 + H_TOP4, ASETNIOP_FN, &state_203, NULL, KC_F11, 0, single_dance};
uint8_t state_204 = IDLE;
const struct Chord chord_204 PROGMEM = {H_TOP7 + H_TOP0, ASETNIOP_FN, &state_204, NULL, KC_F9, 0, single_dance};
uint8_t state_205 = IDLE;
const struct Chord chord_205 PROGMEM = {H_TOP1 + H_TOP7, ASETNIOP_FN, &state_205, NULL, KC_F12, 0, single_dance};
uint8_t state_206 = IDLE;
const struct Chord chord_206 PROGMEM = {H_TOP4 + H_TOP0, ASETNIOP_FN, &state_206, NULL, KC_BSPC, 0, single_dance};
uint8_t state_207 = IDLE;
const struct Chord chord_207 PROGMEM = {H_TOP5, ASETNIOP_FN, &state_207, NULL, KC_ESC, 0, single_dance};
uint8_t state_208 = IDLE;
const struct Chord chord_208 PROGMEM = {H_TOP6, ASETNIOP_FN, &state_208, NULL, KC_DEL, 0, single_dance};
uint8_t state_209 = IDLE;
const struct Chord chord_209 PROGMEM = {H_BOT4, ASETNIOP_FN, &state_209, NULL, KC_LSFT, 0, single_dance};
uint8_t state_210 = IDLE;
const struct Chord chord_210 PROGMEM = {H_BOT5, ASETNIOP_FN, &state_210, NULL, KC_LCTL, 0, single_dance};
uint8_t state_211 = IDLE;
const struct Chord chord_211 PROGMEM = {H_BOT6, ASETNIOP_FN, &state_211, NULL, KC_LALT, 0, single_dance};
uint8_t state_212 = IDLE;
const struct Chord chord_212 PROGMEM = {H_TOP5 + H_TOP6, ASETNIOP_FN, &state_212, NULL, KC_LGUI, 0, single_dance};

const struct Chord* const list_of_chords[] PROGMEM = {
    &chord_0, &chord_1, &chord_2, &chord_3, &chord_4, &chord_5, &chord_6, &chord_7, &chord_8, &chord_9, &chord_10, &chord_11, &chord_12, &chord_13, &chord_14, &chord_15, &chord_16, &chord_17, &chord_18, &chord_19, &chord_20, &chord_21, &chord_22, &chord_23, &chord_24, &chord_25, &chord_26, &chord_27, &chord_28, &chord_29, &chord_30, &chord_31, &chord_32, &chord_33, &chord_34, &chord_35, &chord_36, &chord_37, &chord_38, &chord_39, &chord_40, &chord_41, &chord_42, &chord_43, &chord_44, &chord_45, &chord_46, &chord_47, &chord_48, &chord_49, &chord_50, &chord_51, &chord_52, &chord_53, &chord_54, &chord_55, &chord_56, &chord_57, &chord_58, &chord_59, &chord_60, &chord_61, &chord_62, &chord_63, &chord_64, &chord_65, &chord_66, &chord_67, &chord_68, &chord_69, &chord_70, &chord_71, &chord_72, &chord_73, &chord_74, &chord_75, &chord_76, &chord_77, &chord_78, &chord_79, &chord_80, &chord_81, &chord_82, &chord_83, &chord_84, &chord_85, &chord_86, &chord_87, &chord_88, &chord_89, &chord_90, &chord_91, &chord_92, &chord_93, &chord_94, &chord_95, &chord_96, &chord_97, &chord_98, &chord_99, &chord_100, &chord_101, &chord_102, &chord_103, &chord_104, &chord_105, &chord_106, &chord_107, &chord_108, &chord_109, &chord_110, &chord_111, &chord_112, &chord_113, &chord_114, &chord_115, &chord_116, &chord_117, &chord_118, &chord_119, &chord_120, &chord_121, &chord_122, &chord_123, &chord_124, &chord_125, &chord_126, &chord_127, &chord_128, &chord_129, &chord_130, &chord_131, &chord_132, &chord_133, &chord_134, &chord_135, &chord_136, &chord_137, &chord_138, &chord_139, &chord_140, &chord_141, &chord_142, &chord_143, &chord_144, &chord_145, &chord_146, &chord_147, &chord_148, &chord_149, &chord_150, &chord_151, &chord_152, &chord_153, &chord_154, &chord_155, &chord_156, &chord_157, &chord_158, &chord_159, &chord_160, &chord_161, &chord_162, &chord_163, &chord_164, &chord_165, &chord_166, &chord_167, &chord_168, &chord_169, &chord_170, &chord_171, &chord_172, &chord_173, &chord_174, &chord_175, &chord_176, &chord_177, &chord_178, &chord_179, &chord_180, &chord_181, &chord_182, &chord_183, &chord_184, &chord_185, &chord_186, &chord_187, &chord_188, &chord_189, &chord_190, &chord_191, &chord_192, &chord_193, &chord_194, &chord_195, &chord_196, &chord_197, &chord_198, &chord_199, &chord_200, &chord_201, &chord_202, &chord_203, &chord_204, &chord_205, &chord_206, &chord_207, &chord_208, &chord_209, &chord_210, &chord_211, &chord_212
};

const uint16_t** const leader_triggers PROGMEM = NULL;
void (*leader_functions[]) (void) = {};

#define NUMBER_OF_CHORDS 213
#define NUMBER_OF_LEADER_COMBOS 0

bool are_hashed_keycodes_in_sound(HASH_TYPE keycodes_hash, HASH_TYPE sound) {
    return (keycodes_hash & sound) == keycodes_hash;
}

uint8_t keycode_to_index(uint16_t keycode) {
    return keycode - FIRST_INTERNAL_KEYCODE;
}

void sound_keycode_array(uint16_t keycode) {
    uint8_t index = keycode_to_index(keycode);
    keycode_index++;
    keycodes_buffer_array[index] = keycode_index;
}

void silence_keycode_hash_array(HASH_TYPE keycode_hash) {
    for (int i = 0; i < NUMBER_OF_KEYS; i++) {
        bool index_in_hash = ((HASH_TYPE) 1 << i) & keycode_hash;
        if (index_in_hash) {
            uint8_t current_val = keycodes_buffer_array[i];
            keycodes_buffer_array[i] = 0;
            for (int j = 0; j < NUMBER_OF_KEYS; j++) {
                if (keycodes_buffer_array[j] > current_val) {
                    keycodes_buffer_array[j]--;
                }
            }
            keycode_index--;
        }
    }
}

bool are_hashed_keycodes_in_array(HASH_TYPE keycode_hash) {
    for (int i = 0; i < NUMBER_OF_KEYS; i++) {
        bool index_in_hash = ((HASH_TYPE) 1 << i) & keycode_hash;
        bool index_in_array = (bool) keycodes_buffer_array[i];
        if (index_in_hash && !index_in_array) {
            return false;
        }
    }
    return true;
}

void kill_one_shots(void) {
    struct Chord chord_storage;
    struct Chord* chord_ptr;
    struct Chord* chord;
    
    for (int i = 0; i < NUMBER_OF_CHORDS; i++) {
        chord_ptr = (struct Chord*) pgm_read_word (&list_of_chords[i]);
        memcpy_P(&chord_storage, chord_ptr, sizeof(struct Chord));
        chord = &chord_storage;
        
        if (*chord->state == IN_ONE_SHOT) {
            *chord->state = RESTART;
            chord->function(chord);
            if (*chord->state == RESTART) {
                *chord->state = IDLE;
            }
        }
    }
}

void process_finished_dances(void) {
    struct Chord chord_storage;
    struct Chord* chord_ptr;
    struct Chord* chord;
    
    for (int i = 0; i < NUMBER_OF_CHORDS; i++) {
        chord_ptr = (struct Chord*) pgm_read_word (&list_of_chords[i]);
        memcpy_P(&chord_storage, chord_ptr, sizeof(struct Chord));
        chord = &chord_storage;
        
        if (*chord->state == ACTIVATED) {
            *chord->state = PRESS_FROM_ACTIVE;
            chord->function(chord);
            if (a_key_went_through) {
                kill_one_shots();
            }
            dance_timer = timer_read();
        } else if (*chord->state == IDLE_IN_DANCE) {
            *chord->state = FINISHED;
            chord->function(chord);
            if (*chord->state == FINISHED) {
                *chord->state = RESTART;
                if (*chord->state == RESTART) {
                    *chord->state = IDLE;
                }
            }
        } else if (*chord->state == PRESS_FROM_ACTIVE) {
            *chord->state = FINISHED_FROM_ACTIVE;
            chord->function(chord);
            if (a_key_went_through) {
                kill_one_shots();
            }
            dance_timer = timer_read();
        }
    }
}

uint8_t keycodes_buffer_array_min(uint8_t* first_keycode_index) {
    for (int i = 0; i < NUMBER_OF_KEYS; i++) {
        if (keycodes_buffer_array[i] == 1) {
            if (first_keycode_index != NULL) {
                *first_keycode_index = (uint8_t) i;
            }
            return 1;
        }
    }
    return 0;
}

void remove_subchords(void) {
    struct Chord chord_storage;
    struct Chord* chord_ptr;
    struct Chord* chord;
    
    for (int i = 0; i < NUMBER_OF_CHORDS; i++) {
        chord_ptr = (struct Chord*) pgm_read_word (&list_of_chords[i]);
        memcpy_P(&chord_storage, chord_ptr, sizeof(struct Chord));
        chord = &chord_storage;
        
        if (!(*chord->state == READY || *chord->state == READY_IN_DANCE || *chord->state == READY_LOCKED)) {
            continue;
        }
        
        struct Chord chord_storage_2;
        struct Chord* chord_ptr_2;
        struct Chord* chord_2;
        for (int j = 0; j < NUMBER_OF_CHORDS; j++) {
            if (i == j) {continue;}
            
            chord_ptr_2 = (struct Chord*) pgm_read_word (&list_of_chords[j]);
            memcpy_P(&chord_storage_2, chord_ptr_2, sizeof(struct Chord));
            chord_2 = &chord_storage_2;
            
            if (are_hashed_keycodes_in_sound(chord_2->keycodes_hash, chord->keycodes_hash)) {
                if (*chord_2->state == READY) {
                    *chord_2->state = IDLE;
                }
                if (*chord_2->state == READY_IN_DANCE) {
                    *chord_2->state = IDLE_IN_DANCE;
                }
                if (*chord_2->state == READY_LOCKED) {
                    *chord_2->state = LOCKED;
                }
            }
        }
    }
}

void process_ready_chords(void) {
    uint8_t first_keycode_index = 0;
    while (keycodes_buffer_array_min(&first_keycode_index)) {
        // find ready chords
        struct Chord chord_storage;
        struct Chord* chord_ptr;
        struct Chord* chord;
        
        for (int i = 0; i < NUMBER_OF_CHORDS; i++) {
            chord_ptr = (struct Chord*) pgm_read_word (&list_of_chords[i]);
            memcpy_P(&chord_storage, chord_ptr, sizeof(struct Chord));
            chord = &chord_storage;
            
            // if the chord does not contain the first keycode
            bool contains_first_keycode = ((uint32_t) 1 << first_keycode_index) & chord->keycodes_hash;
            if (!contains_first_keycode) {
                continue;
            }
            
            if (!are_hashed_keycodes_in_array(chord->keycodes_hash)){
                continue;
            }
            
            if (*chord->state == LOCKED) {
                *chord->state = READY_LOCKED;
                continue;
            }
            
            if (!(chord->pseudolayer == current_pseudolayer || chord->pseudolayer == ALWAYS_ON)) {
                continue;
            }
            
            if (*chord->state == IDLE) {
                *chord->state = READY;
                continue;
            }
            
            if (*chord->state == IDLE_IN_DANCE) {
                *chord->state = READY_IN_DANCE;
            }
        }
        
        // remove subchords
        remove_subchords();
        
        // execute logic
        // this should be only one chord
        for (int i = 0; i < NUMBER_OF_CHORDS; i++) {
            chord_ptr = (struct Chord*) pgm_read_word (&list_of_chords[i]);
            memcpy_P(&chord_storage, chord_ptr, sizeof(struct Chord));
            chord = &chord_storage;
            
            if (*chord->state == READY_LOCKED) {
                *chord->state = RESTART;
                chord->function(chord);
                if (*chord->state == RESTART) {
                    *chord->state = IDLE;
                }
                break;
            }
            
            if (*chord->state == READY || *chord->state == READY_IN_DANCE) {
                if (last_chord && last_chord != chord) {
                    process_finished_dances();
                }
                
                bool lock_next_prev_state = lock_next;
                
                *chord->state = ACTIVATED;
                chord->function(chord);
                dance_timer = timer_read();
                
                if (lock_next && lock_next == lock_next_prev_state) {
                    lock_next = false;
                    *chord->state = PRESS_FROM_ACTIVE;
                    chord->function(chord);
                    if (*chord->state == PRESS_FROM_ACTIVE) {
                        *chord->state = LOCKED;
                    }
                    if (a_key_went_through) {
                        kill_one_shots();
                    }
                }
                break;
            }
        }
        
        // silence notes
        silence_keycode_hash_array(chord->keycodes_hash);
    }
}

void deactivate_active_chords(uint16_t keycode) {
    HASH_TYPE hash = (HASH_TYPE)1 << (keycode - SAFE_RANGE);
    bool broken;
    struct Chord chord_storage;
    struct Chord* chord_ptr;
    struct Chord* chord;
    
    for (int i = 0; i < NUMBER_OF_CHORDS; i++) {
        chord_ptr = (struct Chord*) pgm_read_word (&list_of_chords[i]);
        memcpy_P(&chord_storage, chord_ptr, sizeof(struct Chord));
        chord = &chord_storage;
        
        broken = are_hashed_keycodes_in_sound(hash, chord->keycodes_hash);
        if (!broken) {
            continue;
        }
        
        switch (*chord->state) {
            case ACTIVATED:
                *chord->state = DEACTIVATED;
                chord->function(chord);
                
                if (*chord->state == DEACTIVATED) {
                    dance_timer = timer_read();
                    *chord->state = IDLE_IN_DANCE;
                }
                if (*chord->state != IN_ONE_SHOT) {
                    kill_one_shots();
                }
                break;
            case PRESS_FROM_ACTIVE:
            case FINISHED_FROM_ACTIVE:
                *chord->state = RESTART;
                chord->function(chord);
                if (*chord->state == RESTART) {
                    *chord->state = IDLE;
                }
                kill_one_shots();
                break;
            default:
                break;
        }
    }
    
}

void process_command(void) {
    command_mode = 0;
    for (int i = 0; i < COMMAND_MAX_LENGTH; i++) {
        if (command_buffer[i]) {
            register_code(command_buffer[i]);
        }
        send_keyboard_report();
    }
    wait_ms(TAP_TIMEOUT);
    for (int i = 0; i < COMMAND_MAX_LENGTH; i++) {
        if (command_buffer[i]) {
            unregister_code(command_buffer[i]);
        }
        send_keyboard_report();
    }
    for (int i = 0; i < COMMAND_MAX_LENGTH; i++) {
        command_buffer[i] = 0;
    }
    command_ind = 0;
}

void process_leader(void) {
    in_leader_mode = false;
    for (int i = 0; i < NUMBER_OF_LEADER_COMBOS; i++) {
        uint16_t trigger[LEADER_MAX_LENGTH];
        memcpy_P(trigger, leader_triggers[i], LEADER_MAX_LENGTH * sizeof(uint16_t));
        
        if (identical(leader_buffer, trigger)) {
            (*leader_functions[i])();
            break;
        }
    }
    for (int i = 0; i < LEADER_MAX_LENGTH; i++) {
        leader_buffer[i] = 0;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode < FIRST_INTERNAL_KEYCODE || keycode > LAST_INTERNAL_KEYCODE) {
        return true;
    }
    
    if (record->event.pressed) {
        sound_keycode_array(keycode);
    } else {
        process_ready_chords();
        deactivate_active_chords(keycode);
    }
    chord_timer = timer_read();
    leader_timer = timer_read();
    
    return false;
}

void matrix_scan_user(void) {
    bool chord_timer_expired = timer_elapsed(chord_timer) > CHORD_TIMEOUT;
    if (chord_timer_expired && keycodes_buffer_array_min(NULL)) {
        process_ready_chords();
    }
    
    bool dance_timer_expired = timer_elapsed(dance_timer) > DANCE_TIMEOUT;
    if (dance_timer_expired) { // would love to have && in_dance but not sure how
        process_finished_dances();
    }
    
    bool in_command_mode = command_mode == 2;
    if (in_command_mode) {
        process_command();
    }
    
    bool leader_timer_expired = timer_elapsed(leader_timer) > LEADER_TIMEOUT;
    if (leader_timer_expired && in_leader_mode) {
        process_leader();
    }
    
}

void clear(const struct Chord* self) {
    if (*self->state == ACTIVATED) {
        // kill all chords
        struct Chord chord_storage;
        struct Chord* chord_ptr;
        struct Chord* chord;
        
        for (int i = 0; i < NUMBER_OF_CHORDS; i++) {
            chord_ptr = (struct Chord*) pgm_read_word (&list_of_chords[i]);
            memcpy_P(&chord_storage, chord_ptr, sizeof(struct Chord));
            chord = &chord_storage;
            
            *chord->state = IDLE;
            
            if (chord->counter) {
                *chord->counter = 0;
            }
        }
        
        // clear keyboard
        clear_keyboard();
        send_keyboard_report();
        
        // switch to default pseudolayer
        current_pseudolayer = DEFAULT_PSEUDOLAYER;
        
        // clear all keyboard states
        lock_next = false;
        autoshift_mode = true;
        command_mode = 0;
        in_leader_mode = false;
        leader_ind = 0;
        dynamic_macro_mode = false;
        a_key_went_through = false;
        
        for (int i = 0; i < DYNAMIC_MACRO_MAX_LENGTH; i++) {
            dynamic_macro_buffer[i] = 0;
        }
    }
}