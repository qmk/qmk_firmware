#include "ch.h"
#include "hal.h"

#include "hsv2rgb.h"
#include "underglow.h"

#define BYTES_FOR_LED_BYTE 4
#define NB_COLORS 3
#define BYTES_FOR_LED BYTES_FOR_LED_BYTE*NB_COLORS
#define DATA_SIZE BYTES_FOR_LED*NB_LEDS
#define RESET_SIZE 200
#define PREAMBLE_SIZE 4

// Define the spi your LEDs are plugged to here
#define LEDS_SPI SPID2
// Define the number of LEDs you wish to control in your LED strip
#define NB_LEDS 8

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

#if LED_SPIRAL
/*
 * 'Led spiral' is a simple demo in which we put all the leds to the same
 * color, where this color does all the hsv circle in loop.
 * If you want to launch the thread that will chage the led colors to the
 * appropriate value, simply set LED_SPIRAL to 1.
 */
static THD_WORKING_AREA(HSVTRANS_WA, 128);
static THD_FUNCTION(hsv_transThread, arg){
  (void) arg;
  hsv_color color = {0, 255, 127};
  while(1){
    color.h += 1;
    color.h %= 256;
    set_leds_color_hsv(color);
    chThdSleepMilliseconds(50);
  }
}
#endif

static const SPIConfig spicfg = {
  NULL,
  GPIOB,
  15,
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
#if LED_SPIRAL
  chThdCreateStatic(HSVTRANS_WA, sizeof(HSVTRANS_WA),
      NORMALPRIO, hsv_transThread, NULL);
#endif
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

/*
 * If you want to set a LED's color in the HSV color space, simply call this
 * function with a hsv_color containing the desired color and the index of the
 * led on the LED strip (starting from 0, the first one being the closest the
 * first plugged to the board)
 *
 * Only set the color of the LEDs through the functions given by this API
 * (unless you really know what you are doing)
 */
void set_led_color_hsv(hsv_color color, int pos){
  set_led_color_rgb(hsv2rgb(color), pos);
}

/*
 * If you want to set a LED's color in the RGB color space, simply call this
 * function with a hsv_color containing the desired color and the index of the
 * led on the LED strip (starting from 0, the first one being the closest the
 * first plugged to the board)
 *
 * Only set the color of the LEDs through the functions given by this API
 * (unless you really know what you are doing)
 */
void set_led_color_rgb(rgb_color color, int pos){
  for(int j = 0; j < 4; j++)
    txbuf[PREAMBLE_SIZE + BYTES_FOR_LED*pos + j] = get_protocol_eq(color.g, j);
  for(int j = 0; j < 4; j++)
    txbuf[PREAMBLE_SIZE + BYTES_FOR_LED*pos + BYTES_FOR_LED_BYTE+j] = get_protocol_eq(color.r, j);
  for(int j = 0; j < 4; j++)
    txbuf[PREAMBLE_SIZE + BYTES_FOR_LED*pos + BYTES_FOR_LED_BYTE*2+j] = get_protocol_eq(color.b, j);
}

/*
 * Same as the two above, but sets all the LEDs in the LED strip (HSV)
 */
void set_leds_color_hsv(hsv_color color){
  for(int i = 0; i < NB_LEDS; i++)
    set_led_color_hsv(color, i);
}

/*
 * Same as the two above, but sets all the LEDs in the LED strip (RGB)
 */
void set_leds_color_rgb(rgb_color color){
  for(int i = 0; i < NB_LEDS; i++)
    set_led_color_rgb(color, i);
}