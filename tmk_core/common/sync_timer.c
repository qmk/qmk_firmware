#include "sync_timer.h"

#ifdef SPLIT_KEYBOARD
volatile uint32_t sync_timer_ms;

void sync_timer_init(void) {
    sync_timer_ms = timer_read32();
}

void sync_timer_clear(void) {
    sync_timer_ms = 0;
}

void sync_timer_update(uint32_t time) {
    sync_timer_ms = time;
}

uint16_t sync_timer_read(void) {
    return sync_timer_ms;
}

uint32_t sync_timer_read32(void) {
    return sync_timer_ms;
}

#else

void sync_timer_init(void) {
    // Already handled
}

void sync_timer_clear(void) {
    // Already handled
}

void sync_timer_update(uint32_t time) {
    // Unused
}

uint16_t sync_timer_read(void) {
    return timer_read();
}

uint32_t sync_timer_read32(void) {
    return timer_read32();
}

#endif

uint16_t sync_timer_elapsed(uint16_t last) {
    return TIMER_DIFF_16(sync_timer_read(), last);
}

uint32_t sync_timer_elapsed32(uint32_t last) {
    return TIMER_DIFF_32(sync_timer_read32(), last);
}

// TODO: should be moved into timer.h
// Useful for automatically handling wrapping when called more frequently than 32768ms
bool sync_timer_expired(uint16_t future) {
    return sync_timer_read() - future < 0x8000;
}

// TODO: should be moved into timer.h
// Useful for automatically handling wrapping when called more frequently than 2147483648ms
bool sync_timer_expired32(uint32_t future) {
    return sync_timer_read32() - future < 0x80000000;
}
