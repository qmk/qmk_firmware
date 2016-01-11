#include <stdio.h>
#include <string.h>
#include <math.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "beeps.h"
#include "keymap_common.h"
#include "wave.h"

#define PI 3.14159265

#define SAMPLE_DIVIDER 70
#define SAMPLE_RATE (2000000.0/SAMPLE_DIVIDER/256)
// Resistor value of 1/ (2 * PI * 10nF * (2000000 hertz / SAMPLE_DIVIDER / 10)) for 10nF cap

void delay_us(int count) {
  while(count--) {
    _delay_us(1);
  }
}

int voices = 0;
double frequency = 0;
int volume = 0;
long position = 0;

double frequencies[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int volumes[8] = {0, 0, 0, 0, 0, 0, 0, 0};
bool sliding = false;
#define RANGE 1000
volatile int i=0; //elements of the wave

// uint8_t sine[128];
// uint8_t tri[128];
// uint8_t squ[128];
// uint8_t* sine_start;
// uint8_t* sine_end;
// uint8_t* tri_start;
// uint8_t* tri_end;

// uint8_t* s_start;
// uint8_t* s_end;
// uint8_t* s_ptr;



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
    TIMSK0 &= ~_BV(OCIE0A);
    frequency = 0;
    volume = 0;

    for (int i = 0; i < 8; i++) {
        frequencies[i] = 0;
        volumes[i] = 0;
    }
}

void stop_note(double freq) {
    freq = freq / SAMPLE_RATE;
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
        TIMSK0 &= ~_BV(OCIE0A);
        frequency = 0;
        volume = 0;
    } else {
        double freq = frequencies[voices - 1];
        int vol = volumes[voices - 1];
        double starting_f = frequency;
        if (frequency < freq) {
            sliding = true;
            for (double f = starting_f; f <= freq; f += ((freq - starting_f) / 500.0)) {
                frequency = f;
            }
            sliding = false;
        } else if (frequency > freq) {
            sliding = true;
            for (double f = starting_f; f >= freq; f -= ((starting_f - freq) / 500.0)) {
                frequency = f;
            }
            sliding = false;
        }
        // send_freq(freq, vol);
        frequency = freq;
        volume = vol;
    }
}

void init_notes() {

    // for(int i = 0; i < 128; i++) {
    //     sine[i] = sin(i * PI / 64) * 128 + 128;
    //     tri[i] = 256 - abs((i - 64) * 4);
    // }
    // sine_start = &sine;
    // sine_end = &sine + 128;
    // tri_start = &tri;
    // tri_end = &tri + 128;

 // new


  PLLFRQ = _BV(PDIV2);
  PLLCSR = _BV(PLLE);
  while(!(PLLCSR & _BV(PLOCK)));
  PLLFRQ |= _BV(PLLTM0); /* PCK 48MHz */
  
  /* Init a fast PWM on Timer4 */
  TCCR4A = _BV(COM4A0) | _BV(PWM4A); /* Clear OC4A on Compare Match */
  TCCR4B = _BV(CS40); /* No prescaling => f = PCK/256 = 187500Hz */
  OCR4A = 0;

  /* Enable the OC4A output */
  DDRC |= _BV(PORTC6);



       /* First disable the timer overflow interrupt while we're configuring */
  // TIMSK0 &= ~(1<<TOIE0);
 
  // /* Configure timer4 in normal mode (pure counting, no PWM etc.) */
  // TCCR0A &= ~((1<<WGM01) | (1<<WGM00));
  // TCCR0B &= ~(1<<WGM02);

  // /* Disable Compare Match A interrupt enable (only want overflow) */
  // TIMSK0 &= ~(1<<OCIE0A);
  
  // TCCR0B |= (1<<CS01); // Set bits
  // TCCR0B &= ~(1<<CS00) | ~(1<<CS02);             // Clear bit
   
  // /* Save value globally for later reload in ISR */
  // tcnt0 = 45 - 1; 

  // /* Finally load end enable the timer */
  // TCNT0 = tcnt0;
  // TIMSK0 |= (1<<TOIE0);

}

int max = 0xFF;
float sum = 0;
int value = 128;
float place = 0;

ISR(TIMER0_COMPA_vect) {



    // value = *(sine_start+=(long)frequencies[0]);
    // OCR4A = value;
    // if (sine_start >= sine_end) {
    //     sine_start = &sine[(sine_start - sine_end) % 128];
    // }


    // OCR4A = pgm_read_byte(sine_start);
    // // sine_start = &sine[(sine_start - &sine[0] + (int)frequencies[0]) % 128];
    // sine_start +=  (int)frequencies[0];
    // if (sine_start >= sine_end) {
    //     sine_start = &sine[(sine_start - sine_end) % 128];
    // }
    
    // OCR4A = pgm_read_byte(s_ptr);
    // s_ptr = s_start + (uint8_t)place;
    // OCR4A = pgm_read_byte(s_ptr);


    // SINE
    OCR4A = pgm_read_byte(&sinewave[(uint16_t)place]);
    
    // SQUARE
    // if (((int)place) >= 1024){
    //     OCR4A = 0xFF;
    // } else {
    //     OCR4A = 0x00;
    // }
    
    // SAWTOOTH
    // OCR4A = (int)place / 4;

    // TRIANGLE
    // if (((int)place) >= 1024) {
    //     OCR4A = (int)place / 2;
    // } else {
    //     OCR4A = 2048 - (int)place / 2;
    // }

    place += frequency;
    if (place >= SINE_LENGTH)
        place -= SINE_LENGTH;

}


ISR(TIMER0_COMPB_vect)
{

  /* Disable the interrupt */
  TIMSK0 &= ~_BV(OCIE0B);

}

void play_note(double freq, int vol) {

    freq = freq / SAMPLE_RATE;
    if (freq > 0) {

        // TCCR3A = (1 << COM3A1) | (0 << COM3A0) | (1 << WGM31) | (1 << WGM30);
        // TCCR3B = (0 << WGM33) | (1 << WGM32) | (0 << CS32) | (0 << CS31) | (1 << CS30);

      // TIMSK3 = 0x0;
        if (frequency != 0) {
            double starting_f = frequency;
            if (frequency < freq) {
                for (double f = starting_f; f <= freq; f += ((freq - starting_f) / 500.0)) {   
                    frequency = f;
                }
            } else if (frequency > freq) {
                for (double f = starting_f; f >= freq; f -= ((starting_f - freq) / 500.0)) {
                    frequency = f;
                }
            }
        }
        // send_freq(freq, vol);
        frequency = freq;
        volume = vol;

        frequencies[voices] = frequency;
        volumes[voices] = volume;
        voices++;
        // position = 0;
        // TCNT0 = 0;
    }
    // ICR3 = 0xFFFF;
    // for (int i = 0; i < 10000; i++) {
    //     OCR3A = round((sin(i*freq)*.5)+.5)*0xFFFF;
    //     // _delay_us(50);
    // }

    // TCCR3A = 0;
    // TCCR3B = 0;


    TIMSK0 &= ~_BV(OCIE0A) | ~_BV(OCIE0B);

    TCCR0A = _BV(WGM01); 
    TCCR0B = _BV(CS01);
    OCR0A = SAMPLE_DIVIDER - 1;  
    OCR0B = 1;

    TIMSK0 |= _BV(OCIE0A);
    // sei();

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