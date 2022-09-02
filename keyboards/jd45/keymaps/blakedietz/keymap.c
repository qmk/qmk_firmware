#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

/*
 * Each layer gets a name for readability, which is then used in the keymap matrix below.
 * The underscores don't mean anything - you can have a layer called STUFF or any other name.
 * Layer names don't all need to be of the same length, obviously, and you can also skip them
 * entirely and just use numbers.
 */
#define _ADJUST 16
#define _LOWER 3
#define _MEDIA 8
#define _MOUSECURSOR 7
#define _QWERTY 0
#define _RAISE 4
#define _VIM 9
// TODO: (bdietz) - make a symbols layer for fun emoji and ascii art
// TODO: (bdietz) - make a symbol layer for greek symbols

// Keycodes
enum planck_keycodes
{
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
};

enum macro_keycodes
{
    KC_ALT_TAB,
    KC_CMD_TAB,
    KC_CTL_TAB,
    KC_CMD_SLSH,
    KC_AG_FIND,
    KC_AG_AGAIN,
    KC_AG_UNDO,
    KC_AG_CUT,
    KC_AG_COPY,
    KC_AG_PASTE,
    KC_AG_DESK_L,
    KC_AG_DESK_R,
    KC_AG_TAB_C,
    KC_AG_TAB_N,
    KC_AG_TAB_R,
};

/**
 * This section of macros is for tap or hold functionality. Keys will fire off the second symbol in the name if tapped
 * or fire the first symbol in the name if held. For example
 * GUI_Z
 *
 * - will fire z if tapped
 * - will fire cmd/super/win if held
 */
#define ALT_DOT ALT_T(KC_DOT)
#define ALT_X ALT_T(KC_X)
#define CTL_SLSH CTL_T(KC_SLSH)
#define CTL_Z CTL_T(KC_Z)
#define GUI_C GUI_T(KC_C)
#define GUI_COMM GUI_T(KC_COMM)
#define HPR_ESC ALL_T(KC_ESC)
#define HPR_QUO ALL_T(KC_QUOT)

// Toggle to VIM when left space button is held, emit space keycode when left space is tapped
#define TGL_VIM LT(_VIM, KC_SPC)
// Toggle to the mouse layer when the right space button is held and emit enter when right space is tapped
#define TGL_MOUSE LT(_MOUSECURSOR, KC_ENT)

// TODO: (bdietz) - need to audit these keycodes to see what sort of cool things the default layout was doing.
#define ALT_TAB M(KC_ALT_TAB)   // Macro for Alt-Tab
#define CMD_TAB M(KC_CMD_TAB)   // Macro for Cmd-Tab
#define CTL_TAB M(KC_CTL_TAB)   // Macro for Ctl-Tab
#define CMD_SLSH M(KC_CMD_SLSH) // Macro for Cmd-Slash (personal shortcut to toggle iTerm2 visibility)
#define AG_FIND M(KC_AG_FIND)   // Macros for Cmd-[x] vs Ctrl-[x] based on current AG_NORM or AG_SWAP settings
#define AG_AGAIN M(KC_AG_AGAIN)
#define AG_UNDO M(KC_AG_UNDO)
#define AG_CUT M(KC_AG_CUT)
#define AG_COPY M(KC_AG_COPY)
#define AG_PASTE M(KC_AG_PASTE)
#define AG_D_L M(KC_AG_DESK_L) // For Virtual Desktop Switching: Left, and
#define AG_D_R M(KC_AG_DESK_R) //                                Right
#define AG_T_C M(KC_AG_TAB_C)  // For Chrome, etc. Tab Close,
#define AG_T_N M(KC_AG_TAB_N)  //                  Tab New, and
#define AG_T_R M(KC_AG_TAB_R)  //                  Tab Reopen Closed

/* Qwerty
 *
 * ,---------+------+------+------+------+------+------+------+------+------+------+------+------.
 * |   Tab   |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |      |
 * |---------`------`------`------`------`------`------`------`------`------`------`------`------|
 * |Hyper/Esc|   A  |   S  |  D   |   F  |   G  |   H  |   J  |   K  |   L  |MEDIA/;|  Hyper/"   |
 * |----------`------`------`------`------`------`------`------`------`------`------`------------|
 * |   Shift   |CTL/Zl|ALT/X |GUI/C |   V  |   B  |   N  |   M  |GUI/, | ALT/.|CTL// |  Shift    |
 * |-----------`------`------`------`------`-----'-------`------`------`------`------`-----------|
 * |        |       |       | Lower | VIM/Space| MOUSE/Ent|  Raise  |        |        |          |
 *  `-------+-------+-------+-------+---^^^----+---^^^----+---------+--------+--------+----------'
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
        /*,--------+-------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------.*/
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, ALL_T(KC_NO),
        /*|--------`-------`--------`--------`--------`--------`--------`--------`--------`--------`--------`--------`--------|*/
        HPR_ESC, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, LT(_MEDIA, KC_SCLN), HPR_QUO,
        /*|---------`-------`--------`--------`--------`--------`--------`--------`--------`--------`--------`----------------|*/
        KC_LSFT, CTL_Z, ALT_X, GUI_C, KC_V, KC_B, KC_N, KC_M, GUI_COMM, ALT_DOT, CTL_SLSH, KC_RSFT,
        /*|----------`-------`--------`--------`--------`--------`--------`--------`--------`--------`--------`---------------|*/
        _______, _______, _______, LOWER, TGL_VIM, TGL_MOUSE, RAISE, _______, _______, _______),
    /*`----------+-----------+-----------+-----------+----^^^----+----^^^----+-----------+-----------+-----------+--------'*/

    // TODO: (bdietz) - update the keymap documentation to include the modifier keys on the third row
    /* Lower
 * ,---------+------+------+------+------+------+------+------+------+------+------+------+------.
 * |   `     |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp | Bksp |
 * |---------`------`------`------`------`------`------`------`------`------`------`------`------|
 * |   [      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |   "|"      |
 * |----------`------`------`------`------`------`------`------`------`------`------`------------|
 * |   ]       |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |   -  |   =  |   [  |   ]  |    \      |
 * |-----------`------`------`------`------`-----'-------`------`------`------`------`-----------|
 * |        |       |       |       |          |          |         |  Prev  |  Next  |   Mute   |
 *  `-------+-------+-------+-------+---^^^----+---^^^----+---------+--------+--------+----------'
 */
    [_LOWER] = LAYOUT(
        /*,--------+-------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------.*/
        KC_GRV, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, KC_BSPC,
        /*|--------`-------`--------`--------`--------`--------`--------`--------`--------`--------`--------`--------`--------|*/
        KC_LBRC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
        /*|---------`-------`--------`--------`--------`--------`--------`--------`--------`--------`--------`----------------|*/
        KC_RBRC, CTL_T(KC_F7), ALT_T(KC_F8), GUI_T(KC_F9), KC_F10, KC_F11, KC_F12, KC_MINS, GUI_T(KC_EQL), ALT_T(KC_LBRC), CTL_T(KC_RBRC), KC_BSLS,
        /*|----------`-------`--------`--------`--------`--------`--------`--------`--------`--------`--------`---------------|*/
        _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_MNXT, KC_MUTE),
    /*`----------+-----------+-----------+-----------+----^^^----+----^^^----+-----------+-----------+-----------+--------'*/

    /* Raise
 * ,---------+------+------+------+------+------+------+------+------+------+------+------+------.
 * |   ~     |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp | Bksp |
 * |---------`------`------`------`------`------`------`------`------`------`------`------`------|
 * |   $      |   4  |   5  |   6  |   .  |   +  |   .  |   4  |   5  |   6  |   *  |   "|"      |
 * |----------`------`------`------`------`------`------`------`------`------`------`------------|
 * |   =       |   7  |   8  |   9  |   0  |   -  |   .  |   1  |   2  |   3  |   /  |    \      |
 * |-----------`------`------`------`------`-----'-------`------`------`------`------`-----------|
 * |        |       |       |       |          |          |         |  Prev  |  Next  |   Mute   |
 *  `-------+-------+-------+-------+---^^^----+---^^^----+---------+--------+--------+----------'
 */
    [_RAISE] = LAYOUT(
        /*,--------+-------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------.*/
        KC_TILD, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC, KC_BSPC,
        /*|--------`-------`--------`--------`--------`--------`--------`--------`--------`--------`--------`--------`--------|*/
        KC_DLR, KC_4, KC_5, KC_6, KC_DOT, KC_PLUS, KC_DOT, KC_4, KC_5, KC_6, KC_ASTR, KC_PIPE,
        /*|---------`-------`--------`--------`--------`--------`--------`--------`--------`--------`--------`----------------|*/
        KC_EQL, CTL_T(KC_7), ALT_T(KC_8), GUI_T(KC_9), KC_0, KC_MINS, KC_DOT, KC_1, GUI_T(KC_2), ALT_T(KC_3), CTL_T(KC_SLSH), KC_BSLS,
        /*|----------`-------`--------`--------`--------`--------`--------`--------`--------`--------`--------`---------------|*/
        _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_MNXT, KC_MUTE),
    /*`----------+-----------+-----------+-----------+----^^^----+----^^^----+-----------+-----------+-----------+--------'*/

    /* Mouse Layer
 * ,---------+------+------+------+------+------+------+------+------+------+------+------+------.
 * |         |      |ACCL0 |      |      |      |      |WHL_L |  Up  |WHL_R | BTN2 |      |      |
 * |---------`------`------`------`------`------`------`------`------`------`------`------`------|
 * |          |ACCL2 | BTN2 |      | BTN1 |ACCL1 |WHL_Up| Left | Down |Right | BTN4 |   BTN5     |
 * |----------`------`------`------`------`------`------`------`------`------`------`------------|
 * |           |      |      |      | BTN3 |      |WHL_Dn| BTN1 |      |      | BTN3 |           |
 * |-----------`------`------`------`------`-----'-------`------`------`------`------`-----------|
 * |        |       |       |       |          |          |         |        |        |          |
 *  `-------+-------+-------+-------+---^^^----+---^^^----+---------+--------+--------+----------'
 */

    [_MOUSECURSOR] = LAYOUT(
        /*,--------+-------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------.*/
        _______, _______, _______, KC_MS_U, _______, _______, _______, KC_ACL2, KC_ACL1, KC_ACL0, _______, _______, _______,
        /*|--------`-------`--------`--------`--------`--------`--------`--------`--------`--------`--------`--------`--------|*/
        _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, KC_BTN1, KC_BTN2, _______, _______, _______,
        /*|---------`-------`--------`--------`--------`--------`--------`--------`--------`--------`--------`----------------|*/
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        /*|----------`-------`--------`--------`--------`--------`--------`--------`--------`--------`--------`---------------|*/
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),
    /*`----------+-----------+-----------+-----------+----^^^----+----^^^----+-----------+-----------+-----------+--------'*/

    /* Adjust (Lower + Raise)
 * ,---------+------+------+------+------+------+------+------+------+------+------+------+------.
 * |         |      |      |      |      |      |      |      |      |      |      |      | Del  |
 * |---------`------`------`------`------`------`------`------`------`------`------`------`------|
 * |          |      |      |      |      |AGnorm|AGswap|Qwerty|Mouse |      |Plover|            |
 * |----------`------`------`------`------`------`------`------`------`------`------`------------|
 * |           |      |      |      |      |     |       |      |      |      |      |           |
 * |-----------`------`------`------`------`-----'-------`------`------`------`------`-----------|
 * |        |       |       |       |          |          |         |        |        |  Reset   |
 *  `-------+-------+-------+-------+---^^^----+---^^^----+---------+--------+--------+----------'
 */
    [_ADJUST] = LAYOUT(

        /*,--------+-------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------.*/
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,
        /*|--------`-------`--------`--------`--------`--------`--------`--------`--------`--------`--------`--------`--------|*/
        _______, _______, _______, _______, _______, AG_NORM, AG_SWAP, QWERTY, _______, _______, _______, _______,
        /*|---------`-------`--------`--------`--------`--------`--------`--------`--------`--------`--------`----------------|*/
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        /*|----------`-------`--------`--------`--------`--------`--------`--------`--------`--------`--------`---------------|*/
        _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT),
    /*`----------+-----------+-----------+-----------+----^^^----+----^^^----+-----------+-----------+-----------+--------'*/

    /* VIM
 * ,---------+------+------+------+------+------+------+------+------+------+------+------+------.
 * |         |      |      |      |      |      |      |      |      |      |      |      |      |
 * |---------`------`------`------`------`------`------`------`------`------`------`------`------|
 * |          |      |      |      |      |      | LEFT | DOWN | UP   |RIGHT |      |            |
 * |----------`------`------`------`------`------`------`------`------`------`------`------------|
 * |           |      |      |      |      |     |       |      |      |      |      |           |
 * |-----------`------`------`------`------`-----'-------`------`------`------`------`-----------|
 * |        |       |       |       |          |          |         |        |        |          |
 *  `-------+-------+-------+-------+---^^^----+---^^^----+---------+--------+--------+----------'
 */
    [_VIM] = LAYOUT(
        /*,--------+-------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------.*/
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        /*|--------`-------`--------`--------`--------`--------`--------`--------`--------`--------`--------`--------`--------|*/
        _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, _______, _______,
        /*|---------`-------`--------`--------`--------`--------`--------`--------`--------`--------`--------`----------------|*/
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        /*|----------`-------`--------`--------`--------`--------`--------`--------`--------`--------`--------`---------------|*/
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),
    /*`----------+-----------+-----------+-----------+----^^^----+----^^^----+-----------+-----------+-----------+--------'*/

    /* Media
 * ,---------+------+------+------+------+------+------+------+------+------+------+------+------.
 * |         |      |      |      |      |      |      |      |      |      |      |      |      |
 * |---------`------`------`------`------`------`------`------`------`------`------`------`------|
 * |          |      |      |      |      |      |      | Prev | Next | Mute |      | Play/Pause |
 * |----------`------`------`------`------`------`------`------`------`------`------`------------|
 * |           |      |      |      |      |     |       | VolD | VolU |      |      |           |
 * |-----------`------`------`------`------`-----'-------`------`------`------`------`-----------|
 * |        |       |       |       |          |          |         |        |        |          |
 *  `-------+-------+-------+-------+---^^^----+---^^^----+---------+--------+--------+----------'
 */
    [_MEDIA] = LAYOUT(
        /*,--------+-------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------.*/
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        /*|--------`-------`--------`--------`--------`--------`--------`--------`--------`--------`--------`--------`--------|*/
        _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_MNXT, KC_MUTE, _______, KC_MPLY,
        /*|---------`-------`--------`--------`--------`--------`--------`--------`--------`--------`--------`----------------|*/
        _______, _______, _______, _______, _______, _______, _______, KC_VOLD, KC_VOLU, _______, _______, _______,
        /*|----------`-------`--------`--------`--------`--------`--------`--------`--------`--------`--------`---------------|*/
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______)
    /*`----------+-----------+-----------+-----------+----^^^----+----^^^----+-----------+-----------+-----------+--------'*/
};

void persistant_default_layer_set(uint16_t default_layer)
{
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    switch (keycode)
    {
    case QWERTY:
        if (record->event.pressed)
        {
            default_layer_set(1UL << _QWERTY);
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

/*
 * Macro definition
 */
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    if (!eeconfig_is_enabled())
    {
        eeconfig_init();
    }

    bool use_cmd = true; // Use, for example, Cmd-Tab, Cmd-C, Cmd-V, etc.
    // Compare to MAGIC_SWAP_ALT_GUI and MAGIC_UNSWAP_ALT_GUI configs, set in:
    // quantum/quantum.c
    if (keymap_config.swap_lalt_lgui == 1 && keymap_config.swap_ralt_rgui == 1)
    {
        use_cmd = false; // ... or, Alt-Tab, Ctrl-C, Ctrl-V, etc.
    }

    switch (id)
    {
    case KC_ALT_TAB:
        if (use_cmd)
        {
            return (record->event.pressed ? MACRO(D(LALT), D(TAB), END) : MACRO(U(TAB), END));
        }
        else
        {
            return (record->event.pressed ? MACRO(D(LGUI), D(TAB), END) : MACRO(U(TAB), END));
        }
    case KC_CMD_TAB:
        if (use_cmd)
        {
            return (record->event.pressed ? MACRO(D(LGUI), D(TAB), END) : MACRO(U(TAB), END));
        }
        else
        {
            return (record->event.pressed ? MACRO(D(LALT), D(TAB), END) : MACRO(U(TAB), END));
        }

    case KC_CTL_TAB:
        return (record->event.pressed ? MACRO(D(LCTRL), D(TAB), END) : MACRO(U(TAB), END));
    case KC_CMD_SLSH:
        return (record->event.pressed ? MACRO(D(LGUI), D(SLSH), END) : MACRO(U(SLSH), END));

    case KC_AG_FIND:
        return use_cmd ? MACRODOWN(D(LGUI), T(F), END) : MACRODOWN(D(LCTRL), T(F), END);
    case KC_AG_AGAIN:
        return use_cmd ? MACRODOWN(D(LGUI), T(G), END) : MACRODOWN(D(LCTRL), T(G), END);
    case KC_AG_UNDO:
        return use_cmd ? MACRODOWN(D(LGUI), T(Z), END) : MACRODOWN(D(LCTRL), T(Z), END);
    case KC_AG_CUT:
        return use_cmd ? MACRODOWN(D(LGUI), T(X), END) : MACRODOWN(D(LCTRL), T(X), END);
    case KC_AG_COPY:
        return use_cmd ? MACRODOWN(D(LGUI), T(C), END) : MACRODOWN(D(LCTRL), T(C), END);
    case KC_AG_PASTE:
        return use_cmd ? MACRODOWN(D(LGUI), T(V), END) : MACRODOWN(D(LCTRL), T(V), END);

    case KC_AG_DESK_L:
        return use_cmd ? MACRODOWN(D(LGUI), D(LCTRL), T(SCLN), END) : MACRODOWN(D(LALT), D(LCTRL), T(SCLN), END);
    case KC_AG_DESK_R:
        return use_cmd ? MACRODOWN(D(LGUI), D(LCTRL), T(QUOT), END) : MACRODOWN(D(LALT), D(LCTRL), T(QUOT), END);

    case KC_AG_TAB_C:
        return use_cmd ? MACRODOWN(D(LGUI), T(W), END) : MACRODOWN(D(LCTRL), T(W), END);
    case KC_AG_TAB_N:
        return use_cmd ? MACRODOWN(D(LGUI), T(T), END) : MACRODOWN(D(LCTRL), T(T), END);
    case KC_AG_TAB_R:
        return use_cmd ? MACRODOWN(D(LGUI), D(LSHIFT), T(T), END) : MACRODOWN(D(LCTRL), D(LSHIFT), T(T), END);
    }

    return MACRO_NONE;
}
