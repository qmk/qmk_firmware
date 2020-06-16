#include "satisfaction75.h"
#include "print.h"
#include "debug.h"

#include "ch.h"
#include "hal.h"

#ifdef QWIIC_MICRO_OLED_ENABLE
#include "micro_oled.h"
#include "qwiic.h"
#endif

#include "timer.h"

#include "raw_hid.h"
#include "dynamic_keymap.h"
#include "tmk_core/common/eeprom.h"
#include "version.h" // for QMK_BUILDDATE used in EEPROM magic

/* Artificial delay added to get media keys to work in the encoder*/
#define MEDIA_KEY_DELAY 10

uint16_t last_flush;

volatile uint8_t led_numlock = false;
volatile uint8_t led_capslock = false;
volatile uint8_t led_scrolllock = false;

uint8_t layer;

bool queue_for_send = false;
bool clock_set_mode = false;
uint8_t oled_mode = OLED_DEFAULT;
bool oled_sleeping = false;

uint8_t encoder_value = 32;
uint8_t encoder_mode = ENC_MODE_VOLUME;
uint8_t enabled_encoder_modes = 0x1F;

RTCDateTime last_timespec;
uint16_t last_minute = 0;

uint8_t time_config_idx = 0;
int8_t hour_config = 0;
int16_t minute_config = 0;
int8_t year_config = 0;
int8_t month_config = 0;
int8_t day_config = 0;
uint8_t previous_encoder_mode = 0;

backlight_config_t kb_backlight_config = {
  .enable = true,
  .breathing = true,
  .level = BACKLIGHT_LEVELS
};

#ifdef VIA_ENABLE

void backlight_get_value( uint8_t *data )
{
	uint8_t *value_id = &(data[0]);
	uint8_t *value_data = &(data[1]);
  switch (*value_id)
  {
    case id_qmk_backlight_brightness:
    {
      // level / BACKLIGHT_LEVELS * 255
      value_data[0] = ((uint16_t)kb_backlight_config.level) * 255 / BACKLIGHT_LEVELS;
      break;
    }
    case id_qmk_backlight_effect:
    {
      value_data[0] = kb_backlight_config.breathing ? 1 : 0;
      break;
    }
  }
}

void backlight_set_value( uint8_t *data )
{
	uint8_t *value_id = &(data[0]);
	uint8_t *value_data = &(data[1]);
  switch (*value_id)
  {
    case id_qmk_backlight_brightness:
    {
      // level / 255 * BACKLIGHT_LEVELS
      kb_backlight_config.level = ((uint16_t)value_data[0]) * BACKLIGHT_LEVELS / 255;
      backlight_set(kb_backlight_config.level);
      break;
    }
    case id_qmk_backlight_effect:
    {
      if ( value_data[0] == 0 ) {
        kb_backlight_config.breathing = false;
        breathing_disable();
      } else {
        kb_backlight_config.breathing = true;
        breathing_enable();
      }
      break;
    }
  }
}

void raw_hid_receive_kb( uint8_t *data, uint8_t length )
{
  uint8_t *command_id = &(data[0]);
  uint8_t *command_data = &(data[1]);
  switch ( *command_id )
  {
    case id_get_keyboard_value:
    {
            switch( command_data[0])
            {
                case id_oled_default_mode:
                {
                    uint8_t default_oled = eeprom_read_byte((uint8_t*)EEPROM_DEFAULT_OLED);
                    command_data[1] = default_oled;
                    break;
                }
                case id_oled_mode:
                {
                    command_data[1] = oled_mode;
                    break;
                }
                case id_encoder_modes:
                {
                    command_data[1] = enabled_encoder_modes;
                    break;
                }
                case id_encoder_custom:
                {
                    uint8_t custom_encoder_idx = command_data[1];
                    uint16_t keycode = retrieve_custom_encoder_config(custom_encoder_idx, ENC_CUSTOM_CW);
                    command_data[2] =  keycode >> 8;
                    command_data[3] = keycode & 0xFF;
                    keycode = retrieve_custom_encoder_config(custom_encoder_idx, ENC_CUSTOM_CCW);
                    command_data[4] =  keycode >> 8;
                    command_data[5] = keycode & 0xFF;
                    keycode = retrieve_custom_encoder_config(custom_encoder_idx, ENC_CUSTOM_PRESS);
                    command_data[6] =  keycode >> 8;
                    command_data[7] = keycode & 0xFF;
                    break;
                }
                default:
                {
                    *command_id = id_unhandled;
                    break;
                }
            }
      break;
    }
    case id_set_keyboard_value:
    {
      switch(command_data[0]){
        case id_oled_default_mode:
        {
          eeprom_update_byte((uint8_t*)EEPROM_DEFAULT_OLED, command_data[1]);
          break;
        }
        case id_oled_mode:
        {
          oled_mode = command_data[1];
          draw_ui();
          break;
        }
        case id_encoder_modes:
        {
          enabled_encoder_modes = command_data[1];
          eeprom_update_byte((uint8_t*)EEPROM_ENABLED_ENCODER_MODES, enabled_encoder_modes);
          break;
        }
        case id_encoder_custom:
        {
          uint8_t custom_encoder_idx = command_data[1];
          uint8_t encoder_behavior = command_data[2];
          uint16_t keycode = (command_data[3] << 8) | command_data[4];
          set_custom_encoder_config(custom_encoder_idx, encoder_behavior, keycode);
          break;
        }
        default:
        {
          *command_id = id_unhandled;
          break;
        }
      }
      break;
    }
    case id_lighting_set_value:
    {
      backlight_set_value(command_data);
      break;
    }
    case id_lighting_get_value:
    {
      backlight_get_value(command_data);
      break;
    }
    case id_lighting_save:
    {
      backlight_config_save();
      break;
    }
    default:
    {
      // Unhandled message.
      *command_id = id_unhandled;
      break;
    }
  }
  // DO NOT call raw_hid_send(data,length) here, let caller do this
}
#endif


void read_host_led_state(void) {
  uint8_t leds = host_keyboard_leds();
  if (leds & (1 << USB_LED_NUM_LOCK))    {
    if (led_numlock == false){
    led_numlock = true;}
    } else {
    if (led_numlock == true){
    led_numlock = false;}
    }
  if (leds & (1 << USB_LED_CAPS_LOCK))   {
    if (led_capslock == false){
    led_capslock = true;}
    } else {
    if (led_capslock == true){
    led_capslock = false;}
    }
  if (leds & (1 << USB_LED_SCROLL_LOCK)) {
    if (led_scrolllock == false){
    led_scrolllock = true;}
    } else {
    if (led_scrolllock == true){
    led_scrolllock = false;}
    }
}

uint32_t layer_state_set_kb(uint32_t state) {
  state = layer_state_set_user(state);
  layer = biton32(state);
  queue_for_send = true;
  return state;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  queue_for_send = true;
  switch (keycode) {
    case OLED_TOGG:
      if(!clock_set_mode){
        if (record->event.pressed) {
          oled_mode = (oled_mode + 1) % _NUM_OLED_MODES;
          draw_ui();
        }
      }
      return false;
    case CLOCK_SET:
      if (record->event.pressed) {
        if(clock_set_mode){
          pre_encoder_mode_change();
          clock_set_mode = false;
          encoder_mode = previous_encoder_mode;
          post_encoder_mode_change();

        }else{
          previous_encoder_mode = encoder_mode;
          pre_encoder_mode_change();
          clock_set_mode = true;
          encoder_mode = ENC_MODE_CLOCK_SET;
          post_encoder_mode_change();
        }
      }
      return false;
    case ENC_PRESS:
      if (record->event.pressed) {
        uint16_t mapped_code = handle_encoder_press();
        uint16_t held_keycode_timer = timer_read();
        if(mapped_code != 0){
          register_code16(mapped_code);
          while (timer_elapsed(held_keycode_timer) < MEDIA_KEY_DELAY){ /* no-op */ }
          unregister_code16(mapped_code);
        }
      } else {
        // Do something else when release
      }
      return false;
    default:
      break;
  }

  return process_record_user(keycode, record);
}


void encoder_update_kb(uint8_t index, bool clockwise) {
  encoder_value = (encoder_value + (clockwise ? 1 : -1)) % 64;
  queue_for_send = true;
  if (index == 0) {
    if (layer == 0){
      uint16_t mapped_code = 0;
      if (clockwise) {
        mapped_code = handle_encoder_clockwise();
      } else {
        mapped_code = handle_encoder_ccw();
      }
      uint16_t held_keycode_timer = timer_read();
      if(mapped_code != 0){
        register_code16(mapped_code);
        while (timer_elapsed(held_keycode_timer) < MEDIA_KEY_DELAY){ /* no-op */ }
        unregister_code16(mapped_code);
      }
    } else {
      if(clockwise){
        change_encoder_mode(false);
      } else {
        change_encoder_mode(true);
      }
    }
  }
}

void custom_config_reset(void){
  void *p = (void*)(VIA_EEPROM_CUSTOM_CONFIG_ADDR);
  void *end = (void*)(VIA_EEPROM_CUSTOM_CONFIG_ADDR+VIA_EEPROM_CUSTOM_CONFIG_SIZE);
  while ( p != end ) {
    eeprom_update_byte(p, 0);
    ++p;
  }
  eeprom_update_byte((uint8_t*)EEPROM_ENABLED_ENCODER_MODES, 0x1F);
}

void backlight_config_save(){
  eeprom_update_byte((uint8_t*)EEPROM_CUSTOM_BACKLIGHT, kb_backlight_config.raw);
}

void custom_config_load(){
  kb_backlight_config.raw = eeprom_read_byte((uint8_t*)EEPROM_CUSTOM_BACKLIGHT);
#ifdef DYNAMIC_KEYMAP_ENABLE
  oled_mode = eeprom_read_byte((uint8_t*)EEPROM_DEFAULT_OLED);
  enabled_encoder_modes = eeprom_read_byte((uint8_t*)EEPROM_ENABLED_ENCODER_MODES);
#endif
}

// Called from via_init() if VIA_ENABLE
// Called from matrix_init_kb() if not VIA_ENABLE
void via_init_kb(void)
{
  // If the EEPROM has the magic, the data is good.
  // OK to load from EEPROM.
  if (via_eeprom_is_valid()) {
    custom_config_load();
  } else	{
#ifdef DYNAMIC_KEYMAP_ENABLE
    // Reset the custom stuff
    custom_config_reset();
#endif
    // DO NOT set EEPROM valid here, let caller do this
  }
}

void matrix_init_kb(void)
{
#ifndef VIA_ENABLE
  via_init_kb();
  via_eeprom_set_valid(true);
#endif // VIA_ENABLE

  rtcGetTime(&RTCD1, &last_timespec);
  queue_for_send = true;
  backlight_init_ports();
  matrix_init_user();
}


void matrix_scan_kb(void) {
  rtcGetTime(&RTCD1, &last_timespec);
  uint16_t minutes_since_midnight = last_timespec.millisecond / 1000 / 60;

  if (minutes_since_midnight != last_minute){
    last_minute = minutes_since_midnight;
    if(!oled_sleeping){
      queue_for_send = true;
    }
  }
#ifdef QWIIC_MICRO_OLED_ENABLE
  if (queue_for_send && oled_mode != OLED_OFF) {
    oled_sleeping = false;
    read_host_led_state();
    draw_ui();
    queue_for_send = false;
  }
  if (timer_elapsed(last_flush) > ScreenOffInterval && !oled_sleeping) {
    send_command(DISPLAYOFF);      /* 0xAE */
    oled_sleeping = true;
  }
#endif
}

//
// In the case of VIA being disabled, we still need to check if
// keyboard level EEPROM memory is valid before loading.
// Thus these are copies of the same functions in VIA, since
// the backlight settings reuse VIA's EEPROM magic/version,
// and the ones in via.c won't be compiled in.
//
// Yes, this is sub-optimal, and is only here for completeness
// (i.e. catering to the 1% of people that want wilba.tech LED bling
// AND want persistent settings BUT DON'T want to use dynamic keymaps/VIA).
//
#ifndef VIA_ENABLE

bool via_eeprom_is_valid(void)
{
    char *p = QMK_BUILDDATE; // e.g. "2019-11-05-11:29:54"
    uint8_t magic0 = ( ( p[2] & 0x0F ) << 4 ) | ( p[3]  & 0x0F );
    uint8_t magic1 = ( ( p[5] & 0x0F ) << 4 ) | ( p[6]  & 0x0F );
    uint8_t magic2 = ( ( p[8] & 0x0F ) << 4 ) | ( p[9]  & 0x0F );

    return (eeprom_read_byte( (void*)VIA_EEPROM_MAGIC_ADDR+0 ) == magic0 &&
            eeprom_read_byte( (void*)VIA_EEPROM_MAGIC_ADDR+1 ) == magic1 &&
            eeprom_read_byte( (void*)VIA_EEPROM_MAGIC_ADDR+2 ) == magic2 );
}

// Sets VIA/keyboard level usage of EEPROM to valid/invalid
// Keyboard level code (eg. via_init_kb()) should not call this
void via_eeprom_set_valid(bool valid)
{
    char *p = QMK_BUILDDATE; // e.g. "2019-11-05-11:29:54"
    uint8_t magic0 = ( ( p[2] & 0x0F ) << 4 ) | ( p[3]  & 0x0F );
    uint8_t magic1 = ( ( p[5] & 0x0F ) << 4 ) | ( p[6]  & 0x0F );
    uint8_t magic2 = ( ( p[8] & 0x0F ) << 4 ) | ( p[9]  & 0x0F );

    eeprom_update_byte( (void*)VIA_EEPROM_MAGIC_ADDR+0, valid ? magic0 : 0xFF);
    eeprom_update_byte( (void*)VIA_EEPROM_MAGIC_ADDR+1, valid ? magic1 : 0xFF);
    eeprom_update_byte( (void*)VIA_EEPROM_MAGIC_ADDR+2, valid ? magic2 : 0xFF);
}

void via_eeprom_reset(void)
{
    // Set the VIA specific EEPROM state as invalid.
    via_eeprom_set_valid(false);
    // Set the TMK/QMK EEPROM state as invalid.
    eeconfig_disable();
}

#endif // VIA_ENABLE