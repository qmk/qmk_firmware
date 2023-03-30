/*
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "pico/unique_id.h"
#include "cyw43.h"
#include "pico/cyw43_arch.h"
#include "cyw43_ll.h"
#include "cyw43_stats.h"

#if PICO_CYW43_ARCH_DEBUG_ENABLED
#define CYW43_ARCH_DEBUG(...) printf(__VA_ARGS__)
#else
#define CYW43_ARCH_DEBUG(...) ((void)0)
#endif

static uint32_t country_code = PICO_CYW43_ARCH_DEFAULT_COUNTRY_CODE;

static async_context_t *async_context;

void cyw43_arch_set_async_context(async_context_t *context) {
    async_context = context;
}

void cyw43_arch_enable_sta_mode() {
    assert(cyw43_is_initialized(&cyw43_state));
    cyw43_wifi_set_up(&cyw43_state, CYW43_ITF_STA, true, cyw43_arch_get_country_code());
}

void cyw43_arch_enable_ap_mode(const char *ssid, const char *password, uint32_t auth) {
    assert(cyw43_is_initialized(&cyw43_state));
    cyw43_wifi_ap_set_ssid(&cyw43_state, strlen(ssid), (const uint8_t *) ssid);
    if (password) {
        cyw43_wifi_ap_set_password(&cyw43_state, strlen(password), (const uint8_t *) password);
        cyw43_wifi_ap_set_auth(&cyw43_state, auth);
    } else {
        cyw43_wifi_ap_set_auth(&cyw43_state, CYW43_AUTH_OPEN);
    }
    cyw43_wifi_set_up(&cyw43_state, CYW43_ITF_AP, true, cyw43_arch_get_country_code());
}

#if PICO_CYW43_ARCH_DEBUG_ENABLED
// Return a string for the wireless state
static const char* cyw43_tcpip_link_status_name(int status)
{
    switch (status) {
    case CYW43_LINK_DOWN:
        return "link down";
    case CYW43_LINK_JOIN:
        return "joining";
    case CYW43_LINK_NOIP:
        return "no ip";
    case CYW43_LINK_UP:
        return "link up";
    case CYW43_LINK_FAIL:
        return "link fail";
    case CYW43_LINK_NONET:
        return "network fail";
    case CYW43_LINK_BADAUTH:
        return "bad auth";
    }
    return "unknown";
}
#endif


int cyw43_arch_wifi_connect_bssid_async(const char *ssid, const uint8_t *bssid, const char *pw, uint32_t auth) {
    if (!pw) auth = CYW43_AUTH_OPEN;
    // Connect to wireless
    return cyw43_wifi_join(&cyw43_state, strlen(ssid), (const uint8_t *)ssid, pw ? strlen(pw) : 0, (const uint8_t *)pw, auth, bssid, CYW43_CHANNEL_NONE);
}

int cyw43_arch_wifi_connect_async(const char *ssid, const char *pw, uint32_t auth) {
    return cyw43_arch_wifi_connect_bssid_async(ssid, NULL, pw, auth);
}

static int cyw43_arch_wifi_connect_bssid_until(const char *ssid, const uint8_t *bssid, const char *pw, uint32_t auth, absolute_time_t until) {
    int err = cyw43_arch_wifi_connect_bssid_async(ssid, bssid, pw, auth);
    if (err) return err;

    int status = CYW43_LINK_UP + 1;
    while(status >= 0 && status != CYW43_LINK_UP) {
        int new_status = cyw43_tcpip_link_status(&cyw43_state, CYW43_ITF_STA);
        // If there was no network, keep trying
        if (new_status == CYW43_LINK_NONET) {
            new_status = CYW43_LINK_JOIN;
            err = cyw43_arch_wifi_connect_bssid_async(ssid, bssid, pw, auth);
            if (err) return err;
        }
        if (new_status != status) {
            status = new_status;
            CYW43_ARCH_DEBUG("connect status: %s\n", cyw43_tcpip_link_status_name(status));
        }
        if (time_reached(until)) {
            return PICO_ERROR_TIMEOUT;
        }
        // Do polling
        cyw43_arch_poll();
        cyw43_arch_wait_for_work_until(until);
    }
    // Turn status into a pico_error_codes, CYW43_LINK_NONET shouldn't happen as we fail with PICO_ERROR_TIMEOUT instead
    assert(status == CYW43_LINK_UP || status == CYW43_LINK_BADAUTH || status == CYW43_LINK_FAIL);
    if (status == CYW43_LINK_UP) {
        return PICO_OK; // success
    } else if (status == CYW43_LINK_BADAUTH) {
        return PICO_ERROR_BADAUTH;
    } else {
        return PICO_ERROR_CONNECT_FAILED;
    }
}

// Connect to wireless, return with success when an IP address has been assigned
static int cyw43_arch_wifi_connect_until(const char *ssid, const char *pw, uint32_t auth, absolute_time_t until) {
    return cyw43_arch_wifi_connect_bssid_until(ssid, NULL, pw, auth, until);
}

int cyw43_arch_wifi_connect_blocking(const char *ssid, const char *pw, uint32_t auth) {
    return cyw43_arch_wifi_connect_until(ssid, pw, auth, at_the_end_of_time);
}

int cyw43_arch_wifi_connect_bssid_blocking(const char *ssid, const uint8_t *bssid, const char *pw, uint32_t auth) {
    return cyw43_arch_wifi_connect_bssid_until(ssid, bssid, pw, auth, at_the_end_of_time);
}

int cyw43_arch_wifi_connect_timeout_ms(const char *ssid, const char *pw, uint32_t auth, uint32_t timeout_ms) {
    return cyw43_arch_wifi_connect_until(ssid, pw, auth, make_timeout_time_ms(timeout_ms));
}

int cyw43_arch_wifi_connect_bssid_timeout_ms(const char *ssid, const uint8_t *bssid, const char *pw, uint32_t auth, uint32_t timeout_ms) {
    return cyw43_arch_wifi_connect_bssid_until(ssid, bssid, pw, auth, make_timeout_time_ms(timeout_ms));
}

uint32_t cyw43_arch_get_country_code(void) {
    return country_code;
}

int cyw43_arch_init_with_country(uint32_t country) {
    country_code = country;
    return cyw43_arch_init();
}

void cyw43_arch_gpio_put(uint wl_gpio, bool value) {
    invalid_params_if(CYW43_ARCH, wl_gpio >= CYW43_WL_GPIO_COUNT);
    cyw43_gpio_set(&cyw43_state, (int)wl_gpio, value);
}

bool cyw43_arch_gpio_get(uint wl_gpio) {
    invalid_params_if(CYW43_ARCH, wl_gpio >= CYW43_WL_GPIO_COUNT);
    bool value = false;
    cyw43_gpio_get(&cyw43_state, (int)wl_gpio, &value);
    return value;
}

async_context_t *cyw43_arch_async_context(void) {
    return async_context;
}

void cyw43_arch_poll(void)
{
    async_context_poll(async_context);
}

void cyw43_arch_wait_for_work_until(absolute_time_t until) {
    async_context_wait_for_work_until(async_context, until);
}
