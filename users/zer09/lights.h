#include "avr/eeprom.h"
#include "zer09.h"

/* Will hold the RGB brightness level */
#define EECONFIG_LED_DIM_LVL (uint8_t *)15

#define SET_LED_RGB(r, g, b, led_dim, pos)                                     \
  setrgb(r >> led_dim, g >> led_dim, b >> led_dim, (LED_TYPE *)&led[pos])

typedef enum {
  DEFAULT,
  ENABLED,
  DISABLED,
} led_status;

typedef struct {
  led_status status;
  uint8_t pos;
} led_key;

enum rbw_keys { RBW_LCAPS, RBW_RCAPS, RBW_SCRLK, RBW };

extern volatile led_key rbw_led_keys[RBW];

void set_key_led(keyrecord_t *record, uint8_t lyr);
bool set_layer_led(uint8_t lyr);
bool rainbow_loop(uint8_t lyr);
bool led_brightness(uint16_t keycode, keyrecord_t *record);
void eeprom_read_led_dim_lvl(void);
