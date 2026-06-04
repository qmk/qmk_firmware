// Copyright 2024 SM Boards (@sm_boards)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* ============================================================
   I2C buses
   ------------------------------------------------------------
   The Macro2040 uses BOTH I2C peripherals on the RP2040:
     I2C0  →  AS5600 magnetic encoder  (handled by QMK i2c_master)
     I2C1  →  SSD1306 OLED display     (handled by oled_custom.c)
   QMK's `i2c_master` always reads its pins from I2C1_SDA_PIN /
   I2C1_SCL_PIN regardless of which physical peripheral the
   I2C_DRIVER macro selects, so we set those defines to the
   AS5600 pins (GP4/GP5) and point I2C_DRIVER at I2CD0.
   ============================================================ */

// Pins used by QMK's i2c_master to talk to the AS5600.
#define I2C1_SDA_PIN     GP4
#define I2C1_SCL_PIN     GP5
#define I2C1_CLOCK_SPEED 50000   // 50 kHz — conservative, very reliable

// Tell QMK's i2c_master to drive the I2C0 peripheral.
#define I2C_DRIVER I2CD0

// Pins used by oled_custom.c to talk to the OLED. These are
// referenced from the OLED driver only — i2c_master ignores them.
#define OLED_SDA_PIN GP18
#define OLED_SCL_PIN GP19

/* ============================================================
   AS5600 magnetic encoder
   ============================================================ */

#define AS5600_ADDRESS    0x36   // 7-bit I2C address
#define AS5600_ANGLE_REG  0x0C   // Raw 12-bit angle register (0..4095)

// Number of raw angle units that constitute one virtual encoder
// "click". 4096 units = 360°, so 50 units ≈ 4.4° per pulse.
// Increase to make the knob feel chunkier, decrease to make it more sensitive.
#define AS5600_RESOLUTION 50

// GPIOs we drive with the synthetic A/B quadrature pulses. These are
// physically wired back to the QMK encoder input pins on the PCB.
#define AS5600_PIN_A GP20   // PULA — quadrature channel A output
#define AS5600_PIN_B GP21   // PULB — quadrature channel B output

/* ============================================================
   OLED display
   ============================================================ */

// SSD1306 7-bit I2C address (SA0 tied to GND on this PCB).
// The OLED is driven by oled_custom.c on I2CD1; QMK's built-in
// OLED feature is intentionally NOT enabled because it would
// fight i2c_master for I2C0.
#define OLED_I2C_ADDRESS 0x3C

/* ============================================================
   Blue switch indicator LEDs
   ------------------------------------------------------------
   Six blue LEDs sit underneath the key switches in two columns
   of three. Each column is driven by an NPN transistor whose
   base is one GPIO. Driving the GPIO HIGH turns the column on.
   ============================================================ */

#define LED_COL0_PIN GP13   // Q4 base — controls SW3B, SW5B, SW7B (left column)
#define LED_COL1_PIN GP12   // Q3 base — controls SW4B, SW6B, SW8B (right column)

/* ============================================================
   User LED (D6)
   ------------------------------------------------------------
   Single blue LED wired:  +3V3 → R33 (330R) → LED → GP25.
   Active-LOW: GP25 LOW = LED ON, GP25 HIGH = LED OFF.
   Used as a "device alive" indicator and to blink the active
   layer number whenever the layer changes.
   ============================================================ */

#define USER_LED_PIN GP25

/* ============================================================
   Encoder
   ============================================================ */

// Minimum delay between encoder map keypresses (ms). Prevents
// the host from missing rapid encoder spins.
#define ENCODER_MAP_KEY_DELAY 10
