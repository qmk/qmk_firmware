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


#if defined(USE_I2C) || defined(EH)
#  include "i2c.h"
#else
#  error "serial not supported"
#endif

volatile bool isLeftHand = true;

volatile uint8_t setTries = 0;

static void setup_handedness(void) {
  #ifdef SPLIT_HAND_PIN
    // Test pin SPLIT_HAND_PIN for High/Low, if low it's right hand
    pinMode(SPLIT_HAND_PIN, PinDirectionInput);
    isLeftHand = digitalRead(SPLIT_HAND_PIN);
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
  i2c_master_init();  
}

static void keyboard_slave_setup(void) {
  timer_init();
  i2c_slave_init(SLAVE_I2C_ADDRESS);
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
    // Matrix Slave Scan
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
