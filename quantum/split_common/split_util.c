#include "split_util.h"
#include "matrix.h"
#include "keyboard.h"
#include "config.h"
#include "timer.h"
#include "transport.h"
#include "quantum.h"

#ifdef EE_HANDS
#   include "tmk_core/common/eeprom.h"
#   include "eeconfig.h"
#endif

#if defined(RGBLIGHT_ENABLE) && defined(RGBLED_SPLIT)
#include "rgblight.h"
#endif

volatile bool isLeftHand = true;

#ifdef MASTER_CHECK_USB_ENUMERATED
    volatile bool contacted_by_master;
#endif

__attribute__((weak))
bool is_keyboard_left(void) {
  #if defined(SPLIT_HAND_PIN)
    // Test pin SPLIT_HAND_PIN for High/Low, if low it's right hand
    setPinInput(SPLIT_HAND_PIN);
    return readPin(SPLIT_HAND_PIN);
  #elif defined(EE_HANDS)
    return eeprom_read_byte(EECONFIG_HANDEDNESS);
  #elif defined(MASTER_RIGHT)
    return !is_keyboard_master();
  #endif

  return is_keyboard_master();
}

int is_keyboard_master(void) {
#ifdef __AVR__
  static enum { UNKNOWN = -1, SLAVE = 0, MASTER = 1 } usbstate = UNKNOWN;

  // only check once, as this is called often
  if (usbstate == UNKNOWN) {
    // Set half to master if it's been assigned a usb address
    // Set device to slave if it's been contacted by a master half
    #ifdef MASTER_CHECK_USB_ENUMERATED
      // This will be true if a USB connection has been established
      usbstate = (UDADDR & _BV(ADDEN)) ? MASTER : UNKNOWN;
      usbstate = contacted_by_master ? SLAVE : UNKNOWN;

    // Rely on checking VBUS PAD
    #else
      USBCON |= (1 << OTGPADE);  // enables VBUS pad
      wait_us(5);

      usbstate = (USBSTA & (1 << VBUS)) ? MASTER : SLAVE;  // checks state of VBUS
    #endif
  }

  #ifdef MASTER_CHECK_USB_ENUMERATED
    return usbstate;
  #else
    return (usbstate == MASTER);
  #endif
#else
  return true;
#endif
}

void keyboard_master_setup(void) {
#if defined(USE_I2C) || defined(EH)
  #ifdef SSD1306OLED
    matrix_master_OLED_init ();
  #endif
#endif
  transport_master_init();
}

void keyboard_slave_setup(void)
{
  transport_slave_init();
}

// this code runs before the usb and keyboard is initialized
void matrix_setup(void)
{
  isLeftHand = is_keyboard_left();

#if defined(RGBLIGHT_ENABLE) && defined(RGBLED_SPLIT)
  uint8_t num_rgb_leds_split[2] = RGBLED_SPLIT;
  if (isLeftHand) {
    rgblight_set_clipping_range(0, num_rgb_leds_split[0]);
  }
  else {
    rgblight_set_clipping_range(num_rgb_leds_split[0], num_rgb_leds_split[1]);
  }
#endif

#ifndef MASTER_CHECK_USB_ENUMERATED
  if (is_keyboard_master())
  {
    keyboard_master_setup();
  }
  else
  {
    keyboard_slave_setup();
  }
#endif
}
