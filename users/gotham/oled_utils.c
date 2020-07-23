#include "oled_utils.h"

#ifdef SPLIT_KEYBOARD
static bool is_master;
#endif
#if OLED_CUSTOM_TIMEOUT > 0
static uint32_t oled_sleep_timer;
#    ifdef SPLIT_KEYBOARD
static bool oled_reset_flag;
#    endif
#endif

const char PROGMEM layer_names[][OLED_CHAR_COUNT] = {
    // clang-format off
    [_QWERTY]  = OLED_STR_QWERTY,
    [_COLEMAK] = OLED_STR_COLEMAK,
    [_DVORAK]  = OLED_STR_DVORAK,
    [_WORKMAN] = OLED_STR_WORKMAN,
    [_NORMAN]  = OLED_CHAR_COUNTORMAN,
    [_GAME]    = OLED_STR_GAME,
    [_GAMENUM] = OLED_STR_GAMENUM,
    [_LOWER]   = OLED_STR_LOWER,
    [_RAISE]   = OLED_STR_RAISE,
    [_ADJUST]  = OLED_STR_ADJUST,
    // clang-format on
};

#ifdef ENCODER_ENABLE
const char PROGMEM encoder_mode_names[][OLED_CHAR_COUNT] = {
    // clang-format off
    [ENC_MODE_VOLUME]     = OLED_STR_ENC_MODE_VOLUME,
    [ENC_MODE_WORD_NAV]   = OLED_STR_ENC_MODE_WORD_NAV,
    [ENC_MODE_LEFT_RIGHT] = OLED_STR_ENC_MODE_LEFT_RIGHT,
    [ENC_MODE_UP_DOWN]    = OLED_STR_ENC_MODE_UP_DOWN,
    [ENC_MODE_PAGING]     = OLED_STR_ENC_MODE_PAGING,
    // clang-format on
};
#endif

#ifdef THUMBSTICK_ENABLE
const char PROGMEM thumbstick_mode_names[][OLED_CHAR_COUNT] = {
    // clang-format off
    [THUMBSTICK_MODE_MOUSE]  = OLED_STR_THUMBSTICK_MODE_MOUSE,
    [THUMBSTICK_MODE_ARROWS] = OLED_STR_THUMBSTICK_MODE_ARROWS,
    [THUMBSTICK_MODE_SCROLL] = OLED_STR_THUMBSTICK_MODE_SCROLL,
    // clang-format on
};
#endif

#if OLED_CUSTOM_TIMEOUT > 0
void oled_sleep_timer_reset(void) {
    oled_on();
    oled_sleep_timer = timer_read32();
#    ifdef SPLIT_KEYBOARD
    /* If primary side, announce to transport to reset secondary side (flag cleared by transport).
     * If secondary side, clear flag after after timer is reset.
     */
    oled_reset_flag = is_master;
#    endif
}

#    ifdef SPLIT_KEYBOARD
bool oled_reset_flag_get(void) { return oled_reset_flag; }

void oled_reset_flag_set(bool value) { oled_reset_flag = value; }
#    endif
#endif

__attribute__((weak)) oled_rotation_t oled_init_keymap(oled_rotation_t rotation) { return OLED_ROTATION_0; }

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
#ifdef SPLIT_KEYBOARD
    is_master = is_keyboard_master();
#endif
#if OLED_CUSTOM_TIMEOUT > 0
#    ifdef SPLIT_KEYBOARD
    oled_reset_flag = false;
#    endif
    oled_sleep_timer = timer_read32();
#endif
#if defined(OLED_ANIMATIONS_ENABLED)
#    if defined(OLED_ANIM_STARFIELD)
    oled_init_starfield();
#    elif defined(OLED_ANIM_IMAGE_BOUNCE)
    oled_init_image_bounce();
#    endif
#endif
    return oled_init_keymap(rotation);
}

__attribute__((weak)) bool process_record_keymap_oled(uint16_t keycode, keyrecord_t *record) { return true; }

bool process_record_user_oled(uint16_t keycode, keyrecord_t *record) {
#if OLED_CUSTOM_TIMEOUT > 0
    oled_sleep_timer_reset();
#endif
#if defined(OLED_ANIMATIONS_ENABLED) && defined(OLED_ANIM_STARFIELD)
    random16_add_entropy(keycode);
#endif
    return process_record_keymap_oled(keycode, record);
}

void oled_task_user(void) {
#if OLED_CUSTOM_TIMEOUT > 0
    if (timer_elapsed32(oled_sleep_timer) > OLED_CUSTOM_TIMEOUT) {
        oled_off();
#    if defined(OLED_ANIMATIONS_ENABLED) && defined(OLED_ANIM_STARFIELD_WANDER)
        erase_stars();
        set_starfield_center();
#    endif
        return;
    }
#endif
    render_status();
}

void render_keyboard_info(void) {
    oled_advance_page(false);
    oled_write_ln_P(PSTR(QMK_KEYBOARD), false);
    oled_write_ln_P(PSTR(QMK_KEYMAP), false);
}

void render_layout(void) {
    oled_write_P(PSTR(OLED_STR_LAYOUT), false);
    uint32_t layer = get_highest_layer(layer_state);
    layer          = ((layer == _GAME) || (layer == _GAMENUM)) ? _GAME : get_highest_layer(default_layer_state);
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

#ifdef THUMBSTICK_ENABLE
void render_thumbstick(void) {
    oled_write_P(PSTR(OLED_STR_THUMBSTICK_MODE), false);
    oled_write_ln_P(thumbstick_mode_names[thumbstick_mode_get()], false);
}
#endif

__attribute__((weak)) void render_status_main(void) {
    render_layout();
    render_layer();
#ifdef ENCODER_ENABLE
    render_encoders();
#endif
#ifdef THUMBSTICK_ENABLE
    render_thumbstick();
#endif
}

__attribute__((weak)) void render_status_secondary(void) {
#ifdef OLED_ANIMATIONS_ENABLE
#    if defined(OLED_ANIM_STARFIELD)
    render_starfield();
#    elif defined(OLED_ANIM_IMAGE_BOUNCE)
    render_image_bounce();
#    endif
#else
    render_keyboard_info();
#endif
}

void render_status(void) {
#ifdef SPLIT_KEYBOARD
    if (is_master)
#endif
    {
        render_status_main();
    }
#ifdef SPLIT_KEYBOARD
    else {
        render_status_secondary();
    }
#endif
}
