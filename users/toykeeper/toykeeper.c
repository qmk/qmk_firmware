/* Copyright 2021-2022 Selene ToyKeeper
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

#include "toykeeper.h"

#ifdef HAS_RGB
// highlight color for each layer while active
__attribute__ ((weak)) const uint8_t layer_colors[][3] = {
    [L_QWERTY  ] = {0,0,0},
    [L_DVORAK  ] = {0,0,0},
    [L_UNDVORAK] = {0,0,0},
    [L_COLEMAK ] = {0,0,0},
    #ifdef USE_NUMPAD
    [L_NUMPAD  ] = {192,0,0},
    #endif
    #ifdef HAS_F_ROW
    [L_FLCK    ] = {50,10,0},   // yellow
    #endif
    #ifdef USE_PALM  // palm Fn keys
    [L_LPALM   ] = {224,0,80},  // left palm key
    [L_RPALM   ] = {224,0,16},  // right palm key
    [L_BOTH    ] = {0,50,25},   // both palm keys
    #else  // regular Fn keys
    [L_MOUSE   ] = {224,0,16},  // bubble gum pink
    [L_FN1     ] = {224,0,80},  // neon purple-ish
    [L_FN2     ] = {0,50,25},   // teal
    #endif
    #ifdef HAS_XTRA_COLUMN
    [L_XC1     ] = {224,0,80},  // neon purple-ish
    [L_XC2     ] = {0,50,25},   // teal
    [L_XC3     ] = {224,0,16},  // bubble gum pink
    #endif
};
__attribute__ ((weak)) const uint8_t layer_indicator_colors[][6] = {
    // l, x,y, r,g,b
    #ifdef USE_NUMPAD
    { L_NUMPAD  , 0,0, 192,  0,  0 },
    #endif
    #ifdef USE_PALM  // palm Fn keys
    { L_LPALM   , 1,3, 255,200,200 },
    { L_RPALM   , 6,7, 255,200,200 },
    { L_BOTH    , 1,3, 255,255, 30 },
    { L_BOTH    , 6,7, 255,255, 30 },
    #else  // regular Fn keys
    { L_MOUSE   , 0,0, 255,200,200 },
    { L_FN1     , 0,0, 255,200,200 },
    { L_FN2     , 0,0, 255,255, 30 },
    #endif
    { 0         , 0,0,   0,  0,  0 },  // stop
};
__attribute__ ((weak)) const uint8_t mod_colors[] = {100, 224, 80};
__attribute__ ((weak)) const uint8_t mod_indicator_coords[][3] = {
    // mod, x, y
    { 1, 0, 2, },  // L Shift
    { 1, 7, 6, },  // R Shift
    { 2, 0, 0, },  // L Ctrl
    { 2, 7, 4, },  // R Ctrl
    { 3, 0, 1, },  // L Alt
    { 3, 7, 5, },  // R Alt
    { 4, 0, 3, },  // L GUI
    { 4, 7, 7, },  // R GUI
    { 0, 0, 0, },  // stop
};

#endif

#ifndef DONT_USE_EEPROM
user_config_t user_config;
uint8_t boot_complete = 0;
#endif

#ifdef HAS_DIPSWITCH
uint8_t switch_active = 0;
#endif

#ifndef DONT_USE_ANY_KEY
// the "Any" key emits any type-able symbol
deferred_token any_key_token;
uint32_t any_key_cb(uint32_t time, void *arg);
void tap_random_key(void);
#endif


#ifdef HAS_RGB
#ifdef RGB_INDICATORS_RETURN_BOOL  // function signature changed 2022-11
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
#else
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
#endif
    // indicate current status on the RGB matrix
    // (active modifiers and each active non-base layer)

    // light up all keys defined in an active non-base layer
    uint8_t top = get_highest_layer(layer_state);
    if (top >= L_BOTTOM)
    {
        // light up each key according to the
        // highest active non-base layer which defines it
        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];

                if ((index >= led_min) && (index <= led_max) && (index != NO_LED)) {
                    uint16_t kc = 0;
                    for (uint8_t layer=top; (layer>=L_BOTTOM) && (kc<=KC_TRNS); layer--) {
                        if (IS_LAYER_ON(layer)) {
                            kc = keymap_key_to_keycode(layer, (keypos_t){col,row});
                            if (kc > KC_TRNS) {
                                rgb_matrix_set_color(index,
                                        layer_colors[layer][0],
                                        layer_colors[layer][1],
                                        layer_colors[layer][2]
                                        );
                            }  // hooray for deep nesting
                        }
                    }
                }
            }
        }
    }

    // light up the indicator key for each active layer with an indicator
    for (uint8_t i=0; ; i++) {
        uint8_t l = layer_indicator_colors[i][0];
        uint8_t x = layer_indicator_colors[i][1];
        uint8_t y = layer_indicator_colors[i][2];
        uint8_t r = layer_indicator_colors[i][3];
        uint8_t g = layer_indicator_colors[i][4];
        uint8_t b = layer_indicator_colors[i][5];
        if (! l) break;
        if (IS_LAYER_ON(l)) {
            uint8_t index = g_led_config.matrix_co[y][x];
            rgb_matrix_set_color(index, r, g, b);
        }
    }

    // light up each active modifier key
    for (uint8_t i=0; ; i++) {
        uint8_t m = mod_indicator_coords[i][0];
        uint8_t x = mod_indicator_coords[i][1];
        uint8_t y = mod_indicator_coords[i][2];
        uint8_t state = 0;
        if (! m) break;
        switch (m) {
            case 1:  // shift
                if (is_caps_word_on() || 
                    ((get_mods() | get_oneshot_mods()) & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))))
                    state = 1;
                break;
            case 2:  // ctrl
                if ((get_mods() | get_oneshot_mods()) & (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL)))
                    state = 1;
                break;
            case 3:  // alt
                if ((get_mods() | get_oneshot_mods()) & (MOD_BIT(KC_LALT) | MOD_BIT(KC_RALT)))
                    state = 1;
                break;
            case 4:  // gui
                if ((get_mods() | get_oneshot_mods()) & (MOD_BIT(KC_LGUI) | MOD_BIT(KC_RGUI)))
                    state = 1;
                break;
        }
        if (state) {
            uint8_t index = g_led_config.matrix_co[y][x];
            rgb_matrix_set_color(index, mod_colors[0], mod_colors[1], mod_colors[2]);
        }
    }

    #ifdef RGB_INDICATORS_RETURN_BOOL
    return true;
    #endif
}
#endif  // ifdef HAS_RGB


#ifndef HAS_DIPSWITCH
#define set_df_layer(layer) set_single_persistent_default_layer(layer)
#else  // HAS_DIPSWITCH
void set_df_layer(uint8_t layer) {
    // activate a new default layer,
    // but also handle dipswitch interaction,
    // and remember it in eeprom for later

    uint8_t prev_layer;

    // save this layer to the current switch position
    if (switch_active) {
        prev_layer = user_config.switch_on;
        user_config.switch_on = layer;
    } else {
        prev_layer = user_config.switch_off;
        user_config.switch_off = layer;
    }

    // activate the layer
    default_layer_set(1UL << layer);

    #ifndef DONT_USE_EEPROM
    // save the config to persistent storage, if it changed
    // (avoid unnecessary eep writes)
    if (prev_layer != layer) {
        if (boot_complete) {
            eeconfig_update_user(user_config.raw);
        }
    }
    #endif  // ifndef DONT_USE_EEPROM
}
#endif  // if HAS_DIPSWITCH


#ifdef HAS_XTRA_COLUMN
// Xtra Column layers work like base layers... but on only a few keys
void set_xc_layer(uint8_t layer) {
    // activate layer if > 0
    // ... and deactivate all other XC layers > 0
    for (uint8_t i=1; i<=3; i++) {
        if (i == layer) { layer_on(L_XC1 + i - 1); }
        else { layer_off(L_XC1 + i - 1); }
    }
}
#endif


#if defined(HAS_DIPSWITCH) && !defined(DONT_USE_EEPROM)
bool dip_switch_update_user(uint8_t index, bool active) {
    // the toggle switch moved (next to the USB port)
    if (0 == index) {  // switch 0 is the only switch, but it doesn't hurt to check
        // save the state for use elsewhere
        switch_active = active;
        // look up base layer for this slot, and activate it
        if (switch_active)
            default_layer_set(1UL << user_config.switch_on);
        else
            default_layer_set(1UL << user_config.switch_off);
    }
    // mischief managed; don't process again in parent code
    return false;
}
#endif


#ifndef DONT_USE_EEPROM
void keyboard_post_init_user(void) {
    // on boot, load the user config from persistent storage
    user_config.raw = eeconfig_read_user();

    #ifdef HAS_DIPSWITCH
        // ... and restore the last-used layout
        if (switch_active)
            set_df_layer(user_config.switch_on);
        else
            set_df_layer(user_config.switch_off);
    #endif

    #ifdef HAS_F_ROW
        // ... and restore the f-lock setting
        if (user_config.f_lock) layer_on(L_FLCK);
    #endif

    // allow normal processing after this point
    boot_complete = 1;
}


void eeconfig_init_user(void) {
    // eep is getting reset; give it some sane defaults
    user_config.raw = 0;

    #ifdef HAS_DIPSWITCH
        user_config.switch_off = 0;  // qwerty
        user_config.switch_on = 1;   // dvorak
    #endif
    #ifdef HAS_F_ROW
        user_config.f_lock = 0;      // regular F1-F12 keys by default
    #endif
    #ifndef DONT_USE_TK_IUUI
        user_config.dvoriuk = 0;         // don't swap keys on dvorak layer
    #endif

    eeconfig_update_user(user_config.raw);
}
#endif  // ifndef DONT_USE_EEPROM


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // custom behaviors which don't fit into a keymap
    switch(keycode) {

        #ifndef DONT_USE_TK_INFO
        // show build info / version
        case TK_INFO:
            if (record->event.pressed) {
                SEND_STRING("QMK " QMK_VERSION " "
                            "[" QMK_KEYBOARD ":" QMK_KEYMAP "]"
                            ", Build date " QMK_BUILDDATE
                            ", Keymap: " KEYMAP_URL
                            );
            }
            return false;
        #endif  // ifndef DONT_USE_TK_INFO

        #ifndef DONT_USE_ANY_KEY
        // random character (with auto-repeat)
        case TK_ANY:
            if (record->event.pressed) {
                tap_random_key();
                any_key_token = defer_exec(AUTOREPEAT_DELAY, any_key_cb, NULL);
            } else {
                cancel_deferred_exec(any_key_token);
            }
            return false;
        #endif  // ifndef DONT_USE_ANY_KEY

        #ifdef USE_PALM  // palm keys

        // I was going to do something fancy here... but meh

        #else  // no palm keys

        // hold = momentary(L_FN1)
        // tap = layer_off(L_FN1)
        // 2tap+ = layer_on(L_FN1)
        // (don't enable it on 1st tap, because sometimes I do that by accident)
        case TK_MOON:
            if ((1 == record->tap.count) && record->event.pressed) {
                layer_off(L_FN1);  // TG(L_FN1) off
                return false;
            } else if (record->event.pressed) {
                layer_on(L_FN1);  // MO(L_FN1) on, TG(L_FN1) on
                return false;
            }
            else if (!(record->tap.count) && !(record->event.pressed)) {
                layer_off(L_FN1);  // MO(L_FN1) off
                return false;
            }
            break;

        #endif  // ifdef USE_PALM

        // RGUI key does a few things...
        // - hold: RGUI
        // - tap: toggle one-shot RALT
        // - tap, pause, hold: RGUI + one-shot RALT
        // - tap-hold: momentary RALT
        // ... and if there's no dedicated key for the mouse layer:
        // - tap-tap: toggle mouse layer
        // - tap-tap-hold: momentary RALT
        case TK_RGUI:
        #ifdef USE_TK_LGUI
        case TK_LGUI:
            {
                // use the same logic on both keys
                uint16_t this_ALT = KC_RALT;
                uint16_t this_GUI = KC_RGUI;
                if (keycode == TK_LGUI) {
                    this_ALT = KC_LALT;
                    this_GUI = KC_LGUI;
                }
        #else
                #define this_ALT KC_RALT
                #define this_GUI KC_RGUI
        #endif  // ifdef USE_TK_LGUI

                if ((1 == record->tap.count) && record->event.pressed) {
                    if (get_oneshot_mods() & (MOD_BIT(KC_LALT) | MOD_BIT(KC_RALT))) {
                        del_oneshot_mods(MOD_BIT(this_ALT));  // undo OSM(RALT) if tapped again
                    } else {
                        add_oneshot_mods(MOD_BIT(this_ALT));  // do OSM(RALT) on tap
                    }
                    return false;
                #ifdef USE_RGUI_2TAP_MOUSELOCK
                } else if ((2 == record->tap.count) && record->event.pressed) {
                    del_oneshot_mods(MOD_BIT(this_ALT));  // undo OSM(RALT)
                    layer_invert(L_MOUSE);  // TG(L_MOUSE)
                    return false;
                #endif
                } else if ((record->tap.count > 0) && (record->event.pressed)) {  // momentary RALT
                    del_oneshot_mods(MOD_BIT(this_ALT));  // undo OSM(RALT)
                    unregister_mods(MOD_BIT(this_GUI));
                    register_mods(MOD_BIT(this_ALT));
                    #ifdef USE_RGUI_2TAP_MOUSELOCK
                    layer_invert(L_MOUSE);  // undo mouse layer change
                    #endif
                    return false;
                } else if ((record->tap.count > 0) && !(record->event.pressed)) {
                    unregister_mods(MOD_BIT(this_ALT));
                    return false;
                } else if (record->event.pressed) {  // RGUI on first hold
                    register_mods(MOD_BIT(this_GUI));
                    return false;
                } else if (!(record->tap.count) && !(record->event.pressed)) {
                    unregister_mods(MOD_BIT(this_GUI));
                    return false;
                }
        #ifdef USE_TK_LGUI
            }
        #endif
            break;

        #ifdef USE_NUMPAD
        // - hold: RCTL
        // - tap: toggle L_NUMPAD
        case TK_RCTL:
            if (record->tap.count && record->event.pressed) {
                layer_invert(L_NUMPAD);
                return false;
            }
            break;
        #endif

        // save preferred layer into slot for later access via toggle switch
        case TK_DF_0 ... TK_DF_3:
            if (record->event.pressed) set_df_layer(keycode - TK_DF_0);
            return false;

        #ifdef HAS_XTRA_COLUMN
        // choose a base layer for Xtra Column keys
        case TK_XC_0 ... TK_XC_3:
            if (record->event.pressed) set_xc_layer(keycode - TK_XC_0);
            return false;
        #endif

        #ifndef DONT_USE_TK_IUUI
        case TK_IUUI:  // toggle whether U and I are swapped in dvorak layer
            if (record->event.pressed) {
                user_config.dvoriuk = !user_config.dvoriuk;
                eeconfig_update_user(user_config.raw);
            }
            break;

        // dvorak / dvoriuk overrides
        case KC_U:
            if (IS_LAYER_ON_STATE(default_layer_state, L_DVORAK) && user_config.dvoriuk) {
                if (record->event.pressed)
                    register_code(KC_I);
                else
                    unregister_code(KC_I);
                return false;
            }
            break;
        case KC_I:
            if (IS_LAYER_ON_STATE(default_layer_state, L_DVORAK) && user_config.dvoriuk) {
                if (record->event.pressed)
                    register_code(KC_U);
                else
                    unregister_code(KC_U);
                return false;
            }
            break;
        #endif  // ifndef DONT_USE_TK_IUUI

        #ifdef HAS_F_ROW
        case TG(L_FLCK):  // remember F-Lock setting between boots
            if (record->event.pressed) {
                user_config.f_lock = !(IS_LAYER_ON(L_FLCK));  // invert because layer hasn't been toggled yet
                eeconfig_update_user(user_config.raw);
            }
            return true;  // let QMK do the rest
        #endif  // ifdef HAS_F_ROW

    }
    return true;  // send un-handled events to parent for processing
}


#ifdef USE_CAPSWORD_KLUDGE
bool caps_word_press_user(uint16_t keycode) {
    switch(keycode) {

        // Keycodes that continue CapsWord, with shift applied.
        case KC_A ... KC_Z:
        case KC_MINS:
            add_weak_mods(MOD_BIT(KC_LSFT));
            return true;

        // Keycodes that continue CapsWord, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:  // _ is complicated with multiple layouts
            return true;

        // this is the "kludge" part
        // CapsWord interacts badly with host-mapped dvorak, so be more permissive
        case KC_COMM:
        case KC_DOT:
        case KC_SCLN:
        case KC_QUOT:
        case KC_SLSH:
            add_weak_mods(MOD_BIT(KC_LSFT));
            return true;

        // Deactivate CapsWord.
        default:
            return false;

    }
}
#endif  // ifdef USE_CAPSWORD_KLUDGES


#ifndef DONT_USE_ANY_KEY
uint32_t any_key_cb(uint32_t time, void *arg) {
    tap_random_key();
    return AUTOREPEAT_MS;
}

// like tap_random_base64(), but generates a wider range of symbols
void tap_random_key(void) {
    char punc[] = ",.<>/?'\";:!@#$%^&*()[]{}-_=+\\|`~";
    uint8_t key = rand() % (26 + 26 + 10 + sizeof(punc));
    switch (key) {
        case 0 ... 25:
            send_char(  0 + key + 'A');
            break;
        case 26 ... 51:
            send_char(-26 + key + 'a');
            break;
        case 52 ... 61:
            send_char(-52 + key + '0');
            break;
        default:
            send_char(punc[-62 + key]);
            break;
    }
}
#endif  // ifndef DONT_USE_ANY_KEY
