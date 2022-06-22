#pragma once

#include "quantum.h"
#include "raw_hid.h"

#ifndef RAW_ENABLE
#    error "Raw hid needs to be enabled, please enable it!"
#endif
#ifndef RAW_EPSIZE
#    define RAW_EPSIZE 32
#endif

#define ORYX_STOP_BIT -2
#define PAIRING_BLINK_STEPS 512
#define PAIRING_BLINK_END PAIRING_BLINK_STEPS * 60
#define PAIRING_SEQUENCE_SIZE 3
#define PAIRING_SEQUENCE_NUM_STORED 3
#define PAIRING_STORAGE_SIZE PAIRING_SEQUENCE_SIZE* PAIRING_SEQUENCE_NUM_STORED * sizeof(uint16_t)

enum Oryx_Command_Code {
    ORYX_CMD_GET_FW_VERSION,
    ORYX_CMD_PAIRING_INIT,
    ORYX_CMD_PAIRING_VALIDATE,
    ORYX_CMD_DISCONNECT,
    ORYX_SET_LAYER
};

enum Oryx_Event_Code {
    ORYX_EVT_GET_FW_VERSION,
    ORYX_EVT_PAIRING_INPUT,
    ORYX_EVT_PAIRING_KEY_INPUT,
    ORYX_EVT_PAIRING_FAILED,
    ORYX_EVT_PAIRING_SUCCESS,
    ORYX_EVT_LAYER,
    ORYX_EVT_KEYDOWN,
    ORYX_EVT_KEYUP,
};

extern bool oryx_state_live_training_enabled;

typedef struct {
    bool pairing;
    bool paired;
} rawhid_state_t;

extern rawhid_state_t rawhid_state;

void     create_pairing_code(void);
bool     store_pairing_sequence(keypos_t* pairing_sequence);
keypos_t get_random_keypos(void);
void     pairing_init_handler(void);
void     pairing_validate_handler(void);
void     pairing_validate_eeprom_handler(void);
void     pairing_init_event(void);
bool     compare_sequences(keypos_t a[PAIRING_SEQUENCE_SIZE], keypos_t b[PAIRING_SEQUENCE_SIZE]);
void     pairing_key_input_event(void);
void     pairing_failed_event(void);
void     pairing_succesful_event(void);

void oryx_layer_event(void);
bool is_oryx_live_training_enabled(void);
bool process_record_oryx(uint16_t keycode, keyrecord_t* record);
void layer_state_set_oryx(layer_state_t state);
