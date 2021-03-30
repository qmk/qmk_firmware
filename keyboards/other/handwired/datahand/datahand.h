/* Copyright 2017-2019 Nikolaus Wittenstein <nikolaus.wittenstein@gmail.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#pragma once

#include "quantum.h"

/* This a shortcut to help you visually see your layout.
 * The first section contains all of the arguements; the second converts the arguments into a two-dimensional array.
 */

/* Each code is three letters
 * l or r - left or right hand
 * p, r, m, i, t - pinky, ring finger, middle finger, index finger, thumb
 * fingers: n, s, e, w, c - north, south, east, west, and center (manual calls this "well" but we already have "west")
 * thumb:   p, n, c, l, u, k - pad, nail, center, lock (harder center), up, knuckle
 */
#define LAYOUT( \
     lpn,             lrn,             lmn,             lin,                rin,             rmn,             rrn,             rpn,      \
lpw, lpc, lpe,   lrw, lrc, lre,   lmw, lmc, lme,   liw, lic, lie,      riw, ric, rie,   rmw, rmc, rme,   rrw, rrc, rre,   rpw, rpc, rpe, \
     lps,             lrs,             lms,             lis,                ris,             rms,             rrs,             rps,      \
                                                       ltp,    ltn,  rtn,    rtp, \
                                                           ltc,          rtc, \
                                                           ltl,          rtl, \
                                                       ltu,    ltk,  rtk,    rtu) \
{ \
  {riw, rin, lpw, lpn},\
  {ric, rie, lpc, lpe},\
  {ris, rms, lps, lrs},\
  {rmw, rmn, lrw, lrn},\
  {rmc, rme, lrc, lre},\
  {rrw, rrn, lmw, lmn},\
  {rrc, rre, lmc, lme},\
  {rrs, rps, lms, lis},\
  {rpw, rpn, liw, lin},\
  {rpc, rpe, lic, lie},\
  {rtk, rtn, ltk, ltn},\
  {rtc, rtl, ltc, ltl},\
  {rtp, rtu, ltp, ltu},\
}

/* Mode LEDs are active-low on Port B on the Teensy. */
#define LED_MODE_PORT PORTB
#define LED_TENKEY    (1<<3)
#define LED_FN        (1<<4)
#define LED_NORMAL    (1<<5)
#define LED_NAS       (1<<6)

/* Lock LEDs are active-low on Port F on the Teensy. */
#define LED_LOCK_PORT   PORTF
#define LED_CAPS_LOCK   (1<<4)
#define LED_MOUSE_LOCK  (1<<5)
#define LED_NUM_LOCK    (1<<6)
#define LED_SCROLL_LOCK (1<<7)


/* Appendix:
 * Table based on https://geekhack.org/index.php?topic=12212.msg2059319#msg2059319
 * Some pin assignments (e.g. for PS/2 I/O) have been fixed.
 *
 * Teensy    Datahand     8051   pin     pin      8051    Datahand             Teensy
 * ------    --------     ----   ---     ---      ----    --------             ------
 * GND       Mtrx send A  P1.0     1      40      VCC     VCC                  VCC
 * PB7       Mtrx send B  P1.1     2      39      P0.0    LED RH NAS           PB6
 * PD0       Mtrx send C  P1.2     3      38      P0.1    LED RH NORM          PB5
 * PD1       Mtrx send D  P1.3     4      37      P0.2    LED RH FCTN          PB4
 * PD2       RH rcv 0     P1.4     5      36      P0.3    LED RH 10K           PB3
 * PD3       RH rcv 1     P1.5     6      35      P0.4    LED RH unused        PB2
 * PD4       LH rcv 0     P1.6     7      34      P0.5    LED RH unused        PE1
 * PD5       LH rcv 1     P1.7     8      33      P0.6    LED RH unused        PE0
 * PD6       Reset button RST      9      32      P0.7    ?                    PE7
 * PD7       ?            P3.0    10      31      VPP     -                    PE6
 * PE0       ?            P3.1    11      30      ALE     -                    GND
 * PE1       kbd data     P3.2    12      29      PSEN    -                    AREF
 * PC0       ?            P3.3    13      28      P2.7    ?                    PF0
 * PC1       kbd clk      P3.4    14      27      P2.6    ?                    PF1
 * PC2       ?            P3.5    15      26      P2.5    ?                    PF2
 * PC3       RAM          P3.6    16      25      P2.4    ?                    PF3
 * PC4       RAM          P3.7    17      24      P2.3    LED D15 LH (CAPLK)   PF4
 * PC5       XTAL2        XTAL2   18      23      P2.2    LED D13 LH (MSELK)   PF5
 * PC6       XTAL1        XTAL1   19      22      P2.1    LED D6  LH (NUMLK)   PF6
 * PC7       GND          GND     20      21      P2.0    LED D14 LH (SCRLK)   PF7
 *
 * JP3 Pinout
 * 2 - keyboard data
 * 3 - keyboard clock
 *
 * In order to get the Teensy to work, we need to move pin 1 to a different pin. This is
 * because on the Teensy pin 1 is ground, but we need to write to pin 1 in order to read
 * the keyboard matrix. An ideal pin to move it to is VPP (pin 31), because this pin tells
 * the 8051 whether it should read from external or internal memory. The Teensy doesn't
 * care about that.
 *
 * The easiest way to reassign the pin is to use standoffs. You can check out this thread:
 * https://geekhack.org/index.php?topic=12212.msg235382#msg235382 for a picture of what
 * this looks like. Note that in the picture the pin has been reassigned to pin 12. We
 * don't want to do that because we're going to use that pin to send data over PS/2.
 *
 * We could if we wanted also reassign the PS/2 pins to Teensy hardware UART pins, but
 * that's more work. Instead we'll just bit-bang PS/2 because it's an old, slow protocol
 * (and because there's already a bit-banged PS/2 host implementation in QMK - we just
 * need to add the device side).
 *
 * So overall, we want the following inputs and outputs:
 * Outputs:
 *   Matrix:
 *     PB7
 *     PD0
 *     PD1
 *     PE6 (moved from pin1, GND)
 *   LEDs:
 *     PB3-6
 *     PF4-7
 * Inputs:
 *   Matrix:
 *     PD2-5
 * I/Os (start up as inputs):
 *   PS/2:
 *     PC1
 *     PE1
 */
