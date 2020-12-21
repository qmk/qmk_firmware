/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2013 Oleg Kostyuk <cub.uanic@gmail.com>
Copyright 2015 ZSA Technology Labs Inc (@zsa)
Copyright 2020 Christopher Courtney <drashna@live.com> (@drashna)

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

#if !defined(ERGODOX_LED_15) && !defined(ERGODOX_LED_30)
// if no value is defined, assume previous behavior
// #    define ERGODOX_LED_15
// #    define ERGODOX_LED_30
#    define ERGODOX_LED_15_MIRROR
#endif

#if (defined(ERGODOX_LED_30) + defined(ERGODOX_LED_15) + defined(ERGODOX_LED_15_MIRROR)) != 1
#    error "You must only define one of the ERGODOX_LED options."
#endif

#ifdef ERGODOX_LED_30
// If using 30 LEDs, then define that many
#    define RGBLED_NUM 30  // Number of LEDs
#else
// If not, then only define 15
#    define RGBLED_NUM 15  // Number of LEDs
#endif
