#include "action_util.h"
#include "action_layer.h"
#define KC_SW0 KC_FN0
#define DEBUG_ACTION

static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Keymap 0: Basic layer
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |   =    |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |   -    |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * | Del    |   Q  |   W  |   E  |   R  |   T  |  Up  |           |  Up  |   Y  |   U  |   I  |   O  |   P  |   \    |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * | BkSp   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |; / L2|   '    |
     * |--------+------+------+------+------+------|  L1  |           |  L1  |------+------+------+------+------+--------|
     * | LShift |Z/Ctrl|   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |//Ctrl| RShift |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   |Grv/L1| ~L1  | TAB  | Left | Right|                                       | Up   | Down |   [  |   ]  | ~L1  |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        | Rclk | LGui |       | Alt  |Ctrl/Esc|
     *                                 ,------|------|------|       |------+--------+------.
     *                                 |      |      | Home |       | PgUp |        |      |
     *                                 | Space| Enter|------|       |------|  Tab   |Enter |
     *                                 |      |      | End  |       | PgDn |        |      |
     *                                 `--------------------'       `----------------------'
     */


    // Basic layer

    KEYMAP(
           EQL,  1,    2,    3,    4,    5, LEFT,
           DEL,  Q,    W,    E,    R,    T, UP,
           BSPC, A,    S,    D,    F,    G,
           LSFT, FN29, X,    C,    V,    B, FN1,
           FN30,  FN4, TAB,  LEFT, RIGHT,

                                           BTN2,LGUI,
                                                HOME,
                                      SPC, ENT, END,
           //RIGHT
           RIGHT,6,    7,    8,    9,    0,    MINS,
           UP,   Y,    U,    I,    O,    P,    BSLS,
                 H,    J,    K,    L,    FN31, QUOT,
           FN1,  N,    M,    COMM, DOT,  FN28, RSFT,
                       UP,   DOWN, LBRC, RBRC, FN4,
           LALT, FN27,
           PGUP,
           PGDN, TAB, ENT
           ),

    /* Keymap 1: Symbol Layer
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |  Flash |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * |        |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * | :      |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |        |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   |      |      |      |      |      |                                       |      |    . |   0  |   =  |      |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        |      |      |       |      |      |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      |      |       |      |      |      |
     *                                 |      |      |------|       |------|      |      |
     *                                 |      |      |      |       |      |      |      |
     *                                 `--------------------'       `--------------------'
     */
    // SYMBOLS
    KEYMAP(
           FN0,  F1,   F2,   F3,   F4,   F5,   TRNS,
           TRNS, FN7,  FN8,  FN23, FN24, FN18, TRNS,
           FN22, FN9,  FN10, FN15, FN16, GRV,
           TRNS, FN11, FN12, LBRC, RBRC, FN17, TRNS,
           TRNS, TRNS, TRNS, TRNS, TRNS,

                                               TRNS, TRNS,
                                                     TRNS,
                                         TRNS, TRNS, TRNS,
        // right hand
           TRNS, F6,   F7,   F8,   F9,   F10,   F11,
           TRNS, UP,       7,   8,    9,    FN14, F12,
                 DOWN,     4,   5,    6,    FN26, TRNS,
           TRNS, FN13,     1,   2,    3,    BSLS, TRNS,
                           TRNS,DOT,  0,    EQL,  TRNS,
           TRNS, TRNS,
           TRNS,
           TRNS, TRNS, TRNS
    ),
    /* Keymap 2: Media and mouse keys
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * |        |      | MsUp |      |      |      |      |           |      |      |      |      |      |      |        |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |        |MsLeft|MsDown|MsRght|      |      |------|           |------|      |      |      | Play |      |        |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn |      |      |      |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        |      |      |       |      |      |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      |      |       |      |      |      |
     *                                 |      |      |------|       |------|      |      |
     *                                 |      |      |      |       |      |      |      |
     *                                 `--------------------'       `--------------------'
     */
    // MEDIA AND MOUSE
    KEYMAP(
           TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
           TRNS, TRNS, MS_U, TRNS, TRNS, TRNS, TRNS,
           TRNS, MS_L, MS_D, MS_R, TRNS, TRNS,
           TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
           TRNS, TRNS, TRNS, BTN3, BTN2,

                                               TRNS, TRNS,
                                                     TRNS,
                                         TRNS, TRNS, TRNS,
        // right hand
           TRNS,  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
           TRNS,  TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,
                  TRNS, TRNS, TRNS, MPLY, TRNS, TRNS,
           TRNS,  TRNS, TRNS, MPRV, MNXT, TRNS, TRNS,
                        VOLU, VOLD, TRNS, TRNS, TRNS,
           TRNS, TRNS,
           TRNS,
           TRNS, TRNS, WBAK
    ),
};

/* id for user defined functions */
enum function_id {
    TEENSY_KEY,
};

/*
 * Fn action definition
 */
static const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_FUNCTION(TEENSY_KEY),              // FN0  - Teensy key
    [1] = ACTION_LAYER_INVERT(1, ON_RELEASE),       // FN1 - Toggle 1
    [2] = ACTION_LAYER_TOGGLE(2),                   // FN2 - Toggle 2
    [3] = ACTION_LAYER_TOGGLE(3),                   // FN3 - Toggle 3
    [4] = ACTION_LAYER_TAP_TOGGLE(1),               // FN4 - Momentary Layer 1
    [5] = ACTION_LAYER_MOMENTARY(2),                // FN5 - Momentary L2

    // SYMBOLS
    ACTION_MODS_KEY(MOD_LSFT, KC_QUOT),             // FN6 - "
    ACTION_MODS_KEY(MOD_LSFT, KC_1),                // FN7 - !
    ACTION_MODS_KEY(MOD_LSFT, KC_2),                // FN8 - @
    ACTION_MODS_KEY(MOD_LSFT, KC_3),                // FN9 - #
    ACTION_MODS_KEY(MOD_LSFT, KC_4),                // FN10 - $
    ACTION_MODS_KEY(MOD_LSFT, KC_5),                // FN11 - %
    ACTION_MODS_KEY(MOD_LSFT, KC_6),                // FN12 - ^
    ACTION_MODS_KEY(MOD_LSFT, KC_7),                // FN13 - &
    ACTION_MODS_KEY(MOD_LSFT, KC_8),                // FN14 - *
    ACTION_MODS_KEY(MOD_LSFT, KC_9),                // FN15 - (
    ACTION_MODS_KEY(MOD_LSFT, KC_0),                // FN16 - )
    ACTION_MODS_KEY(MOD_LSFT, KC_GRV),              // FN17 - ~
    ACTION_MODS_KEY(MOD_LSFT, KC_BSLS),             // FN18 - |
    ACTION_MODS_KEY(MOD_LSFT, KC_MINS),             // FN19 - _
    ACTION_MODS_KEY(MOD_LSFT, KC_COMM),             // FN20 - <
    ACTION_MODS_KEY(MOD_LSFT, KC_DOT),              // FN21 - >
    ACTION_MODS_KEY(MOD_LSFT, KC_SCLN),             // FN22 - :
    ACTION_MODS_KEY(MOD_LSFT, KC_LBRC),             // FN23 - {
    ACTION_MODS_KEY(MOD_LSFT, KC_RBRC),             // FN24 - }
    ACTION_MODS_KEY(MOD_LSFT, KC_SLSH),             // FN25 - ?
    ACTION_MODS_KEY(MOD_LSFT, KC_EQL),              // FN26 - +

    ACTION_MODS_TAP_KEY(MOD_LCTL, KC_ESC),          // FN27 - Control/esc on tap
    ACTION_MODS_TAP_KEY(MOD_LCTL, KC_SLSH),         // FN28 - slash becomes Ctrl when held (right pinky)
    ACTION_MODS_TAP_KEY(MOD_LCTL, KC_Z),            // FN29 - z becomes Ctrl when held (left pinky)

    // Fancy tapping/toggling
    ACTION_LAYER_TAP_KEY(1, KC_GRV),                // FN30 - Layer 1 when holding backtick key
    ACTION_LAYER_TAP_KEY(2, KC_SCLN),               // FN31 - Layer 2 when holding semicolon key


};

void action_function(keyrecord_t *event, uint8_t id, uint8_t opt)
{
    print("action_function called\n");
    print("id  = "); phex(id); print("\n");
    print("opt = "); phex(opt); print("\n");
    if (id == TEENSY_KEY) {
        clear_keyboard();
        print("\n\nJump to bootloader... ");
        _delay_ms(250);
        bootloader_jump(); // should not return
        print("not supported.\n");
    }
}

void * matrix_init_user(void) {

};

void * matrix_scan_user(void) {

};
