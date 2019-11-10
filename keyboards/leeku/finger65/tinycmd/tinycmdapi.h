#ifndef TINYCMDAPI_H
#define TINYCMDAPI_H

#include "tinycmd.h"
#include "tinycmdpkt.h"

uint8_t tinycmd_config(uint8_t rgb_num, uint16_t rgb_limit, uint8_t rsp);
uint8_t tinycmd_ver(uint8_t rsp);
uint8_t tinycmd_reset(uint8_t type, uint8_t rsp);
uint8_t tinycmd_three_lock(uint8_t num, uint8_t caps, uint8_t scroll, uint8_t rsp);
uint8_t tinycmd_dirty(uint8_t down);
uint8_t tinycmd_sleep(uint8_t sleep, uint8_t rsp);
uint8_t tinycmd_rgb_all(uint8_t on, uint8_t r, uint8_t g, uint8_t b, uint8_t rsp);
uint8_t tinycmd_rgb_pos(uint8_t pos, uint8_t r, uint8_t g, uint8_t b, uint8_t rsp);
uint8_t tinycmd_rgb_range(uint8_t num, uint8_t offset, uint8_t r, uint8_t g, uint8_t b, uint8_t rsp);
uint8_t tinycmd_rgb_buffer(uint8_t num, uint8_t offset, uint8_t *led, uint8_t rsp);
uint8_t tinycmd_rgb_effect_speed(uint16_t speed, uint8_t rsp);
uint8_t tinycmd_rgb_effect_on(uint8_t on, uint8_t rsp);

uint8_t tinycmd_rgb_set_effect(uint8_t index, uint8_t rsp);
uint8_t tinycmd_rgb_set_preset(uint8_t index, rgb_effect_param_type *p_param, uint8_t rsp);
uint8_t tinycmd_led_level(uint8_t channel, uint8_t level, uint8_t rsp);
uint8_t tinycmd_led_set_effect(uint8_t index, uint8_t rsp);
uint8_t tinycmd_led_set_preset(uint8_t preset, uint8_t block, uint8_t mode, uint8_t rsp);
uint8_t tinycmd_led_config_preset(uint8_t *p_led_mode_array, uint8_t rsp);
uint8_t tinycmd_led_effect_on(uint8_t on, uint8_t rsp);


#endif // TINYCMDAPI_H

