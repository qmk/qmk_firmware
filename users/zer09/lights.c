#include "lights.h"

static bool active_key_pos[50] = {};
static uint8_t led_dim = 0;

volatile led_key rbw_led_keys[RBW] = {
    [RBW_LCTL] = {DEFAULT, 21, true},  [RBW_LCAP] = {DEFAULT, 24, false},
    [RBW_LSPR] = {DEFAULT, 23, true},  [RBW_RCTL] = {DEFAULT, 48, true},
    [RBW_RCAP] = {DEFAULT, 45, false}, [RBW_RALT] = {DEFAULT, 46, true},
    [RBW_SCRL] = {DEFAULT, 42, true}};

/* Pressed led color. */
const uint32_t _PC[3] = {0xFF, 0x00, 0x00};

/* Layer color. */
const uint8_t _LC[5][3] = {[_BL] = {0x00, 0x00, 0x00},
                           [_UL] = {0x00, 0x00, 0xFF},
                           [_VL] = {0xFF, 0xFF, 0x00},
                           [_DL] = {0x00, 0xFF, 0x00},
                           [_AL] = {0xFF, 0x00, 0x00}};

/* Color table by sine wave */
const uint8_t _LIGHTS[360] = {
    0,   0,   0,   0,   0,   1,   1,   2,   2,   3,   4,   5,   6,   7,   8,
    11,  12,  9,   13,  15,  17,  18,  20,  22,  24,  26,  28,  30,  32,  35,
    37,  39,  42,  44,  47,  49,  52,  55,  58,  60,  63,  66,  69,  72,  75,
    78,  81,  85,  88,  91,  94,  97,  101, 104, 107, 111, 114, 117, 121, 124,
    127, 131, 134, 137, 141, 144, 147, 150, 154, 157, 160, 163, 167, 170, 173,
    176, 179, 182, 185, 188, 191, 194, 197, 200, 202, 205, 208, 210, 213, 215,
    217, 220, 222, 224, 226, 229, 231, 232, 234, 236, 238, 239, 241, 242, 244,
    245, 246, 248, 249, 250, 251, 251, 252, 253, 253, 254, 254, 255, 255, 255,
    255, 255, 255, 255, 254, 254, 253, 253, 252, 251, 251, 250, 249, 248, 246,
    245, 244, 242, 241, 239, 238, 236, 234, 232, 231, 229, 226, 224, 222, 220,
    217, 215, 213, 210, 208, 205, 202, 200, 197, 194, 191, 188, 185, 182, 179,
    176, 173, 170, 167, 163, 160, 157, 154, 150, 147, 144, 141, 137, 134, 131,
    127, 124, 121, 117, 114, 111, 107, 104, 101, 97,  94,  91,  88,  85,  81,
    78,  75,  72,  69,  66,  63,  60,  58,  55,  52,  49,  47,  44,  42,  39,
    37,  35,  32,  30,  28,  26,  24,  22,  20,  18,  17,  15,  13,  12,  11,
    9,   8,   7,   6,   5,   4,   3,   2,   2,   1,   1,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0};

void set_key_led(keyrecord_t *record, uint8_t lyr) {
  static uint8_t base = 5;

  uint8_t r = record->event.key.row;
  uint8_t c = record->event.key.col;
  uint8_t pos;

  // This was the result of my soldering.
  // Lesson of the day: always check.
  if (r < 5) {
    pos = r % 2 == 0 ? r * base + c : r * base + (base - (c + 1));
  } else {
    pos = r % 2 == 0 ? r * base + (base - (c + 1)) : r * base + c;
  }

  if (record->event.pressed) {
    active_key_pos[pos] = true;
    SET_LED_RGB(_PC[0], _PC[1], _PC[2], led_dim, pos);
  } else {
    active_key_pos[pos] = false;
    SET_LED_RGB(_LC[lyr][0], _LC[lyr][1], _LC[lyr][2], led_dim, pos);
  }
}

/* Fix for unknown reason after testin flash the eeprom handedness,
   the leds will ligth up after boot.
   This should be call in the set layer led.*/
bool is_first_run(void) {
  static uint8_t run = 0;

  if (run == 0) {
    run++;
    return true;
  } else {
    return false;
  }
}

bool set_layer_led(uint8_t lyr) {
  static uint8_t p_lyr = 0; // Previous layer.
  static uint8_t p_dim = 0; // Previous dim.

  if (p_lyr == lyr && p_dim == led_dim && !is_first_run()) {
    return false;
  }

  p_lyr = lyr;
  p_dim = led_dim;
  const uint8_t r = _LC[lyr][0];
  const uint8_t g = _LC[lyr][1];
  const uint8_t b = _LC[lyr][2];
  const uint8_t d = (p_lyr == _VL && p_dim < 1) ? 1 : p_dim;

  for (uint8_t i = 0; i < RGBLED_NUM; i++) {
    SET_LED_RGB(r, g, b, d, i);
  }

  return true;
}

bool rainbow_loop(uint8_t lyr) {
  static uint16_t last_timer = 0;
  static uint16_t i = 0;
  static uint8_t r, g, b, pos;

  if (timer_elapsed(last_timer) < 8) {
    return false;
  }

  if (i >= 360) {
    i = 0;
  }

  last_timer = timer_read();
  r = _LIGHTS[(i + 120) % 360];
  g = _LIGHTS[i];
  b = _LIGHTS[(i + 240) % 360];

  i++;

  bool set_rbw = false;

  for (uint8_t j = 0; j < RBW; j++) {
    pos = rbw_led_keys[j].pos;

    switch (rbw_led_keys[j].status) {
    case ENABLED:
      if (!active_key_pos[pos] || rbw_led_keys[j].forced) {
        SET_LED_RGB(r, g, b, led_dim, pos);
        set_rbw = true;
      }

      break;
    case DISABLED:
      if (!active_key_pos[pos] || rbw_led_keys[j].forced) {
        SET_LED_RGB(_LC[lyr][0], _LC[lyr][1], _LC[lyr][2], led_dim, pos);
        set_rbw = true;
      }

      rbw_led_keys[j].status = DEFAULT;
      break;
    default:
      break;
    }
  }

  return set_rbw;
}

bool led_brightness(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case RGUP:
    if (record->event.pressed && led_dim > 0) {
      led_dim--;
      eeprom_write_byte(EECONFIG_LED_DIM_LVL, led_dim);
    }

    return true;
    break;
  case RGDWN:
    if (record->event.pressed && led_dim < 8) {
      led_dim++;
      eeprom_write_byte(EECONFIG_LED_DIM_LVL, led_dim);
    }

    return true;
    break;
  default:
    return false;
    break;
  }
}

void eeprom_read_led_dim_lvl(void) {
  led_dim = eeprom_read_byte(EECONFIG_LED_DIM_LVL);

  if (led_dim > 8 || led_dim < 0) {
    led_dim = 0;
    eeprom_write_byte(EECONFIG_LED_DIM_LVL, led_dim);
  }
}
