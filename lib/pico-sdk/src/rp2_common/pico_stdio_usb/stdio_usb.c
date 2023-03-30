/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef LIB_TINYUSB_HOST
#include "tusb.h"
#include "pico/stdio_usb.h"

// these may not be set if the user is providing tud support (i.e. LIB_TINYUSB_DEVICE is 1 because
// the user linked in tinyusb_device) but they haven't selected CDC
#if (CFG_TUD_ENABLED | TUSB_OPT_DEVICE_ENABLED) && CFG_TUD_CDC

#include "pico/binary_info.h"
#include "pico/time.h"
#include "pico/stdio/driver.h"
#include "pico/mutex.h"
#include "hardware/irq.h"
#include "device/usbd_pvt.h" // for usbd_defer_func

static mutex_t stdio_usb_mutex;
#ifndef NDEBUG
static uint8_t stdio_usb_core_num;
#endif

#if PICO_STDIO_USB_SUPPORT_CHARS_AVAILABLE_CALLBACK
static void (*chars_available_callback)(void*);
static void *chars_available_param;
#endif

// when tinyusb_device is explicitly linked we do no background tud processing
#if !LIB_TINYUSB_DEVICE
// if this crit_sec is initialized, we are not in periodic timer mode, and must make sure
// we don't either create multiple one shot timers, or miss creating one. this crit_sec
// is used to protect the one_shot_timer_pending flag
static critical_section_t one_shot_timer_crit_sec;
static volatile bool one_shot_timer_pending;
#ifdef PICO_STDIO_USB_LOW_PRIORITY_IRQ
static_assert(PICO_STDIO_USB_LOW_PRIORITY_IRQ >= NUM_IRQS - NUM_USER_IRQS, "");
#define low_priority_irq_num PICO_STDIO_USB_LOW_PRIORITY_IRQ
#else
static uint8_t low_priority_irq_num;
#endif

static int64_t timer_task(__unused alarm_id_t id, __unused void *user_data) {
    int64_t repeat_time;
    if (critical_section_is_initialized(&one_shot_timer_crit_sec)) {
        critical_section_enter_blocking(&one_shot_timer_crit_sec);
        one_shot_timer_pending = false;
        critical_section_exit(&one_shot_timer_crit_sec);
        repeat_time = 0; // don't repeat
    } else {
        repeat_time = PICO_STDIO_USB_TASK_INTERVAL_US;
    }
    irq_set_pending(low_priority_irq_num);
    return repeat_time;
}

static void low_priority_worker_irq(void) {
    if (mutex_try_enter(&stdio_usb_mutex, NULL)) {
        tud_task();
        mutex_exit(&stdio_usb_mutex);
    } else {
        // if the mutex is already owned, then we are in non IRQ code in this file.
        //
        // it would seem simplest to just let that code call tud_task() at the end, however this
        // code might run during the call to tud_task() and we might miss a necessary tud_task() call
        //
        // if we are using a periodic timer (crit_sec is not initialized in this case),
        // then we are happy just to wait until the next tick, however when we are not using a periodic timer,
        // we must kick off a one-shot timer to make sure the tud_task() DOES run (this method
        // will be called again as a result, and will try the mutex_try_enter again, and if that fails
        // create another one shot timer again, and so on).
        if (critical_section_is_initialized(&one_shot_timer_crit_sec)) {
            bool need_timer;
            critical_section_enter_blocking(&one_shot_timer_crit_sec);
            need_timer = !one_shot_timer_pending;
            one_shot_timer_pending = true;
            critical_section_exit(&one_shot_timer_crit_sec);
            if (need_timer) {
                add_alarm_in_us(PICO_STDIO_USB_TASK_INTERVAL_US, timer_task, NULL, true);
            }
        }
    }
}

static void usb_irq(void) {
    irq_set_pending(low_priority_irq_num);
}

#endif

static void stdio_usb_out_chars(const char *buf, int length) {
    static uint64_t last_avail_time;
    if (!mutex_try_enter_block_until(&stdio_usb_mutex, make_timeout_time_ms(PICO_STDIO_DEADLOCK_TIMEOUT_MS))) {
        return;
    }
    if (stdio_usb_connected()) {
        for (int i = 0; i < length;) {
            int n = length - i;
            int avail = (int) tud_cdc_write_available();
            if (n > avail) n = avail;
            if (n) {
                int n2 = (int) tud_cdc_write(buf + i, (uint32_t)n);
                tud_task();
                tud_cdc_write_flush();
                i += n2;
                last_avail_time = time_us_64();
            } else {
                tud_task();
                tud_cdc_write_flush();
                if (!stdio_usb_connected() ||
                    (!tud_cdc_write_available() && time_us_64() > last_avail_time + PICO_STDIO_USB_STDOUT_TIMEOUT_US)) {
                    break;
                }
            }
        }
    } else {
        // reset our timeout
        last_avail_time = 0;
    }
    mutex_exit(&stdio_usb_mutex);
}

int stdio_usb_in_chars(char *buf, int length) {
    // note we perform this check outside the lock, to try and prevent possible deadlock conditions
    // with printf in IRQs (which we will escape through timeouts elsewhere, but that would be less graceful).
    //
    // these are just checks of state, so we can call them while not holding the lock.
    // they may be wrong, but only if we are in the middle of a tud_task call, in which case at worst
    // we will mistakenly think we have data available when we do not (we will check again), or
    // tud_task will complete running and we will check the right values the next time.
    //
    int rc = PICO_ERROR_NO_DATA;
    if (stdio_usb_connected() && tud_cdc_available()) {
        if (!mutex_try_enter_block_until(&stdio_usb_mutex, make_timeout_time_ms(PICO_STDIO_DEADLOCK_TIMEOUT_MS))) {
            return PICO_ERROR_NO_DATA; // would deadlock otherwise
        }
        if (stdio_usb_connected() && tud_cdc_available()) {
            int count = (int) tud_cdc_read(buf, (uint32_t) length);
            rc = count ? count : PICO_ERROR_NO_DATA;
        } else {
            // because our mutex use may starve out the background task, run tud_task here (we own the mutex)
            tud_task();
        }
        mutex_exit(&stdio_usb_mutex);
    }
    return rc;
}

#if PICO_STDIO_USB_SUPPORT_CHARS_AVAILABLE_CALLBACK
void tud_cdc_rx_cb(__unused uint8_t itf) {
    if (chars_available_callback) {
        usbd_defer_func(chars_available_callback, chars_available_param, false);
    }
}

void stdio_usb_set_chars_available_callback(void (*fn)(void*), void *param) {
    chars_available_callback = fn;
    chars_available_param = param;
}
#endif

stdio_driver_t stdio_usb = {
    .out_chars = stdio_usb_out_chars,
    .in_chars = stdio_usb_in_chars,
#if PICO_STDIO_USB_SUPPORT_CHARS_AVAILABLE_CALLBACK
    .set_chars_available_callback = stdio_usb_set_chars_available_callback,
#endif
#if PICO_STDIO_ENABLE_CRLF_SUPPORT
    .crlf_enabled = PICO_STDIO_USB_DEFAULT_CRLF
#endif

};

bool stdio_usb_init(void) {
    if (get_core_num() != alarm_pool_core_num(alarm_pool_get_default())) {
        // included an assertion here rather than just returning false, as this is likely
        // a coding bug, rather than anything else.
        assert(false);
        return false;
    }
#ifndef NDEBUG
    stdio_usb_core_num = (uint8_t)get_core_num();
#endif
#if !PICO_NO_BI_STDIO_USB
    bi_decl_if_func_used(bi_program_feature("USB stdin / stdout"));
#endif

#if !defined(LIB_TINYUSB_DEVICE)
    // initialize TinyUSB, as user hasn't explicitly linked it
    tusb_init();
#else
    assert(tud_inited()); // we expect the caller to have initialized if they are using TinyUSB
#endif

    mutex_init(&stdio_usb_mutex);
    bool rc = true;
#if !LIB_TINYUSB_DEVICE
#ifdef PICO_STDIO_USB_LOW_PRIORITY_IRQ
    user_irq_claim(PICO_STDIO_USB_LOW_PRIORITY_IRQ);
#else
    low_priority_irq_num = (uint8_t) user_irq_claim_unused(true);
#endif
    irq_set_exclusive_handler(low_priority_irq_num, low_priority_worker_irq);
    irq_set_enabled(low_priority_irq_num, true);

    if (irq_has_shared_handler(USBCTRL_IRQ)) {
        // we can use a shared handler to notice when there may be work to do
        irq_add_shared_handler(USBCTRL_IRQ, usb_irq, PICO_SHARED_IRQ_HANDLER_LOWEST_ORDER_PRIORITY);
        critical_section_init_with_lock_num(&one_shot_timer_crit_sec, next_striped_spin_lock_num());
    } else {
        rc = add_alarm_in_us(PICO_STDIO_USB_TASK_INTERVAL_US, timer_task, NULL, true) >= 0;
        // we use initialization state of the one_shot_timer_critsec as a flag
        memset(&one_shot_timer_crit_sec, 0, sizeof(one_shot_timer_crit_sec));
    }
#endif
    if (rc) {
        stdio_set_driver_enabled(&stdio_usb, true);
#if PICO_STDIO_USB_CONNECT_WAIT_TIMEOUT_MS
#if PICO_STDIO_USB_CONNECT_WAIT_TIMEOUT_MS > 0
        absolute_time_t until = make_timeout_time_ms(PICO_STDIO_USB_CONNECT_WAIT_TIMEOUT_MS);
#else
        absolute_time_t until = at_the_end_of_time;
#endif
        do {
            if (stdio_usb_connected()) {
#if PICO_STDIO_USB_POST_CONNECT_WAIT_DELAY_MS != 0
                sleep_ms(PICO_STDIO_USB_POST_CONNECT_WAIT_DELAY_MS);
#endif
                break;
            }
            sleep_ms(10);
        } while (!time_reached(until));
#endif
    }
    return rc;
}

bool stdio_usb_connected(void) {
#if PICO_STDIO_USB_CONNECTION_WITHOUT_DTR
    return tud_ready();
#else
    // this actually checks DTR
    return tud_cdc_connected();
#endif
}

#else
#warning stdio USB was configured along with user use of TinyUSB device mode, but CDC is not enabled
bool stdio_usb_init(void) {
    return false;
}
#endif // CFG_TUD_ENABLED && CFG_TUD_CDC
#else
#warning stdio USB was configured, but is being disabled as TinyUSB host is explicitly linked
bool stdio_usb_init(void) {
    return false;
}
#endif // !LIB_TINYUSB_HOST

