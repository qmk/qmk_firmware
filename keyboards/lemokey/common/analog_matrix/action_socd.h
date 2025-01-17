/* Copyright 2024 @ Keychron (https://www.keychron.com)
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

// SOCD Prioritization
enum {
    SOCD_PRI_NONE = 0,
    SOCD_PRI_DEEPER_TRAVEL,
    SOCD_PRI_DEEPER_TRAVEL_SINGLE,
    SOCD_PRI_LAST_KEYSTROKE,
    SOCD_PRI_KEY_1,
    SOCD_PRI_KEY_2,
    SOCD_PRI_NEUTRAL,
    SOCD_PRI_MAX,
};
