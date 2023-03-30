/*
 * Copyright (c) 2023 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>

#include "cyw43_btbus.h"
#include "cyw43_ll.h"
#include "cyw43_config.h"
#include "cybt_shared_bus_driver.h"

#include "cyw43_btfw_43439.h"

#if CYW43_USE_HEX_BTFW
extern const char    brcm_patch_version[];
extern const uint8_t brcm_patchram_buf[];
extern const int     brcm_patch_ram_length;
#endif

#define  BTSDIO_FW_READY_POLLING_INTERVAL_MS   (1)
#define  BTSDIO_BT_AWAKE_POLLING_INTERVAL_MS   (1)

#define  BTSDIO_FW_READY_POLLING_RETRY_COUNT   (300)
#define  BTSDIO_FW_AWAKE_POLLING_RETRY_COUNT   (300)

#define  BTSDIO_FWBUF_OPER_DELAY_US            (250)
#define  BTFW_WAIT_TIME_MS                     (150)

#define CYBT_DEBUG 0
#define CYBT_VDEBUG 0

#if CYBT_DEBUG
#define cybt_debug(format,args...) printf("%d.%d: " format, (int)cyw43_hal_ticks_ms() / 1000, (int)cyw43_hal_ticks_ms() % 1000, ## args)
#else
#define cybt_debug(format, ...) ((void)0)
#endif
#define cybt_printf(format, args...) printf("%d.%d: " format, (int)cyw43_hal_ticks_ms() / 1000, (int)cyw43_hal_ticks_ms() % 1000, ## args)

#define ROUNDUP(x, a)               ((((x) + ((a) - 1)) / (a)) * (a))
#define ROUNDDN(x, a)               ((x) & ~((a) - 1))
#define ISALIGNED(a, x)             (((uint32_t)(a) & ((x) - 1)) == 0)

#define  CIRC_BUF_CNT(in, out)  (((in) - (out)) & ((BTSDIO_FWBUF_SIZE)-1))
#define  CIRC_BUF_SPACE(in, out)  CIRC_BUF_CNT((out), ((in) + 4))

typedef enum {
    HCI_PACKET_TYPE_IGNORE = 0x00,
    HCI_PACKET_TYPE_COMMAND = 0x01,
    HCI_PACKET_TYPE_ACL = 0x02,
    HCI_PACKET_TYPE_SCO = 0x03,
    HCI_PACKET_TYPE_EVENT = 0x04,
    HCI_PACKET_TYPE_DIAG = 0x07,
    HCI_PACKET_TYPE_LOOPBACK = 0xFF
} hci_packet_type_t;

static cybt_result_t cybt_fw_download_prepare(uint8_t **p_write_buf, uint8_t **p_hex_buf) {
    *p_write_buf = NULL;
    *p_hex_buf = NULL;

    *p_write_buf = malloc(BTFW_DOWNLOAD_BLK_SIZE + BTFW_SD_ALIGN);
    if (NULL == *p_write_buf) {
        return CYBT_ERR_OUT_OF_MEMORY;
    }

    *p_hex_buf = malloc(BTFW_MAX_STR_LEN);
    if (NULL == *p_hex_buf) {
        free(*p_write_buf);
        return CYBT_ERR_OUT_OF_MEMORY;
    }

    return CYBT_SUCCESS;
}

static cybt_result_t cybt_fw_download_finish(uint8_t *p_write_buf, uint8_t *p_hex_buf) {
    if (p_write_buf) {
        free(p_write_buf);
    }

    if (p_hex_buf) {
        free(p_hex_buf);
    }

    return CYBT_SUCCESS;
}

static cybt_result_t cybt_wait_bt_ready(uint32_t max_polling_times) {
    cyw43_delay_ms(BTFW_WAIT_TIME_MS);
    do {
        if (cybt_ready()) {
            return CYBT_SUCCESS;
        }
        cyw43_delay_ms(BTSDIO_FW_READY_POLLING_INTERVAL_MS);
    } while (max_polling_times--);
    return CYBT_ERR_TIMEOUT;
}

static cybt_result_t cybt_wait_bt_awake(uint32_t max_polling_times) {
    do {
        if (cybt_awake()) {
            return CYBT_SUCCESS;
        }
        cyw43_delay_ms(BTSDIO_BT_AWAKE_POLLING_INTERVAL_MS);
    } while (max_polling_times--);
    return CYBT_ERR_TIMEOUT;
}

int cyw43_btbus_init(cyw43_ll_t *self) {
    cybt_result_t ret;

    uint8_t *p_write_buf = NULL;
    uint8_t *p_hex_buf = NULL;

    cybt_sharedbus_driver_init(self);

    ret = cybt_fw_download_prepare(&p_write_buf, &p_hex_buf);
    if (CYBT_SUCCESS != ret) {
        cybt_printf("Could not allocate memory\n");
        return ret;
    }

    cybt_debug("cybt_fw_download\n");
    const uint8_t *fw_data_buf;
    uint32_t fw_data_len;
#if CYW43_USE_HEX_BTFW
    cybt_printf("CYW43_USE_HEX_BTFW is true\n");
#ifndef NDEBUG
    cybt_printf("BT FW download, version = %s\n", brcm_patch_version);
#endif
    fw_data_len = brcm_patch_ram_length;
    fw_data_buf = brcm_patchram_buf;
#else
    fw_data_len = cyw43_btfw_43439_len;
    fw_data_buf = cyw43_btfw_43439;
#endif
    ret = cybt_fw_download(fw_data_buf,
                           fw_data_len,
                           p_write_buf,
                           p_hex_buf
    );

    cybt_debug("cybt_fw_download_finish\n");
    cybt_fw_download_finish(p_write_buf, p_hex_buf);

    if (CYBT_SUCCESS != ret) {
        cybt_printf("hci_open(): FW download failed (0x%x)\n", ret);
        return CYBT_ERR_HCI_INIT_FAILED;
    }

    cybt_debug("// cybt_wait_bt_ready\n");
    ret = cybt_wait_bt_ready(BTSDIO_FW_READY_POLLING_RETRY_COUNT);
    assert(ret == CYBT_SUCCESS);
    if (CYBT_SUCCESS == ret) {
        cybt_debug("hci_open(): FW download successfully\n");
    } else {
        cybt_printf("hci_open(): Failed to download FW\n");
        return CYBT_ERR_HCI_INIT_FAILED;
    }

    ret = cybt_init_buffer();
    assert(ret == 0);
    if (ret != 0) {
        return ret;
    }
    ret = cybt_wait_bt_awake(BTSDIO_FW_AWAKE_POLLING_RETRY_COUNT);
    assert(ret == 0);
    if (ret != 0) {
        return ret;
    }

    cybt_set_host_ready();
    cybt_toggle_bt_intr();

    return CYBT_SUCCESS;
}

#if CYBT_VDEBUG
static void dump_bytes(const uint8_t *bptr, uint32_t len) {
    unsigned int i = 0;

    for (i = 0; i < len; i++) {
        if ((i & 0x07) == 0) {
            printf("\n        ");
        }
        printf("0x%02x", bptr[i]);
        if (i != (len-1)) {
            printf(", ");
        } else {
        }
    }
    printf("\n");
}
#endif

static cybt_result_t cybt_hci_write_buf(const uint8_t *p_data, uint32_t length) {
    cybt_result_t ret_result = CYBT_SUCCESS;
    cybt_fw_membuf_index_t fw_membuf_info = {0};

    assert(ISALIGNED(p_data, 4));
    if (!ISALIGNED(p_data, 4)) {
        cybt_printf("cybt_hci_write_hdr: buffer not aligned\n");
        return CYBT_ERR_BADARG;
    }

    // total length including header
    length = ROUNDUP(length, 4);
    cybt_get_bt_buf_index(&fw_membuf_info);
    uint32_t buf_space = CIRC_BUF_SPACE(fw_membuf_info.host2bt_in_val, fw_membuf_info.host2bt_out_val);
    assert(length <= buf_space); // queue full?
    if (length > buf_space) {
        return CYBT_ERR_QUEUE_FULL;
    }

    if (fw_membuf_info.host2bt_in_val + length <= BTSDIO_FWBUF_SIZE) {
        // Don't need to wrap circular buf
        cybt_debug("cybt_hci_write_hdr: 1-round write, len = %" PRId32 "\n", length);
        cybt_mem_write_idx(H2B_BUF_ADDR_IDX, fw_membuf_info.host2bt_in_val, p_data, length);
        fw_membuf_info.host2bt_in_val += length;
    } else {
        // Need to wrap circular buf
        uint32_t first_write_len = BTSDIO_FWBUF_SIZE - fw_membuf_info.host2bt_in_val;
        if (first_write_len >= 4) {
            cybt_mem_write_idx(H2B_BUF_ADDR_IDX, fw_membuf_info.host2bt_in_val, p_data, first_write_len);
            fw_membuf_info.host2bt_in_val += first_write_len;
        } else {
            first_write_len = 0;
        }
        uint32_t second_write_len = length - first_write_len;
        cybt_debug("cybt_hci_write_hdr: 2-round write, 1st_len = %" PRId32 ", 2nd_len = %" PRId32 "\n", first_write_len,
                   second_write_len);
        if (second_write_len > 0) {
            cybt_mem_write_idx(H2B_BUF_ADDR_IDX, 0, p_data + first_write_len, second_write_len);
            fw_membuf_info.host2bt_in_val += second_write_len;
        }
    }

    // Update circular buf pointer
    const uint32_t new_h2b_in_val = fw_membuf_info.host2bt_in_val & (BTSDIO_FWBUF_SIZE - 1);
    cybt_reg_write_idx(H2B_BUF_IN_ADDR_IDX, new_h2b_in_val);

    cybt_toggle_bt_intr();
    return ret_result;
}

static cybt_result_t cybt_hci_read(uint8_t *p_data, uint32_t *p_length) {
    cybt_result_t ret_result = CYBT_SUCCESS;
    uint32_t fw_b2h_buf_count;
    uint32_t new_b2h_out_val;
    cybt_fw_membuf_index_t fw_membuf_info = {0};
    static uint32_t available = 0;

    assert(ISALIGNED(p_data, 4));
    if (!ISALIGNED(p_data, 4)) {
        assert(false);
        cybt_printf("cybt_hci_read: buffer not aligned\n");
        return CYBT_ERR_BADARG;
    }

    uint32_t read_len = ROUNDUP(*p_length, 4);

    cybt_get_bt_buf_index(&fw_membuf_info);
    fw_b2h_buf_count = CIRC_BUF_CNT(fw_membuf_info.bt2host_in_val,
                                    fw_membuf_info.bt2host_out_val);
    cybt_debug("cybt_hci_read: bt2host_in_val=%lu bt2host_out_val=%lu fw_b2h_buf_count=%ld\n",
               fw_membuf_info.bt2host_in_val, fw_membuf_info.bt2host_out_val, fw_b2h_buf_count);
    if (fw_b2h_buf_count < available) {
        cybt_printf("error: cybt_hci_read buffer overflow fw_b2h_buf_count=%ld available=%lu\n", fw_b2h_buf_count,
                    available);
        cybt_printf("error: cybt_hci_read bt2host_in_val=%lu bt2host_out_val=%lu\n", fw_membuf_info.bt2host_in_val,
                    fw_membuf_info.bt2host_out_val);
        panic("cyw43 buffer overflow");
    }

    // No space in buffer
    if (fw_b2h_buf_count == 0) {
        *p_length = 0;
    } else {
        if (read_len > fw_b2h_buf_count) {
            read_len = fw_b2h_buf_count;
        }

        if (fw_membuf_info.bt2host_out_val + read_len <= BTSDIO_FWBUF_SIZE) {
            // Don't need to wrap the circular buf
            cybt_debug("cybt_hci_read: 1-round read, len = %" PRId32 "\n", read_len);
            cybt_mem_read_idx(B2H_BUF_ADDR_IDX, fw_membuf_info.bt2host_out_val, p_data, read_len);
            fw_membuf_info.bt2host_out_val += read_len;
        } else {
            // Need to wrap the circular buf
            uint32_t first_read_len = BTSDIO_FWBUF_SIZE - fw_membuf_info.bt2host_out_val;
            if (first_read_len >= 4) {
                cybt_mem_read_idx(B2H_BUF_ADDR_IDX, fw_membuf_info.bt2host_out_val, p_data, first_read_len);
                fw_membuf_info.bt2host_out_val += first_read_len;
            } else {
                first_read_len = 0;
            }
            uint32_t second_read_len = read_len - first_read_len;
            cybt_debug("cybt_hci_read: 2-round read, 1st_len = %" PRId32 ", 2nd_len = %" PRId32 "\n", first_read_len,
                       second_read_len);
            if (second_read_len > 0) {
                cybt_mem_read_idx(B2H_BUF_ADDR_IDX, 0, p_data + first_read_len, second_read_len);
                fw_membuf_info.bt2host_out_val += second_read_len;
            }
        }
        available = fw_b2h_buf_count - read_len; // remember amount available to check for buffer overflow

        // Update pointer
        new_b2h_out_val = fw_membuf_info.bt2host_out_val & (BTSDIO_FWBUF_SIZE - 1);
        cybt_debug("cybt_hci_read new b2h_out = %" PRId32 "\n", new_b2h_out_val);
        cybt_reg_write_idx(B2H_BUF_OUT_ADDR_IDX, new_b2h_out_val);

        // in case the real length is less than the requested one
        *p_length = read_len;
    }
    cybt_toggle_bt_intr();
    return ret_result;
}

static void cybt_bus_request(void) {
    CYW43_THREAD_ENTER
    // todo: Handle failure
    cybt_result_t err = cybt_set_bt_awake(true);
    assert(err == 0);
    err = cybt_wait_bt_awake(BTSDIO_FW_AWAKE_POLLING_RETRY_COUNT);
    assert(err == 0);
    (void) err;
}

static void cybt_bus_release(void) {
    // mutex if using wifi
    CYW43_THREAD_EXIT
}

// Send the buffer which includes space for a 4 byte header at the start
// The last byte of the header should already be set to the packet type
int cyw43_btbus_write(uint8_t *buf, uint32_t size) {
    uint16_t cmd_len = 0;

    // The size of the buffer should include a 4 byte header at the start
    cmd_len = size - 4; //in BTSDIO, cmd_len does not include header length

    // Create payload starting with required headers
    // Format: Cmd Len B0, Cmd Len B1, Cmd Len B2, HCI pckt type, Data
    buf[0] = (uint8_t) (cmd_len & 0xFF);
    buf[1] = (uint8_t) ((cmd_len & 0xFF00) >> 8);
    buf[2] = 0;

    cybt_bus_request();

    cybt_debug("cyw43_btbus_write: %d\n", cmd_len);
#if CYBT_VDEBUG
    dump_bytes(buf, size); // dump header and data
#endif

    cybt_hci_write_buf(buf, size);
    cybt_bus_release();

    return 0;
}

static bool cybt_hci_read_packet(uint8_t *buf, uint32_t max_buf_size, uint32_t *size) {
    uint32_t total_read_len = 0;
    uint32_t read_len = 0;
    cybt_result_t bt_result;

    // Read the header into the first 4 bytes of the buffer
    read_len = 4; //3 bytes BTSDIO packet length + 1 bytes PTI
    bt_result = cybt_hci_read(buf, &read_len);

    if (bt_result != CYBT_SUCCESS) {
        *size = 0;
        cybt_printf("cybt_hci_read_packet: error %d", bt_result);
        return true;
    }

    if (read_len == 0) {
        // No data is read from SPI
        *size = 0;
        cybt_debug("cybt_hci_read_packet: no data\n");
        return true;
    }

    uint32_t hci_read_len = ((buf[2] << 16) & 0xFFFF00) | ((buf[1] << 8) & 0xFF00) | (buf[0] & 0xFF);
    if (hci_read_len > max_buf_size - 4) {
        *size = 0;
        cybt_printf("cybt_hci_read_packet: too much data len %" PRId32"\n", hci_read_len);
        assert(false);
        return false;
    }
    total_read_len = hci_read_len;

    // Read the packet data after the header
    cybt_debug("cybt_hci_read_packet: packet type 0x%" PRIx8 " len %" PRId32 "\n", buf[3], hci_read_len);
    bt_result = cybt_hci_read(buf + 4, &total_read_len);
    if (bt_result != CYBT_SUCCESS) {
        *size = 0;
        cybt_printf("cybt_hci_read_packet: read failed\n");
        assert(false);
        return false;
    }

    // Might read more because of alignment
    if (total_read_len >= hci_read_len) {
        assert(total_read_len == ROUNDUP(hci_read_len, 4)); // check if we're losing data?
        *size = hci_read_len + 4;
    } else {
        assert(total_read_len > 0);
        *size = total_read_len + 4;
        cybt_printf("cybt_hci_read_packet: failed to read all data %lu < %lu\n", total_read_len, hci_read_len);
        //assert(false);
        return true;
    }

    cybt_debug("cybt_hci_read_packet: %ld\n", *size);
#if CYBT_VDEBUG
    dump_bytes(buf, *size);
#endif

    return true;
}

// Reads the hci packet prepended with 4 byte header. The last header byte is the packet type
int cyw43_btbus_read(uint8_t *buf, uint32_t max_buf_size, uint32_t *size) {
    cybt_bus_request();
    bool result = cybt_hci_read_packet(buf, max_buf_size, size);
    cybt_bus_release();
    return result ? 0 : -1;
}
