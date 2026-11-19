/* Copyright 2026 NUTWANG
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

#include "kb17.h"

#include "hal.h"
#include "hal_low_power_lld.h"

/* Real CPU low power while the USB bus is suspended.
 * suspend_power_down_kb() is invoked on every iteration of the suspend loop
 * in protocol_pre_task() (tmk_core/protocol/chibios/chibios.c) while the bus
 * stays suspended.  We override the weak default here to enter the SK32 STOP
 * mode (deep sleep) instead of the plain wait_ms(17) busy loop: the core halts
 * until an interrupt wakes it (the forced USB RESUME kept armed by the USB
 * low level driver, or an EXTI).  On a confirmed wakeup suspend_wakeup_init_kb()
 * rebuilds the system/PLL clocks torn down by STOP.
 * Gated on SK32_HAL_USE_LOWPOWER so it only affects this board. */
#if (SK32_HAL_USE_LOWPOWER == TRUE)

/* KB17 matrix: 5 rows x 4 cols, DIODE_DIRECTION ROW2COL (see config.h).
 * The QMK matrix scan drives a column low (select_col) and reads the rows as
 * inputs with pull-up.  While the core sleeps we mirror that electrical state:
 * every row is an input with pull-up armed on both EXTI edges, and every
 * column is held as a push-pull output LOW.  Pressing any key shorts its row
 * to the (low) column (falling edge) and releasing it lets the pull-up take
 * the row high again (rising edge), so any key activity exits STOP.
 *
 * The rows/columns are taken straight from the matrix configuration
 * (MATRIX_ROW_PINS / MATRIX_COL_PINS in config.h, generated MATRIX_ROWS /
 * MATRIX_COLS from keyboard.json) instead of being hard-coded here, so the
 * STOP wake wiring always follows the matrix layout.  Each pin (B2, ...) is
 * an ioline_t (PAL_LINE(...)), which is what arm/release drive directly. */
static const ioline_t kb17_wake_rows[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const ioline_t kb17_wake_cols[MATRIX_COLS] = MATRIX_COL_PINS;

/* Set once the host has been told about the current key press, so that a key
 * held down is reported once instead of on every pass of the suspend loop.
 * Cleared as soon as no key is down any more, and when a suspend session
 * ends (suspend_wakeup_init_kb). */
static bool kb17_press_reported = false;

/* Passes of the suspend loop left to stay out of STOP after the host has been
 * signalled.  STOP gates off the USB clock, so sleeping while the host answers
 * our resume burst (it drives its own resume, then SOF) makes the driver miss
 * the answer and the machine never comes back.  One pass is a suspend loop
 * iteration (~wait_ms(17) plus a matrix scan), so this is roughly 0.8 s of
 * settle time. */
#define KB17_WAKE_SETTLE_PASSES 40U
static uint16_t kb17_wake_settle = 0U;

#define KB17_WAKE_ROW_COUNT (sizeof(kb17_wake_rows) / sizeof(kb17_wake_rows[0]))
#define KB17_WAKE_COL_COUNT (sizeof(kb17_wake_cols) / sizeof(kb17_wake_cols[0]))

static uint32_t kb17_wake_row_mask(void) {
    uint32_t mask = 0U;

    for (unsigned i = 0U; i < KB17_WAKE_ROW_COUNT; i++) {
        mask |= 1U << (uint32_t)PAL_PAD(kb17_wake_rows[i]);
    }

    return mask;
}

/* Samples the rows with the columns still held LOW by the arming above: a key
 * that is down shunts its row to the driven-low column and reads back as a
 * low level.  Returns the same bit layout as kb17_wake_row_mask(). */
static uint32_t kb17_stop_wake_pins_pressed(void) {
    uint32_t pressed = 0U;

    for (unsigned i = 0U; i < KB17_WAKE_ROW_COUNT; i++) {
        if (palReadLine(kb17_wake_rows[i]) == PAL_LOW) {
            pressed |= 1U << (uint32_t)PAL_PAD(kb17_wake_rows[i]);
        }
    }

    return pressed;
}

/* Arms every row as a STOP wake source and holds every column LOW.
 * Reference: SK32F0xx_Firmware Package 26_07_21, RGBKeyboardSTK
 * (Mechanical_SRGB), User/Src/kbcuDrive.c -> KBCUDVE_SleepInit(): before
 * PWR_EnterSTOPMode() the vendor switches each key to input with pull-up and
 * arms its EXTI line so the key pulls the core out of deep sleep.  For a
 * ROW2COL matrix the equivalent is to keep all columns selected (output LOW)
 * so any key press pulls its row down.
 *
 * Both edges are armed - the same choice the vendor makes for the USB resume
 * line (EXTI->RTSR | EXTI->FTSR, see USBUSER_Init()): a press, a release and
 * a tap that opens and closes inside the same sleep window are all key
 * activity, and any of them must be able to pull the core out of STOP.
 *
 * Returns the rows that are pulled low at arming time, in the same bit layout
 * as kb17_wake_row_mask().  This level sample is what makes the wake reliable:
 * the columns are driven low here exactly like a matrix scan drives them, so
 * every key that is down shows up in it - including one that was already down
 * when the core went to sleep, whose edge was dropped by the EXTI->PR clear
 * below and which produces no further edge for as long as it is held. */
static uint32_t kb17_stop_wake_pins_arm(void) {
    uint32_t row_mask = kb17_wake_row_mask();

    /* The EXTI line -> port mapping lives in SYSCFG, which needs its APB2
       clock (the vendor calls RCC_APB2PeriphClockCmd(..SYSCFG, ENABLE) in
       KBCUDVE_SleepInit() for the same reason). */
    rccEnableAPB2(RCC_APB2ENR_SYSCFGEN, true);

    for (unsigned i = 0U; i < KB17_WAKE_ROW_COUNT; i++) {
        ioline_t line  = kb17_wake_rows[i];
        uint32_t pad   = (uint32_t)PAL_PAD(line);
        uint32_t port  = (((uint32_t)PAL_PORT(line) - (uint32_t)GPIOA) >> 10U) & 0xFU;
        uint32_t cr    = pad >> 2U;
        uint32_t shift = (pad & 3U) * 4U;

        /* Input with pull-up: the key shorts the row to a driven-low column. */
        palSetLineMode(line, PAL_MODE_INPUT_PULLUP);

        /* Route the line to its port, 4 bits per line in SYSCFG EXTICR. */
        SYSCFG->EXTICR[cr] = (SYSCFG->EXTICR[cr] & ~(0xFU << shift)) | (port << shift);
    }

    /* Columns driven LOW (all "selected") so a press on any key pulls a row. */
    for (unsigned i = 0U; i < KB17_WAKE_COL_COUNT; i++) {
        palSetLineMode(kb17_wake_cols[i], PAL_MODE_OUTPUT_PUSHPULL);
        palClearLine(kb17_wake_cols[i]);
    }

    /* Sample the rows now that the columns are driving: a key that is already
       held down - pressed while the core was awake, or held over from the
       previous pass - shows up here instead of as an EXTI edge. */
    uint32_t pressed = kb17_stop_wake_pins_pressed();

    /* Both edges on the rows: pressing a key pulls the row low, releasing it
       lets the pull-up take it high, and either one is key activity that must
       pull the core out of STOP.  The event mask is set next to the interrupt
       mask, exactly like USBUSER_Init() arms the USB resume line: the wakeup
       out of STOP is fed by the EXTI request, and none of these lines has an
       NVIC vector of its own on this family. */
    EXTI->RTSR |= row_mask;
    EXTI->FTSR |= row_mask;
    EXTI->EMR  |= row_mask;
    EXTI->IMR  |= row_mask;

    /* Drop anything latched before the arming (a key already held down would
       otherwise end the first WFE immediately with a stale edge). */
    EXTI->PR = row_mask;

    return pressed;
}

/* Releases the wake configuration once the core is awake again: outside the
 * suspend path QMK owns the pins as plain matrix inputs/outputs. */
static void kb17_stop_wake_pins_release(void) {
    uint32_t row_mask = kb17_wake_row_mask();

    EXTI->IMR  &= ~row_mask;
    EXTI->EMR  &= ~row_mask;
    EXTI->FTSR &= ~row_mask;
    EXTI->RTSR &= ~row_mask;
    EXTI->PR    = row_mask;

    /* Restore the columns to the QMK matrix unselected state (input with
       pull-up, which is what unselect_col() puts them in without
       MATRIX_UNSELECT_DRIVE_HIGH) so the next matrix scan starts clean. */
    for (unsigned i = 0U; i < KB17_WAKE_COL_COUNT; i++) {
        palSetLineMode(kb17_wake_cols[i], PAL_MODE_INPUT_PULLUP);
    }
}

void suspend_power_down_kb(void) {
    uint32_t edges = 0U;

    /* Arm the keys as wake sources and read them back in the same pass: the
       columns are driven low exactly like a matrix scan drives them, so this
       sample holds the same keys QMK's suspend_wakeup_condition() would find
       one step later.
       This level sample - not the EXTI edge - is the primary wake evidence.
       The suspend loop is awake for most of every cycle (wait_ms(17) plus the
       matrix scan below), so a key that goes down while the core is awake
       produces no edge to wait for, and the EXTI->PR clear in the arming throws
       its latch away; only the level survives that window.  Waiting for an edge
       alone is why a press did nothing until it was released: a release landing
       in a sleep window still produced a (rising) edge, so the machine only
       answered the release. */
    uint32_t pressed = kb17_stop_wake_pins_arm();

    /* Sleep only when nothing is pending.  While a key is down, and while the
       host is answering a resume burst we just sent, the core must stay awake:
       STOP gates off the USB clock, and the host's own resume followed by SOF
       would be missed in the middle of it. */
    if ((pressed == 0U) && (kb17_wake_settle == 0U)) {
        sk32_lowpower_stop_enter();
        /* Rows that latched a press while the core slept: a tap that opened
           and closed inside one sleep window leaves no level behind, only this
           edge.  Read before the release below clears EXTI->PR. */
        edges = EXTI->PR & kb17_wake_row_mask();
        sk32_lowpower_stop_restore();
        /* The key may still be down: resample after the wake. */
        pressed = kb17_stop_wake_pins_pressed();
    }

    kb17_stop_wake_pins_release();

    /* Remote wakeup (device -> host).
     * Mirrors the vendor usbd_set_remote_wakeup() (SK32F0xx_Firmware Package
     * 25_10_24, RGBKeyboardSTK (Mechanical)): the device drives USB resume
     * unconditionally (POWER.RESUME held ~10 ms then released).
     *
     * QMK's own call site in protocol_pre_task() gates this on
     * (USB_DRIVER.status & USB_GETSTATUS_REMOTE_WAKEUP_ENABLED) - i.e. on the
     * host having sent SET_FEATURE(DEVICE_REMOTE_WAKEUP).  This host never
     * sends it (USBD1.status stays 0, verified over SWD on the LD7), so that
     * path would never signal the bus and a key press could not wake the PC.
     * Calling usbWakeupHost() here bypasses that QMK/SET_FEATURE gate, but
     * usbWakeupHost() is itself gated on (state == USB_SUSPENDED); the STOP
     * exit and the clock rebuild that follows it leave the driver in another
     * state, so the request is silently dropped, no resume is driven on the
     * bus and only the keyboard wakes.  Drive the LLD resume primitive
     * directly instead - exactly the vendor's unconditional
     * usbd_set_remote_wakeup() - so the bus is always pulsed on key activity,
     * whatever the driver state is.  It only runs while we are inside this
     * suspend loop (the bus is suspended), so a resume is not generated on an
     * active bus. */
    if (pressed != 0U) {
        /* Key down: report this press to the host exactly once.
           kb17_press_reported stays set on the following passes, so a key held
           down does not drive USB resume again every iteration.  A resume burst
           repeated like that holds the bus in the resume state permanently, so
           the answer the host sends back can never be observed and the remote
           wakeup is discarded. */
        if (!kb17_press_reported) {
            kb17_press_reported = true;
            kb17_wake_settle    = KB17_WAKE_SETTLE_PASSES;
            usb_lld_wakeup_host(&USBD1);
        }
    } else {
        /* Key(s) up.  A release must not drive resume - that would clobber the
           answer to the press already announced - but a tap that opened and
           closed inside one sleep window leaves no level behind, so report it
           from its latched edge (kb17_press_reported is clear on this path, no
           press has been announced for it). */
        if (edges != 0U) {
            kb17_wake_settle = KB17_WAKE_SETTLE_PASSES;
            usb_lld_wakeup_host(&USBD1);
        }
        kb17_press_reported = false;
    }

    if (kb17_wake_settle != 0U) {
        kb17_wake_settle--;
    }

    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    /* A new suspend session starts with no press announced and nothing to
       settle. */
    kb17_press_reported = false;
    kb17_wake_settle    = 0U;

    /* STOP dropped the PLL/HSI clock config; restore it before any further
       USB/report processing.  Handled here (after the loop has determined a
       real wakeup) so an unrelated interrupt that merely wakes STOP does not
       force a full clock rebuild. */
    sk32_lowpower_stop_restore();
    suspend_wakeup_init_user();
}
#endif /* SK32_HAL_USE_LOWPOWER */


#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = {
	{
		{0, 1, 2, 3},
		{4, 5, 6, NO_LED},
		{7, 8, 9, 10},
		{11, 12, 13, NO_LED},
		{14, NO_LED, 15, 16},
	}, {
		{28, 3}, {84, 3}, {140, 3}, {196, 3},
		{28, 16}, {84, 16}, {140, 16},
		{28, 29}, {84, 29}, {140, 29}, {196, 19},
		{28, 41}, {84, 41}, {140, 41},
		{56, 54}, {140, 54}, {196, 45},
	}, {
		4, 4, 4, 4,
		4, 4, 4,
		4, 4, 4, 4,
		4, 4, 4,
		4, 4, 4,
	}
};

#endif
