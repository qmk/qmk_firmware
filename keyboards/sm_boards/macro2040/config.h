// Copyright 2024 SM Boards (@sm_boards)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* ============================================================
   I2C buses
   ------------------------------------------------------------
   The Macro2040 uses BOTH I2C peripherals on the RP2040:
     I2C0 (GP4/GP5)   →  AS5600 magnetic encoder, driven directly
                         via the ChibiOS I2C API in macro2040.c
     I2C1 (GP18/GP19) →  SSD1306 OLED via QMK's core OLED driver
                         (which talks through i2c_master)
   i2c_master always reads its pins from I2C1_SDA_PIN / I2C1_SCL_PIN
   regardless of which peripheral I2C_DRIVER selects, so those point
   at the OLED bus (I2C1).
   ============================================================ */

// QMK i2c_master — used by the core OLED driver — on the I2C1 peripheral.
#define I2C_DRIVER       I2CD1
#define I2C1_SDA_PIN     GP18
#define I2C1_SCL_PIN     GP19
#define I2C1_CLOCK_SPEED 400000

/* ============================================================
   AS5600 magnetic encoder
   ============================================================ */

#define AS5600_ADDRESS    0x36   // 7-bit I2C address
#define AS5600_ANGLE_REG  0x0C   // Raw 12-bit angle register (0..4095)

// AS5600 sits alone on the I2C0 peripheral, driven directly via ChibiOS.
#define AS5600_SDA_PIN GP4
#define AS5600_SCL_PIN GP5

// Number of raw angle units that constitute one virtual encoder
// "click". 4096 units = 360°, so 50 units ≈ 4.4° per pulse.
// Increase to make the knob feel chunkier, decrease to make it more sensitive.
#define AS5600_RESOLUTION 50

// GPIOs we drive with the synthetic A/B quadrature pulses. These are
// physically wired back to the QMK encoder input pins on the PCB.
#define AS5600_PIN_A GP20   // PULA — quadrature channel A output
#define AS5600_PIN_B GP21   // PULB — quadrature channel B output

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
   Lit at the keyboard level as a "device alive" indicator.
   ============================================================ */

#define USER_LED_PIN GP25

/* ============================================================
   Encoder
   ============================================================ */

// Minimum delay between encoder map keypresses (ms). Prevents
// the host from missing rapid encoder spins.
#define ENCODER_MAP_KEY_DELAY 10
