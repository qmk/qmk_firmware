/* Copyright 2020 grid
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

#define BACKLIGHT_PIN B6
#define BACKLIGHT_BREATHING
#define BACKLIGHT_LEVELS 1
#define BREATHING_PERIOD 5
#define BACKLIGHT_ON_STATE 1


/*  battery level detect */
#define BATTERY_PIN 10 //ADC9 (dont know why pin10)
// #define BATTERY_POLL 20000 //about 7s
// #define BATTERY_POLL 2000 //about 0.7s
// #define BATTERY_POLL 10000 //about 3.5s?
#define BASIC_CNT 2000 //about 2.5s
#define BATTERY_POLL 240 //x times of BASIC_CNT
// #define MAX_VOLTAGE 2.946
// #define MIN_VOLTAGE 2.034
#define MAX_VOLTAGE 2.8
#define MIN_VOLTAGE 2.034

// #define BAT_LEVEL_102 2900
// #define BAT_LEVEL_100 2895
// #define BAT_LEVEL_90 2862
// #define BAT_LEVEL_80 2806
// #define BAT_LEVEL_70 2757
// #define BAT_LEVEL_60 2715
// #define BAT_LEVEL_50 2680
// #define BAT_LEVEL_40 2659
// #define BAT_LEVEL_30 2645
// #define BAT_LEVEL_20 2617
// #define BAT_LEVEL_10 2581
// #define BAT_LEVEL_5 2455
// #define BAT_LEVEL_0 2034

// #define BAT_LEVEL_110 2904
// #define BAT_LEVEL_100 2876
// #define BAT_LEVEL_90 2827
// #define BAT_LEVEL_80 2770
// #define BAT_LEVEL_70 2721
// #define BAT_LEVEL_60 2679
// #define BAT_LEVEL_50 2644
// #define BAT_LEVEL_40 2623
// #define BAT_LEVEL_30 2609
// #define BAT_LEVEL_20 2581
// #define BAT_LEVEL_10 2546
// #define BAT_LEVEL_5 2420
// #define BAT_LEVEL_0 1999

// #define BAT_LEVEL_110 3700
// #define BAT_LEVEL_100 3600
// #define BAT_LEVEL_90 3500
// #define BAT_LEVEL_80 3360
// #define BAT_LEVEL_70 3200
// #define BAT_LEVEL_60 3000
// #define BAT_LEVEL_50 2850
// #define BAT_LEVEL_40 2710
// #define BAT_LEVEL_30 2590
// #define BAT_LEVEL_20 2450
// #define BAT_LEVEL_10 2300
// #define BAT_LEVEL_5 2190
// #define BAT_LEVEL_0 2000

#define BAT_LEVEL_110 2904
#define BAT_LEVEL_100 2876
#define BAT_LEVEL_90 2827
#define BAT_LEVEL_80 2770
#define BAT_LEVEL_70 2721
#define BAT_LEVEL_60 2672
#define BAT_LEVEL_50 2623
#define BAT_LEVEL_40 2574
#define BAT_LEVEL_30 2525
#define BAT_LEVEL_20 2476
#define BAT_LEVEL_10 2279
#define BAT_LEVEL_5 2420
#define BAT_LEVEL_0 2069

/*  power saving counter  */
// #define SLEEP_WAIT 20
#define SLEEP_WAIT 1000


#define OUTPUT_AUTO_ENABLE

// place overrides here

#define BLE_ENABLE
#define MAX_PWR
#define BLE_BATTERY_REPORT