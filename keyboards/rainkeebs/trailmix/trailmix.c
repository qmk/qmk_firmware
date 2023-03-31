#include "quantum.h"
#include "trailmix.h"

bool encoder_update_kb (uint8_t index, bool clockwise)
{
  switch (get_highest_layer (layer_state))
    {
    case _BASE:
      if (index == 0)
	{
	  if (clockwise)
	    {
	      tap_code (KC_VOLU);
	    }
	  else
	    {
	      tap_code (KC_VOLD);
	    }
	}
      else if (index == 1)
	{
	  if (clockwise)
	    {
	      tap_code (KC_MS_WH_DOWN);
	    }
	  else
	    {
	      tap_code (KC_MS_WH_UP);
	    }
	}
      break;
    case _RAISE:
      if (index == 0)
	{
	  if (clockwise)
	    {
	      tap_code (KC_MNXT);
	    }
	  else
	    {
	      tap_code (KC_MPRV);
	    }
	}
      else if (index == 1)
	{
	  if (clockwise)
	    {
	      tap_code (KC_WH_R);
	    }
	  else
	    {
	      tap_code (KC_WH_L);
	    }
	}
      break;
    case _LOWER:
      if (index == 0)
	{
	  if (clockwise)
	    {
	      tap_code (KC_PGUP);
	    }
	  else
	    {
	      tap_code (KC_PGDN);
	    }
	}
      else if (index == 1)
	{
	  if (clockwise)
	    {
	      tap_code (KC_END);
	    }
	  else
	    {
	      tap_code (KC_HOME);
	    }
	}
      break;
    case _ADJUST:
      if (index == 0)
	{
	  if (clockwise)
	    {
	      tap_code (KC_MS_RIGHT);
	    }
	  else
	    {
	      tap_code (KC_MS_LEFT);
	    }
	}
      else if (index == 1)
	{
	  if (clockwise)
	    {
	      tap_code (KC_MS_DOWN);
	    }
	  else
	    {
	      tap_code (KC_MS_UP);
	    }
	}
      break;
    }
  return true;
}
