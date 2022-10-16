/*
Copyright 2022 sporewoh

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "keezyboost40.h"

#include <string.h>
#include <math.h>
#include "quantum.h"
#include <hal_pal.h>
#include "hal.h"
#include "stdlib.h"

#include "iosevka11.qff.h"
#include "kicub.qgf.h"
#include "qp.h"


static painter_device_t lcd;
static painter_image_handle_t image;
// static painter_font_handle_t font;

const int HEIGHT = 160;
const int WIDTH = 128;


void keyboard_post_init_kb(void) {
    // Turn on the LCD
    setPinOutput(GP15);
    writePinHigh(GP15);

    // Let the LCD get some power...
    wait_ms(150);
    // Initialise the LCD
    lcd = qp_st7789_make_spi_device(HEIGHT, WIDTH, GP17, GP16, GP14, 1, 3);

    qp_init(lcd, QP_ROTATION_180);

    // Turn on the LCD and clear the display
    qp_power(lcd, true);

    // begin drawing space
    qp_rect(lcd, 0, 0, WIDTH, HEIGHT, 127, 230, 255, true);

    
    image = qp_load_image_mem(gfx_kicub);
    
    if (image != NULL) {
        // qp_drawimage(lcd, 0, 0, image);
        qp_drawimage_recolor(lcd, 2, 8, image, 0, 255, 0, 127, 230, 255);
        // qp_drawimage_recolor(lcd, 0, 0, image, 0, 255, 255, 0, 255, 0);

        qp_flush(lcd);
    }

    // font = qp_load_font_mem(font_iosevka11);
    // if (font != NULL) {
    //     qp_drawtext(lcd, 0, 0, font, "QUANTUM PAINTER @ RP2040");
    // }

    // Allow for user post-init
    keyboard_post_init_user();
}

#define NUM_PLANETS 4

void housekeeping_task_user(void) {

}