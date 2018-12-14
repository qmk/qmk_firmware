#include "rev1.h"

#define SET_PIN(PORT, BIT) (PORT & ~(1 << BIT))
#define RESET_PIN(PORT, BIT) (PORT | (1 << BIT))

#ifdef NUM_LOCK_INVERT
#define SET_NUM_LOCK RESET_PIN
#define RESET_NUM_LOCK SET_PIN
#else
#define SET_NUM_LOCK SET_PIN
#define RESET_NUM_LOCK RESET_PIN
#endif

#ifdef SCROLL_LOCK_INVERT
#define SET_SCROLL_LOCK RESET_PIN
#define RESET_SCROLL_LOCK SET_PIN
#else
#define SET_SCROLL_LOCK SET_PIN
#define RESET_SCROLL_LOCK RESET_PIN
#endif

#ifdef CAPS_LOCK_INVERT
#define SET_CAPS_LOCK RESET_PIN
#define RESET_CAPS_LOCK SET_PIN
#else
#define SET_CAPS_LOCK SET_PIN
#define RESET_CAPS_LOCK RESET_PIN
#endif

#ifdef SWAP_HANDS_ENABLE
__attribute__ ((weak))
const keypos_t hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
  {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}},
  {{0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}, {6, 5}},
  {{0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}, {6, 6}},
  {{0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}, {6, 7}},
  {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}},
  {{0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}, {6, 1}},
  {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 2}},
  {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {6, 3}},
};
#endif

#ifdef PHYSICAL_LEDS_ENABLE
void led_init_kb(void)
{
#ifdef NUM_LOCK_LED_ENABLE
  NUM_LOCK_LED_DDR |= (1 << NUM_LOCK_LED_BIT);
  //NUM_LOCK_LED_PORT = RESET_NUM_LOCK(NUM_LOCK_LED_PORT, NUM_LOCK_LED_BIT);
  NUM_LOCK_LED_PORT = SET_PIN(NUM_LOCK_LED_PORT, NUM_LOCK_LED_BIT); // this is a personnel crutch, don't mind
#endif // NUM_LOCK_LED_ENABLE
#ifdef CAPS_LOCK_LED_ENABLE
  CAPS_LOCK_LED_DDR |= (1 << CAPS_LOCK_LED_BIT);
  CAPS_LOCK_LED_PORT = RESET_CAPS_LOCK(CAPS_LOCK_LED_PORT, CAPS_LOCK_LED_BIT);
#endif // CAPS_LOCK_LED_ENABLE
#ifdef SCROLL_LOCK_LED_ENABLE
  SCROLL_LOCK_LED_DDR |= (1 << SCROLL_LOCK_LED_BIT);
  SCROLL_LOCK_LED_PORT = RESET_SCROLL_LOCK(SCROLL_LOCK_LED_PORT, SCROLL_LOCK_LED_BIT);
#endif // SCROLL_LOCK_LED_ENABLE
}
#endif // PHYSICAL_LEDS_ENABLE

void matrix_init_kb(void) {
#ifdef PHYSICAL_LEDS_ENABLE
  led_init_kb();
#endif // PHYSICAL_LEDS_ENABLE
  matrix_init_user();
};

#ifdef PHYSICAL_LEDS_ENABLE
void led_set_kb(uint8_t usb_led)
{
#ifdef NUM_LOCK_LED_ENABLE
  if (usb_led & (1<<USB_LED_NUM_LOCK)) {
    NUM_LOCK_LED_PORT = SET_NUM_LOCK(NUM_LOCK_LED_PORT, NUM_LOCK_LED_BIT);
  } else {
    NUM_LOCK_LED_PORT = RESET_NUM_LOCK(NUM_LOCK_LED_PORT, NUM_LOCK_LED_BIT);
  }
#endif // NUM_LOCK_LED_ENABLE
#ifdef CAPS_LOCK_LED_ENABLE
  if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
    CAPS_LOCK_LED_PORT = SET_CAPS_LOCK(CAPS_LOCK_LED_PORT, CAPS_LOCK_LED_BIT);
  } else {
    CAPS_LOCK_LED_PORT = RESET_CAPS_LOCK(CAPS_LOCK_LED_PORT, CAPS_LOCK_LED_BIT);
  }
#endif // CAPS_LOCK_LED_ENABLE
#ifdef SCROLL_LOCK_LED_ENABLE
  if (usb_led & (1<<USB_LED_SCROLL_LOCK)) {
    SCROLL_LOCK_LED_PORT = SET_SCROLL_LOCK(SCROLL_LOCK_LED_PORT, SCROLL_LOCK_LED_BIT);
  } else {
    SCROLL_LOCK_LED_PORT = RESET_SCROLL_LOCK(SCROLL_LOCK_LED_PORT, SCROLL_LOCK_LED_BIT);
  }
#endif // SCROLL_LOCK_LED_ENABLE
  led_set_user(usb_led);
}
#endif // PHYSICAL_LEDS_ENABLE
