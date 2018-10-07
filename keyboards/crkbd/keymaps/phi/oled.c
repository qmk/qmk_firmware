#include <string.h>
#include "ssd1306.h"
#include "split_util.h"

#define L_BASE     0
#define L_RAISE    (2 << (1 - 1))
#define L_FUNCTION (2 << (2 - 1))
#define L_MOUSE    (2 << (3 - 1))
#define L_WHEEL    (2 << (4 - 1))
#define L_LOCK     (2 << (5 - 1))

#define MOD_CTL (MOD_BIT(KC_LCTRL) | MOD_BIT(KC_RCTRL))
#define MOD_SFT (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT))
#define MOD_ALT (MOD_BIT(KC_LALT) | MOD_BIT(KC_RALT))
#define MOD_GUI (MOD_BIT(KC_LGUI) | MOD_BIT(KC_RGUI))

#define KEYFREQ_LOG_UPDATE_INTERVAL 30000 /* 30sec x 20 = 600sec (10min) */
#define SCREEN_FRAME_INTERVAL 55 /* 18fps */
#define ANIMATION_ENABLE

extern uint8_t is_master;

char *get_layer_name(void) {
    switch (layer_state)
    {
      case L_BASE:
        return "Base";
      case L_RAISE:
        return "Raise";
      case L_FUNCTION:
        return "Function";
      case L_MOUSE:
        return "Mouse";
      case L_WHEEL | L_MOUSE:
        return "Wheel";
      case L_LOCK:
        return "LOCKED";
      default:
        return "(Undefined)";
    }
}

int keyfreq_count = 0;
int last_keyfreq_update = 0;
int animation_frame = 0;

char hoshi[2][21] = {
    { 0x20, 0x20, 0x20, 0x91, 0x20, 0x20, 0x20, 0x20, 0x91, 0x20, 0x20, 0x63, 0x72, 0x6b, 0x62, 0x64, 0x20, 0x70, 0x68, 0x69 },
    { 0x20, 0x91, 0x20, 0x20, 0x20, 0x20, 0x91, 0x20, 0x20, 0x20, 0x91, 0x20, 0x20, 0x20, 0x20, 0x20, 0x91, 0x20, 0x20, 0x20 }
};

char taiyo_and_grid[4][21] = {
  { 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x80, 0x81, 0x82, 0x83, 0x84, 0x20 },
  { 0xa5, 0x20, 0x20, 0x20, 0x20, 0xa5, 0x20, 0x20, 0x20, 0x20, 0xa5, 0x20, 0x20, 0x20, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0x20 },
  { 0xc5, 0xc5, 0xc5, 0xc5, 0xc5, 0xc5, 0xc5, 0xc5, 0xc5, 0xc5, 0xc5, 0xc5, 0xc5, 0xc5, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5 }
};

char palm[3][22] = {
  { 0x8f, 0x90, 0x8f, 0x90, 0x8f, 0x90, 0x8f, 0x90, 0x8f, 0x90, 0x8f, 0x90, 0x8f, 0x90, 0x8f, 0x90, 0x8f, 0x90, 0x8f, 0x90, 0x8f, 0x90 },
  { 0xaf, 0xb0, 0xaf, 0xb0, 0xaf, 0xb0, 0xaf, 0xb0, 0xaf, 0xb0, 0xaf, 0xb0, 0xaf, 0xb0, 0xaf, 0xb0, 0xaf, 0xb0, 0xaf, 0xb0, 0xaf, 0xb0 },
  { 0xcf, 0xd0, 0xcf, 0xd0, 0xcf, 0xd0, 0xcf, 0xd0, 0xcf, 0xd0, 0xcf, 0xd0, 0xcf, 0xd0, 0xcf, 0xd0, 0xcf, 0xd0, 0xcf, 0xd0, 0xcf, 0xd0 }
};

char saku_nami_l[3][21] = {
  { 0xd3, 0xd3, 0xd3, 0xd3, 0xd3, 0xd3, 0xd3, 0xd3, 0xd3, 0xd3, 0xd3, 0xd3, 0xd3, 0xd3, 0xd3, 0xd3, 0xd3, 0xd3, 0xd3, 0xd3, 0xd3 },
  { 0xd2, 0xd2, 0xd2, 0xd2, 0xd2, 0xd2, 0xd2, 0xd2, 0xd2, 0xd2, 0xd2, 0xd2, 0xd2, 0xd2, 0xd2, 0xd2, 0xd2, 0xd2, 0xd2, 0xd2 },
  { 0xd1, 0xd1, 0xd1, 0xd1, 0xd1, 0xd1, 0xd1, 0xd1, 0xd1, 0xd1, 0xd1, 0xd1, 0xd1, 0xd1, 0xd1, 0xd1, 0xd1, 0xd1, 0xd1, 0xd1, 0xd1 }
};

char saku_nami_r[3][21] = {
  { 0xb3, 0xb3, 0xb3, 0xb3, 0xb3, 0xb3, 0xb3, 0xb3, 0xb3, 0xb3, 0xb3, 0xb3, 0xb3, 0xb3, 0xb3, 0xb3, 0xb3, 0xb3, 0xb3, 0xb3, 0xb3 },
  { 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2, 0xb2 },
  { 0xb1, 0xb1, 0xb1, 0xb1, 0xb1, 0xb1, 0xb1, 0xb1, 0xb1, 0xb1, 0xb1, 0xb1, 0xb1, 0xb1, 0xb1, 0xb1, 0xb1, 0xb1, 0xb1, 0xb1, 0xb1 }
};

char keyfreq_log[2][21] = {
  { 0xa6, 0xa6, 0xa6, 0xa6, 0xa6, 0xa6, 0xa6, 0xa6, 0xa6, 0xa6, 0xa6, 0xa6, 0xa6, 0xa6, 0xa6, 0xa6, 0xa6, 0xa6, 0xa6, 0xa6, 0xa6 },
  { 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6 }
};

void update_keyfreq_log(void) {
    if (keyfreq_count)
      switch (keyfreq_count / ((KEYFREQ_LOG_UPDATE_INTERVAL / 1000) * 10 / 15)) {
       case 0: keyfreq_log[1][20] = 0xc7; break;
       case 1: keyfreq_log[1][20] = 0xc8; break;
       case 2: keyfreq_log[1][20] = 0xc9; break;
       case 3: keyfreq_log[1][20] = 0xca; break;
       case 4: keyfreq_log[1][20] = 0xcb; break;
       case 5: keyfreq_log[1][20] = 0xcc; break;
       case 6: keyfreq_log[1][20] = 0xcd; break;
       case 7: keyfreq_log[1][20] = 0xce; break;
       case 8: keyfreq_log[0][20] = 0xa7, keyfreq_log[1][20] = 0xce; break;
       case 9: keyfreq_log[0][20] = 0xa8, keyfreq_log[1][20] = 0xce; break;
       case 10: keyfreq_log[0][20] = 0xa9, keyfreq_log[1][20] = 0xce; break;
       case 11: keyfreq_log[0][20] = 0xaa, keyfreq_log[1][20] = 0xce; break;
       case 12: keyfreq_log[0][20] = 0xab, keyfreq_log[1][20] = 0xce; break;
       case 13: keyfreq_log[0][20] = 0xac, keyfreq_log[1][20] = 0xce; break;
       case 14: keyfreq_log[0][20] = 0xad, keyfreq_log[1][20] = 0xce; break;
       default: keyfreq_log[0][20] = 0xae, keyfreq_log[1][20] = 0xce; break; /* > 10 keys per sec */
      }

    if (timer_elapsed(last_keyfreq_update) < KEYFREQ_LOG_UPDATE_INTERVAL) return;
    last_keyfreq_update = timer_read();

    /* shift the log every 60 seconds */
    keyfreq_count = 0;
    memmove(keyfreq_log[0], keyfreq_log[0] + 1, 20);
    memmove(keyfreq_log[1], keyfreq_log[1] + 1, 20);
    keyfreq_log[0][20] = 0xa6;
    keyfreq_log[1][20] = 0xc6;
}

void prepare_background(void) {
  struct CharacterMatrix matrix;

  matrix_clear(&matrix);
  if (is_master) {
    matrix_write_ln(&matrix, taiyo_and_grid[0]);
    matrix_write_ln(&matrix, taiyo_and_grid[1]);
    matrix_write_ln(&matrix, taiyo_and_grid[2]);
    matrix_write(&matrix, saku_nami_l[1]);
  } else {
    matrix_write_ln(&matrix, hoshi[0]);
    matrix_write_ln(&matrix, hoshi[1]);
    matrix_write_ln(&matrix, "");
    matrix_write(&matrix, saku_nami_r[1]);
  }

  matrix_push_background(&matrix);
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
        matrix_write_range(&matrix, saku_nami_l[0], animation_frame % 6, 120);
        set_overwrite_mode(true);
        matrix_return(&matrix);
        matrix_write_range(&matrix, saku_nami_l[2], animation_frame / 4, 120);
        set_overwrite_mode(false);
    } else {
        matrix_write_ln(&matrix, "");
        matrix_write_range_ln(&matrix, palm[0], 12 - animation_frame / 2, 120);
        matrix_write_range_ln(&matrix, palm[1], 12 - animation_frame / 2, 120);
        matrix_write_range(&matrix, palm[2], 12 - animation_frame / 2, 120);
        set_overwrite_mode(true);
        matrix_return(&matrix);
        matrix_write_range(&matrix, saku_nami_r[0], 6 - animation_frame % 6, 120);
        matrix_return(&matrix);
        matrix_return(&matrix);
        matrix_write_range(&matrix, saku_nami_r[2], 6 - animation_frame / 4, 120);
        set_overwrite_mode(false);
    }

    matrix_push(&matrix); /* push to the ssd1306 driver */
}

void oled_init(void) {
  iota_gfx_init(!has_usb());   // turns on the display
  prepare_background();
}

void oled_update(void) {
  if (is_master) update_keyfreq_log();
  prepare_next_frame();
  iota_gfx_task();             // trigger redisplay
}

void oled_record_event(uint16_t keycode, keyrecord_t *record) {
    if (is_master && record->event.pressed) {
        keyfreq_count++;
    }
}
