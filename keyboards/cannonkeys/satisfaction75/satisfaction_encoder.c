#include "satisfaction75.h"

void pre_encoder_mode_change(){
  if(encoder_mode == ENC_MODE_CLOCK_SET){
    RTCDateTime timespec;
    timespec.year = last_timespec.year;
    timespec.month = last_timespec.month;
    timespec.day = last_timespec.day;
    timespec.dayofweek = last_timespec.dayofweek;
    timespec.dstflag = last_timespec.dstflag;
    timespec.millisecond = (hour_config * 60 + minute_config) * 60 * 1000;
    rtcSetTime(&RTCD1, &timespec);
  }
}

void post_encoder_mode_change(){
  if(encoder_mode == ENC_MODE_CLOCK_SET){
    hour_config = (last_minute / 60);
    minute_config = last_minute % 60;
    time_config_idx = 0;
  }
}

void change_encoder_mode(bool negative){
  pre_encoder_mode_change();
  if(negative){
    if (encoder_mode == 0){
      encoder_mode = _NUM_ENCODER_MODES - 1;
    } else{
      encoder_mode = encoder_mode - 1;
    }
  } else {
      encoder_mode = (encoder_mode + 1) % _NUM_ENCODER_MODES;
  }
  post_encoder_mode_change();
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
      // mapped_code = BL_INC;
      kb_backlight_level = kb_backlight_level + 1;
      if(kb_backlight_level > BACKLIGHT_LEVELS){
        kb_backlight_level = BACKLIGHT_LEVELS;
      }
      backlight_set(kb_backlight_level);
      break;
    case ENC_MODE_BRIGHTNESS:
      mapped_code = KC_BRIGHTNESS_UP;
      break;
    case ENC_MODE_CLOCK_SET:
      if(time_config_idx == 0){
        hour_config = (hour_config + 1) % 24;
      }else{
        minute_config = (minute_config + 1) % 60;
      }
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
      if(kb_backlight_level != 0){
        kb_backlight_level = kb_backlight_level - 1;
      }
      backlight_set(kb_backlight_level);
      break;
    case ENC_MODE_BRIGHTNESS:
      mapped_code = KC_BRIGHTNESS_DOWN;
      break;
    case ENC_MODE_CLOCK_SET:
      if(time_config_idx == 0){
        // Note - not using MOD here because it's an unsigned int
        // When we subtract 1 from 0, we get a very large number
        if(hour_config == 0){
          hour_config = 23;
        } else {
          hour_config = (hour_config - 1);
        }
      }else{
        if(minute_config == 0){
          minute_config = 59;
        }else{
          minute_config = minute_config - 1;
        }
      }
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
    case ENC_MODE_MEDIA:
      mapped_code = KC_MEDIA_PLAY_PAUSE;
      break;
    case ENC_MODE_SCROLL:
      mapped_code = KC_BTN3;
      break;
    case ENC_MODE_BACKLIGHT:
      mapped_code = BL_TOGG;
      break;
    case ENC_MODE_CLOCK_SET:
      time_config_idx = (time_config_idx + 1) % 2;
    default:
    case ENC_MODE_BRIGHTNESS:
      break;
  }
  return mapped_code;
}
