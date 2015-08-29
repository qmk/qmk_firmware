#include "beeps.h"
#include <math.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#define PI 3.14159265
#define CHANNEL OCR1C

void delay_us(int count) {
  while(count--) {
    _delay_us(1);
  }
}

int voices = 0;
double frequency = 0;
int volume = 0;

double frequencies[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int volumes[8] = {0, 0, 0, 0, 0, 0, 0, 0};

void beeps() {
 //    DDRB |= (1<<7);
 //    PORTB &= ~(1<<7);
    
 //    // Use full 16-bit resolution. 
 //    ICR1 = 0xFFFF;

 //    // I could write a wall of text here to explain... but TL;DW
 //    // Go read the ATmega32u4 datasheet.
 //    // And this: http://blog.saikoled.com/post/43165849837/secret-konami-cheat-code-to-high-resolution-pwm-on
    
 //    // Pin PB7 = OCR1C (Timer 1, Channel C)
 //    // Compare Output Mode = Clear on compare match, Channel C = COM1C1=1 COM1C0=0
 //    // (i.e. start high, go low when counter matches.)
 //    // WGM Mode 14 (Fast PWM) = WGM13=1 WGM12=1 WGM11=1 WGM10=0
 //    // Clock Select = clk/1 (no prescaling) = CS12=0 CS11=0 CS10=1
    
 //    TCCR1A = _BV(COM1C1) | _BV(WGM11); // = 0b00001010;
 //    TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS10); // = 0b00011001;


 //    // Turn off PWM control on PB7, revert to output low.
 //    // TCCR1A &= ~(_BV(COM1C1));
 //    // CHANNEL = ((1 << level) - 1);

 //    // Turn on PWM control of PB7
 //    TCCR1A |= _BV(COM1C1);
 //    // CHANNEL = level << OFFSET | 0x0FFF;
 //    // CHANNEL = 0b1010101010101010;

 //    float x = 12;
 //    float y = 24;
 //    float length = 50;
 //    float scale = 1;

 // //    int f1 = 1000000/440;
 // //    int f2 = 1000000/880;
	// // for (uint32_t i = 0; i < length * 1000; i++) {
	// // 	// int frequency = 1/((sin(PI*2*i*scale*pow(2, x/12.0))*.5+1 + sin(PI*2*i*scale*pow(2, y/12.0))*.5+1) / 2); 

	// // 	ICR1 = f1; // Set max to the period
	// // 	OCR1C = f1 >> 1; // Set compare to half the period
 // //     	// _delay_us(10);
	// // }
 //    int frequency = 1000000/440;
	// ICR1 = frequency; // Set max to the period
	// OCR1C = frequency >> 1; // Set compare to half the period
 //    _delay_us(500000);

 //    TCCR1A &= ~(_BV(COM1C1));
 //    CHANNEL = 0;
play_notes();


	// play_note(55*pow(2, 0/12.0), 	1);
	// play_note(55*pow(2, 12/12.0), 	1);
	// play_note(55*pow(2, 24/12.0), 	1);
	// play_note(55*pow(2, 0/12.0), 	1);
	// play_note(55*pow(2, 12/12.0), 	1);
	// play_note(55*pow(2, 24/12.0), 	1);

	// play_note(0, 					4);

	// play_note(55*pow(2, 0/12.0), 	8);
	// play_note(55*pow(2, 12/12.0), 	4);
	// play_note(55*pow(2, 10/12.0), 	4);
	// play_note(55*pow(2, 12/12.0), 	8);
	// play_note(55*pow(2, 10/12.0), 	4);
	// play_note(55*pow(2, 7/12.0), 	2);
	// play_note(55*pow(2, 8/12.0), 	2);
	// play_note(55*pow(2, 7/12.0), 	16);
	// play_note(0, 					4);
	// play_note(55*pow(2, 3/12.0), 	8);
	// play_note(55*pow(2, 5/12.0), 	4);
	// play_note(55*pow(2, 7/12.0), 	4);
	// play_note(55*pow(2, 7/12.0), 	8);
	// play_note(55*pow(2, 5/12.0), 	4);
	// play_note(55*pow(2, 3/12.0), 	4);
	// play_note(55*pow(2, 2/12.0), 	16);


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
    if (voices == 0) {
        TCCR3A = 0;
        TCCR3B = 0;
        frequency = 0;
    } else {
        double freq = frequencies[voices - 1];
        int vol = volumes[voices - 1];
        if (frequency < freq) {
            for (double f = frequency; f <= freq; f += ((freq - frequency) / 500.0)) {
                send_freq(f, vol);
            }
        } else if (frequency > freq) {
            for (double f = frequency; f >= freq; f -= ((frequency - freq) / 500.0)) {
                send_freq(f, vol);
            }
        }
        send_freq(freq, vol);
        frequency = freq;
        volume = vol;
    }
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

void note(int x, float length) {
    DDRC |= (1<<6);
	int t = (int)(440*pow(2,-x/12.0)); // starting note
    for (int y = 0; y < length*1000/t; y++) { // note length
        PORTC |= (1<<6);
        delay_us(t);
        PORTC &= ~(1<<6);
        delay_us(t);
    }
	PORTC &= ~(1<<6);
}

void true_note(float x, float y, float length) {
	for (uint32_t i = 0; i < length * 50; i++) {
		uint32_t v = (uint32_t) (round(sin(PI*2*i*640000*pow(2, x/12.0))*.5+1 + sin(PI*2*i*640000*pow(2, y/12.0))*.5+1) / 2 * pow(2, 8)); 
		for (int u = 0; u < 8; u++) {
			if (v & (1 << u) && !(PORTC&(1<<6)))
		        PORTC |= (1<<6);
		    else if (PORTC&(1<<6))
	        	PORTC &= ~(1<<6);
		}
	}
	PORTC &= ~(1<<6);
}