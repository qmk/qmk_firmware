#include QMK_KEYBOARD_H

#include "quantum.h"
#include <stdbool.h>
#include "wireless.h"
#include "raw_hid.h"
#include "via.h"
#include "rgb_record/rgb_record.h"
// #define HS_BT_DEF_PIN                     C14
// #define HS_2G4_DEF_PIN                    C15
// #define HS_BT_PIN_STATE                   0, 1
// #define HS_2G4_PIN_STATE                  1, 0
// #define HS_USB_PIN_STATE                  1, 1

#define HS_MODE_SW_PIN C14

#define HS_GET_MODE_PIN_(pin_bt, pin_2g4) ((((#pin_bt)[0] == 'x') || ((readPin(HS_BT_DEF_PIN) + 0x30) == ((#pin_bt)[0]))) && (((#pin_2g4)[0] == 'x') || ((readPin(HS_2G4_DEF_PIN) + 0x30) == ((#pin_2g4)[0]))))
#define HS_GET_MODE_PIN(state)            HS_GET_MODE_PIN_(state)
#define HS_MODEIO_DETECTION_TIME          50
#define HS_LBACK_TIMEOUT                  (30 * 6000)
#define HS_PAIR_TIMEOUT                   (30 * 6000)
#define HS_SLEEP_TIMEOUT                  (5 * 60000) //(1 * 60000)

enum modeio_mode {
    hs_none = 0,
    hs_usb,
    hs_bt,
    hs_2g4,
    hs_wireless
};

enum mm_sleep_timeout {
    hs_sleep_timeout_none = 0,
    hs_sleep_timeout_1min,
    hs_sleep_timeout_3min,
    hs_sleep_timeout_5min,
    hs_sleep_timeout_10min,
    hs_sleep_timeout_20min,
    hs_sleep_timeout_30min,
    hs_sleep_timeout_vendor, // Max. 7
};

enum via_custom_defined_id {
    id_sleep_timeout = 0x01,
    id_rgbrec_channel,
    id_rgbrec_hs_data,
    id_rgbrec_hs_buffer,
};

extern bool lower_sleep;
extern uint8_t hs_get_sleep_timeout(void);
extern void hs_set_sleep_timeout(uint8_t time);
extern void eeconfig_confinfo_update(void);
extern void hs_reset_settings(void);
bool hs_rgb_blink_hook(void);
bool hs_mode_scan(bool update, uint8_t moude, uint8_t lsat_btdev);
bool hs_modeio_detection(bool update, uint8_t *mode, uint8_t lsat_btdev);
void hs_rgb_blink_set_timer(uint32_t time);