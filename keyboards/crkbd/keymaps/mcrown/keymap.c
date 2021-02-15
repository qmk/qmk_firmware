#include "keymap.h"

keymap_config_t keymap_config;
uint8_t is_master;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] =  LAYOUT_wrapper( \
          /*,-------------------------------------------------|-----|--------------------------------------------------------|.*/
          _____________________QWERTY_L1______________________,      _____________________QWERTY_R1______________________,
          /*|--------+--------+--------+--------+--------+----|     |--------+--------+--------+--------+--------+-----------|*/
          _____________________QWERTY_L2______________________,      _____________________QWERTY_R2______________________,
          /*|--------+--------+--------+--------+--------+----|     |--------+--------+--------+--------+--------+-----------|*/
          _____________________QWERTY_L3______________________,      _____________________QWERTY_R3______________________,
          /*|--------+--------+--------+--------+--------+----|     |--------+--------+--------+--------+--------+-----------|*/
                            _____________MOD_LEFT_____________,      _____________MOD_RIGHT____________
                        /*|-----------------------------------|     |----------------------------------|*/
  ),

  [_LOWER] =  LAYOUT_wrapper( \
          /*,-------------------------------------------------|-----|--------------------------------------------------------|.*/
          _____________________LOWER_L1_______________________,      _____________________LOWER_R1_______________________,
          /*|--------+--------+--------+--------+--------+----|     |--------+--------+--------+--------+--------+-----------|*/
          _____________________LOWER_L2_______________________,      _____________________LOWER_R2_______________________,
          /*|--------+--------+--------+--------+--------+----|     |--------+--------+--------+--------+--------+-----------|*/
          _____________________LOWER_L3_______________________,      _____________________LOWER_R3_______________________,
          /*|--------+--------+--------+--------+--------+----|     |--------+--------+--------+--------+--------+-----------|*/
                            _____________MOD_LEFT_____________,      _____________MOD_RIGHT____________
                        /*|-----------------------------------|     |----------------------------------|*/
  ),

  [_RAISE] = LAYOUT_wrapper( \
          /*,-------------------------------------------------|-----|--------------------------------------------------------|.*/
          _____________________RAISE_L1_______________________,      _____________________RAISE_R1_______________________,
          /*|--------+--------+--------+--------+--------+----|     |--------+--------+--------+--------+--------+-----------|*/
          _____________________RAISE_L2_______________________,      _____________________RAISE_R2_______________________,
          /*|--------+--------+--------+--------+--------+----|     |--------+--------+--------+--------+--------+-----------|*/
          _____________________RAISE_L3_______________________,      _____________________RAISE_R3_______________________,
          /*|--------+--------+--------+--------+--------+----|     |--------+--------+--------+--------+--------+-----------|*/
                            _____________MOD_LEFT_____________,      _____________MOD_RIGHT____________
                        /*|-----------------------------------|     |----------------------------------|*/
  ),

  [_ADJUST] = LAYOUT_wrapper( \
          /*,-------------------------------------------------|-----|--------------------------------------------------------|.*/
          _____________________ADJUST_L1______________________,      _____________________ADJUST_R1______________________,
          /*|--------+--------+--------+--------+--------+----|     |--------+--------+--------+--------+--------+-----------|*/
          _____________________ADJUST_L2______________________,      _____________________ADJUST_R2______________________,
          /*|--------+--------+--------+--------+--------+----|     |--------+--------+--------+--------+--------+-----------|*/
          _____________________ADJUST_L3______________________,      _____________________ADJUST_R3______________________,
          /*|--------+--------+--------+--------+--------+----|     |--------+--------+--------+--------+--------+-----------|*/
                            _____________MOD_LEFT_____________,      _____________MOD_RIGHT____________
                        /*|-----------------------------------|     |----------------------------------|*/
  ),
};

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    /* SD1306 OLED init, make sure to add #define SSD1306OLED in config.h */
    #ifdef SSD1306OLED
    iota_gfx_init(FALSE==has_usb());   /* turns on the display */
    #endif
}

/* SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h */
#ifdef SSD1306OLED

/* When add source files to SRC in rules.mk, you can use functions. */
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

void matrix_scan_user(void)
{
    iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix)
{
    if (is_master)
    {
        /* If you want to change the display of OLED, you need to change here. */
        matrix_write_ln(matrix, read_layer_state());
        matrix_write_ln(matrix, read_keylog());
        matrix_write_ln(matrix, read_keylogs());
    }
    else
    {
        matrix_write(matrix, read_logo());
    }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source)
{
    if(memcmp(dest->display, source->display, sizeof(dest->display)))
    {
        memcpy(dest->display, source->display, sizeof(dest->display));
        dest->dirty = TRUE;
    }
}

void iota_gfx_task_user(void)
{
    struct CharacterMatrix matrix;
    matrix_clear(&matrix);
    matrix_render_user(&matrix);
    matrix_update(&display, &matrix);
}
#endif /* SSD1306OLED */

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    bool user_records_press=TRUE;

    if (record->event.pressed)
    {
        #ifdef SSD1306OLED
        set_keylog(keycode, record);
        #endif
    }

    switch (keycode)
    {
        case QWERTY:
            if (record->event.pressed)
            {
                set_single_persistent_default_layer(_QWERTY);
            }
            break;

        case LOWER:
            if(record->event.pressed)
            {
                layer_on(_LOWER);
                update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
            }
            else
            {
                layer_off(_LOWER);
                update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
            }
            break;

        case RAISE:
            if (record->event.pressed)
            {
                layer_on(_RAISE);
                update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
            }
            else
            {
                layer_off(_RAISE);
                update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
            }
            break;

        case ADJUST:
            if (record->event.pressed)
            {
                layer_on(_ADJUST);
            }
            else
            {
                layer_off(_ADJUST);
            }
            break;

        case RGB_MOD:
            #ifdef RGBLIGHT_ENABLE
            if(record->event.pressed)
            {
                rgblight_mode(RGB_current_mode);
                rgblight_step();
                RGB_current_mode = rgblight_config.mode;
            }
            #endif
            break;

        case RGBRST:
            #ifdef RGBLIGHT_ENABLE
            if(record->event.pressed)
            {
                eeconfig_update_rgblight_default();
                rgblight_enable();
                RGB_current_mode = rgblight_config.mode;
            }
            #endif
            break;

        default:
            user_records_press=FALSE;
            break;
    }

    return FALSE==user_records_press;
}
