#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum planck_layers {
    _QWERTY,
    _ARROW,
    _NUMPAD,
    _MOVEMENT,
    _LOWER,
    _RAISE,
    _ADJUST
};

#define _MV _MOVEMENT

enum planck_keycodes {
    QWERTY = SAFE_RANGE,
    ARROW,
    NUMPAD,
    LOWER,
    RAISE,
};

#define KC_MUP KC_MS_UP
#define KC_MDN KC_MS_DOWN
#define KC_MLFT KC_MS_LEFT
#define KC_MRGT KC_MS_RIGHT
#define KC_MB1 KC_MS_BTN1
#define KC_MB2 KC_MS_BTN2
#define KC_MB3 KC_MS_BTN3
#define KC_MB4 KC_MS_BTN4
#define KC_MB5 KC_MS_BTN5
#define KC_MWUP KC_MS_WH_UP
#define KC_MWDN KC_MS_WH_DOWN

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Qwerty
     * ,-----------------------------------------------------------------------------------.
     * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |Enter |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |Shift |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Shift |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * | Ctrl | GUI  | Alt  | Move |Lower |    Space    |Raise | Move | Alt  | GUI  | Ctrl |
     * `-----------------------------------------------------------------------------------'
     */
    [_QWERTY] = LAYOUT_planck_grid(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT ,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, MO(_MV), LOWER,   KC_SPC,  KC_SPC,  RAISE,   MO(_MV), KC_RALT, KC_RGUI, KC_RCTL
    ),

    /* Arrow
     * ,-----------------------------------------------------------------------------------.
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |  Up  |      |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * |      |      |      |      |      |             |      |      | Left | Down | Right|
     * `-----------------------------------------------------------------------------------'
     */
    [_ARROW] = LAYOUT_planck_grid(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_UP,   _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    /* Numpad
     * ,-----------------------------------------------------------------------------------.
     * |      |      |      |      |      |      |NumLck|   7  |   8  |   9  |   /  |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |Enter |   4  |   5  |   6  |   *  |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |   3  |   2  |   1  |   -  |      |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * |      |      |      |      |      |             |      |   0  |   .  |   +  |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_NUMPAD] = LAYOUT_planck_grid(
        _______, _______, _______, _______, _______, _______, KC_NUM,  KC_P7,   KC_P8,   KC_P9,   KC_PSLS, _______,
        _______, _______, _______, _______, _______, _______, KC_PENT, KC_P4,   KC_P5,   KC_P6,   KC_PAST, _______,
        _______, _______, _______, _______, _______, _______, _______, KC_P1,   KC_P2,   KC_P3,   KC_PMNS, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_P0,   KC_PDOT, KC_PPLS, _______
    ),

    /* Movement
     * ,-----------------------------------------------------------------------------------.
     * |      |MsBut2|Ms Up |MsBut1|MsWhUp|      | Home | PgDn | PgUp |  End |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |Ms Lft|Ms Dn |Ms Rgt|MsWhDn|      | Left | Down |  Up  | Right|      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * |      |      |      |      |      |             |      |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_MOVEMENT] = LAYOUT_planck_grid(
        _______, KC_MB2,  KC_MUP,  KC_MB1,  KC_MWUP, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,
        _______, KC_MLFT, KC_MDN,  KC_MRGT, KC_MWDN, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    /* Lower
     * ,-----------------------------------------------------------------------------------.
     * |   `  |   1  |   2  |   3  |   4  |   5  |   -  |   =  |  Del | End  | PgDn |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Caps |   6  |   7  |   8  |   9  |   0  |   [  |   ]  |   \  |   '  |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |  F1  |  F2  |  F3  |  F4  |      |      |  F5  |  F6  |  F7  |  F8  |      |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * |      |      |      |      |      |             |      |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_LOWER] = LAYOUT_planck_grid(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS, KC_EQL,  KC_DEL,  KC_END,  KC_PGDN, _______,
        KC_CAPS, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_LBRC, KC_RBRC, KC_BSLS, KC_QUOT, XXXXXXX, _______,
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   XXXXXXX, XXXXXXX, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    /* Raise
     * ,-----------------------------------------------------------------------------------.
     * |   ~  |   !  |   @  |   #  |   $  |   %  |   _  |   +  |  Ins | Home | PgUp |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * | Caps |   ^  |   &  |   *  |   (  |   )  |   {  |   }  |   |  |   "  |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |  F9  |  F10 |  F11 |  F12 |      |      |      |      |      |      |      |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * |      |      |      |      |      |             |      |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_RAISE] = LAYOUT_planck_grid(
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_UNDS, KC_PLUS, KC_INS,  KC_HOME, KC_PGUP, _______,
        KC_CAPS, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_LCBR, KC_RCBR, KC_PIPE, KC_DQUO, XXXXXXX, _______,
        _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    /* Adjust (Lower + Raise)
     * ,-----------------------------------------------------------------------------------.
     * |Reset |      |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |Bcklgt| Mute |Vol Dn|Vol Up|      |      |Qwerty|Arrow |Numpad|      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+-------------+------+------+------+------+------|
     * |      |      |      |      |      |             |      |      |      |      |      |
     * `-----------------------------------------------------------------------------------'
     */
    [_ADJUST] = LAYOUT_planck_grid(
        QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, BL_STEP, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______, QWERTY,  ARROW,   NUMPAD,  _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )

};

#ifdef AUDIO_ENABLE

float tone_startup[][2]    = SONG(STARTUP_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);

float tone_goodbye[][2] = SONG(GOODBYE_SOUND);

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    switch (keycode) {
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
            } else {
                layer_off(_LOWER);
            }
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
            return false;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
            } else {
                layer_off(_RAISE);
            }
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
            return false;
        case QWERTY:
            if (record->event.pressed) {
                layer_off(_ARROW);
                layer_off(_NUMPAD);
            }
            return false;
        case ARROW:
            if (record->event.pressed) {
                layer_off(_NUMPAD);
                layer_on(_ARROW);
            }
            return false;
        case NUMPAD:
            if (record->event.pressed) {
                layer_off(_ARROW);
                layer_on(_NUMPAD);
            }
            return false;
    }
    return true;
}

void matrix_init_user(void)
{
#ifdef AUDIO_ENABLE
    startup_user();
#endif
}

#ifdef AUDIO_ENABLE

void startup_user(void)
{
    _delay_ms(100); // gets rid of tick
    PLAY_SONG(tone_startup);
}

void shutdown_user(void)
{
    PLAY_SONG(tone_goodbye);
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_SONG(music_scale);
}

#endif
