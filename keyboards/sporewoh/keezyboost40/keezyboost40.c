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
    // lcd = qp_st7789_make_spi_device(240, 320, GP17, GP16, GP14, 1, 3);
    int SUN_RADIUS = 7;
    lcd = qp_st7789_make_spi_device(HEIGHT, WIDTH, GP17, GP16, GP14, 1, 3);

    qp_init(lcd, QP_ROTATION_180);

    // Turn on the LCD and clear the display
    qp_power(lcd, true);
    //qp_rect(lcd, 0, 0, 239, 319, 255, 255, 255, true);

    // begin drawing space
    // qp_rect(lcd, 0, 0, 200, 200, 150, 0, 255, true);
    qp_rect(lcd, 0, 0, WIDTH, HEIGHT, 127, 230, 255, true);


    // draw sun 
    qp_circle(lcd, (WIDTH/2), (HEIGHT/2), SUN_RADIUS, 5, 255, 255, true);

    // qp_rect(lcd, 0, 100, 60, 319, 0,0,0, tque);                
    
    image = qp_load_image_mem(gfx_kicub);
    
    if (image != NULL) {
        // qp_drawimage(lcd, 0, 0, image);
        qp_drawimage_recolor(lcd, 2, 8, image, 0, 255, 0, 127, 230, 255);
        // qp_drawimage_recolor(lcd, 0, 0, image, 0, 255, 255, 0, 255, 0);

        qp_flush(lcd);
    }

    // font = qp_load_font_mem(font_iosevka11);
    // if (font != NULL) {
    //     qp_drawtext(lcd, 40, 160, font, "QUANTUM PAINTER @ RP2040");
    // }

    // Allow for user post-init
    keyboard_post_init_user();
}

#define NUM_PLANETS 4

void housekeeping_task_user(void) {
    static uint32_t last_draw = 0;

    // const int PLANET_RADIUS_SIZE = 10;

    // const double ORBIT_1_RADIUS = 15;
    // const double ORBIT_SEPERATION = 10;
    
    // const double LINEAR_VELOCITY = 3;

    // static double planets_radians[NUM_PLANETS] = {0};
    // static double planets_x[NUM_PLANETS] = {0};
    // static double planets_y[NUM_PLANETS] = {0};

    static int i;

    if (timer_elapsed32(last_draw) > 33) { // Throttle to 30fps
        last_draw = timer_read32();
        // // Draw r=4 filled circles down the left side of the display
        i++;
        // qp_drawimage_recolor(lcd, 2, 8, image, 0, 0, 0, rand()%255, 190, 255);

        //qp_rect(lcd, 0, 0, 200, 200, (i*8)%255, 225, 255, true);
        //qp_drawimage_recolor(lcd, 0, 0, image, 50, 255, 255, 50, 255, 0);
        //qp_drawimage_recolor(lcd, 0, 0, image, 0, 0, 0, 0, 0, 0);



        

        // for (int i = 0; i < NUM_PLANETS; i++){
        //     // Clear old planets
        //     if (planets_x[i] != 0 && planets_y[i] != 0){
        //         //qp_circle(lcd, planets_x[i], planets_y[i],PLANET_RADIUS_SIZE, 255, 0, 255, true);
        //     }

        //     int orbit_radius = ORBIT_1_RADIUS+(ORBIT_SEPERATION*i);
            
        //     // Draw orbits
        //     qp_circle(lcd, (WIDTH/2), (HEIGHT/2), orbit_radius, 255, 255, 0, false);
        //     double orbital_velocity = LINEAR_VELOCITY/orbit_radius;
            
        //     // Add radians
        //     planets_radians[i] += fmod(orbital_velocity,6.285714); 
        //     planets_x[i] = (WIDTH/2) + (cos(planets_radians[i])*orbit_radius);
        //     planets_y[i] = (HEIGHT/2) + (sin(planets_radians[i])*orbit_radius);
            
        //     qp_circle(lcd, planets_x[i], planets_y[i], PLANET_RADIUS_SIZE, (i+1)*64, 0, 255, true);
        // }

        //qp_flush(lcd);
    }
}