// Copyright 2022 Jose Pablo Ramirez (@jpe230)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "qp_lvgl.h"
#include "deferred_exec.h"
#include "lvgl.h"

typedef struct lvgl_state_t {
    uint8_t                fnc_id;                  // Ideally this should be the pointer of the function to run
    uint16_t               delay_ms;
    deferred_token         defer_token;
} lvgl_state_t;

static deferred_executor_t lvgl_executors[2] = {0}; // For lv_tick_inc and lv_task_handler
static lvgl_state_t        lvgl_states[2]    = {0}; // For lv_tick_inc and lv_task_handler

painter_device_t selected_display;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter LVGL Integration Internal: qp_lvgl_flush

void qp_lvgl_flush(lv_disp_drv_t * disp, const lv_area_t * area, lv_color_t * color_p) {
    uint32_t number_pixels = (area->x2 - area->x1 + 1) * (area->y2 - area->y1 + 1);
    qp_viewport(selected_display, area->x1, area->y1, area->x2, area->y2);
    qp_pixdata(selected_display, (void *)color_p, number_pixels);
    qp_flush(selected_display);
    lv_disp_flush_ready(disp);
}

static uint32_t tick_task_callback(uint32_t trigger_time, void *cb_arg) {
    lvgl_state_t *state = (lvgl_state_t *)cb_arg;

    switch (state->fnc_id)
    {
        case 0:
            lv_tick_inc(1);
            break;
        case 1:
            lv_task_handler();
            break;

        default:
            break;
    }

    // The tasks should run indefinitely
    return state->delay_ms;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter LVGL Integration API: qp_lvgl_start

bool qp_lvgl_start(painter_device_t device) {
    qp_dprintf("qp_lvgl_start: entry\n");

    struct painter_driver_t *driver = (struct painter_driver_t *)device;
    if (!driver->validate_ok) {
        qp_dprintf("qp_lvgl_start: fail (validation_ok == false)\n");
        return false;
    }

    selected_display = device;

    // Setting up the tasks
    lvgl_state_t *lv_tick_inc_state = &lvgl_states[0];
    lv_tick_inc_state->fnc_id = 0;
    lv_tick_inc_state->delay_ms = 1;
    lv_tick_inc_state->defer_token = defer_exec_advanced(lvgl_executors, 2, 1, tick_task_callback, lv_tick_inc_state);

    if (lv_tick_inc_state->defer_token == INVALID_DEFERRED_TOKEN) {
        qp_dprintf("qp_lvgl_start_tasks: fail (could not set up qp_lvgl executor)\n");
        return false;
    }

    lvgl_state_t *lv_task_handler_state = &lvgl_states[1];
    lv_task_handler_state->fnc_id = 1;
    lv_task_handler_state->delay_ms = 5;
    lv_task_handler_state->defer_token = defer_exec_advanced(lvgl_executors, 2, 5, tick_task_callback, lv_task_handler_state);

    if (lv_task_handler_state->defer_token == INVALID_DEFERRED_TOKEN) {
        qp_dprintf("qp_lvgl_start_tasks: fail (could not set up qp_lvgl executor)\n");
        return false;
    }

    // Init LVGL
    lv_init();

    // Setting up lvgl display buffer
    static lv_disp_draw_buf_t draw_buf;
    static lv_color_t color_buffer[QUANTUM_PAINTER_LVGL_DISPLAY_WIDTH*(QUANTUM_PAINTER_LVGL_DISPLAY_HEIGHT / 10)];                       /*Declare a buffer for 1/10 screen size*/
    lv_disp_draw_buf_init(&draw_buf, color_buffer, NULL, QUANTUM_PAINTER_LVGL_DISPLAY_WIDTH*(QUANTUM_PAINTER_LVGL_DISPLAY_HEIGHT / 10)); /*Initialize the display buffer.*/

    // Setting up display driver
    static lv_disp_drv_t disp_drv;                            /*Descriptor of a display driver*/
    lv_disp_drv_init(&disp_drv);                              /*Basic initialization*/
    disp_drv.flush_cb = qp_lvgl_flush;                        /*Set your driver function*/
    disp_drv.draw_buf = &draw_buf;                            /*Assign the buffer to the display*/
    disp_drv.hor_res = QUANTUM_PAINTER_LVGL_DISPLAY_WIDTH;    /*Set the horizontal resolution of the display*/
    disp_drv.ver_res = QUANTUM_PAINTER_LVGL_DISPLAY_HEIGHT;   /*Set the vertical resolution of the display*/
    lv_disp_drv_register(&disp_drv);                          /*Finally register the driver*/

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter LVGL Integration API: qp_lvgl_stop_tasks

void qp_lvgl_stop_tasks() {
    for (int i = 0; i < 2; ++i) {
        cancel_deferred_exec_advanced(lvgl_executors, 2, lvgl_states[i].defer_token);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantum Painter LVGL Integration Internal: qp_lvgl_internal_tick

void qp_lvgl_internal_tick(void) {
    static uint32_t last_lvgl_exec = 0;
    deferred_exec_advanced_task(lvgl_executors, 2, &last_lvgl_exec);
}
