// Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "christrotter.h"
#ifdef __AVR__
#    include <avr/wdt.h>
#endif

userspace_config_t userspace_config;
