/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2020 Ploopy Corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include <stdbool.h>

#ifndef SCROLLER_AR_SIZE
#    define SCROLLER_AR_SIZE 31
#endif

#ifndef SCROLL_THRESH_RANGE_LIM
#    define SCROLL_THRESH_RANGE_LIM 10
#endif

enum State { HIHI, HILO, LOLO, LOHI };

extern enum State state;

/* Variables used for scroll wheel functionality. */
extern bool lohif;
extern bool hilof;
extern int  lowA;
extern int  highA;
extern bool cLowA;
extern bool cHighA;
extern int  lowIndexA;
extern int  highIndexA;
extern bool lowOverflowA;
extern bool highOverflowA;
extern int  lowB;
extern int  highB;
extern bool cLowB;
extern bool cHighB;
extern int  lowIndexB;
extern int  highIndexB;
extern bool lowOverflowB;
extern bool highOverflowB;
extern int  scrollThresholdA;
extern int  scrollThresholdB;
extern int  arLowA[SCROLLER_AR_SIZE];
extern int  arHighA[SCROLLER_AR_SIZE];
extern int  arLowB[SCROLLER_AR_SIZE];
extern int  arHighB[SCROLLER_AR_SIZE];

void calculateThresholdA(int curA);
void calculateThresholdB(int curB);
int  calculateThreshold(int cur, int* low, int* high, bool* cLow, bool* cHigh, int arLow[], int arHigh[], int* lowIndex, int* highIndex, bool* lowOverflow, bool* highOverflow);
int  thresholdEquation(int lo, int hi);
void incrementIndex(int* index, bool* ovflw);

void opt_encoder_init(void);
int  opt_encoder_handler(int curA, int curB);
