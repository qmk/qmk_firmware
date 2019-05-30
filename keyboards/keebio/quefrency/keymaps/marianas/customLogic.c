#include QMK_KEYBOARD_H
#include "customLogic.h"
#include "keymap.h"
#include "keyDefinitions.h"
#include "relativity.h"
#include "timer.h"

static int16_t fnTimer = 0;

static uint16_t random_value = 26339;

uint32_t layer_state_set_user(uint32_t state)
{
  switch (biton32(state))
  {
    case QWERTY:
      rgblight_mode(9);
      break;
    case SQLMACROS:
      rgblight_mode(RGBLIGHT_MODE_RAINBOW_MOOD+2);
      break;
    case FN_LAYER:
      rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL+5);
      break;
  }
  return state;
}

#define colTimeout 250

static int16_t colonTimer = 0;

bool custom_keys(uint16_t keycode, keyrecord_t *record)
{
  if (record->event.pressed)
  {
    switch(keycode)
    {
      case SM_UP:
        for (int i = 0; i < 19; i++)
        {
          register_code(KC_UP);
          unregister_code(KC_UP);
        }
        register_code(KC_UP);
        return false;
      case SM_DN:
        for (int i = 0; i < 19; i++)
        {
          register_code(KC_DOWN);
          unregister_code(KC_DOWN);
        }
        register_code(KC_DOWN);
        return false;
      case KC_SCLN:

        if (colonTimer == 0 || TIMER_DIFF_16(timer_read(), colonTimer) >= colTimeout){
          register_code(KC_SCLN);
          unregister_code(KC_SCLN);
        }
        colonTimer = timer_read();
        return false;

    }
  }
  else
  {
    switch(keycode)
    {
      case SM_UP:
      unregister_code(KC_UP);
        return false;
      case SM_DN:
      unregister_code(KC_DOWN);
        return false;
      case KC_SCLN:
        return false;
    }
  }
  return true;
}


bool printSqlVerbs(uint16_t keycode, keyrecord_t *record)
{
  if (record->event.pressed)
  {
    switch (keycode)
    {
      case S_LFTJN:
        SEND_STRING("LEFT JOIN ");
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
      case S_NOT:
        SEND_STRING("NOT "); return false;
      case S_GROUP:
        SEND_STRING("GROUP BY "); return false;
      case S_COUNT:
        SEND_STRING("COUNT(1) "); return false;

    }
  }
  return true;
}


bool isFn = false;
bool didFn = false;

bool justGrv = false;

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
      case ESCAP:
        if (isShifted())
        {
                register_code(KC_GRV);
                justGrv = true;
                return false;
        }
	      return true;
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
      case ESCAP:
        if (justGrv)
        {
                unregister_code(KC_GRV);
                justGrv = false;
                return false;
        }
        return true;

    }
  }
  return true;
}

uint16_t getRand(void)
{
  uint16_t clockbyte=0;
  clockbyte = TCNT1 % 65536;
  uint16_t rval;
  random_value = ((random_value + randadd) * randmul) % randmod;
  rval = (random_value ^ clockbyte);
  return rval;
}

static bool numDiceEntered = false;
static uint16_t numDice = 0;

void printNumber(uint16_t roll)
{
  register_code (KC_1 + ((KC_0 + (roll+1)/10) - KC_1)%10);
  unregister_code (KC_1 + ((KC_0 + (roll+1)/10) - KC_1)%10);
  register_code (KC_1 + roll%10);
  unregister_code (KC_1 + roll%10);
  register_code(KC_ENTER);
  unregister_code (KC_ENTER);
}

bool process_dice_roll(uint16_t keycode, keyrecord_t *record)
{

  if (record->event.pressed)
  {

    if (numDiceEntered)
    {
      switch (keycode)
      {
        case R_D1:
          for (int i = 0; i < numDice; i++)
          {
            printNumber(getRand()%1);
          }
          numDiceEntered = false;
          return false;
        case R_D2:
          for (int i = 0; i < numDice; i++)
          {
            printNumber(getRand()%2);
          }
          numDiceEntered = false;
          return false;
        case R_D3:
          for (int i = 0; i < numDice; i++)
          {
            printNumber(getRand()%3);
          }
          numDiceEntered = false;
          return false;
        case R_D4:
          for (int i = 0; i < numDice; i++)
          {
            printNumber(getRand()%4);
          }
          numDiceEntered = false;
          return false;
        case R_D5:
          for (int i = 0; i < numDice; i++)
          {
            printNumber(getRand()%5);
          }
          numDiceEntered = false;
          return false;
        case R_D6:
          for (int i = 0; i < numDice; i++)
          {
            printNumber(getRand()%6);
          }
          numDiceEntered = false;
          return false;
        case R_D7:
          for (int i = 0; i < numDice; i++)
          {
            printNumber(getRand()%7);
          }
          numDiceEntered = false;
          return false;
        case R_D8:
          for (int i = 0; i < numDice; i++)
          {
            printNumber(getRand()%8);
          }
          numDiceEntered = false;
          return false;
        case R_D9:
          for (int i = 0; i < numDice; i++)
          {
            printNumber(getRand()%9);
          }
          numDiceEntered = false;
          return false;
        case R_D10:
          for (int i = 0; i < numDice; i++)
          {
            printNumber(getRand()%10);
          }
          numDiceEntered = false;
          return false;
        case R_D12:
          for (int i = 0; i < numDice; i++)
          {
            printNumber(getRand()%12);
          }
          numDiceEntered = false;
          return false;
        case R_D20:
          for (int i = 0; i < numDice; i++)
          {
            printNumber(getRand()%20);
          }
          numDiceEntered = false;
          return false;
      }
    }
    else
    {

      switch (keycode)
      {
        case R_D1:
          numDice = 1;
          numDiceEntered = true;
          return false;
        case R_D2:
          numDice = 2;
          numDiceEntered = true;
          return false;
        case R_D3:
          numDice = 3;
          numDiceEntered = true;
          return false;
        case R_D4:
          numDice = 4;
          numDiceEntered = true;
          return false;
        case R_D5:
          numDice = 5;
          numDiceEntered = true;
          return false;
        case R_D6:
          numDice = 6;
          numDiceEntered = true;
          return false;
        case R_D7:
          numDice = 7;
          numDiceEntered = true;
          return false;
        case R_D8:
          numDice = 8;
          numDiceEntered = true;
          return false;
        case R_D9:
          numDice = 9;
          numDiceEntered = true;
          return false;
        case R_D10:
          numDice = 10;
          numDiceEntered = true;
          return false;
      }
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
    handleSmartMacros(keycode, record) &&
    process_dice_roll(keycode, record) &&
    custom_keys(keycode, record);
}
