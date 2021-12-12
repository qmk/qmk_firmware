/* Copyright 2021 QMK
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
#include <stdint.h>
#include "xtimer.h"
#include "timer.h"

/** \brief timer initialization
 *
 * FIXME: needs doc
 */
void _timer_init(void) { _timer_clear(); }

/** \brief timer clear
 *
 * FIXME: needs doc
 */
inline void _timer_clear(void) {
    // TODO: do nothing?
}

/** \brief timer read
 *
 * FIXME: needs doc
 */
inline uint16_t _timer_read(void) {
    //
    return (uint16_t)(xtimer_now_usec64() / US_PER_MS);
}

/** \brief timer read32
 *
 * FIXME: needs doc
 */
inline uint32_t _timer_read32(void) {
    //
    return (uint32_t)(xtimer_now_usec64() / US_PER_MS);
}

uint16_t _timer_elapsed(uint16_t last) { return TIMER_DIFF_16(timer_read(), last); }

uint32_t _timer_elapsed32(uint32_t last) { return TIMER_DIFF_32(timer_read32(), last); }
