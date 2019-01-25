#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include "split_util.h"
#include "matrix.h"
#include "keyboard.h"

#ifdef USE_MATRIX_I2C
#  include "i2c.h"
#else
#  include "serial.h"
#endif

volatile bool isLeftHand = true;

static void setup_handedness(void) {
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
}

static void keyboard_master_setup(void) {

#ifdef USE_MATRIX_I2C
    i2c_master_init();
#else
    serial_master_init();
#endif
}

static void keyboard_slave_setup(void) {

#ifdef USE_MATRIX_I2C
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

// this code runs before the usb and keyboard is initialized
void matrix_setup(void) {
    split_keyboard_setup();
}
