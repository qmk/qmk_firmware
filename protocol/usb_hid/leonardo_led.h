#ifndef LEONARDO_LED_H
#define LEONARDO_LED_H

// Leonardo "TX" LED for debug
#define LED_TX_INIT    (DDRD  |=  (1<<5))
#define LED_TX_ON      (PORTD &= ~(1<<5))
#define LED_TX_OFF     (PORTD |=  (1<<5))
#define LED_TX_TOGGLE  (PORTD ^=  (1<<5))

#endif
