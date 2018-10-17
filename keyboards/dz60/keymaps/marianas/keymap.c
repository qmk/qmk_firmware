#include QMK_KEYBOARD_H

enum marianas_layers {
  QWERTY,
  COLEMAK,
  DVORAK,
  NAV_CLUSTER,
  RGB,
  MOUSE,
  GAMING,
  SQLMACROS,
  SQLNAMES,
  FN_LAYER,
  LAYER_SEL
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

  TD_C, // Corp, Corporation, Company
  TD_D, // Distribution, Dist, Distributor
  TD_G, // GlobalLookup
  TD_I, // Instance, Item
  TD_N, // NadRate
  TD_P, // Product, Person,
  TD_Q, // Darden
  TD_S, // Supplier, Step
  TD_T, // Task, Type
  TD_W, // Workflow,
  TD_BSPC,
  TD_ENT,
  TD_ESC
};

uint16_t *macroTaps = 0;

char *tableNameList = 0;

uint8_t *charCount = 0;
uint8_t countPointer = 0;

#define macroTapsLen 32
#define tableNameListLen 32
#define charCountLen 32

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
    case COLEMAK:
      rgblight_mode(27);
      break;
    case DVORAK:
      rgblight_mode(28);
      break;
    case NAV_CLUSTER:
      rgblight_mode(29);
      break;
    /*
      */
    case RGB:
      eeconfig_update_rgblight_default();
      break;
    case MOUSE:
      rgblight_mode(30);
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
    case LAYER_SEL:
      rgblight_mode(1);
      rgblight_setrgb(0xFF, 0x00, 0xFF);
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
    //for (i = 0; i < tableNameListLen && tableNameList[i] > 0; i++)
    //{
    //  send_char(tableNameList[i]);
    //}
    //send_string_P("Darden");
    //send_string_P(&myarray);
    //send_string_P(str);
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

      case TD_C:
      case TD_D:
      case TD_G:
      case TD_I:
      case TD_N:
      case TD_P:
      case TD_Q:
      case TD_S:
      case TD_T:
      case TD_W:
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
    LAYOUT(
      KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_NO, KC_BSPC,
      KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
      MO(FN_LAYER), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, LT(SQLMACROS,KC_ENT),
      KC_LSPO, KC_NO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSPC, KC_NO,
      KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_SPC, KC_SPC, KC_RALT, KC_LGUI, KC_NO, KC_APP, KC_RCTL),

  [COLEMAK]=
    LAYOUT(
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_LBRC, KC_RBRC, KC_BSLS,
      KC_TRNS, KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E, KC_I, KC_O, KC_QUOT, KC_ENT,
      KC_TRNS, KC_NO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_K, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_TRNS, KC_NO,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

  [DVORAK]=
    LAYOUT(
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LBRC, KC_RBRC, KC_NO, KC_BSPC,
      KC_TRNS, KC_QUOT, KC_COMM, KC_DOT, KC_P, KC_Y, KC_F, KC_G, KC_C, KC_R, KC_L, KC_SLSH, KC_EQL, KC_BSLS,
      KC_TRNS, KC_A, KC_O, KC_E, KC_U, KC_I, KC_D, KC_H, KC_T, KC_N, KC_S, KC_MINS, KC_TRNS,
      KC_TRNS, KC_NO, KC_SCLN, KC_Q, KC_J, KC_K, KC_X, KC_B, KC_M, KC_W, KC_V, KC_Z, KC_TRNS, KC_NO,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

  [NAV_CLUSTER]=
    LAYOUT(
      KC_TRNS, KC_PSCREEN, KC_SCROLLLOCK, KC_PAUSE, KC_INSERT, KC_HOME, KC_PGUP, KC_NUMLOCK, KC_KP_SLASH, KC_KP_ASTERISK, KC_KP_MINUS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DELETE, KC_END, KC_PGDOWN, KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_PLUS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_UP, KC_UP, KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_PLUS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_ENTER, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_KP_0, KC_KP_0, KC_KP_0, KC_KP_DOT, KC_KP_ENTER, KC_TRNS, KC_TRNS, KC_TRNS),

  [RGB]=
    LAYOUT(
      KC_TRNS, RGB_TOG, RGB_MOD, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_M_K, RGB_M_X, RGB_M_G, RGB_SPD, RGB_SPI, KC_TRNS, KC_TRNS,
      KC_TRNS, RGB_HUI, RGB_HUD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, RGB_SAI, RGB_SAD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, RGB_VAI, RGB_VAD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

  [MOUSE]=
    LAYOUT(
      KC_TRNS, KC_ACL0, KC_ACL1, KC_ACL2, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_WH_U, KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN3, KC_BTN1, KC_MS_U, KC_BTN2, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_WH_L, KC_WH_D, KC_WH_R, KC_TRNS, KC_TRNS, KC_BTN4, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN5, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TO(QWERTY)),

  [GAMING]=
    LAYOUT(
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS),

  [SQLMACROS]=
    LAYOUT(
      S_ALTER, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, S_WHERE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, S_INRJN, S_ORDER, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_LBRC, S_SLCT,  KC_PAST, S_FROM,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, S_LFTJN, KC_TRNS, KC_RBRC, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

  [SQLNAMES]=
    LAYOUT(
      TD_ESC,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TD_BSPC,
      KC_TRNS, TD_Q,    TD_W,    KC_TRNS, KC_TRNS, TD_T,    KC_TRNS, KC_TRNS, TD_I,    KC_TRNS, TD_P,    KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, TD_S,    TD_D,    KC_TRNS, TD_G,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TD_ENT,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TD_C,    KC_TRNS, KC_TRNS, TD_N,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, TD_ESC, TD_ESC, TD_ESC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

  [FN_LAYER]=
    LAYOUT(
      KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, KC_DEL,
      KC_CAPSLOCK, KC_MPRV, KC_MPLY, KC_MNXT, LWIN(KC_R), KC_TRNS, KC_CALC, KC_PGUP, KC_UP, KC_PGDN, KC_PSCR, KC_SLCK, KC_BRK, KC_TRNS,
      KC_TRNS, KC_VOLD, KC_MUTE, KC_VOLU, KC_TRNS, KC_TRNS, KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, KC_INS, KC_DEL, MO(LAYER_SEL),
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_END, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HYPR, KC_TRNS, KC_MEH, KC_TRNS),

  [LAYER_SEL]=
    LAYOUT(
      TO(QWERTY), TO(NAV_CLUSTER), KC_TRNS, TO(MOUSE), TO(GAMING), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, TO(QWERTY), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, TO(DVORAK), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TO(COLEMAK), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS, KC_TRNS, KC_TRNS, RESET, RESET, RESET, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)

};
