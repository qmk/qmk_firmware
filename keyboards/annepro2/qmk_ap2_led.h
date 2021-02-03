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
#define CMD_LED_SET_MASK                    0xA
#define CMD_LED_CLEAR_MASK                  0xB
#define CMD_LED_NEXT_INTENSITY              0xC
#define CMD_LED_NEXT_ANIMATION_SPEED        0xD
#define CMD_LED_SET_FOREGROUND_COLOR        0xE
#define CMD_LED_CLEAR_FOREGROUND_COLOR      0xF
#define CMD_LED_IAP                         0x10
#define CMD_LED_KEYPRESS                    0x11

void annepro2SetIAP(void);
void annepro2LedDisable(void);
void annepro2LedEnable(void);
void annepro2LedUpdate(uint8_t row, uint8_t col);
void annepro2LedUpdateRow(uint8_t row);
void annepro2LedSetProfile(uint8_t prof);
uint8_t annepro2LedGetProfile(void);
uint8_t annepro2LedGetNumProfiles(void);
void annepro2LedNextProfile(void);
void annepro2LedPrevProfile(void);
void annepro2LedSetMask(uint8_t key);
void annepro2LedClearMask(uint8_t key);
void annepro2LedNextIntensity(void);
void annepro2LedNextAnimationSpeed(void);
void annepro2LedSetForegroundColor(uint8_t red, uint8_t green, uint8_t blue);
void annepro2LedResetForegroundColor(void);
void annepro2LedForwardKeypress(uint8_t row, uint8_t col);


extern bool AP2_LED_ENABLED;
extern bool AP2_LED_DYNAMIC_PROFILE;
extern bool AP2_FOREGROUND_COLOR_SET;
