#pragma once

// Serial functions for Atmega32u4

#include "quantum.h"

#define SERIAL_UART_BAUD 153600 //low error rate for 32u4 @ 16MHz
#define RX_BUFFER_SIZE 16
#define TX_BUFFER_SIZE 16

static volatile uint8_t tx_buffer[TX_BUFFER_SIZE],
 tx_buffer_head,
 tx_buffer_tail,
 rx_buffer[RX_BUFFER_SIZE],
 rx_buffer_head,
 rx_buffer_tail;

void
 uart_init(uint32_t baud),
 uart_putchar(uint8_t c);

uint8_t uart_getchar(void),
 uart_available(void);

void uart_init(uint32_t baud) {
  cli();
  UBRR1L = (F_CPU / (16UL * SERIAL_UART_BAUD) - 1);
  UBRR1H = (F_CPU / (16UL * SERIAL_UART_BAUD) - 1) >> 8;
  UCSR1A = (1 << U2X1);
  UCSR1B = (1 << RXEN1) | (1 << TXEN1) | (1 << RXCIE1);
  UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);
  tx_buffer_head = tx_buffer_tail = 0;
  rx_buffer_head = rx_buffer_tail = 0;
  sei();
}

void uart_putchar(uint8_t c) {
  uint8_t i;

  i = tx_buffer_head + 1;
  if (i >= TX_BUFFER_SIZE) i = 0;
  while (tx_buffer_tail == i);
  tx_buffer[i] = c;
  tx_buffer_head = i;
  UCSR1B = (1 << RXEN1) | (1 << TXEN1) | (1 << RXCIE1) | (1 << UDRIE1);
}

uint8_t uart_getchar(void) {
  uint8_t c, i;

  while (rx_buffer_head == rx_buffer_tail); 
  i = rx_buffer_tail + 1;
  if (i >= RX_BUFFER_SIZE) i = 0;
  c = rx_buffer[i];
  rx_buffer_tail = i;
  return c;
}

uint8_t uart_available(void) {
  uint8_t head, tail;

  head = rx_buffer_head;
  tail = rx_buffer_tail;
  if (head >= tail) return head - tail;
  return RX_BUFFER_SIZE + head - tail;
}

ISR(USART1_UDRE_vect) {
  uint8_t i;

  if (tx_buffer_head == tx_buffer_tail) {
    UCSR1B = (1 << RXEN1) | (1 << TXEN1) | (1 << RXCIE1);
  } else {
    i = tx_buffer_tail + 1;
    if (i >= TX_BUFFER_SIZE) i = 0;
    UDR1 = tx_buffer[i];
    tx_buffer_tail = i;
  }
}

ISR(USART1_RX_vect) {
  uint8_t c, i;

  c = UDR1;
  i = rx_buffer_head + 1;
  if (i >= RX_BUFFER_SIZE) i = 0;
  if (i != rx_buffer_tail) {
    rx_buffer[i] = c;
    rx_buffer_head = i;
  }
}