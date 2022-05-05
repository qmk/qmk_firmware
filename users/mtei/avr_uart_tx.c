// Copyright 2022 Takeshi Ishii (@mtei)
// SPDX-License-Identifier: GPL-2.0-or-later

/* clang-format off */
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/atomic.h>

#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega168P__) || defined(__AVR_ATmega328P__)
/* alternate function PD0:RXD,PCINT16, PD1:TXD,PCINT17 */
#define USART_RX_PORT D,0
#define USART_TX_PORT D,1

#define RX_vect    USART_RX_vect
#define UDRE_vect  USART_UDRE_vect
#define TX_vect    USART_TX_vect

#define UBRRL      UBRR0L   /* USART Baud Rate Register 0 Low */
#define UBRRH      UBRR0H   /* USART Baud Rate Register 0 High */
#define UDR        UDR0     /* USART I/O Data Register 0 */
#define UCSRA      UCSR0A   /* USART Control and Status Register 0 A */
#define UCSRB      UCSR0B   /* USART Control and Status Register 0 B */
#define UCSRC      UCSR0C   /* USART Control and Status Register 0 C */

#elif defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega32U2__)
/* alternate function PD2:RXD1,INT2, PD3:TXD1,INT3 */
#define USART_RX_PORT D,2
#define USART_TX_PORT D,3

#define RX_vect    USART1_RX_vect
#define UDRE_vect  USART1_UDRE_vect
#define TX_vect    USART1_TX_vect

#define UBRRL      UBRR1L   /* USART Baud Rate Register 1 Low */
#define UBRRH      UBRR1H   /* USART Baud Rate Register 1 High */
#define UDR        UDR1     /* USART I/O Data Register 1 */
#define UCSRA      UCSR1A   /* USART Control and Status Register 1 A */
#define UCSRB      UCSR1B   /* USART Control and Status Register 1 B */
#define UCSRC      UCSR1C   /* USART Control and Status Register 1 C */

#elif defined (__AVR_ATtiny2313__)
/* alternate function PD0:RXD, PD1:TXD */
#define USART_RX_PORT D,0
#define USART_TX_PORT D,1

#define RX_vect    USART_RX_vect
#define UDRE_vect  USART_UDRE_vect
#define TX_vect    USART_TX_vect

//#define UBRRL      UBRRL   /* USART Baud Rate Register 0 Low */
//#define UBRRH      UBRRH   /* USART Baud Rate Register 0 High */
//#define UDR        UDR     /* USART I/O Data Register 0 */
//#define UCSRA      UCSRA   /* USART Control and Status Register A */
//#define UCSRB      UCSRB   /* USART Control and Status Register B */
//#define UCSRC      UCSRC   /* USART Control and Status Register C */

#else
   #error avr_uart_tx.c not yet support your AVR
#endif

/* USART Control and Status Register x A */
#define   RXCV   (1<<7)   /*   Receive Complate (R only) */
#define   TXCV   (1<<6)   /*   Transmit Complate (R/W) */
#define   UDREV  (1<<5)   /*   Transmit Data Register Empty (R only) */
#define   FEV    (1<<4)   /*   Framing Error (R only) */
#define   DORV   (1<<3)   /*   Data OverRun (R only) */
#define   UPEV   (1<<2)   /*   Parity Error (R only) */
#define   U2XV   (1<<1)   /*   Double the USART Transmission Speed (R/W) */
#define   MPCMV  (1<<0)   /*   Multi-Procesor Communication Mode (R/W) */
/* USART Control and Status Register x B */
#define   RXCIEV (1<<7)   /*   Receive Complete Interrupt Enable (R/W) */
#define   TXCIEV (1<<6)   /*   Transmit Complete Inter Enable (R/W) */
#define   UDRIEV (1<<5)   /*   Transmit Data Regi Empty Inter Enable(R/W)*/
#define   RXENV  (1<<4)   /*   Receiver Enable (R/W) */
#define   TXENV  (1<<3)   /*   Transmitter Enable (R/W) */
#define   UCSZ2V (1<<2)   /*   Character Size (9bit) (R/W) */
#define   RXB8V  (1<<1)   /*   Receive Data Bit 8 (R only) */
#define   TXB8V  (1<<0)   /*   Transmit Data Bit 8 (R/W) */
/* USART Control and Status Register x C */
#define   UMSEL_ASYNC  0     /*   Mode Select bit 7:6 (R/W) */
#define   UPM_NONE     0     /*   Parity Mode bit 5:4 (R/W) */
#define   UPM_EVEN     0x20
#define   UPM_ODD      0x30
#define   USBS_1       0     /*   Stop Bit Select 1,2 (R/W) */
#define   USBS_2       0x8
#define   UCSZ_5       0     /*   Character Size 5,6,7,8 */
#define   UCSZ_6       0x2
#define   UCSZ_7       0x4
#define   UCSZ_8       0x6

#define   BORV   (1<<0)   /*   soft buffer over run */

void init_avr_uart_tx(uint16_t ubrr_value) {
    UBRRH = (ubrr_value >> 8) ;
    UBRRL = (ubrr_value & 0xff);
    UCSRA = 0;
    UCSRB = 0;
    UCSRC = (UMSEL_ASYNC | UPM_NONE | USBS_1 | UCSZ_8);
    UCSRB |= TXENV;
}

void send_avr_uart_tx(uint8_t data) {
    while (!(UCSRA & UDREV)) {
        __builtin_avr_delay_cycles(2);
    }
    UDR = data;
}
