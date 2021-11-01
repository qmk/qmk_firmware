/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <https://github.com/Legonut> wrote this file.  As long as you retain this
 * notice you can do whatever you want with this stuff. If we meet some day, and
 * you think this stuff is worth it, you can buy me a beer in return. David Rauseo
 * ----------------------------------------------------------------------------
 */

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