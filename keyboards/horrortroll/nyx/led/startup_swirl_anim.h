#include <string.h>
#include <math.h>
#include <lib/lib8tion/lib8tion.h>

#define LED_TRAIL 10

static int8_t top = 0;
static int8_t bottom = MATRIX_ROWS - 1;
static int8_t left = 0;
static int8_t right = MATRIX_COLS - 1;
static int8_t dir = 1;

static int8_t i = 0;
static int8_t j = 0;

static bool traverse = true;

static uint8_t v_values[RGB_MATRIX_LED_COUNT] = {0};

static void traverse_matrix(void) {
    if (dir == 1) {
        // moving left->right
        i++;
        // Since we have traversed the whole first
        // row, move down to the next row.
        if (i > right) {
            ++top;
            dir = 2;
            j = top;
            i -= 1;
        }
    } else if (dir == 2) {
        // moving top->bottom
        j++;
        // Since we have traversed the whole last
        // column, move left to the previous column.
        if (j > bottom) {
            --right;
            dir = 3;
            i = right;
            j -= 1;
        }
    } else if (dir == 3) {
        // moving right->left
        i--;
        // Since we have traversed the whole last
        // row, move up to the previous row.
        if (i < left) {
            --bottom;
            dir = 4;
            j = bottom;
            i += 1;
        }
    } else if (dir == 4) {
        // moving bottom->up
        j--;
        // Since we have traversed the whole first
        // col, move right to the next column.
        if (j < top) {
            ++left;
            dir = 1;
            i = left;
            j += 1;
        }
    }
}

static void swirl_set_color(HSV hsv) {
    uint8_t index = g_led_config.matrix_co[j][i];

    if(index != NO_LED){
        v_values[index] = 255;
    }

    for(uint8_t v = 0; v < RGB_MATRIX_LED_COUNT; v++)
    {
        if(index != v) {
            if(v_values[v] >= 20)
                v_values[v] -= 20;
            else
                v_values[v] = 0;
        }
        hsv.v =  v_values[v];
        RGB rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(v, rgb.r, rgb.g, rgb.b);
    }

    traverse_matrix();

    if (!(top <= bottom && left <= right)) {
        eeprom_read_block(&rgb_matrix_config, EECONFIG_RGB_MATRIX, sizeof(rgb_matrix_config));
        rgb_matrix_mode_noeeprom(rgb_matrix_config.mode);
        return;
    }
}

static bool STARTUP_SWIRL_ANIM(effect_params_t* params) {
    HSV      hsv = rgb_matrix_config.hsv;
    uint8_t time = scale16by8(g_rgb_timer, qadd8(24, 1));
    hsv.h        = time;
    RGB      rgb = hsv_to_rgb(hsv);

    if (traverse) {
        swirl_set_color(hsv);
    }
    traverse = !traverse;
    return false;

    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    for (int i = led_min; i < led_max; i++) {
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b); // Clear matrix just in case
    }

    return rgb_matrix_check_finished_leds(led_max);
}
