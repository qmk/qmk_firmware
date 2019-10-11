#include "quantum.h"
#include "led_matrix.h"

extern issi3733_led_t *led_cur;
extern uint8_t led_per_run;
extern issi3733_led_t *lede;
extern issi3733_led_t led_map[];

static uint16_t last_boost_update;
static uint8_t led_boosts[ISSI3733_LED_COUNT];
static uint8_t led_boost_index;
static uint8_t led_cur_index;

#define LED_BOOST_REFRESH_INTERVAL_IN_MS 40
#define LED_BOOST_DECAY 0.7
#define LED_BOOST_PROPAGATE 0.5
#define LED_BOOST_PEAK 100

#define MIN_RGB 0x050008
#define MIN_R (MIN_RGB >> 16 & 0xff)
#define MIN_G (MIN_RGB >> 8 & 0xff)
#define MIN_B (MIN_RGB & 0xff)

#define MAX_RGB 0xc26eff
#define MAX_R (MAX_RGB >> 16 & 0xff)
#define MAX_G (MAX_RGB >> 8 & 0xff)
#define MAX_B (MAX_RGB & 0xff)

#define UNDERGLOW_RGB 0x4f002e
#define UNDERGLOW_R (UNDERGLOW_RGB >> 16 & 0xff)
#define UNDERGLOW_G (UNDERGLOW_RGB >> 8 & 0xff)
#define UNDERGLOW_B (UNDERGLOW_RGB & 0xff)

#define UNDERGLOW_SCAN_CODE 255

#define max(a, b) (((a) > (b)) ? (a) : (b))

#define __ -1
static const uint8_t KEY_TO_LED_MAP[MATRIX_ROWS][MATRIX_COLS] = {
  { 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14},
  {15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29},
  {30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, __, 42, 43},
  {44, __, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57},
  {58, 59, 60, __, __, __, 61, __, __, __, 62, 63, 64, 65, 66},
};

#define KEY_LED_COUNT 67
#define KP(c, r) { .col = c, .row = r } // shorthand for keypos_t
static const keypos_t LED_TO_KEY_MAP[KEY_LED_COUNT] = {
  KP(0, 0), KP(1, 0), KP(2, 0), KP(3, 0), KP(4, 0), KP(5, 0), KP(6, 0), KP(7, 0), KP(8, 0), KP(9, 0), KP(10, 0), KP(11, 0), KP(12, 0), KP(13, 0), KP(14, 0),
  KP(0, 1), KP(1, 1), KP(2, 1), KP(3, 1), KP(4, 1), KP(5, 1), KP(6, 1), KP(7, 1), KP(8, 1), KP(9, 1), KP(10, 1), KP(11, 1), KP(12, 1), KP(13, 1), KP(14, 1),
  KP(0, 2), KP(1, 2), KP(2, 2), KP(3, 2), KP(4, 2), KP(5, 2), KP(6, 2), KP(7, 2), KP(8, 2), KP(9, 2), KP(10, 2), KP(11, 2),            KP(13, 2), KP(14, 2),
  KP(0, 3),           KP(2, 3), KP(3, 3), KP(4, 3), KP(5, 3), KP(6, 3), KP(7, 3), KP(8, 3), KP(9, 3), KP(10, 3), KP(11, 3), KP(12, 3), KP(13, 3), KP(14, 3),
  KP(0, 4), KP(1, 4), KP(2, 4),                               KP(6, 4),                               KP(10, 4), KP(11, 4), KP(12, 4), KP(13, 4), KP(14, 4),
};


static void update_led_boosts(void);
static void update_led_cur_rgb_values(void);
static void set_nearest_led_to_max(uint8_t col, uint8_t row);
static uint8_t calculate_new_color_component_value(uint8_t max, uint8_t min);
static void calculate_new_led_boosts(uint8_t new_led_boosts[]);
static uint8_t calculate_new_led_boost_at(int index);
static uint8_t get_propagated_boost_from_neighbors(int led_position);
static uint8_t get_led_boost_at_keypos(uint8_t row, uint8_t col);
static void set_new_led_boosts(uint8_t* new_led_boosts);
static uint8_t map_key_position_to_led_index(uint8_t col, uint8_t row);


void rgb_matrix_init_user(void) {
  for (int i = 0; i < ISSI3733_LED_COUNT; i++) {
    led_boosts[i] = 0;
  }
  last_boost_update = timer_read();
  led_boost_index = 0;
  led_cur_index = 0;
}

void led_matrix_run(void) {
  uint8_t led_this_run = 0;

  if (led_cur == 0) { //Denotes start of new processing cycle in the case of chunked processing
    led_cur = led_map;
    led_cur_index = 0;
  }
  update_led_boosts();

  while (led_cur < lede && led_this_run < led_per_run) {
    update_led_cur_rgb_values();

    led_cur++;
    led_cur_index++;
    led_this_run++;
  }
}

void rgb_matrix_record_key_press(keyrecord_t *record) {
  if (record->event.pressed) {
    keypos_t key = record->event.key;
    set_nearest_led_to_max(key.col, key.row);
  }
}


static void update_led_boosts(void) {
  if (timer_elapsed(last_boost_update) > LED_BOOST_REFRESH_INTERVAL_IN_MS) {
    last_boost_update = timer_read();

    uint8_t new_led_boosts[ISSI3733_LED_COUNT];
    calculate_new_led_boosts(new_led_boosts);
    set_new_led_boosts(new_led_boosts);
  }
}

static void update_led_cur_rgb_values(void) {
  if (led_cur->scan == UNDERGLOW_SCAN_CODE) {
    *led_cur->rgb.r = UNDERGLOW_R;
    *led_cur->rgb.g = UNDERGLOW_G;
    *led_cur->rgb.b = UNDERGLOW_B;
  } else {
    *led_cur->rgb.r = calculate_new_color_component_value(MAX_R, MIN_R);
    *led_cur->rgb.g = calculate_new_color_component_value(MAX_G, MIN_G);
    *led_cur->rgb.b = calculate_new_color_component_value(MAX_B, MIN_B);
  }
}

static void set_nearest_led_to_max(uint8_t col, uint8_t row) {
  uint8_t led_index = map_key_position_to_led_index(col, row);
  if (led_index >= 0 && led_index < ISSI3733_LED_COUNT) {
    led_boosts[led_index] = LED_BOOST_PEAK;
  }
}

static uint8_t calculate_new_color_component_value(uint8_t max, uint8_t min) {
  uint8_t current_boost = led_boosts[led_cur_index];
  return (float)(max - min) * current_boost / LED_BOOST_PEAK + min;
}

static void calculate_new_led_boosts(uint8_t new_led_boosts[]) {
  for (int i = 0; i < ISSI3733_LED_COUNT; i++) {
    new_led_boosts[i] = calculate_new_led_boost_at(i);
  }
}

static uint8_t calculate_new_led_boost_at(int index) {
  uint8_t decayed_boost = led_boosts[index] * LED_BOOST_DECAY;
  uint8_t propagated_boost = get_propagated_boost_from_neighbors(index);
  uint8_t new_boost = (propagated_boost > decayed_boost) ? propagated_boost : decayed_boost;
  if (new_boost > LED_BOOST_PEAK) {
    new_boost = LED_BOOST_PEAK;
  }
  return new_boost;
}

static uint8_t get_propagated_boost_from_neighbors(int led_position) {
  if (led_position < 0 || led_position >= KEY_LED_COUNT) {
    return 0;
  }
  keypos_t led_keypos = LED_TO_KEY_MAP[led_position];
  uint8_t top_boost    = get_led_boost_at_keypos(led_keypos.row - 1, led_keypos.col);
  uint8_t bottom_boost = get_led_boost_at_keypos(led_keypos.row + 1, led_keypos.col);
  uint8_t left_boost   = get_led_boost_at_keypos(led_keypos.row, led_keypos.col - 1);
  uint8_t right_boost  = get_led_boost_at_keypos(led_keypos.row, led_keypos.col + 1);
  uint8_t max_boost = max(max(top_boost, bottom_boost), max(left_boost, right_boost));
  if (max_boost > LED_BOOST_PEAK) {
    max_boost = LED_BOOST_PEAK;
  }
  return max_boost * LED_BOOST_PROPAGATE;
}

static uint8_t get_led_boost_at_keypos(uint8_t row, uint8_t col) {
  if (row < 0 || row >= MATRIX_ROWS || col < 0 || col >= MATRIX_COLS) {
    return 0;
  }
  uint8_t led_index = KEY_TO_LED_MAP[row][col];
  if (led_index < 0) {
    return 0;
  }
  return led_boosts[led_index];
}

static void set_new_led_boosts(uint8_t* new_led_boosts) {
  for (int i = 0; i < ISSI3733_LED_COUNT; i++) {
    led_boosts[i] = new_led_boosts[i];
  }
}

static uint8_t map_key_position_to_led_index(uint8_t col, uint8_t row) {
  if (row >= 0 && row < MATRIX_ROWS && col >= 0 && col < MATRIX_COLS) {
    return KEY_TO_LED_MAP[row][col];
  }
  return -1;
}
