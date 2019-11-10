#ifndef HWADDRESS_H
#define HWADDRESS_H

#define KBD_ACTIVATION              ((void *)2)
#define KBD_ACTIVATION_BIT          (0x5)


#define EEPADDR_BOOTLOADER_ACT      ((void *)0)
#define EEPVAL_BOOTLOADER_BIT       (0xCA)


#define EEPADDR_MACRO_SET           ((uint8_t *)0x80)    // 256-511 (1Byte x 52)
#define EEPVAL_MACRO_BIT            (0xCA)                // 0xCA :macro is recorded 

#define EEPADDR_KBD_CONF            ((void *)0x100)    // 256 - 128

#define EEPADDR_KEYMAP_LAYER0       ((void *)0x200)    // 512 - 128
#define EEPADDR_KEYMAP_LAYER1       ((void *)0x280)    // 640 - 128
#define EEPADDR_KEYMAP_LAYER2       ((void *)0x300)    // 768 - 128
#define EEPADDR_KEYMAP_LAYER3       ((void *)0x380)    // 896 - 128

#define EEPSIZE_KEYMAP              (0x80)


#define EEP_KEYMAP_ADDR(layer)  (EEPADDR_KEYMAP_LAYER0 + (EEPSIZE_KEYMAP * layer))



#define MAX_RGB_CHAIN       20

enum
{
    RGB_EFFECT_BOOTHID = 0,
    RGB_EFFECT_FADE_BUF,
    RGB_EFFECT_FADE_LOOP,
    RGB_EFFECT_HEARTBEAT_BUF,
    RGB_EFFECT_HEARTBEAT_LOOP,
    RGB_EFFECT_BASIC,
    RGB_EFFECT_MAX
};

#define FADE_HIGH_HOLD             5
#define FADE_LOW_HOLD              0
#define FADE_IN_ACCEL              0  // normal ascending

#define HEARTBEAT_HIGH_HOLD        1
#define HEARTBEAT_LOW_HOLD         5
#define HEARTBEAT_IN_ACCEL         1  // 1: weighted ascending. 2: quadratic ascending 

typedef struct {
    uint8_t index;
    uint8_t high_hold;
    uint8_t low_hold;
    uint8_t accel_mode;
} rgb_effect_param_type;


typedef struct kbd_conf
{
    uint8_t ps2usb_mode;                    // 0: PS2, 1: USB
    uint8_t keymapLayerIndex;               // KEYMAP layer index;
    uint8_t swapCtrlCaps;                   // 1: Swap Capslock <-> Left Ctrl
    uint8_t swapAltGui;                     // 1: Swap Alt <-> GUI(WIN) 
    uint8_t led_preset_index;               // LED effect  preset index
    uint8_t led_preset[3][5];               // Block configuration for LED effect  preset
    uint8_t rgb_effect_index;               // RGB effect index
    uint8_t rgb_chain;                      // RGB5050 numbers (H/W dependent)
    uint8_t rgb_preset[MAX_RGB_CHAIN][3];   // Chain color
    rgb_effect_param_type rgb_effect_param[RGB_EFFECT_MAX]; // RGB effect parameter
    uint16_t rgb_limit;
    uint16_t rgb_speed;
    uint8_t  matrix_debounce;
    uint8_t  sleepTimerMin;
}kbd_configuration_t;

#define MACRO_ADDR_START      0x4400     // 0x4400 ~ 0x6FFF  (7KBytes - 256B x 44)

extern kbd_configuration_t kbdConf;
extern void updateConf(void);

#endif // HWADDRESS_H
