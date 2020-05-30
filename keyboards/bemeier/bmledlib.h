/*
Copyright 2019 bemeier

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

// This may belong to the "/user" space...

#pragma once

#ifndef BMLED_SMOOTH_NVALS
  #define BMLED_SMOOTH_NVALS 1
#endif

#ifndef BMLED_SMOOTH_INTERVAL
  #define BMLED_SMOOTH_INTERVAL 15 
#endif

typedef struct {
    bool wrap_around_fade;
    float current_value;
    float target_value;
    float max_value;
    float min_value;
    float smooth_param;
} bmled_smooth;

static uint16_t bmled_smooth_last_update;

uint8_t bmled_get_val(uint8_t val);
float bmled_get_val_f(uint8_t val);
void bmled_smooth_init(uint8_t val, uint8_t start_val, float start_target, uint8_t min, uint8_t max, float param, bool wrap);
void bmled_smooth_add_target(uint8_t val, int add);
void bmled_smooth_add_target_f(uint8_t val, float add);
void bmled_smooth_set_target(uint8_t val, uint8_t target);
void bmled_smooth_set_target_f(uint8_t val, float target);
void bmled_set(uint8_t val, uint8_t target);
void bmled_set_f(uint8_t val, float target);
float bmled_get_dist(uint8_t val);
bool bmled_smooth_update(void);

bmled_smooth bmled_smooth_vals[BMLED_SMOOTH_NVALS];

// Initialize a smooth value
void bmled_smooth_init(uint8_t val, uint8_t start_val, float start_target, uint8_t min, uint8_t max, float param, bool wrap) {
  if (val >= BMLED_SMOOTH_NVALS) return;
  bmled_smooth_last_update = timer_read();
  bmled_smooth_vals[val].current_value = (float) start_val;
  bmled_smooth_vals[val].target_value = start_target;
  bmled_smooth_vals[val].min_value = (float) min;
  bmled_smooth_vals[val].max_value = (float) max;
  bmled_smooth_vals[val].smooth_param = param;
  bmled_smooth_vals[val].wrap_around_fade = wrap;
}

// update all smoothed values
bool bmled_smooth_update(void) {
  if (timer_elapsed(bmled_smooth_last_update) > BMLED_SMOOTH_INTERVAL) {
    bmled_smooth_last_update = timer_read();
    for (uint8_t valIdx = 0; valIdx < BMLED_SMOOTH_NVALS; valIdx++) {
	  float dist = bmled_get_dist(valIdx);
	  if (fabs(dist) <= 1.25) continue;
      float change = bmled_smooth_vals[valIdx].smooth_param * dist;
      float magnitude = fmin(fmax(fabs(change), 0.2), 6.0);
	  change = magnitude * change/fabs(change);
      bmled_smooth_vals[valIdx].current_value = bmled_smooth_vals[valIdx].current_value - change;
      if (bmled_smooth_vals[valIdx].current_value > bmled_smooth_vals[valIdx].max_value) {
		bmled_smooth_vals[valIdx].current_value = bmled_smooth_vals[valIdx].current_value - bmled_smooth_vals[valIdx].max_value;
	  }
	  if (bmled_smooth_vals[valIdx].current_value < bmled_smooth_vals[valIdx].min_value) {
		bmled_smooth_vals[valIdx].current_value = bmled_smooth_vals[valIdx].max_value - bmled_smooth_vals[valIdx].current_value;
	  }
    }
    return true;
  }
  return false;
}

void bmled_smooth_add_target(uint8_t val, int add) {
  bmled_smooth_add_target_f(val, (float) add);
}

void bmled_smooth_add_target_f(uint8_t val, float add) {
  if (val >= BMLED_SMOOTH_NVALS) return;
  float new_val = bmled_smooth_vals[val].target_value + add;
  if (bmled_smooth_vals[val].wrap_around_fade) {
    bmled_smooth_vals[val].target_value = fmod(new_val, 255.0);
  } else {
    if (new_val > bmled_smooth_vals[val].max_value) bmled_smooth_vals[val].target_value = bmled_smooth_vals[val].max_value;
    else if (new_val < bmled_smooth_vals[val].min_value) bmled_smooth_vals[val].target_value = bmled_smooth_vals[val].min_value;
    else bmled_smooth_vals[val].target_value = (float) new_val;
  }
}

void bmled_set(uint8_t val, uint8_t target) {
    bmled_set_f(val, (float) target);
}

void bmled_set_f(uint8_t val, float target) {
  if (val >= BMLED_SMOOTH_NVALS) return;
  if (target > bmled_smooth_vals[val].max_value) bmled_smooth_vals[val].current_value = bmled_smooth_vals[val].max_value;
  else if (target < bmled_smooth_vals[val].min_value) bmled_smooth_vals[val].current_value = bmled_smooth_vals[val].min_value;
  else bmled_smooth_vals[val].current_value = target;
  bmled_smooth_vals[val].target_value = bmled_smooth_vals[val].current_value;
}

void bmled_smooth_set_target(uint8_t val, uint8_t target) {
    bmled_smooth_set_target_f(val, (float) target);
}
    
void bmled_smooth_set_target_f(uint8_t val, float target) {
  if (val >= BMLED_SMOOTH_NVALS) return;
  if (target > bmled_smooth_vals[val].max_value) bmled_smooth_vals[val].target_value = bmled_smooth_vals[val].max_value;
  else if (target < bmled_smooth_vals[val].min_value) bmled_smooth_vals[val].target_value = bmled_smooth_vals[val].min_value;
  else bmled_smooth_vals[val].target_value = target;
}


float bmled_get_target_f(uint8_t val) {
  if (val >= BMLED_SMOOTH_NVALS) return 0;
  return bmled_smooth_vals[val].target_value;
}

uint8_t bmled_get_target(uint8_t val) {
  return (uint8_t) bmled_get_target_f(val);
}

float bmled_get_dist(uint8_t val) {
  if (val >= BMLED_SMOOTH_NVALS) return 0;
  int delta = bmled_smooth_vals[val].current_value-bmled_smooth_vals[val].target_value;
  if (bmled_smooth_vals[val].wrap_around_fade && bmled_smooth_vals[val].max_value/2.0 < fabs(delta)) {
    return -(bmled_smooth_vals[val].max_value * delta/fabs(delta) - delta);
  }
  return delta;
}

uint8_t bmled_get_val(uint8_t val) {
  return (uint8_t) bmled_get_val_f(val);
}

float bmled_get_val_f(uint8_t val) {
  if (val >= BMLED_SMOOTH_NVALS) return 0.0;
  return bmled_smooth_vals[val].current_value;
}
