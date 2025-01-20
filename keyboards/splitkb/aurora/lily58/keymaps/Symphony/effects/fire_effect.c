#include "fire_effect.h"
#include "quantum.h"
#include "print.h"
#include <stdlib.h>

#define FIRE_LED_COUNT 5 // Apply effect to LEDs 0-4

// Fire color palette (RGB values)
const uint8_t fire_palette[][3] = {
    {128, 17, 0},   // Dark Red
    {182, 34, 3},   // Deep Orange-Red
    {215, 53, 2},   // Fiery Red-Orange
    {252, 100, 0},  // Molten Orange
    {255, 117, 0},  // Bright Ember Orange
    {250, 192, 0}   // Bright Yellow
};

#define FIRE_PALETTE_SIZE (sizeof(fire_palette) / sizeof(fire_palette[0]))

// Track the current color index of each LED
uint8_t fire_led_colors[FIRE_LED_COUNT] = {0};

// Function to transition fire effect over time
void fire_effect_update(void) {
    for (uint8_t i = 0; i < FIRE_LED_COUNT; i++) {
        // Randomly change color every few frames
        if (rand() % 20 == 0) {
            fire_led_colors[i] = rand() % FIRE_PALETTE_SIZE;
        }

        // Get target color
        uint8_t target_color_index = fire_led_colors[i];
        uint8_t r = fire_palette[target_color_index][0];
        uint8_t g = fire_palette[target_color_index][1];
        uint8_t b = fire_palette[target_color_index][2];

        // Apply effect to both master and slave halves
        rgb_matrix_set_color(i, r, g, b);
        rgb_matrix_set_color(i + DRIVER_LED_TOTAL / 2, r, g, b);
    }
}

// Initialize randomness (call once in `matrix_init_user`)
void fire_effect_init(void) {
    srand(timer_read());
}

