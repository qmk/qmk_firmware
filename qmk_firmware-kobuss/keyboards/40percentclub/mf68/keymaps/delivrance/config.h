/*
 * Dan's Magicforce 68 (MF68) QMK Keyboard
 * Copyright (C) Dan <https://github.com/delivrance>
 *
 * This file is part of Dan's MF68 QMK Keyboard.
 *
 * Dan's MF68 QMK Keyboard is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Dan's MF68 QMK Keyboard is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Dan's MF68 QMK Keyboard.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#undef MANUFACTURER
#define MANUFACTURER Dan

#undef PRODUCT
#define PRODUCT Magicforce 68 QMK

#undef BACKLIGHT_LEVELS
#define BACKLIGHT_LEVELS 20

// Disable backlight breathing
#undef BACKLIGHT_BREATHING

// Set USB polling rate to 1000 Hz
#define USB_POLLING_INTERVAL_MS 1

// Enable NKRO on boot
#define FORCE_NKRO

// Backlight idle timeout in seconds
#define BACKLIGHT_IDLE_TIMEOUT 1200