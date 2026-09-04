
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_MORE_TAPS
} argos_td_state_t;

void argos_reload_tap_dances(void);
bool argos_tap_dance_read_eeprom(uint8_t index, argos_td_entry_t *entry);
bool argos_tap_dance_write_eeprom(uint8_t index, const argos_td_entry_t *entry);
void argos_tap_dance_listen_for_key(uint8_t *data);
void argos_tap_dance_set_keycode(uint8_t tap_dance_index, uint16_t keycode, uint8_t key_index);
void argos_tap_dance_reset_capturing_tap_dance_key_index(uint8_t index);
void argos_tap_dances_load_from_eeprom(void);
void argos_tap_dance_load_from_eeprom(uint8_t index);
void argos_tap_dance_set(uint8_t index, argos_td_entry_t entry);
argos_td_entry_t* argos_tap_dance_get(uint8_t index);