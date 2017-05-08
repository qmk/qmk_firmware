/*
Copyright 2016 flabbergast <s3+flabbergast@sdfeu.org>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
 * LED controller code
 * WF uses IS31FL3731C matrix LED driver from ISSI
 * datasheet: http://www.issi.com/WW/pdf/31FL3731C.pdf
 */

#include "ch.h"
#include "hal.h"
#include "print.h"
#include "led.h"
#include "action_layer.h"
#include "host.h"

#include "led_controller.h"

#include "suspend.h"

#include "usb_main.h"

/* Infinity60 LED MAP
    - digits mean "row" and "col", i.e. 45 means C4-5 in the IS31 datasheet, matrix A

  11 12 13 14 15 16 17 18 21 22 23 24 25  26 27*
   28 31 32 33 34 35 36 37 38 41 42 43 44 45
   46 47 48 51 52 53 54 55 56 57 58 61    62
    63 64 65 66 67 68 71 72 73 74 75      76 77*
  78  81  82       83         84  85  86  87

*Unused in Alphabet Layout
*/

/*
  each page has 0xB4 bytes
  0 - 0x11: LED control (on/off):
    order: CA1, CB1, CA2, CB2, .... (CA - matrix A, CB - matrix B)
      CAn controls Cn-8 .. Cn-1 (LSbit)
  0x12 - 0x23: blink control (like "LED control")
  0x24 - 0xB3: PWM control: byte per LED, 0xFF max on
    order same as above (CA 1st row (8bytes), CB 1st row (8bytes), ...)
*/

/* Which LED should be used for CAPS LOCK indicator
 * The usual Caps Lock position is C4-6, so the address is
 * 0x24 + (4-1)*0x10 + (8-1) = 0x59 */
#if !defined(CAPS_LOCK_LED_ADDRESS)
#define CAPS_LOCK_LED_ADDRESS 46
#endif

#if !defined(NUM_LOCK_LED_ADDRESS)
#define NUM_LOCK_LED_ADDRESS 85
#endif

/* Which LED should breathe during sleep */
#if !defined(BREATHE_LED_ADDRESS)
#define BREATHE_LED_ADDRESS CAPS_LOCK_LED_ADDRESS
#endif

#define DEBUG_ENABLED 0

/* =================
 * ChibiOS I2C setup
 * ================= */
static const I2CConfig i2ccfg = {
  400000 // clock speed (Hz); 400kHz max for IS31
};

/* ==============
 *   variables
 * ============== */
// internal communication buffers
uint8_t tx[2] __attribute__((aligned(2)));
uint8_t rx[1] __attribute__((aligned(2)));

// buffer for sending the whole page at once (used also as a temp buffer)
uint8_t full_page[0xB4+1] = {0};

// LED mask (which LEDs are present, selected by bits)
// See page comment above, control alternates CA matrix/CB matrix
// IC60 pcb uses only CA matrix.
// Each byte is a control pin for 8 leds ordered 8-1
const uint8_t all_on_leds_mask[0x12] = {
  0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
  0x00, 0xFF, 0x00, 0xFF, 0x00, 0x7F, 0x00, 0x00, 0x00
};

// array to hold brightness pwm steps
const uint8_t pwm_levels[5] = {
    0x00, 0x16, 0x4E, 0xA1, 0xFF
};

// array to write to pwm register
uint8_t pwm_register_array[9] = {0};


/* ============================
 *   communication functions
 * ============================ */
msg_t is31_select_page(uint8_t page) {
  tx[0] = IS31_COMMANDREGISTER;
  tx[1] = page;
  return i2cMasterTransmitTimeout(&I2CD1, IS31_ADDR_DEFAULT, tx, 2, NULL, 0, US2ST(IS31_TIMEOUT));
}

msg_t is31_write_data(uint8_t page, uint8_t *buffer, uint8_t size) {
  is31_select_page(page);
  return i2cMasterTransmitTimeout(&I2CD1, IS31_ADDR_DEFAULT, buffer, size, NULL, 0, US2ST(IS31_TIMEOUT));
}

msg_t is31_write_register(uint8_t page, uint8_t reg, uint8_t data) {
  is31_select_page(page);
  tx[0] = reg;
  tx[1] = data;
  return i2cMasterTransmitTimeout(&I2CD1, IS31_ADDR_DEFAULT, tx, 2, NULL, 0, US2ST(IS31_TIMEOUT));
}

msg_t is31_read_register(uint8_t page, uint8_t reg, uint8_t *result) {
  is31_select_page(page);

  tx[0] = reg;
  return i2cMasterTransmitTimeout(&I2CD1, IS31_ADDR_DEFAULT, tx, 1, result, 1, US2ST(IS31_TIMEOUT));
}

/* ========================
 * initialise the IS31 chip
 * ======================== */
void is31_init(void) {
  // just to be sure that it's all zeroes
  __builtin_memset(full_page,0,0xB4+1);
  // zero function page, all registers (assuming full_page is all zeroes)
  is31_write_data(IS31_FUNCTIONREG, full_page, 0xD + 1);
  // disable hardware shutdown
  palSetPadMode(GPIOB, 16, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPad(GPIOB, 16);
  chThdSleepMilliseconds(10);
  // software shutdown
  is31_write_register(IS31_FUNCTIONREG, IS31_REG_SHUTDOWN, 0);
  chThdSleepMilliseconds(10);
  // software shutdown disable (i.e. turn stuff on)
  is31_write_register(IS31_FUNCTIONREG, IS31_REG_SHUTDOWN, IS31_REG_SHUTDOWN_ON);
  chThdSleepMilliseconds(10);
  // zero all LED registers on all 8 pages
  uint8_t i;
  for(i=0; i<8; i++) {
    is31_write_data(i, full_page, 0xB4 + 1);
    chThdSleepMilliseconds(1);
  }
}

/* ==================
 * LED control thread
 * ================== */
#define LED_MAILBOX_NUM_MSGS 5
static msg_t led_mailbox_queue[LED_MAILBOX_NUM_MSGS];
mailbox_t led_mailbox;
static THD_WORKING_AREA(waLEDthread, 256);
static THD_FUNCTION(LEDthread, arg) {
  (void)arg;
  chRegSetThreadName("LEDthread");

  uint8_t i;
  uint8_t control_register_word[2] = {0};//2 bytes: register address, byte to write
  uint8_t led_control_reg[0x13] = {0};//led control register start address + 0x12 bytes

  //persistent status variables
  uint8_t pwm_step_status, page_status;

  //mailbox variables
  uint8_t temp, msg_type, msg_led;
  msg_t msg;

/*  //control register variables
  uint8_t page, save_page, save_breath1, save_breath2;
  msg_t msg, retval;
*/

// initialize persistent variables
pwm_step_status = 4; //full brightness
page_status = 0; //start frame 0 (all off/on)

  while(true) {
    // wait for a message (asynchronous)
    // (messages are queued (up to LED_MAILBOX_NUM_MSGS) if they can't
    //  be processed right away)
    chMBFetch(&led_mailbox, &msg, TIME_INFINITE);
    msg_type = (msg >> 8) & 0xFF; //first byte is msg type
    msg_led = (msg) & 0xFF; //second byte is action information

    xprintf("--------------------\n");
            chThdSleepMilliseconds(10);
    xprintf("mailbox fetch\nmsg: %X\n", msg);
            chThdSleepMilliseconds(10);
    xprintf("type: %X - led: %X\n", msg_type, msg_led); 
            chThdSleepMilliseconds(10);

    switch (msg_type){
      case KEY_LIGHT:
      //TODO: lighting key led on keypress
      break;
      
      //TODO: custom page that is written using keypresses
      //TODO: BLINK_ON/OFF_LED

      case OFF_LED:      
      //on/off/toggle single led, msg_led = row/col of led
      xprintf("OFF_LED\n");
            chThdSleepMilliseconds(10);
        set_led_bit(7, control_register_word, msg_led, 0);
        is31_write_data (7, control_register_word, 0x02);
        break;

      case ON_LED:      
      xprintf("ON_LED\n");
            chThdSleepMilliseconds(10);
        set_led_bit(7, control_register_word, msg_led, 1);
        is31_write_data (7, control_register_word, 0x02);
        break;

      case TOGGLE_LED:      
      xprintf("TOGGLE_LED\n");
            chThdSleepMilliseconds(10);
        set_led_bit(7, control_register_word, msg_led, 2);
        is31_write_data (7, control_register_word, 0x02);
        break;

      case TOGGLE_ALL:
      xprintf("TOGGLE_ALL\n");
            chThdSleepMilliseconds(10);
        //msg_led = unused
        is31_read_register(0, 0x00, &temp);//if first byte is on, then toggle frame 0 off
        led_control_reg[0] = 0;
        if (temp==0 || page_status > 0) {
          xprintf("all leds on");
            chThdSleepMilliseconds(10);
          __builtin_memcpy(led_control_reg+1, all_on_leds_mask, 0x12);
        } else {
          xprintf("all leds off");
            chThdSleepMilliseconds(10);
          __builtin_memset(led_control_reg+1, 0, 0x12);
        }
        is31_write_data(0, led_control_reg, 0x13);

        if (page_status > 0) {
          is31_write_register(IS31_FUNCTIONREG, IS31_REG_PICTDISP, 0);
        }

        //maintain lock leds
        if (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) {
          set_lock_leds(NUM_LOCK_LED_ADDRESS, 1);
        }
        if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
          set_lock_leds(CAPS_LOCK_LED_ADDRESS, 1);
        }

        page_status=0;
        break;

      case TOGGLE_BACKLIGHT:
        //msg_led = on/off
      xprintf("TOGGLE_BACKLIGHT\n");
            chThdSleepMilliseconds(10);

        //populate the 9 byte rows to be written to each pin, first byte is register (pin) address
        if (msg_led == 1) {
          __builtin_memset(pwm_register_array+1, pwm_levels[pwm_step_status], 8);
        } else {
          __builtin_memset(pwm_register_array+1, 0, 8);
        }

        for(i=0; i<8; i++) {
        //first byte is register address, every 0x10 9 bytes is A-register pwm pins
          pwm_register_array[0] = 0x24 + (i * 0x10);
          is31_write_data(0,pwm_register_array,9);
        }
        break;

      case DISPLAY_PAGE://show single layer indicator or full map of layer
        //msg_led = page to toggle on
      xprintf("DISPLAY_PAGE\n");
            chThdSleepMilliseconds(10);
        if (page_status != msg_led) {
          is31_write_register(IS31_FUNCTIONREG, IS31_REG_PICTDISP, msg_led);
        }
        page_status = msg_led;
        break;

      case RESET_PAGE:
        //led_msg = page to reset
        led_control_reg[0] = 0;
        __builtin_memset(led_control_reg+1, 0, 0x12);
        is31_write_data(msg_led, led_control_reg, 0x13);

        //maintain lock leds
        if (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) {
          set_lock_leds(NUM_LOCK_LED_ADDRESS, 1);
        }
        if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
          set_lock_leds(CAPS_LOCK_LED_ADDRESS, 1);
        }
        break;
        
      case TOGGLE_NUM_LOCK:
        //msg_led = 0 or 1, off/on
        set_lock_leds(NUM_LOCK_LED_ADDRESS, 1);
        break;
      
      case TOGGLE_CAPS_LOCK:
        //msg_led = 0 or 1, off/on
        set_lock_leds(CAPS_LOCK_LED_ADDRESS, 1);
        break;

      //TODO: MODE_BREATH
      case MODE_BREATH:
        break;
      case STEP_BRIGHTNESS:
      xprintf("TOGGLE_BACKLIGHT\n");
            chThdSleepMilliseconds(10);
        //led_msg = step pwm up or down
      switch (msg_led) {
        case 0:
          if (pwm_step_status == 0) {
            pwm_step_status = 4;
          } else {
            pwm_step_status--;
          }
          break;
        
        case 1:
          if (pwm_step_status == 4) {
            pwm_step_status = 0;
          } else {
            pwm_step_status++;
          }
          break;
      }

      //populate 8 byte rows to write on each pin
      //first byte is register address, every 0x10 9 bytes are A-register pwm pins
      __builtin_memset(pwm_register_array+1, pwm_levels[pwm_step_status], 8);

      for(i=0; i<8; i++) {
        pwm_register_array[0] = 0x24 + (i * 0x10);
        is31_write_data(0,pwm_register_array,9);
      }
      break;

/*    case LED_MSG_SLEEP_LED_ON:
      // save current settings
        is31_read_register(IS31_FUNCTIONREG, IS31_REG_PICTDISP, &save_page);
        is31_read_register(IS31_FUNCTIONREG, IS31_REG_BREATHCTRL1, &save_breath1);
        is31_read_register(IS31_FUNCTIONREG, IS31_REG_BREATHCTRL2, &save_breath2);
        // use pages 7 and 8 for (hardware) breathing (assuming they're empty)
        is31_write_register(6, BREATHE_LED_ADDRESS, 0xFF);
        is31_write_register(7, BREATHE_LED_ADDRESS, 0x00);
        is31_write_register(IS31_FUNCTIONREG, IS31_REG_BREATHCTRL1, (6<<4)|6);
        is31_write_register(IS31_FUNCTIONREG, IS31_REG_BREATHCTRL2, IS31_REG_BREATHCTRL2_ENABLE|3);
        retval = MSG_TIMEOUT;
        temp = 6;
        while(retval == MSG_TIMEOUT) {
          // switch to the other page
          is31_write_register(IS31_FUNCTIONREG, IS31_REG_PICTDISP, temp);
          temp = (temp == 6 ? 7 : 6);
          // the times should be sufficiently long for IS31 to finish switching pages
          retval = chMBFetch(&led_mailbox, &msg, MS2ST(temp == 6 ? 4000 : 6000));
        }
        // received a message (should be a wakeup), so restore previous state
        chThdSleepMilliseconds(3000); // need to wait until the page change finishes
        // note: any other messages are queued
        is31_write_register(IS31_FUNCTIONREG, IS31_REG_BREATHCTRL1, save_breath1);
        is31_write_register(IS31_FUNCTIONREG, IS31_REG_BREATHCTRL2, save_breath2);
        is31_write_register(IS31_FUNCTIONREG, IS31_REG_PICTDISP, save_page);
        break;
      case LED_MSG_SLEEP_LED_OFF: 
        // should not get here; wakeup should be received in the branch above break;
        break;
*/  
      xprintf("--------------------\n");
            chThdSleepMilliseconds(10);
    }
#if DEBUG_ENABLED
    uint8_t j, page;
    //debugging code - print full led/blink/pwm registers on each frame
          xprintf("----layer state----: %X\n", layer_state);
      for(i=0;i<8;i++) {
          xprintf("page: %d", i);
            chThdSleepMilliseconds(2);
        for(j=0;j<0xB4;j++){
            is31_read_register(i,j,&temp);
            chThdSleepMilliseconds(2);
            xprintf("%02X, ", temp);
            if(j % 9 == 0){
            xprintf("\n");
              if(j % 18 ==0){
              xprintf("register");
              xprintf("\n");
              }
            }
            chThdSleepMilliseconds(1);
        }
            xprintf("\n");
      }
#endif
  }
}

/* ==============================
 *    led processing functions
 * ============================== */

void set_led_bit (uint8_t page, uint8_t *led_control_reg, uint8_t led_addr, uint8_t action) {
  //returns 2 bytes led control register address and byte to write

  uint8_t control_reg_addr, column_bit, column_byte, temp;
  //check for valid led address
  if (led_addr < 0 || led_addr > 90 || led_addr % 10 > 8) {
    xprintf("Invalid address: %d\n", led_addr);
    return;
  }

  //first byte is led control register address 0x00
  //msg_led tens column is pin#, ones column is bit position in 8-bit mask
  control_reg_addr = ((led_addr / 10) % 10 - 1 ) * 0x02;// A-register is every other byte
  column_bit = 1<<(led_addr % 10 - 1);

  is31_read_register(page, control_reg_addr, &temp);//maintain status of leds on this byte
  column_byte = temp;

  switch(action) {
    case 0:
      column_byte &= ~column_bit;
      break;
    case 1:
      column_byte |= column_bit;
      break;
    case 2:
      column_byte ^= column_bit;
      break;
  }

  //return word to be written in register
  led_control_reg[0] = control_reg_addr;
  led_control_reg[1] = column_byte;
}

void set_lock_leds(uint8_t led_addr, uint8_t led_action) {
  uint8_t page;
  uint8_t led_control_word[2] = {0};

  //ignore frame0 if all leds are on or if option set in led_controller.h
  //TODO: blink of all leds are on, clear blink register if not
  //is31_read_register(0, 0x00, &temp);
  //led_addr += temp == 0 ? 0 : 0x12;//send bit to blink register instead
  //start = BACKLIGHT_OFF_LOCK_LED_OFF ? 1 : 0; 

  for(page=0; page<8; page++) { 
    set_led_bit(page,led_control_word,led_addr,led_action);
    is31_write_data(page, led_control_word, 0x02);
  }
}

void write_led_page (uint8_t page, uint8_t *user_led_array, uint8_t led_count) {
  uint8_t i;
  uint8_t row, col;
  uint8_t led_control_register[0x13] = {0};//led control register start address + 0x12 bytes

  __builtin_memset(led_control_register,0,13);

  for(i=0;i<led_count;i++){
    row = ((user_led_array[i] / 10) % 10 - 1 ) * 2 + 1;// 1 byte shift for led register 0x00 address
    col = user_led_array[i] % 10 - 1;
    
    led_control_register[row] |= 1<<(col);
  }

  is31_write_data(page, led_control_register, 0x13);
}

/* =====================
 * hook into user keymap
 * ===================== */
void led_controller_init(void) {
  uint8_t i;

  /* initialise I2C */
  /* I2C pins */
  palSetPadMode(GPIOB, 0, PAL_MODE_ALTERNATIVE_2); // PTB0/I2C0/SCL
  palSetPadMode(GPIOB, 1, PAL_MODE_ALTERNATIVE_2); // PTB1/I2C0/SDA
  /* start I2C */
  i2cStart(&I2CD1, &i2ccfg);
  // try high drive (from kiibohd)
  I2CD1.i2c->C2 |= I2Cx_C2_HDRS;
  // try glitch fixing (from kiibohd)
  I2CD1.i2c->FLT = 4;

  chThdSleepMilliseconds(10);

  /* initialise IS31 chip */
  is31_init();

  //set Display Option Register so all pwm intensity is controlled from Frame 0
  is31_write_register(IS31_FUNCTIONREG, IS31_REG_DISPLAYOPT, IS31_REG_DISPLAYOPT_INTENSITY_SAME);

  /* set full pwm on Frame 1 */
  pwm_register_array[0] = 0;
  __builtin_memset(pwm_register_array+1, 0xFF, 8);
  for(i=0; i<8; i++) {
    pwm_register_array[0] = 0x24 + (i * 0x10);//first byte of 9 bytes must be register address
    is31_write_data(0, pwm_register_array, 9);
    chThdSleepMilliseconds(5);
  }

  /* enable breathing when the displayed page changes */
  // Fade-in Fade-out, time = 26ms * 2^N, N=3
  is31_write_register(IS31_FUNCTIONREG, IS31_REG_BREATHCTRL1, (3<<4)|3);
  is31_write_register(IS31_FUNCTIONREG, IS31_REG_BREATHCTRL2, IS31_REG_BREATHCTRL2_ENABLE|3);

  // clean up the lock LEDs
  set_lock_leds(NUM_LOCK_LED_ADDRESS, 0);
  set_lock_leds(CAPS_LOCK_LED_ADDRESS, 0);

  /* more time consuming LED processing should be offloaded into
   * a thread, with asynchronous messaging. */
  chMBObjectInit(&led_mailbox, led_mailbox_queue, LED_MAILBOX_NUM_MSGS);
  chThdCreateStatic(waLEDthread, sizeof(waLEDthread), LOWPRIO, LEDthread, NULL);
}

//TODO: Don't know equivalent QMK hooks for these
//
//void hook_usb_suspend_entry(void) {
//#ifdef SLEEP_LED_ENABLE
//  chSysLockFromISR();
//  chMBPostI(&led_mailbox, LED_MSG_SLEEP_LED_ON);
//  chSysUnlockFromISR();
//#endif /* SLEEP_LED_ENABLE */
//}
//
//void hook_usb_suspend_loop(void) {
//  chThdSleepMilliseconds(100);
//  /* Remote wakeup */
//  if((USB_DRIVER.status & 2) && suspend_wakeup_condition()) {
//    send_remote_wakeup(&USB_DRIVER);
//  }
//}
//
//void hook_usb_wakeup(void) {
//#ifdef SLEEP_LED_ENABLE
//  chSysLockFromISR();
//  chMBPostI(&led_mailbox, LED_MSG_SLEEP_LED_OFF);
//  chSysUnlockFromISR();
//#endif /* SLEEP_LED_ENABLE */
//}
//*/
