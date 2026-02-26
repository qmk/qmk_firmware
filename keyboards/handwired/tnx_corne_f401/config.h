
#pragma once

// Split configuration
#define SPLIT_HAND_PIN C13
#define SPLIT_HAND_PIN_LOW_IS_LEFT
#define SPLIT_WATCHDOG_ENABLE

// Enable full duplex operation mode 
#define SERIAL_USART_FULL_DUPLEX    
#define SERIAL_USART_TX_PIN      B6
#define SERIAL_USART_RX_PIN      B7

// Tap dance for HRM 
#define TAPPING_TERM 200
#define PERMISSIVE_HOLD

// Mouse key speed and acceleration 
#undef MOUSEKEY_DELAY
#define MOUSEKEY_DELAY          0
#undef MOUSEKEY_INTERVAL
#define MOUSEKEY_INTERVAL       16
#undef MOUSEKEY_WHEEL_DELAY
#define MOUSEKEY_WHEEL_DELAY    0
#undef MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED      6
#undef MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX    64
