#pragma once

bool is_capsword_enabled;

void capsword_sync_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data);
