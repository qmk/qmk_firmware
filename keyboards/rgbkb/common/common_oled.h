#pragma once

#include <stdint.h>
#include <stdbool.h>

void render_logo(void);
void render_icon(void);
void render_rgb_menu(void);
void rgb_menu_selection(void);
void rgb_menu_action(bool clockwise);
void rgb_menu_update(int8_t transaction_id);
void rgb_menu_slave_sync(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer);