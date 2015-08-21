#include "beeps.h"
#include <math.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#define PI 3.14159265
#define CHANNEL OCR1C

volatile uint16_t sample;
uint16_t lastSample;

const int sounddata_length=200;

const unsigned char sounddata_data[] PROGMEM = {128, 
128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 
128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 
128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 
128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 
128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 
128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 
128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 
128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 
128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 
128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 129, 127, 129, 128, 127, 133, 
117, 109, 125, 121, 116, 132, 140, 126, 114, 114, 116, 120, 114, 93, 73, 66, 76, 116, 142, 129, 
128, 129, 120, 119, 118, 104, 87, 123, 181, 194, 196, 198, 189, 176, 160, 162, 172, 164, 164, 183, 
197, 188, 168, 167, 170, 165, 185, 209, 206, 196, 196, 199, 185, 162, 156, 167, 176, 173, 170, 166, 
151, 142, 140, 134, 130, 127, 113, 86, 67, 66, 69, 75, 73, 75, 86, 90, 91, 84, 65, 48, 
41, 30, 26, 56, 91, 88, 72, 70, 73, 82, 89, 73, 57, 60, 74, 89, 92, 77, 63, 60, 
53, 47, 56, 64, 63, 61, 56, 54, 52, 36, 16, 22, 51, 66, 67, 70, 76, 88, 99, 92, 
77, 74, 85, 100, 106, 97, 83, 85, 96, 108, 133, 160, 164};

void delay_us(int count) {
  while(count--) {
    _delay_us(1);
  }
}

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

void play_note(float freq, int length) {
    DDRB |= (1<<7);
    PORTB &= ~(1<<7);

    if (freq > 0) {
	    int frequency = 1000000/freq;
		ICR1 = frequency; // Set max to the period
		OCR1C = frequency >> 1; // Set compare to half the period

	    TCCR1A = _BV(COM1C1) | _BV(WGM11); // = 0b00001010;
	    TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS10); // = 0b00011001;
    }

	for (int i = 0; i < length; i++) {
	    _delay_us(50000);
	}

    TCCR1A &= ~(_BV(COM1C1));
}

// This is called at 8000 Hz to load the next sample.
ISR(TIMER1_COMPA_vect) {
    if (sample >= sounddata_length) {
        if (sample == sounddata_length + lastSample) {
            TIMSK1 &= ~_BV(OCIE1A);

			// Disable the per-sample timer completely.
   			 TCCR1B &= ~_BV(CS10);
        }
        else {
            OCR1C = sounddata_length + lastSample - sample;                
        }
    }
    else {
        OCR1C = pgm_read_byte(&sounddata_data[sample]);            
    }

    ++sample;
}

void play_notes() {


    // Set up Timer 2 to do pulse width modulation on the speaker
    // pin.

    DDRB |= (1<<7);
    PORTB &= ~(1<<7);

    // Use internal clock (datasheet p.160)
    // ASSR &= ~(_BV(EXCLK) | _BV(AS2));

    // Set fast PWM mode  (p.157)
    TCCR1A |= _BV(WGM21) | _BV(WGM20);
    TCCR1B &= ~_BV(WGM22);

    // Do non-inverting PWM on pin OC2A (p.155)
    // On the Arduino this is pin 11.
    TCCR1A = (TCCR2A | _BV(COM2A1)) & ~_BV(COM2A0);
    TCCR1A &= ~(_BV(COM2B1) | _BV(COM2B0));
    // No prescaler (p.158)
    TCCR1B = (TCCR1B & ~(_BV(CS12) | _BV(CS11))) | _BV(CS10);

    // Set initial pulse width to the first sample.
    OCR1A = pgm_read_byte(&sounddata_data[0]);




	cli();

    // Set CTC mode (Clear Timer on Compare Match) (p.133)
    // Have to set OCR1A *after*, otherwise it gets reset to 0!
    TCCR2B = (TCCR2B & ~_BV(WGM13)) | _BV(WGM12);
    TCCR2A = TCCR2A & ~(_BV(WGM11) | _BV(WGM10));

    // No prescaler (p.134)
    TCCR2B = (TCCR2B & ~(_BV(CS12) | _BV(CS11))) | _BV(CS10);

    // Set the compare register (OCR1A).
    // OCR1A is a 16-bit register, so we have to do this with
    // interrupts disabled to be safe.
    // OCR2A = F_CPU / SAMPLE_RATE;    // 16e6 / 8000 = 2000
    OCR2A = 2000;

    // Enable interrupt when TCNT1 == OCR1A (p.136)
    TIMSK1 |= _BV(OCIE2A);

    sample = 0;
    sei();
}

void note(int x, float length) {
    DDRB |= (1<<1);
	int t = (int)(440*pow(2,-x/12.0)); // starting note
    for (int y = 0; y < length*1000/t; y++) { // note length
        PORTB |= (1<<1);
        delay_us(t);
        PORTB &= ~(1<<1);
        delay_us(t);
    }
	PORTB &= ~(1<<1);
}

void true_note(float x, float y, float length) {
	for (uint32_t i = 0; i < length * 50; i++) {
		uint32_t v = (uint32_t) (round(sin(PI*2*i*640000*pow(2, x/12.0))*.5+1 + sin(PI*2*i*640000*pow(2, y/12.0))*.5+1) / 2 * pow(2, 8)); 
		for (int u = 0; u < 8; u++) {
			if (v & (1 << u) && !(PORTB&(1<<1)))
		        PORTB |= (1<<1);
		    else if (PORTB&(1<<1))
	        	PORTB &= ~(1<<1);
		}
	}
	PORTB &= ~(1<<1);
}