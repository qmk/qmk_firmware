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

/*                            SET HSV List                            */
/*   If you're doing layer indication, this is best, as it won't      */
/*   write to the eeprom, since it's limited (very high value).       */
/*   If you want to use modes with this (since you can), then you     */
/*   want to use rgblight_mode_noeeprom(x) instead.                   */
#define rgblight_sethsv_noeeprom_white() rgblight_sethsv_noeeprom(HSV_WHITE)
#define rgblight_sethsv_noeeprom_red() rgblight_sethsv_noeeprom(HSV_RED)
#define rgblight_sethsv_noeeprom_orange() rgblight_sethsv_noeeprom(HSV_ORANGE)
#define rgblight_sethsv_noeeprom_goldenrod() rgblight_sethsv_noeeprom(HSV_GOLDENROD)
#define rgblight_sethsv_noeeprom_yellow() rgblight_sethsv_noeeprom(HSV_YELLOW)
#define rgblight_sethsv_noeeprom_chartreuse() rgblight_sethsv_noeeprom(HSV_CHARTREUSE)
#define rgblight_sethsv_noeeprom_green() rgblight_sethsv_noeeprom(HSV_GREEN)
#define rgblight_sethsv_noeeprom_turquoise() rgblight_sethsv_noeeprom(HSV_TURQUOISE)
#define rgblight_sethsv_noeeprom_teal() rgblight_sethsv_noeeprom(HSV_TEAL)
#define rgblight_sethsv_noeeprom_cyan() rgblight_sethsv_noeeprom(HSV_CYAN)
#define rgblight_sethsv_noeeprom_blue() rgblight_sethsv_noeeprom(HSV_BLUE)
#define rgblight_sethsv_noeeprom_purple() rgblight_sethsv_noeeprom(HSV_PURPLE)
#define rgblight_sethsv_noeeprom_magenta() rgblight_sethsv_noeeprom(HSV_MAGENTA)
#define rgblight_sethsv_noeeprom_pink() rgblight_sethsv_noeeprom(HSV_PINK)
