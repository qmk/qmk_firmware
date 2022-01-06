/* Copyright 2021 Chris Tanaka <https://github.com/christanaka>
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

#include "clock.h"
#include QMK_KEYBOARD_H
#include "time.h"
#include <string.h>

#define _DELIMITER ","

struct tm clock_time = {0};
struct tm clock_time_prev = {0};

static bool initialized = false;
static uint32_t timer = 0;

void update_clock_host(char *data) {
  char year[10], month[10], day[10], hour[10], min[10], sec[10], ms[10];
  strcpy(year, strtok(data, _DELIMITER));
  strcpy(month, strtok(NULL, _DELIMITER));
  strcpy(day, strtok(NULL, _DELIMITER));
  strcpy(hour, strtok(NULL, _DELIMITER));
  strcpy(min, strtok(NULL, _DELIMITER));
  strcpy(sec, strtok(NULL, _DELIMITER));
  strcpy(ms, strtok(NULL, _DELIMITER));

  clock_time.tm_year = atoi(year) - 1900;
  clock_time.tm_mon = atoi(month) - 1;
  clock_time.tm_mday = atoi(day);
  clock_time.tm_hour = atoi(hour);
  clock_time.tm_min = atoi(min);
  clock_time.tm_sec = atoi(sec);
  timer = atoi(ms);

  initialized = true;
}

void update_clock_timer(void) {
  if (initialized && timer_elapsed32(timer) >= 1000) {
    timer = timer_read32();
    clock_time_prev = clock_time;
    clock_time.tm_sec += 1;
    mktime(&clock_time);
  }
}
