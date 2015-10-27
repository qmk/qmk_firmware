/*
 * @brief LPC8xx I2C ROM API declarations and functions
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#ifndef __ROM_I2C_8XX_H_
#define __ROM_I2C_8XX_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup CHIP_I2CROM_8XX CHIP: LPC8xx I2C ROM API declarations and functions
 * @ingroup CHIP_8XX_Drivers
 * @{
 */

/**
 * @brief LPC8xx I2C ROM driver handle structure
 */
typedef void *I2C_HANDLE_T;

typedef uint32_t ErrorCode_t;

/**
 * @brief LPC8xx I2C ROM driver callback function
 */
typedef void  (*I2C_CALLBK_T)(uint32_t err_code, uint32_t n);

/**
 * LPC8xx I2C ROM driver parameter structure
 */
typedef struct I2C_PARAM {
	uint32_t        num_bytes_send;		/*!< No. of bytes to send */
	uint32_t        num_bytes_rec;		/*!< No. of bytes to receive */
	uint8_t         *buffer_ptr_send;	/*!< Pointer to send buffer */
	uint8_t         *buffer_ptr_rec;	/*!< Pointer to receive buffer */
	I2C_CALLBK_T    func_pt;			/*!< Callback function */
	uint8_t         stop_flag;			/*!< Stop flag */
	uint8_t         dummy[3];
} I2C_PARAM_T;

/**
 * LPC8xx I2C ROM driver result structure
 */
typedef struct I2C_RESULT {
	uint32_t n_bytes_sent;	/*!< No. of bytes sent */
	uint32_t n_bytes_recd;	/*!< No. of bytes received */
} I2C_RESULT_T;

/**
 * LPC8xx I2C ROM driver modes enum
 */
typedef enum CHIP_I2C_MODE {
	IDLE,			/*!< IDLE state */
	MASTER_SEND,	/*!< Master send state */
	MASTER_RECEIVE,	/*!< Master Receive state */
	SLAVE_SEND,		/*!< Slave send state */
	SLAVE_RECEIVE	/*!< Slave receive state */
} CHIP_I2C_MODE_T;

/**
 * LPC8xx I2C ROM driver APIs structure
 */
typedef struct  I2CD_API {
	/*!< Interrupt Support Routine */
	void (*i2c_isr_handler)(I2C_HANDLE_T *handle);

	/*!< MASTER functions */
	ErrorCode_t (*i2c_master_transmit_poll)(I2C_HANDLE_T *handle, I2C_PARAM_T *param, I2C_RESULT_T *result);
	ErrorCode_t (*i2c_master_receive_poll)(I2C_HANDLE_T *handle, I2C_PARAM_T *param, I2C_RESULT_T *result);
	ErrorCode_t (*i2c_master_tx_rx_poll)(I2C_HANDLE_T *handle, I2C_PARAM_T *param, I2C_RESULT_T *result);
	ErrorCode_t (*i2c_master_transmit_intr)(I2C_HANDLE_T *handle, I2C_PARAM_T *param, I2C_RESULT_T *result);
	ErrorCode_t (*i2c_master_receive_intr)(I2C_HANDLE_T *handle, I2C_PARAM_T *param, I2C_RESULT_T *result);
	ErrorCode_t (*i2c_master_tx_rx_intr)(I2C_HANDLE_T *handle, I2C_PARAM_T *param, I2C_RESULT_T *result);

	/*!< SLAVE functions */
	ErrorCode_t (*i2c_slave_receive_poll)(I2C_HANDLE_T *handle, I2C_PARAM_T *param, I2C_RESULT_T *result);
	ErrorCode_t (*i2c_slave_transmit_poll)(I2C_HANDLE_T *handle, I2C_PARAM_T *param, I2C_RESULT_T *result);
	ErrorCode_t (*i2c_slave_receive_intr)(I2C_HANDLE_T *handle, I2C_PARAM_T *param, I2C_RESULT_T *result);
	ErrorCode_t (*i2c_slave_transmit_intr)(I2C_HANDLE_T *handle, I2C_PARAM_T *param, I2C_RESULT_T *result);
	ErrorCode_t (*i2c_set_slave_addr)(I2C_HANDLE_T *handle, uint32_t slave_addr_0_3, uint32_t slave_mask_0_3);

	/*!< OTHER support functions */
	uint32_t        (*i2c_get_mem_size)(void);
	I2C_HANDLE_T *  (*i2c_setup)( uint32_t  i2c_base_addr, uint32_t * start_of_ram);
	ErrorCode_t     (*i2c_set_bitrate)(I2C_HANDLE_T *handle, uint32_t  p_clk_in_hz, uint32_t bitrate_in_bps);
	uint32_t        (*i2c_get_firmware_version)(void);
	CHIP_I2C_MODE_T (*i2c_get_status)(I2C_HANDLE_T *handle);
	ErrorCode_t     (*i2c_set_timeout)(I2C_HANDLE_T *handle, uint32_t timeout);
} I2CD_API_T;

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __ROM_I2C_8XX_H_ */
