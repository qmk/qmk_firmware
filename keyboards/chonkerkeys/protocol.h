#pragma once

void on_connected(void);

void on_get_version(void);

void _get_config_data_writer(void);

void on_get_config(void);

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

void _send_event_raw(uint8_t event_type, uint16_t data_length, void(*data_writer)(void));

void _send_uint16(uint16_t buffer);

void _send_uint32(uint32_t buffer);

void _dispatch_command(void);
