#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include "bootloader.h"

#ifdef PROTOCOL_LUFA
#include <LUFA/Drivers/USB/USB.h>
#endif


/* Boot Section Size in *BYTEs*
 *   Teensy   halfKay    512
 *   Teensy++ halfKay    1024
 *   Atmel DFU loader    4096
 *   LUFA bootloader     4096
 *   USBaspLoader        2048
 */
#ifndef BOOTLOADER_SIZE
#warning To use bootloader_jump() you need to define BOOTLOADER_SIZE in config.h.
#define BOOTLOADER_SIZE     4096
#endif

#define FLASH_SIZE          (FLASHEND + 1L)
#define BOOTLOADER_START    (FLASH_SIZE - BOOTLOADER_SIZE)


/* 
 * Entering the Bootloader via Software 
 * http://www.fourwalledcubicle.com/files/LUFA/Doc/120730/html/_page__software_bootloader_start.html
 */
#define BOOTLOADER_RESET_KEY 0xB007B007
uint32_t reset_key  __attribute__ ((section (".noinit")));

/* initialize MCU status by watchdog reset */
void bootloader_jump(void) {
#ifdef PROTOCOL_LUFA
    USB_Disable();
    cli();
    _delay_ms(2000);
#endif

#ifdef PROTOCOL_PJRC
    cli();
    UDCON = 1;
    USBCON = (1<<FRZCLK);
    UCSR1B = 0;
    _delay_ms(5);
#endif

    // watchdog reset
    reset_key = BOOTLOADER_RESET_KEY;
    wdt_enable(WDTO_250MS);
    for (;;);
}


/* this runs before main() */
void bootloader_jump_after_watchdog_reset(void) __attribute__ ((used, naked, section (".init3")));
void bootloader_jump_after_watchdog_reset(void)
{
    if ((MCUSR & (1<<WDRF)) && reset_key == BOOTLOADER_RESET_KEY) {
        reset_key = 0;

        // My custom USBasploader requires this to come up.
        MCUSR = 0;

        // Seems like Teensy halfkay loader requires clearing WDRF and disabling watchdog.
        MCUSR &= ~(1<<WDRF);
        wdt_disable();

        // This is compled into 'icall', address should be in word unit, not byte.
        ((void (*)(void))(BOOTLOADER_START/2))();
    }
}


#if 0
/* Jumping To The Bootloader
 * http://www.pjrc.com/teensy/jump_to_bootloader.html
 * 
 * This method doen't work when using LUFA. idk why.
 * - needs to initialize more regisers or interrupt setting?
 */
void bootloader_jump(void) {
#ifdef PROTOCOL_LUFA
    USB_Disable();
    cli();
    _delay_ms(2000);
#endif

#ifdef PROTOCOL_PJRC
    cli();
    UDCON = 1;
    USBCON = (1<<FRZCLK);
    UCSR1B = 0;
    _delay_ms(5);
#endif

    /*
     * Initialize
     */
#if defined(__AVR_AT90USB162__)
    EIMSK = 0; PCICR = 0; SPCR = 0; ACSR = 0; EECR = 0;
    TIMSK0 = 0; TIMSK1 = 0; UCSR1B = 0;
    DDRB = 0; DDRC = 0; DDRD = 0;
    PORTB = 0; PORTC = 0; PORTD = 0;
#elif defined(__AVR_ATmega32U4__)
    EIMSK = 0; PCICR = 0; SPCR = 0; ACSR = 0; EECR = 0; ADCSRA = 0;
    TIMSK0 = 0; TIMSK1 = 0; TIMSK3 = 0; TIMSK4 = 0; UCSR1B = 0; TWCR = 0;
    DDRB = 0; DDRC = 0; DDRD = 0; DDRE = 0; DDRF = 0; TWCR = 0;
    PORTB = 0; PORTC = 0; PORTD = 0; PORTE = 0; PORTF = 0;
#elif defined(__AVR_AT90USB646__)
    EIMSK = 0; PCICR = 0; SPCR = 0; ACSR = 0; EECR = 0; ADCSRA = 0;
    TIMSK0 = 0; TIMSK1 = 0; TIMSK2 = 0; TIMSK3 = 0; UCSR1B = 0; TWCR = 0;
    DDRA = 0; DDRB = 0; DDRC = 0; DDRD = 0; DDRE = 0; DDRF = 0;
    PORTA = 0; PORTB = 0; PORTC = 0; PORTD = 0; PORTE = 0; PORTF = 0;
#elif defined(__AVR_AT90USB1286__)
    EIMSK = 0; PCICR = 0; SPCR = 0; ACSR = 0; EECR = 0; ADCSRA = 0;
    TIMSK0 = 0; TIMSK1 = 0; TIMSK2 = 0; TIMSK3 = 0; UCSR1B = 0; TWCR = 0;
    DDRA = 0; DDRB = 0; DDRC = 0; DDRD = 0; DDRE = 0; DDRF = 0;
    PORTA = 0; PORTB = 0; PORTC = 0; PORTD = 0; PORTE = 0; PORTF = 0;
#endif

    /*
     * USBaspLoader
     */
#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega168P__) || defined(__AVR_ATmega328P__)
    // This makes custom USBasploader come up.
    MCUSR = 0;

    // initialize ports
    PORTB = 0; PORTC= 0; PORTD = 0;
    DDRB = 0; DDRC= 0; DDRD = 0;

    // disable interrupts
    EIMSK = 0; EECR = 0; SPCR = 0;
    ACSR = 0; SPMCSR = 0; WDTCSR = 0; PCICR = 0;
    TIMSK0 = 0; TIMSK1 = 0; TIMSK2 = 0;
    ADCSRA = 0; TWCR = 0; UCSR0B = 0;
#endif

    // This is compled into 'icall', address should be in word unit, not byte.
    ((void (*)(void))(BOOTLOADER_START/2))();
}
#endif
