#pragma once

#include "t4corun.h"
#include "oled_driver.h"

#define OLED_RENDER_KEYLOCK_NAME      "Lock:"
#define OLED_RENDER_MODS_NAME         "Mods:"


#define OLED_RENDER_LAYOUT_NAME       "Lyout"
#define OLED_RENDER_LAYOUT_QWERTY     " QRTY"
#define OLED_RENDER_LAYOUT_COLEMAK_DH " cmDH"

#if defined(GAMELAYER_ENABLE)
# define OLED_RENDER_LAYOUT_GAMING    " Game"
#endif //GAMELAYER_ENABLE


#define OLED_RENDER_LAYER_NAME        "Layer"
#define OLED_RENDER_LAYER_BASE        " Def "
#define OLED_RENDER_LAYER_NUMBER      " Num "
#define OLED_RENDER_LAYER_NAVIGATION  " Nav "
#define OLED_RENDER_LAYER_CONFIG      " Con "

#if defined(MOUSELAYER_ENABLE)
# define OLED_RENDER_LAYER_MOUSE      " Mou "
#endif //MOUSELAYER_ENABLE

void              render_crkbd_logo(void);
void              render_default_layer_state(void);
void              render_layer_state(void);
void              render_keylock_status(void);
void              render_mod_status(void);
void              render_oled_main(void);
bool              oled_task_user(void);
oled_rotation_t   oled_init_user(oled_rotation_t rotation);