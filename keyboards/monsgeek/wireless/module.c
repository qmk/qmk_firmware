// Copyright 2024 Su (@isuua)
// Copyright 2024 Priyadie (@priyadie)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "module.h"
#include "smsg.h"
#include "uart.h"

#ifndef MD_BAUD_RATE
#    define MD_BAUD_RATE 115200
#endif

#ifndef MD_SNED_PKT_TIMEOUT
#    define MD_SNED_PKT_TIMEOUT 10
#endif

#ifndef MD_SEND_PKT_RETRY
#    define MD_SEND_PKT_RETRY 40
#endif

#ifndef MD_SEND_PKT_PAYLOAD_MAX
#    define MD_SEND_PKT_PAYLOAD_MAX 36
#endif

#ifndef MD_BT1_NAME
#    define MD_BT1_NAME PRODUCT " BT1"
#endif

#ifndef MD_BT2_NAME
#    define MD_BT2_NAME PRODUCT " BT2"
#endif

#ifndef MD_BT3_NAME
#    define MD_BT3_NAME PRODUCT " BT3"
#endif

#ifndef MD_BT4_NAME
#    define MD_BT4_NAME PRODUCT " BT4"
#endif

#ifndef MD_BT5_NAME
#    define MD_BT5_NAME PRODUCT " BT5"
#endif

#define USBCONCAT(a, b) a##b
#define USBSTR(s) USBCONCAT(L, s)

typedef struct
{
    uint8_t state;
    uint8_t indicator;
    uint8_t bat;
} md_info_t;

static uint8_t md_pkt_payload[MD_SEND_PKT_PAYLOAD_MAX] = {0};
static uint8_t md_rev_payload[MD_SEND_PKT_PAYLOAD_MAX] = {0};

static md_info_t md_info = {
    .bat       = 100,
    .indicator = 0,
    .state     = MD_STATE_NONE,
};

static void md_send_ack(void) {

    uint8_t sdata[0x03] = {0x66, 0xAA, 0xBB};
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
    static uint32_t data_count = 0x00;
    static uint8_t data_remain = 0x00;

    while (uart_available()) {
        uint8_t data = uart_read();

        switch (data_count) {
            case 0: { // cmd
                switch (data) {
                    case 0xAC:
                    case 0x66: {
                        md_rev_payload[data_count++] = data;
                        data_remain                  = 4;
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
                if ((md_rev_payload[0] == 0x66) && (md_rev_payload[1] == 0xAA) && (data == 0xBB)) {
                    if (smsg_get_state() == smsg_state_busy) {
                        smsg_set_state(smsg_state_replied);
                    }
                    data_count = 0;
                    return;
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
                default:
                    break;
            }
        }
        data_count = 0;
    }
}

static void md_send_pkt_task(void) {
    static uint32_t smsg_timer = 0x00;
    static uint8_t smsg_retry  = 0;

    switch (smsg_get_state()) {
        case smsg_state_busy: {
            if (sync_timer_elapsed32(smsg_timer) > (MD_SNED_PKT_TIMEOUT)) {
                smsg_retry = 0;
                smsg_set_state(smsg_state_retry);
            }
        } break;
        case smsg_state_retry: {
            if (++smsg_retry > MD_SEND_PKT_RETRY) {
                smsg_retry = 0;
                smsg_pop();
            }
            smsg_set_state(smsg_state_free);
        } break;
        case smsg_state_replied: {
            smsg_pop();
            smsg_set_state(smsg_state_free);
        } // break;
        case smsg_state_free: {
            uint32_t size = smsg_peek(md_pkt_payload);
            if (size) {
                md_send_pkt(md_pkt_payload, size);
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

    memset(md_pkt_payload, 0, sizeof(md_pkt_payload));
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

void md_send_pkt(uint8_t *data, uint32_t len) {

    if (!data || !len) {
        return;
    }

    // send
    uart_transmit(data, len);
}

void md_send_kb(uint8_t *data) {
    uint8_t sdata[MD_SND_CMD_KB_LEN + 4] = {0x00};

    sdata[0] = 0xAC; // head
    sdata[1] = MD_SND_CMD_SEND_KB;
    sdata[2] = MD_SND_CMD_KB_LEN;
    memcpy(&sdata[3], data, sizeof(sdata) - 4);
    md_calc_check_sum(sdata, sizeof(sdata) - 1);
    smsg_push(sdata, sizeof(sdata));
}

void md_send_nkro(uint8_t *data) {
    uint8_t sdata[MD_SND_CMD_NKRO_LEN + 4] = {0x00};

    sdata[0] = 0xAC; // head
    sdata[1] = MD_SND_CMD_SEND_NKRO;
    sdata[2] = MD_SND_CMD_NKRO_LEN;
    memcpy(&sdata[3], data, sizeof(sdata) - 4);
    md_calc_check_sum(sdata, sizeof(sdata) - 1);
    smsg_push(sdata, sizeof(sdata));
}

void md_send_consumer(uint8_t *data) {
    uint8_t sdata[MD_SND_CMD_CONSUMER_LEN + 4] = {0x00};

    sdata[0] = 0xAC; // head
    sdata[1] = MD_SND_CMD_SEND_CONSUMER;
    sdata[2] = MD_SND_CMD_CONSUMER_LEN;
    memcpy(&sdata[3], data, sizeof(sdata) - 4);
    md_calc_check_sum(sdata, sizeof(sdata) - 1);
    smsg_push(sdata, sizeof(sdata));
}

void md_send_system(uint8_t *data) {
    uint8_t sdata[MD_SND_CMD_SYSTEM_LEN + 4] = {0x00};

    sdata[0] = 0xAC; // head
    sdata[1] = MD_SND_CMD_SEND_SYSTEM;
    sdata[2] = MD_SND_CMD_SYSTEM_LEN;
    memcpy(&sdata[3], data, sizeof(sdata) - 4);
    md_calc_check_sum(sdata, sizeof(sdata) - 1);
    smsg_push(sdata, sizeof(sdata));
}

void md_send_fn(uint8_t *data) {
    uint8_t sdata[MD_SND_CMD_FN_LEN + 4] = {0x00};

    sdata[0] = 0xAC; // head
    sdata[1] = MD_SND_CMD_SEND_FN;
    sdata[2] = MD_SND_CMD_FN_LEN;
    memcpy(&sdata[3], data, sizeof(sdata) - 4);
    md_calc_check_sum(sdata, sizeof(sdata) - 1);
    smsg_push(sdata, sizeof(sdata));
}

void md_send_mouse(uint8_t *data) {
    uint8_t sdata[MD_SND_CMD_MOUSE_LEN + 4] = {0x00};

    sdata[0] = 0xAC; // head
    sdata[1] = MD_SND_CMD_SEND_MOUSE;
    sdata[2] = MD_SND_CMD_MOUSE_LEN;
    memcpy(&sdata[3], data, sizeof(sdata) - 4);
    md_calc_check_sum(sdata, sizeof(sdata) - 1);
    smsg_push(sdata, sizeof(sdata));
}

void md_send_devinfo(const char *name) {
    uint8_t sdata[MD_SND_CMD_DEVINFO_LEN + 4] = {0x00};
    uint8_t infolen                           = strlen((const char *)name);

    if (infolen > MD_SND_CMD_DEVINFO_LEN) {
        return;
    }

    sdata[0] = 0xAC; // head
    sdata[1] = MD_SND_CMD_SEND_DEVINFO;
    sdata[2] = infolen;

    memcpy(&sdata[3], name, infolen);
    md_calc_check_sum(sdata, infolen + 3);
    smsg_push(sdata, sizeof(sdata));
}

void md_send_devctrl(uint8_t cmd) {
    uint8_t sdata[5] = {0x00};

    sdata[0] = 0xAC; // head
    sdata[1] = MD_SND_CMD_DEVCTRL;
    sdata[2] = 1;
    sdata[3] = cmd;
    md_calc_check_sum(sdata, sizeof(sdata) - 1);
    smsg_push(sdata, sizeof(sdata));
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
                md_send_devctrl(MD_SND_CMD_DEVCTRL_CLEAN);
                md_send_devctrl(MD_SND_CMD_DEVCTRL_PAIR);
            }
        } break;
        case DEVS_BT1: {
            md_send_devctrl(MD_SND_CMD_DEVCTRL_BT1);
            if (reset) {
                md_send_devctrl(MD_SND_CMD_DEVCTRL_CLEAN);
                md_send_devinfo(MD_BT1_NAME);
                md_send_devctrl(MD_SND_CMD_DEVCTRL_PAIR);
            }
        } break;
        case DEVS_BT2: {
            md_send_devctrl(MD_SND_CMD_DEVCTRL_BT2);
            if (reset) {
                md_send_devctrl(MD_SND_CMD_DEVCTRL_CLEAN);
                md_send_devinfo(MD_BT2_NAME);
                md_send_devctrl(MD_SND_CMD_DEVCTRL_PAIR);
            }
        } break;
        case DEVS_BT3: {
            md_send_devctrl(MD_SND_CMD_DEVCTRL_BT3);
            if (reset) {
                md_send_devctrl(MD_SND_CMD_DEVCTRL_CLEAN);
                md_send_devinfo(MD_BT3_NAME);
                md_send_devctrl(MD_SND_CMD_DEVCTRL_PAIR);
            }
        } break;
        case DEVS_BT4: {
            md_send_devctrl(MD_SND_CMD_DEVCTRL_BT4);
            if (reset) {
                md_send_devctrl(MD_SND_CMD_DEVCTRL_CLEAN);
                md_send_devinfo(MD_BT4_NAME);
                md_send_devctrl(MD_SND_CMD_DEVCTRL_PAIR);
            }
        } break;
        case DEVS_BT5: {
            md_send_devctrl(MD_SND_CMD_DEVCTRL_BT5);
            if (reset) {
                md_send_devctrl(MD_SND_CMD_DEVCTRL_CLEAN);
                md_send_devinfo(MD_BT5_NAME);
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
