#include "beeps.h"
#include <math.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#define PI 3.14159265

void delay_us(int count) {
  while(count--) {
    _delay_us(1);
  }
}

int voices = 0;
double frequency = 0;
int volume = 0;
int position = 0;

double frequencies[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int volumes[8] = {0, 0, 0, 0, 0, 0, 0, 0};
bool sliding = false;
#define RANGE 1000
volatile int i=0; //elements of the wave


void beeps() {
    play_notes();
}

void send_freq(double freq, int vol) {
    int duty = (((double)F_CPU) / freq);
    ICR3 = duty; // Set max to the period
    OCR3A = duty >> (0x10 - vol); // Set compare to half the period
}

void stop_all_notes() {
    voices = 0;
    TCCR3A = 0;
    TCCR3B = 0;
    frequency = 0;
    volume = 0;

    for (int i = 0; i < 8; i++) {
        frequencies[i] = 0;
        volumes[i] = 0;
    }
}

void stop_note(double freq) {
    for (int i = 7; i >= 0; i--) {
        if (frequencies[i] == freq) {
            frequencies[i] = 0;
            volumes[i] = 0;
            for (int j = i; (j < 7); j++) {
                frequencies[j] = frequencies[j+1];
                frequencies[j+1] = 0;
                volumes[j] = volumes[j+1];
                volumes[j+1] = 0;
            }
        }
    }
    voices--;
    if (voices < 0)
        voices = 0;
    if (voices == 0) {
        TCCR3A = 0;
        TCCR3B = 0;
        frequency = 0;
        volume = 0;
    } else {
        double freq = frequencies[voices - 1];
        int vol = volumes[voices - 1];
        if (frequency < freq) {
            sliding = true;
            for (double f = frequency; f <= freq; f += ((freq - frequency) / 500.0)) {
                send_freq(f, vol);
            }
            sliding = false;
        } else if (frequency > freq) {
            sliding = true;
            for (double f = frequency; f >= freq; f -= ((frequency - freq) / 500.0)) {
                send_freq(f, vol);
            }
            sliding = false;
        }
        send_freq(freq, vol);
        frequency = freq;
        volume = vol;
    }
}

void init_notes() {
    // TCCR1A = (1 << COM1A1) | (0 << COM1A0) | (1 << WGM11) | (1 << WGM10);
    // TCCR1B = (1 << COM1B1) | (0 << COM1A0) | (1 << WGM13) | (1 << WGM12) | (0 << CS12) | (0 << CS11) | (1 << CS10);

    // DDRC |= (1<<6); 

    // TCCR3A = (1 << COM3A1) | (0 << COM3A0) | (1 << WGM31) | (0 << WGM30);
    // TCCR3B = (1 << WGM33) | (1 << WGM32) | (0 << CS32) | (0 << CS31) | (1 << CS30);

    // ICR3 = 0xFFFF; 
    // OCR3A = (int)((float)wave[i]*ICR3/RANGE); //go to next array element


    // cli();

    // /* Enable interrupt on timer2 == 127, with clk/8 prescaler. At 16MHz,
    //    this gives a timer interrupt at 15625Hz. */
    // TIMSK3 = (1 << OCIE3A);

    // /* clear/reset timer on match */
    // // TCCR3A = 1<<WGM31 | 0<<WGM30;  CTC mode, reset on match 
    // // TCCR3B = 0<<CS32 | 1<<CS31 | 0<<CS30; /* clk, /8 prescaler */

    // TCCR3A = (1 << COM3A1) | (0 << COM3A0) | (1 << WGM31) | (0 << WGM30);
    // TCCR3B = (0 << WGM33) | (0 << WGM32) | (0 << CS32) | (0 << CS31) | (1 << CS30);


    // TCCR1A = (1 << COM1A1) | (0 << COM1A0) | (1 << WGM11) | (0 << WGM10);
    // TCCR1B = (1 << WGM12) | (0 << CS12) | (0 << CS11) | (1 << CS10);
    // // SPCR = 0x50;
    // // SPSR = 0x01;
    // DDRC |= (1<<6);
    // // ICR3 = 0xFFFF; 
    // // OCR3A=80;
    // PORTC |= (1<<6);

    // sei();
}

// #define highByte(c) ((c >> 8) & 0x00FF)
// #define lowByte(c) (c & 0x00FF)

ISR(TIMER3_COMPA_vect) {

    if (ICR3 > 0 && !sliding) {
        switch (position) {
            case 0: {
                int duty = (((double)F_CPU) / (frequency));
                ICR3 = duty; // Set max to the period
                OCR3A = duty >> 1; // Set compare to half the period
                break;
            }
            case 1: {
                int duty = (((double)F_CPU) / (frequency*2));
                ICR3 = duty; // Set max to the period
                OCR3A = duty >> 1; // Set compare to half the period
                break;
            }
            case 2: {
                int duty = (((double)F_CPU) / (frequency*3));
                ICR3 = duty; // Set max to the period
                OCR3A = duty >> 1; // Set compare to half the period
                break;
            }
        }
        position = (position + 1) % 3;
    }
//     /* OCR2A has been cleared, per TCCR2A above */
//     // OCR3A = 127;

//     // pos1 += incr1;
//     // pos2 += incr2;
//     // pos3 += incr3;

//     // sample = sinewave[highByte(pos1)] + sinewave[highByte(pos2)] + sinewave[highByte(pos3)];

//     // OCR3A = sample;


//     OCR3A=pgm_read_byte(&sinewave[pos1]);
//     pos1++;
//     // PORTC &= ~(1<<6);

//     /* buffered, 1x gain, active mode */
//     // SPDR = highByte(sample) | 0x70;
//     // while (!(SPSR & (1<<SPIF)));

//     // SPDR = lowByte(sample);
//     // while (!(SPSR & (1<<SPIF)));

//     // PORTC |= (1<<6);
}

void play_note(double freq, int vol) {

    if (freq > 0) {
        DDRC |= (1<<6); 

        TCCR3A = (1 << COM3A1) | (0 << COM3A0) | (1 << WGM31) | (0 << WGM30);
        TCCR3B = (1 << WGM33) | (1 << WGM32) | (0 << CS32) | (1 << CS31) | (0 << CS30);

        if (frequency != 0) {
            if (frequency < freq) {
                for (double f = frequency; f <= freq; f += ((freq - frequency) / 500.0)) {
                    send_freq(f, vol);
                }
            } else if (frequency > freq) {
                for (double f = frequency; f >= freq; f -= ((frequency - freq) / 500.0)) {
                    send_freq(f, vol);
                }
            }
        }
        send_freq(freq, vol);
        frequency = freq;
        volume = vol;

        frequencies[voices] = frequency;
        volumes[voices] = volume;
        voices++;
    }
    // ICR3 = 0xFFFF;
    // for (int i = 0; i < 10000; i++) {
    //     OCR3A = round((sin(i*freq)*.5)+.5)*0xFFFF;
    //     // _delay_us(50);
    // }

    // TCCR3A = 0;
    // TCCR3B = 0;
}

// void note(int x, float length) {
//     DDRC |= (1<<6);
// 	int t = (int)(440*pow(2,-x/12.0)); // starting note
//     for (int y = 0; y < length*1000/t; y++) { // note length
//         PORTC |= (1<<6);
//         delay_us(t);
//         PORTC &= ~(1<<6);
//         delay_us(t);
//     }
// 	PORTC &= ~(1<<6);
// }

// void true_note(float x, float y, float length) {
// 	for (uint32_t i = 0; i < length * 50; i++) {
// 		uint32_t v = (uint32_t) (round(sin(PI*2*i*640000*pow(2, x/12.0))*.5+1 + sin(PI*2*i*640000*pow(2, y/12.0))*.5+1) / 2 * pow(2, 8)); 
// 		for (int u = 0; u < 8; u++) {
// 			if (v & (1 << u) && !(PORTC&(1<<6)))
// 		        PORTC |= (1<<6);
// 		    else if (PORTC&(1<<6))
// 	        	PORTC &= ~(1<<6);
// 		}
// 	}
// 	PORTC &= ~(1<<6);
// }