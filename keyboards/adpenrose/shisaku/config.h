// Copyright 2022 Arturo Avila (@ADPenrose)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once


/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */
#define MATRIX_ROW_PINS { B2, B0, B1, D0, B4, D6, B3, D7 }
#define MATRIX_COL_PINS { D1, C3, C4, D4, C0, C1, C2 }

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Solenoid pin */
#define SOLENOID_PIN C5
