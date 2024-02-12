// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

/*******************************************************************************
  88888888888 888      d8b                .d888 d8b 888               d8b
      888     888      Y8P               d88P"  Y8P 888               Y8P
      888     888                        888        888
      888     88888b.  888 .d8888b       888888 888 888  .d88b.       888 .d8888b
      888     888 "88b 888 88K           888    888 888 d8P  Y8b      888 88K
      888     888  888 888 "Y8888b.      888    888 888 88888888      888 "Y8888b.
      888     888  888 888      X88      888    888 888 Y8b.          888      X88
      888     888  888 888  88888P'      888    888 888  "Y8888       888  88888P'
                                                        888                 888
                                                        888                 888
                                                        888                 888
     .d88b.   .d88b.  88888b.   .d88b.  888d888 8888b.  888888 .d88b.   .d88888
    d88P"88b d8P  Y8b 888 "88b d8P  Y8b 888P"      "88b 888   d8P  Y8b d88" 888
    888  888 88888888 888  888 88888888 888    .d888888 888   88888888 888  888
    Y88b 888 Y8b.     888  888 Y8b.     888    888  888 Y88b. Y8b.     Y88b 888
     "Y88888  "Y8888  888  888  "Y8888  888    "Y888888  "Y888 "Y8888   "Y88888
         888
    Y8b d88P
     "Y88P"
*******************************************************************************/

#pragma once

// Autocorrection dictionary (3 entries):
//   bkj  -> between
//   bekj -> become
//   bkej -> become

#define AUTOCORRECT_MIN_LENGTH 3 // "bkj"
#define AUTOCORRECT_MAX_LENGTH 4 // "bekj"
#define DICTIONARY_SIZE 42

static const uint8_t autocorrect_data[DICTIONARY_SIZE] PROGMEM = {
    0x0D, 0x00, 0x48, 0x09, 0x00, 0x0E, 0x13, 0x00, 0x00, 0x0E, 0x05, 0x00, 0x82, 0x65, 0x63, 0x6F,
    0x6D, 0x65, 0x00, 0x45, 0x1A, 0x00, 0x08, 0x22, 0x00, 0x00, 0x81, 0x65, 0x74, 0x77, 0x65, 0x65,
    0x6E, 0x00, 0x05, 0x00, 0x81, 0x63, 0x6F, 0x6D, 0x65, 0x00
};
