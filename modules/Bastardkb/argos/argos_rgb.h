#include "quantum.h"
#include "argos.h"

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)

// bool rgb_matrix_indicators_advanced_module(uint8_t led_min, uint8_t led_max);
void argos_rgb_init(void);
void argos_rgb_load_from_eeprom(void);
void argos_rgb_set_led_at_position(uint8_t layer, uint8_t row, uint8_t col, uint8_t r, uint8_t g, uint8_t b, bool passthrough, bool on, bool custom, uint8_t offset, uint8_t index);
void argos_rgb_get_led_at_position(argos_rgb_t *entry, uint8_t layer, uint8_t index, uint8_t offset);
void rgb_sync_handler(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer);
void argos_rgb_handle_set_led_at_position(uint16_t keyIndex, uint8_t r, uint8_t g, uint8_t b, bool passthrough, bool on, bool custom);
void argos_rgb_get_layer_color(uint8_t layer, RGB *rgb);

#endif