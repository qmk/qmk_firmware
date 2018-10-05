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
#include "split_flags.h"

#ifdef RGBLIGHT_ENABLE
#   include "rgblight.h"
#endif
#ifdef BACKLIGHT_ENABLE
#   include "backlight.h"
#endif

#ifdef SPLIT_HAND_PIN
#   include "pincontrol.h"
#endif

#if defined(USE_I2C) || defined(EH)
#  include "i2c.h"
#else
#  include "serial.h"
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
#if defined(USE_I2C) || defined(EH)
  i2c_master_init();
  #ifdef SSD1306OLED
    matrix_master_OLED_init ();
  #endif
#else
  serial_master_init();
#endif

    // For master the Backlight info needs to be sent on startup
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
   
   //Init RGB
   #ifdef RGBLIGHT_ENABLE
      rgblight_init();
   #endif

   while (1) {
    // Matrix Slave Scan
    matrix_slave_scan();
    
    // Read Backlight Info
    #ifdef BACKLIGHT_ENABLE
        #ifdef USE_I2C
            if (BACKLIT_DIRTY) {
                backlight_set(i2c_slave_buffer[I2C_BACKLIT_START]);
                BACKLIT_DIRTY = false;
            }
        #else // USE_SERIAL
            backlight_set(serial_master_buffer[SERIAL_BACKLIT_START]);
        #endif
    #endif
    // Read RGB Info
    #ifdef RGBLIGHT_ENABLE
        #ifdef USE_I2C
            if (RGB_DIRTY) {
                // Disable interupts (RGB data is big)
                cli();
                // Create new DWORD for RGB data
                uint32_t dword; 
                
                // Fill the new DWORD with the data that was sent over
                uint8_t *dword_dat = (uint8_t *)(&dword);
                for (int i = 0; i < 4; i++) {
                    dword_dat[i] = i2c_slave_buffer[I2C_RGB_START+i];
                }
                
                // Update the RGB now with the new data and set RGB_DIRTY to false
                rgblight_update_dword(dword);
                RGB_DIRTY = false;
                // Re-enable interupts now that RGB is set
                sei();
            }
        #else // USE_SERIAL
            // Add serial implementation for RGB here
        #endif
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
