/* Copyright 2024 Morgan Newell Sun
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

#ifdef POINTING_DEVICE_DRAGSCROLL_ENABLE

#    include <stdlib.h>
#    include <math.h>
#    include "host_driver.h"
#    include "pointing_device.h"
#    include "pointing_device_dragscroll.h"
#    include "send_string.h"
#    include "timer.h"
#    include "usb_descriptor_common.h"

/* implement a simple ring buffer for smoothing hires scrolling */

#    ifdef POINTING_DEVICE_HIRES_SCROLL_ENABLE
typedef struct {
    float  items[DRAGSCROLL_SMOOTHING];
    float  current_sum;
    size_t current_size;
    size_t next_index;
} ring_buffer_t;

static void ring_buffer_reset(ring_buffer_t* rb) {
    rb->current_sum  = 0;
    rb->current_size = 0;
    rb->next_index   = 0;
}

static void ring_buffer_push(ring_buffer_t* rb, float item) {
    if (rb->current_size == DRAGSCROLL_SMOOTHING) {
        rb->current_sum -= rb->items[rb->next_index];
    } else {
        rb->current_size++;
    }
    rb->items[rb->next_index] = item;
    rb->current_sum += item;
    rb->next_index = (rb->next_index + 1) % DRAGSCROLL_SMOOTHING;
}

static float ring_buffer_mean(ring_buffer_t* rb) {
    return rb->current_size > 0 ? rb->current_sum / rb->current_size : 0;
}
#    endif

/* stuff to keep track of dragscroll state */

enum dragscroll_axis_snapping_states {
    AXIS_SNAPPING_UNDECIDED = 0,
    AXIS_SNAPPING_HORIZONTAL,
    AXIS_SNAPPING_VERTICAL,
    AXIS_SNAPPING_OFF,
};

typedef struct {
    float accumulator_h;
    float accumulator_v;
    float rounding_error_h;
    float rounding_error_v;
    float axis_snapping_deviation;
#    ifdef POINTING_DEVICE_HIRES_SCROLL_ENABLE
    ring_buffer_t smoothing_buffer_h;
    ring_buffer_t smoothing_buffer_v;
#    endif
    uint32_t last_movement_time;
    size_t   axis_snapping_state;
    bool     active;
} dragscroll_state_t;

uint32_t last_scroll_time = 0; // use a single shared timer for throttling

dragscroll_state_t dragscroll_state            = {0};
report_mouse_t     pre_dragscroll_mouse_report = {0};

#    if defined(SPLIT_POINTING_ENABLE) && defined(POINTING_DEVICE_COMBINED) && !defined(DRAGSCROLL_APPLIED_AFTER_POINTING_DEVICE_TASK_KB)
dragscroll_state_t dragscroll_state_right            = {0};
report_mouse_t     pre_dragscroll_mouse_report_right = {0};
#    endif

#    ifdef DRAGSCROLL_ACCELERATION
float acceleration_const_p;
float acceleration_const_q;
float acceleration_const_r;
#        ifdef SEND_STRING_ENABLE
bool  acceleration_scale_calibration_is_on = false;
float acceleration_scale_calibration_mean  = 0;
long  acceleration_scale_calibration_count = 0;
float acceleration_scale_calibration_max   = 0;
#        endif
#    endif

/* core implementation of drag scroll */

static void dragscroll_reset_task(dragscroll_state_t* d) {
    d->accumulator_h           = 0;
    d->accumulator_v           = 0;
    d->rounding_error_h        = 0;
    d->rounding_error_v        = 0;
    d->axis_snapping_deviation = 0;
#    ifdef POINTING_DEVICE_HIRES_SCROLL_ENABLE
    ring_buffer_reset(&(d->smoothing_buffer_h));
    ring_buffer_reset(&(d->smoothing_buffer_v));
#    endif
    d->last_movement_time = timer_read32();
    if (d->axis_snapping_state != AXIS_SNAPPING_OFF) {
        d->axis_snapping_state = AXIS_SNAPPING_UNDECIDED;
    }
}

static void dragscroll_accumulate_task(dragscroll_state_t* d, report_mouse_t* mouse_report) {
    if (!(d->active)) {
        return;
    }
    float delta_h;
    float delta_v;

    // reset drag scroll if the pointing device has been idle for too long
    if (mouse_report->x == 0 && mouse_report->y == 0) {
        if (timer_elapsed32(d->last_movement_time) > DRAGSCROLL_TIMEOUT_MS) {
            dragscroll_reset_task(d);
        }
        return;
    }
    d->last_movement_time = timer_read32();

    // scale hires scrolling so that hires and normal scrolling have the same speed
#    ifdef POINTING_DEVICE_HIRES_SCROLL_ENABLE
    if (is_hires_scroll_on()) {
        delta_h = ((float)(mouse_report->x)) * pointing_device_get_hires_scroll_resolution();
        delta_v = ((float)(mouse_report->y)) * pointing_device_get_hires_scroll_resolution();
    }
#    endif

    // update accumulators
    d->accumulator_h += delta_h;
    d->accumulator_v += delta_v;

    // zero out the mouse report
    mouse_report->x = 0;
    mouse_report->y = 0;
}

static void dragscroll_scroll_task(dragscroll_state_t* d, report_mouse_t* mouse_report) {
    if (!(d->active)) {
        return;
    }

    float h;
    float v;

    // apply smoothing to hires scrolling - don't apply it to normal scrolling since it makes normal scrolling feel unresponsive
#    ifdef POINTING_DEVICE_HIRES_SCROLL_ENABLE
    if (is_hires_scroll_on()) {
        ring_buffer_push(&(d->smoothing_buffer_h), d->accumulator_h);
        ring_buffer_push(&(d->smoothing_buffer_v), d->accumulator_v);
        h = ring_buffer_mean(&(d->smoothing_buffer_h));
        v = ring_buffer_mean(&(d->smoothing_buffer_v));
    } else {
#    endif
        h = d->accumulator_h;
        v = d->accumulator_v;
#    ifdef POINTING_DEVICE_HIRES_SCROLL_ENABLE
    }
#    endif

    // zero out the accumulators
    d->accumulator_h = 0;
    d->accumulator_v = 0;

    // apply axis snapping
    switch (d->axis_snapping_state) {
        case AXIS_SNAPPING_OFF:
            break;
        case AXIS_SNAPPING_UNDECIDED:
            // we don't know which axis to snap since the user hasn't moved the pointing device
            if (abs(h) > abs(v)) {
                // snap to horizontal axis
                v                      = 0;
                d->axis_snapping_state = AXIS_SNAPPING_HORIZONTAL;
            } else if (abs(h) < abs(v)) {
                // snap to vertical axis
                h                      = 0;
                d->axis_snapping_state = AXIS_SNAPPING_VERTICAL;
            }
            break;
        case AXIS_SNAPPING_HORIZONTAL:
            d->axis_snapping_deviation += v;
            if (d->axis_snapping_deviation > 0) {
                d->axis_snapping_deviation -= abs(h) * DRAGSCROLL_AXIS_SNAPPING_RATIO;
                d->axis_snapping_deviation = d->axis_snapping_deviation < 0 ? 0 : d->axis_snapping_deviation;
            } else if (d->axis_snapping_deviation < 0) {
                d->axis_snapping_deviation += abs(h) * DRAGSCROLL_AXIS_SNAPPING_RATIO;
                d->axis_snapping_deviation = d->axis_snapping_deviation > 0 ? 0 : d->axis_snapping_deviation;
            }
            if (abs(d->axis_snapping_deviation) > DRAGSCROLL_AXIS_SNAPPING_THRESHOLD) {
                // switch to the vertical axis
                h                   = 0;
                d->rounding_error_h = 0;
                d->rounding_error_v = 0;
#    ifdef POINTING_DEVICE_HIRES_SCROLL_ENABLE
                ring_buffer_reset(&(d->smoothing_buffer_h));
                ring_buffer_reset(&(d->smoothing_buffer_v));
#    endif
                d->axis_snapping_state     = AXIS_SNAPPING_VERTICAL;
                d->axis_snapping_deviation = 0;
            } else {
                v = 0;
            }
            break;
        case AXIS_SNAPPING_VERTICAL:
            d->axis_snapping_deviation += h;
            if (d->axis_snapping_deviation > 0) {
                d->axis_snapping_deviation -= abs(v) * DRAGSCROLL_AXIS_SNAPPING_RATIO;
                d->axis_snapping_deviation = d->axis_snapping_deviation < 0 ? 0 : d->axis_snapping_deviation;
            } else if (d->axis_snapping_deviation < 0) {
                d->axis_snapping_deviation += abs(v) * DRAGSCROLL_AXIS_SNAPPING_RATIO;
                d->axis_snapping_deviation = d->axis_snapping_deviation > 0 ? 0 : d->axis_snapping_deviation;
            }
            if (abs(d->axis_snapping_deviation) > DRAGSCROLL_AXIS_SNAPPING_THRESHOLD) {
                // switch to the horizontal axis
                v                   = 0;
                d->rounding_error_h = 0;
                d->rounding_error_v = 0;
#    ifdef POINTING_DEVICE_HIRES_SCROLL_ENABLE
                ring_buffer_reset(&(d->smoothing_buffer_h));
                ring_buffer_reset(&(d->smoothing_buffer_v));
#    endif
                d->axis_snapping_state     = AXIS_SNAPPING_HORIZONTAL;
                d->axis_snapping_deviation = 0;
            } else {
                h = 0;
            }
            break;
    }

        // apply acceleration
#    ifdef DRAGSCROLL_ACCELERATION
#        if defined(DRAGSCROLL_ACCELERATION_WHEN_HIRES_SCROLLING_IS_ON) && !defined(DRAGSCROLL_ACCELERATION_WHEN_HIRES_SCROLLING_IS_OFF)
    if (is_hires_scroll_on()) {
#        elif !defined(DRAGSCROLL_ACCELERATION_WHEN_HIRES_SCROLLING_IS_ON) && defined(DRAGSCROLL_ACCELERATION_WHEN_HIRES_SCROLLING_IS_OFF)
    if (!is_hires_scroll_on()) {
#        endif
        if (!(h == 0 && v == 0)) {
            // v_out = p * square(min(v_in - r, 0)) + q * (v_in - r) + r
            float speed        = sqrt(h * h + v * v);
            float speed_offset = speed - acceleration_const_r;
            float scale_factor = acceleration_const_q * speed_offset + acceleration_const_r;
            if (speed_offset < 0) {
                scale_factor += acceleration_const_p * speed_offset * speed_offset;
            }
            scale_factor /= speed;
            h *= scale_factor;
            v *= scale_factor;
#        ifdef SEND_STRING_ENABLE
            if (acceleration_scale_calibration_is_on) {
                acceleration_scale_calibration_count += 1;
                acceleration_scale_calibration_mean += (speed - acceleration_scale_calibration_mean) / acceleration_scale_calibration_count;
                acceleration_scale_calibration_max = speed > acceleration_scale_calibration_max ? speed : acceleration_scale_calibration_max;
            }
#        endif
        }
#        if defined(DRAGSCROLL_ACCELERATION_WHEN_HIRES_SCROLLING_IS_ON) && !defined(DRAGSCROLL_ACCELERATION_WHEN_HIRES_SCROLLING_IS_OFF)
    }
#        elif !defined(DRAGSCROLL_ACCELERATION_WHEN_HIRES_SCROLLING_IS_ON) && defined(DRAGSCROLL_ACCELERATION_WHEN_HIRES_SCROLLING_IS_OFF)
    }
#        endif
#    endif

    // apply scaling
    h *= DRAGSCROLL_MULTIPLIER_H;
    v *= DRAGSCROLL_MULTIPLIER_V;

    // save rounding errors
    h += d->rounding_error_h;
    v += d->rounding_error_v;
    mouse_report->h     = (mouse_hv_report_t)h;
    mouse_report->v     = (mouse_hv_report_t)v;
    d->rounding_error_h = h - mouse_report->h;
    d->rounding_error_v = v - mouse_report->v;
}

#    ifdef DRAGSCROLL_ACCELERATION
static inline void set_acceleration_consts(float blend, float scale) {
    // multiply by DRAGSCROLL_THROTTLE_MS so that acceleration behaves the same when DRAGSCROLL_THROTTLE_MS is changed
    // potential todo: also multiply by CPI so that acceleration behaves the same when CPI is changed
    scale *= DRAGSCROLL_THROTTLE_MS;
    scale                = scale < 0 ? 0 : scale;
    blend                = blend < 0 ? 0 : blend;
    blend                = blend > 1 ? 1 : blend;
    acceleration_const_p = blend / scale;
    acceleration_const_q = blend + 1;
    acceleration_const_r = scale;
}
#    endif

static void dragscroll_on_task(dragscroll_state_t* d) {
    if (d->active) {
        return;
    }
    dragscroll_reset_task(d);
    d->active = true;
}

static void dragscroll_off_task(dragscroll_state_t* d) {
    d->active = false;
}

static void dragscroll_toggle_task(dragscroll_state_t* d) {
    if (d->active) {
        dragscroll_off_task(d);
    } else {
        dragscroll_on_task(d);
    }
}

static bool is_dragscroll_on_task(dragscroll_state_t* d) {
    return d->active;
}

static void dragscroll_axis_snapping_on_task(dragscroll_state_t* d) {
    if (d->axis_snapping_state != AXIS_SNAPPING_OFF) {
        return;
    }
    d->axis_snapping_deviation = 0;
    d->axis_snapping_state     = AXIS_SNAPPING_UNDECIDED;
}

static void dragscroll_axis_snapping_off_task(dragscroll_state_t* d) {
    d->axis_snapping_state = AXIS_SNAPPING_OFF;
}

static void dragscroll_axis_snapping_toggle_task(dragscroll_state_t* d) {
    if (d->axis_snapping_state == AXIS_SNAPPING_OFF) {
        dragscroll_axis_snapping_on_task(d);
    } else {
        dragscroll_axis_snapping_off_task(d);
    }
}

static bool is_dragscroll_axis_snapping_on_task(dragscroll_state_t* d) {
    return d->axis_snapping_state != AXIS_SNAPPING_OFF;
}

/* functions used in pointing_device.c */

void dragscroll_init(void) {
#    ifdef DRAGSCROLL_ACCELERATION
    set_acceleration_consts(DRAGSCROLL_ACCELERATION_BLEND, DRAGSCROLL_ACCELERATION_SCALE);
#    endif
}

void pointing_device_dragscroll(report_mouse_t* mouse_report) {
    // save unmodified mouse report in case it's needed in pointing_device_task_user
    pre_dragscroll_mouse_report = *mouse_report;
    // accumulate on every call, but only send a nonzero mouse report periodically
    dragscroll_accumulate_task(&dragscroll_state, mouse_report);
    if (timer_elapsed32(last_scroll_time) < DRAGSCROLL_THROTTLE_MS) {
        return;
    }
    last_scroll_time = timer_read32();
    dragscroll_scroll_task(&dragscroll_state, mouse_report);
}

#    if defined(SPLIT_POINTING_ENABLE) && defined(POINTING_DEVICE_COMBINED) && !defined(DRAGSCROLL_APPLIED_AFTER_POINTING_DEVICE_TASK_KB)
void pointing_device_dragscroll_combined(report_mouse_t* mouse_report_left, report_mouse_t* mouse_report_right) {
    // save unmodified mouse report in case it's needed in pointing_device_task_user
    pre_dragscroll_mouse_report       = *mouse_report_left;
    pre_dragscroll_mouse_report_right = *mouse_report_right;
    // accumulate on every call, but only send a nonzero mouse report periodically
    dragscroll_accumulate_task(&dragscroll_state, mouse_report_left);
    dragscroll_accumulate_task(&dragscroll_state_right, mouse_report_right);
    if (timer_elapsed32(last_scroll_time) < DRAGSCROLL_THROTTLE_MS) {
        return;
    }
    last_scroll_time = timer_read32();
    dragscroll_scroll_task(&dragscroll_state, mouse_report_left);
    dragscroll_scroll_task(&dragscroll_state_right, mouse_report_right);
}
#    endif

/* functions to allow the user to control drag scroll */

#    if defined(DRAGSCROLL_ACCELERATION) && defined(SEND_STRING_ENABLE)
void start_dragscroll_acceleration_scale_calibration(void) {
    acceleration_scale_calibration_is_on = true;
    acceleration_scale_calibration_mean  = 0;
    acceleration_scale_calibration_count = 0;
    acceleration_scale_calibration_max   = 0;
}
void finish_dragscroll_acceleration_scale_calibration(void) {
    acceleration_scale_calibration_is_on = false;
    send_string("\nAverage speed: 0x");
    send_dword((uint32_t)(acceleration_scale_calibration_mean / DRAGSCROLL_THROTTLE_MS)); // divide by DRAGSCROLL_THROTTLE_MS to account for multiplication by DRAGSCROLL_THROTTLE_MS in set_acceleration_consts()
    send_string("\nMaximum speed: 0x");
    send_dword((uint32_t)(acceleration_scale_calibration_max / DRAGSCROLL_THROTTLE_MS)); // divide by DRAGSCROLL_THROTTLE_MS to account for multiplication by DRAGSCROLL_THROTTLE_MS in set_acceleration_consts()
    send_string("\n");
}
#    endif

void dragscroll_on(void) {
    dragscroll_on_task(&dragscroll_state);
}
void dragscroll_off(void) {
    dragscroll_off_task(&dragscroll_state);
}
void dragscroll_toggle(void) {
    dragscroll_toggle_task(&dragscroll_state);
}
bool is_dragscroll_on(void) {
    return is_dragscroll_on_task(&dragscroll_state);
}
void dragscroll_axis_snapping_on(void) {
    dragscroll_axis_snapping_on_task(&dragscroll_state);
}
void dragscroll_axis_snapping_off(void) {
    dragscroll_axis_snapping_off_task(&dragscroll_state);
}
void dragscroll_axis_snapping_toggle(void) {
    dragscroll_axis_snapping_toggle_task(&dragscroll_state);
}
bool is_dragscroll_axis_snapping_on(void) {
    return is_dragscroll_axis_snapping_on_task(&dragscroll_state);
}
report_mouse_t get_pre_dragscroll_mouse_report(void) {
    return pre_dragscroll_mouse_report;
}

#    if defined(SPLIT_POINTING_ENABLE) && defined(POINTING_DEVICE_COMBINED) && !defined(DRAGSCROLL_APPLIED_AFTER_POINTING_DEVICE_TASK_KB)
void dragscroll_on_right(void) {
    dragscroll_on_task(&dragscroll_state_right);
}
void dragscroll_off_right(void) {
    dragscroll_off_task(&dragscroll_state_right);
}
void dragscroll_toggle_right(void) {
    dragscroll_toggle_task(&dragscroll_state_right);
}
bool is_dragscroll_on_right(void) {
    return is_dragscroll_on_task(&dragscroll_state_right);
}
void dragscroll_axis_snapping_on_right(void) {
    dragscroll_axis_snapping_on_task(&dragscroll_state_right);
}
void dragscroll_axis_snapping_off_right(void) {
    dragscroll_axis_snapping_off_task(&dragscroll_state_right);
}
void dragscroll_axis_snapping_toggle_right(void) {
    dragscroll_axis_snapping_toggle_task(&dragscroll_state_right);
}
bool is_dragscroll_axis_snapping_on_right(void) {
    return is_dragscroll_axis_snapping_on_task(&dragscroll_state_right);
}
report_mouse_t get_pre_dragscroll_mouse_report_right(void) {
    return pre_dragscroll_mouse_report_right;
}

#    endif

#endif // POINTING_DEVICE_DRAGSCROLL_ENABLE
