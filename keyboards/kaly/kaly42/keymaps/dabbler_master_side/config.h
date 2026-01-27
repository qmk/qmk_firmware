#pragma once

// must be used to be able to provide power 
// from either side. Unable to make it work.
// Use when flashing: dfu-util-split-left/right.
// Define master left/right must be commented out.
// #define EE_HANDS
// #define SPLIT_USB_DETECT
// #define SPLIT_USB_TIMEOUT 2000
// #define SPLIT_WATCHDOG_ENABLE

#define MASTER_LEFT

#define SERIAL_USART_FULL_DUPLEX   // Enable full duplex operation mode.

#define SERIAL_USART_TX_PIN B6     // USART TX pin
#define SERIAL_USART_RX_PIN B7     // USART RX pin

#define CAPS_WORD_IDLE_TIMEOUT 5000  // Turn off Caps Word after 5 seconds.

#define ONESHOT_TAP_TOGGLE 5  /* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TIMEOUT 500  /* Time (in ms) before the one shot key is released */

#define TAPPING_TERM 300 // global time im millseconds default 200

// Combo settings
#define COMBO_COUNT 9
#define COMBO_TERM 60

// #define COMBO_ONLY_FROM_LAYER 0