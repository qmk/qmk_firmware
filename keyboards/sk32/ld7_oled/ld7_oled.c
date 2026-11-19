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

#include "ld7_oled.h"

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

/* KEY1..KEY7 of the LD7, same order as keyboard.json "matrix_pins.direct".
 * These are the lines turned into STOP wake sources while the core sleeps. */
static const ioline_t ld7_wake_lines[] = {
    PAL_LINE(GPIOB, 12), /* KEY1 */
    PAL_LINE(GPIOB, 11), /* KEY2 */
    PAL_LINE(GPIOB, 10), /* KEY3 */
    PAL_LINE(GPIOB, 2),  /* KEY4 */
    PAL_LINE(GPIOB, 1),  /* KEY5 */
    PAL_LINE(GPIOB, 0),  /* KEY6 */
    PAL_LINE(GPIOC, 5),  /* KEY7 */
};

#define LD7_WAKE_LINE_COUNT (sizeof(ld7_wake_lines) / sizeof(ld7_wake_lines[0]))

static uint32_t ld7_wake_pin_mask(void) {
    uint32_t mask = 0U;

    for (unsigned i = 0U; i < LD7_WAKE_LINE_COUNT; i++) {
        mask |= 1U << (uint32_t)PAL_PAD(ld7_wake_lines[i]);
    }

    return mask;
}

/* Arms every key line as a STOP wake source.
 * Reference: SK32F0xx_Firmware Package 26_07_21, RGBKeyboardSTK
 * (Mechanical_SRGB), User/Src/kbcuDrive.c -> KBCUDVE_SleepInit(): before
 * PWR_EnterSTOPMode() the vendor switches each key to input with pull-up and
 * arms its EXTI line on the falling edge (SYSCFG_EXTILineConfig +
 * EXTI_Init(EXTI_Trigger_Falling)) so that the first key press pulls the core
 * out of deep sleep.  Without it a key cannot wake the chip at all: the only
 * other wake sources are the periodic TIM6 tick and the USB resume line. */
static void ld7_stop_wake_pins_arm(void) {
    uint32_t mask = ld7_wake_pin_mask();

    /* The EXTI line -> port mapping lives in SYSCFG, which needs its APB2
       clock (the vendor calls RCC_APB2PeriphClockCmd(..SYSCFG, ENABLE) in
       KBCUDVE_SleepInit() for the same reason). */
    rccEnableAPB2(RCC_APB2ENR_SYSCFGEN, true);

    for (unsigned i = 0U; i < LD7_WAKE_LINE_COUNT; i++) {
        ioline_t line  = ld7_wake_lines[i];
        uint32_t pad   = (uint32_t)PAL_PAD(line);
        uint32_t port  = (((uint32_t)PAL_PORT(line) - (uint32_t)GPIOA) >> 10U) & 0xFU;
        uint32_t cr    = pad >> 2U;
        uint32_t shift = (pad & 3U) * 4U;

        /* Input with pull-up: the key shorts the line to ground. */
        palSetLineMode(line, PAL_MODE_INPUT_PULLUP);

        /* Route the line to its port, 4 bits per line in SYSCFG EXTICR. */
        SYSCFG->EXTICR[cr] = (SYSCFG->EXTICR[cr] & ~(0xFU << shift)) | (port << shift);
    }

    /* Falling edge: pressing a key pulls the line low.  The event mask is set
       next to the interrupt mask, exactly like USBUSER_Init() arms the USB
       resume line (EXTI->IMR|=EXTI_IMR_MR18; EXTI->EMR|=..): the wakeup out of
       STOP is fed by the EXTI request, and none of these lines has an NVIC
       vector of its own on this family. */
    EXTI->RTSR &= ~mask;
    EXTI->FTSR |= mask;
    EXTI->EMR  |= mask;
    EXTI->IMR  |= mask;

    /* Drop anything latched before the arming (a key already held down would
       otherwise end the first WFE immediately with a stale edge). */
    EXTI->PR = mask;
}

/* Releases the key lines once the core is awake again: outside the suspend
 * path QMK owns them as plain matrix inputs. */
static void ld7_stop_wake_pins_release(void) {
    uint32_t mask = ld7_wake_pin_mask();

    EXTI->IMR  &= ~mask;
    EXTI->EMR  &= ~mask;
    EXTI->FTSR &= ~mask;
    EXTI->RTSR &= ~mask;
    EXTI->PR    = mask;
}

void suspend_power_down_kb(void) {
    /* Arm the keys as wake sources, sleep, then release them so the matrix
       scan in suspend_wakeup_condition() reads the pins as plain inputs. */
    ld7_stop_wake_pins_arm();
    sk32_lowpower_stop_enter();

    /* Which key lines latched a falling edge while the core slept: the same
       hardware evidence the vendor uses to leave STOP.  Read before the
       release below clears EXTI->PR. */
    uint32_t wake_lines = EXTI->PR & ld7_wake_pin_mask();

    sk32_lowpower_stop_restore();
    ld7_stop_wake_pins_release();

    /* Remote wakeup (device -> host).
     * Mirrors the vendor usbd_set_remote_wakeup() (SK32F0xx_Firmware Package
     * 25_10_24, RGBKeyboardSTK (Mechanical)): on a key edge the device drives
     * USB resume unconditionally.
     *
     * QMK's own call site in protocol_pre_task() gates this on
     * (USB_DRIVER.status & USB_GETSTATUS_REMOTE_WAKEUP_ENABLED), i.e. on the
     * host having sent SET_FEATURE(DEVICE_REMOTE_WAKEUP).  This host never
     * sends it (USBD1.status stays 0, verified over SWD), so that path would
     * never signal the bus and a key press could not wake the PC.  Calling
     * usbWakeupHost() here bypasses that gate; it still only acts while
     * state == USB_SUSPENDED, so the bus is only driven when it is really
     * suspended. */
    if (wake_lines != 0U) {
        usbWakeupHost(&USBD1);
    }

    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    /* STOP dropped the PLL/HSI clock config; restore it before any further
       USB/report processing.  Handled here (after the loop has determined a
       real wakeup) so an unrelated interrupt that merely wakes STOP does not
       force a full clock rebuild. */
    sk32_lowpower_stop_restore();
    suspend_wakeup_init_user();
}
#endif /* SK32_HAL_USE_LOWPOWER */

#ifdef OLED_ENABLE

#include "ch.h"
#include "oled_driver.h"

/* The whole OLED draw + blocking SSD1306 I2C render belongs to a dedicated
 * thread, not to the QMK main loop (see OLED_TASK_EXTERNAL_LOOP in config.h).
 * Main loop and thread never race on oled_buffer: the main loop's oled_task()
 * returns immediately (buffer untouched) and this thread is the only accessor,
 * serializing oled_set_cursor + oled_task_kb (redraw) then oled_render_dirty
 * (send over I2C).  Without this a drawn block could be sent half-old / half-new
 * while it is in flight on the bus, leaving a permanently "stacked" digit.
 *
 * Priority NORMALPRIO+1: it must be strictly above NORMALPRIO, otherwise, with
 * CH_CFG_TIME_QUANTUM = 0, the busy main loop never yields to it (starved).
 * It is kept only +1 (rather than the onekey bring-up +8) so that each render
 * wake preempts the main loop for at most the time to send a few blocks.
 */
static THD_WORKING_AREA(waOledRenderThread, 512);
static THD_FUNCTION(oled_render_thread, arg) {
    (void)arg;
    chRegSetThreadName("oled-render");
    while (true) {
        chThdSleepMilliseconds(OLED_UPDATE_INTERVAL);
        /* Single-owner draw+send: keeps the block consistent, no tearing. */
        oled_set_cursor(0, 0);
        oled_task_kb();
        oled_render_dirty(true);
    }
}

void keyboard_post_init_user(void) {
    /* oled_init() has already run, so oled_initialized is true here. */
    chThdCreateStatic(waOledRenderThread, sizeof(waOledRenderThread),
                      (tprio_t)(NORMALPRIO + 1U), oled_render_thread, NULL);
}

#endif /* OLED_ENABLE */

#ifdef RGB_MATRIX_ENABLE

/* The 7 LEDs sit in a single row above KEY1..KEY7.  matrix_co maps every
 * directly wired key (matrix [0][0..6]) to its LED index 0..6. */
led_config_t g_led_config = {
	{
		{0, 1, 2, 3, 4, 5, 6}
	}, {
		{0, 32}, {37, 32}, {74, 32}, {111, 32}, {148, 32}, {185, 32}, {224, 32}
	}, {
		4, 4, 4, 4, 4, 4, 4
	}
};

#endif
