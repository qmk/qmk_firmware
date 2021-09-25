

#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint8_t bits[256 / 8];
} keyboard_parse_result_t;

typedef struct {
    uint16_t button;
    int16_t  x;
    int16_t  y;
    int16_t  v;
    int16_t  h;
    uint16_t undefined;
} mouse_parse_result_t;

bool parse_report(uint8_t interface, uint8_t const *report, uint8_t len);

// default hooks are defined in keyboard_quantizer.c
void keyboard_report_hook(keyboard_parse_result_t const *report);
void mouse_report_hook(mouse_parse_result_t const *report);
void system_report_hook(uint16_t report);
void consumer_report_hook(uint16_t report);

