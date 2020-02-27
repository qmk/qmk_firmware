
// Redefine USB Device to match Ramaworks current style
#undef VENDOR_ID
#undef PRODUCT_ID
#undef DEVICE_VER
#undef MANUFACTURER
#undef PRODUCT
#undef DESCRIPTION

#define VENDOR_ID       0x5241 // "RA"
#define PRODUCT_ID      0x00AA // 10-A
#define DEVICE_VER      0x0001
#define MANUFACTURER    RAMA WORKS
#define PRODUCT         RAMA WORKS M10-A
#define DESCRIPTION     RAMA WORKS M10-A

// Keep default crazy number of layers
#define DYNAMIC_KEYMAP_LAYER_COUNT 10