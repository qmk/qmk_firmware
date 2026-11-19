/* Copyright 2026 ryanm
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
#include "quantum.h"
#include "CH579.h"
#include "encoder.h"

/* encoder_quadrature_handle_read declared in encoder_quadrature.c (no public header) */
extern void encoder_quadrature_handle_read(uint8_t index, uint8_t pin_a_state, uint8_t pin_b_state);

/* Override weak encoder_driver_task — read encoder pins directly from hardware
 * registers.  enc1 (index 0): B0=phase-A, B1=phase-B.
 *              enc2 (index 1): A0=phase-A, A5=phase-B. */
void encoder_driver_task(void) {
    uint32_t pb = R32_PB_PIN;
    uint32_t pa = R32_PA_PIN;
    encoder_quadrature_handle_read(0, (uint8_t)((pb >> 0) & 1u), (uint8_t)((pb >> 1) & 1u));
    encoder_quadrature_handle_read(1, (uint8_t)((pa >> 0) & 1u), (uint8_t)((pa >> 5) & 1u));
}
