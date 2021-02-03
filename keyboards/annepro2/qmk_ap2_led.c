#include "hal.h"
#include "annepro2.h"
#include "qmk_ap2_led.h"

bool AP2_LED_ENABLED = false;
bool AP2_LED_DYNAMIC_PROFILE = false;
bool AP2_FOREGROUND_COLOR_SET = false;

void annepro2LedDisable(void)
{
  sdPut(&SD0, CMD_LED_OFF);
  AP2_LED_ENABLED = false;
}

void annepro2LedEnable(void)
{
  sdPut(&SD0, CMD_LED_ON);
  AP2_LED_ENABLED = true;
}

void annepro2LedUpdate(uint8_t row, uint8_t col)
{
  sdPut(&SD0, CMD_LED_SET);
  sdPut(&SD0, row);
  sdPut(&SD0, col);
  sdWrite(&SD0, (uint8_t *)&annepro2LedMatrix[row * MATRIX_COLS + col], sizeof(uint16_t));
}

void annepro2LedUpdateRow(uint8_t row)
{
  sdPut(&SD0, CMD_LED_SET_ROW);
  sdPut(&SD0, row);
  sdWrite(&SD0, (uint8_t *)&annepro2LedMatrix[row * MATRIX_COLS], sizeof(uint16_t) * MATRIX_COLS);
}

void annepro2LedSetProfile(uint8_t prof)
{
  sdPut(&SD0, CMD_LED_SET_PROFILE);
  sdPut(&SD0, prof);
  uint8_t buf = sdGet(&SD0);
  AP2_LED_DYNAMIC_PROFILE = buf;
}

uint8_t annepro2LedGetProfile()
{
  uint8_t buf = 0;
  sdPut(&SD0, CMD_LED_GET_PROFILE);
  buf = sdGet(&SD0);
  return buf;
}

uint8_t annepro2LedGetNumProfiles()
{
  uint8_t buf = 0;
  sdPut(&SD0, CMD_LED_GET_NUM_PROFILES);
  buf = sdGet(&SD0);
  return buf;
}

void annepro2LedNextProfile()
{
  sdPut(&SD0, CMD_LED_NEXT_PROFILE);
  uint8_t buf = sdGet(&SD0);
  AP2_LED_DYNAMIC_PROFILE = buf;
}

void annepro2LedNextIntensity()
{
  sdPut(&SD0, CMD_LED_NEXT_INTENSITY);
}

void annepro2LedNextAnimationSpeed()
{
  sdPut(&SD0, CMD_LED_NEXT_ANIMATION_SPEED);
}

void annepro2LedPrevProfile()
{
  sdPut(&SD0, CMD_LED_PREV_PROFILE);
  uint8_t buf = sdGet(&SD0);
  AP2_LED_DYNAMIC_PROFILE = buf;
}

void annepro2LedSetMask(uint8_t key)
{
  sdPut(&SD0, CMD_LED_SET_MASK);
  sdPut(&SD0, key);
}

void annepro2LedClearMask(uint8_t key)
{
  sdPut(&SD0, CMD_LED_CLEAR_MASK);
  sdPut(&SD0, key);
}

void annepro2LedSetForegroundColor(uint8_t red, uint8_t green, uint8_t blue)
{
  sdPut(&SD0, CMD_LED_SET_FOREGROUND_COLOR);
  uint8_t colors[3]={red,green,blue};
  sdWrite(&SD0, (uint8_t *)&colors, sizeof(colors));
  AP2_FOREGROUND_COLOR_SET = true;
}

void annepro2LedResetForegroundColor()
{
  sdPut(&SD0, CMD_LED_CLEAR_FOREGROUND_COLOR);
  uint8_t buf = sdGet(&SD0);
  AP2_LED_DYNAMIC_PROFILE = buf;
  AP2_FOREGROUND_COLOR_SET = false;
}

/*
 * If enabled, this data is sent to LED MCU on every keypress.
 * In order to improve performance, both row and column values
 * are packed into a single byte.
 * Row range is [0, 4] and requires only 3 bits.
 * Column range is [0, 13] and requires 4 bits.
 *
 * In order to differentiate this command from regular commands,
 * the leftmost bit is set to 1 (0b10000000).
 * Following it are 3 bits of row and 4 bits of col.
 * 1 + 3 + 4 = 8 bits - only a single byte is sent for every keypress.
 */
void annepro2LedForwardKeypress(uint8_t row, uint8_t col)
{
  uint8_t msg = 0b10000000 | (row << 4) | col;
  sdPut(&SD0, msg);
}
