/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <sys/stat.h>

#include "pico.h"
#if LIB_PICO_PRINTF_PICO
#include "pico/printf.h"
#endif
#include "pico/stdio.h"
#include "pico/stdio/driver.h"
#include "pico/time.h"
#if PICO_STDOUT_MUTEX
#include "pico/mutex.h"
#endif

#if LIB_PICO_STDIO_UART
#include "pico/stdio_uart.h"
#endif

#if LIB_PICO_STDIO_USB
#include "pico/stdio_usb.h"
#endif

#if LIB_PICO_STDIO_SEMIHOSTING
#include "pico/stdio_semihosting.h"
#endif

#define STDIO_HANDLE_STDIN  0
#define STDIO_HANDLE_STDOUT 1
#define STDIO_HANDLE_STDERR 2

static stdio_driver_t *drivers;
static stdio_driver_t *filter;

#if PICO_STDOUT_MUTEX
auto_init_mutex(print_mutex);

bool stdout_serialize_begin(void) {
    return mutex_try_enter_block_until(&print_mutex, make_timeout_time_ms(PICO_STDIO_DEADLOCK_TIMEOUT_MS));
}

void stdout_serialize_end(void) {
    mutex_exit(&print_mutex);
}

#else
static bool stdout_serialize_begin(void) {
    return true;
}
static void stdout_serialize_end(void) {
}
#endif
static void stdio_out_chars_no_crlf(stdio_driver_t *driver, const char *s, int len) {
    driver->out_chars(s, len);
}

static void stdio_out_chars_crlf(stdio_driver_t *driver, const char *s, int len) {
#if PICO_STDIO_ENABLE_CRLF_SUPPORT
    if (!driver->crlf_enabled) {
        driver->out_chars(s, len);
        return;
    }
    int first_of_chunk = 0;
    static const char crlf_str[] = {'\r', '\n'};
    for (int i = 0; i < len; i++) {
        bool prev_char_was_cr = i > 0 ? s[i - 1] == '\r' : driver->last_ended_with_cr;
        if (s[i] == '\n' && !prev_char_was_cr) {
            if (i > first_of_chunk) {
                driver->out_chars(&s[first_of_chunk], i - first_of_chunk);
            }
            driver->out_chars(crlf_str, 2);
            first_of_chunk = i + 1;
        }
    }
    if (first_of_chunk < len) {
        driver->out_chars(&s[first_of_chunk], len - first_of_chunk);
    }
    if (len > 0) {
        driver->last_ended_with_cr = s[len - 1] == '\r';
    }
#else
    driver->out_chars(s, len);
#endif
}

static bool stdio_put_string(const char *s, int len, bool newline, bool no_cr) {
    bool serialized = stdout_serialize_begin();
    if (!serialized) {
#if PICO_STDIO_IGNORE_NESTED_STDOUT
        return false;
#endif
    }
    if (len == -1) len = (int)strlen(s);
    void (*out_func)(stdio_driver_t *, const char *, int) = no_cr ? stdio_out_chars_no_crlf : stdio_out_chars_crlf;
    for (stdio_driver_t *driver = drivers; driver; driver = driver->next) {
        if (!driver->out_chars) continue;
        if (filter && filter != driver) continue;
        out_func(driver, s, len);
        if (newline) {
            const char c = '\n';
            out_func(driver, &c, 1);
        }
    }
    if (serialized) {
        stdout_serialize_end();
    }
    return len;
}

static int stdio_get_until(char *buf, int len, absolute_time_t until) {
    do {
        // todo round robin might be nice on each call, but then again hopefully
        //  no source will starve the others
        for (stdio_driver_t *driver = drivers; driver; driver = driver->next) {
            if (filter && filter != driver) continue;
            if (driver->in_chars) {
                int read = driver->in_chars(buf, len);
                if (read > 0) {
                    return read;
                }
            }
        }
        if (time_reached(until)) {
            return PICO_ERROR_TIMEOUT;
        }
        // we sleep here in case the in_chars methods acquire mutexes or disable IRQs and
        // potentially starve out what they are waiting on (have seen this with USB)
        busy_wait_us(1);
    } while (true);
}

int WRAPPER_FUNC(putchar)(int c) {
    char cc = (char)c;
    stdio_put_string(&cc, 1, false, false);
    return c;
}

int WRAPPER_FUNC(puts)(const char *s) {
    int len = (int)strlen(s);
    stdio_put_string(s, len, true, false);
    stdio_flush();
    return len;
}

int putchar_raw(int c) {
    char cc = (char)c;
    stdio_put_string(&cc, 1, false, true);
    return c;
}

int puts_raw(const char *s) {
    int len = (int)strlen(s);
    stdio_put_string(s, len, true, true);
    stdio_flush();
    return len;
}

int __attribute__((weak)) _read(int handle, char *buffer, int length) {
    if (handle == STDIO_HANDLE_STDIN) {
        return stdio_get_until(buffer, length, at_the_end_of_time);
    }
    return -1;
}

int __attribute__((weak)) _write(int handle, char *buffer, int length) {
    if (handle == STDIO_HANDLE_STDOUT || handle == STDIO_HANDLE_STDERR) {
        stdio_put_string(buffer, length, false, false);
        return length;
    }
    return -1;
}

int __attribute__((weak)) _open(__unused const char *fn, __unused int oflag, ...) {
    return -1;
}

int __attribute__((weak)) _close(__unused int fd) {
    return -1;
}

off_t __attribute__((weak)) _lseek(__unused int fd, __unused off_t pos, __unused int whence) {
    return -1;
}

int __attribute__((weak)) _fstat(__unused int fd, __unused struct stat *buf) {
    return -1;
}

int __attribute__((weak)) _isatty(int fd) {
    return fd == STDIO_HANDLE_STDIN || fd == STDIO_HANDLE_STDOUT || fd == STDIO_HANDLE_STDERR;
}

void stdio_set_driver_enabled(stdio_driver_t *driver, bool enable) {
    stdio_driver_t **prev = &drivers;
    while (*prev) {
        if (*prev == driver) {
            if (!enable) {
                *prev = driver->next;
                driver->next = NULL;
            }
            return;
        }
        prev = &(*prev)->next;
    }
    if (enable) {
        *prev = driver;
    }
}

void stdio_flush() {
    for (stdio_driver_t *d = drivers; d; d = d->next) {
        if (d->out_flush) d->out_flush();
    }
}

typedef struct stdio_stack_buffer {
    int used;
    char buf[PICO_STDIO_STACK_BUFFER_SIZE];
} stdio_stack_buffer_t;

static void stdio_stack_buffer_flush(stdio_stack_buffer_t *buffer) {
    if (buffer->used) {
        for (stdio_driver_t *d = drivers; d; d = d->next) {
            if (!d->out_chars) continue;
            if (filter && filter != d) continue;
            stdio_out_chars_crlf(d, buffer->buf, buffer->used);
        }
        buffer->used = 0;
    }
}

static void stdio_buffered_printer(char c, void *arg) {
    stdio_stack_buffer_t *buffer = (stdio_stack_buffer_t *)arg;
    if (buffer->used == PICO_STDIO_STACK_BUFFER_SIZE) {
        stdio_stack_buffer_flush(buffer);
    }
    buffer->buf[buffer->used++] = c;
}

int WRAPPER_FUNC(vprintf)(const char *format, va_list va) {
    bool serialzed = stdout_serialize_begin();
    if (!serialzed) {
#if PICO_STDIO_IGNORE_NESTED_STDOUT
        return 0;
#endif
    }
    int ret;
#if LIB_PICO_PRINTF_PICO
    struct stdio_stack_buffer buffer;
    buffer.used = 0;
    ret = vfctprintf(stdio_buffered_printer, &buffer, format, va);
    stdio_stack_buffer_flush(&buffer);
    stdio_flush();
#elif LIB_PICO_PRINTF_NONE
    extern void printf_none_assert();
    printf_none_assert();
#else
    extern int REAL_FUNC(vprintf)(const char *format, va_list va);
    ret = REAL_FUNC(vprintf)(format, va);
#endif
    if (serialzed) {
        stdout_serialize_end();
    }
    return ret;
}

int __printflike(1, 0) WRAPPER_FUNC(printf)(const char* format, ...)
{
    va_list va;
    va_start(va, format);
    int ret = vprintf(format, va);
    va_end(va);
    return ret;
}

bool stdio_init_all(void) {
    // todo add explicit custom, or registered although you can call stdio_enable_driver explicitly anyway
    // These are well known ones

    bool rc = false;
#if LIB_PICO_STDIO_UART
    stdio_uart_init();
    rc = true;
#endif

#if LIB_PICO_STDIO_SEMIHOSTING
    stdio_semihosting_init();
    rc = true;
#endif

#if LIB_PICO_STDIO_USB
    rc |= stdio_usb_init();
#endif
    return rc;
}

int WRAPPER_FUNC(getchar)(void) {
    char buf[1];
    int len = stdio_get_until(buf, 1, at_the_end_of_time);
    if (len < 0) return len;
    assert(len == 1);
    return (uint8_t)buf[0];
}

int getchar_timeout_us(uint32_t timeout_us) {
    char buf[1];
    int rc = stdio_get_until(buf, sizeof(buf), make_timeout_time_us(timeout_us));
    if (rc < 0) return rc;
    assert(rc);
    return (uint8_t)buf[0];
}

void stdio_filter_driver(stdio_driver_t *driver) {
    filter = driver;
}

void stdio_set_translate_crlf(stdio_driver_t *driver, bool enabled) {
#if PICO_STDIO_ENABLE_CRLF_SUPPORT
    if (enabled && !driver->crlf_enabled) {
        driver->last_ended_with_cr = false;
    }
    driver->crlf_enabled = enabled;
#else
    // Suppress -Wunused-parameter
    (void)driver;
    (void)enabled;
    
    panic_unsupported();
#endif
}

void stdio_set_chars_available_callback(void (*fn)(void*), void *param) {
    for (stdio_driver_t *s = drivers; s; s = s->next) {
        if (s->set_chars_available_callback) s->set_chars_available_callback(fn, param);
    }
}
