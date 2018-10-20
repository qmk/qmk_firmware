#include QMK_KEYBOARD_H
#include "keymap.h"

enum marianas_layers {
  QWERTY,
/*
  COLEMAK,
  DVORAK,
*/
  NAV_CLUSTER,
  GAMING,
  SQLMACROS,
  SQLNAMES,
  FN_LAYER
};

enum sql_macros {
  S_LFTJN = SAFE_RANGE, // L
  S_INRJN, // I
  S_SLCT,  // S
  S_FROM,  // F
  S_DSNCT, // D
  S_ORDER, // O
  S_WHERE, // W
  S_ALTER, // Esc
  S_ASTRK, // *

  TD_A,
  TD_B,
  TD_C, // Corp, Corporation, Company
  TD_D, // Distribution, Dist, Distributor
  TD_E,
  TD_F,
  TD_G, // GlobalLookup
  TD_H,
  TD_I, // Instance, Item
  TD_J,
  TD_K,
  TD_L,
  TD_M,
  TD_N, // NadRate
  TD_O,
  TD_P, // Product, Person,
  TD_Q, // Darden
  TD_R,
  TD_S, // Supplier, Step
  TD_T, // Task, Type
  TD_U,
  TD_V,
  TD_W, // Workflow,
  TD_X,
  TD_Y,
  TD_Z,
  TD_BSPC,
  TD_ENT,
  TD_ESC
};

uint16_t *macroTaps = 0;

char *tableNameList = 0;

uint8_t *charCount = 0;
uint8_t countPointer = 0;

bool shifted = false;

bool sendAbbr = false;


void initStringData(void)
{
  if (macroTaps == 0)
  {
    macroTaps = malloc(macroTapsLen*sizeof(uint16_t));
    for(int i = 0; i < macroTapsLen; i++)
    {
      macroTaps[i] = 0;
    }
  }
  if (tableNameList == 0)
  {
    tableNameList = malloc(tableNameListLen*sizeof(char));
    for(int i = 0; i < tableNameListLen; i++)
    {
      tableNameList[i] = 0;
    }
  }
  if (charCount == 0)
  {
    charCount = malloc(charCountLen*sizeof(uint8_t));
    for (int i = 0; i < charCountLen; i++)
    {
      charCount[i] = 0;
    }
  }
}


uint32_t layer_state_set_user(uint32_t state)
{
  switch (biton32(state))
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
      rgblight_setrgb(0x00, 0xFF, 0x80);
      break;
    case SQLNAMES:
      rgblight_mode(1);
      rgblight_setrgb(0x80, 0xFF, 0x00);
      break;
    case FN_LAYER:
      rgblight_mode(1);
      rgblight_setrgb(0x00, 0x80, 0xFF);
      break;
  }
  return state;
}

bool containsCode(uint16_t kc)
{
  for (int i = 0; i < macroTapsLen && macroTaps[i] > 0; i++)
  {
    if (macroTaps[i] == kc) return true;
  }
  return false;
}

bool lastCodeIs(uint16_t kc)
{
  for (int i = 0; i < macroTapsLen-1 && macroTaps[i] > 0; i++)
  {
    if (macroTaps[i] == kc && macroTaps[i+1] == 0) return true;
  }
  return false;
}

bool last2CodeAre(uint16_t kc)
{
  for (int i = 0; i < macroTapsLen-2 && macroTaps[i] > 0; i++)
  {
    if (macroTaps[i] == kc && macroTaps[i+1] == kc && macroTaps[i+2] == 0) return true;
  }
  return false;
}

bool last2CodesAre(uint16_t kc, uint16_t kc2)
{
  for (int i = 0; i < macroTapsLen-2 && macroTaps[i] > 0; i++)
  {
    if (macroTaps[i] == kc && macroTaps[i+1] == kc2 && macroTaps[i+2] == 0) return true;
  }
  return false;
}

void addKeyCode(uint16_t kc)
{
  int i = 0;
  while (i < macroTapsLen-2 && macroTaps[i] > 0) i++;
  if (macroTaps[i] == 0)
  {
    macroTaps[i] = kc;
    macroTaps[i+1] = 0;
  }
}

void eraseKeyCodes(void)
{
  int i = 0;
  while (i < macroTapsLen && macroTaps[i] > 0) macroTaps[i++] = 0;
}

void eraseCharCounts(void)
{
  int i = 0;
  while (i < charCountLen)
  {
    charCount[i] = 0;
  }
}

void printTableAbbreviation(void)
{
  initStringData();
  if (tableNameList[0] == 0)
  {
    return;
  }
  send_char(0x20);
  int i = 0;
  for (i = 0; i < tableNameListLen && tableNameList[i] > 0; i++)
  {
    if (tableNameList[i] >= 65 && tableNameList[i] <= 90)
    {
      send_char(tableNameList[i]+32);
    }
    else
    {
      send_char(tableNameList[i]);
    }
  }
  send_char(0x20);
}

void eraseTableAbbreviation(void)
{
  initStringData();
  for (int i = 0; i < tableNameListLen && tableNameList[i] > 0; i++)
  {
    tableNameList[i] = '\0';
  }
}

void printString(char* str)
{

  if (str[0] != '\0')
  {
    int i = 0;
    while (true)
    {
      if (str[i] == 0)
      {
        break;
      }
      send_char(str[i++]);
      charCount[countPointer]++;
    }
  }
}

void printStringAndQueueChar(char* str)
{
  initStringData();
  if (charCount[countPointer] != 0)
  {
    countPointer++;
  }
  sendAbbr = true;
  if (str[0] != '\0')
  {
    printString(str);

    for (int i = 0; i < tableNameListLen-1; i++)
    {
      if (tableNameList[i] == '\0')
      {
        tableNameList[i] = str[0];
        tableNameList[i+1] = '\0';
        break;
      }
      else if (i == tableNameListLen-2)
      {
        printTableAbbreviation();
        break;
      }
    }
    //for (i = 0; i < tableNameListLen && tableNameList[i] > 0; i++)
    //{
    //  send_char(tableNameList[i]);
    //}
    //send_string_P("Darden");
    //send_string_P(&myarray);
    //send_string_P(str);
  }
}

void ReplaceString(char *orig, char *repl)
{
  int i = 0;
  while((orig[i] != 0x0 && repl[i] != 0x0) && orig[i] == repl[i])
   i++;

  if(orig[i] != 0x0)
  {
    int o = i;
    while (orig[o++] != 0x0) {
      charCount[countPointer]--;
      register_code(KC_BSPC);
      unregister_code(KC_BSPC);
    }
  }
  printString(repl+i);
}

void deletePrev(void)
{
  for (int i = 0; i < charCount[countPointer]; i++)
  {
      register_code(KC_BSPC);
      unregister_code(KC_BSPC);
  }
  charCount[countPointer] = 0;
  countPointer--;
  int i = 1;
  for (;i < tableNameListLen-1; i++)
  {
    if (tableNameList[i] == 0x0)
    {
      break;
    }
  }
  tableNameList[i-1] = 0x0;
}

void processSmartMacroTap(uint16_t kc)
{
  initStringData();
  switch(kc)
  {
    case TD_C:
      if (containsCode(TD_D))
      {
        printString("ribution");
        printStringAndQueueChar("Center");
      }
      else if (last2CodeAre(TD_C))
      {
        ReplaceString("Corporation", "Contact");
      }
      else if(lastCodeIs(TD_C))
      {
        printString("oration");
      }
      else
      {
        printStringAndQueueChar("Corp");
      }
      break;
    case TD_D:
      if (last2CodeAre(TD_D))
      {
        ReplaceString("Distribution", "Distributor");
      }
      else if(lastCodeIs(TD_D))
      {
        printString("ribution");
      }
      else
      {
        printStringAndQueueChar("Dist");
      }
      break;
    case TD_G:
        printStringAndQueueChar("Global");
        printStringAndQueueChar("Lookup");
      break;
    case TD_I:
      if (containsCode(TD_W))
        printStringAndQueueChar("Instance");
      else
        printStringAndQueueChar("Item");
      break;
    case TD_N:
      printStringAndQueueChar("NadRate");
      break;
    case TD_P:
      if (last2CodesAre(TD_D, TD_C))
      {
        ReplaceString("DistributionCenter", "DistCenter");
        printStringAndQueueChar("Pricing");
      }
      else if (last2CodeAre(TD_P))
      {
      }
      else if(lastCodeIs(TD_P))
      {
        ReplaceString("Product", "Person");
      }
      else
      {
        printStringAndQueueChar("Product");
      }
      break;
    case TD_Q:
      printStringAndQueueChar("Darden");
      break;
    case TD_S:
      if (containsCode(TD_W))
        if (containsCode(TD_S) || containsCode(TD_D))
          printStringAndQueueChar("Step");
        else
          printStringAndQueueChar("Session");
      else
        printStringAndQueueChar("Supplier");
      break;
    case TD_T:
      if (containsCode(TD_W))
        printStringAndQueueChar("Task");
      else
        printStringAndQueueChar("Type");
      break;
    case TD_W:
      printStringAndQueueChar("Workflow");
      break;
  }
  addKeyCode(kc);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  if (record->event.pressed)
  {
    switch (keycode)
    {
      case KC_LSPO:
      case KC_RSPC:
        shifted = true;
        return true;

      case S_LFTJN: SEND_STRING("LEFT JOIN"); return false;
      case S_INRJN: SEND_STRING("INNER JOIN "); return false;
      case S_SLCT:  SEND_STRING("SELECT "); return false;
      case S_FROM:  SEND_STRING("FROM "); return false;
      case S_DSNCT: SEND_STRING("DISTINCT "); return false;
      case S_ORDER: SEND_STRING("ORDER "); return false;
      case S_WHERE: SEND_STRING("WHERE "); return false;
      case S_ALTER: SEND_STRING("ALTER SESSION SET CURRENT_SCHEMA = "); return false;
      case S_ASTRK: SEND_STRING("* "); return false;

      case KC_BSLS:
        initStringData();
        layer_on(SQLNAMES);
        return false;

      case TD_BSPC:
        if (!shifted){
          deletePrev();
        }
        else {
          register_code(KC_BSPC);
          unregister_code(KC_BSPC);
        }
        return false;

      case TD_A:
      case TD_B:
      case TD_C:
      case TD_D:
      case TD_E:
      case TD_F:
      case TD_G:
      case TD_H:
      case TD_I:
      case TD_J:
      case TD_K:
      case TD_L:
      case TD_M:
      case TD_N:
      case TD_O:
      case TD_P:
      case TD_Q:
      case TD_R:
      case TD_S:
      case TD_T:
      case TD_U:
      case TD_V:
      case TD_W:
      case TD_X:
      case TD_Y:
      case TD_Z:
        processSmartMacroTap(keycode);
        return false;

      case TD_ENT:
        printTableAbbreviation();
      case TD_ESC:
        eraseKeyCodes();
        eraseTableAbbreviation();
        layer_off(SQLNAMES);
        return true;
    }
  }
  else
  {
    switch (keycode)
    {

      case KC_BSLS:
        if (macroTaps[0] == 0)
        {
          SEND_STRING("\\");
          layer_off(SQLNAMES);
        }
        return true;
      case KC_LSPO:
      case KC_RSPC:
        shifted = false;
        return true;
    }
  }
  return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [QWERTY]=
    LAYOUT_60_ansi(
      ESCAP,  KC_1,  KC_2,  KC_3,  KC_4,  KC_5,  KC_6,  KC_7,  KC_8,  KC_9,  KC_0,  MNUS,  EQUL,  BACKSPC,
      KC_TAB,  KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,  KC_Y,  KC_U,  KC_I,  KC_O,  KC_P,  LBRC,  RBRC,  BSLASH,
      MO_FNLR,  KC_A,  KC_S,  KC_D,  KC_F,  KC_G,  KC_H,  KC_J,  KC_K,  KC_L,  COLN,  QUOT,  ENTER_OR_SQL,
      LEFTSHFT,  KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,  KC_N,  KC_M,  CMMA,  PRRD,  SLSH,  RIGHT_SHIFT__PAREN,
      CTLL,  WINL,  ALTL,  SPAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACE,  ALTR,  WINR,  APPR,  CTLR),

  [NAV_CLUSTER]=
    LAYOUT_60_ansi(
      _____,  PSCR,  SCRL,  PAUS,  NSRT,  HOME,  PGUP,  NMLK,  KSSH,  STAR,  KMIN,  ____,  ____,  ______,
      ______,  ____,  ____,  ____,  DELT,  END_,  PGDN,  KP_7,  KP_8,  KP_9,  PLUS,  ____,  ____,  _____,
      _______,  ____,  ____,  ____,  ____,  UPUP,  UPUP,  KP_4,  KP_5,  KP_6,  PLUS,  ____,  ___________,
      ________,  ____,  ____,  ____,  LEFT,  D_WN,  RGHT,  KP_1,  KP_2,  KP_3,  KNTR,  _________________,
      ____,  ____,  ____,  /*-----------------*/KC_KP_0/*-----------------*/,  KDOT,  KNTR,  ____,  ____),

  [GAMING]=
    LAYOUT_60_ansi(
      _____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ______,
      ______,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  _____,
         KCNO,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ___________,
      ________,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  _________________,
      ____,  KCNO,  ____,  /*------------------*/_____/*------------------*/,  ____,  KCNO,  ____,  QWRTY),

  [SQLMACROS]=
    LAYOUT_60_ansi(
      S_ALTER, ____, ____, ____, ____, ____, ____, ____, S_ASTRK, ____, ____, ____, ____,    ___________,
      ______,    ____, S_WHERE, ____, ____, ____, ____, ____, S_INRJN, S_ORDER, ____, ____, ____, ______,
      _______, KC_LBRC, S_SLCT, KC_PAST,S_FROM, ____, ____, ____, ____, S_LFTJN, ____, RBRC, ___________,
      ________,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  _________________,
      ____,  ____,  ____,  /*------------------*/_____/*------------------*/,  ____,  ____,  ____,  ____),

  [SQLNAMES]=
    LAYOUT_60_ansi(
      TD_ESC,    ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____,  ____, TD_BSPC,
      ________,   TD_Q,  TD_W,  TD_E,  TD_R,  TD_T,  TD_Y,  TD_U,  TD_I,  TD_O,  TD_P,  ____,  ____,  _____,
      ___________, TD_A,  TD_S,  TD_D,  TD_F,  TD_G,  TD_H,  TD_J,  TD_K,  TD_L,  ____,  ____,       TD_ENT,
      ___________,  TD_Z,  TD_X,  TD_C,  TD_V,  TD_B,  TD_N,  TD_M,  ____,  ____,  ____,  _________________,
      ____, ____, ____, /*----------------------*/TD_ENT/*-----------------------*/, ____, ____, ____, RESET),

  [FN_LAYER]=
    LAYOUT_60_ansi(
      KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL,
      KC_CAPSLOCK, KC_MPRV, KC_MPLY, KC_MNXT, LWIN(KC_R), ____, KC_CALC, KC_PGUP, KC_UP, KC_PGDN, KC_PSCR, KC_SLCK, KC_BRK, ____,
      ____, KC_VOLD, KC_MUTE, KC_VOLU, ____, ____, KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, KC_INS, KC_DEL, ____,
      ____, ____, ____, ____, ____, ____, KC_END, ____, QWRTY, NAVS, GAME, ____,
      ____, ____, ____, _________________, ____, KC_HYPR, KC_MEH, ____)
};
