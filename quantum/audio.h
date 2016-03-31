#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>

void play_sample(uint8_t * s, uint16_t l, bool r);
void play_note(double freq, int vol);
void stop_note(double freq);
void stop_all_notes();
void init_notes();
void play_notes(float (*np)[][2], uint8_t n_length, bool n_repeat);