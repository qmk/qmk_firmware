#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include "bootloader.h"
#include <avr/boot.h>

#ifdef PROTOCOL_LUFA
#include <LUFA/Drivers/USB/USB.h>
#endif


/** \brief Bootloader Size in *bytes*
 *
 * AVR Boot section size are defined by setting BOOTSZ fuse in fact. Consult with your MCU datasheet.
 * Note that 'Word'(2 bytes) size and address are used in datasheet while TMK uses 'Byte'.
 *
 * Size of Bootloaders in bytes:
 *   Atmel DFU loader(ATmega32U4)   4096
 *   Atmel DFU loader(AT90USB128)   8192
 *   LUFA bootloader(ATmega32U4)    4096
 *   Arduino Caterina(ATmega32U4)   4096
 *   USBaspLoader(ATmega***)        2048
 *   Teensy   halfKay(ATmega32U4)   512
 *   Teensy++ halfKay(AT90USB128)   1024
 *
 * AVR Boot section is located at the end of Flash memory like the followings.
 *
 * byte     Atmel/LUFA(ATMega32u4)          byte     Atmel(AT90SUB128)
 * 0x0000   +---------------+               0x00000  +---------------+
 *          |               |                        |               |
 *          |               |                        |               |
 *          |  Application  |                        |  Application  |
 *          |               |                        |               |
 *          =               =                        =               =
 *          |               | 32KB-4KB               |               | 128KB-8KB
 * 0x7000   +---------------+               0x1E000  +---------------+
 *          |  Bootloader   | 4KB                    |  Bootloader   | 8KB
 * 0x7FFF   +---------------+               0x1FFFF  +---------------+
 *
 *
 * byte     Teensy(ATMega32u4)              byte     Teensy++(AT90SUB128)
 * 0x0000   +---------------+               0x00000  +---------------+
 *          |               |                        |               |
 *          |               |                        |               |
 *          |  Application  |                        |  Application  |
 *          |               |                        |               |
 *          =               =                        =               =
 *          |               | 32KB-512B              |               | 128KB-1KB
 * 0x7E00   +---------------+               0x1FC00  +---------------+
 *          |  Bootloader   | 512B                   |  Bootloader   | 1KB
 * 0x7FFF   +---------------+               0x1FFFF  +---------------+
 */
#define FLASH_SIZE (FLASHEND + 1L)

#if !defined(BOOTLOADER_SIZE)
    uint16_t bootloader_start;
#endif

#define BOOT_SIZE_256  0b110
#define BOOT_SIZE_512  0b100
#define BOOT_SIZE_1024 0b010
#define BOOT_SIZE_2048 0b000

/** \brief Entering the Bootloader via Software
 *
 * http://www.fourwalledcubicle.com/files/LUFA/Doc/120730/html/_page__software_bootloader_start.html
 */
#define BOOTLOADER_RESET_KEY 0xB007B007
uint32_t reset_key  __attribute__ ((section (".noinit,\"aw\",@nobits;")));

/** \brief initialize MCU status by watchdog reset
 *
 * FIXME: needs doc
 */
void bootloader_jump(void) {

    #if !defined(BOOTLOADER_SIZE)
        uint8_t high_fuse = boot_lock_fuse_bits_get(GET_HIGH_FUSE_BITS);

        if (high_fuse & BOOT_SIZE_256) {
            bootloader_start = (FLASH_SIZE - 512) >> 1;
        } else if (high_fuse & BOOT_SIZE_512) {
            bootloader_start = (FLASH_SIZE - 1024) >> 1;
        } else if (high_fuse & BOOT_SIZE_1024) {
            bootloader_start = (FLASH_SIZE - 2048) >> 1;
        } else {
            bootloader_start = (FLASH_SIZE - 4096) >> 1;
        }
    #endif

    // Something like this might work, but it compiled larger than the block above
    // bootloader_start = FLASH_SIZE - (256 << (~high_fuse & 0b110 >> 1));


    #if defined(BOOTLOADER_HALFKAY)
        //  http://www.pjrc.com/teensy/jump_to_bootloader.html
        cli();
        // disable watchdog, if enabled (it's not)
        // disable all peripherals
        // a shutdown call might make sense here
        UDCON = 1;
        USBCON = (1<<FRZCLK);  // disable USB
        UCSR1B = 0;
        _delay_ms(5);
        #if defined(__AVR_AT90USB162__)                // Teensy 1.0
            EIMSK = 0; PCICR = 0; SPCR = 0; ACSR = 0; EECR = 0;
            TIMSK0 = 0; TIMSK1 = 0; UCSR1B = 0;
            DDRB = 0; DDRC = 0; DDRD = 0;
            PORTB = 0; PORTC = 0; PORTD = 0;
            asm volatile("jmp 0x3E00");
        #elif defined(__AVR_ATmega32U4__)              // Teensy 2.0
            EIMSK = 0; PCICR = 0; SPCR = 0; ACSR = 0; EECR = 0; ADCSRA = 0;
            TIMSK0 = 0; TIMSK1 = 0; TIMSK3 = 0; TIMSK4 = 0; UCSR1B = 0; TWCR = 0;
            DDRB = 0; DDRC = 0; DDRD = 0; DDRE = 0; DDRF = 0; TWCR = 0;
            PORTB = 0; PORTC = 0; PORTD = 0; PORTE = 0; PORTF = 0;
            asm volatile("jmp 0x7E00");
        #elif defined(__AVR_AT90USB646__)              // Teensy++ 1.0
            EIMSK = 0; PCICR = 0; SPCR = 0; ACSR = 0; EECR = 0; ADCSRA = 0;
            TIMSK0 = 0; TIMSK1 = 0; TIMSK2 = 0; TIMSK3 = 0; UCSR1B = 0; TWCR = 0;
            DDRA = 0; DDRB = 0; DDRC = 0; DDRD = 0; DDRE = 0; DDRF = 0;
            PORTA = 0; PORTB = 0; PORTC = 0; PORTD = 0; PORTE = 0; PORTF = 0;
            asm volatile("jmp 0xFC00");
        #elif defined(__AVR_AT90USB1286__)             // Teensy++ 2.0
            EIMSK = 0; PCICR = 0; SPCR = 0; ACSR = 0; EECR = 0; ADCSRA = 0;
            TIMSK0 = 0; TIMSK1 = 0; TIMSK2 = 0; TIMSK3 = 0; UCSR1B = 0; TWCR = 0;
            DDRA = 0; DDRB = 0; DDRC = 0; DDRD = 0; DDRE = 0; DDRF = 0;
            PORTA = 0; PORTB = 0; PORTC = 0; PORTD = 0; PORTE = 0; PORTF = 0;
            asm volatile("jmp 0x1FC00");
        #endif

    #elif defined(BOOTLOADER_CATERINA)
        // this block may be optional
        // TODO: figure it out

        uint16_t *const bootKeyPtr = (uint16_t *)0x0800;

        // Value used by Caterina bootloader use to determine whether to run the
        // sketch or the bootloader programmer.
        uint16_t bootKey = 0x7777;

        *bootKeyPtr = bootKey;

        // setup watchdog timeout
        wdt_enable(WDTO_60MS);

        while(1) {} // wait for watchdog timer to trigger

    #else // Assume remaining boards are DFU, even if the flag isn't set

        #if !(defined(__AVR_ATmega32A__) || defined(__AVR_ATmega328P__)) // no USB - maybe BOOTLOADER_BOOTLOADHID instead though?
            UDCON = 1;
            USBCON = (1<<FRZCLK);  // disable USB
            UCSR1B = 0;
            _delay_ms(5); // 5 seems to work fine
        #endif

        #ifdef BOOTLOADER_BOOTLOADHID
            // force bootloadHID to stay in bootloader mode, so that it waits
            // for a new firmware to be flashed
            eeprom_write_byte((uint8_t *)1, 0x00);
        #endif

        // watchdog reset
        reset_key = BOOTLOADER_RESET_KEY;
        wdt_enable(WDTO_250MS);
        for (;;);
    #endif

}

#ifdef __AVR_ATmega32A__
    // MCUSR is actually called MCUCSR in ATmega32A
    #define MCUSR MCUCSR
#endif

/* this runs before main() */
void bootloader_jump_after_watchdog_reset(void) __attribute__ ((used, naked, section (".init3")));
void bootloader_jump_after_watchdog_reset(void)
{
    #ifndef BOOTLOADER_HALFKAY
        if ((MCUSR & (1<<WDRF)) && reset_key == BOOTLOADER_RESET_KEY) {
            reset_key = 0;

            // My custom USBasploader requires this to come up.
            MCUSR = 0;

            // Seems like Teensy halfkay loader requires clearing WDRF and disabling watchdog.
            MCUSR &= ~(1<<WDRF);
            wdt_disable();


            // This is compled into 'icall', address should be in word unit, not byte.
            #ifdef BOOTLOADER_SIZE
                ((void (*)(void))( (FLASH_SIZE - BOOTLOADER_SIZE) >> 1))();
            #else
                asm("ijmp" :: "z" (bootloader_start));
            #endif
        }
    #endif
}


#if 0
    /*
     * USBaspLoader - I'm not sure if this is used at all in any projects
     *                would love to support it if it is -Jack
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
