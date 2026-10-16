// Copyright 2024 Su (@isuua)
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
    MD_SND_CMD_MANUFACTURER_LEN = 46,
    MD_SND_CMD_PRODUCT_LEN      = 46,
};

enum {
    /* send report */
    MD_SND_CMD_SEND_KB       = 0xA1,
    MD_SND_CMD_SEND_NKRO     = 0xA2,
    MD_SND_CMD_SEND_CONSUMER = 0xA3,
    MD_SND_CMD_SEND_SYSTEM   = 0xA4,
    MD_SND_CMD_SEND_FN       = 0xA5,
    MD_SND_CMD_SEND_MOUSE    = 0xA8,
    MD_SND_CMD_SEND_DEVINFO  = 0xA9,
    /* Dongle */
    MD_SND_CMD_MANUFACTURER = 0xAB,
    MD_SND_CMD_PRODUCT      = 0xAC,
    MD_SND_CMD_VPID         = 0xAD,
    MD_SND_CMD_RAW          = 0xAF,
    MD_SND_CMD_RAW_IN       = 0x61,
    /* device ctrl */
    MD_SND_CMD_DEVCTRL                    = 0xA6,
    MD_SND_CMD_DEVCTRL_BAT                = 0xA7,
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
    MD_SND_CMD_DEVCTRL_RSV_DEBUG          = 0x60, // reserved
    MD_SND_CMD_DEVCTRL_RSV_SLEEP          = 0x61, // reserved
    MD_SND_CMD_DEVCTRL_FORCED_PAIRING_BT  = 0x62, // forced pairing, to be used in a factory environment.
    MD_SND_CMD_DEVCTRL_FORCED_PAIRING_2G4 = 0x63, // forced pairing, to be used in a factory environment.
    MD_SND_CMD_DEVCTRL_CHARGING           = 0x64, // battery power control.
    MD_SND_CMD_DEVCTRL_CHARGING_STOP      = 0x65, // battery power control.
    MD_SND_CMD_DEVCTRL_CHARGING_DONE      = 0x66, // battery power control.
    MD_SND_CMD_DEVCTRL_FW_VERSION         = 0x70, // module fw version.
    MD_SND_CMD_INVALID_DATA               = 0x00, // unused
};

enum {
    MD_REV_CMD_RAW                  = 0xAF,
    MD_REV_CMD_RAW_OUT              = 0x60,
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
    MD_REV_CMD_DEVCTRL_UNPAIRED     = 0x37, // reserved
    MD_REV_CMD_DEVCTRL_MD_WAKEUP    = 0x42, // unused
    MD_REV_CMD_DEVCTRL_CLS_UART     = 0x43, // unused
    MD_REV_CMD_BATVOL               = 0x5C,
    MD_REV_CMD_MD_FW_VERSION        = 0x5D,
    MD_REV_CMD_HOST_STATE           = 0x60,
    MD_REV_CMD_HOST_STATE_SUSPEND   = 0x00,
    MD_REV_CMD_HOST_STATE_RESUME    = 0x01,
};

enum {
    BURST                           = 0xB2,
    CONTINUE                        = 0xB3,
    STOP                            = 0xB4,
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
void md_send_manufacturer(char *str, uint8_t len);
void md_send_product(char *str, uint8_t len);
void md_send_vpid(uint16_t vid, uint16_t pid);
void md_send_raw(uint8_t *data, uint8_t length);
void md_send_pkt(uint8_t *data, uint32_t len);
bool md_receive_process_user(uint8_t *pdata, uint8_t len);
void md_devs_change(uint8_t devs, bool reset);
bool md_inquire_bat(void);
uint8_t md_get_version(void);
uint8_t *md_getp_state(void);
uint8_t *md_getp_bat(void);
uint8_t *md_getp_indicator(void);
void md_rf_send_carrier(uint8_t channel, uint8_t tx_power, uint8_t phy);
void md_rf_send_stop(void);
void md_send_devctrl_bat(uint8_t cmd);
