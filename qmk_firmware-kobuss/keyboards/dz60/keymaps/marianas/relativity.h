#include QMK_KEYBOARD_H
#define macroTapsLen 32
#define tableNameListLen 32
#define charCountLen 32

#define relTimeout 1500


void activateRelativity(void);
bool deactivateRelativity(void);
void initStringData(void);
bool containsCode(uint16_t kc);
bool lastCodeIs(uint16_t kc);
bool last2CodeAre(uint16_t kc);
bool last2CodesAre(uint16_t kc, uint16_t kc2);
void addKeyCode(uint16_t kc);
void eraseKeyCodes(void);
void eraseCharCounts(void);
void printTableAbbreviation(void);
void eraseTableAbbreviation(void);
void printString(char* str);
void printStringAndQueueChar(char* str);
void ReplaceString(char *orig, char *repl);
void deletePrev(void);
bool processSmartMacroTap(uint16_t kc);
bool isShifted(void);
void setShifted(bool);



bool handleSmartMacros(uint16_t keycode, keyrecord_t *record);
bool storeShiftState(uint16_t keycode, keyrecord_t *record);
