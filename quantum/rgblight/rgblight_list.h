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
#pragma once

#include "color.h"

/*
########################################################################################
##                                                                                    ##
##                                                                                    ##
##                                                                                    ##
##  The functions below have been deprecated and may be removed in a future release.  ##
##                                                                                    ##
##              Please use the values in color.h with the RGB functions.              ##
##                                                                                    ##
##                                                                                    ##
##                                                                                    ##
########################################################################################
*/

/*                            SET RGB List                            */
#define rgblight_setrgb_white() rgblight_setrgb(RGB_WHITE)
#define rgblight_setrgb_red() rgblight_setrgb(RGB_RED)
#define rgblight_setrgb_coral() rgblight_setrgb(RGB_CORAL)
#define rgblight_setrgb_orange() rgblight_setrgb(RGB_ORANGE)
#define rgblight_setrgb_goldenrod() rgblight_setrgb(RGB_GOLDENROD)
#define rgblight_setrgb_gold() rgblight_setrgb(RGB_GOLD)
#define rgblight_setrgb_yellow() rgblight_setrgb(RGB_YELLOW)
#define rgblight_setrgb_chartreuse() rgblight_setrgb(RGB_CHARTREUSE)
#define rgblight_setrgb_green() rgblight_setrgb(RGB_GREEN)
#define rgblight_setrgb_springgreen() rgblight_setrgb(RGB_SPRINGGREEN)
#define rgblight_setrgb_turquoise() rgblight_setrgb(RGB_TURQUOISE)
#define rgblight_setrgb_teal() rgblight_setrgb(RGB_TEAL)
#define rgblight_setrgb_cyan() rgblight_setrgb(RGB_CYAN)
#define rgblight_setrgb_azure() rgblight_setrgb(RGB_AZURE)
#define rgblight_setrgb_blue() rgblight_setrgb(RGB_BLUE)
#define rgblight_setrgb_purple() rgblight_setrgb(RGB_PURPLE)
#define rgblight_setrgb_magenta() rgblight_setrgb(RGB_MAGENTA)
#define rgblight_setrgb_pink() rgblight_setrgb(RGB_PINK)

/*                            SET RGB List                            */
#define rgblight_setrgb_white_at(at) rgblight_setrgb_at(RGB_WHITE, at)
#define rgblight_setrgb_red_at(at) rgblight_setrgb_at(RGB_RED, at)
#define rgblight_setrgb_coral_at(at) rgblight_setrgb_at(RGB_CORAL, at)
#define rgblight_setrgb_orange_at(at) rgblight_setrgb_at(RGB_ORANGE at)
#define rgblight_setrgb_goldenrod_at(at) rgblight_setrgb_at(RGB_GOLDENROD, at)
#define rgblight_setrgb_gold_at(at) rgblight_setrgb_at(RGB_GOLD, at)
#define rgblight_setrgb_yellow_at(at) rgblight_setrgb_at(RGB_YELLOW, at)
#define rgblight_setrgb_chartreuse_at(at) rgblight_setrgb_at(RGB_CHARTREUSE, at)
#define rgblight_setrgb_green_at(at) rgblight_setrgb_at(RGB_GREEN, at)
#define rgblight_setrgb_springgreen_at(at) rgblight_setrgb_at(RGB_SPRINGGREEN, at)
#define rgblight_setrgb_turquoise_at(at) rgblight_setrgb_at(RGB_TURQUOISE, at)
#define rgblight_setrgb_teal_at(at) rgblight_setrgb_at(RGB_TEAL, at)
#define rgblight_setrgb_cyan_at(at) rgblight_setrgb_at(RGB_CYAN, at)
#define rgblight_setrgb_azure_at(at) rgblight_setrgb_at(RGB_AZURE, at)
#define rgblight_setrgb_blue_at(at) rgblight_setrgb_at(RGB_BLUE, at)
#define rgblight_setrgb_purple_at(at) rgblight_setrgb_at(RGB_PURPLE, at)
#define rgblight_setrgb_magenta_at(at) rgblight_setrgb_at(RGB_MAGENTA, at)
#define rgblight_setrgb_pink_at(at) rgblight_setrgb_at(RGB_PINK, at)

/*                            SET HSV List                            */
#define rgblight_sethsv_white() rgblight_sethsv(HSV_WHITE)
#define rgblight_sethsv_red() rgblight_sethsv(HSV_RED)
#define rgblight_sethsv_coral() rgblight_sethsv(HSV_CORAL)
#define rgblight_sethsv_orange() rgblight_sethsv(HSV_ORANGE)
#define rgblight_sethsv_goldenrod() rgblight_sethsv(HSV_GOLDENROD)
#define rgblight_sethsv_gold() rgblight_sethsv(HSV_GOLD)
#define rgblight_sethsv_yellow() rgblight_sethsv(HSV_YELLOW)
#define rgblight_sethsv_chartreuse() rgblight_sethsv(HSV_CHARTREUSE)
#define rgblight_sethsv_green() rgblight_sethsv(HSV_GREEN)
#define rgblight_sethsv_springgreen() rgblight_sethsv(HSV_SPRINGGREEN)
#define rgblight_sethsv_turquoise() rgblight_sethsv(HSV_TURQUOISE)
#define rgblight_sethsv_teal() rgblight_sethsv(HSV_TEAL)
#define rgblight_sethsv_cyan() rgblight_sethsv(HSV_CYAN)
#define rgblight_sethsv_azure() rgblight_sethsv(HSV_AZURE)
#define rgblight_sethsv_blue() rgblight_sethsv(HSV_BLUE)
#define rgblight_sethsv_purple() rgblight_sethsv(HSV_PURPLE)
#define rgblight_sethsv_magenta() rgblight_sethsv(HSV_MAGENTA)
#define rgblight_sethsv_pink() rgblight_sethsv(HSV_PINK)

/*                            SET HSV List                            */
/*   If you're doing layer indication, this is best, as it won't      */
/*   write to the eeprom, since it's limited (very high value).       */
/*   If you want to use modes with this (since you can), then you     */
/*   want to use rgblight_mode_noeeprom(x) instead.                   */
#define rgblight_sethsv_noeeprom_white() rgblight_sethsv_noeeprom(HSV_WHITE)
#define rgblight_sethsv_noeeprom_red() rgblight_sethsv_noeeprom(HSV_RED)
#define rgblight_sethsv_noeeprom_coral() rgblight_sethsv_noeeprom(HSV_CORAL)
#define rgblight_sethsv_noeeprom_orange() rgblight_sethsv_noeeprom(HSV_ORANGE)
#define rgblight_sethsv_noeeprom_goldenrod() rgblight_sethsv_noeeprom(HSV_GOLDENROD)
#define rgblight_sethsv_noeeprom_gold() rgblight_sethsv_noeeprom(HSV_GOLD)
#define rgblight_sethsv_noeeprom_yellow() rgblight_sethsv_noeeprom(HSV_YELLOW)
#define rgblight_sethsv_noeeprom_chartreuse() rgblight_sethsv_noeeprom(HSV_CHARTREUSE)
#define rgblight_sethsv_noeeprom_green() rgblight_sethsv_noeeprom(HSV_GREEN)
#define rgblight_sethsv_noeeprom_springgreen() rgblight_sethsv_noeeprom(HSV_SPRINGGREEN)
#define rgblight_sethsv_noeeprom_turquoise() rgblight_sethsv_noeeprom(HSV_TURQUOISE)
#define rgblight_sethsv_noeeprom_teal() rgblight_sethsv_noeeprom(HSV_TEAL)
#define rgblight_sethsv_noeeprom_cyan() rgblight_sethsv_noeeprom(HSV_CYAN)
#define rgblight_sethsv_noeeprom_azure() rgblight_sethsv_noeeprom(HSV_AZURE)
#define rgblight_sethsv_noeeprom_blue() rgblight_sethsv_noeeprom(HSV_BLUE)
#define rgblight_sethsv_noeeprom_purple() rgblight_sethsv_noeeprom(HSV_PURPLE)
#define rgblight_sethsv_noeeprom_magenta() rgblight_sethsv_noeeprom(HSV_MAGENTA)
#define rgblight_sethsv_noeeprom_pink() rgblight_sethsv_noeeprom(HSV_PINK)

/*                            SET HSV List                            */
#define rgblight_sethsv_white_at(at) rgblight_sethsv_at(HSV_WHITE, at)
#define rgblight_sethsv_red_at(at) rgblight_sethsv_at(HSV_RED, at)
#define rgblight_sethsv_coral_at(at) rgblight_sethsv_at(HSV_CORAL, at)
#define rgblight_sethsv_orange_at(at) rgblight_sethsv_at(HSV_ORANGE, at)
#define rgblight_sethsv_goldenrod_at(at) rgblight_sethsv_at(HSV_GOLDENROD, at)
#define rgblight_sethsv_gold_at(at) rgblight_sethsv_at(HSV_GOLD, at)
#define rgblight_sethsv_yellow_at(at) rgblight_sethsv_at(HSV_YELLOW, at)
#define rgblight_sethsv_chartreuse_at(at) rgblight_sethsv_at(HSV_CHARTREUSE, at)
#define rgblight_sethsv_green_at(at) rgblight_sethsv_at(HSV_GREEN, at)
#define rgblight_sethsv_springgreen_at(at) rgblight_sethsv_at(HSV_SPRINGGREEN, at)
#define rgblight_sethsv_turquoise_at(at) rgblight_sethsv_at(HSV_TURQUOISE, at)
#define rgblight_sethsv_teal_at(at) rgblight_sethsv_at(HSV_TEAL, at)
#define rgblight_sethsv_cyan_at(at) rgblight_sethsv_at(HSV_CYAN, at)
#define rgblight_sethsv_azure_at(at) rgblight_sethsv_at(HSV_AZURE, at)
#define rgblight_sethsv_blue_at(at) rgblight_sethsv_at(HSV_BLUE, at)
#define rgblight_sethsv_purple_at(at) rgblight_sethsv_at(HSV_PURPLE, at)
#define rgblight_sethsv_magenta_at(at) rgblight_sethsv_at(HSV_MAGENTA, at)
#define rgblight_sethsv_pink_at(at) rgblight_sethsv_at(HSV_PINK, at)
