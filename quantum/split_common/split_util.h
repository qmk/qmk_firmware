#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

extern volatile bool isLeftHand;

void matrix_master_OLED_init(void);
void split_pre_init(void);
void split_post_init(void);

void set_split_host_leds(uint8_t host_leds);
uint8_t get_split_host_leds(void);
