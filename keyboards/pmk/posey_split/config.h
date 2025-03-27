// Copyright 2023 Javier Oliver (@joliverMI)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*Split keyboard configuration*/
// Hardware Settings
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP1
#define SERIAL_USART_RX_PIN GP0

// Communication Settings
#define FORCED_SYNC_THROTTLE_MS 1000
#define SPLIT_MAX_CONNECTION_ERRORS 5
#define SPLIT_CONNECTION_CHECK_TIMEOUT 2000

// RGB Configuration
#define RGBLIGHT_EFFECT_BREATHE_CENTER 2.0 //1.0 to 2.7