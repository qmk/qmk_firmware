/*
 * Copyright (c) 2023 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef CYBT_SHARE_BUS_DRIVER_H
#define CYBT_SHARE_BUS_DRIVER_H

#define BTSDIO_FWBUF_SIZE                     (0x1000)
#define BTFW_MAX_STR_LEN            (600)
#define BTFW_SD_ALIGN               (32)
#define BTFW_DOWNLOAD_BLK_SIZE      (((BTFW_MAX_STR_LEN) / 2) + 8)

typedef enum {
    CYBT_SUCCESS = 0,
    CYBT_ERR_BADARG = 0xB1,
    CYBT_ERR_OUT_OF_MEMORY,
    CYBT_ERR_TIMEOUT,
    CYBT_ERR_HCI_INIT_FAILED,
    CYBT_ERR_HCI_UNSUPPORTED_IF,
    CYBT_ERR_HCI_UNSUPPORTED_BAUDRATE,
    CYBT_ERR_HCI_NOT_INITIALIZE,
    CYBT_ERR_HCI_WRITE_FAILED,
    CYBT_ERR_HCI_READ_FAILED,
    CYBT_ERR_HCI_GET_TX_MUTEX_FAILED,
    CYBT_ERR_HCI_GET_RX_MUTEX_FAILED,
    CYBT_ERR_HCI_SET_BAUDRATE_FAILED,
    CYBT_ERR_HCI_SET_FLOW_CTRL_FAILED,
    CYBT_ERR_INIT_MEMPOOL_FAILED,
    CYBT_ERR_INIT_QUEUE_FAILED,
    CYBT_ERR_CREATE_TASK_FAILED,
    CYBT_ERR_SEND_QUEUE_FAILED,
    CYBT_ERR_MEMPOOL_NOT_INITIALIZE,
    CYBT_ERR_QUEUE_ALMOST_FULL,
    CYBT_ERR_QUEUE_FULL,
    CYBT_ERR_GPIO_POWER_INIT_FAILED,
    CYBT_ERR_GPIO_DEV_WAKE_INIT_FAILED,
    CYBT_ERR_GPIO_HOST_WAKE_INIT_FAILED,
    CYBT_ERR_GENERIC
} cybt_result_t;

typedef enum {
    H2B_BUF_ADDR_IDX       = 0x10,
    H2B_BUF_IN_ADDR_IDX,
    H2B_BUF_OUT_ADDR_IDX,
    B2H_BUF_ADDR_IDX,
    B2H_BUF_IN_ADDR_IDX,
    B2H_BUF_OUT_ADDR_IDX,
} cybt_addr_idx_t;

typedef struct {
    uint32_t host2bt_in_val;
    uint32_t host2bt_out_val;
    uint32_t bt2host_in_val;
    uint32_t bt2host_out_val;
} cybt_fw_membuf_index_t;

struct _cyw43_ll_t;
void cybt_sharedbus_driver_init(struct _cyw43_ll_t *driver);

cybt_result_t cybt_init_buffer(void);

cybt_result_t cybt_reg_write_idx(cybt_addr_idx_t reg_idx, uint32_t value);
cybt_result_t cybt_mem_write_idx(cybt_addr_idx_t mem_idx, uint32_t offset, const uint8_t *p_data, uint32_t data_len);
cybt_result_t cybt_mem_read_idx(cybt_addr_idx_t mem_idx, uint32_t offset, uint8_t *p_data, uint32_t data_len);

cybt_result_t cybt_fw_download(const uint8_t *p_bt_firmware, uint32_t bt_firmware_len, uint8_t *p_write_buf, uint8_t *p_hex_buf);

int cybt_ready(void);
int cybt_awake(void);

cybt_result_t cybt_set_bt_awake(int value);
cybt_result_t cybt_set_host_ready(void);
cybt_result_t cybt_set_bt_intr(int value);
cybt_result_t cybt_toggle_bt_intr(void);
cybt_result_t cybt_get_bt_buf_index(cybt_fw_membuf_index_t *p_buf_index);

void cybt_debug_dump(void);

#endif
