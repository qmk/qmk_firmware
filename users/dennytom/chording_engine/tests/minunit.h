#define mu_assert(message, test) \
    do { \
        if (!(test)) { \
            return message; \
        } \
    } while (0)

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define NC "\033[0m"

enum ASSERT_TYPES {
    UINT,
    INT
};

#define BUFF_SIZE 1024
char buffer[BUFF_SIZE];

#define ASSERT_EQ(type, actual, expected) \
    do { \
        if (actual != expected) { \
            switch (type) { \
                case UINT: \
                    snprintf(buffer, BUFF_SIZE, "\nline %d\nvar %s\nactual = %u\nexpected = %u\n", __LINE__, #actual, actual, expected); \
                    break; \
                case INT: \
                    snprintf(buffer, BUFF_SIZE, "\nline %d\nvar %s\nactual = %d\nexpected = %d\n", __LINE__, #actual, actual, expected); \
                    break; \
                default: \
                    snprintf(buffer, BUFF_SIZE, "\nline %d\nunsupported ASSERT_EQ type\n", __LINE__); \
                    break; \
            } \
            printf("%s\n", buffer); \
            passed = false; \
            all_passed = false; \
        } \
    } while (0)

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#define MATRIX_ROWS 2
#define MATRIX_COLS 10
#define LAYOUT_test( 										\
    k09, k08, k07, k06, k05, k04, k03, k02, k01, k00,		\
	k19, k18, k17, k16, k15, k14, k13, k12, k11, k10		\
) { 														\
	{ k00, k01, k02, k03, k04, k05, k06, k07, k08, k09},	\
	{ k10, k11, k12, k13, k14, k15, k16, k17, k18, k19},	\
}

#define PROGMEM
#define memcpy_P memcpy
const struct Chord* pgm_read_word(const struct Chord* const* chord) {return *chord;}

typedef struct {
    uint8_t col;
    uint8_t row;
} keypos_t;

typedef struct {
    keypos_t key;
    bool     pressed;
    uint16_t time;
} keyevent_t;

typedef struct {
    bool    interrupted :1;
    bool    reserved2   :1;
    bool    reserved1   :1;
    bool    reserved0   :1;
    uint8_t count       :4;
} tap_t;

typedef struct {
    keyevent_t event;
    tap_t tap;
} keyrecord_t;

keyrecord_t pressed = {{{0,0},true,0}, {0,0,0,0,0}};
keyrecord_t depressed = {{{0,0},false,0}, {0,0,0,0,0}};

enum keycodes {
    KC_NO,
    KC_TILDE,
    KC_GRAVE,
    KC_EXCLAIM,
    KC_1,
    KC_AT,
    KC_2,
    KC_HASH,
    KC_3,
    KC_DOLLAR,
    KC_4,
    KC_PERCENT,
    KC_5,
    KC_CIRCUMFLEX,
    KC_6,
    KC_AMPERSAND,
    KC_7,
    KC_ASTERISK,
    KC_8,
    KC_LEFT_PAREN,
    KC_9,
    KC_RIGHT_PAREN,
    KC_0,
    KC_UNDERSCORE,
    KC_MINUS,
    KC_PLUS,
    KC_EQUAL,
    KC_LEFT_CURLY_BRACE,
    KC_LEFT_BRACKET,
    KC_RIGHT_CURLY_BRACE,
    KC_RIGHT_BRACKET,
    KC_PIPE,
    KC_BACKSLASH,
    KC_COLON,
    KC_SEMICOLON,
    KC_DOUBLE_QUOTE,
    KC_QUOTE,
    KC_LEFT_ANGLE_BRACKET,
    KC_COMMA,
    KC_RIGHT_ANGLE_BRACKET,
    KC_DOT,
    KC_QUESTION,
    KC_SLASH,
    KC_Q,
    KC_W,
    KC_E,
    KC_R,
    KC_T,
    KC_Y,
    KC_U,
    KC_I,
    KC_O,
    KC_P,
    KC_A,
    KC_S,
    KC_D,
    KC_F,
    KC_G,
    KC_H,
    KC_J,
    KC_K,
    KC_L,
    KC_Z,
    KC_X,
    KC_C,
    KC_V,
    KC_B,
    KC_N,
    KC_M,
    KC_ESC,
    KC_LSFT,
    KC_LCTL,
    KC_LGUI,
    KC_LALT,
    KC_RALT,
    KC_RCTL,
    KC_RGUI,
    KC_RSFT,
    KC_TAB,
    KC_DEL,
    KC_INS,
    KC_BSPC,
    KC_ENTER,
    KC_SPACE,
    KC_F1,
    KC_F2,
    KC_F3,
    KC_F4,
    KC_F5,
    KC_F6,
    KC_F7,
    KC_F8,
    KC_F9,
    KC_F10,
    KC_F11,
    KC_F12,
    KC_LEFT,
    KC_DOWN,
    KC_UP,
    KC_RIGHT,
    
    SAFE_RANGE
};

#define HISTORY 20

int16_t current_time;
uint8_t keyboard_history[HISTORY][SAFE_RANGE-1];
int16_t time_history[HISTORY];
uint8_t history_index;

void register_code(int16_t keycode) {
    history_index++;
    for (int j = 0; j < SAFE_RANGE-1; j++) {
        keyboard_history[history_index][j] = keyboard_history[history_index-1][j];
    }
    keyboard_history[history_index][keycode] = 1;
    time_history[history_index] = current_time;
};
void unregister_code(int16_t keycode) {
    history_index++;
    for (int j = 0; j < SAFE_RANGE-1; j++) {
        keyboard_history[history_index][j] = keyboard_history[history_index-1][j];
    }
    keyboard_history[history_index][keycode] = 0;
    time_history[history_index] = current_time;
};
void send_keyboard_report(void) { /*still don't know what this does*/ };
void matrix_scan_user (void);
void wait_ms(uint16_t ms) {
    current_time += ms;
};
uint16_t timer_read(void) {
    uint16_t result = current_time;
    return result;
};
uint16_t timer_elapsed(uint16_t timer) {
    uint16_t result = current_time - timer;
    return result;
};
void layer_move(int16_t layer) { /*ignoring for now*/ };
void clear_keyboard(void) {
    history_index++;
    for (int j = 0; j < SAFE_RANGE-1; j++) {
        keyboard_history[history_index][j] = 0;
    }
    time_history[history_index] = current_time;
};
void reset_keyboard(void) { /*ignoring for now*/ };

void pause_ms(uint16_t ms) {
    for (int i = 0; i < ms; i++) {
        current_time++;
        matrix_scan_user();
    }
};

#define TEST(name) \
    do { \
        printf("%s\n", name); \
        passed = true; \
        do { \
            uint8_t clear_state = ACTIVATED; \
            struct Chord clear_chord PROGMEM = {0, QWERTY, &clear_state, NULL, 0, 0, clear}; \
            clear_chord.function(&clear_chord); \
        } while (0); \
        current_time = 0; \
        history_index = 0; \
        for (int j = 0; j < SAFE_RANGE-1; j++) { \
            keyboard_history[0][j] = 0; \
        } \
        time_history[0] = 0; \
        for (int i = 1; i < HISTORY; i++) { \
            for (int j = 0; j < SAFE_RANGE-1; j++) { \
                keyboard_history[i][j] = -1; \
            } \
            time_history[i] = -1; \
        }

#define END_TEST \
        if (passed) { \
            printf(GREEN"PASSED"NC"\n"); \
        } else { \
            printf(RED"FAILED"NC"\n"); \
        } \
    } while(0);

#define MAIN \
int main(int argc, char **argv) { \
    bool passed = true; \
    bool all_passed = true;

#define END \
    printf("\n"); \
    if (all_passed) { \
        printf(GREEN"ALL TESTS PASSED"NC"\n"); \
    } else { \
        printf(RED"TESTS FAILED"NC"\n"); \
    } \
    return 1 - all_passed; \
}