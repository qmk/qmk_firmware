#include <stdint.h>

#include "action.h"
#include "deferred_exec.h"
#include "digitizer.h"
#include "keycodes.h"
#include "keymap_introspection.h"
#include "mousegrid.h"
#include "print.h"
#include "progmem.h"
#include "timer.h"

#define MG_ANIMATION_SLEEP 5

typedef struct {
    // Cursor x/y position from 0...1 
    float x, y;
    // Bounding box width/height for the next cursor movement
    float scale_x, scale_y;
} mousegrid_cursor_t;

// Current active grid cursor.
static mousegrid_cursor_t mousegrid_cursor;
// If non-zero, an animation (visual feedback) of cursor bounds is active.
static uint16_t animation_since;
// If non-zero, an animation (visual feedback) of cursor bounds is active.
static uint16_t alphabet_hook_since;
static bool alphabet_x;
// How many cursors are saved 
static uint8_t undo_count;
static mousegrid_cursor_t undo_buffer[MG_UNDO_DEPTH];

const uint16_t alphabet[MG_ALPHABET_SIZE + 1] PROGMEM = {MG_ALPHABET, 0};

mousegrid_cursor_t init_cursor(void) {
    return (mousegrid_cursor_t) {
        .x = 0.5,
        .y = 0.5,
        .scale_x = 1.0,
        .scale_y = 1.0,
    };
}

void adjust_position(float *position, int8_t delta, float step) {
    *position = *position + step * (float)delta;
    if (*position < 0) {
        *position = 0;
    }
    if (*position > 1) {
        *position = 1;
    }
}

void rescale(float *scale, float ratio) {
    *scale = *scale * ratio;
    if (*scale < MG_MIN_SCALE) {
        *scale = MG_MIN_SCALE;
    }
}

mousegrid_cursor_t update(mousegrid_cursor_t cursor, int8_t dx, int8_t dy) {
    adjust_position(&(cursor.x), dx, cursor.scale_x / MG_HORIZONTAL_GRID);
    adjust_position(&(cursor.y), dy, cursor.scale_y / MG_VERTICAL_GRID);
    rescale(&(cursor.scale_x), MG_RESCALE_MULTIPLIER / MG_HORIZONTAL_GRID);
    rescale(&(cursor.scale_y), MG_RESCALE_MULTIPLIER / MG_VERTICAL_GRID);
    return cursor;
}

void save_undo(mousegrid_cursor_t cursor) {
    if (undo_count == MG_UNDO_DEPTH) {
        return;
    }
    undo_buffer[undo_count++] = cursor;
}

mousegrid_cursor_t restore_undo(void) {
    if (undo_count == 0) {
        return init_cursor();
    }
    return undo_buffer[--undo_count];
}

void move(int8_t dx, int8_t dy) {
    save_undo(mousegrid_cursor);
    mousegrid_cursor = update(mousegrid_cursor, dx, dy);
}

uint32_t mousegrid_animate(uint32_t trigger_time, void *cb_arg) {
    if (animation_since == 0) {
        // Animation has been cancelled.
        return 0;
    }

    uint8_t step = (timer_read() - animation_since) / MG_ANIMATION_STEP;
    int8_t dx, dy;
    switch (step) {
#if MG_ANIMATION == full
        case 0:
        case 8:
            dx = 0;
            dy = -1;
            break;
        case 1:
            dx = 1;
            dy = -1;
            break;
        case 2:
            dx = 1;
            dy = 0;
            break;
        case 3:
            dx = 1;
            dy = 1;
            break;
        case 4:
            dx = 0;
            dy = 1;
            break;
        case 5:
            dx = -1;
            dy = 1;
            break;
        case 6:
            dx = -1;
            dy = 0;
            break;
        case 7:
            dx = -1;
            dy = -1;
            break;
#elif MG_ANIMATION == corners
        case 0:
            dx = 1;
            dy = -1;
            break;
        case 1:
            dx = 1;
            dy = 1;
            break;
        case 2:
            dx = -1;
            dy = 1;
            break;
        case 3:
            dx = -1;
            dy = -1;
            break;
#endif
        default:
            dx = 0;
            dy = 0;
            animation_since = 0;
            break;
    }
    mousegrid_cursor_t animation_cursor = update(mousegrid_cursor, dx, dy);
    digitizer_in_range_on();
    digitizer_set_position(animation_cursor.x, animation_cursor.y);
    return MG_ANIMATION_SLEEP;
}

void trigger_animation(void) {
    animation_since = timer_read();
    defer_exec(1, &mousegrid_animate, NULL);
}

void cancel_animation(void) {
    animation_since = 0;
}

void send(void) {
    digitizer_in_range_on();
    digitizer_set_position(mousegrid_cursor.x, mousegrid_cursor.y);
    uprintf(
        "mousegrid to: %ux%u scale=%ux%u\n",
        (int) (mousegrid_cursor.x * 100),
        (int) (mousegrid_cursor.y * 100),
        (int) (mousegrid_cursor.scale_x * 100),
        (int) (mousegrid_cursor.scale_y * 100)
    );
}

bool process_direction(uint16_t keycode) {
    switch (keycode) {
        case MG_TL:
            move(-1, -1);
            break;
        case MG_T:
            move(0, -1);
            break;
        case MG_TR:
            move(1, -1);
            break;
        case MG_L:
            move(-1, 0);
            break;
        case MG_C:
            move(0, 0);
            break;
        case MG_R:
            move(1, 0);
            break;
        case MG_BL:
            move(-1, 1);
            break;
        case MG_B:
            move(0, 1);
            break;
        case MG_BR:
            move(1, 1);
            break;
        default:
            return false;
    }
    cancel_animation();
    send();
    return true;
}

void trigger_alphabet(void) {
    alphabet_hook_since = timer_read();
    alphabet_x = true;
}

bool process_alphabet(keyrecord_t *record) {
    // Most of the time we don't need to steal keycodes.
    if (alphabet_hook_since == 0) {
        return false;
    }
    // Has the hook expired?
    if (alphabet_hook_since < timer_read() - MG_ALPHABET_HOOK_TIMEOUT) {
        alphabet_hook_since = 0;
        return false;
    }
    // Only key down events.
    if (!record->event.pressed) {
      return false;
    }

    keypos_t pos = record->event.key;
    uint16_t keycode = keycode_at_keymap_location(MG_ALPHABET_LAYER, pos.row, pos.col);
    int8_t index = 0;
    for (;; ++index) {
        uint16_t character = pgm_read_word(&alphabet[index]);
        if (character == 0) {
            // End of array.
            return false;
        }
        if (character == keycode) {
            break;
        }
    }

    mousegrid_cursor_t cursor = mousegrid_cursor;
    if (alphabet_x) {
        cursor.x = (float)index * 1.0 / (MG_ALPHABET_SIZE - 1);
        cursor.scale_x = MG_ALPHABET_RESCALE_MULTIPLIER / MG_ALPHABET_SIZE;
        alphabet_x = false;
    } else {
        cursor.y = (float)index * 1.0 / (MG_ALPHABET_SIZE - 1);
        cursor.scale_y = MG_ALPHABET_RESCALE_MULTIPLIER / MG_ALPHABET_SIZE;
        alphabet_hook_since = 0;
    }
    mousegrid_cursor = cursor;
    send();

    return true;
}

bool process_command(uint16_t keycode) {
    switch (keycode) {
        case MG_ANIM:
            trigger_animation();
            return true;

        case MG_UNDO:
            mousegrid_cursor = restore_undo();
            send();
            return true;

        case MG_ABC:
            mousegrid_init();
            trigger_alphabet();
            send();
            return true;

        case MG_NEAR:
            mousegrid_cursor.scale_x = MG_LOCAL_SCALE;
            mousegrid_cursor.scale_y = MG_LOCAL_SCALE;
            return true;

        case MG_RST:
            mousegrid_init();
            send();
            return true;
    }

    return false;
}

void mousegrid_init(void) {
    mousegrid_cursor = init_cursor();
    undo_count = 0;
}

bool process_mousegrid(uint16_t keycode, keyrecord_t *record) {
    if (process_alphabet(record)) {
        return false;
    }

    if (record->event.pressed) {
        if (process_command(keycode)) {
            return false;
        }
        if (process_direction(keycode)) {
            return false;
        }
    }

    if (IS_MOUSEGRID_KEYCODE(keycode)) {
        return false;
    }

    return true;
}

