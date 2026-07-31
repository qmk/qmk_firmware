// Copyright 2026 Heer (@heer)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// ── OLED (SH1106 1.3", 128×64, I2C address 0x3C) ────────────────────────────
#define OLED_DISPLAY_128X64
#define OLED_IC              OLED_IC_SH1106
#define OLED_COLUMN_OFFSET   2
#define OLED_BRIGHTNESS      180
#define OLED_TIMEOUT              0
#define OLED_UPDATE_INTERVAL      10
// NOTE: do NOT raise OLED_UPDATE_PROCESS_LIMIT. The default of 1 keeps each I2C
// transaction to a single 32-byte block.
//
// TESTED, TWICE, ON HARDWARE: a limit of 4 — only 128 bytes, one page, the write
// size stock SSD1306/SH1106 drivers use — blanks this panel completely. The board
// keeps running (keys and encoders work) but the display never comes up. The
// reasoning that "a page is safe because everyone writes pages" is wrong for this
// module. Do not try it again.
//
// OLED_UPDATE_INTERVAL is a different knob and is safe to shorten: it changes how
// OFTEN a block is flushed, not how BIG the transaction is, which stays one
// 32-byte block. At the old 33ms, swapping the right-hand panel between the key
// grid and the encoder bars took ~21 blocks * 33ms = ~700ms to reach the glass —
// you would turn the knob and see the bar most of a second later. 10ms puts that
// at ~210ms. If the panel ever misbehaves, this is the first value to put back.

// ── I2C (OLED on GP16=SDA, GP17=SCL via RP2040 I2C0) ────────────────────────
#define I2C_DRIVER   I2CD0
#define I2C1_SDA_PIN GP16
#define I2C1_SCL_PIN GP17
