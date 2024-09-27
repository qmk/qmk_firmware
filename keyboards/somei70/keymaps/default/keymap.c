// Copyright 2024 James Gzowski
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

enum custom_layer {
	_LAYERA,
	_LAYERB,
	_LAYERC
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_LAYERA] = LAYOUT_5x15(
	KC_ESC ,KC_1	,KC_2	,KC_3	,KC_4	,KC_5	,KC_6	,KC_7	,KC_8	,KC_9	,KC_0	,KC_MINS,KC_EQL	,KC_BSPC,
	KC_TAB ,KC_Q    ,KC_W   ,KC_E   ,KC_R   ,KC_T   ,KC_Y   ,KC_U   ,KC_I   ,KC_O   ,KC_P   ,KC_LBRC,KC_RBRC,KC_BSLS,
	KC_CAPS,KC_A	,KC_S	,KC_D	,KC_F	,KC_G	,KC_H	,KC_J	,KC_K	,KC_L	,KC_SCLN,KC_QUOT,KC_GRV	, KC_DEL, KC_PGUP,
	KC_LSFT,KC_Z	,KC_X	,KC_C	,KC_V	,KC_B	,KC_N	,KC_M	,KC_COMM,KC_DOT ,KC_SLSH,KC_RSFT,KC_INS , KC_UP , KC_PGDN,
	KC_LCTL,KC_LGUI ,KC_LALT	,KC_SPC ,KC_MUTE,KC_ENT		,KC_RALT,MO(_LAYERB)	,KC_RCTL,KC_LEFT,KC_DOWN, KC_RGHT
),
	[_LAYERB] = LAYOUT_5x15(
	KC_ESC ,KC_F1   ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  ,KC_F6  ,KC_F7  ,KC_F8  ,KC_F9  ,KC_F10 ,KC_F11 ,KC_F12 ,KC_PSCR,
	KC_TAB ,RGB_MOD ,RGB_VAD,RGB_VAI,RGB_SPD,RGB_SPI,RGB_HUD,RGB_HUI,RGB_SAD,RGB_SAI,KC_P   ,KC_LBRC,KC_RBRC,KC_BSLS,
	KC_CAPS,KC_A    ,KC_S   ,KC_D   ,KC_F   ,KC_G   ,KC_H   ,KC_J   ,KC_K   ,KC_L   ,KC_SCLN,KC_QUOT,KC_GRV , KC_DEL, KC_PGUP,
	KC_LSFT,KC_Z    ,KC_X   ,KC_C   ,KC_V   ,KC_B   ,KC_N   ,KC_M   ,KC_COMM,KC_DOT ,KC_SLSH,KC_RSFT,KC_INS , KC_UP , KC_PGDN,
	KC_LCTL,KC_LGUI ,KC_LALT        ,KC_SPC ,RGB_TOG,KC_ENT         ,KC_RALT,_______	,KC_RCTL,KC_LEFT,KC_DOWN, KC_RGHT
),
	[_LAYERC] = LAYOUT_5x15(
	KC_ESC ,KC_F1   ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  ,KC_F6  ,KC_F7  ,KC_F8  ,KC_F9  ,KC_F10 ,KC_F11 ,KC_F12 ,KC_PSCR,
	KC_TAB ,RGB_MOD ,RGB_VAD,RGB_VAI,RGB_SPD,RGB_SPI,RGB_HUD,RGB_HUI,RGB_SAD,RGB_SAI,KC_P   ,KC_LBRC,KC_RBRC,KC_BSLS,
	KC_CAPS,KC_A    ,KC_S   ,KC_D   ,KC_F   ,KC_G   ,KC_H   ,KC_J   ,KC_K   ,KC_L   ,KC_SCLN,KC_QUOT,KC_GRV , KC_DEL, KC_PGUP,
	KC_LSFT,KC_Z    ,KC_X   ,KC_C   ,KC_V   ,KC_B   ,KC_N   ,KC_M   ,KC_COMM,KC_DOT ,KC_SLSH,KC_RSFT,KC_INS , KC_UP , KC_PGDN,
	KC_LCTL,KC_LGUI ,KC_LALT        ,KC_SPC ,RGB_TOG,KC_ENT         ,KC_RALT,_______	,KC_RCTL,KC_LEFT,KC_DOWN, KC_RGHT
)
};

#ifdef OLED_ENABLE
static uint8_t oled_mode = 0;
static uint8_t esc_press_count = 0;
static uint16_t esc_timer = 0;

//Stats display
void render_stats(void)
{
	char wpm_str[10];
	snprintf(wpm_str, sizeof(wpm_str), "WPM: %03u", get_current_wpm());
	oled_write_ln(wpm_str, false);
	if (host_keyboard_led_state().caps_lock)
	{
		oled_write_P(PSTR("CAPS: On   "), false);
	}
	else
	{
		oled_write_P(PSTR("CAPS: Off  "), false);
	}

	if (keymap_config.nkro)
	{
		oled_write_ln("NKRO: On", false);
	}
	else
	{
		oled_write_ln("NKRO: Off", false);
	}

	uint8_t brightness = rgblight_get_val();
	char brightness_str[255];
	snprintf(brightness_str, sizeof(brightness_str), "LED Brightness: %03u", brightness);
	oled_write_ln(brightness_str, false);
	oled_write_ln(PSTR("P: 0x6F64  V: 0x73CA"), false);
}

//Static images
static void render_caps(void)
{
	static
	const char PROGMEM my_caps[] = { 0, 128, 192, 192, 248, 120, 8, 8, 24, 24, 48, 96, 96, 176, 24, 12, 4, 6, 6, 30, 60, 48, 48, 240, 240, 16, 16, 16, 16, 16, 16, 16, 16, 16, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 16, 16, 16, 144, 208, 208, 248, 120, 24, 24, 24, 24, 48, 96, 96, 176, 24, 12, 4, 6, 6, 30, 60, 48, 48, 240, 224, 0, 0, 0, 0, 0, 0, 0,
		0, 7, 31, 56, 64, 128, 128, 128, 192, 192, 192, 224, 192, 225, 255, 240, 240, 128, 128, 64, 64, 48, 24, 7, 7, 6, 4, 140, 216, 120, 48, 0, 0, 0, 128, 128, 128, 128, 128, 0, 0, 0, 240, 248, 12, 12, 12, 12, 12, 28, 56, 0, 0, 240, 248, 156, 12, 12, 12, 12, 156, 248, 240, 0, 0, 248, 252, 156, 12, 12, 12, 12, 152, 240, 0, 0, 32, 112, 216, 140, 140, 140, 12, 12, 4, 0, 0, 0, 0, 128, 128, 128, 128, 128, 0, 0, 0, 7, 31, 56, 64, 128, 128, 128, 192, 192, 192, 224, 192, 225, 255, 240, 240, 128, 128, 64, 64, 48, 24, 7, 7, 6, 4, 140, 216, 120, 48, 0,
		0, 224, 240, 24, 4, 3, 1, 0, 0, 0, 0, 6, 255, 135, 7, 15, 31, 17, 49, 32, 32, 32, 96, 224, 224, 32, 48, 17, 27, 14, 4, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 15, 31, 48, 48, 48, 48, 48, 56, 28, 0, 0, 63, 63, 3, 1, 1, 1, 1, 3, 63, 63, 0, 0, 63, 63, 3, 3, 3, 3, 3, 1, 0, 0, 0, 16, 48, 48, 49, 49, 49, 27, 14, 4, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 224, 240, 24, 4, 3, 1, 0, 0, 0, 0, 6, 255, 135, 7, 15, 31, 17, 49, 32, 32, 32, 96, 224, 224, 32, 48, 17, 27, 14, 4, 0,
		0, 3, 7, 6, 30, 60, 48, 32, 48, 48, 24, 12, 7, 7, 12, 16, 32, 96, 96, 120, 124, 60, 12, 15, 15, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 11, 15, 14, 30, 60, 48, 32, 48, 48, 24, 12, 7, 7, 12, 16, 32, 96, 96, 120, 124, 60, 12, 15, 7, 0, 0, 0, 0, 0, 0, 0,
	};

	oled_write_raw_P(my_caps, sizeof(my_caps));
}

static void render_logo(void)
{
	static
	const char PROGMEM my_logo[] = { 0, 128, 192, 192, 248, 120, 8, 8, 24, 24, 48, 96, 96, 176, 24, 12, 4, 6, 6, 30, 60, 48, 48, 240, 240, 16, 16, 16, 16, 16, 16, 16, 16, 16, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 144, 16, 16, 16, 144, 208, 208, 248, 120, 24, 24, 24, 24, 48, 96, 96, 176, 24, 12, 4, 6, 6, 30, 60, 48, 48, 240, 224, 0, 0, 0, 0, 0, 0, 0,
		0, 7, 31, 56, 64, 128, 128, 128, 192, 192, 192, 224, 192, 225, 255, 240, 240, 128, 128, 64, 64, 48, 24, 7, 7, 6, 4, 140, 216, 120, 48, 0, 48, 120, 204, 204, 204, 204, 204, 140, 8, 0, 0, 240, 248, 12, 12, 12, 12, 12, 248, 240, 0, 0, 248, 252, 24, 48, 96, 96, 48, 24, 252, 248, 0, 0, 248, 252, 140, 140, 140, 12, 8, 0, 0, 252, 252, 0, 0, 8, 12, 12, 12, 12, 252, 248, 0, 0, 240, 248, 12, 12, 140, 76, 248, 240, 0, 7, 31, 56, 64, 128, 128, 128, 192, 192, 192, 224, 192, 225, 255, 240, 240, 128, 128, 64, 64, 48, 24, 7, 7, 6, 4, 140, 216, 120, 48, 0,
		0, 224, 240, 24, 4, 3, 1, 0, 0, 0, 0, 6, 255, 135, 7, 15, 31, 17, 49, 32, 32, 32, 96, 224, 224, 32, 48, 17, 27, 14, 4, 0, 16, 48, 48, 48, 48, 48, 48, 63, 15, 0, 0, 15, 31, 48, 48, 48, 48, 48, 31, 15, 0, 0, 63, 31, 0, 0, 0, 0, 0, 0, 31, 63, 0, 0, 31, 63, 49, 49, 49, 48, 16, 0, 0, 63, 63, 0, 0, 0, 0, 0, 0, 0, 63, 63, 0, 0, 15, 31, 50, 49, 48, 48, 31, 15, 0, 224, 240, 24, 4, 3, 1, 0, 0, 0, 0, 6, 255, 135, 7, 15, 31, 17, 49, 32, 32, 32, 96, 224, 224, 32, 48, 17, 27, 14, 4, 0,
		0, 3, 7, 6, 30, 60, 48, 32, 48, 48, 24, 12, 7, 7, 12, 16, 32, 96, 96, 120, 124, 60, 12, 15, 15, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 11, 15, 14, 30, 60, 48, 32, 48, 48, 24, 12, 7, 7, 12, 16, 32, 96, 96, 120, 124, 60, 12, 15, 7, 0, 0, 0, 0, 0, 0, 0,
	};

	oled_write_raw_P(my_logo, sizeof(my_logo));
}

//Render chosen display
void render_oled_display(void)
{
	if (oled_mode == 0)
	{
		if (host_keyboard_led_state().caps_lock)
		{
			render_caps();
		}
		else
		{
			render_logo();
		}
	}
	else if (oled_mode == 1)
	{
		render_stats();
	}
}

//Rotate 180 degrees
oled_rotation_t oled_init_user(oled_rotation_t rotation)
{
	return OLED_ROTATION_180;
}

bool oled_task_user(void)
{
	render_oled_display();
	return false;
}
#endif

//Record keypress
bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
	switch (keycode)
	{
		case KC_ESC:
			if (record->event.pressed)
			{
				if (timer_elapsed(esc_timer) > 250)
				{
					esc_press_count = 0;
				}

				esc_press_count++;
				esc_timer = timer_read();

				if (esc_press_count == 3)
				{
					oled_clear();
					oled_mode = (oled_mode == 0) ? 1 : 0;
					esc_press_count = 0;
				}
			}

			break;
	}

	return true;
}
