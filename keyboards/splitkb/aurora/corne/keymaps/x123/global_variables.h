#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>


uint32_t timeout_tap = 150;
uint32_t timeout_seq = 80;
uint32_t timeout_following = 150;
uint32_t timeout_release_key = 20;

uint16_t alt_tab_timer = 0;
uint16_t caps_timer = 0;

bool is_alt_tab_active = false; // ADD this near the beginning of keymap.c
bool turbo_modifier_active = false; // For supascrolling
uint16_t turbo_threshold = 5; /* Delay in ms between pressing the up/down keys during turbo mode. */
uint16_t turbo_timer = 0; /* Keeps track of when a direction was last input, so we don't spam too much.*/
bool turbo_up = false;
bool turbo_down = false;
bool turbo_left = false;
bool turbo_right = false;

#endif