#include "satisfaction75.h"
#include "print.h"
#include "debug.h"
#include "micro_oled.h"
// #include "ssd1306.h"

// // #include "action_layer.h"
// // #include "matrix.h"
// static const I2CConfig i2ccfg = { // I2CCLK=48MHz, SCL=~100kHz
// #if 0 // 100kHz @ 48MHz
//   STM32_TIMINGR_PRESC(0x0B)  |
//   STM32_TIMINGR_SCLDEL(0x04) | STM32_TIMINGR_SDADEL(0x02) |
//   STM32_TIMINGR_SCLH(0x0F)   | STM32_TIMINGR_SCLL(0x13),
// #else // 400kHz @ 48Mhz
//   STM32_TIMINGR_PRESC(0x05)  |
//   STM32_TIMINGR_SCLDEL(0x03) | STM32_TIMINGR_SDADEL(0x03) |
//   STM32_TIMINGR_SCLH(0x03)   | STM32_TIMINGR_SCLL(0x09),
// #endif
//   0,
//   0
// };

// static const SSD1306Config ssd1306cfg = {
//   &I2CD1,
//   &i2ccfg,
//   SSD1306_SAD_0X78,
// };

// static SSD1306Driver SSD1306D1;

// static void __attribute__((unused)) delayUs(uint32_t val) {
//   (void)val;
// }

// static void __attribute__((unused)) delayMs(uint32_t val) {
//   chThdSleepMilliseconds(val);
// }

// static THD_WORKING_AREA(waOledDisplay, 512);
// static __attribute__((noreturn)) THD_FUNCTION(OledDisplay, arg) {
//   (void)arg;

//   chRegSetThreadName("OledDisplay");

//   ssd1306ObjectInit(&SSD1306D1);
//   ssd1306Start(&SSD1306D1, &ssd1306cfg);

//   ssd1306FillScreen(&SSD1306D1, 0x00);

//   while (TRUE) {
// 	ssd1306GotoXy(&SSD1306D1, 0, 32);
// 	ssd1306Puts(&SSD1306D1, "Hello, world!", &ssd1306_font_7x10, SSD1306_COLOR_WHITE);

// 	ssd1306UpdateScreen(&SSD1306D1);

//     chThdSleepMilliseconds(30);
//   }

//   ssd1306Stop(&SSD1306D1);
// }

void matrix_init_user(void){
    debug_enable = true;
    debug_keyboard = true;
    // chThdCreateStatic(waOledDisplay, sizeof(waOledDisplay), NORMALPRIO, OledDisplay, NULL);
}

void matrix_scan_user(void){
  // xprintf("lolololololol\n");
  // send_buffer();

 	printf("Scanning I2C bus:\r\n");
 	uint8_t i;
 	for (i=1; i<128; i++)
 	{
 	  /*
 	   * the HAL wants a left aligned i2c address
 	   * &hi2c1 is the handle
 	   * (uint16_t)(i<<1) is the i2c address left aligned
 	   * retries 2
 	   * timeout 2
 	   */
     uint8_t arr[] = {1,2,3,4};
     printf("Addr: %d\n", i);
     i2c_transmit(i, arr, 4, 100);
 	}
}



// #ifdef QWIIC_MICRO_OLED_ENABLE
// #include "qwiic.h"


// /* screen off after this many milliseconds */
// #include "timer.h"
// #define ScreenOffInterval 60000 /* milliseconds */
// static uint16_t last_flush;

// volatile uint8_t led_numlock = false;
// volatile uint8_t  led_capslock = false;
// volatile uint8_t  led_scrolllock = false;

// static uint8_t layer;
// static bool queue_for_send = false;
// static uint8_t encoder_value = 32;

// __attribute__ ((weak))
// void draw_ui(void) {
//   clear_buffer();
//   last_flush = timer_read();
//   send_command(DISPLAYON);

// /* Layer indicator is 41 x 10 pixels */
// #define LAYER_INDICATOR_X 0
// #define LAYER_INDICATOR_Y 0

//   draw_string(LAYER_INDICATOR_X + 1, LAYER_INDICATOR_Y + 2, "LAYER", PIXEL_ON, NORM, 0);
//   draw_rect_filled_soft(LAYER_INDICATOR_X + 32, LAYER_INDICATOR_Y + 1, 9, 9, PIXEL_ON, NORM);
//   draw_char(LAYER_INDICATOR_X + 34, LAYER_INDICATOR_Y + 2, layer + 0x30, PIXEL_ON, XOR, 0);

// /* Matrix display is 19 x 9 pixels */
// #define MATRIX_DISPLAY_X 0
// #define MATRIX_DISPLAY_Y 18

//   for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
//     for (uint8_t y = 0; y < MATRIX_COLS; y++) {
//       draw_pixel(MATRIX_DISPLAY_X + y + 2, MATRIX_DISPLAY_Y + x + 2,(matrix_get_row(x) & (1 << y)) > 0, NORM);
//     }
//   }
//   draw_rect_soft(MATRIX_DISPLAY_X, MATRIX_DISPLAY_Y, 19, 9, PIXEL_ON, NORM);
//   /* hadron oled location on thumbnail */
//   draw_rect_filled_soft(MATRIX_DISPLAY_X + 14, MATRIX_DISPLAY_Y + 2, 3, 1, PIXEL_ON, NORM);
// /*
//   draw_rect_soft(0, 13, 64, 6, PIXEL_ON, NORM);
//   draw_line_vert(encoder_value, 13, 6, PIXEL_ON, NORM);

// */

// /* Mod display is 41 x 16 pixels */
// #define MOD_DISPLAY_X 30
// #define MOD_DISPLAY_Y 18

//   uint8_t mods = get_mods();
//   if (mods & MOD_LSFT) {
//     draw_rect_filled_soft(MOD_DISPLAY_X + 0, MOD_DISPLAY_Y, 5 + (1 * 6), 11, PIXEL_ON, NORM);
//     draw_string(MOD_DISPLAY_X + 3, MOD_DISPLAY_Y + 2, "S", PIXEL_OFF, NORM, 0);
//   } else {
//     draw_string(MOD_DISPLAY_X + 3, MOD_DISPLAY_Y + 2, "S", PIXEL_ON, NORM, 0);
//   }
//   if (mods & MOD_LCTL) {
//     draw_rect_filled_soft(MOD_DISPLAY_X + 10, MOD_DISPLAY_Y, 5 + (1 * 6), 11, PIXEL_ON, NORM);
//     draw_string(MOD_DISPLAY_X + 13, MOD_DISPLAY_Y + 2, "C", PIXEL_OFF, NORM, 0);
//   } else {
//     draw_string(MOD_DISPLAY_X + 13, MOD_DISPLAY_Y + 2, "C", PIXEL_ON, NORM, 0);
//   }
//   if (mods & MOD_LALT) {
//     draw_rect_filled_soft(MOD_DISPLAY_X + 20, MOD_DISPLAY_Y, 5 + (1 * 6), 11, PIXEL_ON, NORM);
//     draw_string(MOD_DISPLAY_X + 23, MOD_DISPLAY_Y + 2, "A", PIXEL_OFF, NORM, 0);
//   } else {
//     draw_string(MOD_DISPLAY_X + 23, MOD_DISPLAY_Y + 2, "A", PIXEL_ON, NORM, 0);
//   }
//   if (mods & MOD_LGUI) {
//     draw_rect_filled_soft(MOD_DISPLAY_X + 30, MOD_DISPLAY_Y, 5 + (1 * 6), 11, PIXEL_ON, NORM);
//     draw_string(MOD_DISPLAY_X + 33, MOD_DISPLAY_Y + 2, "G", PIXEL_OFF, NORM, 0);
//   } else {
//     draw_string(MOD_DISPLAY_X + 33, MOD_DISPLAY_Y + 2, "G", PIXEL_ON, NORM, 0);
//   }

// /* Lock display is 23 x 32 */
// #define LOCK_DISPLAY_X 100
// #define LOCK_DISPLAY_Y 0

//   if (led_numlock == true) {
//     draw_rect_filled_soft(LOCK_DISPLAY_X, LOCK_DISPLAY_Y, 5 + (3 * 6), 9, PIXEL_ON, NORM);
//     draw_string(LOCK_DISPLAY_X + 3, LOCK_DISPLAY_Y + 1, "NUM", PIXEL_OFF, NORM, 0);
//   } else if (led_numlock == false) {
//     draw_string(LOCK_DISPLAY_X + 3, LOCK_DISPLAY_Y + 1, "NUM", PIXEL_ON, NORM, 0);
//   }
//   if (led_capslock == true) {
//     draw_rect_filled_soft(LOCK_DISPLAY_X + 0, LOCK_DISPLAY_Y + 11, 5 + (3 * 6), 9, PIXEL_ON, NORM);
//     draw_string(LOCK_DISPLAY_X + 3, LOCK_DISPLAY_Y + 11 +1, "CAP", PIXEL_OFF, NORM, 0);
//   } else if (led_capslock == false) {
//     draw_string(LOCK_DISPLAY_X + 3, LOCK_DISPLAY_Y + 11 +1, "CAP", PIXEL_ON, NORM, 0);
//   }

//   if (led_scrolllock == true) {
//     draw_rect_filled_soft(LOCK_DISPLAY_X + 0, LOCK_DISPLAY_Y + 22, 5 + (3 * 6), 9, PIXEL_ON, NORM);
//     draw_string(LOCK_DISPLAY_X + 3, LOCK_DISPLAY_Y + 22 +1, "SCR", PIXEL_OFF, NORM, 0);
//   } else if (led_scrolllock == false) {
//     draw_string(LOCK_DISPLAY_X + 3, LOCK_DISPLAY_Y + 22 +1, "SCR", PIXEL_ON, NORM, 0);
//   }
//   send_buffer();
// }

// void read_host_led_state(void) {
//   uint8_t leds = host_keyboard_leds();
//   if (leds & (1 << USB_LED_NUM_LOCK))    {
//     if (led_numlock == false){
//     led_numlock = true;}
//     } else {
//     if (led_numlock == true){
//     led_numlock = false;}
//     }
//   if (leds & (1 << USB_LED_CAPS_LOCK))   {
//     if (led_capslock == false){
//     led_capslock = true;}
//     } else {
//     if (led_capslock == true){
//     led_capslock = false;}
//     }
//   if (leds & (1 << USB_LED_SCROLL_LOCK)) {
//     if (led_scrolllock == false){
//     led_scrolllock = true;}
//     } else {
//     if (led_scrolllock == true){
//     led_scrolllock = false;}
//     }
// }

// uint32_t layer_state_set_kb(uint32_t state) {
//   state = layer_state_set_user(state);
//   layer = biton32(state);
//   queue_for_send = true;
//   return state;
// }

// // bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
// //   queue_for_send = true;
// //   return process_record_user(keycode, record);
// // }

// void encoder_update_kb(uint8_t index, bool clockwise) {
//   encoder_value = (encoder_value + (clockwise ? 1 : -1)) % 64;
//   queue_for_send = true;
// }

// void matrix_init_user(void) {
//   queue_for_send = true;
//   printf("Queued OLED send on init\n");
// }

// void matrix_scan_user(void) {
//   if (queue_for_send) {
//     read_host_led_state();
//     draw_ui();
//     queue_for_send = false;
//   }
//   if (timer_elapsed(last_flush) > ScreenOffInterval) {
//     send_command(DISPLAYOFF);      /* 0xAE */
//   }
// }

// #endif
