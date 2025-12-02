// Copyright 2025 QMK
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

// Autocorrection dictionary (7 entries):
// From /home/drashna/repos/qmk_firmware/../qmk_secrets/autocorrection_dict_test.txt
//   fales -> false
//   :ture -> true
// ---------------
// From /home/drashna/repos/qmk_firmware/../qmk_secrets/typos_small.txt
//   :iv'e:    -> I've
//   activbate -> activate
//   :atcually -> actually
//   :agian    -> again
//   :laso:    -> also
// ---------------

#define N_DICTS 2

static const uint32_t autocorrect_offsets[N_DICTS] PROGMEM     = {0, 26};
static const uint16_t autocorrect_min_lengths[N_DICTS] PROGMEM = {5, 6};
static const uint16_t autocorrect_max_lengths[N_DICTS] PROGMEM = {5, 9};
static const uint32_t autocorrect_sizes[N_DICTS] PROGMEM       = {26, 85};
static const uint8_t  autocorrect_node_size[N_DICTS] PROGMEM    = {2, 2};

#define DICTIONARY_SIZE 111
#define TYPO_BUFFER_SIZE 9

static const uint8_t autocorrect_data[DICTIONARY_SIZE] PROGMEM = {
    0x48, 0x07, 0x00, 0x16, 0x11, 0x00, 0x00, 0x15, 0x18, 0x17, 0x2C, 0x00, 0x82, 0x72, 0x75, 0x65,
    0x00, 0x08, 0x0F, 0x04, 0x09, 0x00, 0x81, 0x73, 0x65, 0x00, 0x6C, 0x0D, 0x00, 0x08, 0x2A, 0x00,
    0x11, 0x38, 0x00, 0x1C, 0x43, 0x00, 0x00, 0x48, 0x14, 0x00, 0x12, 0x1F, 0x00, 0x00, 0x34, 0x19,
    0x0C, 0x2C, 0x00, 0x84, 0x49, 0x27, 0x76, 0x65, 0x00, 0x16, 0x04, 0x0F, 0x2C, 0x00, 0x84, 0x61,
    0x6C, 0x73, 0x6F, 0x00, 0x17, 0x04, 0x05, 0x19, 0x0C, 0x17, 0x06, 0x04, 0x00, 0x83, 0x61, 0x74,
    0x65, 0x00, 0x04, 0x0C, 0x0A, 0x04, 0x2C, 0x00, 0x82, 0x61, 0x69, 0x6E, 0x00, 0x0F, 0x0F, 0x04,
    0x18, 0x06, 0x17, 0x04, 0x2C, 0x00, 0x86, 0x63, 0x74, 0x75, 0x61, 0x6C, 0x6C, 0x79, 0x00
};
