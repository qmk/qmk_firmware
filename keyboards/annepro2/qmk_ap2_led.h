#pragma once

#define CMD_LED_ON                          0x1
#define CMD_LED_OFF                         0x2
#define CMD_LED_SET                         0x3
#define CMD_LED_SET_ROW                     0x4
#define CMD_LED_SET_PROFILE                 0x5
#define CMD_LED_NEXT_PROFILE                0x6
#define CMD_LED_PREV_PROFILE                0x7
#define CMD_LED_GET_PROFILE                 0x8
#define CMD_LED_GET_NUM_PROFILES            0x9

void annepro2LedDisable(void);
void annepro2LedEnable(void);
void annepro2LedUpdate(uint8_t row, uint8_t col);
void annepro2LedUpdateRow(uint8_t row);
void annepro2LedSetProfile(uint8_t prof);
uint8_t annepro2LedGetProfile(void);
uint8_t annepro2LedGetNumProfiles(void);
void annepro2LedNextProfile(void);
void annepro2LedPrevProfile(void);
