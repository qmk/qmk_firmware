#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>

void note(int x, float length);
void beeps();
void true_note(float x, float y, float length);
void play_note(double freq, int vol);
void stop_note(double freq);
void stop_all_notes();
void init_notes();