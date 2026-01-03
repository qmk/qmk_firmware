#include <stdbool.h>
#include <stdint.h>

#define HS_BT_DEF_PIN C14     // SYSTEM_MAC_PIN
#define HS_2G4_DEF_PIN C15    // SYSTEM_WIN_PIN
#define HS_BT_PIN_STATE 0, 1  // Mac wireless mode (top)
#define HS_2G4_PIN_STATE 1, 0 // Windows wireless mode (bottom)
#define HS_USB_PIN_STATE 1, 1 // USB mode (middle)

#define HS_GET_MODE_PIN_(pin_bt, pin_2g4) ((((#pin_bt)[0] == 'x') || ((gpio_read_pin(HS_BT_DEF_PIN) + 0x30) == ((#pin_bt)[0]))) && (((#pin_2g4)[0] == 'x') || ((gpio_read_pin(HS_2G4_DEF_PIN) + 0x30) == ((#pin_2g4)[0]))))
#define HS_GET_MODE_PIN(state) HS_GET_MODE_PIN_(state)
#define HS_MODEIO_DETECTION_TIME 50
#define HS_LBACK_TIMEOUT (30 * 1000)
// #define HS_SLEEP_TIMEOUT (5 * 1000) //(5s)
#define HS_SLEEP_TIMEOUT (5 * 60 * 1000) //(5min)

enum modeio_mode { hs_none = 0, hs_usb, hs_mac_wireless, hs_win_wireless, hs_wireless };

extern bool lower_sleep;
bool        hs_rgb_blink_hook(void);
bool        hs_mode_scan(bool update, uint8_t moude, uint8_t lsat_btdev, uint8_t last_wireless_dev);
bool        hs_modeio_detection(bool update, uint8_t *mode, uint8_t lsat_btdev, uint8_t last_wireless_dev);
void        hs_rgb_blink_set_timer(uint32_t time);
