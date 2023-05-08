#pragma once

#include "T4CORUN.h"
#include "oled_driver.h"

#define OLED_RENDER_KEYLOCK_NAME      "Lock:"
#define OLED_RENDER_MODS_NAME         "Mods:"

#if defined(KEYLOG_ENABLE)
# define OLED_RENDER_KEYLOGGER_NAME    "KLog:"
#endif

#define OLED_RENDER_LAYOUT_NAME       "Lyout"
#define OLED_RENDER_LAYOUT_QWERTY     " QRTY"
#define OLED_RENDER_LAYOUT_COLEMAK_DH " cmDH"

#if defined(GAMELAYER_ENABLE)
# define OLED_RENDER_LAYOUT_GAMING    " Game"
#endif //GAMELAYER_ENABLE

#define OLED_RENDER_RGB_NAME          "RGB: "
#define OLED_RENDER_RGB_ON            " On  "
#define OLED_RENDER_RGB_OFF           " Off "

#define OLED_RENDER_LAYER_NAME        "Layer"
#define OLED_RENDER_LAYER_BASE        " Def "
#define OLED_RENDER_LAYER_NUMBER      " Num "
#define OLED_RENDER_LAYER_NAVIGATION  " Nav "
#define OLED_RENDER_LAYER_FUNCTION    " Fun "
#define OLED_RENDER_LAYER_MOUSE       " Mou "
#define OLED_RENDER_LAYER_ADJUST      " Adj "

#define KEYLOG_LEN 5