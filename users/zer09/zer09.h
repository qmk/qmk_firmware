#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

enum custom_keycodes { CK_SAFE = SAFE_RANGE, RGUP, RGDWN, NEWPLACEHOLDER };

typedef enum {
  DEFAULT,
  ENABLED,
  DISABLED,
} rbw_led_status;

typedef struct {
  rbw_led_status status;
  uint8_t pos;
} rbw_key_led;

#define _______ KC_TRNS
#define KC_RGUP RGUP
#define KC_RGDWN RGDWN

#define _BL 0 // The base layer
#define _UL 1 // The up layer
#define _DL 2 // The down layer
#define _VL 3 // The shifted up layer

#define _RBWC 3 // The count of rainbow leds.
#define _RBW_LCAPS 0
#define _RBW_RCAPS 1
#define _RBW_SCRLK 2

#define SET_LED_RGB(r, g, b, d, p)                                             \
  setrgb(r >> d, g >> d, b >> d, (LED_TYPE *)&led[p])

void set_key_led(keyrecord_t *record);
void set_layer_led(uint8_t dim);
void shifted_layer(void);
void layer_action(uint8_t layer);
void rainbow_loop(void);
bool led_brightness(uint16_t keycode, keyrecord_t *record);
void read_eeprom(void);

#endif
