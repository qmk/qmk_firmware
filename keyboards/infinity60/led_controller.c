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

#include "led_controller.h"

#include "hook.h"
#include "suspend.h"

#include "usb_main.h"

/* WF LED MAP
    - digits mean "row" and "col", i.e. 45 means C4-5 in the IS31 datasheet, matrix A

  11 12 13 14 15 16 17 18 21 22 23 24 25 26 27  28
   31 32 33 34 35 36 37 38 41 42 43 44 45  46   47
   48 51 52 53 54 55 56 57 58 61 62 63 64   65  66
    67 68 71 72 73 74 75 76 77 78 81 82  83  84 85
  86  87  88       91        92  93 (94)  95 96 97
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
 * The usual Caps Lock position is C4-8, so the address is
 * 0x24 + (4-1)*0x10 + (8-1) = 0x5B */
#if !defined(CAPS_LOCK_LED_ADDRESS)
#define CAPS_LOCK_LED_ADDRESS 0x5B
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
const uint8_t is31_wf_leds_mask[0x12] = {
  0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF,
  0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0x7F, 0x00
};

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

msg_t is31_read_register(uint8_t b, uint8_t reg, uint8_t *result) {
  is31_select_page(b);

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

  uint8_t temp;
  uint8_t save_page, save_breath1, save_breath2;
  msg_t msg, retval;

  while(true) {
    // wait for a message (asynchronous)
    // (messages are queued (up to LED_MAILBOX_NUM_MSGS) if they can't
    //  be processed right away)
    chMBFetch(&led_mailbox, &msg, TIME_INFINITE);

    // process 'msg' here
    switch(msg) {
      case LED_MSG_CAPS_ON:
        // turn caps on on pages 1 and 2
        is31_write_register(0, CAPS_LOCK_LED_ADDRESS, 0xFF);
        is31_write_register(1, CAPS_LOCK_LED_ADDRESS, 0xFF);
        is31_write_register(2, CAPS_LOCK_LED_ADDRESS, 0xFF);
        break;
      case LED_MSG_CAPS_OFF:
        // turn caps off on pages 1 and 2
        is31_write_register(0, CAPS_LOCK_LED_ADDRESS, 0);
        is31_write_register(1, CAPS_LOCK_LED_ADDRESS, 0);
        is31_write_register(2, CAPS_LOCK_LED_ADDRESS, 0);
        break;
      case LED_MSG_SLEEP_LED_ON:
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
        // should not get here; wakeup should be received in the branch above
        break;
      case LED_MSG_ALL_TOGGLE:
        // read current page into 'temp'
        is31_read_register(IS31_FUNCTIONREG, IS31_REG_PICTDISP, &temp);
        chThdSleepMilliseconds(1);
        // switch to 'the other' page
        if(temp==2) {
          is31_write_register(IS31_FUNCTIONREG, IS31_REG_PICTDISP, 0);
        } else {
          is31_write_register(IS31_FUNCTIONREG, IS31_REG_PICTDISP, 2);
        }
        break;
      case LED_MSG_GAME_TOGGLE:
        // read current page into 'temp'
        is31_read_register(IS31_FUNCTIONREG, IS31_REG_PICTDISP, &temp);
        chThdSleepMilliseconds(1);
        // switch to 'the other' page
        if(temp==1) {
          is31_write_register(IS31_FUNCTIONREG, IS31_REG_PICTDISP, 0);
        } else {
          is31_write_register(IS31_FUNCTIONREG, IS31_REG_PICTDISP, 1);
        }
        break;
    }
  }
}

/* LED game mode */
const uint8_t led_game[83] = {
  0x24,
  0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x34,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x44,
  0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x54,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x64,
  0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x74,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x84,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x94,
  0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00,
  0xA4,
  0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00,
};

/* ALL LEDs */
const uint8_t led_all[83] = {
  0x24,
  0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
  0x34,
  0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
  0x44,
  0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
  0x54,
  0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
  0x64,
  0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
  0x74,
  0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
  0x84,
  0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
  0x94,
  0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
  0xA4,
  0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0,
};

/* =============
 * hook into TMK
 * ============= */
void hook_early_init(void) {
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

  /* enable WF LEDs on all pages */
  full_page[0] = 0;
  __builtin_memcpy(full_page+1, is31_wf_leds_mask, 0x12);
  for(i=0; i<8; i++) {
    is31_write_data(i, full_page, 1+0x12);
  }

  /* enable breathing when the displayed page changes */
  // Fade-in Fade-out, time = 26ms * 2^N, N=3
  is31_write_register(IS31_FUNCTIONREG, IS31_REG_BREATHCTRL1, (3<<4)|3);
  is31_write_register(IS31_FUNCTIONREG, IS31_REG_BREATHCTRL2, IS31_REG_BREATHCTRL2_ENABLE|3);

  /* Write pages */
  for(i=0; i<9; i++) {
    is31_write_data(1,(uint8_t *)(led_game+(9*i)),9);
    chThdSleepMilliseconds(5);
    is31_write_data(2,(uint8_t *)(led_all+(9*i)),9);
    chThdSleepMilliseconds(5);
  }

  // clean up the capslock LED
  is31_write_register(1, CAPS_LOCK_LED_ADDRESS, 0);
  is31_write_register(2, CAPS_LOCK_LED_ADDRESS, 0);

  /* more time consuming LED processing should be offloaded into
   * a thread, with asynchronous messaging. */
  chMBObjectInit(&led_mailbox, led_mailbox_queue, LED_MAILBOX_NUM_MSGS);
  chThdCreateStatic(waLEDthread, sizeof(waLEDthread), LOWPRIO, LEDthread, NULL);
}

void hook_usb_suspend_entry(void) {
#ifdef SLEEP_LED_ENABLE
  chSysLockFromISR();
  chMBPostI(&led_mailbox, LED_MSG_SLEEP_LED_ON);
  chSysUnlockFromISR();
#endif /* SLEEP_LED_ENABLE */
}

void hook_usb_suspend_loop(void) {
  chThdSleepMilliseconds(100);
  /* Remote wakeup */
  if((USB_DRIVER.status & 2) && suspend_wakeup_condition()) {
    send_remote_wakeup(&USB_DRIVER);
  }
}

void hook_usb_wakeup(void) {
#ifdef SLEEP_LED_ENABLE
  chSysLockFromISR();
  chMBPostI(&led_mailbox, LED_MSG_SLEEP_LED_OFF);
  chSysUnlockFromISR();
#endif /* SLEEP_LED_ENABLE */
}
