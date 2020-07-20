#include "oled_utils.h"

static bool     is_master;
// static uint16_t oled_sleep_timer;

const char PROGMEM layer_names[][OLED_CHAR_COUNT] = {
    [_QWERTY] = OLED_STR_QWERTY,
    [_COLEMAK] = OLED_STR_COLEMAK,
    [_DVORAK] = OLED_STR_DVORAK,
    [_WORKMAN] = OLED_STR_WORKMAN,
    [_NORMAN] = OLED_CHAR_COUNTORMAN,
    [_GAME] = OLED_STR_GAME,
    [_GAMENUM] = OLED_STR_GAMENUM,
    [_LOWER] = OLED_STR_LOWER,
    [_RAISE] = OLED_STR_RAISE,
    [_ADJUST] = OLED_STR_ADJUST,
};

#ifdef ENCODER_ENABLE
const char PROGMEM encoder_mode_names[][OLED_CHAR_COUNT] = {
    [ENC_MODE_VOLUME] = OLED_STR_ENC_MODE_VOLUME,
    [ENC_MODE_WORD_NAV] = OLED_STR_ENC_MODE_WORD_NAV,
    [ENC_MODE_LEFT_RIGHT] = OLED_STR_ENC_MODE_LEFT_RIGHT,
    [ENC_MODE_UP_DOWN] = OLED_STR_ENC_MODE_UP_DOWN,
    [ENC_MODE_PAGING] = OLED_STR_ENC_MODE_PAGING,
};
#endif

// void oled_sleep_timer_reset(void) { oled_sleep_timer = timer_read(); }

__attribute__((weak)) oled_rotation_t oled_init_keymap(oled_rotation_t rotation) {
    is_master = is_keyboard_master();
    return OLED_ROTATION_0;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    // oled_sleep_timer_reset();
#if defined(OLED_ANIMATIONS_ENABLED) && defined(OLED_ANIM_STARFIELD)
    oled_init_starfield();
#elif defined(OLED_ANIMATIONS_ENABLED) && defined(OLED_ANIM_DVD_LOGO)
    oled_init_dvd_logo();
#endif
    return oled_init_keymap(rotation);
}

__attribute__((weak)) bool process_record_keymap_oled(uint16_t keycode, keyrecord_t *record) {
    // oled_sleep_timer_reset();
#if defined(OLED_ANIMATIONS_ENABLED) && defined(OLED_ANIM_STARFIELD)
    random16_add_entropy(keycode);
#endif
    return true;
}

void oled_task_user(void) {
//     if (timer_elapsed(oled_sleep_timer) >= 30000) {
//         oled_off();
// #if defined(OLED_ANIMATIONS_ENABLED) && defined(OLED_ANIM_STARFIELD_WANDER)
//         erase_stars();
//         set_starfield_center();
// #endif
//         return;
//     }
    render_status();
}

void render_layout(void) {
    oled_write_P(PSTR(OLED_STR_LAYOUT), false);
    uint32_t layer = get_highest_layer(layer_state);
    layer = ((layer == _GAME) || (layer == _GAMENUM)) ? _GAME : get_highest_layer(default_layer_state);
    oled_write_ln_P(layer_names[layer], false);
}

void render_layer(void) {
    oled_write_P(PSTR(OLED_STR_LAYER), false);
    uint32_t layer = get_highest_layer(layer_state);
    oled_write_ln_P(((!layer || (layer == _GAME)) ? PSTR(OLED_STR_LAYER_NONE) : layer_names[layer]), false);
}

#ifdef ENCODER_ENABLE
void render_encoder(uint8_t index) {
    char encoder_index[OLED_CHAR_COUNT] = "";
    snprintf(encoder_index, OLED_CHAR_COUNT, OLED_STR_ENC_MODE, index + 1);
    oled_write(encoder_index, false);
    oled_write_ln_P(encoder_mode_names[encoder_mode_get(index)], false);
}

static pin_t encoders_pad[] = ENCODERS_PAD_A;
#    ifdef SPLIT_KEYBOARD
#        define NUMBER_OF_ENCODERS (2 * sizeof(encoders_pad) / sizeof(pin_t))
#    else
#        define NUMBER_OF_ENCODERS (sizeof(encoders_pad) / sizeof(pin_t))
#    endif
void render_encoders(void) {
    for (uint8_t i = 0; i < NUMBER_OF_ENCODERS; i++) {
        render_encoder(i);
    }
}
#endif

// #ifdef THUMBSTICK_ENABLE
// void render_thumbstick(thumbstick_mode_t mode) {
//     switch (mode) {
//         case THUMBSTICK_MODE_MOUSE:
//             oled_write_P(PSTR("Mouse"), false);
//             break;
//         case THUMBSTICK_MODE_ARROWS:
//             oled_write_P(PSTR("Arrows"), false);
//             break;
//         case THUMBSTICK_MODE_SCROLL:
//             oled_write_P(PSTR("Scroll"), false);
//             break;
//         default:
//             oled_write_P(PSTR("???\n"), false);
//     }
// }
// #endif

__attribute__((weak)) void render_status_main(void) {
    render_layout();
    render_layer();
#ifdef ENCODER_ENABLE
    render_encoders();
#endif
    // #ifdef THUMBSTICK_ENABLE
    //     render_thumbstick();
    // #endif
}

__attribute__((weak)) void render_status_secondary(void) {
#ifdef OLED_ANIMATIONS_ENABLE
#    if defined(OLED_ANIM_STARFIELD)
    render_starfield();
#    elif defined(OLED_ANIM_DVD_LOGO)
    render_dvd_logo();
#    endif
#endif
}

void render_status(void) {
    if (is_master) {
        render_status_main();
    } else {
        render_status_main();
        // render_status_secondary();
    }
}
