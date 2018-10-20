#include QMK_KEYBOARD_H
#include "relativity.h"
#include "keyDefinitions.h"


uint16_t *macroTaps = 0;

char *tableNameList = 0;

uint8_t *charCount = 0;
uint8_t countPointer = 0;



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



bool handleSmartMacros(uint16_t keycode, keyrecord_t *record)
{
  if (record->event.pressed)
  {
    switch (keycode)
    {
      case TD_BSPC:
        if (!isShifted()){
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
  return true;
}
