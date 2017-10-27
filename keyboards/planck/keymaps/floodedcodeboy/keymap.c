#include "planck.h"
#include "action_layer.h"

extern keymap_config_t keymap_config;

enum planck_layers
{
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
    _AMYTHEST
};

enum planck_keycodes
{
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
    EXT_PLV,
    AMYTHEST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

        /* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |Esc/~ |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  Up  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | TBC1 | Ctrl | Alt  | GUI  |Lower |Space |Space |Raise |   /  | Left | Down |Right |
 * `-----------------------------------------------------------------------------------'
 *
 * TBC1 - possible switch to windows control layer / terminal/amythest controls
 * LShift - Shift when held / Caps when tapped
 * Enter - MOD TAP with ENTER / R.SHIFT If held
 * Esc - Esc then ~ when pressed with Shift
 */
        [_QWERTY] = {
            {KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC},
            {KC_GESC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT},
            {SFT_T(KC_CAPS), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_UP, KC_ENTER},
            {_______, KC_LCTL, KC_LALT, KC_LGUI, LOWER, KC_SPC, KC_SPC, RAISE, KC_SLSH, KC_LEFT, KC_DOWN, KC_RGHT}},

        /* Lower
 * ,-----------------------------------------------------------------------------------.
 * | Mute |  F1  |  F2  |  F3  |  7   |   8  |   9  |   /  |   *  |   {  |   }  | DEL  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Vol+ |  F4  |  F5  |  F6  |  4   |   5  |   6  |   -  |   +  |   (  |   )  |   |  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Vol- |  F7  |  F8  |  F9  |  1   |   2  |   3  |   \  |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F10 |  F11 |  F12 |      |   0  |   .  |      | Home |PG Up |PG Dn | End  |
 * `-----------------------------------------------------------------------------------'
 *
 * Proposed Additions:
 * CMD+~ to bring up iterm
 * AMY - Amythest Layer
 */
        [_LOWER] = {
            {KC_MUTE, KC_F1, KC_F2, KC_F3, KC_KP_7, KC_KP_8, KC_KP_9, KC_SLASH, KC_ASTERISK, KC_LPRN, KC_RPRN, KC_DEL},
            {KC_VOLU, KC_F4, KC_F5, KC_F6, KC_KP_4, KC_KP_5, KC_KP_6, KC_PLUS, KC_MINUS, KC_LCBR, KC_RCBR, KC_PIPE},
            {KC_VOLD, KC_F7, KC_F8, KC_F9, KC_KP_1, KC_KP_2, KC_KP_3, KC_BSLASH, _______, _______, _______, _______},
            {_______, KC_F10, KC_F11, KC_F12, _______, KC_KP_0, KC_DOT, _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END}
        },

        /* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | DEL  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |      |      |      |      |      |      |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |ISO # |ISO / |Pg Up |Pg Dn |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Prev | Vol- | Vol+ | Next |
 * `-----------------------------------------------------------------------------------'
 */
        [_RAISE] = {
            {KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_DEL},
            {KC_DEL, _______, _______, _______, _______, _______, _______, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS},
            {_______, _______, _______, _______, _______, _______, _______, KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______},
            {_______, _______, _______, _______, _______, _______, _______, _______, KC_MEDIA_PREV_TRACK, KC_VOLD, KC_VOLU, KC_MEDIA_NEXT_TRACK}
        },

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
        [_ADJUST] = {{_______, RESET, DEBUG, _______, _______, _______, _______, TERM_ON, TERM_OFF, _______, _______, KC_DEL}, {_______, _______, MU_MOD, AU_ON, AU_OFF, AG_NORM, AG_SWAP, QWERTY, _______, _______, _______, _______}, {_______, MUV_DE, MUV_IN, MU_ON, MU_OFF, MI_ON, MI_OFF, _______, _______, _______, _______, _______}, {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}},

        /* Amythest ()
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
        [_AMYTHEST] = {{_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}, {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}, {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}, {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}}

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
        case AMYTHEST:
                if (record->event.pressed)
                {
                    set_single_persistent_default_layer(_AMYTHEST);
                }
                return false;
            break;
    }
    return true;
}