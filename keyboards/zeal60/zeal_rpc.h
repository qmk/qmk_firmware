#ifndef ZEAL_RPC_H
#define ZEAL_RPC_H

#include "zeal_color.h"

#define PROTOCOL_VERSION 0x0001

enum
{
	id_protocol_version = 0x01, // always 0x01
	id_keymap_keycode_load,
	id_keymap_keycode_save,
	id_keymap_default_save,
	id_backlight_config_set_flags,
	id_backlight_config_set_alphas_mods,
	id_backlight_set_key_color,

	id_unhandled = 0xFF,
};

#if defined(__GNUC__)
#define PACKED __attribute__ ((__packed__))
#else
#define PACKED
#endif

#if defined(_MSC_VER)
#pragma pack( push, 1 )
#endif

typedef struct PACKED
{
	uint16_t version;
} msg_protocol_version;

typedef struct PACKED
{
	uint8_t layer;
	uint8_t row;
	uint8_t col;
	uint16_t keycode;
} msg_keymap_keycode_load;

typedef struct PACKED
{
	uint8_t layer;
	uint8_t row;
	uint8_t col;
	uint16_t keycode;
} msg_keymap_keycode_save;

typedef struct PACKED
{
	uint16_t flags;
} msg_backlight_config_set_flags;

typedef struct PACKED
{
	uint16_t alphas_mods[5];
} msg_backlight_config_set_alphas_mods;

typedef struct PACKED
{
	uint8_t row;
	uint8_t col;
	HSV hsv;
} msg_backlight_set_key_color;

#if defined(_MSC_VER)
#pragma pack( pop )
#endif

#endif // ZEAL_RPC_H
