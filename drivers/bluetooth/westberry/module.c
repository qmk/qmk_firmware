// Copyright 2025 emolitor (github.com/emolitor)
// Copyright 2024 Su (@isuua)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "module.h"
#include "smsg.h"
#include "uart.h"

#ifndef MD_BAUD_RATE
#    define MD_BAUD_RATE 115200
#endif

#ifndef MD_SEND_PKT_TIMEOUT
#    define MD_SEND_PKT_TIMEOUT 10
#endif

#ifndef MD_SEND_PKT_RETRY
#    define MD_SEND_PKT_RETRY 40
#endif

#ifndef MD_SEND_PKT_PAYLOAD_MAX
#    define MD_SEND_PKT_PAYLOAD_MAX ((MD_RAW_SIZE) + 4)
#endif

#ifndef MD_RAW_SIZE
#    define MD_RAW_SIZE 32
#endif

typedef struct {
    uint8_t state;
    uint8_t indicator;
    uint8_t version;
    uint8_t bat;
} md_info_t;

static uint8_t md_rev_payload[MD_SEND_PKT_PAYLOAD_MAX] = {0};
static uint8_t md_raw_payload[MD_RAW_SIZE]             = {0};

static md_info_t md_info = {
    .bat       = 100,
    .indicator = 0,
    .version   = 0,
    .state     = MD_STATE_NONE,
};

static void md_send_ack(void) {
    uint8_t sdata[0x03] = {0x61, 0x0D, 0x0A};
    uart_transmit(sdata, sizeof(sdata));
}

static bool md_check_sum(const uint8_t *data, uint32_t length) {
    uint8_t sum = 0;

    for (uint32_t i = 0; i < (length - 1); i++) {
        sum += data[i];
    }

    return sum == data[length - 1];
}

static void md_calc_check_sum(uint8_t *data, uint32_t length) {
    uint8_t sum = 0;

    for (uint32_t i = 0; i < length; i++) {
        sum += data[i];
    }

    data[length] = sum;
}

bool md_receive_process_user(uint8_t *pdata, uint8_t len) __attribute__((weak));
bool md_receive_process_user(uint8_t *pdata, uint8_t len) {
    return true;
}

bool md_receive_process_kb(uint8_t *pdata, uint8_t len) __attribute__((weak));
bool md_receive_process_kb(uint8_t *pdata, uint8_t len) {
    return md_receive_process_user(pdata, len);
}

void md_receive_raw_cb(uint8_t *pdata, uint8_t len) __attribute__((weak));
void md_receive_raw_cb(uint8_t *pdata, uint8_t len) {}

void md_receive_host_cb(bool resume) __attribute__((weak));
void md_receive_host_cb(bool resume) {}

static void md_receive_msg_task(void) {
    static uint32_t data_count  = 0x00;
    static uint8_t  data_remain = 0x00;

    while (uart_available()) {
        uint8_t data = uart_read();

        switch (data_count) {
            case 0: { // cmd
                switch (data) {
                    case MD_REV_CMD_RAW:
                    case MD_REV_CMD_INDICATOR:
                    case MD_REV_CMD_DEVCTRL:
                    case MD_REV_CMD_BATVOL:
                    case MD_REV_CMD_MD_FW_VERSION:
                    case MD_REV_CMD_HOST_STATE:
                    case 0x61: {
                        md_rev_payload[data_count++] = data;
                        data_remain                  = 2;
                    } break;
                    default: {
                        data_count = 0;
                    } break;
                }
                continue;
            } break;
            case 1: {
                md_rev_payload[data_count++] = data;
                data_remain--;
                continue;
            } break;
            case 2: {
                // ACK
                if ((md_rev_payload[0] == 0x61) && (md_rev_payload[1] == 0x0D) && (data == 0x0A)) {
                    if (smsg_get_state() == smsg_state_busy) {
                        smsg_set_state(smsg_state_replied);
                    }
                    data_count = 0;
                    return;
                }

                // raw data
                if ((md_rev_payload[0] == MD_REV_CMD_RAW) && (md_rev_payload[1] == MD_REV_CMD_RAW_OUT)) {
                    md_rev_payload[data_count++] = data;
                    data_remain                  = data + 1;
                    continue;
                }
            }
            default: {
                md_rev_payload[data_count++] = data;
                data_remain--;

                if (data_remain) {
                    continue;
                }
            } break;
        }

        if (md_check_sum(md_rev_payload, data_count)) {
            md_send_ack();

            if (md_receive_process_kb(md_rev_payload, data_count) != true) {
                return;
            }

            switch (md_rev_payload[0]) {
                case MD_REV_CMD_RAW: {
                    uint8_t *pdata;
                    uint8_t  len;

                    len   = md_rev_payload[2];
                    pdata = &md_rev_payload[3];

                    if (len == sizeof(md_raw_payload)) {
                        memcpy(md_raw_payload, pdata, len);
                        md_receive_raw_cb(md_raw_payload, len);
                    }
                } break;
                case MD_REV_CMD_INDICATOR: {
                    md_info.indicator = md_rev_payload[1];
                } break;
                case MD_REV_CMD_DEVCTRL: {
                    switch (md_rev_payload[1]) {
                        case MD_REV_CMD_DEVCTRL_PAIRING: {
                            md_info.state = MD_STATE_PAIRING;
                        } break;
                        case MD_REV_CMD_DEVCTRL_CONNECTED: {
                            md_info.state = MD_STATE_CONNECTED;
                        } break;
                        case MD_REV_CMD_DEVCTRL_DISCONNECTED: {
                            md_info.state = MD_STATE_DISCONNECTED;
                        } break;
                        case MD_REV_CMD_DEVCTRL_REJECT: {
                            md_info.state = MD_STATE_REJECT;
                        } break;
                        default:
                            break;
                    }
                } break;
                case MD_REV_CMD_BATVOL: {
                    md_info.bat = md_rev_payload[1];
                } break;
                case MD_REV_CMD_MD_FW_VERSION: {
                    md_info.version = md_rev_payload[1];
                } break;
                case MD_REV_CMD_HOST_STATE: {
                    md_receive_host_cb(md_rev_payload[1] == MD_REV_CMD_HOST_STATE_RESUME);
                } break;
                default:
                    break;
            }
        }
        data_count = 0;
    }
}

static void md_send_pkt_task(void) {
    static uint32_t        smsg_timer  = 0x00;
    static uint8_t         smsg_retry  = 0;
    static smsg_message_t *current_msg = NULL;

    switch (smsg_get_state()) {
        case smsg_state_busy: {
            if (sync_timer_elapsed32(smsg_timer) > (MD_SEND_PKT_TIMEOUT)) {
                smsg_retry = 0;
                smsg_set_state(smsg_state_retry);
            }
        } break;
        case smsg_state_retry: {
            if (++smsg_retry > MD_SEND_PKT_RETRY) {
                smsg_retry = 0;
                if (current_msg) {
                    smsg_return(current_msg);
                    current_msg = NULL;
                }
            }
            smsg_set_state(smsg_state_free);
        } break;
        case smsg_state_replied: {
            if (current_msg) {
                smsg_return(current_msg);
                current_msg = NULL;
            }
            smsg_set_state(smsg_state_free);
        } // break;
        case smsg_state_free: {
            if (!current_msg) {
                current_msg = smsg_receive();
            }
            if (current_msg) {
                md_send_pkt(current_msg->data, current_msg->size);
                smsg_timer = sync_timer_read32();
                smsg_set_state(smsg_state_busy);
            }
        } break;
        default:
            break;
    }
}

void md_init(void) {
    uart_init(MD_BAUD_RATE);
    smsg_init();
}

void md_main_task(void) {
    md_send_pkt_task();
    md_receive_msg_task();
}

uint8_t *md_getp_state(void) {
    return &md_info.state;
}

uint8_t *md_getp_bat(void) {
    return &md_info.bat;
}

uint8_t *md_getp_indicator(void) {
    return &md_info.indicator;
}

uint8_t md_get_version(void) {
    return md_info.version;
}

void md_send_pkt(uint8_t *data, uint32_t len) {
    if (!data || !len) {
        return;
    }

    uart_transmit(data, len);
}

static bool md_send_fixed_length(uint8_t cmd, uint8_t *data, uint8_t data_len) {
    smsg_message_t *msg = smsg_take();
    if (!msg) return false;

    msg->data[0] = cmd;
    memcpy(&msg->data[1], data, data_len);
    md_calc_check_sum(msg->data, data_len + 1);
    msg->size = data_len + 2;
    smsg_send(msg);
    return true;
}

static bool md_send_variable_length(uint8_t cmd, const void *data, uint8_t data_len, uint8_t max_len) {
    if (data_len > max_len) {
        return false;
    }

    smsg_message_t *msg = smsg_take();
    if (!msg) return false;

    msg->data[0] = cmd;
    msg->data[1] = data_len;
    memcpy(&msg->data[2], data, data_len);
    md_calc_check_sum(msg->data, data_len + 2);
    msg->size = data_len + 3;
    smsg_send(msg);
    return true;
}

void md_send_kb(uint8_t *data) {
    md_send_fixed_length(MD_SND_CMD_SEND_KB, data, MD_SND_CMD_KB_LEN);
}

void md_send_nkro(uint8_t *data) {
    md_send_fixed_length(MD_SND_CMD_SEND_NKRO, data, MD_SND_CMD_NKRO_LEN);
}

void md_send_consumer(uint8_t *data) {
    md_send_fixed_length(MD_SND_CMD_SEND_CONSUMER, data, MD_SND_CMD_CONSUMER_LEN);
}

void md_send_system(uint8_t *data) {
    md_send_fixed_length(MD_SND_CMD_SEND_SYSTEM, data, MD_SND_CMD_SYSTEM_LEN);
}

void md_send_fn(uint8_t *data) {
    md_send_fixed_length(MD_SND_CMD_SEND_FN, data, MD_SND_CMD_FN_LEN);
}

void md_send_mouse(uint8_t *data) {
    md_send_fixed_length(MD_SND_CMD_SEND_MOUSE, data, MD_SND_CMD_MOUSE_LEN);
}

void md_send_devinfo(const char *name) {
    uint8_t infolen = strlen(name);
    md_send_variable_length(MD_SND_CMD_SEND_DEVINFO, name, infolen, MD_SND_CMD_DEVINFO_LEN);
}

void md_send_devctrl(uint8_t cmd) {
    md_send_fixed_length(MD_SND_CMD_DEVCTRL, &cmd, 1);
}

void md_send_manufacturer(char *str, uint8_t len) {
    md_send_variable_length(MD_SND_CMD_MANUFACTURER, str, len, MD_SND_CMD_MANUFACTURER_LEN);
}

void md_send_product(char *str, uint8_t len) {
    md_send_variable_length(MD_SND_CMD_PRODUCT, str, len, MD_SND_CMD_PRODUCT_LEN);
}

void md_send_vpid(uint16_t vid, uint16_t pid) {
    uint32_t vpid = (pid << 16) | vid;
    md_send_fixed_length(MD_SND_CMD_VPID, (uint8_t *)&vpid, sizeof(vpid));
}

void md_send_raw(uint8_t *data, uint8_t length) {
    if (length != MD_RAW_SIZE) {
        return;
    }

    smsg_message_t *msg = smsg_take();
    if (!msg) return;

    msg->data[0] = MD_SND_CMD_RAW;
    msg->data[1] = MD_SND_CMD_RAW_IN;
    msg->data[2] = length;
    memcpy(&msg->data[3], data, length);
    md_calc_check_sum(msg->data, MD_RAW_SIZE + 3);
    msg->size = MD_RAW_SIZE + 4;
    smsg_send(msg);
}

void md_devs_change(uint8_t devs, bool reset) __attribute__((weak));
void md_devs_change(uint8_t devs, bool reset) {
    switch (devs) {
        case DEVS_USB: {
            md_send_devctrl(MD_SND_CMD_DEVCTRL_USB);
        } break;
        case DEVS_2G4: {
            md_send_devctrl(MD_SND_CMD_DEVCTRL_2G4);
            if (reset) {
                md_send_devctrl(MD_SND_CMD_DEVCTRL_PAIR);
            }
        } break;
        case DEVS_BT1: {
            md_send_devctrl(MD_SND_CMD_DEVCTRL_BT1);
            if (reset) {
                md_send_devctrl(MD_SND_CMD_DEVCTRL_PAIR);
            }
        } break;
        case DEVS_BT2: {
            md_send_devctrl(MD_SND_CMD_DEVCTRL_BT2);
            if (reset) {
                md_send_devctrl(MD_SND_CMD_DEVCTRL_PAIR);
            }
        } break;
        case DEVS_BT3: {
            md_send_devctrl(MD_SND_CMD_DEVCTRL_BT3);
            if (reset) {
                md_send_devctrl(MD_SND_CMD_DEVCTRL_PAIR);
            }
        } break;
        case DEVS_BT4: {
            md_send_devctrl(MD_SND_CMD_DEVCTRL_BT4);
            if (reset) {
                md_send_devctrl(MD_SND_CMD_DEVCTRL_PAIR);
            }
        } break;
        case DEVS_BT5: {
            md_send_devctrl(MD_SND_CMD_DEVCTRL_BT5);
            if (reset) {
                md_send_devctrl(MD_SND_CMD_DEVCTRL_PAIR);
            }
        } break;
        default:
            break;
    }
}

bool md_inquire_bat(void) {
    if (smsg_is_busy()) {
        return false;
    }

    md_send_devctrl(MD_SND_CMD_DEVCTRL_INQVOL);

    return true;
}
