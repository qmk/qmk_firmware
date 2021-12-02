#include "satisfaction75.h"
#include "tmk_core/common/eeprom.h"

void pre_encoder_mode_change(){
  if(encoder_mode == ENC_MODE_CLOCK_SET){
    RTCDateTime timespec;
    timespec.year = year_config;
    timespec.month = month_config;
    timespec.day = day_config;
    // timespec.dayofweek = last_timespec.dayofweek;
    // timespec.dstflag = last_timespec.dstflag;
    timespec.millisecond = (hour_config * 60 + minute_config) * 60 * 1000;
    rtcSetTime(&RTCD1, &timespec);
  } else if (encoder_mode == ENC_MODE_BACKLIGHT){
    backlight_config_save();
  }
}

void post_encoder_mode_change(){
  if(encoder_mode == ENC_MODE_CLOCK_SET){
    hour_config = (last_minute / 60);
    minute_config = last_minute % 60;
    year_config = last_timespec.year;
    month_config = last_timespec.month;
    day_config = last_timespec.day;
    time_config_idx = 0;
  }
}

void change_encoder_mode(bool negative){
  pre_encoder_mode_change();
  if(enabled_encoder_modes == 0){
    enabled_encoder_modes = 0x1F;
  }
  do {
    if(negative){
      if (encoder_mode == 0){
        encoder_mode = _NUM_ENCODER_MODES - 1;
      } else{
        encoder_mode = encoder_mode - 1;
      }
    } else {
        encoder_mode = (encoder_mode + 1) % _NUM_ENCODER_MODES;
    }
  } while(((1 << encoder_mode) & enabled_encoder_modes) == 0);
  post_encoder_mode_change();
}

void update_time_config(int8_t increment){
  uint8_t day_limit = 31;
  uint16_t adjusted_year = 1980 + year_config;
  switch(time_config_idx){
    case 0: // hour
    default:
      hour_config = (hour_config + increment) % 24;
      if (hour_config < 0){
        hour_config += 24;
      }
      break;
    case 1: // minute
      minute_config = (minute_config + increment) % 60;
      if (minute_config < 0){
        minute_config += 60;
      }
      break;
    case 2: // year
      year_config += increment;
      break;
    case 3: // month
      month_config = (month_config % 12) + increment;
      if (month_config <= 0){
        month_config += 12;
      }
      break;
    case 4: //day
      if (month_config == 9 || month_config == 4 || month_config == 6 || month_config == 11){
        day_limit = 30;
      } else if(month_config == 2){
        day_limit = adjusted_year % 4 == 0 && !(adjusted_year % 100 == 0 && adjusted_year % 400 != 0) ? 29 : 28;
      }
      day_config = (day_config % day_limit) + increment;
      if(day_config <= 0){
        day_config += day_limit;
      }
      break;
  }
}

uint16_t handle_encoder_clockwise(){
  uint16_t mapped_code = 0;
  switch(encoder_mode){
    default:
    case ENC_MODE_VOLUME:
      mapped_code = KC_VOLU;
      break;
    case ENC_MODE_MEDIA:
      mapped_code = KC_MEDIA_NEXT_TRACK;
      break;
    case ENC_MODE_SCROLL:
      mapped_code = KC_WH_D;
      break;
    case ENC_MODE_BACKLIGHT:
      kb_backlight_config.level = kb_backlight_config.level + 1;
      if(kb_backlight_config.level > BACKLIGHT_LEVELS){
        kb_backlight_config.level = BACKLIGHT_LEVELS;
      }
      backlight_set(kb_backlight_config.level);
      if (kb_backlight_config.level != 0){
        kb_backlight_config.enable = true;
      }
      break;
    case ENC_MODE_BRIGHTNESS:
      mapped_code = KC_BRIGHTNESS_UP;
      break;
#ifdef DYNAMIC_KEYMAP_ENABLE
    case ENC_MODE_CUSTOM0:
      mapped_code = retrieve_custom_encoder_config(0, ENC_CUSTOM_CW);
      break;
    case ENC_MODE_CUSTOM1:
      mapped_code = retrieve_custom_encoder_config(1, ENC_CUSTOM_CW);
      break;
    case ENC_MODE_CUSTOM2:
      mapped_code = retrieve_custom_encoder_config(2, ENC_CUSTOM_CW);
      break;
#endif
    case ENC_MODE_CLOCK_SET:
      update_time_config(1);
      queue_for_send = true;
      break;
  }
  return mapped_code;
}

uint16_t handle_encoder_ccw(){
  uint16_t mapped_code = 0;
  switch(encoder_mode){
    default:
    case ENC_MODE_VOLUME:
      mapped_code = KC_VOLD;
      break;
    case ENC_MODE_MEDIA:
      mapped_code = KC_MEDIA_PREV_TRACK;
      break;
    case ENC_MODE_SCROLL:
      mapped_code = KC_WH_U;
      break;
    case ENC_MODE_BACKLIGHT:
      // mapped_code = BL_DEC;
      if(kb_backlight_config.level != 0){
        kb_backlight_config.level = kb_backlight_config.level - 1;
      }
      backlight_set(kb_backlight_config.level);
      if (kb_backlight_config.level == 0){
        kb_backlight_config.enable = false;
      }
      break;
    case ENC_MODE_BRIGHTNESS:
      mapped_code = KC_BRIGHTNESS_DOWN;
      break;
#ifdef DYNAMIC_KEYMAP_ENABLE
    case ENC_MODE_CUSTOM0:
      mapped_code = retrieve_custom_encoder_config(0, ENC_CUSTOM_CCW);
      break;
    case ENC_MODE_CUSTOM1:
      mapped_code = retrieve_custom_encoder_config(1, ENC_CUSTOM_CCW);
      break;
    case ENC_MODE_CUSTOM2:
      mapped_code = retrieve_custom_encoder_config(2, ENC_CUSTOM_CCW);
      break;
#endif

    case ENC_MODE_CLOCK_SET:
      update_time_config(-1);
      queue_for_send = true;
      break;
  }
  return mapped_code;
}

uint16_t handle_encoder_press(){
  uint16_t mapped_code = 0;
  switch(encoder_mode){
    case ENC_MODE_VOLUME:
      mapped_code = KC_MUTE;
      break;
    default:
    case ENC_MODE_MEDIA:
      mapped_code = KC_MEDIA_PLAY_PAUSE;
      break;
    case ENC_MODE_SCROLL:
      mapped_code = KC_BTN3;
      break;
    case ENC_MODE_BACKLIGHT:
      // mapped_code = BL_TOGG;
      kb_backlight_config.breathing = !kb_backlight_config.breathing;
      if(!kb_backlight_config.breathing){
        breathing_disable();
      } else{
        breathing_enable();
      }
      break;
#ifdef DYNAMIC_KEYMAP_ENABLE
    case ENC_MODE_CUSTOM0:
      mapped_code = retrieve_custom_encoder_config(0, ENC_CUSTOM_PRESS);
      break;
    case ENC_MODE_CUSTOM1:
      mapped_code = retrieve_custom_encoder_config(1, ENC_CUSTOM_PRESS);
      break;
    case ENC_MODE_CUSTOM2:
      mapped_code = retrieve_custom_encoder_config(2, ENC_CUSTOM_PRESS);
      break;
#endif
    case ENC_MODE_CLOCK_SET:
      time_config_idx = (time_config_idx + 1) % 5;
    case ENC_MODE_BRIGHTNESS:
      break;
  }
  return mapped_code;
}


uint16_t retrieve_custom_encoder_config(uint8_t encoder_idx, uint8_t behavior){
#ifdef DYNAMIC_KEYMAP_ENABLE
    void* addr = (void*)(EEPROM_CUSTOM_ENCODER + (encoder_idx * 6) + (behavior * 2));
    //big endian
    uint16_t keycode = eeprom_read_byte(addr) << 8;
    keycode |= eeprom_read_byte(addr + 1);
    return keycode;
#else
    return 0;
#endif
}

void set_custom_encoder_config(uint8_t encoder_idx, uint8_t behavior, uint16_t new_code){
#ifdef DYNAMIC_KEYMAP_ENABLE
    void* addr = (void*)(EEPROM_CUSTOM_ENCODER + (encoder_idx * 6) + (behavior * 2));
    eeprom_update_byte(addr, (uint8_t)(new_code >> 8));
    eeprom_update_byte(addr + 1, (uint8_t)(new_code & 0xFF));
#endif
}
