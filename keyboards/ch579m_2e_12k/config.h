/* Copyright 2026 Ryan McLean
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

/* TODO: verify these by probing PCB traces with a multimeter */

/* CRITICAL: EP0 uses 8-byte packets on CH579M (confirmed from lsusb).
 * FIXED_CONTROL_ENDPOINT_SIZE overrides the QMK/LUFA ChibiOS platform default
 * of 64 — without this override the device descriptor advertises 64-byte EP0
 * which causes host enumeration to fail against the 8-byte hardware buffer. */
#define USB_EP0_SIZE                8
#undef  FIXED_CONTROL_ENDPOINT_SIZE
#define FIXED_CONTROL_ENDPOINT_SIZE 8

/* Bypass the USB-suspend gate in protocol_pre_task so the main loop always
 * runs regardless of USB bus state.  Without this the loop blocks inside
 * suspend_power_down(17 ms) whenever USBD1.state == USB_SUSPENDED, which
 * prevents matrix_scan and keyboard report sending from ever executing. */
#define NO_USB_STARTUP_CHECK

/* Debounce handled directly in matrix_scan_custom (eager lockout, LOCKOUT_MS=150).
 * Set to 0 here so QMK's sym_defer_g layer is a pass-through (none.c). */
#define DEBOUNCE 0

/* Encoder 2: A0=phase-A (CW), A5=phase-B (CCW). Confirmed by rotation test.
 * Encoder 1: phase pins not yet identified — TBD once PCB traces are probed.
 * Pin assignments live in keyboard.json "encoder.rotary"; QMK auto-generates
 * ENCODER_A_PINS / ENCODER_B_PINS from there into info_config.h. */
#define ENCODER_RESOLUTION 4
/* Fire encoder event on return-to-rest with any net movement.
 * Tolerates bouncy quadrature signals (enc1 is electrically noisy). */
#define ENCODER_DEFAULT_POS 0x3

