# VIA keymap for the Drop Alt Keyboard
## *LED Modes:*
Enables all RGB Matrix animation modes available in QMK, all of which are selectable through VIA or using the LED mode keys

```c
#define USB_LED_INDICATOR_ENABLE
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS 
#define RGB_MATRIX_KEYPRESSES
```

## *User Keycodes:*
All keyboard specific keycodes are defined in the user_keycodes space, allowing for them to be placed on your keyboard through VIA

```c
enum alt_keycodes {
    U_T_AUTO = USER00,     //USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,              //USB Toggle Automatic GCR control
    DBG_TOG,               //DEBUG Toggle On / Off
    DBG_MTRX,              //DEBUG Toggle Matrix Prints
    DBG_KBD,               //DEBUG Toggle Keyboard Prints
    DBG_MOU,               //DEBUG Toggle Mouse Prints
    MD_BOOT,               //Restart into bootloader after hold timeout
};
```