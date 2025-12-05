// Copyright 2024 Su (@isuua)
// Copyright 2024 Priyadie (@priyadie)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// device index
enum {
    DEVS_USB = 0,
    DEVS_BT1,
    DEVS_BT2,
    DEVS_BT3,
    DEVS_BT4,
    DEVS_BT5,
    DEVS_2G4,
};

enum {
    MD_STATE_NONE = 0,
    MD_STATE_PAIRING,
    MD_STATE_CONNECTED,
    MD_STATE_DISCONNECTED,
    MD_STATE_REJECT,
};

enum {
    MD_SND_CMD_KB_LEN           = 8,
    MD_SND_CMD_NKRO_LEN         = 14,
    MD_SND_CMD_CONSUMER_LEN     = 2,
    MD_SND_CMD_SYSTEM_LEN       = 1,
    MD_SND_CMD_FN_LEN           = 1,
    MD_SND_CMD_MOUSE_LEN        = 5,
    MD_SND_CMD_DEVINFO_LEN      = 18,
};

enum {
    /* send report */
    MD_SND_CMD_SEND_KB       = 0x51,
    MD_SND_CMD_SEND_NKRO     = 0x52,
    MD_SND_CMD_SEND_CONSUMER = 0x53,
    MD_SND_CMD_SEND_SYSTEM   = 0x54,
    MD_SND_CMD_SEND_FN       = 0x55,
    MD_SND_CMD_SEND_MOUSE    = 0x58,
    MD_SND_CMD_SEND_DEVINFO  = 0x59,
    /* device ctrl */
    MD_SND_CMD_DEVCTRL                    = 0x56,
    MD_SND_CMD_DEVCTRL_USB                = 0x11,
    MD_SND_CMD_DEVCTRL_2G4                = 0x30,
    MD_SND_CMD_DEVCTRL_BT1                = 0x31,
    MD_SND_CMD_DEVCTRL_BT2                = 0x32,
    MD_SND_CMD_DEVCTRL_BT3                = 0x33,
    MD_SND_CMD_DEVCTRL_BT4                = 0x34,
    MD_SND_CMD_DEVCTRL_BT5                = 0x35,
    MD_SND_CMD_DEVCTRL_PAIR               = 0x51,
    MD_SND_CMD_DEVCTRL_CLEAN              = 0x52,
    MD_SND_CMD_DEVCTRL_INQVOL             = 0x53,
    MD_SND_CMD_DEVCTRL_SLEEP_INSTANT      = 0x54, // reserved
    MD_SND_CMD_DEVCTRL_SLEEP_BT_EN        = 0x55, // timeout 30min enable in BT mode
    MD_SND_CMD_DEVCTRL_SLEEP_BT_DIS       = 0x56, // timeout 30min disable in BT mode
    MD_SND_CMD_DEVCTRL_SLEEP_2G4_EN       = 0x57, // timeout 30min enable in 2.4G mode
    MD_SND_CMD_DEVCTRL_SLEEP_2G4_DIS      = 0x58, // timeout 30min enable in 2.4G mode
};

enum {
    MD_REV_CMD_INDICATOR            = 0x5A,
    MD_REV_CMD_DEVCTRL              = 0x5B,
    MD_REV_CMD_DEVCTRL_BAT_LOW      = 0x21, // unused
    MD_REV_CMD_DEVCTRL_BAT_PWROFF   = 0x22, // unused
    MD_REV_CMD_DEVCTRL_BAT_NORMAL   = 0x23, // unused
    MD_REV_CMD_DEVCTRL_PAIRING      = 0x31,
    MD_REV_CMD_DEVCTRL_CONNECTED    = 0x32,
    MD_REV_CMD_DEVCTRL_DISCONNECTED = 0x33,
    MD_REV_CMD_DEVCTRL_DONE         = 0x34, // reserved
    MD_REV_CMD_DEVCTRL_RECONNECT    = 0x35, // reserved
    MD_REV_CMD_DEVCTRL_REJECT       = 0x36,
    MD_REV_CMD_DEVCTRL_MD_WAKEUP    = 0x42, // unused
    MD_REV_CMD_BATVOL               = 0x5C,
};

void md_init(void);
void md_main_task(void);
void md_send_kb(uint8_t *data);
void md_send_nkro(uint8_t *data);
void md_send_consumer(uint8_t *data);
void md_send_system(uint8_t *data);
void md_send_fn(uint8_t *data);
void md_send_mouse(uint8_t *data);
void md_send_devctrl(uint8_t cmd);
void md_send_pkt(uint8_t *data, uint32_t len);
bool md_receive_process_user(uint8_t *pdata, uint8_t len);
void md_devs_change(uint8_t devs, bool reset);
bool md_inquire_bat(void);
uint8_t *md_getp_state(void);
uint8_t *md_getp_bat(void);
uint8_t *md_getp_indicator(void);
