/*
Copyright 2016 flabbergast <s3+flabbergast@sdfeu.org>
Copyright 2017 jpetermans <tibcmhhm@gmail.com>

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
 * IS31FL3731C matrix LED driver from ISSI
 * datasheet: http://www.issi.com/WW/pdf/31FL3731C.pdf
 */

#include "ch.h"
#include "hal.h"
#include "print.h"
#include "led.h"
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

// Which LED should be used for CAPS LOCK indicator
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
  is31_write_register(IS31_FUNCTIONREG, IS31_REG_SHUTDOWN, IS31_REG_SHUTDOWN_ON);
  chThdSleepMilliseconds(10);
  // zero function page, all registers
  is31_write_data(IS31_FUNCTIONREG, full_page, 0xD + 1);
  chThdSleepMilliseconds(10);
  // software shutdown disable (i.e. turn stuff on)
  is31_write_register(IS31_FUNCTIONREG, IS31_REG_SHUTDOWN, IS31_REG_SHUTDOWN_OFF);
  chThdSleepMilliseconds(10);
  // zero all LED registers on all 8 pages
  uint8_t i;
  for(i=0; i<8; i++) {
    is31_write_data(i, full_page, 0xB4 + 1);
    chThdSleepMilliseconds(5);
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
  uint8_t pwm_step_status, page_status, capslock_status, numlock_status;

  //mailbox variables
  uint8_t temp, msg_type;
  uint8_t msg_args[3];
  msg_t msg;

  // initialize persistent variables
  pwm_step_status = 4; //full brightness
  page_status = 0; //start frame 0 (all off/on)
  numlock_status = (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ? 1 : 0;
  capslock_status = (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ? 1 : 0;

  while(true) {
    // wait for a message (asynchronous)
    // (messages are queued (up to LED_MAILBOX_NUM_MSGS) if they can't
    //  be processed right away
    chMBFetch(&led_mailbox, &msg, TIME_INFINITE);
    msg_type = msg & 0xFF; //first byte is action information
    msg_args[0] = (msg >> 8) & 0xFF;
    msg_args[1] = (msg >> 16) & 0XFF;
    msg_args[2] = (msg >> 24) & 0xFF;


    switch (msg_type){
      case SET_FULL_ROW:
      //write full byte to pin address, msg_args[1] = pin #, msg_args[0] = 8 bits to write
      //writes only to currently displayed page
        write_led_byte(page_status, msg_args[1], msg_args[0]);
        break;

      case OFF_LED:
      //on/off/toggle single led, msg_args[0] = row/col of led, msg_args[1] = page
        set_led_bit(msg_args[1], control_register_word, msg_args[0], 0);
        break;
      case ON_LED:
        set_led_bit(msg_args[1], control_register_word, msg_args[0], 1);
        break;
      case TOGGLE_LED:
        set_led_bit(msg_args[1], control_register_word, msg_args[0], 2);
        break;

      case BLINK_OFF_LED:
      //on/off/toggle single led, msg_args[0] = row/col of led
        set_led_bit(msg_args[1], control_register_word, msg_args[0], 4);
        break;
      case BLINK_ON_LED:
        set_led_bit(msg_args[1], control_register_word, msg_args[0], 5);
        break;
      case BLINK_TOGGLE_LED:
        set_led_bit(msg_args[1], control_register_word, msg_args[0], 6);
        break;

      case TOGGLE_ALL:
      //turn on/off all leds, msg_args = unused
        is31_write_register(IS31_FUNCTIONREG, IS31_REG_SHUTDOWN, IS31_REG_SHUTDOWN_ON);
        chThdSleepMilliseconds(5);
        is31_read_register(0, 0x00, &temp);
        is31_write_register(IS31_FUNCTIONREG, IS31_REG_SHUTDOWN, IS31_REG_SHUTDOWN_OFF);

        led_control_reg[0] = 0;

        //toggle led mask based on current state (temp)
        if (temp==0 || page_status > 0) {
          __builtin_memcpy(led_control_reg+1, all_on_leds_mask, 0x12);
        } else {
          __builtin_memset(led_control_reg+1, 0, 0x12);
        }
        is31_write_data(0, led_control_reg, 0x13);

        if (page_status > 0) {
          is31_write_register(IS31_FUNCTIONREG, IS31_REG_PICTDISP, 0);

          page_status=0;

          //maintain lock leds, reset to off and force recheck to blink of all leds toggled on
          numlock_status = 0;
          capslock_status = 0;
          led_set(host_keyboard_leds());
        }
        break;

      case TOGGLE_BACKLIGHT:
        //msg_args[0] = on/off

        //populate 9 byte rows to be written to each pin, first byte is register (pin) address
        if (msg_args[0] == 1) {
          __builtin_memset(pwm_register_array+1, pwm_levels[pwm_step_status], 8);
        } else {
          __builtin_memset(pwm_register_array+1, 0, 8);
        }

        for(i=0; i<8; i++) {
        //first byte is register address, every 0x10 9 bytes is A-matrix pwm pins
          pwm_register_array[0] = 0x24 + (i * 0x10);
          is31_write_data(0,pwm_register_array,9);
        }
        break;

      case DISPLAY_PAGE:
      //msg_args[0] = page to toggle on
        if (page_status != msg_args[0]) {
          is31_write_register(IS31_FUNCTIONREG, IS31_REG_PICTDISP, msg_args[0]);
          page_status = msg_args[0];

          //maintain lock leds, reset to off and force recheck for new page
          numlock_status = 0;
          capslock_status = 0;
          led_set(host_keyboard_leds());
        }
        break;

      case RESET_PAGE:
      //led_args[0] = page to reset
        led_control_reg[0] = 0;
        __builtin_memset(led_control_reg+1, 0, 0x12);
        is31_write_data(msg_args[0], led_control_reg, 0x13);

        //repeat for blink register
        led_control_reg[0] = 0x12;
        is31_write_data(msg_args[0], led_control_reg, 0x13);
        break;

      case TOGGLE_NUM_LOCK:
      //msg_args[0] = 0 or 1, off/on
        if (numlock_status != msg_args[0]) {
          set_lock_leds(NUM_LOCK_LED_ADDRESS, msg_args[0], page_status);
          numlock_status = msg_args[0];
        }
        break;
      case TOGGLE_CAPS_LOCK:
      //msg_args[0] = 0 or 1, off/on
        if (capslock_status != msg_args[0]) {
          set_lock_leds(CAPS_LOCK_LED_ADDRESS, msg_args[0], page_status);
          capslock_status = msg_args[0];
        }
        break;

      case STEP_BRIGHTNESS:
      //led_args[0] = step up (1) or down (0)
        switch (msg_args[0]) {
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

        //populate 8 byte arrays to write on each pin
        //first byte is register address, every 0x10 9 bytes are A-matrix pwm pins
        __builtin_memset(pwm_register_array+1, pwm_levels[pwm_step_status], 8);

        for(i=0; i<8; i++) {
          pwm_register_array[0] = 0x24 + (i * 0x10);
          is31_write_data(0,pwm_register_array,9);
        }
        break;
    }
  }
}

/* ==============================
 *    led processing functions
 * ============================== */

void set_led_bit (uint8_t page, uint8_t *led_control_word, uint8_t led_addr, uint8_t action) {
  //returns 2 bytes: led control register address and byte to write
  //action: 0 - off, 1 - on, 2 - toggle, 4 - blink on, 5 - blink off, 6 - toggle blink

  uint8_t control_reg_addr, column_bit, column_byte, temp, blink_bit;

  //check for valid led address
  if (led_addr < 0 || led_addr > 87 || led_addr % 10 > 8) {
    return;
  }

  blink_bit = action>>2;//check for blink bit
  action &= ~(1<<2); //strip blink bit

  //led_addr tens column is pin#, ones column is bit position in 8-bit mask
  control_reg_addr = ((led_addr / 10) % 10 - 1 ) * 0x02;// A-matrix is every other byte
  control_reg_addr += blink_bit == 1 ? 0x12 : 0x00;//if blink_bit, shift 12 bytes to blink register

  is31_write_register(IS31_FUNCTIONREG, IS31_REG_SHUTDOWN, IS31_REG_SHUTDOWN_ON);
  chThdSleepMilliseconds(5);
  is31_read_register(page, control_reg_addr, &temp);//maintain status of leds on this byte
  is31_write_register(IS31_FUNCTIONREG, IS31_REG_SHUTDOWN, IS31_REG_SHUTDOWN_OFF);

  column_bit = 1<<(led_addr % 10 - 1);
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
  led_control_word[0] = control_reg_addr;
  led_control_word[1] = column_byte;
  is31_write_data (page, led_control_word, 0x02);
}

void write_led_byte (uint8_t page, uint8_t row, uint8_t led_byte) {
  uint8_t led_control_word[2] = {0};//register address and on/off byte

  led_control_word[0] = (row - 1 ) * 0x02;// A-matrix is every other byte
  led_control_word[1] = led_byte;
  is31_write_data(page, led_control_word, 0x02);
}

void write_led_page (uint8_t page, uint8_t *user_led_array, uint8_t led_count) {
  uint8_t i;
  uint8_t pin, col;
  uint8_t led_control_register[0x13] = {0};

  __builtin_memset(led_control_register,0,13);

  for(i=0;i<led_count;i++){
    //shift pin by 1 for led register 0x00 address
    pin = ((user_led_array[i] / 10) % 10 - 1 ) * 2 + 1;
    col = user_led_array[i] % 10 - 1;
    led_control_register[pin] |= 1<<(col);
  }

  is31_write_data(page, led_control_register, 0x13);
}

void set_lock_leds(uint8_t led_addr, uint8_t led_action, uint8_t page) {
  uint8_t temp;
  uint8_t led_control_word[2] = {0};

  //blink if all leds are on
  if (page == 0) {
    is31_write_register(IS31_FUNCTIONREG, IS31_REG_SHUTDOWN, IS31_REG_SHUTDOWN_ON);
    chThdSleepMilliseconds(5);
    is31_read_register(0, 0x00, &temp);
    is31_write_register(IS31_FUNCTIONREG, IS31_REG_SHUTDOWN, IS31_REG_SHUTDOWN_OFF);

    if (temp == 0xFF) {
      led_action |= (1<<2); //set blink bit
    }
  }

  set_led_bit(page,led_control_word,led_addr,led_action);
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

  //set Display Option Register so all pwm intensity is controlled from page 0
  //enable blink and set blink period to 0.27s x rate
  is31_write_register(IS31_FUNCTIONREG, IS31_REG_DISPLAYOPT, IS31_REG_DISPLAYOPT_INTENSITY_SAME + IS31_REG_DISPLAYOPT_BLINK_ENABLE + 4);

  /* set full pwm on page 1 */
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

  /* more time consuming LED processing should be offloaded into
   * a thread, with asynchronous messaging. */
  chMBObjectInit(&led_mailbox, led_mailbox_queue, LED_MAILBOX_NUM_MSGS);
  chThdCreateStatic(waLEDthread, sizeof(waLEDthread), LOWPRIO, LEDthread, NULL);
}
