// Copyright 2022 Jose Pablo Ramirez (@jpe230)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "jpe230.h"
#include <stdio.h>

#define ANIM_SIZE 352 // number of bytes in array, max is 1024 (minimize where possible)
#define IDLE_FRAMES 67 //number of total frames

void change_frame_up(uint8_t frame_number);
void change_frame_down(uint8_t frame_number);
const char first_frame[ANIM_SIZE];
const uint8_t key_frame[4];
