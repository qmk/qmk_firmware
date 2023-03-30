/*
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_CYW43_ARCH_H
#define _PICO_CYW43_ARCH_H

#include "pico.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "cyw43.h"
#include "cyw43_country.h"
#include "pico/async_context.h"

#ifdef PICO_CYW43_ARCH_HEADER
#include __XSTRING(PICO_CYW43_ARCH_HEADER)
#else
#if PICO_CYW43_ARCH_POLL
#include "pico/cyw43_arch/arch_poll.h"
#elif PICO_CYW43_ARCH_THREADSAFE_BACKGROUND
#include "pico/cyw43_arch/arch_threadsafe_background.h"
#elif PICO_CYW43_ARCH_FREERTOS
#include "pico/cyw43_arch/arch_freertos.h"
#else
#error must specify support pico_cyw43_arch architecture type or set PICO_CYW43_ARCH_HEADER
#endif
#endif

/**
 * \defgroup cyw43_driver cyw43_driver
 * \ingroup pico_cyw43_arch
 * \brief Driver used for Pico W wireless
*/

/**
 * \defgroup cyw43_ll cyw43_ll
 * \ingroup cyw43_driver
 * \brief Low Level CYW43 driver interface
*/

/** \file pico/cyw43_arch.h
 *  \defgroup pico_cyw43_arch pico_cyw43_arch
 *
 * Architecture for integrating the CYW43 driver (for the wireless on Pico W) and lwIP (for TCP/IP stack) into the SDK. It is also necessary for accessing the on-board LED on Pico W
 *
 * Both the low level \c cyw43_driver and the lwIP stack require periodic servicing, and have limitations
 * on whether they can be called from multiple cores/threads.
 *
 * \c pico_cyw43_arch attempts to abstract these complications into several behavioral groups:
 *
 * * \em 'poll' - This not multi-core/IRQ safe, and requires the user to call \ref cyw43_arch_poll periodically from their main loop
 * * \em 'thread_safe_background' - This is multi-core/thread/task safe, and maintenance of the driver and TCP/IP stack is handled automatically in the background
 * * \em 'freertos' - This is multi-core/thread/task safe, and uses a separate FreeRTOS task to handle lwIP and and driver work.
 *
 * As of right now, lwIP is the only supported TCP/IP stack, however the use of \c pico_cyw43_arch is intended to be independent of
 * the particular TCP/IP stack used (and possibly Bluetooth stack used) in the future. For this reason, the integration of lwIP
 * is handled in the base (\c pico_cyw43_arch) library based on the #define \ref CYW43_LWIP used by the \c cyw43_driver.
 *
 * \note As of version 1.5.0 of the Raspberry Pi Pico SDK, the \c pico_cyw43_arch library no longer directly implements
 * the distinct behavioral abstractions. This is now handled by the more general \ref pico_async_context library. The
 * user facing behavior of pico_cyw43_arch has not changed as a result of this implementation detail, however pico_cyw43_arch
 * is now just a thin wrapper which creates an appropriate async_context and makes a simple call to add lwIP or cyw43_driver support
 * as appropriate. You are free to perform this context creation and adding of lwIP, cyw43_driver or indeed any other additional
 * future protocol/driver support to your async_context, however for now pico_cyw43_arch does still provide a few cyw43_ specific (i.e. Pico W)
 * APIs for connection management, locking and GPIO interaction.
 *
 * \note The connection management APIs at least may be moved
 * to a more generic library in a future release. The locking methods are now backed by their \ref pico_async_context equivalents, and
 * those methods may be used interchangeably (see \ref cyw43_arch_lwip_begin, \ref cyw43_arch_lwip_end and \ref cyw43_arch_lwip_check for more details).
 *
 * \note For examples of creating of your own async_context and addition of \c cyw43_driver and \c lwIP support, please
 * refer to the specific source files \c cyw43_arch_poll.c, \c cyw43_arch_threadsafe_background.c and \c cyw43_arch_freertos.c.
 *
 * Whilst you can use the \c pico_cyw43_arch library directly and specify \ref CYW43_LWIP (and other defines) yourself, several
 * other libraries are made available to the build which aggregate the defines and other dependencies for you:
 *
 * * \b pico_cyw43_arch_lwip_poll - For using the RAW lwIP API (in `NO_SYS=1` mode) without any background processing or multi-core/thread safety.
 *
 *    The user must call \ref pico_cyw43_poll periodically from their main loop.
 *
 *    This wrapper library:
 *    - Sets \c CYW43_LWIP=1 to enable lwIP support in \c pico_cyw43_arch and \c cyw43_driver.
 *    - Sets \c PICO_CYW43_ARCH_POLL=1 to select the polling behavior.
 *    - Adds the \c pico_lwip as a dependency to pull in lwIP.
 *
 * * \b pico_cyw43_arch_lwip_threadsafe_background - For using the RAW lwIP API (in `NO_SYS=1` mode) with multi-core/thread safety, and automatic servicing of the \c cyw43_driver and
 * lwIP in background.
 *
 *    Calls into the \c cyw43_driver high level API (cyw43.h) may be made from either core or from lwIP callbacks, however calls into lwIP (which
 * is not thread-safe) other than those made from lwIP callbacks, must be bracketed with \ref cyw43_arch_lwip_begin and \ref cyw43_arch_lwip_end. It is fine to bracket
 * calls made from within lwIP callbacks too; you just don't have to.
 *
 *    \note lwIP callbacks happen in a (low priority) IRQ context (similar to an alarm callback), so care should be taken when interacting
 *    with other code.
 *
 *    This wrapper library:
 *    - Sets \c CYW43_LWIP=1 to enable lwIP support in \c pico_cyw43_arch and \c cyw43_driver
 *    - Sets \c PICO_CYW43_ARCH_THREADSAFE_BACKGROUND=1 to select the thread-safe/non-polling behavior.
 *    - Adds the pico_lwip as a dependency to pull in lwIP.
 *
 *
 *    This library \em can also be used under the RP2040 port of FreeRTOS with lwIP in `NO_SYS=1` mode (allowing you to call \c cyw43_driver APIs
 * from any task, and to call lwIP from lwIP callbacks, or from any task if you bracket the calls with \ref cyw43_arch_lwip_begin and \ref cyw43_arch_lwip_end. Again, you should be
 * careful about what you do in lwIP callbacks, as you cannot call most FreeRTOS APIs from within an IRQ context. Unless you have good reason, you should probably
 * use the full FreeRTOS integration (with `NO_SYS=0`) provided by \c pico_cyw43_arch_lwip_sys_freertos.
 *
 * * \b pico_cyw43_arch_lwip_sys_freertos - For using the full lwIP API including blocking sockets in OS (`NO_SYS=0`) mode, along with with multi-core/task/thread safety, and automatic servicing of the \c cyw43_driver and
 * the lwIP stack.
 *
 *    This wrapper library:
 *    - Sets \c CYW43_LWIP=1 to enable lwIP support in \c pico_cyw43_arch and \c cyw43_driver.
 *    - Sets \c PICO_CYW43_ARCH_FREERTOS=1 to select the NO_SYS=0 lwip/FreeRTOS integration
 *    - Sets \c LWIP_PROVIDE_ERRNO=1 to provide error numbers needed for compilation without an OS
 *    - Adds the \c pico_lwip as a dependency to pull in lwIP.
 *    - Adds the lwIP/FreeRTOS code from lwip-contrib (in the contrib directory of lwIP)
 *
 *    Calls into the \c cyw43_driver high level API (cyw43.h) may be made from any task or from lwIP callbacks, but not from IRQs. Calls into the lwIP RAW API (which is not thread safe)
 *    must be bracketed with \ref cyw43_arch_lwip_begin and \ref cyw43_arch_lwip_end. It is fine to bracket calls made from within lwIP callbacks too; you just don't have to.
 *
 *    \note this wrapper library requires you to link FreeRTOS functionality with your application yourself.
 *
 * * \b pico_cyw43_arch_none - If you do not need the TCP/IP stack but wish to use the on-board LED.
 *
 *    This wrapper library:
 *    - Sets \c CYW43_LWIP=0 to disable lwIP support in \c pico_cyw43_arch and \c cyw43_driver
 */

// PICO_CONFIG: PARAM_ASSERTIONS_ENABLED_CYW43_ARCH, Enable/disable assertions in the pico_cyw43_arch module, type=bool, default=0, group=pico_cyw43_arch
#ifndef PARAM_ASSERTIONS_ENABLED_CYW43_ARCH
#define PARAM_ASSERTIONS_ENABLED_CYW43_ARCH 0
#endif

// PICO_CONFIG: PICO_CYW43_ARCH_DEBUG_ENABLED, Enable/disable some debugging output in the pico_cyw43_arch module, type=bool, default=1 in debug builds, group=pico_cyw43_arch
#ifndef PICO_CYW43_ARCH_DEBUG_ENABLED
#ifndef NDEBUG
#define PICO_CYW43_ARCH_DEBUG_ENABLED 1
#else
#define PICO_CYW43_ARCH_DEBUG_ENABLED 0
#endif
#endif

// PICO_CONFIG: PICO_CYW43_ARCH_DEFAULT_COUNTRY_CODE, Default country code for the cyw43 wireless driver, default=CYW43_COUNTRY_WORLDWIDE, group=pico_cyw43_arch
#ifndef PICO_CYW43_ARCH_DEFAULT_COUNTRY_CODE
#define PICO_CYW43_ARCH_DEFAULT_COUNTRY_CODE CYW43_COUNTRY_WORLDWIDE
#endif

/*!
 * \brief Initialize the CYW43 architecture
 * \ingroup pico_cyw43_arch
 *
 * This method initializes the `cyw43_driver` code and initializes the lwIP stack (if it
 * was enabled at build time). This method must be called prior to using any other \c pico_cyw43_arch,
 * \c cyw43_driver or lwIP functions.
 *
 * \note this method initializes wireless with a country code of \c PICO_CYW43_ARCH_DEFAULT_COUNTRY_CODE
 * which defaults to \c CYW43_COUNTRY_WORLDWIDE. Worldwide settings may not give the best performance; consider
 * setting PICO_CYW43_ARCH_DEFAULT_COUNTRY_CODE to a different value or calling \ref cyw43_arch_init_with_country
 *
 * By default this method initializes the cyw43_arch code's own async_context by calling
 * \ref cyw43_arch_init_default_async_context, however the user can specify use of their own async_context
 * by calling \ref cyw43_arch_set_async_context() before calling this method
 *
 * \return 0 if the initialization is successful, an error code otherwise \see pico_error_codes
 */
int cyw43_arch_init(void);

/*!
 * \brief Initialize the CYW43 architecture for use in a specific country
 * \ingroup pico_cyw43_arch
 *
 * This method initializes the `cyw43_driver` code and initializes the lwIP stack (if it
 * was enabled at build time). This method must be called prior to using any other \c pico_cyw43_arch,
 * \c cyw43_driver or lwIP functions.
 *
 * By default this method initializes the cyw43_arch code's own async_context by calling
 * \ref cyw43_arch_init_default_async_context, however the user can specify use of their own async_context
 * by calling \ref cyw43_arch_set_async_context() before calling this method
 *
 * \param country the country code to use (see \ref CYW43_COUNTRY_)
 * \return 0 if the initialization is successful, an error code otherwise \see pico_error_codes
 */
int cyw43_arch_init_with_country(uint32_t country);

/*!
 * \brief De-initialize the CYW43 architecture
 * \ingroup pico_cyw43_arch
 *
 * This method de-initializes the `cyw43_driver` code and de-initializes the lwIP stack (if it
 * was enabled at build time). Note this method should always be called from the same core (or RTOS
 * task, depending on the environment) as \ref cyw43_arch_init.
 *
 * Additionally if the cyw43_arch is using its own async_context instance, then that instance is de-initialized.
 */
void cyw43_arch_deinit(void);

/*!
 * \brief Return the current async_context currently in use by the cyw43_arch code
 * \ingroup pico_cyw43_arch
 *
 * \return the async_context.
 */
async_context_t *cyw43_arch_async_context(void);

/*!
 * \brief Set the async_context to be used by the cyw43_arch_init
 * \ingroup pico_cyw43_arch
 *
 * \note This method must be called before calling cyw43_arch_init or cyw43_arch_init_with_country
 * if you wish to use a custom async_context instance.
 *
 * \param context the async_context to be used
 */
void cyw43_arch_set_async_context(async_context_t *context);

/*!
 * \brief Initialize the default async_context for the current cyw43_arch type
 * \ingroup pico_cyw43_arch
 *
 * This method initializes and returns a pointer to the static async_context associated
 * with cyw43_arch. This method is called by \ref cyw43_arch_init automatically
 * if a different async_context has not been set by \ref cyw43_arch_set_async_context
 *
 * \return the context or NULL if initialization failed.
 */
async_context_t *cyw43_arch_init_default_async_context(void);

/*!
 * \brief Perform any processing required by the \c cyw43_driver or the TCP/IP stack
 * \ingroup pico_cyw43_arch
 *
 * This method must be called periodically from the main loop when using a
 * \em polling style \c pico_cyw43_arch (e.g. \c pico_cyw43_arch_lwip_poll ). It
 * may be called in other styles, but it is unnecessary to do so.
 */
void cyw43_arch_poll(void);

/*!
 * \brief Sleep until there is cyw43_driver work to be done
 * \ingroup pico_cyw43_arch
 *
 * This method may be called by code that is waiting for an event to
 * come from the cyw43_driver, and has no work to do, but would like
 * to sleep without blocking any background work associated with the cyw43_driver.
 *
 * \param until the time to wait until if there is no work to do.
 */
void cyw43_arch_wait_for_work_until(absolute_time_t until);

/*!
 * \fn cyw43_arch_lwip_begin
 * \brief Acquire any locks required to call into lwIP
 * \ingroup pico_cyw43_arch
 *
 * The lwIP API is not thread safe. You should surround calls into the lwIP API
 * with calls to this method and \ref cyw43_arch_lwip_end. Note these calls are not
 * necessary (but harmless) when you are calling back into the lwIP API from an lwIP callback.
 * If you are using single-core polling only (pico_cyw43_arch_poll) then these calls are no-ops
 * anyway it is good practice to call them anyway where they are necessary.
 *
 * \note as of SDK release 1.5.0, this is now equivalent to calling \ref pico_async_context_acquire_lock_blocking
 * on the async_context associated with cyw43_arch and lwIP.
 *
 * \sa cyw43_arch_lwip_end
 * \sa cyw43_arch_lwip_protect
 * \sa async_context_acquire_lock_blocking
 * \sa cyw43_arch_async_context
 */
static inline void cyw43_arch_lwip_begin(void) {
    cyw43_thread_enter();
}

/*!
 * \fn void cyw43_arch_lwip_end(void)
 * \brief Release any locks required for calling into lwIP
 * \ingroup pico_cyw43_arch
 *
 * The lwIP API is not thread safe. You should surround calls into the lwIP API
 * with calls to \ref cyw43_arch_lwip_begin and this method. Note these calls are not
 * necessary (but harmless) when you are calling back into the lwIP API from an lwIP callback.
 * If you are using single-core polling only (pico_cyw43_arch_poll) then these calls are no-ops
 * anyway it is good practice to call them anyway where they are necessary.
 *
 * \note as of SDK release 1.5.0, this is now equivalent to calling \ref async_context_release_lock
 * on the async_context associated with cyw43_arch and lwIP.
 *
 * \sa cyw43_arch_lwip_begin
 * \sa cyw43_arch_lwip_protect
 * \sa async_context_release_lock
 * \sa cyw43_arch_async_context
 */
static inline void cyw43_arch_lwip_end(void) {
    cyw43_thread_exit();
}

/*!
 * \fn int cyw43_arch_lwip_protect(int (*func)(void *param), void *param)
 * \brief sad Release any locks required for calling into lwIP
 * \ingroup pico_cyw43_arch
 *
 * The lwIP API is not thread safe. You can use this method to wrap a function
 * with any locking required to call into the lwIP API. If you are using
 * single-core polling only (pico_cyw43_arch_poll) then there are no
 * locks to required, but it is still good practice to use this function.
 *
 * \param func the function ta call with any required locks held
 * \param param parameter to pass to \c func
 * \return the return value from \c func
 * \sa cyw43_arch_lwip_begin
 * \sa cyw43_arch_lwip_end
 */
static inline int cyw43_arch_lwip_protect(int (*func)(void *param), void *param) {
    cyw43_arch_lwip_begin();
    int rc = func(param);
    cyw43_arch_lwip_end();
    return rc;
}

/*!
 * \fn void cyw43_arch_lwip_check(void)
 * \brief Checks the caller has any locks required for calling into lwIP
 * \ingroup pico_cyw43_arch
 *
 * The lwIP API is not thread safe. You should surround calls into the lwIP API
 * with calls to \ref cyw43_arch_lwip_begin and this method. Note these calls are not
 * necessary (but harmless) when you are calling back into the lwIP API from an lwIP callback.
 *
 * This method will assert in debug mode, if the above conditions are not met (i.e. it is not safe to
 * call into the lwIP API)
 *
 * \note as of SDK release 1.5.0, this is now equivalent to calling \ref async_context_lock_check
 * on the async_context associated with cyw43_arch and lwIP.
 *
 * \sa cyw43_arch_lwip_begin
 * \sa cyw43_arch_lwip_protect
 * \sa async_context_lock_check
 * \sa cyw43_arch_async_context
 */

/*!
 * \brief Return the country code used to initialize cyw43_arch
 * \ingroup pico_cyw43_arch
 *
 * \return the country code (see \ref CYW43_COUNTRY_)
 */
uint32_t cyw43_arch_get_country_code(void);

/*!
 * \brief Enables Wi-Fi STA (Station) mode.
 * \ingroup pico_cyw43_arch
 *
 * This enables the Wi-Fi in \emStation mode such that connections can be made to other Wi-Fi Access Points
 */
void cyw43_arch_enable_sta_mode(void);

/*!
 * \brief Enables Wi-Fi AP (Access point) mode.
 * \ingroup pico_cyw43_arch
 *
 * This enables the Wi-Fi in \em Access \em Point mode such that connections can be made to the device by  other Wi-Fi clients
 * \param ssid the name for the access point
 * \param password the password to use or NULL for no password.
 * \param auth the authorization type to use when the password is enabled. Values are \ref CYW43_AUTH_WPA_TKIP_PSK,
 *             \ref CYW43_AUTH_WPA2_AES_PSK, or \ref CYW43_AUTH_WPA2_MIXED_PSK (see \ref CYW43_AUTH_)
 */
void cyw43_arch_enable_ap_mode(const char *ssid, const char *password, uint32_t auth);

/*!
 * \brief Attempt to connect to a wireless access point, blocking until the network is joined or a failure is detected.
 * \ingroup pico_cyw43_arch
 *
 * \param ssid the network name to connect to
 * \param pw the network password or NULL if there is no password required
 * \param auth the authorization type to use when the password is enabled. Values are \ref CYW43_AUTH_WPA_TKIP_PSK,
 *             \ref CYW43_AUTH_WPA2_AES_PSK, or \ref CYW43_AUTH_WPA2_MIXED_PSK (see \ref CYW43_AUTH_)
 *
 * \return 0 if the initialization is successful, an error code otherwise \see pico_error_codes
 */
int cyw43_arch_wifi_connect_blocking(const char *ssid, const char *pw, uint32_t auth);

/*!
 * \brief Attempt to connect to a wireless access point specified by SSID and BSSID, blocking until the network is joined or a failure is detected.
 * \ingroup pico_cyw43_arch
 *
 * \param ssid the network name to connect to
 * \param bssid the network BSSID to connect to or NULL if ignored
 * \param password the network password or NULL if there is no password required
 * \param auth the authorization type to use when the password is enabled. Values are \ref CYW43_AUTH_WPA_TKIP_PSK,
 *             \ref CYW43_AUTH_WPA2_AES_PSK, or \ref CYW43_AUTH_WPA2_MIXED_PSK (see \ref CYW43_AUTH_)
 *
 * \return 0 if the initialization is successful, an error code otherwise \see pico_error_codes
 */
int cyw43_arch_wifi_connect_bssid_blocking(const char *ssid, const uint8_t *bssid, const char *pw, uint32_t auth);

/*!
 * \brief Attempt to connect to a wireless access point, blocking until the network is joined, a failure is detected or a timeout occurs
 * \ingroup pico_cyw43_arch
 *
 * \param ssid the network name to connect to
 * \param pw the network password or NULL if there is no password required
 * \param auth the authorization type to use when the password is enabled. Values are \ref CYW43_AUTH_WPA_TKIP_PSK,
 *             \ref CYW43_AUTH_WPA2_AES_PSK, or \ref CYW43_AUTH_WPA2_MIXED_PSK (see \ref CYW43_AUTH_)
 *
 * \return 0 if the initialization is successful, an error code otherwise \see pico_error_codes
 */
int cyw43_arch_wifi_connect_timeout_ms(const char *ssid, const char *pw, uint32_t auth, uint32_t timeout);

/*!
 * \brief Attempt to connect to a wireless access point specified by SSID and BSSID, blocking until the network is joined, a failure is detected or a timeout occurs
 * \ingroup pico_cyw43_arch
 *
 * \param ssid the network name to connect to
 * \param bssid the network BSSID to connect to or NULL if ignored
 * \param password the network password or NULL if there is no password required
 * \param auth the authorization type to use when the password is enabled. Values are \ref CYW43_AUTH_WPA_TKIP_PSK,
 *             \ref CYW43_AUTH_WPA2_AES_PSK, or \ref CYW43_AUTH_WPA2_MIXED_PSK (see \ref CYW43_AUTH_)
 *
 * \return 0 if the initialization is successful, an error code otherwise \see pico_error_codes
 */
int cyw43_arch_wifi_connect_bssid_timeout_ms(const char *ssid, const uint8_t *bssid, const char *pw, uint32_t auth, uint32_t timeout);

/*!
 * \brief Start attempting to connect to a wireless access point
 * \ingroup pico_cyw43_arch
 *
 * This method tells the CYW43 driver to start connecting to an access point. You should subsequently check the
 * status by calling \ref cyw43_wifi_link_status.
 *
 * \param ssid the network name to connect to
 * \param pw the network password or NULL if there is no password required
 * \param auth the authorization type to use when the password is enabled. Values are \ref CYW43_AUTH_WPA_TKIP_PSK,
 *             \ref CYW43_AUTH_WPA2_AES_PSK, or \ref CYW43_AUTH_WPA2_MIXED_PSK (see \ref CYW43_AUTH_)
 *
 * \return 0 if the scan was started successfully, an error code otherwise \see pico_error_codes
 */
int cyw43_arch_wifi_connect_async(const char *ssid, const char *pw, uint32_t auth);

/*!
 * \brief Start attempting to connect to a wireless access point specified by SSID and BSSID
 * \ingroup pico_cyw43_arch
 *
 * This method tells the CYW43 driver to start connecting to an access point. You should subsequently check the
 * status by calling \ref cyw43_wifi_link_status.
 *
 * \param ssid the network name to connect to
 * \param bssid the network BSSID to connect to or NULL if ignored
 * \param password the network password or NULL if there is no password required
 * \param auth the authorization type to use when the password is enabled. Values are \ref CYW43_AUTH_WPA_TKIP_PSK,
 *             \ref CYW43_AUTH_WPA2_AES_PSK, or \ref CYW43_AUTH_WPA2_MIXED_PSK (see \ref CYW43_AUTH_)
 *
 * \return 0 if the scan was started successfully, an error code otherwise \see pico_error_codes
 */
int cyw43_arch_wifi_connect_bssid_async(const char *ssid, const uint8_t *bssid, const char *pw, uint32_t auth);

/*!
 * \brief Set a GPIO pin on the wireless chip to a given value
 * \ingroup pico_cyw43_arch
 * \note this method does not check for errors setting the GPIO. You can use the lower level \ref cyw43_gpio_set instead if you wish
 * to check for errors.
 *
 * \param wl_gpio the GPIO number on the wireless chip
 * \param value true to set the GPIO, false to clear it.
 */
void cyw43_arch_gpio_put(uint wl_gpio, bool value);

/*!
 * \brief Read the value of a GPIO pin on the wireless chip
 * \ingroup pico_cyw43_arch
 * \note this method does not check for errors setting the GPIO. You can use the lower level \ref cyw43_gpio_get instead if you wish
 * to check for errors.
 *
 * \param wl_gpio the GPIO number on the wireless chip
 * \return true if the GPIO is high, false otherwise
 */
bool cyw43_arch_gpio_get(uint wl_gpio);

#ifdef __cplusplus
}
#endif

#endif
