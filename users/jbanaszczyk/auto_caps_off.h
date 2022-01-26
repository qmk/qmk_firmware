#pragma once

//==[ LED_UPDATE_AUTO_CAPS configuration begins ]=============

#define LED_UPDATE_AUTO_CAPS_OFF_RETURNS true

#define AUTO_CAPS_OFF_TIMEOUT_SECONDS 30

// uncomment according to your needs
//#define AUTO_CAPS_OFF_IGNORE_CAPS
//#define AUTO_CAPS_OFF_IGNORE_SCROLL
//#define AUTO_CAPS_OFF_IGNORE_NUM

//==[ LED_UPDATE_AUTO_CAPS configuration ends ]===============

bool process_record_auto_caps_off(uint16_t keycode, keyrecord_t *record);
bool led_update_auto_caps_off(void);
