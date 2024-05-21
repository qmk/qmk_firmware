/*
Copyright 2023 Spencer Deven <splitlogicdesign@gmail.com>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "quantum.h"
#include "print.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
// Key Matrix to LED Index
  // Left Hand
  { 8, 6, 5, 3, 2, 0, NO_LED },
  { 9, 10, 11, 12, 13, 14, 15 },
  { 24, 22, 21, 19, 18, 17, 31 },
  { 25, 26, 27, 28, 29, 30, 32 },
  { 43, 41, 40, 38, 37, 35, 33 },
  // Right Hand
  { 52, 50, 49, 47, 46, 44, NO_LED },
  { 53, 54, 55, 56, 57, 58, 59 },
  { 68, 66, 65, 63, 62, 64, 75 },
  { 69, 70, 71, 72, 73, 74, 76 },
  { 87, 85, 84, 82, 81, 79, 77 },


},
{
{ 80, 10 },
{ 74, 2 },
{ 64, 9 },
{ 49, 7 },
{ 38, 1 },
{ 33, 9 },
{ 18, 13 },
{ 9, 5 },
{ 2, 13 },
{ 2, 24 },
{ 18, 24 },
{ 33, 19 },
{ 49, 18 },
{ 64, 20 },
{ 80, 21 },
{ 96, 37 },
{ 91, 29 },
{ 80, 32 },
{ 64, 31 },
{ 49, 29 },
{ 41, 29 },
{ 33, 30 },
{ 18, 35 },
{ 10, 35 },
{ 2, 35 },
{ 2, 45 },
{ 18, 45 },
{ 33, 41 },
{ 49, 40 },
{ 64, 41 },
{ 80, 42 },
{ 96, 49 },
{ 108, 54 },
{ 102, 64 },
{ 93, 61 },
{ 85, 58 },
{ 72, 53 },
{ 64, 52 },
{ 49, 50 },
{ 41, 52 },
{ 33, 52 },
{ 18, 56 },
{ 10, 57 },
{ 2, 56 },
{ 142, 10 },
{ 149, 2 },
{ 158, 9 },
{ 174, 7 },
{ 185, 1 },
{ 190, 9 },
{ 205, 13 },
{ 213, 5 },
{ 220, 13 },
{ 220, 24 },
{ 205, 24 },
{ 190, 19 },
{ 174, 18 },
{ 158, 20 },
{ 142, 21 },
{ 126, 37 },
{ 133, 29 },
{ 142, 32 },
{ 158, 31 },
{ 174, 29 },
{ 182, 29 },
{ 190, 30 },
{ 205, 35 },
{ 213, 35 },
{ 220, 35 },
{ 220, 45 },
{ 205, 45 },
{ 190, 41 },
{ 174, 40 },
{ 158, 41 },
{ 142, 42 },
{ 127, 49 },
{ 113, 54 },
{ 120, 64 },
{ 129, 61 },
{ 138, 58 },
{ 151, 53 },
{ 158, 52 },
{ 174, 50 },
{ 182, 52 },
{ 190, 52 },
{ 205, 56 },
{ 214, 57 },
{ 220, 56 },
},
{
  // LED Index to Flag
 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
} };
#endif

#ifdef ENCODER_ENABLE

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
      return false; /* Don't process further events if user function exists and returns false */
    }
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code_delay(KC_VOLD, 10);
        } else {
            tap_code_delay(KC_VOLU, 10);
        }
    } else if (index == 1) { /* Second encoder */
        if (clockwise) {
            rgblight_decrease_val();
        } else {
            rgblight_increase_val();
        }

    } else if (index == 2) { /* Third encoder */
        if (clockwise) {
            tap_code(KC_MS_WH_DOWN);
        } else {
            tap_code(KC_MS_WH_UP);
        }
    } else if (index == 3) { /* Fourth encoder */
        if (clockwise) {
            tap_code(KC_MS_WH_RIGHT);
        } else {
            tap_code(KC_MS_WH_LEFT);
        }
    } else if (index == 4) { /* Fifth encoder */
        if (clockwise) {
            tap_code(KC_MS_WH_DOWN);
        } else {
            tap_code(KC_MS_WH_UP);
        }
    }
    return true;
}

#endif

#ifdef QUANTUM_PAINTER_ENABLE

#include "images/ZodiarkPiLogoGC.qgf.c"
#include "images/ZodiarkPiLogo2Green.qgf.c"
#include "images/ZodiarkPiLogoSTpink.qgf.c"

static painter_device_t display;
static painter_image_handle_t image;

// st7789 enable, comment out the following line if not using a st7789
painter_device_t qp_st7789_make_spi_device(uint16_t panel_width, uint16_t panel_height, pin_t chip_select_pin, pin_t dc_pin, pin_t reset_pin, uint16_t spi_divisor, int spi_mode);
// gc9a01 enable, comment out the following line if not using a gc9a01
// painter_device_t qp_gc9a01_make_spi_device(uint16_t panel_width, uint16_t panel_height, pin_t chip_select_pin, pin_t dc_pin, pin_t reset_pin, uint16_t spi_divisor, int spi_mode);

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  debug_keyboard=true;
  debug_mouse=true;
}

uint32_t deferred_init(uint32_t trigger_time, void *cb_arg) {

    print("doing stuff\n");

// ##st7789 screen support, comment out down to "##end st7789 screen support" if not using a st7789 screen
    display = qp_st7789_make_spi_device(320, 240, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, LCD_SPI_DIVISOR, 3);
    if (is_keyboard_left()) {
        qp_power(display, true);
        }
    if (is_keyboard_left()) {
        qp_init(display, QP_ROTATION_180);
        }
// If using pointing device on right side, comment out following 3 lines, if using dual screens, uncomment.
        else {
        qp_init(display, QP_ROTATION_0);
        }
    if (is_keyboard_left()) {
        image = qp_load_image_mem(gfx_ZodiarkPiLogoSTpink);
    }
// If using pointing device on right side, comment out following 3 lines, if using dual screens, uncomment
    else {
        image = qp_load_image_mem(gfx_ZodiarkPiLogoSTpink);
    }
    // ##end st7789 screen support

// ##gc9a01 screeen support, comment out down to "##end GC9A01 screen support" if not using a gc9a01 screen
    // display = qp_gc9a01_make_spi_device(240, 240, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, LCD_SPI_DIVISOR, 0);
    // qp_power(display, true);
    // if (is_keyboard_left()) {
    //     qp_init(display, QP_ROTATION_0);
    //     }
    // If using pointing device on right side, comment out following 3 lines, if using dual screens, uncomment.
    //     else {
    //     qp_init(display, QP_ROTATION_0);
    //     }

    //     if (is_keyboard_left()) {
    //     image = qp_load_image_mem(gfx_ZodiarkPiLogoGC);
    //      }
    // If using pointing device on right side, comment out following 3 lines, if using dual screens, uncomment.
    //     else {
    //     image = qp_load_image_mem(gfx_ZodiarkPiLogoGC);
    // }
    // ##end GC9A01 screeen support

    if (image != NULL) {
        print("image was not null\n");
        if (is_keyboard_left()) {
            qp_drawimage(display, 0, 0, image);
        }
    // If using pointing device on right side, comment out following 3 lines, if using dual screens, uncomment.
        else {
            qp_drawimage(display, 0, 0, image);
        }
    }


    return(0);
}

void keyboard_post_init_kb(void)
{
    debug_enable=true;
    defer_exec(3000, deferred_init, NULL);
}
#endif
