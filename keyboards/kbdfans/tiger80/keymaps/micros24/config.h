/* Copyright 2022 micros24 <jasperjano.ph@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

/* Disable locking support */
#ifdef LOCKING_SUPPORT_ENABLE
	#undef LOCKING_SUPPORT_ENABLE
#endif

/* Disable locking support */
#ifdef LOCKING_RESYNC_ENABLE
	#undef LOCKING_RESYNC_ENABLE
#endif

/* Increasing performance */
#define MATRIX_IO_DELAY 20
#define FORCE_NKRO

/* Disable unused features to save space */
#define NO_ACTION_LAYER
#define NO_ACTION_ONESHOT

/* Tap-Hold configuration */
#define TAPPING_TERM 200