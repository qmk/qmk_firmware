#pragma once
#include "oled_driver.h"

bool process_record_user_oled(uint16_t keycode, keyrecord_t *record);
//void oled_dice(int num);

static const char PROGMEM shift_key[] = {210,211,32,0};
static const char PROGMEM win_key[] = {147,148,32,0};
static const char PROGMEM alt_key[] = {146,32,0};
static const char PROGMEM ctrl_key[] = {127,32,0};

static const char PROGMEM logo[] = {
  0x20,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x20,0x20,0x20,0xb8,0xb9,0xba,0xbb,0xbc,0xbd,0xbe,0x20,
  0x20,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0x20,0x20,0x20,0xd8,0xd9,0xda,0xdb,0xdc,0xdd,0xde,0x20,
  0x20,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0
  };

#ifdef OLED_DISPLAY_128X64
#    define OLED_RENDER_KEYLOGGER "History: "

#    define OLED_RENDER_LAYOUT_NAME    "Layout: "
#    define OLED_RENDER_LAYOUT_QWERTY  "Qwerty"
#    define OLED_RENDER_LAYOUT_COLEMAK "Colemak"
#    define OLED_RENDER_LAYOUT_SYMNUM "Sym Num"
#    define OLED_RENDER_LAYOUT_SHORTCUT "Shortcut"
#    define OLED_RENDER_LAYOUT_GAMING "GAME ZONE"
//#    define OLED_RENDER_LAYOUT_WARHAMMER "WAAAAGH!!"
#    define OLED_RENDER_LAYOUT_NAVIGATION "Navigate"
//#    define OLED_RENDER_LAYOUT_RPG "Roll Dice"

#    define OLED_RENDER_LOCK_NAME "Lock: "
#    define OLED_RENDER_LOCK_NUML "NUML"
#    define OLED_RENDER_LOCK_CAPS "CAPS"
#    define OLED_RENDER_LOCK_SCLK "SCLK"

#    define OLED_RENDER_MODS_NAME "Mods: "
//#    define OLED_RENDER_MODS_SFT  "Sft"
//#    define OLED_RENDER_MODS_CTL  "Ctl"
//#    define OLED_RENDER_MODS_ALT  "Alt"
//#    define OLED_RENDER_MODS_GUI  "GUI"

#endif
/*
void render_custom_image(void) {
  static const char PROGMEM custom_image[] = { 
// 'dice_magic', 128x64px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x80, 0x80, 0xc0, 0x20, 0x00, 0x00, 
0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xa0, 0x20, 0x20, 0x20, 0x20, 
0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xa0, 
0xa0, 0x60, 0xe0, 0xc0, 0x80, 0x00, 0xb0, 0x60, 0x30, 0x28, 0x40, 0x40, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x80, 0x70, 0x2c, 0x20, 0x20, 0x00, 0x80, 0xc0, 0xa0, 0x80, 0x80, 0x80, 0x40, 0x40, 0x40, 
0x40, 0x80, 0x80, 0x00, 0x80, 0x80, 0x40, 0x40, 0x40, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x20, 0x60, 0x99, 0x86, 0x02, 0x80, 0x60, 0x18, 0x26, 0x41, 0xc0, 0x40, 0x41, 0x01, 0x02, 0x02, 
0x03, 0x04, 0x04, 0x00, 0x00, 0xc0, 0x20, 0x18, 0x04, 0x03, 0x00, 0x00, 0x03, 0x1c, 0x60, 0x80, 
0x80, 0x40, 0x40, 0x20, 0x20, 0x10, 0x10, 0x08, 0x08, 0x04, 0x04, 0x02, 0x02, 0x01, 0x01, 0x00, 
0x00, 0x00, 0x07, 0x78, 0xe1, 0x07, 0x0c, 0x18, 0x68, 0xc8, 0x44, 0x44, 0x44, 0x44, 0x64, 0x42, 
0xc2, 0x43, 0x22, 0x03, 0x01, 0x01, 0x01, 0x01, 0x00, 0xe0, 0x40, 0x20, 0x01, 0x02, 0x00, 0x00, 
0x80, 0x80, 0x80, 0x41, 0x41, 0x42, 0x42, 0x84, 0x84, 0x88, 0x88, 0x90, 0x10, 0x30, 0x28, 0x4f, 
0x44, 0x84, 0x82, 0x02, 0x03, 0x03, 0x04, 0x04, 0x08, 0x38, 0xd0, 0x10, 0x28, 0x24, 0x40, 0x40, 
0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x20, 0x30, 0x28, 0x24, 0x20, 
0x00, 0x00, 0x00, 0x00, 0x03, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 
0x80, 0x60, 0x18, 0x04, 0x03, 0x80, 0x40, 0x20, 0x10, 0x10, 0x08, 0x04, 0x02, 0x02, 0x01, 0xff, 
0x01, 0x81, 0x82, 0x02, 0x04, 0x08, 0x08, 0x90, 0xa0, 0x20, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x07, 0x7c, 0xc0, 0x00, 0x00, 0x00, 0x03, 0x04, 0x18, 0x30, 0xe0, 0xa0, 
0x10, 0x11, 0x10, 0x08, 0x88, 0x88, 0x44, 0x26, 0x25, 0x04, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 
0x01, 0x02, 0x82, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x02, 0x02, 0x1c, 0x64, 0x04, 
0x08, 0x08, 0x10, 0x11, 0x21, 0x22, 0x22, 0xc4, 0x44, 0x88, 0x88, 0x10, 0x10, 0x30, 0x30, 0x48, 
0x48, 0x88, 0x88, 0x04, 0x04, 0x06, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0xa4, 0x24, 0x24, 0x04, 0x84, 0x24, 0xa4, 0x24, 0x04, 0x04, 0x24, 0xa4, 0xe4, 0x5c, 0x24, 0x13, 
0x08, 0x08, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
0x00, 0x7f, 0x7f, 0x06, 0x06, 0x18, 0x18, 0x61, 0x61, 0x1e, 0x1e, 0x00, 0x00, 0x01, 0x01, 0x02, 
0x04, 0x04, 0x08, 0x08, 0x10, 0x20, 0x3f, 0xf8, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x81, 
0x82, 0x8e, 0x91, 0xe1, 0x80, 0x81, 0x82, 0x40, 0x40, 0x40, 0x40, 0x20, 0x20, 0x20, 0x30, 0x18, 
0x16, 0x11, 0x08, 0x18, 0x18, 0x28, 0x24, 0x44, 0x44, 0x04, 0x08, 0x08, 0x08, 0x0c, 0x0c, 0x0a, 
0x12, 0x30, 0x30, 0x10, 0x10, 0x20, 0x20, 0x23, 0x20, 0x20, 0x40, 0x41, 0x41, 0x42, 0x42, 0x42, 
0x84, 0x84, 0x88, 0x89, 0x91, 0x92, 0xa2, 0xa4, 0x24, 0x04, 0x84, 0x24, 0xa4, 0x24, 0x04, 0x04, 
0x24, 0x25, 0x24, 0x20, 0x20, 0x25, 0x24, 0x24, 0x20, 0x20, 0x24, 0x25, 0x27, 0x3a, 0x24, 0xc8, 
0x10, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
0x00, 0x78, 0x78, 0x86, 0x86, 0x86, 0x86, 0x86, 0x86, 0x78, 0x78, 0x00, 0x00, 0x80, 0x80, 0x40, 
0x20, 0x20, 0x10, 0x10, 0x08, 0x04, 0xfc, 0x1f, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x81, 
0x41, 0x71, 0x89, 0x87, 0x01, 0x81, 0x41, 0x02, 0x02, 0x02, 0x02, 0x04, 0x04, 0x04, 0x0c, 0x18, 
0x68, 0x88, 0x10, 0x18, 0x18, 0x14, 0x24, 0x22, 0x22, 0x20, 0x10, 0x10, 0x10, 0x30, 0x30, 0x50, 
0x48, 0x0c, 0x0c, 0x08, 0x08, 0x04, 0x04, 0xc4, 0x04, 0x04, 0x02, 0x82, 0x82, 0x42, 0x42, 0x42, 
0x21, 0x21, 0x11, 0x91, 0x89, 0x49, 0x45, 0x25, 0x24, 0x20, 0x20, 0x25, 0x24, 0x24, 0x20, 0x21, 
0x00, 0x00, 0x00, 0x00, 0xc0, 0xa0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 
0x01, 0x06, 0x18, 0x20, 0xc0, 0x01, 0x02, 0x04, 0x08, 0x08, 0x10, 0x20, 0x40, 0x40, 0x80, 0xff, 
0x80, 0x80, 0x40, 0x41, 0x21, 0x11, 0x11, 0x09, 0x05, 0x04, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0xe0, 0x3e, 0x03, 0x00, 0x00, 0x00, 0xc0, 0x20, 0x18, 0x0c, 0x07, 0x05, 
0x08, 0x88, 0x08, 0x10, 0x11, 0x11, 0x22, 0x64, 0xa4, 0x20, 0x40, 0x40, 0x40, 0x80, 0x80, 0x80, 
0x80, 0x40, 0x41, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x40, 0x38, 0x26, 0x20, 
0x10, 0x10, 0x08, 0x88, 0x84, 0x44, 0x44, 0x23, 0x22, 0x11, 0x11, 0x08, 0x08, 0x0c, 0x0c, 0x12, 
0x12, 0x11, 0x11, 0x20, 0x20, 0x60, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x04, 0x06, 0x99, 0x61, 0x40, 0x01, 0x06, 0x18, 0x64, 0x82, 0x03, 0x02, 0x82, 0x80, 0x40, 0x40, 
0xc0, 0x20, 0x20, 0x00, 0x00, 0x03, 0x04, 0x18, 0x20, 0xc0, 0x00, 0x00, 0xc0, 0x38, 0x06, 0x01, 
0x01, 0x02, 0x02, 0x04, 0x04, 0x08, 0x08, 0x10, 0x10, 0x20, 0x20, 0x40, 0x40, 0x80, 0x80, 0x00, 
0x00, 0x00, 0xe0, 0x1e, 0x87, 0xe0, 0x30, 0x18, 0x16, 0x13, 0x22, 0x22, 0x22, 0x22, 0x26, 0x42, 
0x43, 0xc2, 0x44, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x07, 0x02, 0x04, 0x80, 0x40, 0x00, 0x00, 
0x01, 0x01, 0x01, 0x82, 0x82, 0x42, 0x42, 0x21, 0x21, 0x11, 0x11, 0x09, 0x08, 0x0c, 0x14, 0xf2, 
0x22, 0x21, 0x41, 0x40, 0xc0, 0xc0, 0x20, 0x20, 0x10, 0x1c, 0x0b, 0x08, 0x14, 0x24, 0x02, 0x02, 
0x04, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x02, 0x04, 0x0c, 0x14, 0x24, 0x04, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x01, 0x01, 0x03, 0x04, 0x00, 0x00, 
0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x05, 0x04, 0x04, 0x04, 0x04, 
0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 
0x05, 0x06, 0x07, 0x03, 0x01, 0x00, 0x0d, 0x06, 0x0c, 0x14, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x01, 0x0e, 0x34, 0x04, 0x04, 0x00, 0x01, 0x03, 0x05, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 
0x02, 0x01, 0x01, 0x00, 0x01, 0x01, 0x02, 0x02, 0x02, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
  oled_write_raw_P(custom_image, sizeof(custom_image));
}
#endif*/
/*
static void render_status_page(void){
	static char roll_str[10];
	// Write roll
	
}*/