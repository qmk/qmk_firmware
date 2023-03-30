/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _HARDWARE_SPI_H
#define _HARDWARE_SPI_H

#include "pico.h"
#include "hardware/structs/spi.h"
#include "hardware/regs/dreq.h"

// PICO_CONFIG: PARAM_ASSERTIONS_ENABLED_SPI, Enable/disable assertions in the SPI module, type=bool, default=0, group=hardware_spi
#ifndef PARAM_ASSERTIONS_ENABLED_SPI
#define PARAM_ASSERTIONS_ENABLED_SPI 0
#endif

#ifdef __cplusplus
extern "C" {
#endif

/** \file hardware/spi.h
 *  \defgroup hardware_spi hardware_spi
 *
 * Hardware SPI API
 *
 * RP2040 has 2 identical instances of the Serial Peripheral Interface (SPI) controller.
 *
 * The PrimeCell SSP is a master or slave interface for synchronous serial communication with peripheral devices that have
 * Motorola SPI, National Semiconductor Microwire, or Texas Instruments synchronous serial interfaces.
 *
 * Controller can be defined as master or slave using the \ref spi_set_slave function.
 *
 * Each controller can be connected to a number of GPIO pins, see the datasheet GPIO function selection table for more information.
 */

// PICO_CONFIG: PICO_DEFAULT_SPI, Define the default SPI for a board, min=0, max=1, group=hardware_spi
// PICO_CONFIG: PICO_DEFAULT_SPI_SCK_PIN, Define the default SPI SCK pin, min=0, max=29, group=hardware_spi
// PICO_CONFIG: PICO_DEFAULT_SPI_TX_PIN, Define the default SPI TX pin, min=0, max=29, group=hardware_spi
// PICO_CONFIG: PICO_DEFAULT_SPI_RX_PIN, Define the default SPI RX pin, min=0, max=29, group=hardware_spi
// PICO_CONFIG: PICO_DEFAULT_SPI_CSN_PIN, Define the default SPI CSN pin, min=0, max=29, group=hardware_spi

/**
 * Opaque type representing an SPI instance.
 */
typedef struct spi_inst spi_inst_t;

/** Identifier for the first (SPI 0) hardware SPI instance (for use in SPI functions).
 *
 * e.g. spi_init(spi0, 48000)
 *
 *  \ingroup hardware_spi
 */
#define spi0 ((spi_inst_t *)spi0_hw)

/** Identifier for the second (SPI 1) hardware SPI instance (for use in SPI functions).
 *
 * e.g. spi_init(spi1, 48000)
 *
 *  \ingroup hardware_spi
 */
#define spi1 ((spi_inst_t *)spi1_hw)

#if !defined(PICO_DEFAULT_SPI_INSTANCE) && defined(PICO_DEFAULT_SPI)
#define PICO_DEFAULT_SPI_INSTANCE (__CONCAT(spi,PICO_DEFAULT_SPI))
#endif

#ifdef PICO_DEFAULT_SPI_INSTANCE
#define spi_default PICO_DEFAULT_SPI_INSTANCE
#endif

/** \brief Enumeration of SPI CPHA (clock phase) values.
 *  \ingroup hardware_spi
 */
typedef enum {
    SPI_CPHA_0 = 0,
    SPI_CPHA_1 = 1
} spi_cpha_t;

/** \brief Enumeration of SPI CPOL (clock polarity) values.
 *  \ingroup hardware_spi
 */
typedef enum {
    SPI_CPOL_0 = 0,
    SPI_CPOL_1 = 1
} spi_cpol_t;

/** \brief Enumeration of SPI bit-order values.
 *  \ingroup hardware_spi
 */
typedef enum {
    SPI_LSB_FIRST = 0,
    SPI_MSB_FIRST = 1
} spi_order_t;

// ----------------------------------------------------------------------------
// Setup

/*! \brief Initialise SPI instances
 *  \ingroup hardware_spi
 * Puts the SPI into a known state, and enable it. Must be called before other
 * functions.
 *
 * \note There is no guarantee that the baudrate requested can be achieved exactly; the nearest will be chosen
 * and returned
 *
 * \param spi SPI instance specifier, either \ref spi0 or \ref spi1
 * \param baudrate Baudrate requested in Hz
 * \return the actual baud rate set
 */
uint spi_init(spi_inst_t *spi, uint baudrate);

/*! \brief Deinitialise SPI instances
 *  \ingroup hardware_spi
 * Puts the SPI into a disabled state. Init will need to be called to reenable the device
 * functions.
 *
 * \param spi SPI instance specifier, either \ref spi0 or \ref spi1
 */
void spi_deinit(spi_inst_t *spi);

/*! \brief Set SPI baudrate
 *  \ingroup hardware_spi
 *
 * Set SPI frequency as close as possible to baudrate, and return the actual
 * achieved rate.
 *
 * \param spi SPI instance specifier, either \ref spi0 or \ref spi1
 * \param baudrate Baudrate required in Hz, should be capable of a bitrate of at least 2Mbps, or higher, depending on system clock settings.
 * \return The actual baudrate set
 */
uint spi_set_baudrate(spi_inst_t *spi, uint baudrate);

/*! \brief Get SPI baudrate
 *  \ingroup hardware_spi
 *
 * Get SPI baudrate which was set by \see spi_set_baudrate
 *
 * \param spi SPI instance specifier, either \ref spi0 or \ref spi1
 * \return The actual baudrate set
 */
uint spi_get_baudrate(const spi_inst_t *spi);

/*! \brief Convert SPI instance to hardware instance number
 *  \ingroup hardware_spi
 *
 * \param spi SPI instance
 * \return Number of SPI, 0 or 1.
 */
static inline uint spi_get_index(const spi_inst_t *spi) {
    invalid_params_if(SPI, spi != spi0 && spi != spi1);
    return spi == spi1 ? 1 : 0;
}

static inline spi_hw_t *spi_get_hw(spi_inst_t *spi) {
    spi_get_index(spi); // check it is a hw spi
    return (spi_hw_t *)spi;
}

static inline const spi_hw_t *spi_get_const_hw(const spi_inst_t *spi) {
    spi_get_index(spi);  // check it is a hw spi
    return (const spi_hw_t *)spi;
}

/*! \brief Configure SPI
 *  \ingroup hardware_spi
 *
 * Configure how the SPI serialises and deserialises data on the wire
 *
 * \param spi SPI instance specifier, either \ref spi0 or \ref spi1
 * \param data_bits Number of data bits per transfer. Valid values 4..16.
 * \param cpol SSPCLKOUT polarity, applicable to Motorola SPI frame format only.
 * \param cpha SSPCLKOUT phase, applicable to Motorola SPI frame format only
 * \param order Must be SPI_MSB_FIRST, no other values supported on the PL022
 */
static inline void spi_set_format(spi_inst_t *spi, uint data_bits, spi_cpol_t cpol, spi_cpha_t cpha, __unused spi_order_t order) {
    invalid_params_if(SPI, data_bits < 4 || data_bits > 16);
    // LSB-first not supported on PL022:
    invalid_params_if(SPI, order != SPI_MSB_FIRST);
    invalid_params_if(SPI, cpol != SPI_CPOL_0 && cpol != SPI_CPOL_1);
    invalid_params_if(SPI, cpha != SPI_CPHA_0 && cpha != SPI_CPHA_1);
    hw_write_masked(&spi_get_hw(spi)->cr0,
                    ((uint)(data_bits - 1)) << SPI_SSPCR0_DSS_LSB |
                    ((uint)cpol) << SPI_SSPCR0_SPO_LSB |
                    ((uint)cpha) << SPI_SSPCR0_SPH_LSB,
        SPI_SSPCR0_DSS_BITS |
        SPI_SSPCR0_SPO_BITS |
        SPI_SSPCR0_SPH_BITS);
}

/*! \brief Set SPI master/slave
 *  \ingroup hardware_spi
 *
 * Configure the SPI for master- or slave-mode operation. By default,
 * spi_init() sets master-mode.
 *
 * \param spi SPI instance specifier, either \ref spi0 or \ref spi1
 * \param slave true to set SPI device as a slave device, false for master.
 */
static inline void spi_set_slave(spi_inst_t *spi, bool slave) {
    if (slave)
        hw_set_bits(&spi_get_hw(spi)->cr1, SPI_SSPCR1_MS_BITS);
    else
        hw_clear_bits(&spi_get_hw(spi)->cr1, SPI_SSPCR1_MS_BITS);
}

// ----------------------------------------------------------------------------
// Generic input/output

/*! \brief Check whether a write can be done on SPI device
 *  \ingroup hardware_spi
 *
 * \param spi SPI instance specifier, either \ref spi0 or \ref spi1
 * \return false if no space is available to write. True if a write is possible
 */
static inline bool spi_is_writable(const spi_inst_t *spi) {
    return (spi_get_const_hw(spi)->sr & SPI_SSPSR_TNF_BITS);
}

/*! \brief Check whether a read can be done on SPI device
 *  \ingroup hardware_spi
 *
 * \param spi SPI instance specifier, either \ref spi0 or \ref spi1
 * \return true if a read is possible i.e. data is present
 */
static inline bool spi_is_readable(const spi_inst_t *spi) {
    return (spi_get_const_hw(spi)->sr & SPI_SSPSR_RNE_BITS);
}

/*! \brief Check whether SPI is busy
 *  \ingroup hardware_spi
 *
 * \param spi SPI instance specifier, either \ref spi0 or \ref spi1
 * \return true if SPI is busy
 */
static inline bool spi_is_busy(const spi_inst_t *spi) {
    return (spi_get_const_hw(spi)->sr & SPI_SSPSR_BSY_BITS);
}

/*! \brief Write/Read to/from an SPI device
 *  \ingroup hardware_spi
 *
 * Write \p len bytes from \p src to SPI. Simultaneously read \p len bytes from SPI to \p dst.
 * Blocks until all data is transferred. No timeout, as SPI hardware always transfers at a known data rate.
 *
 * \param spi SPI instance specifier, either \ref spi0 or \ref spi1
 * \param src Buffer of data to write
 * \param dst Buffer for read data
 * \param len Length of BOTH buffers
 * \return Number of bytes written/read
*/
int spi_write_read_blocking(spi_inst_t *spi, const uint8_t *src, uint8_t *dst, size_t len);

/*! \brief Write to an SPI device, blocking
 *  \ingroup hardware_spi
 *
 * Write \p len bytes from \p src to SPI, and discard any data received back
 * Blocks until all data is transferred. No timeout, as SPI hardware always transfers at a known data rate.
 *
 * \param spi SPI instance specifier, either \ref spi0 or \ref spi1
 * \param src Buffer of data to write
 * \param len Length of \p src
 * \return Number of bytes written/read
 */
int spi_write_blocking(spi_inst_t *spi, const uint8_t *src, size_t len);

/*! \brief Read from an SPI device
 *  \ingroup hardware_spi
 *
 * Read \p len bytes from SPI to \p dst.
 * Blocks until all data is transferred. No timeout, as SPI hardware always transfers at a known data rate.
 * \p repeated_tx_data is output repeatedly on TX as data is read in from RX.
 * Generally this can be 0, but some devices require a specific value here,
 * e.g. SD cards expect 0xff
 *
 * \param spi SPI instance specifier, either \ref spi0 or \ref spi1
 * \param repeated_tx_data Buffer of data to write
 * \param dst Buffer for read data
 * \param len Length of buffer \p dst
 * \return Number of bytes written/read
 */
int spi_read_blocking(spi_inst_t *spi, uint8_t repeated_tx_data, uint8_t *dst, size_t len);

// ----------------------------------------------------------------------------
// SPI-specific operations and aliases

// FIXME need some instance-private data for select() and deselect() if we are going that route

/*! \brief Write/Read half words to/from an SPI device
 *  \ingroup hardware_spi
 *
 * Write \p len halfwords from \p src to SPI. Simultaneously read \p len halfwords from SPI to \p dst.
 * Blocks until all data is transferred. No timeout, as SPI hardware always transfers at a known data rate.
 *
 * \note SPI should be initialised with 16 data_bits using \ref spi_set_format first, otherwise this function will only read/write 8 data_bits.
 *
 * \param spi SPI instance specifier, either \ref spi0 or \ref spi1
 * \param src Buffer of data to write
 * \param dst Buffer for read data
 * \param len Length of BOTH buffers in halfwords
 * \return Number of halfwords written/read
*/
int spi_write16_read16_blocking(spi_inst_t *spi, const uint16_t *src, uint16_t *dst, size_t len);

/*! \brief Write to an SPI device
 *  \ingroup hardware_spi
 *
 * Write \p len halfwords from \p src to SPI. Discard any data received back.
 * Blocks until all data is transferred. No timeout, as SPI hardware always transfers at a known data rate.
 *
 * \note SPI should be initialised with 16 data_bits using \ref spi_set_format first, otherwise this function will only write 8 data_bits.
 *
 * \param spi SPI instance specifier, either \ref spi0 or \ref spi1
 * \param src Buffer of data to write
 * \param len Length of buffers
 * \return Number of halfwords written/read
*/
int spi_write16_blocking(spi_inst_t *spi, const uint16_t *src, size_t len);

/*! \brief Read from an SPI device
 *  \ingroup hardware_spi
 *
 * Read \p len halfwords from SPI to \p dst.
 * Blocks until all data is transferred. No timeout, as SPI hardware always transfers at a known data rate.
 * \p repeated_tx_data is output repeatedly on TX as data is read in from RX.
 * Generally this can be 0, but some devices require a specific value here,
 * e.g. SD cards expect 0xff
 *
 * \note SPI should be initialised with 16 data_bits using \ref spi_set_format first, otherwise this function will only read 8 data_bits.
 *
 * \param spi SPI instance specifier, either \ref spi0 or \ref spi1
 * \param repeated_tx_data Buffer of data to write
 * \param dst Buffer for read data
 * \param len Length of buffer \p dst in halfwords
 * \return Number of halfwords written/read
 */
int spi_read16_blocking(spi_inst_t *spi, uint16_t repeated_tx_data, uint16_t *dst, size_t len);

/*! \brief Return the DREQ to use for pacing transfers to/from a particular SPI instance
 *  \ingroup hardware_spi
 *
 * \param spi SPI instance specifier, either \ref spi0 or \ref spi1
 * \param is_tx true for sending data to the SPI instance, false for receiving data from the SPI instance
 */
static inline uint spi_get_dreq(spi_inst_t *spi, bool is_tx) {
    static_assert(DREQ_SPI0_RX == DREQ_SPI0_TX + 1, "");
    static_assert(DREQ_SPI1_RX == DREQ_SPI1_TX + 1, "");
    static_assert(DREQ_SPI1_TX == DREQ_SPI0_TX + 2, "");
    return DREQ_SPI0_TX + spi_get_index(spi) * 2 + !is_tx;
}

#ifdef __cplusplus
}
#endif

#endif
