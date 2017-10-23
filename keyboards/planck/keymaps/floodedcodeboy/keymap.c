#include "planck.h"
#include "action_layer.h"

extern keymap_config_t keymap_config;

enum planck_layers
{
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum planck_keycodes
{
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
    EXT_PLV
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

        /* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | TBC1 | Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 *
 * TBC1 - possible switch to windows control layer
 * LSHIRT - Shift when held / Caps when tapped
 * ENTER - MOD TAP with ENTER / R.SHIFT If held
 */
        [_QWERTY] = {
            {KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC},
            {KC_ESC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT},
            {SFT_T(KC_CAPS), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, MT(MOD_RSFT, KC_ENTER)},
            {_______, KC_LCTL, KC_LALT, KC_LGUI, LOWER, KC_SPC, KC_SPC, RAISE, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT}},

        /* Lower
 * ,-----------------------------------------------------------------------------------.
 * | Del  |  F1  |  F2  |  F3  |  7   |   8  |   9  |   /  |   *  |   {  |   }  | DEL  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   ~  |  F4  |  F5  |  F6  |  4   |   5  |   6  |   +  |   -  |   (  |   )  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  1   |   2  |   3  | Home | Pg Up|Pg Dn | End  | Mute |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F10 |  F11 |  F12 |      |   0  |   .  |      | Prev | Vol- | Vol+ | Next |
 * `-----------------------------------------------------------------------------------'
 */
        [_LOWER] = {{KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC}, {KC_DEL, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE}, {_______, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END, _______}, {_______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}},

        /* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |Pg Up |Pg Dn |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
        [_RAISE] = {{KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC}, {KC_DEL, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS}, {_______, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______}, {_______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}},

        /* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
        [_ADJUST] = {{_______, RESET, DEBUG, _______, _______, _______, _______, TERM_ON, TERM_OFF, _______, _______, KC_DEL}, {_______, _______, MU_MOD, AU_ON, AU_OFF, AG_NORM, AG_SWAP, QWERTY, _______, _______, _______, _______}, {_______, MUV_DE, MUV_IN, MU_ON, MU_OFF, MI_ON, MI_OFF, _______, _______, _______, _______, _______}, {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}}

};

#ifdef AUDIO_ENABLE
float plover_song[][2] = SONG(PLOVER_SOUND);
float plover_gb_song[][2] = SONG(PLOVER_GOODBYE_SOUND);
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    switch (keycode)
    {
    case QWERTY:
        if (record->event.pressed)
        {
            print("mode just switched to qwerty and this is a huge string\n");
            set_single_persistent_default_layer(_QWERTY);
        }
        return false;
        break;
    case LOWER:
        if (record->event.pressed)
        {
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
        }
        else
        {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
        }
        return false;
        break;
    case RAISE:
        if (record->event.pressed)
        {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
        }
        else
        {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
        }
        return false;
        break;
    }
    return true;
}