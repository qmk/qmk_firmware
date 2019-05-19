#pragma once

#include "pointing_device.h"
#include "quantum.h"
#include "report.h"
#include <util/delay.h>
#include "../../lib/lufa/LUFA/Drivers/Peripheral/SPI.h"

// Trackpad speed adjustments
#define POINTER_SPEED_MULTIPLIER 2
#define SCROLL_SPEED_DIVIDER 6

// Pins on corresponding ports
#define TP_RESET     1
#define TP_SHUTDOWN  0
#define TP_CS        0
#define LVL_SHIFT_EN 7

// Configure as output
#define TP_RESET_INIT     DDRF |= (1 << TP_RESET);
#define TP_SHUTDOWN_INIT  DDRF |= (1 << TP_SHUTDOWN);
#define TP_CS_INIT        DDRB |= (1 << TP_CS);
#define LVL_SHIFT_EN_INIT DDRC |= (1 << LVL_SHIFT_EN);

#define TP_RESET_HI     PORTF |= (1 << TP_RESET);
#define TP_RESET_LO     PORTF &= ~ (1 << TP_RESET);
#define TP_SHUTDOWN_HI  PORTF |= (1 << TP_SHUTDOWN);
#define TP_SHUTDOWN_LO  PORTF &= ~ (1 << TP_SHUTDOWN);
#define TP_CS_HI        PORTB |= (1 << TP_CS);
#define TP_CS_LO        PORTB &= ~ (1 << TP_CS);
#define LVL_SHIFT_EN_HI PORTC |= (1 << LVL_SHIFT_EN);
#define LVL_SHIFT_EN_LO PORTC &= ~ (1 << LVL_SHIFT_EN);
