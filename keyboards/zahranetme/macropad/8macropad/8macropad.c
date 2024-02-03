#include "quantum.h"

void
eeconfig_init_kb (void)
{
#ifdef BACKLIGHT_ENABLE
  backlight_enable ();
  backlight_level (5);
#endif
#ifdef RGBLIGHT_ENABLE
  rgblight_enable ();
  rgblight_sethsv (0, 255, 255);
#ifdef RGBLIGHT_EFFECT_RAINBOW_SWIRL
  rgblight_mode (RGBLIGHT_MODE_RAINBOW_SWIRL + 2);
#endif
#endif

  eeconfig_update_kb (0);
  eeconfig_init_user ();
}

bool
encoder_update_kb (uint8_t index, bool clockwise)
{
  if (!encoder_update_user (index, clockwise))
	{
	  return false;
	}
  if (index == 0)
	{
	  if (clockwise)
		{
		  tap_code (KC_NO);
		}
	  else
		{
		  tap_code (KC_NO);
		}
	}
  else if (index == 1)
	{
	  if (clockwise)
		{
		  tap_code (KC_NO);
		}
	  else
		{
		  tap_code (KC_NO);
		}
	}
  else if (index == 2)
	{
	  if (clockwise)
		{
		  tap_code (KC_NO);
		}
	  else
		{
		  tap_code (KC_NO);
		}
	}
  return false;
}
