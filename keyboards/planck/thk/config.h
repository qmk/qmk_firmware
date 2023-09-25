/*
 * Copyright 2018 Jack Humbert <jack.humb@gmail.com>
 * Copyright 2021 Erovia

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#define DIP_SWITCH_PINS { D0, D1, D4, D6 }

// THK uses D5 for audio
#undef AUDIO_PIN
#define AUDIO_PIN D5

// VUSB D- port
#define USB_CFG_DMINUS_BIT 3
