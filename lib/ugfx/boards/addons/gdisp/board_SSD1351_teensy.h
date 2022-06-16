/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#ifndef _GDISP_LLD_BOARD_H
#define _GDISP_LLD_BOARD_H

#define init_board(g)			ssd1351_init_board()
#define post_init_board(g)
#define setpin_reset(g, s)		ssd1351_setpin_reset(s)
#define set_backlight(g, p)
#define acquire_bus(g)			ssd1351_acquire_bus()
#define release_bus(g)			ssd1351_release_bus()
#define write_cmd(g, i)			ssd1351_write_cmd(i)
#define write_data(g, d)		ssd1351_write_cmd(d)

/* This test is needed as this file is also included in the .cpp file providing the below functions */
#ifdef __cplusplus
extern "C" {
#endif

void ssd1351_init_board(void);
void ssd1351_setpin_reset(int state);
void ssd1351_acquire_bus(void);
void ssd1351_release_bus(void);
void ssd1351_write_cmd(unsigned char index);
void ssd1351_write_data(unsigned char data);

#ifdef __cplusplus
}
#endif

#endif /* _GDISP_LLD_BOARD_H */
