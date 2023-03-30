/*
 * Copyright (c) 2023 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <inttypes.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>

#include "cyw43_ll.h"
#include "cybt_shared_bus_driver.h"

// Bluetooth register corruption occurs if both wifi and bluetooth are fully utilised.
#define CYBT_CORRUPTION_TEST 1
#if CYBT_CORRUPTION_TEST
static cybt_fw_membuf_index_t last_buf_index;
static uint32_t last_host_ctrl_reg;
static uint32_t last_bt_ctrl_reg;

#include <stdio.h>

#endif

#ifndef NDEBUG
#define cybt_printf(format, args ...) printf(format,##args)
#else
#define cybt_printf(...)
#endif

#ifndef CYBT_DEBUG
#define CYBT_DEBUG 0
#endif

#if CYBT_DEBUG
#include <stdio.h>
#define cybt_debug(format, args ...) printf(format,##args)
#else
#define cybt_debug(format, ...) ((void)0)
#endif


/******************************************************************************
 *                                Constants
 ******************************************************************************/
#define BTFW_MEM_OFFSET             (0x19000000)

/* BIT0 => WLAN Power UP and BIT1=> WLAN Wake */
#define BT2WLAN_PWRUP_WAKE          (0x03)
#define BT2WLAN_PWRUP_ADDR          (0x640894)/* This address is specific to 43012B0 */

#define BTSDIO_OFFSET_HOST2BT_IN    (0x00002000)
#define BTSDIO_OFFSET_HOST2BT_OUT   (0x00002004)
#define BTSDIO_OFFSET_BT2HOST_IN    (0x00002008)
#define BTSDIO_OFFSET_BT2HOST_OUT   (0x0000200C)

#define H2B_BUF_ADDR                (buf_info.host2bt_buf_addr)
#define H2B_BUF_IN_ADDR             (buf_info.host2bt_in_addr)
#define H2B_BUF_OUT_ADDR            (buf_info.host2bt_out_addr)
#define B2H_BUF_ADDR                (buf_info.bt2host_buf_addr)
#define B2H_BUF_IN_ADDR             (buf_info.bt2host_in_addr)
#define B2H_BUF_OUT_ADDR            (buf_info.bt2host_out_addr)

static uint32_t wlan_ram_base_addr;
#define WLAN_RAM_BASE_ADDR            (wlan_ram_base_addr)

// In wifi host driver these are all constants
#define BT_CTRL_REG_ADDR            ((uint32_t)0x18000c7c)
#define HOST_CTRL_REG_ADDR          ((uint32_t)0x18000d6c)
#define WLAN_RAM_BASE_REG_ADDR      ((uint32_t)0x18000d68)

typedef struct
{
    uint32_t host2bt_buf_addr;
    uint32_t host2bt_in_addr;
    uint32_t host2bt_out_addr;
    uint32_t bt2host_buf_addr;
    uint32_t bt2host_in_addr;
    uint32_t bt2host_out_addr;
} cybt_fw_membuf_info_t;

cybt_fw_membuf_info_t buf_info;

#define BTFW_ADDR_MODE_UNKNOWN      (0)
#define BTFW_ADDR_MODE_EXTENDED     (1)
#define BTFW_ADDR_MODE_SEGMENT      (2)
#define BTFW_ADDR_MODE_LINEAR32     (3)

#define BTFW_HEX_LINE_TYPE_DATA                      (0)
#define BTFW_HEX_LINE_TYPE_END_OF_DATA               (1)
#define BTFW_HEX_LINE_TYPE_EXTENDED_SEGMENT_ADDRESS  (2)
#define BTFW_HEX_LINE_TYPE_EXTENDED_ADDRESS          (4)
#define BTFW_HEX_LINE_TYPE_ABSOLUTE_32BIT_ADDRESS    (5)

#define  BTSDIO_REG_DATA_VALID_BITMASK         (1 << 1)
#define  BTSDIO_REG_WAKE_BT_BITMASK            (1 << 17)
#define  BTSDIO_REG_SW_RDY_BITMASK             (1 << 24)

#define  BTSDIO_REG_BT_AWAKE_BITMASK           (1 << 8)
#define  BTSDIO_REG_FW_RDY_BITMASK             (1 << 24)

#define  BTSDIO_OFFSET_HOST_WRITE_BUF          (0)
#define  BTSDIO_OFFSET_HOST_READ_BUF           BTSDIO_FWBUF_SIZE

#define  BTSDIO_FWBUF_OPER_DELAY_US            (250)

#define ROUNDUP(x, a)               ((((x) + ((a) - 1)) / (a)) * (a))
#define ROUNDDN(x, a)               ((x) & ~((a) - 1))
#define ISALIGNED(a, x)             (((uint32_t)(a) & ((x) - 1)) == 0)

typedef struct cybt_fw_cb
{
    const uint8_t *p_fw_mem_start;
    uint32_t fw_len;
    const uint8_t *p_next_line_start;
} cybt_fw_cb_t;

typedef struct hex_file_data
{
    int addr_mode;
    uint16_t hi_addr;
    uint32_t dest_addr;
    uint8_t *p_ds;
} hex_file_data_t;

#if USE_SDIO
#define MAX_BLOCK_SIZE 16384
#else
#define MAX_BLOCK_SIZE 64
#endif

static cyw43_ll_t *cyw43_ll = NULL;

static cybt_result_t cybt_reg_write(uint32_t reg_addr, uint32_t value);
static cybt_result_t cybt_reg_read(uint32_t reg_addr, uint32_t *p_value);
static cybt_result_t cybt_mem_write(uint32_t mem_addr, const uint8_t *p_data, uint32_t data_len);
static cybt_result_t cybt_mem_read(uint32_t mem_addr, uint8_t *p_data, uint32_t data_len);

#if CYW43_USE_HEX_BTFW
const char *strnchr(const char *str, uint32_t len, int character) {
    const char *end = str + len;
    char c = (char)character;
    do {
        if (*str == c) {
            return str;
        }
    } while (++str <= end);
    return NULL;
}

static uint32_t cybt_fw_hex_read_line(cybt_fw_cb_t *p_btfw_cb,
    const char **p_line_start,
    int len
    ) {
    uint32_t str_len = 0;
    const char *p_str_end = NULL;

    if (NULL == p_btfw_cb || NULL == p_line_start) {
        return str_len;
    }

    *p_line_start = (const char *)p_btfw_cb->p_next_line_start;
    p_str_end = strnchr(*p_line_start, len, '\n');
    if (p_str_end == NULL) {
        return str_len;
    }

    str_len = (uint32_t)(p_str_end - *p_line_start);

    /* Advance file pointer past the string length */
    p_btfw_cb->p_next_line_start += str_len + 1;

    return str_len;
}

static inline uint8_t nibble_for_char(char c){
    if ((c >= '0') && (c <= '9')) return c - '0';
    if ((c >= 'A') && (c <= 'F')) return c - 'A' + 10;
    return -1;
}

static inline uint8_t read_hex_byte(const char *str) {
    return nibble_for_char(*str) << 4 | nibble_for_char(*(str + 1));
}

static uint32_t read_hex(const char *str, int nchars) {
    uint32_t result = 0;
    assert(nchars > 0 && nchars <= 8 && nchars % 2 == 0);
    for(int pos = 0; pos < nchars; pos += 2) {
        result <<= 8;
        result |= read_hex_byte(str + pos);
    }
    return result;
}

static uint32_t cybt_fw_get_data(cybt_fw_cb_t *p_btfw_cb,
    hex_file_data_t *hfd
    ) {
    uint32_t line_len;
    uint16_t num_bytes, addr, data_pos, type, idx, octet;
    uint32_t abs_base_addr32 = 0;
    uint32_t data_len = 0;
    const char *p_line_start = NULL;

    if (NULL == p_btfw_cb || NULL == hfd->p_ds) {
        return data_len;
    }

    while (data_len == 0) {
        line_len = cybt_fw_hex_read_line(p_btfw_cb, &p_line_start, BTFW_MAX_STR_LEN);
        if (line_len == 0) {
            break;
        } else if (line_len > 9) {

            num_bytes = (uint16_t)read_hex(p_line_start + 1, 2);
            assert(num_bytes * 2 + 8 + 2 + 1 == line_len);

            int addr32 = read_hex(p_line_start + 3, 4);
            assert(addr32 <= 0xffff);
            addr = (uint16_t)addr32;
            type = (uint16_t)read_hex(p_line_start + 7, 2);
            assert(type <= 0xff);

            data_pos = 9;

            for (idx = 0; idx < num_bytes; idx++)
            {
                octet = (uint16_t)read_hex(p_line_start + data_pos, 2);
                hfd->p_ds[idx] = (uint8_t)(octet & 0x00FF);
                data_pos += 2;
            }

            if (type == BTFW_HEX_LINE_TYPE_EXTENDED_ADDRESS) {
                hfd->hi_addr = (hfd->p_ds[0] << 8) | hfd->p_ds[1];
                hfd->addr_mode = BTFW_ADDR_MODE_EXTENDED;
            } else if (type == BTFW_HEX_LINE_TYPE_EXTENDED_SEGMENT_ADDRESS) {
                hfd->hi_addr = (hfd->p_ds[0] << 8) | hfd->p_ds[1];
                hfd->addr_mode = BTFW_ADDR_MODE_SEGMENT;
            } else if (type == BTFW_HEX_LINE_TYPE_ABSOLUTE_32BIT_ADDRESS) {
                abs_base_addr32 = (hfd->p_ds[0] << 24) | (hfd->p_ds[1] << 16) |
                    (hfd->p_ds[2] << 8) | hfd->p_ds[3];
                hfd->addr_mode = BTFW_ADDR_MODE_LINEAR32;
            } else if (type == BTFW_HEX_LINE_TYPE_DATA) {
                hfd->dest_addr = addr;

                if (hfd->addr_mode == BTFW_ADDR_MODE_EXTENDED) {
                    hfd->dest_addr += (hfd->hi_addr << 16);
                } else if (hfd->addr_mode == BTFW_ADDR_MODE_SEGMENT) {
                    hfd->dest_addr += (hfd->hi_addr << 4);
                } else if (hfd->addr_mode == BTFW_ADDR_MODE_LINEAR32) {
                    hfd->dest_addr += abs_base_addr32;
                }

                data_len = num_bytes;
            }
        }
    }

    return data_len;
}
#else

static uint32_t cybt_fw_get_data(cybt_fw_cb_t *p_btfw_cb, hex_file_data_t *hfd) {
    uint32_t abs_base_addr32 = 0;
    while (true) {
        // 4 byte header
        uint8_t num_bytes = *(p_btfw_cb->p_next_line_start)++;
        uint16_t addr = *(p_btfw_cb->p_next_line_start)++ << 8;
        addr |= *(p_btfw_cb->p_next_line_start)++;
        uint8_t type = *(p_btfw_cb->p_next_line_start)++;

        // No data?
        if (num_bytes == 0) break;

        // Copy the data
        memcpy(hfd->p_ds, p_btfw_cb->p_next_line_start, num_bytes);
        p_btfw_cb->p_next_line_start += num_bytes;

        // Adjust address based on type
        if (type == BTFW_HEX_LINE_TYPE_EXTENDED_ADDRESS) {
            hfd->hi_addr = (hfd->p_ds[0] << 8) | hfd->p_ds[1];
            hfd->addr_mode = BTFW_ADDR_MODE_EXTENDED;
        } else if (type == BTFW_HEX_LINE_TYPE_EXTENDED_SEGMENT_ADDRESS) {
            hfd->hi_addr = (hfd->p_ds[0] << 8) | hfd->p_ds[1];
            hfd->addr_mode = BTFW_ADDR_MODE_SEGMENT;
        } else if (type == BTFW_HEX_LINE_TYPE_ABSOLUTE_32BIT_ADDRESS) {
            abs_base_addr32 = (hfd->p_ds[0] << 24) | (hfd->p_ds[1] << 16) |
                              (hfd->p_ds[2] << 8) | hfd->p_ds[3];
            hfd->addr_mode = BTFW_ADDR_MODE_LINEAR32;
        } else if (type == BTFW_HEX_LINE_TYPE_DATA) {
            hfd->dest_addr = addr;
            if (hfd->addr_mode == BTFW_ADDR_MODE_EXTENDED) {
                hfd->dest_addr += (hfd->hi_addr << 16);
            } else if (hfd->addr_mode == BTFW_ADDR_MODE_SEGMENT) {
                hfd->dest_addr += (hfd->hi_addr << 4);
            } else if (hfd->addr_mode == BTFW_ADDR_MODE_LINEAR32) {
                hfd->dest_addr += abs_base_addr32;
            }
            return num_bytes;
        }
    }
    return 0;
}

#endif

cybt_result_t cybt_fw_download(const uint8_t *p_bt_firmware,
                               uint32_t bt_firmware_len,
                               uint8_t *p_write_buf,
                               uint8_t *p_hex_buf) {
    cybt_fw_cb_t btfw_cb;
    hex_file_data_t hfd = {BTFW_ADDR_MODE_EXTENDED, 0, 0, NULL};
    uint8_t *p_mem_ptr;
    uint32_t data_len;

    if (cyw43_ll == NULL) {
        return CYBT_ERR_BADARG;
    }

    if (NULL == p_bt_firmware || 0 == bt_firmware_len || NULL == p_write_buf || NULL == p_hex_buf) {
        return CYBT_ERR_BADARG;
    }

    // BT firmware starts with length of version string including a null terminator
#if !CYW43_USE_HEX_BTFW
    uint8_t version_len = *p_bt_firmware;
    assert(*(p_bt_firmware + version_len) == 0);
#ifndef NDEBUG
    cybt_printf("BT FW download, version = %s\n", p_bt_firmware + 1);
#endif
    p_bt_firmware += version_len + 1; // skip over version
    p_bt_firmware += 1; // skip over record count
#endif

    p_mem_ptr = p_write_buf;
    if ((uint32_t) (uintptr_t) p_mem_ptr % BTFW_SD_ALIGN) {
        p_mem_ptr += (BTFW_SD_ALIGN - ((uint32_t) (uintptr_t) p_mem_ptr % BTFW_SD_ALIGN));
    }

    hfd.p_ds = p_hex_buf;

    btfw_cb.p_fw_mem_start = p_bt_firmware;
    btfw_cb.fw_len = bt_firmware_len;
    btfw_cb.p_next_line_start = p_bt_firmware;

    cybt_reg_write(BTFW_MEM_OFFSET + BT2WLAN_PWRUP_ADDR, BT2WLAN_PWRUP_WAKE);

    while ((data_len = cybt_fw_get_data(&btfw_cb, &hfd)) > 0) {
        uint32_t fwmem_start_addr, fwmem_start_data, fwmem_end_addr, fwmem_end_data;
        uint32_t write_data_len, idx, pad;

        fwmem_start_addr = BTFW_MEM_OFFSET + hfd.dest_addr;
        write_data_len = 0;

        /**
         * Make sure the start address is 4 byte aligned to avoid alignment issues
         * with SD host controllers
         */
        if (!ISALIGNED(fwmem_start_addr, 4)) {
            pad = fwmem_start_addr % 4;
            fwmem_start_addr = ROUNDDN(fwmem_start_addr, 4);

            cybt_mem_read(fwmem_start_addr, (uint8_t *) &fwmem_start_data, sizeof(uint32_t));

            for (idx = 0; idx < pad; idx++, write_data_len++) {
                p_mem_ptr[write_data_len] = (uint8_t) ((uint8_t *) &fwmem_start_data)[idx];
            }
        }
        memcpy(&(p_mem_ptr[write_data_len]), hfd.p_ds, data_len);
        write_data_len += data_len;

        /**
         * Make sure the length is multiple of 4bytes to avoid alignment issues
         * with SD host controllers
         */
        fwmem_end_addr = fwmem_start_addr + write_data_len;
        if (!ISALIGNED(fwmem_end_addr, 4)) {
            cybt_mem_read(ROUNDDN(fwmem_end_addr, 4), (uint8_t *) &fwmem_end_data, sizeof(uint32_t));
            for (idx = (fwmem_end_addr % 4); idx < 4; idx++, write_data_len++) {
                p_mem_ptr[write_data_len] = (uint8_t) ((uint8_t *) &fwmem_end_data)[idx];
            }
        }

        /*
         *  write ram
         */
        if (((fwmem_start_addr & 0xFFF) + write_data_len) <= 0x1000) {
            cybt_mem_write(fwmem_start_addr, p_mem_ptr, write_data_len);
        } else {
            uint32_t first_write_len = 0x1000 - (fwmem_start_addr & 0xFFF);
            cybt_mem_write(fwmem_start_addr, p_mem_ptr, first_write_len);
            cybt_mem_write(fwmem_start_addr + first_write_len,
                           p_mem_ptr + first_write_len,
                           write_data_len - first_write_len);
        }
    }

    return CYBT_SUCCESS;
}

cybt_result_t cybt_set_host_ready(void) {
    uint32_t reg_val;

    cybt_reg_read(HOST_CTRL_REG_ADDR, &reg_val);
    reg_val |= BTSDIO_REG_SW_RDY_BITMASK;
    cybt_reg_write(HOST_CTRL_REG_ADDR, reg_val);
#if CYBT_CORRUPTION_TEST
    last_host_ctrl_reg = reg_val;
#endif
    return CYBT_SUCCESS;
}

cybt_result_t cybt_toggle_bt_intr(void) {
    uint32_t reg_val, new_val;

    cybt_reg_read(HOST_CTRL_REG_ADDR, &reg_val);
#if CYBT_CORRUPTION_TEST
    if ((reg_val & ~(BTSDIO_REG_SW_RDY_BITMASK | BTSDIO_REG_WAKE_BT_BITMASK | BTSDIO_REG_DATA_VALID_BITMASK)) != 0) {
        cybt_printf("cybt_toggle_bt_intr read HOST_CTRL_REG_ADDR as 0x%08lx\n", reg_val);
        cybt_debug_dump();
        panic("cyw43 btsdio register corruption");
    }
    assert((reg_val & ~(BTSDIO_REG_SW_RDY_BITMASK | BTSDIO_REG_WAKE_BT_BITMASK | BTSDIO_REG_DATA_VALID_BITMASK)) == 0);
#endif
    new_val = reg_val ^ BTSDIO_REG_DATA_VALID_BITMASK;
    cybt_reg_write(HOST_CTRL_REG_ADDR, new_val);
#if CYBT_CORRUPTION_TEST
    last_host_ctrl_reg = new_val;
#endif
    return CYBT_SUCCESS;
}

cybt_result_t cybt_set_bt_intr(int value) {
    uint32_t reg_val, new_val;

    cybt_reg_read(HOST_CTRL_REG_ADDR, &reg_val);
    if (value) {
        new_val = reg_val | BTSDIO_REG_DATA_VALID_BITMASK;
    } else {
        new_val = reg_val & ~BTSDIO_REG_DATA_VALID_BITMASK;
    }
    cybt_reg_write(HOST_CTRL_REG_ADDR, new_val);
#if CYBT_CORRUPTION_TEST
    last_host_ctrl_reg = new_val;
#endif
    return CYBT_SUCCESS;
}

int cybt_ready(void) {
    uint32_t reg_val;
    cybt_reg_read(BT_CTRL_REG_ADDR, &reg_val);
#if CYBT_CORRUPTION_TEST
    if (reg_val & BTSDIO_REG_FW_RDY_BITMASK) {
        last_bt_ctrl_reg = reg_val;
    }
#endif
    return (reg_val & BTSDIO_REG_FW_RDY_BITMASK) ? 1 : 0;
}

int cybt_awake(void) {
    uint32_t reg_val;
    cybt_reg_read(BT_CTRL_REG_ADDR, &reg_val);
#if CYBT_CORRUPTION_TEST
    if (reg_val & BTSDIO_REG_BT_AWAKE_BITMASK) {
        last_bt_ctrl_reg = reg_val;
    }
#endif
    return (reg_val & BTSDIO_REG_BT_AWAKE_BITMASK) ? 1 : 0;
}

cybt_result_t cybt_set_bt_awake(int value) {
    uint32_t reg_val_before;
    cybt_reg_read(HOST_CTRL_REG_ADDR, &reg_val_before);

    uint32_t reg_val_after = reg_val_before;
    if (value)
        reg_val_after |= BTSDIO_REG_WAKE_BT_BITMASK;
    else
        reg_val_after &= ~BTSDIO_REG_WAKE_BT_BITMASK;

    if (reg_val_before != reg_val_after) {
        cybt_reg_write(HOST_CTRL_REG_ADDR, reg_val_after);
#if CYBT_CORRUPTION_TEST
        last_host_ctrl_reg = reg_val_after;
#endif
    }
    return 0;
}

void cybt_debug_dump(void) {
#if CYBT_CORRUPTION_TEST
    uint32_t reg_val = 0;
    cybt_fw_membuf_index_t buf_index;

    cybt_printf("WLAN_RAM_BASE_ADDR: 0x%08lx\n", WLAN_RAM_BASE_ADDR);
    cybt_printf("H2B_BUF_ADDR: 0x%08lx\n", H2B_BUF_ADDR);
    cybt_printf("B2H_BUF_ADDR: 0x%08lx\n", B2H_BUF_ADDR);

    cybt_reg_read(H2B_BUF_IN_ADDR, &buf_index.host2bt_in_val);
    cybt_printf("H2B_BUF_IN_ADDR: 0x%08lx = 0x%08lx (last 0x%08lx)\n", H2B_BUF_IN_ADDR, buf_index.host2bt_in_val,
                last_buf_index.host2bt_in_val);

    cybt_reg_read(H2B_BUF_OUT_ADDR, &buf_index.host2bt_out_val);
    cybt_printf("H2B_BUF_OUT_ADDR: 0x%08lx = 0x%08lx (last 0x%08lx)\n", H2B_BUF_OUT_ADDR, buf_index.host2bt_out_val,
                last_buf_index.host2bt_out_val);

    cybt_reg_read(B2H_BUF_IN_ADDR, &buf_index.bt2host_in_val);
    cybt_printf("B2H_BUF_IN_ADDR: 0x%08lx = 0x%08lx (last 0x%08lx)\n", B2H_BUF_IN_ADDR, buf_index.bt2host_in_val,
                last_buf_index.bt2host_in_val);

    cybt_reg_read(B2H_BUF_OUT_ADDR, &buf_index.bt2host_out_val);
    cybt_printf("B2H_BUF_OUT_ADDR: 0x%08lx = 0x%08lx (last 0x%08lx)\n", B2H_BUF_OUT_ADDR, buf_index.bt2host_out_val,
                last_buf_index.bt2host_out_val);

    cybt_reg_read(HOST_CTRL_REG_ADDR, &reg_val);
    cybt_printf("HOST_CTRL_REG_ADDR: 0x%08lx = 0x%08lx (last 0x%08lx)\n", HOST_CTRL_REG_ADDR, reg_val,
                last_host_ctrl_reg);

    cybt_reg_read(BT_CTRL_REG_ADDR, &reg_val);
    cybt_printf("BT_CTRL_REG_ADDR: 0x%08lx = 0x%08lx (last 0x%08lx)\n", BT_CTRL_REG_ADDR, reg_val, last_bt_ctrl_reg);
#endif
}

cybt_result_t cybt_get_bt_buf_index(cybt_fw_membuf_index_t *p_buf_index) {
    uint32_t buf[4];

    cybt_mem_read(H2B_BUF_IN_ADDR, (uint8_t *) buf, sizeof(buf));

    p_buf_index->host2bt_in_val = buf[0];
    p_buf_index->host2bt_out_val = buf[1];
    p_buf_index->bt2host_in_val = buf[2];
    p_buf_index->bt2host_out_val = buf[3];

    cybt_debug("cybt_get_bt_buf_index: h2b_in = 0x%08lx, h2b_out = 0x%08lx, b2h_in = 0x%08lx, b2h_out = 0x%08lx\n",
               p_buf_index->host2bt_in_val,
               p_buf_index->host2bt_out_val,
               p_buf_index->bt2host_in_val,
               p_buf_index->bt2host_out_val);

#if CYBT_CORRUPTION_TEST
    if (p_buf_index->host2bt_in_val >= BTSDIO_FWBUF_SIZE || p_buf_index->host2bt_out_val >= BTSDIO_FWBUF_SIZE ||
        p_buf_index->bt2host_in_val >= BTSDIO_FWBUF_SIZE || p_buf_index->bt2host_out_val >= BTSDIO_FWBUF_SIZE) {
        cybt_printf("cybt_get_bt_buf_index invalid buffer value\n");
        cybt_debug_dump();
    } else {
        memcpy((uint8_t *) &last_buf_index, (uint8_t *) p_buf_index, sizeof(cybt_fw_membuf_index_t));
    }
#endif

    assert(p_buf_index->host2bt_in_val < BTSDIO_FWBUF_SIZE);
    assert(p_buf_index->host2bt_out_val < BTSDIO_FWBUF_SIZE);
    assert(p_buf_index->bt2host_in_val < BTSDIO_FWBUF_SIZE);
    assert(p_buf_index->bt2host_out_val < BTSDIO_FWBUF_SIZE);

    return CYBT_SUCCESS;
}

static cybt_result_t cybt_reg_write(uint32_t reg_addr, uint32_t value) {
    cybt_debug("cybt_reg_write 0x%08lx 0x%08lx\n", reg_addr, value);
    cyw43_ll_write_backplane_reg(cyw43_ll, reg_addr, value);
    return CYBT_SUCCESS;
}

static cybt_result_t cybt_reg_read(uint32_t reg_addr, uint32_t *p_value) {
    *p_value = cyw43_ll_read_backplane_reg(cyw43_ll, reg_addr);
    cybt_debug("cybt_reg_read 0x%08lx == 0x%08lx\n", reg_addr, *p_value);
    return CYBT_SUCCESS;
}

#if CYBT_DEBUG
static void dump_bytes(const uint8_t *bptr, uint32_t len) {
    unsigned int i = 0;

    for (i = 0; i < len; i++) {
        if ((i & 0x07) == 0) {
            cybt_debug("\n        ");
        }
        cybt_debug("0x%02x", bptr[i]);
        if (i != (len - 1)) {
            cybt_debug(", ");
        } else {
        }
    }
    cybt_debug("\n");
}
#define DUMP_BYTES dump_bytes
#else
#define DUMP_BYTES(...)
#endif

static cybt_result_t cybt_mem_write(uint32_t mem_addr, const uint8_t *p_data, uint32_t data_len) {
    cybt_debug("cybt_mem_write addr 0x%08lx len %ld\n", mem_addr, data_len);
    do {
        uint32_t transfer_size = (data_len > MAX_BLOCK_SIZE) ? MAX_BLOCK_SIZE : data_len;
        cyw43_ll_write_backplane_mem(cyw43_ll, mem_addr, transfer_size, p_data);
        cybt_debug("  write_mem addr 0x%08lx len %ld\n", mem_addr, transfer_size);
        DUMP_BYTES(p_data, transfer_size);
        data_len -= transfer_size;
        p_data += transfer_size;
        mem_addr += transfer_size;
    } while (data_len > 0);
    return CYBT_SUCCESS;
}

static cybt_result_t cybt_mem_read(uint32_t mem_addr, uint8_t *p_data, uint32_t data_len) {
    assert(data_len >= 4);
    cybt_debug("cybt_mem_read addr 0x%08lx len %ld\n", mem_addr, data_len);
    do {
        uint32_t transfer_size = (data_len > MAX_BLOCK_SIZE) ? MAX_BLOCK_SIZE : data_len;
        /* this limitation from BT, we need to read twice when spi clock setting is more than 25MHz */
        cyw43_ll_read_backplane_mem(cyw43_ll, mem_addr, transfer_size, p_data);
        cybt_debug("  read_mem addr 0x%08lx len %ld\n", transfer_size, mem_addr);
        DUMP_BYTES(p_data, transfer_size);
        data_len -= transfer_size;
        p_data += transfer_size;
        mem_addr += transfer_size;
    } while (data_len > 0);
    return CYBT_SUCCESS;
}

static uint32_t cybt_get_addr(cybt_addr_idx_t addr_idx) {
    uint32_t addr = 0;

    switch (addr_idx) {
        case H2B_BUF_ADDR_IDX:
            addr = H2B_BUF_ADDR;
            break;
        case H2B_BUF_IN_ADDR_IDX:
            addr = H2B_BUF_IN_ADDR;
            break;
        case H2B_BUF_OUT_ADDR_IDX:
            addr = H2B_BUF_OUT_ADDR;
            break;
        case B2H_BUF_ADDR_IDX:
            addr = B2H_BUF_ADDR;
            break;
        case B2H_BUF_IN_ADDR_IDX:
            addr = B2H_BUF_IN_ADDR;
            break;
        case B2H_BUF_OUT_ADDR_IDX:
            addr = B2H_BUF_OUT_ADDR;
            break;
        default:
            assert(0);
            break;
    }

    return addr;
}

cybt_result_t cybt_reg_write_idx(cybt_addr_idx_t reg_idx, uint32_t value) {
    assert(reg_idx == H2B_BUF_IN_ADDR_IDX || reg_idx == B2H_BUF_OUT_ADDR_IDX);
    assert(value < BTSDIO_FWBUF_SIZE); // writing out of bounds register value?
    if ((reg_idx != H2B_BUF_IN_ADDR_IDX && reg_idx != B2H_BUF_OUT_ADDR_IDX) || value >= BTSDIO_FWBUF_SIZE) {
        assert(0);
        return CYBT_ERR_BADARG;
    }
    uint32_t reg_addr = cybt_get_addr(reg_idx);
    return cybt_reg_write(reg_addr, value);
}

cybt_result_t cybt_mem_write_idx(cybt_addr_idx_t mem_idx, uint32_t offset, const uint8_t *p_data, uint32_t data_len) {
    assert(mem_idx == H2B_BUF_ADDR_IDX); // caller should only be writing to here?
    assert(offset + data_len <= BTSDIO_FWBUF_SIZE); // writing out of bounds?
    if (mem_idx != H2B_BUF_ADDR_IDX || (offset + data_len) > BTSDIO_FWBUF_SIZE) {
        assert(0);
        return CYBT_ERR_BADARG;
    }
    if (!ISALIGNED(p_data, 4)) {
        return CYBT_ERR_BADARG;
    }
    uint32_t mem_addr = cybt_get_addr(mem_idx) + offset;
    return cybt_mem_write(mem_addr, p_data, data_len);
}

cybt_result_t cybt_mem_read_idx(cybt_addr_idx_t mem_idx, uint32_t offset, uint8_t *p_data, uint32_t data_len) {
    assert(mem_idx == B2H_BUF_ADDR_IDX); // caller should only be reading from here?
    assert(offset + data_len <= BTSDIO_FWBUF_SIZE); // reading out of bounds?
    if (mem_idx != B2H_BUF_ADDR_IDX || (offset + data_len) > BTSDIO_FWBUF_SIZE) {
        assert(0);
        return CYBT_ERR_BADARG;
    }
    uint32_t mem_addr = cybt_get_addr(mem_idx) + offset;
    return cybt_mem_read(mem_addr, p_data, data_len);
}

cybt_result_t cybt_init_buffer(void) {
    int result;
    result = cybt_reg_read(WLAN_RAM_BASE_REG_ADDR, &WLAN_RAM_BASE_ADDR);
    if (CYBT_SUCCESS != result) {
        return result;
    }

    cybt_debug("hci_open(): btfw ram base = 0x%" PRIx32 "\n", WLAN_RAM_BASE_ADDR);

    // Fill in reg info
    // Data buffers
    H2B_BUF_ADDR = WLAN_RAM_BASE_ADDR + BTSDIO_OFFSET_HOST_WRITE_BUF;
    B2H_BUF_ADDR = WLAN_RAM_BASE_ADDR + BTSDIO_OFFSET_HOST_READ_BUF;

    // circular buffer indexes
    H2B_BUF_IN_ADDR = WLAN_RAM_BASE_ADDR + BTSDIO_OFFSET_HOST2BT_IN;
    H2B_BUF_OUT_ADDR = WLAN_RAM_BASE_ADDR + BTSDIO_OFFSET_HOST2BT_OUT;
    B2H_BUF_IN_ADDR = WLAN_RAM_BASE_ADDR + BTSDIO_OFFSET_BT2HOST_IN;
    B2H_BUF_OUT_ADDR = WLAN_RAM_BASE_ADDR + BTSDIO_OFFSET_BT2HOST_OUT;

    uint32_t reg_val = 0;
    cybt_reg_write(H2B_BUF_IN_ADDR, reg_val);
    cybt_reg_write(H2B_BUF_OUT_ADDR, reg_val);
    cybt_reg_write(B2H_BUF_IN_ADDR, reg_val);
    cybt_reg_write(B2H_BUF_OUT_ADDR, reg_val);

    return CYBT_SUCCESS;
}

void cybt_sharedbus_driver_init(cyw43_ll_t *driver) {
    cyw43_ll = driver;
}
