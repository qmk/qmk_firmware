#include "lets_split.h"
#include "keymap_extras/keymap_german_ch.h"
#include "ws2812.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define QWERTY 0



// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// leds status
bool RGB_LIGHT_STATUS = true;

enum Color_Keycodes {
  BLACK = SAFE_RANGE,
  BLUE,
  BROWN,
  CYAN,
  GOLD,
  GREEN,
  GREY,
  MAROON,
  ORANGE,
  PINK,
  PURPLE,
  RED,
  WHITE,
  YELLOW,
  COLOR0,
  COLOR1,
  COLOR2,
  COLOR3,
  COLOR4,
  COLOR5,
  COLOR6,
  COLOR7,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Adjust| Ctrl | Alt  | GUI  |Lower |Space |Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[QWERTY] = KEYMAP( \
  RGB_TOG,  BLACK,    BLUE,    BROWN,    CYAN,    GOLD,    RGB_TOG,  BLACK,    BLUE,    BROWN,    CYAN,    GOLD, \
  GREEN,  GREY,    MAROON,    GREEN,    ORANGE,    PINK,    GREEN,  GREY,    MAROON,    GREEN,    ORANGE,    PINK, \
  PURPLE, RED,    WHITE,    YELLOW,    COLOR0,    COLOR1,    PURPLE,    RED,    WHITE,    YELLOW,    COLOR0,    COLOR1, \
  COLOR2, COLOR3,    COLOR4,    COLOR5,    COLOR6,    COLOR7,    COLOR2, COLOR3,    COLOR4,    COLOR5,    COLOR6,    COLOR7 \
)
};



struct cRGB led[RGBLED_NUM];
void rgbsps_set(uint8_t index, uint8_t r, uint8_t g, uint8_t b) {
  led[index].r = r;
  led[index].g = g;
  led[index].b = b;
}
void rgbsps_setall(uint8_t r, uint8_t g, uint8_t b) {
  for (uint16_t i = 0; i < RGBLED_NUM; i++) {
    rgbsps_set(i, r, g, b);
  }
}


// this runs on key pressed
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case RGB_TOG: {
      // capture one press, otherway it will enter here multiple times
      if (record->event.pressed) {
        RGB_LIGHT_STATUS = RGB_LIGHT_STATUS ? false : true;
      }
      break;
    }
    case BLACK: {
      if (record->event.pressed)
      {
        rgbsps_setall(50,0,0);
        ws2812_setleds(led, RGBLED_NUM);
      }
      break;
    }
    case BLUE: {
      if (record->event.pressed)
      {
        rgbsps_setall(100,1,0);
        ws2812_setleds(led, RGBLED_NUM);
      }
      break;
    }
    case BROWN: {
      if (record->event.pressed)
      {
        rgbsps_setall(200,50,0);
        ws2812_setleds(led, RGBLED_NUM);
      }
      break;
    }
    case CYAN: {
      if (record->event.pressed)
      {
        rgbsps_setall(200,50,50);
        ws2812_setleds(led, RGBLED_NUM);
      }
      break;
    }
    case GOLD: {
      if (record->event.pressed)
      {
        rgbsps_setall(200,100,50);
        ws2812_setleds(led, RGBLED_NUM);
      }
      break;
    }
    case GREEN: {
      if (record->event.pressed)
      {
        rgbsps_setall(200,150,50);
        ws2812_setleds(led, RGBLED_NUM);
      }
      break;
    }
    case GREY: {
      if (record->event.pressed)
      {
        rgbsps_setall(200,150,100);
        ws2812_setleds(led, RGBLED_NUM);
      }
      break;
    }
    case MAROON: {
      if (record->event.pressed)
      {
        rgbsps_setall(250,50,100);
        ws2812_setleds(led, RGBLED_NUM);
      }
      break;
    }
    case ORANGE: {
      if (record->event.pressed)
      {
        rgbsps_setall(250,50,150);
        ws2812_setleds(led, RGBLED_NUM);
      }
      break;
    }
    case PINK: {
      if (record->event.pressed)
      {
        rgbsps_setall(200,50,200);
        ws2812_setleds(led, RGBLED_NUM);
      }
      break;
    }
    case PURPLE: {
      if (record->event.pressed)
      {
        rgbsps_setall(150,50,200);
        ws2812_setleds(led, RGBLED_NUM);
      }
      break;
    }
    case RED: {
      if (record->event.pressed)
      {
        rgbsps_setall(100,50,250);
        ws2812_setleds(led, RGBLED_NUM);
      }
      break;
    }
    case WHITE: {
      if (record->event.pressed)
      {
        rgbsps_setall(250,250,250);
        ws2812_setleds(led, RGBLED_NUM);
      }
      break;
    }
    case YELLOW: {
      if (record->event.pressed)
      {
        rgbsps_setall(50,50,50);
        ws2812_setleds(led, RGBLED_NUM);
      }
      break;
    }
    case COLOR0: {
      if (record->event.pressed)
      {
        rgbsps_setall(0,50,250);
        ws2812_setleds(led, RGBLED_NUM);
      }
      break;
    }
    case COLOR1: {
      if (record->event.pressed)
      {
        rgbsps_setall(50,50,250);
        ws2812_setleds(led, RGBLED_NUM);
      }
      break;
    }
    case COLOR2: {
      if (record->event.pressed)
      {
        rgbsps_setall(0,100,250);
        ws2812_setleds(led, RGBLED_NUM);
      }
      break;
    }
    case COLOR3: {
      if (record->event.pressed)
      {
        rgbsps_setall(50,150,250);
        ws2812_setleds(led, RGBLED_NUM);
      }
      break;
    }
    case COLOR4: {
      if (record->event.pressed)
      {
        rgbsps_setall(100,150,250);
        ws2812_setleds(led, RGBLED_NUM);
      }
      break;
    }
    case COLOR5: {
      if (record->event.pressed)
      {
        rgbsps_setall(0,250,0);
        ws2812_setleds(led, RGBLED_NUM);
      }
      break;
    }
    case COLOR6: {
      if (record->event.pressed)
      {
        rgbsps_setall(50,250,0);
        ws2812_setleds(led, RGBLED_NUM);
      }
      break;
    }
    case COLOR7: {
      if (record->event.pressed)
      {
        rgbsps_setall(50,250,50);
        ws2812_setleds(led, RGBLED_NUM);
      }
      break;
    }
  }
  return true;
}

