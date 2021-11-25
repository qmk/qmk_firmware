#pragma once

void on_connected(void);

void on_get_version(void);

void process_protocol(uint8_t c);

// @param index The 0-based index within the data section.
void _parse_data(uint8_t index, uint8_t c);

void _dispatch_command(void);
