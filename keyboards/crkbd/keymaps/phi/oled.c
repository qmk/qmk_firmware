#include <string.h>
#include "crkbd.h"
#include "ssd1306.h"
#include "split_util.h"
#include "LUFA/Drivers/Peripheral/TWI.h"

#define L_BASE     0
#define L_SYMB     (2 << (1 - 1))
#define L_FUNCTION (2 << (2 - 1))
#define L_MOUSE    (2 << (3 - 1))
#define L_WHEEL    (2 << (4 - 1))

#define MOD_CTL (MOD_BIT(KC_LCTRL) | MOD_BIT(KC_RCTRL))
#define MOD_SFT (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT))
#define MOD_ALT (MOD_BIT(KC_LALT) | MOD_BIT(KC_RALT))
#define MOD_GUI (MOD_BIT(KC_LGUI) | MOD_BIT(KC_RGUI))

#define KEYFREQ_LOG_UPDATE_INTERVAL 60000 /* 60sec */
#define SCREEN_UPDATE_INTERVAL 50 /* 20fps */
/* #define ANIMATION_FRAME_RATE 200 */

extern uint8_t is_master;

void oled_init(void) {
    // SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    TWI_Init(TWI_BIT_PRESCALE_1, TWI_BITLENGTH_FROM_FREQ(1, 800000));
    iota_gfx_init(!has_usb());   // turns on the display
}

void oled_update(void) {
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
int shift = 0;

char right_image[2][21] = {
    { 0x20, 0x20, 0x20, 0x93, 0x20, 0x20, 0x20, 0x20, 0x93, 0x3e, 0x20, 0x63, 0x72, 0x6b, 0x62, 0x64, 0x20, 0x70, 0x68, 0x69 },
    { 0x20, 0x93, 0x20, 0x20, 0x20, 0x20, 0x93, 0x20, 0x20, 0x20, 0x93, 0x20, 0x20, 0x20, 0x20, 0x20, 0x93, 0x00, 0x20, 0x20 }
};

char left_background_image[4][21] = {
  { 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0x20 },
  { 0x9d, 0x20, 0x20, 0x20, 0x20, 0x9d, 0x20, 0x20, 0x20, 0x20, 0x9d, 0x20, 0x20, 0x20, 0xb9, 0xba, 0xba, 0xba, 0xbb, 0x20 },
  { 0x9e, 0x9e, 0x9e, 0x9e, 0x9e, 0x9e, 0x9e, 0x9e, 0x9e, 0x9e, 0x9e, 0x9e, 0x9e, 0x9e, 0xbc, 0xbd, 0xbd, 0xbd, 0xbe, 0x9e },
  { 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20 }
};

char palm[2][2][21] = {
  {
    { 0xd0, 0xd1, 0xd0, 0xd1, 0xd0, 0xd1, 0xd0, 0xd1, 0xd0, 0xd1, 0xd0, 0xd1, 0xd0, 0xd1, 0xd0, 0xd1, 0xd0, 0xd1, 0xd0, 0xd1 },
    { 0xd1, 0xd0, 0xd1, 0xd0, 0xd1, 0xd0, 0xd1, 0xd0, 0xd1, 0xd0, 0xd1, 0xd0, 0xd1, 0xd0, 0xd1, 0xd0, 0xd1, 0xd0, 0xd1, 0xd0 },
  } , {
    { 0xd2, 0xd3, 0xd2, 0xd3, 0xd2, 0xd3, 0xd2, 0xd3, 0xd2, 0xd3, 0xd2, 0xd3, 0xd2, 0xd3, 0xd2, 0xd3, 0xd2, 0xd3, 0xd2, 0xd3 },
    { 0xb1, 0xb0, 0xb1, 0xb0, 0xb1, 0xb0, 0xb1, 0xb0, 0xb1, 0xb0, 0xb1, 0xb0, 0xb1, 0xb0, 0xb1, 0xb0, 0xb1, 0xb0, 0xb1, 0xb0 }
  }
};

char saku[2][21] = {
  { 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2 },
  { 0xb3, 0xb3, 0xb3, 0xb3, 0xb3, 0xb3, 0xb3, 0xb3, 0xb3, 0xb3, 0xb3, 0xb3, 0xb3, 0xb3, 0xb3, 0xb3, 0xb3, 0xb3, 0xb3, 0xb3 }
};

void shift_frame (void) {
  #ifdef ANIMATION_FRAME_RATE
  static int last_time = 0;
  if (timer_elapsed(last_time) > ANIMATION_FRAME_RATE) {
    last_time = timer_read();
    shift = shift ? 0 : 1;
  }
  #endif
}

void matrix_write_keyfreq_log_ln(struct CharacterMatrix *matrix) {
    static char log1[21] = {
      0xdc, 0xdc, 0xdc, 0xdc, 0xdc, 0xdc, 0xdc, 0xdc, 0xdc, 0xdc, 0xdc, 0xdc, 0xdc, 0xdc, 0xdc, 0xdc, 0xdc, 0xdc, 0xdc, 0xdc
    };
    static char log2[21] = {
      0x9c, 0x9c, 0x9c, 0x9c, 0x9c, 0x9c, 0x9c, 0x9c, 0x9c, 0x9c, 0x9c, 0x9c, 0x9c, 0x9c, 0x9c, 0x9c, 0x9c, 0x9c, 0x9c, 0x9c
    };
    static int last_time = 0;

    if (keyfreq_count)
      switch (keyfreq_count / 40) {
       case 0: log2[19] = 0x9b; break;
       case 1: log2[19] = 0x9a; break;
       case 2: log2[19] = 0x99; break;
       case 3: log2[19] = 0x98; break;
       case 4: log2[19] = 0x97; break;
       case 5: log2[19] = 0x96; break;
       case 6: log2[19] = 0x95; break;
       case 7: log2[19] = 0x94; break;
       case 8: log1[19] = 0xdb, log2[19] = 0x94; break;
       case 9: log1[19] = 0xda, log2[19] = 0x94; break;
       case 10: log1[19] = 0xd9, log2[19] = 0x94; break;
       case 11: log1[19] = 0xd8, log2[19] = 0x94; break;
       case 12: log1[19] = 0xd7, log2[19] = 0x94; break;
       case 13: log1[19] = 0xd6, log2[19] = 0x94; break;
       case 14: log1[19] = 0xd5, log2[19] = 0x94; break;
       default: log1[19] = 0xd4, log2[19] = 0x94; break;
      }

    /* shift the log every 60 seconds */
    if (timer_elapsed(last_time) > KEYFREQ_LOG_UPDATE_INTERVAL) {
        last_time = timer_read();
        keyfreq_count = 0;
        for (int i = 0; i < 19; i++) {
          log1[i] = log1[i + 1];
          log2[i] = log2[i + 1];
        }
        log1[19] = 0x9c;
        log2[19] = 0xdc;
    }

    matrix_write_ln(matrix, log1);
    matrix_write_ln(matrix, log2);
}

void prepare_next_frame(void) {
    static int last_update = 0;
    static struct CharacterMatrix matrix;

    if (timer_elapsed(last_update) < SCREEN_UPDATE_INTERVAL) return;
    last_update = timer_read();

    matrix_clear(&matrix);

    shift_frame();
    if (is_master) {
        uint8_t mods = get_mods();
        if (mods & MOD_CTL) matrix_write(&matrix, "C-");
        if (mods & MOD_ALT) matrix_write(&matrix, "M-");
        if (mods & MOD_SFT) matrix_write(&matrix, "S-");
        if (mods & MOD_GUI) matrix_write(&matrix, "A-");
        matrix_write_ln(&matrix, get_layer_name());
        matrix_write_keyfreq_log_ln(&matrix);
        matrix_write(&matrix, saku[shift]);
        /* render BG */
        matrix_reset_cursor(&matrix);
        matrix_overwrite_ln(&matrix, left_background_image[0]);
        matrix_overwrite_ln(&matrix, left_background_image[1]);
        matrix_overwrite_ln(&matrix, left_background_image[2]);
        matrix_overwrite(&matrix, left_background_image[3]);
    } else {
        matrix_write_ln(&matrix, right_image[0]);
        matrix_write_ln(&matrix, right_image[1]);
        matrix_write_ln(&matrix, palm[0][shift]);
        matrix_write(&matrix, palm[1][shift]);
    }

    matrix_push(&matrix); /* push to the ssd1306 driver */
}

void iota_gfx_task_user(void) {
  prepare_next_frame();
}

void oled_record_event(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        keyfreq_count++;
    }
}
