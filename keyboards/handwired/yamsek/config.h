/* Copyright 2023 Johannes Schneider (@JohSchneider) */
/* SPDX-License-Identifier: GPL-2.0-or-later */
#pragma once

/* colum major:
   first four rows are on the lefthand side, behind a port expander
   next four rows are on the rightnad side, connected to the single MCU running this keyboard
*/

// black mark on diode facing columns
#define DIODE_DIRECTION ROW2COL


/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5
