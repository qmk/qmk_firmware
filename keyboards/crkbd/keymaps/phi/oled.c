#ifdef SSD1306OLED

#include "crkbd.h"
#include "ssd1306.h"

#define L_BASE     0
#define L_SYMB     (2 << (1 - 1))
#define L_FUNCTION (2 << (2 - 1))
#define L_MOUSE    (2 << (3 - 1))
#define L_WHEEL    (2 << (4 - 1))

#define MOD_CTL (MOD_BIT(KC_LCTRL) | MOD_BIT(KC_RCTRL))
#define MOD_SFT (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT))
#define MOD_ALT (MOD_BIT(KC_LALT) | MOD_BIT(KC_RALT))
#define MOD_GUI (MOD_BIT(KC_LGUI) | MOD_BIT(KC_RGUI))

#include "../lib/logo_reader.c"

extern uint8_t is_master;

void matrix_init_user(void) {
    // SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    TWI_Init(TWI_BIT_PRESCALE_1, TWI_BITLENGTH_FROM_FREQ(1, 800000));
    iota_gfx_init(!has_usb());   // turns on the display
}

void matrix_scan_user(void) {
    iota_gfx_task();
}

char *get_layer_name(void) {
    switch (layer_state)
    {
      case L_BASE:
        return "Base";
      case L_SYMB:
        return "Symbol";
      case L_FUNCTION:
        return "Function";
      case L_MOUSE:
        return "Mouse";
      case L_WHEEL | L_MOUSE:
        return "Wheel";
      default:
        return "(Undefined)";
    }
}

int keyfreq_count = 0;

char keyfreq_log_grid[21] = {   /* 21th byte for a null character */
  0x20, 0x20, 0x20, 0x20, 0x9c,
  0x20, 0x20, 0x20, 0x20, 0x9c,
  0x20, 0x20, 0x20, 0x20, 0x9c,
  0x20, 0x20, 0x20, 0x20, 0x9c
};

char *get_keyfreq_log(void) {
   static char log[21] = {
     0x9b, 0x9b, 0x9b, 0x9b, 0x9b,
     0x9b, 0x9b, 0x9b, 0x9b, 0x9b,
     0x9b, 0x9b, 0x9b, 0x9b, 0x9b,
     0x9b, 0x9b, 0x9b, 0x9b, 0x9b
   };
   static int last_time = 0;

   log[0] =
     keyfreq_count == 0 ? 0x9b :
     keyfreq_count < 100 ? 0x9a :
     keyfreq_count < 200 ? 0x99 :
     keyfreq_count < 300 ? 0x98 :
     keyfreq_count < 400 ? 0x97 :
     keyfreq_count < 500 ? 0x96 :
     keyfreq_count < 600 ? 0x95 : 0x94;

   /* shift the log every 60 seconds */
   if (timer_elapsed(last_time) > 60000) {
       last_time = timer_read();
       keyfreq_count = 0;
       for (int i = 19; i > 0; i--) log[i] = log[i - 1];
       log[0] = 0x9b;
   }

   return log;
}

void matrix_render_user(struct CharacterMatrix *matrix) {
    if (is_master) {
        uint8_t mods = get_mods();
        matrix_write_ln(matrix, "crkbd phi >");
        if (mods & MOD_CTL) matrix_write(matrix, "C-");
        if (mods & MOD_ALT) matrix_write(matrix, "M-");
        if (mods & MOD_SFT) matrix_write(matrix, "S-");
        if (mods & MOD_GUI) matrix_write(matrix, "A-");
        matrix_write_ln(matrix, get_layer_name());
        matrix_write_ln(matrix, get_keyfreq_log());
        matrix_write(matrix, keyfreq_log_grid);
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        keyfreq_count++;
    }
    return true;
}

#endif
