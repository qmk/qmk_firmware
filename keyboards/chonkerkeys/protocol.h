#pragma once

void on_connected(void);

void on_get_version(void);

uint8_t layer_count(void);

uint8_t layer_type(uint8_t index);

uint8_t key_size_and_ordinal(uint8_t layer, uint8_t x, uint8_t y);

uint8_t key_action_type(uint8_t layer, uint8_t x, uint8_t y);

uint32_t key_icon(uint8_t layer, uint8_t x, uint8_t y);

void process_protocol(uint8_t c);

void send_protocol(uint8_t c);

// @param index The 0-based index within the data section.
void _parse_data(uint8_t index, uint8_t c);

void _send_event(uint8_t event_type, uint8_t* event);

void _send_uint16(uint16_t buffer);

void _send_uint32(uint32_t buffer);

void _dispatch_command(void);
