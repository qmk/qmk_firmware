#include "counter_key.h"

int       counter_time_limit = 1000;
int       counter_time_last  = 0;
int       counter_count      = 0;
bool      counter_expired    = true;

int       incrementer_time_limit = 30000;
int       incrementer_time_last  = 0;
int       incrementer_count      = 0;
bool      incrementer_expired    = true;

bool process_counter_key(uint16_t keycode, keyrecord_t* record){
    switch (keycode) {
        case COUNT:
            if (record->event.pressed) {
                if (counter_expired) {
                    counter_count   = 0;
                    counter_expired = false;

                } else {
                    counter_count++;
                }
                counter_time_last = timer_read();
            }
            uprintf("break");
            break;
        case INCR:
            if (record->event.pressed) {
                if (incrementer_expired) {
                    incrementer_count   = 0;
                    incrementer_expired = false;

                } else {
                    incrementer_count++;
                }
                incrementer_time_last = timer_read();
            }
            uprintf("break");
            break;
        default:
            break;
    }
}

void register_codes16(uint16_t* keycodes, size_t* len){
    uprintf("Keycodes registered: ");
    for (size_t i = 0; i < *len; i++) {
        uprintf("%04X ", keycodes[i]);
        tap_code16(keycodes[i]);
    }
    uprintf("\n");
}

void number_to_keycode(uint16_t number, size_t* len, int *digits) {
    // Allocate an array to hold the keycodes.
    uint16_t* keycodes = malloc(*len * sizeof(uint16_t));

    // Convert each digit to a keycode.
    for (size_t i = 0; i < *len; i++) {
        keycodes[i] = KC_1 + digits[i] - 1;
    }

    // Send the keycodes as a sequence of keypresses.
    register_codes16(keycodes, len);

    // Free the memory allocated for the keycodes array.
    free(keycodes);
}

size_t count_digits(int n) {
    size_t count = 0;
    do {
        count++;
        n /= 10;
    } while (n!=0);
    return count;
}

void process_counter_key(void) {
    if (!counter_expired) {
        elapsed_time = timer_elapsed(counter_time_last);
        if (elapsed_time >= counter_time_limit) {
            size_t len = count_digits(++counter_count);
            int digits[len];
            int n = counter_count;
            for (size_t i = 0; i < len; i++) {
                digits[len - i - 1] = n % 10;
                n /= 10;
            }
            number_to_keycode(counter_count, &len, digits);

            counter_time_last = counter_time_limit;
            counter_expired   = true;
        }
    }
}

void process_incrementer_key(void) {
    if (!incrementer_expired) {
        elapsed_time = timer_elapsed(incrementer_time_last);
        if (elapsed_time >= incrementer_time_limit) {
            size_t len = count_digits(++incrementer_count);
            int digits[len];
            int n = incrementer_count;
            for (size_t i = 0; i < len; i++) {
                digits[len - i - 1] = n % 10;
                n /= 10;
            }
            number_to_keycode(incrementer_count, &len, digits);

            incrementer_time_last = incrementer_time_limit;
            incrementer_expired   = true;
        }
    }
}
