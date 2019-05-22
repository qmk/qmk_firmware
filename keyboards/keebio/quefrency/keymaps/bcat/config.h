#pragma once

/*
 * I2C seems to randomly drop keystrokes. Not sure why. It seems a bit like
 * https://github.com/qmk/qmk_firmware/issues/5037, but that issue is closed,
 * and our problems happen even with underglow disabled.
 *
 * This issue occurs with multiple TRRS cables of different lengths from
 * different companies, so it's most likely not a cable issue.  It may be that
 * we are running into issues with long I2C runs, in which case stronger
 * pull-up resistors might help:
 * https://hackaday.com/2017/02/08/taking-the-leap-off-board-an-introduction-to-i2c-over-long-wires/.
 * For now, just don't use I2C.
 */
#define USE_SERIAL

/* Use an extra LED on the right side since it's wider on the 65% PCB. */
#undef RGBLED_NUM
#define RGBLED_NUM 17

/* Set up RGB lighting so it works with either side as master. */
#define RGBLED_SPLIT { 8, 9 }
