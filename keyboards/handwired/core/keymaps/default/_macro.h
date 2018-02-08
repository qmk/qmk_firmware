#define MACRO_INDEX(macro) macro - _CKC_START - 1
#define CALLBACK_MACRO_INDEX(macro) macro - _CM_START - 1

typedef struct {
  void (*func)(const char arg[50]);
  const char arg[50];
} Macro;

typedef struct {
  void (*callback)(char arg[]);
  bool numbers_only;
} CallbackMacro;


const PROGMEM Macro macros[] = {
  [MACRO_INDEX(EMAIL)]   = { send_string,    "ma.van.manen@live.nl" },
  [MACRO_INDEX(CMD)]     = { run_command,    "cmd" },
  [MACRO_INDEX(UBUNTU)]  = { run_command,    "ubuntu.exe" },
  [MACRO_INDEX(VS_PROP)] = { vs_snippet,     "prop" }
};

const PROGMEM CallbackMacro callback_macros[] = {
  [CALLBACK_MACRO_INDEX(PASTEX)]  = { pastex, true }
};

void run_macro(enum custom_keycodes macro_keycode) {
  static Macro macro;
  memcpy_P(&macro, &macros[MACRO_INDEX(macro_keycode)], sizeof(Macro));
  macro.func(macro.arg);
}

uint16_t space_keycodes[] = { KC_SPACE, SPC_FN1, SPC_FN };
void run_callback_macro(enum custom_keycodes macro_keycode) {
  static CallbackMacro macro;
  memcpy_P(&macro, &callback_macros[CALLBACK_MACRO_INDEX(macro_keycode)], sizeof(CallbackMacro));
  callback_with_param(macro.callback, macro.numbers_only, space_keycodes);
}

void pastex(char input[]){
  int num = atoi(input);
  for(int x = 0; x < num; x++) {
    send_string(SS_LCTRL("v"));
  }
}
