/*
 * Copyright (c) 2023 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "btstack_config.h"

#ifdef HAVE_BTSTACK_STDIN

#include "btstack_stdin.h"
#include "btstack_run_loop.h"
#include "pico/stdio.h"

static btstack_data_source_t stdin_data_source;
static void (*stdin_handler)(char c);

// Data source callback, return any character received
static void btstack_stdin_process(__unused struct btstack_data_source *ds, __unused btstack_data_source_callback_type_t callback_type){
    if (stdin_handler) {
        while(true) {
            int c = getchar_timeout_us(0);
            if (c == PICO_ERROR_TIMEOUT) return;
            (*stdin_handler)(c);
        }
    }
}

void on_chars_available_callback(__unused void *param) {
    btstack_run_loop_poll_data_sources_from_irq();
}

// Test code calls this if HAVE_BTSTACK_STDIN is defined and it wants key presses
void btstack_stdin_setup(void (*handler)(char c)) {
    if (stdin_handler) {
        return;
    }

	// set handler
	stdin_handler = handler;

	// set up polling data_source
	btstack_run_loop_set_data_source_handler(&stdin_data_source, &btstack_stdin_process);
	btstack_run_loop_enable_data_source_callbacks(&stdin_data_source, DATA_SOURCE_CALLBACK_POLL);
	btstack_run_loop_add_data_source(&stdin_data_source);

    stdio_set_chars_available_callback(on_chars_available_callback, NULL);
}

// Deinit everything
void btstack_stdin_reset(void){
    if (!stdin_handler) {
        return;
    }
    stdio_set_chars_available_callback(NULL, NULL);
    stdin_handler = NULL;
    btstack_run_loop_remove_data_source(&stdin_data_source);
}

#endif