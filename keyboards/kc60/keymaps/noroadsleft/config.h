/* Copyright 2018-2020 James Young (@noroadsleft)
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

#define PERMISSIVE_HOLD // https://docs.qmk.fm/#/feature_advanced_keycodes?id=permissive-hold

// Enable single-color backlighting
#define BACKLIGHT_BREATHING
#define BACKLIGHT_LEVELS 5
#define BREATHING_PERIOD 4

#ifdef LOCKING_SUPPORT_ENABLE
#   undef LOCKING_SUPPORT_ENABLE
#endif
#ifdef LOCKING_RESYNC_ENABLE
#   undef LOCKING_RESYNC_ENABLE
#endif

#define NO_ACTION_ONESHOT

#define ANSI_NUBS_ROW 3
#define ANSI_NUBS_COL 2
