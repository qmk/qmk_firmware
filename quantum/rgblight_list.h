/* Copyright 2018 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef RGBLIGHT_LIST_H
#define RGBLIGHT_LIST_H

/*                            SET RGB List                            */
#define rgblight_setrgb_white()       rgblight_setrgb (0xFF, 0xFF, 0xFF)
#define rgblight_setrgb_red()         rgblight_setrgb (0xFF, 0x00, 0x00)
#define rgblight_setrgb_coral()       rgblight_setrgb (0xFF, 0x7C, 0x4D)
#define rgblight_setrgb_orange()      rgblight_setrgb (0xFF, 0x80, 0x00)
#define rgblight_setrgb_goldenrod()   rgblight_setrgb (0xD9, 0xA5, 0x21)
#define rgblight_setrgb_gold()        rgblight_setrgb (0xFF, 0xD9, 0x00)
#define rgblight_setrgb_yellow()      rgblight_setrgb (0xFF, 0xFF, 0x00)
#define rgblight_setrgb_chartreuse()  rgblight_setrgb (0x80, 0xFF, 0x00)
#define rgblight_setrgb_green()       rgblight_setrgb (0x00, 0xFF, 0x00)
#define rgblight_setrgb_springgreen() rgblight_setrgb (0x00, 0xFF, 0x80)
#define rgblight_setrgb_turquoise()   rgblight_setrgb (0x47, 0x6E, 0x6A)
#define rgblight_setrgb_teal()        rgblight_setrgb (0x00, 0x80, 0x80)
#define rgblight_setrgb_cyan()        rgblight_setrgb (0x00, 0xFF, 0xFF)
#define rgblight_setrgb_azure()       rgblight_setrgb (0x99, 0xf5, 0xFF)
#define rgblight_setrgb_blue()        rgblight_setrgb (0x00, 0x00, 0xFF)
#define rgblight_setrgb_purple()      rgblight_setrgb (0x7A, 0x00, 0xFF)
#define rgblight_setrgb_magenta()     rgblight_setrgb (0xFF, 0x00, 0xFF)
#define rgblight_setrgb_pink()        rgblight_setrgb (0xFF, 0x80, 0xBF)

/*                            SET RGB List                            */
#define rgblight_setrgb_white_at(at)       rgblight_setrgb_at (0xFF, 0xFF, 0xFF, at)
#define rgblight_setrgb_red_at(at)         rgblight_setrgb_at (0xFF, 0x00, 0x00, at)
#define rgblight_setrgb_coral_at(at)       rgblight_setrgb_at (0xFF, 0x7C, 0x4D, at)
#define rgblight_setrgb_orange_at(at)      rgblight_setrgb_at (0xFF, 0x80, 0x00, at)
#define rgblight_setrgb_goldenrod_at(at)   rgblight_setrgb_at (0xD9, 0xA5, 0x21, at)
#define rgblight_setrgb_gold_at(at)        rgblight_setrgb_at (0xFF, 0xD9, 0x00, at)
#define rgblight_setrgb_yellow_at(at)      rgblight_setrgb_at (0xFF, 0xFF, 0x00, at)
#define rgblight_setrgb_chartreuse_at(at)  rgblight_setrgb_at (0x80, 0xFF, 0x00, at)
#define rgblight_setrgb_green_at(at)       rgblight_setrgb_at (0x00, 0xFF, 0x00, at)
#define rgblight_setrgb_springgreen_at(at) rgblight_setrgb_at (0x00, 0xFF, 0x80, at)
#define rgblight_setrgb_turquoise_at(at)   rgblight_setrgb_at (0x47, 0x6E, 0x6A, at)
#define rgblight_setrgb_teal_at(at)        rgblight_setrgb_at (0x00, 0x80, 0x80, at)
#define rgblight_setrgb_cyan_at(at)        rgblight_setrgb_at (0x00, 0xFF, 0xFF, at)
#define rgblight_setrgb_azure_at(at)       rgblight_setrgb_at (0x99, 0xf5, 0xFF, at)
#define rgblight_setrgb_blue_at(at)        rgblight_setrgb_at (0x00, 0x00, 0xFF, at)
#define rgblight_setrgb_purple_at(at)      rgblight_setrgb_at (0x7A, 0x00, 0xFF, at)
#define rgblight_setrgb_magenta_at(at)     rgblight_setrgb_at (0xFF, 0x00, 0xFF, at)
#define rgblight_setrgb_pink_at(at)        rgblight_setrgb_at (0xFF, 0x80, 0xBF, at)

/*                            SET HSV List                            */
#define rgblight_sethsv_white()       rgblight_sethsv (  0,   0, 255)
#define rgblight_sethsv_red()         rgblight_sethsv (  0, 255, 255)
#define rgblight_sethsv_coral()       rgblight_sethsv ( 16, 176, 255)
#define rgblight_sethsv_orange()      rgblight_sethsv ( 39, 255, 255)
#define rgblight_sethsv_goldenrod()   rgblight_sethsv ( 43, 218, 218)
#define rgblight_sethsv_gold()        rgblight_sethsv ( 51, 255, 255)
#define rgblight_sethsv_yellow()      rgblight_sethsv ( 60, 255, 255)
#define rgblight_sethsv_chartreuse()  rgblight_sethsv ( 90, 255, 255)
#define rgblight_sethsv_green()       rgblight_sethsv (120, 255, 255)
#define rgblight_sethsv_springgreen() rgblight_sethsv (150, 255, 255)
#define rgblight_sethsv_turquoise()   rgblight_sethsv (174,  90, 112)
#define rgblight_sethsv_teal()        rgblight_sethsv (180, 255, 128)
#define rgblight_sethsv_cyan()        rgblight_sethsv (180, 255, 255)
#define rgblight_sethsv_azure()       rgblight_sethsv (186, 102, 255)
#define rgblight_sethsv_blue()        rgblight_sethsv (240, 255, 255)
#define rgblight_sethsv_purple()      rgblight_sethsv (270, 255, 255)
#define rgblight_sethsv_magenta()     rgblight_sethsv (300, 255, 255)
#define rgblight_sethsv_pink()        rgblight_sethsv (330, 128, 255)

/*                            SET HSV List                            */
#define rgblight_sethsv_white_at(at)       rgblight_sethsv_at (  0,   0, 255, at)
#define rgblight_sethsv_red_at(at)         rgblight_sethsv_at (  0, 255, 255, at)
#define rgblight_sethsv_coral_at(at)       rgblight_sethsv_at ( 16, 176, 255, at)
#define rgblight_sethsv_orange_at(at)      rgblight_sethsv_at ( 39, 255, 255, at)
#define rgblight_sethsv_goldenrod_at(at)   rgblight_sethsv_at ( 43, 218, 218, at)
#define rgblight_sethsv_gold_at(at)        rgblight_sethsv_at ( 51, 255, 255, at)
#define rgblight_sethsv_yellow_at(at)      rgblight_sethsv_at ( 60, 255, 255, at)
#define rgblight_sethsv_chartreuse_at(at)  rgblight_sethsv_at ( 90, 255, 255, at)
#define rgblight_sethsv_green_at(at)       rgblight_sethsv_at (120, 255, 255, at)
#define rgblight_sethsv_springgreen_at(at) rgblight_sethsv_at (150, 255, 255, at)
#define rgblight_sethsv_turquoise_at(at)   rgblight_sethsv_at (174,  90, 112, at)
#define rgblight_sethsv_teal_at(at)        rgblight_sethsv_at (180, 255, 128, at)
#define rgblight_sethsv_cyan_at(at)        rgblight_sethsv_at (180, 255, 255, at)
#define rgblight_sethsv_azure_at(at)       rgblight_sethsv_at (186, 102, 255, at)
#define rgblight_sethsv_blue_at(at)        rgblight_sethsv_at (240, 255, 255, at)
#define rgblight_sethsv_purple_at(at)      rgblight_sethsv_at (270, 255, 255, at)
#define rgblight_sethsv_magenta_at(at)     rgblight_sethsv_at (300, 255, 255, at)
#define rgblight_sethsv_pink_at(at)        rgblight_sethsv_at (330, 128, 255, at)

#endif
