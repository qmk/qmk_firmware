#pragma once

#include "command.h"

void on_connected(void);

void on_get_version(void);

void on_get_config(void);

void on_reset(void);

void on_set_led(struct command_set_led *set_led);

// Technically these should be defined as function pointer and core.c would assign function to the pointer for proper
// inversion of control, but this firmware couldn't afford such abstraction due to perf penalty.
void set_led_steady(uint8_t key_x, uint8_t key_y, uint8_t r, uint8_t g, uint8_t b);

void set_led_blink(uint8_t key_x, uint8_t key_y, uint8_t r, uint8_t g, uint8_t b, uint8_t frequency_tbc);

void set_led_like(uint8_t key_x, uint8_t key_y, uint8_t r, uint8_t g, uint8_t b);

void set_led_leave_meeting(uint8_t key_x, uint8_t key_y, uint8_t r, uint8_t g, uint8_t b);

void set_led_momentary(uint8_t key_x, uint8_t key_y, uint8_t r, uint8_t g, uint8_t b, uint32_t duration_ms);

uint8_t get_layer_count(void);

uint8_t get_layer_type(uint8_t index);

uint8_t get_key_size_and_ordinal(uint8_t layer, uint8_t x, uint8_t y);

uint8_t get_key_action_type(uint8_t layer, uint8_t x, uint8_t y);

uint32_t get_key_icon(uint8_t layer, uint8_t x, uint8_t y);

void process_protocol(uint8_t c);

void send_protocol(uint8_t c);

void key_down(uint8_t layer, uint8_t x, uint8_t y);

// @param index The 0-based index within the data section.
void _parse_data(uint8_t index, uint8_t c);

void _send_event(uint8_t event_type, uint8_t* event);

void _send_event_raw(uint8_t event_type, uint16_t data_length, void(*data_writer)(void*), void* user_data);

void _send_uint16(uint16_t buffer);

void _send_uint32(uint32_t buffer);

void _dispatch_command(void);
