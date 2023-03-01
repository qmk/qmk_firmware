// Copyright 2022 CAO THAI DUONG (@KD-MM2)
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
#define DIODE_DIRECTION ROW2COL
 
#define MATRIX_ROW_PINS { B0, B1, B2, B3, B4, B5 }
#define MATRIX_COL_PINS { D3, D2, D1, D0, D4, C6, D7, E6, B7, F0, F1, D6, C7, B6, F7, F6, F5, F4 }
