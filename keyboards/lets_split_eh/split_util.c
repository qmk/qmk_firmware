#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include "split_util.h"
#include "matrix.h"
#include "keyboard.h"
#include "config.h"
#include "timer.h"
#include "pincontrol.h"
#include "split_flags.h"
#include "backlight.h"

#if defined(USE_I2C) || defined(EH)
#  include "i2c.h"
#else
#  include "serial.h"
#endif

volatile bool isLeftHand = true;

volatile uint8_t setTries = 0;

static void setup_handedness(void) {
  #ifdef EH
    // Test pin D3 for High/Low, if low it's right hand
    pinMode(D3, PinDirectionInput);
    isLeftHand = digitalRead(D3);
  #else
    #ifdef EE_HANDS
      isLeftHand = eeprom_read_byte(EECONFIG_HANDEDNESS);
    #else
      // I2C_MASTER_RIGHT is deprecated, use MASTER_RIGHT instead, since this works for both serial and i2c
      #if defined(I2C_MASTER_RIGHT) || defined(MASTER_RIGHT)
        isLeftHand = !has_usb();
      #else
        isLeftHand = has_usb();
      #endif
    #endif
  #endif
}

static void keyboard_master_setup(void) {
#if defined(USE_I2C) || defined(EH)
  i2c_master_init();
  #ifdef SSD1306OLED
    matrix_master_OLED_init ();
  #endif
#else
  serial_master_init();
#endif

    // For master the Backlight and RGB info needs to be sent on startup
    // Otherwise the salve won't start with the proper info until an update
    BACKLIT_DIRTY = true;
}

static void keyboard_slave_setup(void) {
  timer_init();
#if defined(USE_I2C) || defined(EH)
    i2c_slave_init(SLAVE_I2C_ADDRESS);
#else
    serial_slave_init();
#endif
}

bool has_usb(void) {
   USBCON |= (1 << OTGPADE); //enables VBUS pad
   _delay_us(5);
   return (USBSTA & (1<<VBUS));  //checks state of VBUS
}

void split_keyboard_setup(void) {
   setup_handedness();

   if (has_usb()) {
      keyboard_master_setup();
   } else {
      keyboard_slave_setup();
   }
   sei();
}

void keyboard_slave_loop(void) {
   matrix_init();

   while (1) {
      matrix_slave_scan();
      
      // read backlight info
    #ifdef BACKLIGHT_ENABLE
        if (BACKLIT_DIRTY) {
            //cli();
            backlight_set(i2c_slave_buffer[I2C_BACKLIT_START]);
            /*if (setTries < SET_TRIES) {
                setTries++;
            } else {
                setTries = 0;
                BACKLIT_DIRTY = false;
            }*/
            BACKLIT_DIRTY = false;
            //sei();
        }
    #endif
   }
}

// this code runs before the usb and keyboard is initialized
void matrix_setup(void) {
    split_keyboard_setup();

    if (!has_usb()) {
        //rgblight_init();
        keyboard_slave_loop();
    }
}
