#ifndef PROCESS_RECORD_USER_H
#define PROCESS_RECORD_USER_H

#include QMK_KEYBOARD_H

bool process_record_user(uint16_t keycode, keyrecord_t *record);

extern bool isSneaking;
extern bool isJumping;
extern bool isBarking;
extern bool showedJump;

//uint32_t anim_sleep_timer;


#endif