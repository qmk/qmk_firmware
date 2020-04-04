#ifndef HAS_USB
    #define HAS_USB() true
#endif

#include "ssd1306.h"

extern uint8_t is_master;

bool PLUG_OLED_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
    //  set_keylog(keycode, record);
    // set_timelog();
    }
    return true;
}

void PLUG_OLED_matrix_init_user(void) {
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    iota_gfx_init(!HAS_USB());   // turns on the display
}

char _layer_state[24] = "\0";
//__attribute__((weak))
void indicate_layer(const char* pstr) {
    strncpy(_layer_state,pstr,sizeof(_layer_state));
}

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void PLUG_OLED_matrix_scan_user(void) {
    iota_gfx_task();
}

void matrix_write_cond(struct CharacterMatrix *matrix,const char* pstr,uint8_t cond) {
    if(cond) matrix_write(matrix,pstr);
}
void matrix_write_ln_cond(struct CharacterMatrix *matrix,const char* pstr,uint8_t cond) {
    if(cond) matrix_write_ln(matrix,pstr);
}

void render_keylock_status(struct CharacterMatrix *matrix,uint8_t led_usb_state) {
    matrix_write_cond(matrix,"NUM|", led_usb_state & (1 << USB_LED_NUM_LOCK));
    matrix_write_cond(matrix,"CAP|", led_usb_state & (1 << USB_LED_CAPS_LOCK));
    matrix_write_cond(matrix,"SCL|", led_usb_state & (1 << USB_LED_SCROLL_LOCK));
}

void render_mod_status(struct CharacterMatrix *matrix,uint8_t modifiers) {
    matrix_write_cond(matrix,"Sft>", (modifiers & MOD_MASK_SHIFT));
    matrix_write_cond(matrix,"Ctl>", (modifiers & MOD_MASK_CTRL));
    matrix_write_cond(matrix,"Alt>", (modifiers & MOD_MASK_ALT));
    matrix_write_cond(matrix,"Cmd>", (modifiers & MOD_MASK_GUI));
}

#define STRPPP(X) #X
#define STRPP(X) STRPPP(X)

void matrix_render_user(struct CharacterMatrix *matrix) {
    if (is_master) {
        matrix_write(matrix,"| ");
        matrix_write(matrix,STRPP(PRODUCT));
        matrix_write(matrix,"/");
        matrix_write_ln(matrix,STRPP(MANUFACTURER));

        matrix_write(matrix,"| ");
        matrix_write(matrix, get_kb_layout());
        matrix_write(matrix, " / ");
        const char* p;
        switch(_harmonize.os_type) {
            case OS_WIN:p="Windows";break;
            case OS_MAC:p="Mac";break;
            default:p="Linux";break;
        }
        matrix_write_ln(matrix, p);
        
        matrix_write(matrix,"| ");
        matrix_write_ln(matrix, _layer_state);

        matrix_write(matrix,"| ");
        render_keylock_status(matrix,host_keyboard_leds());
        render_mod_status(matrix,get_mods() | get_oneshot_mods());
    } else {
        matrix_write(matrix, read_logo());
    }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
    if (memcmp(dest->display, source->display, sizeof(dest->display))) {
        memcpy(dest->display, source->display, sizeof(dest->display));
        dest->dirty = true;
    }
}

void iota_gfx_task_user(void) {
    struct CharacterMatrix matrix;
    matrix_clear(&matrix);
    matrix_render_user(&matrix);
    matrix_update(&display, &matrix);
}
