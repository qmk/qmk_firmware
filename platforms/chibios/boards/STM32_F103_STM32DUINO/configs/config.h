// Copyright 2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

// Value to place in RTC backup register 10 for persistent bootloader mode
#define RTC_BOOTLOADER_FLAG 0x424C

// Value to place in RTC backup register 10 for instant reboot mode
#define RTC_BOOTLOADER_JUST_UPLOADED 0x424D
