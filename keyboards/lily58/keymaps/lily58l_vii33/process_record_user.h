#ifndef PROCESS_RECORD_USER_H
#define PROCESS_RECORD_USER_H

#include QMK_KEYBOARD_H

bool process_record_user(uint16_t keycode, keyrecord_t *record);

extern bool lunaIsSneaking;
extern bool lunaIsJumping;
extern bool lunaIsBarking;
extern bool lunaShowedJump;

//uint32_t anim_sleep_timer;


#endif