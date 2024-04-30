#define LOGO_LINE 7
#define SIDE_LINE 5
#define SIDE_LED_NUM (LOGO_LINE + SIDE_LINE)

enum {
    SIDE_WAVE = 0,
    SIDE_MIX,
    SIDE_STATIC,
    SIDE_BREATH,
    SIDE_OFF,
} side_effects;

#define LIGHT_COLOUR_MAX 8
#define SIDE_COLOUR_MAX 8

// from side_logo.c
#define STARRY_INDEX_LEN (160)
#define FIREWORK_INDEX_LEN (158)
#define STARRY_DATA_LEN 96
#define TIDE_DATA_LEN 120
#define LIGHT_SPEED_MAX 4

// from side.c
#define LIGHT_SPEED_MAX 4
#define RF_LED_LINK_PERIOD 500
#define RF_LED_PAIR_PERIOD 250
#define CHARGING_SHIFT 1
#define RFLINK_SHIFT 0
#define CHARGING_BREATHE 1

#define RFLINK_BLINK 1
#define LOW_BAT_BLINK_PRIOD 500


// data tables lengths
#define WAVE_TAB_LEN 112
#define LIGHT_TAB_LEN           101
#define BREATHE_TAB_LEN 128
#define FLOW_COLOUR_TAB_LEN 224
