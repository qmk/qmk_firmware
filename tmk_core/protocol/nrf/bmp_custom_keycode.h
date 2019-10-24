
#pragma once

#include "quantum_keycodes.h"

#define BMP_EX_KC_LEN 32
enum bmp_custom_keycodes {
    BLE_DIS = SAFE_RANGE, /* Disable BLE HID sending              */
    BLE_EN,               /* Enable BLE HID sending               */
    USB_DIS,              /* Disable USB HID sending              */
    USB_EN,               /* Enable USB HID sending               */
    SEL_BLE,              /* Enable BLE and disable USB           */
    SEL_USB,              /* Enable USB and disable BLE           */
    ADV_ID0,              /* Start advertising to PeerID 0        */
    ADV_ID1,              /* Start advertising to PeerID 1        */
    ADV_ID2,              /* Start advertising to PeerID 2        */
    ADV_ID3,              /* Start advertising to PeerID 3        */
    ADV_ID4,              /* Start advertising to PeerID 4        */
    ADV_ID5,              /* Start advertising to PeerID 5        */
    ADV_ID6,              /* Start advertising to PeerID 6        */
    ADV_ID7,              /* Start advertising to PeerID 7        */
    AD_WO_L,              /* Start advertising without whitelist  */
    DEL_ID0,              /* Delete bonding of PeerID 0           */
    DEL_ID1,              /* Delete bonding of PeerID 1           */
    DEL_ID2,              /* Delete bonding of PeerID 2           */
    DEL_ID3,              /* Delete bonding of PeerID 3           */
    DEL_ID4,              /* Delete bonding of PeerID 4           */
    DEL_ID5,              /* Delete bonding of PeerID 5           */
    DEL_ID6,              /* Delete bonding of PeerID 6           */
    DEL_ID7,              /* Delete bonding of PeerID 7           */
    DELBNDS,              /* Delete all bonding                   */
    ENT_DFU,              /* Start bootloader                     */
    ENT_WEB,              /* Start web configurator               */
    ENT_SLP,              /* Deep sleep mode                      */
    BATT_LV,              /* Display battery level in milli volts */
    SAVE_EE,
    DEL_EE,
    xEISU,
    xKANA,
    EXKC_START,           /* Extended keycode START               */
    EXKC_END = EXKC_START + BMP_EX_KC_LEN - 1,
    BMP_SAFE_RANGE        /* End of custom kecode                 */
};

