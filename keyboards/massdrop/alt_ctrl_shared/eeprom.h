#ifndef MD_ALT_CTRL_SHARED_EEPROM
#define MD_ALT_CTRL_SHARED_EEPROM

typedef union {
  uint32_t raw;
  struct {
    uint8_t led_animation_id: 3,
            led_lighting_mode: 2,
            led_animation_breathing: 1,
            led_enabled: 1,
            led_animation_direction: 1;
    uint8_t gcr_desired;
    uint8_t led_animation_speed;
    uint8_t nkro: 1,
            _unused: 7;
  };
} kb_config_t;

kb_config_t kb_config;

void load_saved_settings(void) {
    kb_config.raw = eeconfig_read_kb();

    led_animation_id = kb_config.led_animation_id;
    gcr_desired = kb_config.gcr_desired;
    led_lighting_mode = kb_config.led_lighting_mode;
    keymap_config.nkro = kb_config.nkro;

    bool prev_led_animation_breathing = led_animation_breathing;
    led_animation_breathing = kb_config.led_animation_breathing;
    if (led_animation_breathing && !prev_led_animation_breathing) {
        gcr_breathe = gcr_desired;
        led_animation_breathe_cur = BREATHE_MIN_STEP;
        breathe_dir = 1;
    }

    led_animation_direction = kb_config.led_animation_direction;
    led_animation_speed = kb_config.led_animation_speed;

    bool led_enabled = kb_config.led_enabled;
    I2C3733_Control_Set(led_enabled);

#ifdef CONSOLE_ENABLE
    uprintf("Loading saved settings from EEPROM:\n");
    uprintf("  led_animation_id %d\n", led_animation_id);
    uprintf("  gcr_desired %d\n", gcr_desired);
    uprintf("  led_lighting_mode %d\n", led_lighting_mode);
    uprintf("  nkro %d\n", keymap_config.nkro);
    uprintf("  led_animation_breathing %d\n", led_animation_breathing);
    uprintf("  led_animation_direction %d\n", led_animation_direction);
    uprintf("  led_animation_speed %f\n", led_animation_speed);
    uprintf("  led_enabled %d\n", led_enabled);
#endif
}

void save_settings(void) {
    // Save the keyboard config to EEPROM
    eeconfig_update_kb(kb_config.raw);
#ifdef CONSOLE_ENABLE
    uprintf("Saving settings to EEPROM\n");
#endif
}

void sync_settings(void) {
    save_settings();
    load_saved_settings();
}

void keyboard_post_init_kb(void) {
#ifdef CONSOLE_ENABLE
    uprintf("Running keyboard post-init\n");
#endif
    load_saved_settings();
}

void eeconfig_init_kb(void) {
#ifdef CONSOLE_ENABLE
    uprintf("Running eeconfig_init_kb\n");
#endif
    kb_config.raw = 0;
    kb_config.led_animation_id = 0;
    kb_config.led_lighting_mode = 0;
    kb_config.led_animation_breathing = false;
    kb_config.led_enabled = true;
    kb_config.led_animation_direction = 1;
    kb_config.gcr_desired = LED_GCR_MAX;
    kb_config.led_animation_speed = 4;
    kb_config.nkro = keymap_config.nkro;

    save_settings();
}

void led_pattern_next(void) {
    kb_config.led_animation_id = (kb_config.led_animation_id + 1) % led_setups_count;
    sync_settings();
}

void led_pattern_prev(void) {
    kb_config.led_animation_id = (kb_config.led_animation_id - 1) % led_setups_count;
    sync_settings();
}

void led_mode_next(void) {
    kb_config.led_lighting_mode = (kb_config.led_lighting_mode + 1) % LED_MODE_MAX_INDEX;
    sync_settings();
}

void gcr_desired_increase(void) {
    int brightness = kb_config.gcr_desired + LED_GCR_STEP;
    kb_config.gcr_desired = brightness > LED_GCR_MAX ? LED_GCR_MAX : brightness;
    sync_settings();
}

void gcr_desired_decrease(void) {
    int brightness = kb_config.gcr_desired - LED_GCR_STEP;
    kb_config.gcr_desired = brightness < 0 ? 0 : brightness;
    sync_settings();
}

void led_set_enabled(bool enabled) {
    kb_config.led_enabled = enabled;
    sync_settings();
}

void led_set_animation_breathing(bool breathing) {
    kb_config.led_animation_breathing = breathing;
    sync_settings();
}

void led_animation_speed_increase(void) {
    kb_config.led_animation_speed += 1;
    sync_settings();
}

void led_animation_speed_decrease(void) {
    kb_config.led_animation_speed = kb_config.led_animation_speed < 1
        ? 0
        : kb_config.led_animation_speed - 1;
    sync_settings();
}

void nkro_toggle(void) {
    kb_config.nkro = !kb_config.nkro;
    sync_settings();
}

keymap_config_t keymap_config;

#endif