#include "color.h"
#include "rgblight_list.h"

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)

// Laser Colors
#define HSV_LSR_PURPLE   HSV_PURPLE
#define HSV_LSR_PINK     HSV_PINK
#define HSV_LSR_BLUE     HSV_BLUE
#define HSV_LSR_CYAN     HSV_CYAN
#define HSV_LSR_MAGENTA  HSV_MAGENTA

// Granite Colors
#define HSV_GNT_BLUE     HSV_BLUE
#define HSV_GNT_RED      HSV_RED
#define HSV_GNT_GREEN    HSV_GREEN
#define HSV_GNT_YELLOW   HSV_YELLOW
#define HSV_GNT_WHITE    HSV_WHITE

// Theme Colors
#if defined(THEME_LASER)
#   define HSV_THEME_0   HSV_LSR_PURPLE
#   define HSV_THEME_1   HSV_LSR_PINK
#   define HSV_THEME_2   HSV_LSR_BLUE
#   define HSV_THEME_3   HSV_LSR_CYAN
#elif defined(THEME_GRANITE)
#   define HSV_THEME_0   HSV_GNT_WHITE
#   define HSV_THEME_1   HSV_GNT_BLUE
#   define HSV_THEME_2   HSV_GNT_RED
#   define HSV_THEME_3   HSV_GNT_YELLOW
#else
#   define HSV_THEME_0   HSV_LSR_PURPLE
#   define HSV_THEME_1   HSV_LSR_PINK
#   define HSV_THEME_2   HSV_LSR_BLUE
#   define HSV_THEME_3   HSV_LSR_CYAN
#endif

// Set Color for Light Layer
#if !defined(HSV_THEME_L) && defined(HSV_THEME_0)
#   define HSV_THEME_L   HSV_THEME_0
#else
#   define HSV_THEME_L   HSV_CORAL
#endif
// Set Color for Magic Layer
#if !defined(HSV_THEME_M)
#   define HSV_THEME_M   HSV_SPRINGGREEN
#endif


typedef enum {
    LASER = 0,
    GRANITE
} rgb_theme_name_t;

typedef struct {
    rgb_theme_name_t theme;
    HSV colors[5];
} rgb_theme_t;

extern const HSV laser_purple;
extern const HSV laser_pink;
extern const HSV laser_blue;
extern const HSV laser_cyan;
extern const HSV laser_magenta;
extern const rgb_theme_t rgb_laser;

extern const HSV granite_white;
extern const HSV granite_blue;
extern const HSV granite_red;
extern const HSV granite_green;
extern const HSV granite_yellow;
extern const rgb_theme_t rgb_granite;

extern const HSV default_magic;

extern const rgb_theme_t *themes[];

void set_rgb_theme(rgb_theme_name_t theme_name);
rgb_theme_t get_rgb_theme(void);

HSV get_rgb_theme_color(uint8_t index);
#endif
