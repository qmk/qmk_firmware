/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_RTC_H
#define _HARDWARE_RTC_H

#include "pico.h"
#include "hardware/structs/rtc.h"

/** \file hardware/rtc.h
 *  \defgroup hardware_rtc hardware_rtc
 *
 * Hardware Real Time Clock API
 *
 * The RTC keeps track of time in human readable format and generates events when the time is equal
 * to a preset value. Think of a digital clock, not epoch time used by most computers. There are seven
 * fields, one each for year (12 bit), month (4 bit), day (5 bit), day of the week (3 bit), hour (5 bit)
 * minute (6 bit) and second (6 bit), storing the data in binary format.
 *
 * \sa datetime_t
 *
 * \subsection rtc_example Example
 * \addtogroup hardware_rtc
 *
 * \include hello_rtc.c
 */

#ifdef __cplusplus
extern "C" {
#endif

/*! Callback function type for RTC alarms
 *  \ingroup hardware_rtc
 *
 * \sa rtc_set_alarm()
 */
typedef void (*rtc_callback_t)(void);

/*! \brief Initialise the RTC system
 *  \ingroup hardware_rtc
 */
void rtc_init(void);

/*! \brief Set the RTC to the specified time
 *  \ingroup hardware_rtc
 *
 * \note Note that after setting the RTC date and time, a subsequent read of the values (e.g. via rtc_get_datetime()) may not
 * reflect the new setting until up to three cycles of the potentially-much-slower RTC clock domain have passed. This represents a period
 * of 64 microseconds with the default RTC clock configuration.
 *
 * \param t Pointer to a \ref datetime_t structure contains time to set
 * \return true if set, false if the passed in datetime was invalid.
 */
bool rtc_set_datetime(datetime_t *t);

/*! \brief Get the current time from the RTC
 *  \ingroup hardware_rtc
 *
 * \param t Pointer to a \ref datetime_t structure to receive the current RTC time
 * \return true if datetime is valid, false if the RTC is not running.
 */
bool rtc_get_datetime(datetime_t *t);

/*! \brief Is the RTC running?
 *  \ingroup hardware_rtc
 *
 */
bool rtc_running(void);

/*! \brief Set a time in the future for the RTC to call a user provided callback
 *  \ingroup hardware_rtc
 *
 *  \param t Pointer to a \ref datetime_t structure containing a time in the future to fire the alarm. Any values set to -1 will not be matched on.
 *  \param user_callback pointer to a \ref rtc_callback_t to call when the alarm fires
 */
void rtc_set_alarm(datetime_t *t, rtc_callback_t user_callback);

/*! \brief Enable the RTC alarm (if inactive)
 *  \ingroup hardware_rtc
 */
void rtc_enable_alarm(void);

/*! \brief Disable the RTC alarm (if active)
 *  \ingroup hardware_rtc
 */
void rtc_disable_alarm(void);

#ifdef __cplusplus
}
#endif

#endif
