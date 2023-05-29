#include "relativity.h"
#include "keymap.h"
#include "keyDefinitions.h"


uint16_t *macroTaps = 0;

char *tableNameList = 0;

uint8_t *charCount = 0;
uint8_t countPointer = 0;

bool relativityActive = false;


bool sendAbbr = false;


static int16_t relativityTimer = 0;


bool tempOff = false;




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

void activateRelativity(void)
{
  initStringData();
  rgblight_mode(RGBLIGHT_MODE_KNIGHT);
  relativityTimer = timer_read();
  relativityActive = true;
}

bool deactivateRelativity(void)
{  
  rgblight_mode(9);
  eraseKeyCodes();
  eraseTableAbbreviation();
  eraseCharCounts();
  relativityActive = false;
  tempOff = false;
  return false;
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
  while (countPointer > 0)
  {
    charCount[countPointer] = 0;
    countPointer--;
  }
  charCount[countPointer] = 0;
}

void printTableAbbreviationLimited(void)
{
  if (tableNameList[0] == 0)
  {
    return;
  }
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
}

void printTableAbbreviation(void)
{
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
  if (charCount[countPointer] > 0 && countPointer < charCountLen)
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
  if (countPointer == 0 && charCount[countPointer] == 0)
    return;
  for (int i = 0; i < charCount[countPointer]; i++)
  {
      register_code(KC_BSPC);
      unregister_code(KC_BSPC);
  }
  charCount[countPointer] = 0;
  int i = 1;
  for (;i < tableNameListLen-1; i++)
  {
    if (tableNameList[i] == 0x0)
    {
      break;
    }
  }
  tableNameList[i-1] = 0x0;
  if (countPointer > 0)
  {
    countPointer--;
  }
}

bool processSmartMacroTap(uint16_t kc)
{
  if (relativityTimer > 0 && TIMER_DIFF_16(timer_read(), relativityTimer) >= relTimeout)
  {
    deactivateRelativity();
    return true;
  }
  relativityTimer = 0;
  switch(kc)
  {
    case KC_C:
      if (containsCode(KC_D))
      {
        printString("ribution");
        printStringAndQueueChar("Center");
      }
      else if (last2CodeAre(KC_C))
      {
        ReplaceString("Corporation", "Contact");
      }
      else if(lastCodeIs(KC_C))
      {
        printString("oration");
      }
      else
      {
        printStringAndQueueChar("Corp");
      }
      break;
    case KC_D:
      if (last2CodeAre(KC_D))
      {
        ReplaceString("Distribution", "Distributor");
      }
      else if(lastCodeIs(KC_D))
      {
        printString("ribution");
      }
      else
      {
        printStringAndQueueChar("Dist");
      }
      break;
    case KC_G:
        printStringAndQueueChar("Global");
        printStringAndQueueChar("Lookup");
      break;
    case KC_I:
      if (containsCode(KC_W))
        printStringAndQueueChar("Instance");
      else
        printStringAndQueueChar("Item");
      break;
    case KC_N:
      printStringAndQueueChar("NadRate");
      break;
    case KC_P:
      if (last2CodesAre(KC_D, KC_C))
      {
        ReplaceString("DistributionCenter", "DistCenter");
        printStringAndQueueChar("Pricing");
      }
      else if (last2CodeAre(KC_P))
      {
      }
      else if(lastCodeIs(KC_P))
      {
        ReplaceString("Product", "Person");
      }
      else
      {
        printStringAndQueueChar("Product");
      }
      break;
    case KC_Q:
      printStringAndQueueChar("Darden");
      break;
    case KC_S:
      if (containsCode(KC_W))
        if (containsCode(KC_S) || containsCode(KC_D))
          printStringAndQueueChar("Step");
        else
          printStringAndQueueChar("Session");
      else
        printStringAndQueueChar("Supplier");
      break;
    case KC_T:
      if (containsCode(KC_W))
        printStringAndQueueChar("Task");
      else
        printStringAndQueueChar("Type");
      break;
    case KC_W:
      printStringAndQueueChar("Workflow");
      break;
  }
  addKeyCode(kc);
  return false;
}


bool shifted = false;
bool isShifted(void)
{
  return shifted;
}

void setShifted(bool val)
{
  shifted = val;
}


bool storeShiftState(uint16_t keycode, keyrecord_t *record)
{

  if (record->event.pressed)
  {
    switch (keycode)
    {
      case SC_LSPO:
      case SC_RSPC:
        shifted = true;
    }
  }
  else
  {
    switch (keycode)
    {

      case SC_LSPO:
      case SC_RSPC:
        shifted = false;
        return true;
    }
  }
  return true;
}

bool handleSmartMacros(uint16_t keycode, keyrecord_t *record)
{
  if (relativityActive != true) return true;
  if (record->event.pressed)
  {
    switch (keycode)
    {
      case KC_BSPC:
        if (!isShifted()){
          deletePrev();
        }
        else {
          register_code(KC_BSPC);
          unregister_code(KC_BSPC);
        }
        return false;
      case KC_A:
      case KC_B:
      case KC_C:
      case KC_D:
      case KC_E:
      case KC_F:
      case KC_G:
      case KC_H:
      case KC_I:
      case KC_J:
      case KC_K:
      case KC_L:
      case KC_M:
      case KC_N:
      case KC_O:
      case KC_P:
      case KC_Q:
      case KC_R:
      case KC_S:
      case KC_T:
      case KC_U:
      case KC_V:
      case KC_W:
      case KC_X:
      case KC_Y:
      case KC_Z:
        return processSmartMacroTap(keycode);

      case PRRD:
        if (tempOff)
        {
          SEND_STRING("Id = ");
          printTableAbbreviationLimited();
          SEND_STRING(".Id");
          return deactivateRelativity();
        }
        else
        {
          printTableAbbreviation();
          SEND_STRING("ON ");
          printTableAbbreviationLimited();
          eraseKeyCodes();
          eraseTableAbbreviation();
          eraseCharCounts();
          tempOff = true;
          return true;
        }
        

      case KC_SPC:
        printTableAbbreviation();
          return deactivateRelativity();
      case ENTER_OR_SQL:
        if (tempOff)
        {
          SEND_STRING("Id = ");
          printTableAbbreviationLimited();
          SEND_STRING(".Id");
          deactivateRelativity();
          return true;
        }
        else
        {
          printTableAbbreviation();
          deactivateRelativity();
          return true;
        }
      case KC_ESC:
          return deactivateRelativity();
    }
  }
  return true;
}
