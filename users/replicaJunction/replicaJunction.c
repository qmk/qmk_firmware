#include "replicaJunction.h"
#include "version.h"

#ifdef TAP_DANCE_ENABLE
void dance_layer(qk_tap_dance_state_t *state, void *user_data)
{
    uint8_t layer = biton32(layer_state);

    if (state->count >= 5)
    {
        // 5 or more taps resets the keyboard
        reset_keyboard();
    }
    #ifdef L_QWERTY
    else if (state->count == 3)
    {
        // Triple tap changes to QWERTY layer
        if (layer == L_QWERTY)
        {
            layer_off(L_QWERTY);
        }
        else
        {
            layer_on(L_QWERTY);
        }
    }
    #endif
    #ifdef L_NUM
    else if (state->count == 2)
    {
        // Double tap toggles Number layer
        if (layer == L_NUM)
        {
            layer_off(L_NUM);
        }
        else
        {
            layer_on(L_NUM);
        }
    }
    #endif
    else
    {
        // Single tap sends Escape, and also turns off layers
        // That's mostly in case I get stuck and forget where I am
        #ifdef L_NUM
        layer_off(L_NUM);
        #endif
        #ifdef L_EXTEND
        layer_off(L_EXTEND);
        #endif
        #ifdef L_SYMBOL
        layer_off(L_SYMBOL);
        #endif
        #ifdef L_QWERTY
        layer_off(L_QWERTY);
        #endif
        register_code(KC_ESC);
        unregister_code(KC_ESC);
    }
};

// Tap Dance Definitions
// Note - this needs to come AFTER the function is declared
qk_tap_dance_action_t tap_dance_actions[] = {
        [TD_LAYER_TOGGLE] = ACTION_TAP_DANCE_FN(dance_layer)
};

#endif // TAP_DANCE_ENABLE

// These functions can be overridden in individual keymap files.
// This allows a user function to be shared for all my keyboards, while each
// keyboard can also have a keyboard-specific section.

// Note that keymaps don't need to override these if there's nothing to
// override them with.
__attribute__ ((weak))
void matrix_init_keymap(void) {}

__attribute__ ((weak))
void matrix_scan_keymap(void) {}

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
        return true;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    #ifdef UNICODEMAP_ENABLE
    // Set Unicode input to use WinCompose
    // https://github.com/samhocevar/wincompose
    set_unicode_input_mode(UC_WINC);
    #endif // UNICODEMAP_ENABLE

    matrix_init_keymap();
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
    matrix_scan_keymap();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed)
        return true;

    switch(keycode)
    {
        case RJ_MAKE:  // Compiles the firmware, and adds the flash command based on keyboard bootloader
            SEND_STRING("make " QMK_KEYBOARD ":" QMK_KEYMAP
            #if  (defined(BOOTLOADER_DFU) || defined(BOOTLOADER_LUFA_DFU) || defined(BOOTLOADER_QMK_DFU))
                                    ":dfu"
            #elif defined(BOOTLOADER_HALFKAY)
                                    ":teensy"
            #elif defined(BOOTLOADER_CATERINA)
                                    ":avrdude"
            #endif // bootloader options
                                    //SS_TAP(X_ENTER)
                                    );
            return false;
        case RJ_QMKV:
            SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
            return false;
        case RJ_EQ:
            SEND_STRING("==");
            return false;
        case RJ_NEQ:
            SEND_STRING("!=");
            return false;
        case RJ_GEQ:
            SEND_STRING(">=");
            return false;
        case RJ_LEQ:
            SEND_STRING("<=");
            return false;
        case RJ_GEQR:
            SEND_STRING("=>");
            return false;
        case RJ_DUND:
            SEND_STRING("$_");
            return false;
        case RJ_SELS:
            SEND_STRING("select *");
            return false;
    }

    return process_record_keymap(keycode, record);
};
