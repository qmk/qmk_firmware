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

#ifdef USE_I2C
#  include "i2c.h"
#else
#  include "serial.h"
#endif

volatile bool isLeftHand = true;

static void setup_handedness(void) {
  // Test D2 pin for handedness, if D2 is grounded, it's the right hand
  pinMode(D2, PinDirectionInput);
  isLeftHand = digitalRead(D2);
}

static void keyboard_master_setup(void) {
#ifdef USE_I2C
    i2c_master_init();
#ifdef SSD1306OLED
    matrix_master_OLED_init();
#endif
#else
    serial_master_init();
#endif
}

static void keyboard_slave_setup(void) {
  timer_init();
#ifdef USE_I2C
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
   }
}

// this code runs before the usb and keyboard is initialized
void matrix_setup(void) {
    split_keyboard_setup();

    if (!has_usb()) {
        keyboard_slave_loop();
    }
}
