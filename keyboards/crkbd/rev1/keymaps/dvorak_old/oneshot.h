#pragma once

#include QMK_KEYBOARD_H

// Represents the four states a oneshot can be in
typedef enum {
    os_up_unqueued,
    os_up_queued,
    os_down_unused,
    os_down_used,
} oneshot_state;


// Cusotm oneshot mod impl that doesnt rely on timers.
// If a mod is used while it is held it will be unregistered on keyup as normal,
// otherwise it will be queued and only released after the next non-mod keyup
void update_oneshot(
        oneshot_state *state,
        uint16_t mod,
        uint16_t trigger,
        uint16_t keycode,
        keyrecord_t *record
        );


// To be implemented by the consumer. Defines keys to cancel oneshot mods.
bool is_oneshot_cancel_key(uint16_t keycode);


// To be implemented by the consumer. Defines keys to ignore when determining wheter a onesht mod has been usd.
// Setting this to modifiers and layer change keys allows stacking multiple oneshot modifiers, and carrying them between layers
bool is_oneshot_ignored_key(uint16_t keycode);
