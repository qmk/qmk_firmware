/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/

#pragma once
// 15,  the default,  is too low for Kailh Coppers. I get lots of double presses.
// (ba-dum tish)
// #undef  DEBOUNCE
// #define DEBOUNCE 22

// Reduce USB power consumption to 100 mA to make it work with a Lightning to USB 3 Camera Adapter (MK0W2AM/A). ZSA says 100 mA is high enough for the keyboard if you disable the big Shine/Glow LEDs first.
#undef  USB_MAX_POWER_CONSUMPTION
#define USB_MAX_POWER_CONSUMPTION 100
