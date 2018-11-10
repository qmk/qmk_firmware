/*
 * LEDDriver.c
 *
 *  Created on: Aug 26, 2013
 *      Author: Omri Iluz
 */

#include "ws2812.h"
#include "stdlib.h"

#define BYTES_FOR_LED_BYTE 4
#define NB_COLORS 3
#define BYTES_FOR_LED BYTES_FOR_LED_BYTE*NB_COLORS
#define DATA_SIZE BYTES_FOR_LED*NB_LEDS
#define RESET_SIZE 200
#define PREAMBLE_SIZE 4
// Define the spi your LEDs are plugged to here
#define WS2812_SPI SPID2
// Define the number of LEDs you wish to control in your LED strip
#define NB_LEDS RGBLED_NUM

#define LED_SPIRAL 1

static uint8_t txbuf[PREAMBLE_SIZE + DATA_SIZE + RESET_SIZE];
static uint8_t get_protocol_eq(uint8_t data, int pos);

/*
 * This lib is meant to be used asynchronously, thus the colors contained in
 * the txbuf will be sent in loop, so that the colors are always the ones you
 * put in the table (the user thus have less to worry about)
 *
 * Since the data are sent via DMA, and the call to spiSend is a blocking one,
 * the processor ressources are not used to much, if you see your program being
 * too slow, simply add a:
 * chThdSleepMilliseconds(x);
 * after the spiSend, where you increment x untill you are satisfied with your
 * program speed, another trick may be to lower this thread priority : your call
 */
static THD_WORKING_AREA(LEDS_THREAD_WA, 128);
static THD_FUNCTION(ledsThread, arg) {
  (void) arg;
  while(1){
    spiSend(&LEDS_SPI, PREAMBLE_SIZE + DATA_SIZE + RESET_SIZE, txbuf);
  }
}

static const SPIConfig spicfg = {
  NULL,
  PORT_WS2812,
  PIN_WS2812,
  SPI_CR1_BR_1|SPI_CR1_BR_0 // baudrate : fpclk / 8 => 1tick is 0.32us
};

/*
 * Function used to initialize the driver.
 *
 * Starts by shutting off all the LEDs.
 * Then gets access on the LED_SPI driver.
 * May eventually launch an animation on the LEDs (e.g. a thread setting the
 * txbuff values)
 */
void leds_init(void){
  for(int i = 0; i < RESET_SIZE; i++)
    txbuf[DATA_SIZE+i] = 0x00;
  for (int i=0; i<PREAMBLE_SIZE; i++)
    txbuf[i] = 0x00;
  spiAcquireBus(&LEDS_SPI);              /* Acquire ownership of the bus.    */
  spiStart(&LEDS_SPI, &spicfg);          /* Setup transfer parameters.       */
  spiSelect(&LEDS_SPI);                  /* Slave Select assertion.          */
  chThdCreateStatic(LEDS_THREAD_WA, sizeof(LEDS_THREAD_WA),NORMALPRIO, ledsThread, NULL);
}

/*
 * As the trick here is to use the SPI to send a huge pattern of 0 and 1 to
 * the ws2812b protocol, we use this helper function to translate bytes into
 * 0s and 1s for the LED (with the appropriate timing).
 */
static uint8_t get_protocol_eq(uint8_t data, int pos){
  uint8_t eq = 0;
  if (data & (1 << (2*(3-pos))))
    eq = 0b1110;
  else
    eq = 0b1000;
  if (data & (2 << (2*(3-pos))))
    eq += 0b11100000;
  else
    eq += 0b10000000;
  return eq;
}


void WS2812_init(void) {
  /* MOSI pin*/
  palSetPadMode(PORT_WS2812, PIN_WS2812, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
  leds_init();
}

void ws2812_setleds(LED_TYPE *ledarray, uint16_t number_of_leds) {
//   uint8_t i = 0;
//   while (i < number_of_leds) {
//     ws2812_write_led(i, ledarray[i].r, ledarray[i].g, ledarray[i].b);
//     i++;
//   }
  uint8_t i = 0;
  while (i < number_of_leds) {
    setColor(ledarray[i].g, (fb+24*i), sMask);
    setColor(ledarray[i].r, (fb+24*i)+8, sMask);
    setColor(ledarray[i].b, (fb+24*i)+16, sMask);
    i++;
  }
}

void ws2812_setleds_rgbw(LED_TYPE *ledarray, uint16_t number_of_leds) {

}

void WS2812_send_color( uint8_t index ) {
  setColor(led_array[index].g, (fb+24*index), sMask);
  setColor(led_array[index].r, (fb+24*index)+8, sMask);
  setColor(led_array[index].b, (fb+24*index)+16, sMask);
}

void WS2812_set_color( uint8_t index, uint8_t red, uint8_t green, uint8_t blue ) {
  led_array[index].r = red;
  led_array[index].g = green;
  led_array[index].b = blue;
}

void WS2812_set_color_all( uint8_t red, uint8_t green, uint8_t blue ) {
  for (int i = 0; i < RGBLED_NUM; i++) {
    WS2812_set_color( i, red, green, blue );
  }
}

void WS2812_send_colors(void) {
  for (int i = 0; i < RGBLED_NUM; i++) {
    WS2812_send_color( i );
  }
}
