#include QMK_KEYBOARD_H
#include "customLogic.h"
#include "keymap.h"
#include "keyDefinitions.h"
#include "relativity.h"
#include "timer.h"

static int16_t fnTimer = 0;



layer_state_t layer_state_set_user(layer_state_t state)
{
  switch (get_highest_layer(state))
  {
    case QWERTY:
      rgblight_mode(9);
      break;
    case NAV_CLUSTER:
      rgblight_mode(29);
      break;
    case GAMING:
      rgblight_mode(26);
      break;
    case SQLMACROS:
      rgblight_mode(1);
      break;
    case FN_LAYER:
      rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL+5);
      break;
  }
  return state;
}



bool printSqlVerbs(uint16_t keycode, keyrecord_t *record)
{
  if (record->event.pressed)
  {
    switch (keycode)
    {
      case S_LFTJN:
        SEND_STRING("LEFT JOIN");
        activateRelativity();
        return false;
      case S_INRJN:
        SEND_STRING("INNER JOIN ");
        activateRelativity();
        return false;
      case S_SLCT:
        SEND_STRING("SELECT "); return
        false;
      case S_FROM:
        SEND_STRING("FROM "); return
        false;
      case S_DSNCT:
        SEND_STRING("DISTINCT "); return
        false;
      case S_ORDER:
        SEND_STRING("ORDER BY "); return
        false;
      case S_WHERE:
        SEND_STRING("WHERE "); return
        false;
      case S_ALTER:
        SEND_STRING("ALTER SESSION SET CURRENT_SCHEMA = SUPPLY;"); return false;
      case S_ASTRK:
        SEND_STRING("* "); return false;

    }
  }
  return true;
}


bool isFn = false;
bool didFn = false;


bool updateLayerState(uint16_t keycode, keyrecord_t *record)
{

  if (record->event.pressed)
  {
    switch (keycode)
    {
      case FN_QT:
        fnTimer = timer_read();
        layer_on(FN_LAYER);
        isFn = true;
        return false;
    }
    if (isFn)
    {
      didFn = true;
      return true;
    }
  }
  else
  {
    switch(keycode)
    {
      case FN_QT:
        layer_off(FN_LAYER);
        if (!didFn)
        {
          #if fnTimeout
          if (TIMER_DIFF_16(timer_read(), fnTimer) <= fnTimeout)
          {
            activateRelativity();
          }
          else
          {
            deactivateRelativity();
          }
          #else
          activateRelativity();
          #endif
        }
        didFn = false;
        isFn = false;
        return false;
    }
  }
  return true;
}



bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  return
    storeShiftState(keycode, record) &&
    printSqlVerbs(keycode, record) &&
    updateLayerState(keycode, record) &&
    handleSmartMacros(keycode, record);
}
