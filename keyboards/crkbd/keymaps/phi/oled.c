#include <string.h>
#include "ssd1306.h"
#include "split_util.h"

#define L_BASE     0
#define L_SYMB     (2 << (1 - 1))
#define L_FUNCTION (2 << (2 - 1))
#define L_MOUSE    (2 << (3 - 1))
#define L_WHEEL    (2 << (4 - 1))

#define MOD_CTL (MOD_BIT(KC_LCTRL) | MOD_BIT(KC_RCTRL))
#define MOD_SFT (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT))
#define MOD_ALT (MOD_BIT(KC_LALT) | MOD_BIT(KC_RALT))
#define MOD_GUI (MOD_BIT(KC_LGUI) | MOD_BIT(KC_RGUI))

#define KEYFREQ_LOG_UPDATE_INTERVAL 12000 /* 12sec x 20 = 240sec (4min) */
#define SCREEN_FRAME_INTERVAL 55 /* 18fps */
#define ANIMATION_ENABLE

extern uint8_t is_master;

void oled_init(void) {
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
int last_keyfreq_update = 0;
int animation_frame = 0;

char hoshi[2][21] = {
    { 0x20, 0x20, 0x20, 0x93, 0x20, 0x20, 0x20, 0x20, 0x93, 0x20, 0x20, 0x63, 0x72, 0x6b, 0x62, 0x64, 0x20, 0x70, 0x68, 0x69 },
    { 0x20, 0x93, 0x20, 0x20, 0x20, 0x20, 0x93, 0x20, 0x20, 0x20, 0x93, 0x20, 0x20, 0x20, 0x20, 0x20, 0x93, 0x20, 0x20, 0x20 }
};

char taiyo_and_grid[4][21] = {
  { 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0x20 },
  { 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xb9, 0xba, 0xba, 0xba, 0xbb, 0x20 },
  { 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0xbc, 0xbd, 0xbd, 0xbd, 0xbe, 0x9f }
};

char palm[3][22] = {
  { 0xd0, 0xd1, 0xd0, 0xd1, 0xd0, 0xd1, 0xd0, 0xd1, 0xd0, 0xd1, 0xd0, 0xd1, 0xd0, 0xd1, 0xd0, 0xd1, 0xd0, 0xd1, 0xd0, 0xd1, 0xd0, 0xd1 },
  { 0xd2, 0xd3, 0xd2, 0xd3, 0xd2, 0xd3, 0xd2, 0xd3, 0xd2, 0xd3, 0xd2, 0xd3, 0xd2, 0xd3, 0xd2, 0xd3, 0xd2, 0xd3, 0xd2, 0xd3, 0xd2, 0xd3 },
  { 0x91, 0x92, 0x91, 0x92, 0x91, 0x92, 0x91, 0x92, 0x91, 0x92, 0x91, 0x92, 0x91, 0x92, 0x91, 0x92, 0x91, 0x92, 0x91, 0x92, 0x91, 0x92 }
};

char saku[21] = {
  0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2
};

char saku_nami[2][21] = {
  { 0xb1, 0xb1, 0xb1, 0xb1, 0xb1, 0xb1, 0xb1, 0xb1, 0xb1, 0xb1, 0xb1, 0xb1, 0xb1, 0xb1, 0xb1, 0xb1, 0xb1, 0xb1, 0xb1, 0xb1 },
  { 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0, 0xb0 }
};

char keyfreq_log[2][21] = {
  { 0xdc, 0xdc, 0xdc, 0xdc, 0xdc, 0xdc, 0xdc, 0xdc, 0xdc, 0xdc, 0xdc, 0xdc, 0xdc, 0xdc, 0xdc, 0xdc, 0xdc, 0xdc, 0xdc, 0xdc, 0xdc },
  { 0x9e, 0x9e, 0x9e, 0x9e, 0x9e, 0x9e, 0x9e, 0x9e, 0x9e, 0x9e, 0x9e, 0x9e, 0x9e, 0x9e, 0x9e, 0x9e, 0x9e, 0x9e, 0x9e, 0x9e, 0x9e }
};

void update_keyfreq_log(void) {
    if (keyfreq_count)
      switch (keyfreq_count / ((KEYFREQ_LOG_UPDATE_INTERVAL / 1000) * 10 / 15)) {
       case 0: keyfreq_log[1][20] = 0x9b; break;
       case 1: keyfreq_log[1][20] = 0x9a; break;
       case 2: keyfreq_log[1][20] = 0x99; break;
       case 3: keyfreq_log[1][20] = 0x98; break;
       case 4: keyfreq_log[1][20] = 0x97; break;
       case 5: keyfreq_log[1][20] = 0x96; break;
       case 6: keyfreq_log[1][20] = 0x95; break;
       case 7: keyfreq_log[1][20] = 0x94; break;
       case 8: keyfreq_log[0][20] = 0xdb, keyfreq_log[1][20] = 0x94; break;
       case 9: keyfreq_log[0][20] = 0xda, keyfreq_log[1][20] = 0x94; break;
       case 10: keyfreq_log[0][20] = 0xd9, keyfreq_log[1][20] = 0x94; break;
       case 11: keyfreq_log[0][20] = 0xd8, keyfreq_log[1][20] = 0x94; break;
       case 12: keyfreq_log[0][20] = 0xd7, keyfreq_log[1][20] = 0x94; break;
       case 13: keyfreq_log[0][20] = 0xd6, keyfreq_log[1][20] = 0x94; break;
       case 14: keyfreq_log[0][20] = 0xd5, keyfreq_log[1][20] = 0x94; break;
       default: keyfreq_log[0][20] = 0xd4, keyfreq_log[1][20] = 0x94; break; /* > 10 keys per sec */
      }

    if (timer_elapsed(last_keyfreq_update) < KEYFREQ_LOG_UPDATE_INTERVAL) return;
    last_keyfreq_update = timer_read();

    /* shift the log every 60 seconds */
    keyfreq_count = 0;
    for (int i = 0; i < 20; i++) {
      keyfreq_log[0][i] = keyfreq_log[0][i + 1];
      keyfreq_log[1][i] = keyfreq_log[1][i + 1];
    }
    keyfreq_log[0][20] = 0xdc;
    keyfreq_log[1][20] = 0x9e;
}

void prepare_next_frame(void) {
    static int last_update = 0;
    static struct CharacterMatrix matrix;

    if (timer_elapsed(last_update) < SCREEN_FRAME_INTERVAL) return;
    last_update = timer_read();

   #ifdef ANIMATION_ENABLE
    animation_frame = (animation_frame + 1) % 24;
   #endif

    matrix_reset_cursor(&matrix);
    if (is_master) {
        uint8_t mods = get_mods();
        if (mods & MOD_CTL) matrix_write(&matrix, "C-");
        if (mods & MOD_ALT) matrix_write(&matrix, "M-");
        if (mods & MOD_SFT) matrix_write(&matrix, "S-");
        if (mods & MOD_GUI) matrix_write(&matrix, "A-");
        matrix_write_ln(&matrix, get_layer_name());
        matrix_write_range_ln(&matrix, keyfreq_log[0], timer_elapsed(last_keyfreq_update) / (KEYFREQ_LOG_UPDATE_INTERVAL / 6), 120);
        matrix_write_range_ln(&matrix, keyfreq_log[1], timer_elapsed(last_keyfreq_update) / (KEYFREQ_LOG_UPDATE_INTERVAL / 6), 120);
        matrix_write_range(&matrix, saku, animation_frame % 6, 120);
        /* render BG */
        matrix_reset_cursor(&matrix);
        set_overwrite_mode(true);
        matrix_write_ln(&matrix, taiyo_and_grid[0]);
        matrix_write_ln(&matrix, taiyo_and_grid[1]);
        matrix_write_ln(&matrix, taiyo_and_grid[2]);
        matrix_write(&matrix, saku_nami[0]);
        matrix_reset_cursor(&matrix);
        matrix_write_range(&matrix, saku_nami[1], animation_frame / 4, 120);
        set_overwrite_mode(false);
    } else {
        matrix_write_ln(&matrix, hoshi[0]);
        matrix_write_ln(&matrix, hoshi[1]);
        matrix_write_ln(&matrix, "");
        matrix_write_range(&matrix, saku, 6 - animation_frame % 6, 120);
        /* render BG */
        matrix_reset_cursor(&matrix);
        set_overwrite_mode(true);
        matrix_write_ln(&matrix, "");
        matrix_write_range_ln(&matrix, palm[0], 12 - animation_frame / 2, 120);
        matrix_write_range_ln(&matrix, palm[1], 12 - animation_frame / 2, 120);
        matrix_write_range(&matrix, palm[2], 12 - animation_frame / 2, 120);
        matrix_reset_cursor(&matrix);
        matrix_write(&matrix, saku_nami[0]);
        matrix_reset_cursor(&matrix);
        matrix_write_range(&matrix, saku_nami[1], animation_frame / 4, 120);
        set_overwrite_mode(false);
    }

    matrix_push(&matrix); /* push to the ssd1306 driver */
}

void iota_gfx_task_user(void) {
  if (is_master) update_keyfreq_log();
  prepare_next_frame();
}

void oled_record_event(uint16_t keycode, keyrecord_t *record) {
    if (is_master && record->event.pressed) {
        keyfreq_count++;
    }
}
