#undef BOOTMAGIC_ENABLE
#undef BOOTMAGIC_LITE

/* Bootmagic Lite key configuration */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0


#undef BOOTMAGIC_ENABLE
#undef BOOTMAGIC_LITE

/* Bootmagic Lite key configuration */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0

// VIA version 3 does not like 0xfeed as the VID.
// Using the VID and PID for the xwhatsit controller.
#undef VENDOR_ID
#undef PRODUCT_ID
#undef DEVICE_VER
#undef MANUFACTURER 
#undef PRODUCT

/* USB Device descriptor parameter */
#define VENDOR_ID 0x1209
#define PRODUCT_ID 0x4704
#define DEVICE_VER 0x0001
#define MANUFACTURER Model F Labs
#define PRODUCT VIA - Reproduction IBM F77 Keyboard

