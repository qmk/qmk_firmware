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
#define CAPS_LOCK_LED_ADDRESS 0x46
#endif

#if !defined(NUM_LOCK_LED_ADDRESS)
#define NUM_LOCK_LED_ADDRESS 0x85
#endif

/* Which LED should breathe during sleep */
#if !defined(BREATHE_LED_ADDRESS)
#define BREATHE_LED_ADDRESS CAPS_LOCK_LED_ADDRESS
#endif

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
const uint8_t is31_ic60_leds_mask[0x12] = {
  0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
  0x00, 0xFF, 0x00, 0xFF, 0x00, 0x7F, 0x00, 0x00, 0x00
};

// array to hold brightness pwm steps
const uint8_t pwm_levels[5] = {
    0x00, 0x16, 0x4E, 0xA1, 0xFF
};

// array to write to pwm register
uint8_t pwm_reg_array[9] = {0};


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
    xprintf("page display: %X\n", page);
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
  // TODO: This already done above, remove?
  // zero function page, all registers
  is31_write_data(IS31_FUNCTIONREG, full_page, 0xD + 1);
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

  uint8_t i, page;

  //persistent status variables
  uint8_t backlight_status, lock_status, led_step, active_layer;
  uint8_t led_control_reg[0x13] = {0};//led control register start address + 0x12 bytes

  //mailbox variables
  uint8_t temp, msg_type, msg_led;
  msg_t msg;

/*  //control register variables
  uint8_t page, save_page, save_breath1, save_breath2;
  msg_t msg, retval;
*/

// initialize persistent variables
backlight_status = 0;
lock_status = 0;//TODO: does keyboard remember locks?
led_step = 4; //full brightness
active_layer = 0;

  while(true) {
    // wait for a message (asynchronous)
    // (messages are queued (up to LED_MAILBOX_NUM_MSGS) if they can't
    //  be processed right away)
    chMBFetch(&led_mailbox, &msg, TIME_INFINITE);
    msg_type = (msg >> 8) & 0xFF; //first byte is msg type
    msg_led = (msg) & 0xFF; //second byte is action information

    xprintf("--------------------\n");
    xprintf("mailbox fetch\nmsg: %X\n", msg);
    xprintf("type: %X - led: %X\n", msg_type, msg_led); //test if msg_type is 1 or 2 bytes after mask
  switch (msg_type){
    case KEY_LIGHT:
    //TODO: lighting key led on keypress
    break;
    
    case TOGGLE_LED:      
      //TODO: toggle existing indicator off, or let user do this, but write frame 7 for every led change
      //turn on single led, msg_led = row/col of led
      set_led_bit(led_control_reg, msg_led, 1);

      is31_write_data (7, led_control_reg, 0x12+1);
      is31_write_register(IS31_FUNCTIONREG, IS31_REG_PICTDISP, 7);
      active_layer = 7;
      is31_read_register(IS31_FUNCTIONREG, IS31_REG_PICTDISP, &temp);
    xprintf("page display: %X\n", temp);
      break;

    case TOGGLE_ALL:
    xprintf("TOGGLE_ALL\n");
      //msg_led = unused, TODO: consider using msg_led to toggle layer display
      is31_read_register(IS31_FUNCTIONREG, IS31_REG_PICTDISP, &temp);

    xprintf("temp: %X\n", temp);
      //if LED_ALL is on then toggle off, any other layer, turn on LED_ALL
      if(temp == 1) {
    xprintf("page display true: %X\n", temp);
        is31_write_register(IS31_FUNCTIONREG, IS31_REG_PICTDISP, 0);
      } else {
    xprintf("page display false: %X\n", temp);
        is31_write_register(IS31_FUNCTIONREG, IS31_REG_PICTDISP, 1);
      }
      is31_read_register(IS31_FUNCTIONREG, IS31_REG_PICTDISP, &temp);
    xprintf("page display: %X\n", temp);
      break;

    case TOGGLE_BACKLIGHT:
      //msg_led = unused
      backlight_status ^= 1;
      is31_read_register(IS31_FUNCTIONREG, IS31_REG_PICTDISP, &temp);
      active_layer = temp;

      page = backlight_status == 0 ? 0 : active_layer;
      is31_write_register(IS31_FUNCTIONREG, IS31_REG_PICTDISP, page);
      break;

    case TOGGLE_LAYER_LEDS://show layer indicator or full map of layer keys.
      //TODO: change so user can flag which they want, indiv or full map in fn_actions
      //msg_led = layer to toggle on
      is31_read_register(IS31_FUNCTIONREG, IS31_REG_PICTDISP, &temp);

      if(temp == msg_led) {
        is31_write_register(IS31_FUNCTIONREG, IS31_REG_PICTDISP, 7);
        active_layer = 7;
      } else {
        is31_write_register(IS31_FUNCTIONREG, IS31_REG_PICTDISP, msg_led);
        active_layer = msg_led;
      }
      break;
      
    case TOGGLE_LOCK_LED:
      //msg_led = 0-3 for lock flags
      lock_status ^= msg_led; //TODO: confirm toggling works and doesn't get out of sync
      set_lock_leds(led_control_reg, lock_status);
      break;
    
    case MODE_BREATH:
      break;
    case STEP_BRIGHTNESS:
      //pwm_levels[] bounds checking, loop through array
      //TODO: find a cleaner way to walk through this logic
      if (msg_led == 0) {
          if (led_step == 0) {
              led_step = 4;
          } else {
              led_step--;
          }
      } else {
          if (led_step == 4) {
              led_step = 0;
          } else {
              led_step++;
          }
      }

      //TODO: this seems a messy way to populate the pwm register
      //populate the 9 byte rows to be written to each pin, first byte is register (pin) address
      for(i=1; i<9; i++) {
        pwm_reg_array[i]=pwm_levels[led_step]; 
      }
      for(i=0; i<8; i++) {
        pwm_reg_array[0] = 0x24 + (i * 0x10);//first byte of 9 bytes must be register address
        is31_write_data(0, pwm_reg_array, 9);
        chThdSleepMilliseconds(5);
      }
      break;

/*      case LED_MSG_SLEEP_LED_ON:
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
      default:
        //TODO: individual led state unchanged if page arrays are selected in code above
        //avoidable if full pages are written on the fly
        //or use pg8 for individual leds, have pointer to currently on led address for toggling
        if (msg == 0x59 || msg == 0x84) {
          //toggle lock keys on all layers
          for (i=0,i<8,i++) {
            is31_read_register(0, msg, &temp);
            pwm = (temp > 0x00 ? 0x00 : 0xFF);
            is31_write_register(i,msg,pwm);
          }

        } else if(msg >= 0x24) { 
          xprintf("Power pre-read\ntemp: %X - msg: %X - pwm: %X\n", temp, msg, pwm);
          is31_read_register(7, msg, &temp);
          xprintf("Post-read\ntemp: %X - msg: %X - pwm: %X\n", temp, msg, pwm);
          if (msg == active_led) {
            //toggle led power
            pwm = (temp > 0x00 ? 0x00 : 0xFF);

            //Use 8th led page for individual led indicators
            is31_write_register(7, msg, pwm);
          } else {
            is31_write_register(7, active_led, 0x00);
            is31_write_register(7, msg, 0xFF);
          }
          xprintf("Power post-change\ntemp: %X - msg: %X - pwm: %X\n", temp, msg, pwm);
          is31_write_register(IS31_FUNCTIONREG, IS31_REG_PICTDISP, 7);
          }
          break;
*/
    }
    xprintf("--------------------\n");
  }
}


/* ========================
 *    led bit processing
 * ======================== */
void set_led_bit (uint8_t *led_control_reg, uint8_t msg_led, uint8_t toggle_on) {
  uint8_t row_byte, column_bit;
  //msg_led tens column is pin#, A-control register is every other 8 bits
  //ones column is bit position in 8-bit mask
  //control register will be one bit shifted into position along register's full 0x12 bytes
  ////first byte is register address 0x00
  row_byte = ((msg_led / 10) % 10 - 1 ) * 2 + 1;
  column_bit = 1<<(msg_led % 10 - 1);

  if (toggle_on) {
    led_control_reg[row_byte] |= 1<<(column_bit);
  } else {
    led_control_reg[row_byte] &= ~1<<(column_bit);
  }
}

void set_lock_leds(uint8_t *led_control_reg, uint8_t lock_status) {
  uint8_t i;

  switch (lock_status) {
    case 1:
      set_led_bit(led_control_reg, CAPS_LOCK_LED_ADDRESS, 1);//TODO: define lock addresses by matrix#, and loop for all frames
      set_led_bit(led_control_reg, NUM_LOCK_LED_ADDRESS, 0);
      break;
    case 2:
      set_led_bit(led_control_reg, CAPS_LOCK_LED_ADDRESS, 0);
      set_led_bit(led_control_reg, NUM_LOCK_LED_ADDRESS, 1);
      break;
    case 3:
      set_led_bit(led_control_reg, NUM_LOCK_LED_ADDRESS, 1);
      set_led_bit(led_control_reg, CAPS_LOCK_LED_ADDRESS, 1);
      break;
  }

  for(i=1; i<8; i++) { //keep LED_OFF layer all off, including locks
    is31_write_data (i, led_control_reg, 0x12+1);
    chThdSleepMilliseconds(5);
  }
}

void write_led_page (uint8_t page, const uint8_t *led_array, uint8_t led_count) {
//TODO: init function that accepts array of led addresses and sets them by row
  uint8_t i;
  uint8_t row, col;
  uint8_t temp_control_reg[0x13] = {0};//led control register start address + 0x12 bytes
    xprintf("-------------\n");
    xprintf("write page %X\n", page);

  for(i=0;i<led_count;i++){
    row = ((led_array[i] / 10) % 10 - 1 ) * 2 + 1;//includes 1 byte shift for 0x00 address
    col = 1<<(led_array[i] % 10 - 1);
    
    temp_control_reg[row] |= 1<<(col);
  }

  is31_write_data(page, temp_control_reg, 0x13);
    xprintf("-------------\n");
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

  /* enable LEDs on all pages */
  full_page[0] = 0;
  __builtin_memcpy(full_page+1, is31_ic60_leds_mask, 0x12);
  for(i=0; i<8; i++) {
    is31_write_data(i, full_page, 1+0x12);
  }

  //set Display Option Register so all pwm intensity is controlled from Frame 1
  is31_write_register(IS31_FUNCTIONREG, IS31_REG_DISPLAYOPT, IS31_REG_DISPLAYOPT_INTENSITY_SAME);

  /* enable breathing when the displayed page changes */
  // Fade-in Fade-out, time = 26ms * 2^N, N=3
  is31_write_register(IS31_FUNCTIONREG, IS31_REG_BREATHCTRL1, (3<<4)|3);
  is31_write_register(IS31_FUNCTIONREG, IS31_REG_BREATHCTRL2, IS31_REG_BREATHCTRL2_ENABLE|3);

  // clean up the lock LEDs
  //TODO: adjust for new addressing and additional frames
  //is31_write_register(1, CAPS_LOCK_LED_ADDRESS, 0);
  //is31_write_register(2, CAPS_LOCK_LED_ADDRESS, 0);

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
