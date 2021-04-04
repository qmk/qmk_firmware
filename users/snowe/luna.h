#ifndef QMK_FIRMWARE_LUNA_H
#define QMK_FIRMWARE_LUNA_H
#endif  // QMK_FIRMWARE_LUNA_H

#pragma once

extern bool isSneaking;
extern bool isJumping;
extern bool showedJump;

// status variables
extern led_t led_usb_state;
//extern int current_wpm;


void render_luna(int LUNA_X, int LUNA_Y);

