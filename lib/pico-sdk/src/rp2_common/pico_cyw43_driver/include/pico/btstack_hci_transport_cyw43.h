/*
 * Copyright (c) 2023 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_BTSTACK_HCI_TRANSPORT_CYW43_H
#define _PICO_BTSTACK_HCI_TRANSPORT_CYW43_H

#ifdef __cplusplus
extern "C" {
#endif

/** \file pico/btstack_hci_transport_cyw43.h
* \ingroup pico_cyw43_driver
* \brief Adds low level Bluetooth HCI support
*/

/**
 * \brief Get the Bluetooth HCI transport instance for cyw43
 * \ingroup pico_cyw43_driver
 *
 * \return An instantiation of the hci_transport_t interface for the cyw43 chipset
 */
const hci_transport_t *hci_transport_cyw43_instance(void);

#ifdef __cplusplus
}
#endif

#endif // HCI_TRANSPORT_CYW43_H
