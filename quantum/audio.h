#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>

typedef union {
    uint8_t raw;
    struct {
        bool    enable :1;
        uint8_t level  :7;
    };
} audio_config_t;

void audio_toggle(void);
void audio_on(void);
void audio_off(void);

void play_sample(uint8_t * s, uint16_t l, bool r);
void play_note(double freq, int vol);
void stop_note(double freq);
void stop_all_notes();
void init_notes();
void play_notes(float (*np)[][2], uint8_t n_length, bool n_repeat);
