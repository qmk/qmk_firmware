#include QMK_KEYBOARD_H

#ifdef OLED_ENABLE
enum layers {
    _BASE = 0,
    _MOVE = 1,
    _NUM = 2,
    _SETTINGS = 3,
};

enum encoder_modes {
    _PAGE = 0,
    _MOUSE = 1,
    _MUSIC = 2,
    _RGB = 3,
};

#define ANIM_FRAME_DURATION 50  // how long each frame lasts in ms
#define BEGINING 0
#define MIDDLE 1
#define END 2

//#define SPLASH
#ifdef SPLASH
static uint8_t startup = 3;
#endif // SPLASH
static uint32_t uptime_timer = 0;
static uint32_t anim_timer = 0;
static uint8_t loop_circle = 0;

// exported variables :
enum encoder_modes encoder_mode = _PAGE;
#define RGBLIGHT_LIMIT_VAL 224
#define RGBLIGHT_DEFAULT_VAL 0
uint8_t base_val = RGBLIGHT_DEFAULT_VAL;
uint8_t base_hue = RGBLIGHT_DEFAULT_HUE;
uint8_t base_sat = RGBLIGHT_DEFAULT_SAT;


#define PROGRESS_BAR_SIZE 16
static const char empty_bar[] = {0x83, 0x84, 0x85, 0x0};

enum cat_states {
    SITTING = 0,
    LICKING,
    SLEEPY,
    ASLEEP,
    STANDING,
    JUMPING,
    RUNNING,
};

static enum cat_states cat_state = ASLEEP;
static uint8_t cat_idle_frame = 0;
static bool cat_running_right = true;
static uint8_t tail_frame = 0;
static uint8_t sleepy_frame = 0;
static uint8_t count_timer = 0;
static uint8_t sleep_timer = 0;
static uint8_t cat_pos[2] = {0, 0};
static uint32_t anim_sleep = 0;

#define CAT_SLEEP_COUNT_TIMEOUT 200
#define CAT_FRAME_DURATION 200

void render_uptime(void) {
    static char str_sleep[11];
    oled_write_P(PSTR("Cd:"), false);
    ultoa(sync_timer_elapsed32(anim_sleep) >> 10, str_sleep, 10);
    //ultoa((OLED_TIMEOUT - sync_timer_elapsed32(anim_sleep)) / 1000, str_sleep, 10);
    oled_write(str_sleep, false);
    //oled_write_P(PSTR("kims"), false);
    oled_write_P(PSTR("s"), false);
    oled_advance_page(true);

    static char str_uptime[11];
    oled_write_P(PSTR("Up:"), false);
    ultoa(sync_timer_elapsed32(uptime_timer) >> 10, str_uptime, 10);
    //ultoa(sync_timer_elapsed32(uptime_timer) / 1000, str_uptime, 10);
    oled_write(str_uptime, false);
    //oled_write_P(PSTR("kims"), false);
    oled_write_P(PSTR("s"), false);
    //oled_advance_page(true); // should be useless but prevent slave oled from turning on ??
}

#define rot8(x,k) (((x) << (k))|((x) >> (8 - (k))))
uint8_t jsf8(void) {
	static uint8_t a = 0xf1, b = 0xee, c = 0xee, d = 0xee, e;
	e = a - rot8(b, 1);
	a = b ^ rot8(c, 4);
	b = c + d;
	c = d + e;
	return d = e + a;
}

void render_cat(uint16_t bit_mask) {
    if (sync_timer_elapsed32(anim_timer) > CAT_FRAME_DURATION) {
        oled_clear();
        oled_set_cursor(cat_pos[0], cat_pos[1]);

        switch(cat_state) {
            case SITTING:
                if (!cat_running_right) {
                    oled_set_cursor(cat_pos[0], cat_pos[1]);
                }
                oled_write_char(0xA4 + tail_frame, false);
                oled_write_char(0xAE + cat_idle_frame, false);

                count_timer++;
                if (count_timer >= 20) {
                    cat_idle_frame = (cat_idle_frame + 1) & 0x1;
                    count_timer = 0;
                }

                if ((jsf8() & 0x3F) == 0) {
                    cat_state = LICKING;
                    if (count_timer >= 10) {
                        count_timer = 10;
                    }
                } 
                
                sleep_timer++;
                if (sleep_timer >= CAT_SLEEP_COUNT_TIMEOUT) {
                    cat_state = SLEEPY;
                    sleep_timer = 0;
                }

                tail_frame = (tail_frame + 1) % 10;
                break;
            case LICKING:
                oled_write_char(0xA4 + tail_frame, false);
                oled_write_char(0xB5 + cat_idle_frame, false);

                count_timer++;
                if ((count_timer & 0x1) == 0) {
                    cat_idle_frame = (cat_idle_frame + 1) & 0x1;
                }
                
                // counter shared with left/right glances of SITTING state
                if (count_timer >= 20) {
                    cat_state = SITTING;
                    count_timer = 0;
                }

                tail_frame = (tail_frame + 1) % 10;
                break;
            case SLEEPY:
                oled_write_char(0xA4 + tail_frame, false);
                oled_write_char(0xAF + sleepy_frame, false);
                
                sleepy_frame = (sleepy_frame + 1) & 0x3; // % 4
                tail_frame = (tail_frame + 1) % 10;

                if (sleepy_frame == 0) {
                    cat_state = ASLEEP;
                }
                break;
            case ASLEEP:
                oled_write_char(0xB4, false);
                oled_write_char(0xB2 + cat_idle_frame, false);

                if (tail_frame != 7) {
                    tail_frame = (tail_frame + 1) % 10;
                }
                
                count_timer++;
                if (count_timer >= 5) {
                    cat_idle_frame = (cat_idle_frame + 1) & 0x1;
                    count_timer = 0;
                }

                break;
            case STANDING:
                if (cat_running_right) {
                    oled_write_char(0xCD, false);
                    oled_write_char(0xCE + cat_idle_frame, false);
                } else {
                    oled_write_char(0xD0 + cat_idle_frame, false);
                    oled_write_char(0xD2, false);
                }

                count_timer++;
                if (count_timer >= 20) {
                    cat_idle_frame = (cat_idle_frame + 1) & 0x1;
                    count_timer = 0;
                    cat_state = SITTING;
                }
                break;
            case JUMPING:
                if (cat_running_right) {
                    oled_write_char(0xD3, false);
                    oled_write_char(0xD4, false);
                } else {
                    oled_write_char(0xD5, false);
                    oled_write_char(0xD6, false);
                }

                cat_state = STANDING;
                sleep_timer = 0;
                break;
            case RUNNING:
                if (cat_running_right) {
                    oled_write_char(0x8D + cat_idle_frame * 3, false);
                    oled_write_char(0x8E + cat_idle_frame * 3, false);
                    oled_write_char(0x8F + cat_idle_frame * 3, false);
                    
                    cat_pos[0] = (cat_pos[0] + 2) % 18;
                    if (cat_pos[0] == 0) {
                        //cat_pos[1] = (cat_pos[1] + jsf8()) % 6;
                        // change direction :
                        cat_running_right = false;
                        cat_pos[0] = 18;
                    }
                } else {
                    oled_write_char(0x99 + cat_idle_frame * 3, false);
                    oled_write_char(0x9A + cat_idle_frame * 3, false);
                    oled_write_char(0x9B + cat_idle_frame * 3, false);

                    cat_pos[0] = (cat_pos[0] - 2) % 18;
                    if (cat_pos[0] == 0) {
                        //cat_pos[1] = (cat_pos[1] + jsf8()) % 6;
                        // change direction :
                        cat_running_right = true;
                    }
                }

                static uint8_t prn;
                prn = jsf8() & 0x7;
                if (prn == 0) {
                    cat_pos[1] = ((cat_pos[1] == 5) ? 5 : cat_pos[1]+1);
                } else if (prn == 1) {
                    cat_pos[1] = ((cat_pos[1] == 0) ? 0 : cat_pos[1]-1);
                }

                cat_idle_frame = (cat_idle_frame + 1) & 0x1;
                sleep_timer = 0;
                break;
        }

        // extra exclamation mark when waking the cat up before changing state
        if ((bit_mask > 0) && (cat_state == ASLEEP)) { // means timer has been reset
            oled_write_char(0xA3, false);
            cat_state = JUMPING;
        }

        if (cat_state != JUMPING) {
            if (bit_mask > 14){
                cat_state = RUNNING;
            } else if (bit_mask > 2) {
                cat_state = STANDING;
            }
        }

        anim_timer = sync_timer_read32();
    }
}

void render_loop(void) {
    oled_write_char(0x89 + loop_circle, false);
    loop_circle = (loop_circle + 1) & 3;
}

void render_progress_bar(uint16_t bit_mask) {
    static char loading_bar[PROGRESS_BAR_SIZE + 1];

    loading_bar[0] = empty_bar[BEGINING] + ((bit_mask & 0x01) ? 0x03 : 0x0);
    for (int i = 1; i < (PROGRESS_BAR_SIZE - 1); i++) {       
        loading_bar[i] = empty_bar[MIDDLE] + ((bit_mask & (0x01 << i)) ? 0x03 : 0x0);
    }
    loading_bar[PROGRESS_BAR_SIZE - 1] = empty_bar[END] + ((bit_mask & (0x01 << (PROGRESS_BAR_SIZE - 1))) ? 0x03 : 0x0);

    oled_write(loading_bar, false);
}

uint16_t get_wpm_bit_mask(void) {
    static uint16_t bit_mask;
    static uint8_t current_wpm;
    current_wpm = get_current_wpm();    

    current_wpm >>= 3; // position from 0 to 7 in a scale going +1 every 16wpm
    // mask for the loading bar e.g. 0x00000011
    //                                 |----| length is equal to bitwise not current_wpm
    //bit_mask = 0xFF >> (~current_wpm); // not is more efficient than (8 - current_wpm)
    bit_mask = 0xFFFF >> (PROGRESS_BAR_SIZE - current_wpm); // not is more efficient than (8 - current_wpm)

    return bit_mask;
}

#ifdef DYNAMIC_MACRO_ENABLE
#define PRINT_DM_NB_FRAMES 10
static bool recording = false;
static bool full = false;
static bool saved = false;
static bool saved1 = false;
uint32_t times_saved = PRINT_DM_NB_FRAMES + 1; // initialised greater than max to not display anim
static bool playing = false;
static bool playing1 = false;
uint32_t times_played = PRINT_DM_NB_FRAMES + 1;

void dynamic_macro_record_start_user(void) {
    recording = true;
    full = false;
}

void dynamic_macro_play_user(int8_t direction) {
    times_played = 0;
    playing = true;
    if (direction > 0) { // 4bytes lighter than playing1 = (direction > 0)
        playing1 = true;
    }
}

void dynamic_macro_record_end_user(int8_t direction) {
    recording = false;
    times_saved = 0;
    saved = true;
    if (direction > 0) {
        saved1 = true;
    }
}

void dynamic_macro_record_key_user(int8_t direction, keyrecord_t *record) {
    full = true;
}

static void render_rec(void) { 
    // macro related infos
    if (recording) {
        oled_write_P(PSTR("REC "), false);
        if (full) {
            oled_write_P(PSTR("FULL!"), false);
        } else { //if (sync_timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
            render_loop();
            //anim_timer = sync_timer_read32();
        }
    }
            
    if (times_saved < PRINT_DM_NB_FRAMES) {
        times_saved++;
        oled_write_P(PSTR("SAVED"), false);
        oled_write_P(saved1 ? PSTR(" 1") : PSTR(" 2"), false);
    } else if (times_saved == PRINT_DM_NB_FRAMES) {
        saved1 = false;
        saved = false;
    }

    if (times_played < PRINT_DM_NB_FRAMES) {
        times_played++;
        oled_write_P(PSTR("PLAYED"), false);
        oled_write_P(playing1 ? PSTR(" 1") : PSTR(" 2"), false);
    } else if (times_played == PRINT_DM_NB_FRAMES) {
        playing1 = false;
        playing = false;
    }
}
#endif // DYNAMIC_MACRO_ENABLE

#ifdef RGBLIGHT_ENABLE
enum RGBLIGHT_EFFECT_MODE rgb_mode;
uint8_t rgb_val;
uint8_t rgb_hue;
char str_rgb[3+1];

static void render_led_status(void) { 
    // RGB animation mode 
    rgb_mode = rgblight_get_mode();
    itoa(rgb_mode, str_rgb, 10);
    oled_write_P(PSTR("M: "), false);
    oled_write(str_rgb, false);

    // Color aka 'rgb_hue'
    //rgb_hue = rgblight_get_hue();
    //itoa(rgb_hue, str_rgb, 10);
    itoa(base_hue, str_rgb, 10);
    oled_write_P(PSTR(" H: "), false);
    oled_write(str_rgb, false);

    // brightness aka 'rgb_val'
    //rgb_val = rgblight_get_val();
    //itoa(rgb_val, str_rgb, 10);
    itoa(base_val, str_rgb, 10);
    oled_write_P(PSTR(" V: "), false);
    oled_write(str_rgb, false);
}
#endif // RGBLIGHT_ENABLE

static uint8_t previous_layer = 0;
static uint8_t previous_encoder_mode = 0;

static uint8_t appearing_letter_id = 0;
static uint8_t appearing_letter_id_enc = 0;
static const uint8_t str_pos_x[4] = {0, 5, 10, 15};

static const char str_layers[4][4] = { 
    {0x42, 0x41, 0x53, 0x45},
    {0x4D, 0x4F, 0x56, 0x45},
    {0x4E, 0x55, 0x4D, 0x53},
    {0x50, 0x41, 0x52, 0x41},
};

static const char str_enc[4][5] = { 
    {0x50, 0x41, 0x47, 0x45},
    {0x4D, 0x4F, 0x55, 0x53},// 0x45},
    {0x4D, 0x55, 0x53, 0x49},// 0x43},
    {0x4C, 0x45, 0x44, 0x53},
};

static void slide_selected_enc(uint8_t encoder_mode) {
    oled_set_cursor(str_pos_x[previous_encoder_mode], 0);
    for (int i = 0; i < 4; i++) {
        if (previous_encoder_mode < encoder_mode) {
            oled_write_char(str_enc[previous_encoder_mode][i], (i > appearing_letter_id_enc));
        } else {
            oled_write_char(str_enc[previous_encoder_mode][i], (i + appearing_letter_id_enc < 3));
        }
    }
    oled_set_cursor(str_pos_x[encoder_mode], 0);
    for (int i = 0; i < 4; i++) {
        if (previous_encoder_mode < encoder_mode) {
            oled_write_char(str_enc[encoder_mode][i], (i <= appearing_letter_id_enc));
        } else {
            oled_write_char(str_enc[encoder_mode][i], (i + appearing_letter_id_enc >= 3));
        }
    }

    appearing_letter_id_enc++;

    if (appearing_letter_id_enc == 4) {
        previous_encoder_mode = encoder_mode;
        appearing_letter_id_enc = 0;
    }
}

static void slide_selected_layers(uint8_t highest_layer) {
    oled_set_cursor(str_pos_x[previous_layer], 7);
    for (int i = 0; i < 4; i++) {
        if (previous_layer < highest_layer) {
            oled_write_char(str_layers[previous_layer][i], (i > appearing_letter_id));
        } else {
            oled_write_char(str_layers[previous_layer][i], (i + appearing_letter_id < 3));
        }
    }
    oled_set_cursor(str_pos_x[highest_layer], 7);
    for (int i = 0; i < 4; i++) {
        if (previous_layer < highest_layer) {
            oled_write_char(str_layers[highest_layer][i], (i <= appearing_letter_id));
        } else {
            oled_write_char(str_layers[highest_layer][i], (i + appearing_letter_id >= 3));
        }
    }

    appearing_letter_id++;
    //anim_timer = sync_timer_read32();

    if (appearing_letter_id == 4) {
        previous_layer = highest_layer;
        appearing_letter_id = 0;
    }
}

static void render_layer(void) { 
    // layer related infos
    static uint8_t highest_layer;
    highest_layer = get_highest_layer(layer_state);
    if (highest_layer != previous_layer) {
            slide_selected_layers(highest_layer);
    } else {
        oled_write_P(PSTR("BASE"), highest_layer == _BASE);
        oled_write_char(0x00, false);
        oled_write_P(PSTR("MOVE"), highest_layer == _MOVE);
        oled_write_char(0x00, false);
        oled_write_P(PSTR("NUMS"), highest_layer == _NUM);
        oled_write_char(0x00, false);
        oled_write_P(PSTR("PARA"), highest_layer == _SETTINGS);
        previous_layer = highest_layer;
    }
}

void render_enc_state(void) {
    if (encoder_mode != previous_encoder_mode) {
        slide_selected_enc(encoder_mode);
    } else {
        oled_write_P(PSTR("PAGE"), encoder_mode == _PAGE);
        oled_write_char(0x00, false);
        oled_write_P(PSTR("MOUS"), encoder_mode == _MOUSE);
        oled_write_char(0x00, false);
        oled_write_P(PSTR("MUSI"), encoder_mode == _MUSIC);
        oled_write_char(0x00, false);
        oled_write_P(PSTR("LEDS"), encoder_mode == _RGB);
        previous_encoder_mode = encoder_mode;
    }
}

void render_encoder_info(void) {
    switch(encoder_mode) {
        case _PAGE:
            oled_write_P(PSTR("L: Vol +/- (Mute)"), false);
            oled_advance_page(true);
            oled_write_P(PSTR("R: PgUp/PgDn"), false);
            oled_advance_page(true);
            break;
        case _MOUSE:
            oled_write_P(PSTR("L: Left/Right"), false); // (Mute)
            oled_advance_page(true);
            oled_write_P(PSTR("R: Up/Down"), false);
            oled_advance_page(true);
            break;
        case _MUSIC:
            oled_write_P(PSTR("L: Vol +/- (Play)"), false);
            oled_advance_page(true);
            oled_write_P(PSTR("R: Prev/Next"), false);
            oled_advance_page(true);
            break;
        case _RGB:
            oled_write_P(PSTR("L: Hue +/- (LED tog)"), false);
            oled_advance_page(true);
            oled_write_P(PSTR("R: Brightness +/-"), false);
            oled_advance_page(true);
            break;
    }
}

//void render_border(void) {
//    for (int i = 0; i < 8 ; i++) {
//        oled_set_cursor(20, i);
//        oled_write_char(0x7C, false);
//    }
//}

void render_content(uint16_t bit_mask) {
    if (is_keyboard_master()) {
        oled_set_cursor(0, 0);
        render_enc_state();

        oled_set_cursor(0, 2);
        render_encoder_info();

        oled_set_cursor(0, 5);
        oled_advance_page(true);

        if (get_highest_layer(layer_state) == _SETTINGS) {
            #ifdef RGBLIGHT_ENABLE
            oled_set_cursor(0, 5);
            render_led_status();
            #endif // RGBLIGHT_ENABLE
        } else if (recording || playing || saved) {
            oled_set_cursor(7, 5);
            render_rec();
        } else {
            oled_set_cursor(2, 5);
            render_progress_bar(bit_mask);
        }
        oled_set_cursor(0, 7);
        render_layer();
        //render_border();
    } else {
        render_cat(bit_mask);
        oled_set_cursor(0, 6);
        render_uptime();
    }
}

#ifdef RGBLIGHT_ENABLE
static bool led_max = false;
static bool led_zero = true;

void fade_led(bool turn_on) {
    if (sync_timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
        if (turn_on) {
            if (rgblight_get_val() != RGBLIGHT_LIMIT_VAL) {
                rgblight_increase_val_noeeprom();
                led_zero = false;
            } else {
                led_max = true;
                base_val = RGBLIGHT_LIMIT_VAL;

            }
        } else {
            if (rgblight_get_val() != 0) {
                rgblight_decrease_val_noeeprom();
                led_max = false;
            } else {
                led_zero = true;
                base_val = 0;
            }
        }
        anim_timer = sync_timer_read32();
    }
}
#endif // RGBLIGHT_ENABLE

bool wpm_keycode_user(uint16_t keycode) {
    // every input increases WPM
    return true;
}

void render_sides(void) {
    // each side are rendered separately
    static uint16_t bit_mask;
    bit_mask = get_wpm_bit_mask(); 

    // TODO : remove this shit 
    uint32_t useless_var = 0;
    useless_var = sync_timer_elapsed32(anim_sleep);
    useless_var = useless_var;

    if (bit_mask != 0) {
        if (!is_oled_on()) {
            oled_on();
            led_max = false;
        }
        if (!led_max) {
            fade_led(true);
        }
        anim_sleep = sync_timer_read32();
    } 
    
    if (sync_timer_elapsed32(anim_sleep) > OLED_TIMEOUT) {
        #ifdef RGBLIGHT_ENABLE
        if (!led_zero) {
            fade_led(false);
        }
        #endif // RGBLIGHT_ENABLE

        if (is_oled_on()) {
            oled_clear(); // prevents the slave from being turned on with garbage on and no refresh
            oled_off();
            led_zero = false;
        }
    } else {
        render_content(bit_mask);
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    uptime_timer = sync_timer_read32();
    anim_sleep = sync_timer_read32(); // for render_splash
    return OLED_ROTATION_180; 
}

/*
const char PROGMEM kyria_logo[3][38] = {
    {0x04, 0x04, 0xFE, 0xFF, 0x60, 0x30, 0x78, 0xEE, 0xC7, 0x00, 0x80, 0xC0, 0xE0, 0x00, 0x00, 0xC0, 0xE0, 0x00,
     0x80, 0xC0, 0xE0, 0x80, 0x40, 0xE0, 0xC0, 0x00, 0x40, 0xE6, 0xF3, 0x00, 0x90, 0xC8, 0x2C, 0x2C, 0xFC, 0xF8,
     0x00, 0x00},
    {0x00, 0x04, 0x07, 0x07, 0x02, 0x00, 0x00, 0x07, 0x07, 0x02, 0x60, 0xCF, 0x9F, 0x88, 0x44, 0x3F, 0x1F, 0x00,
     0x00, 0x1F, 0x1F, 0x08, 0x00, 0x80, 0x80, 0x80, 0x00, 0x0F, 0x0F, 0x04, 0x01, 0x03, 0x82, 0x02, 0x03, 0x03,
     0x06, 0x04},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x7C, 0x08, 0x04, 0x0C, 0x00, 0x38, 0x54, 0x4C, 0x20, 0x08, 0x3C, 0x40,
     0x38, 0x04, 0x40, 0x00, 0x03, 0x65, 0x51, 0x4D, 0x63, 0x60, 0x00, 0x40, 0x02, 0x43, 0x7F, 0x60, 0x00, 0x00,
     0x00, 0x00}
};                
*/

bool oled_task_user(void) {
    #ifdef SPLASH
    if (startup) {
        if (sync_timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
            oled_set_cursor(8, 3);
            oled_write_P(PSTR("Kyria"), false);
            oled_set_cursor(10, 5);
            render_loop();
        
            if (loop_circle == 0) {
                startup--;
            }
            if (!startup) {
                oled_clear();
            }
            anim_timer = sync_timer_read32();
        }
    } else {
    #endif // SPLASH
        render_sides();
    #ifdef SPLASH
    }
    #endif // SPLASH

    return false;
}

#endif // OLED_ENABLE
