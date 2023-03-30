/*
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

// -----------------------------------------------------
// NOTE: THIS HEADER IS ALSO INCLUDED BY ASSEMBLER SO
//       SHOULD ONLY CONSIST OF PREPROCESSOR DIRECTIVES
// -----------------------------------------------------
//
//------------------------------------------------------------------------------------------
// Board definition for the Solder Party RP2040 Stamp Carrier
//
// This header may be included by other board headers as "boards/solderparty_rp2040_stamp_carrier.h"

#ifndef _BOARDS_SOLDERPARTY_RP2040_STAMP_CARRIER_H
#define _BOARDS_SOLDERPARTY_RP2040_STAMP_CARRIER_H

// For board detection
#define SOLDERPARTY_RP2040_STAMP_CARRIER

#ifndef PICO_DEFAULT_LED_PIN
#define PICO_DEFAULT_LED_PIN   20
#endif

#include "solderparty_rp2040_stamp.h"

#endif
