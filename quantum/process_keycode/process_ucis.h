#ifndef PROCESS_UCIS_H
#define PROCESS_UCIS_H

#include "quantum.h"
#include "process_unicode_common.h"

#ifndef UCIS_MAX_SYMBOL_LENGTH
#define UCIS_MAX_SYMBOL_LENGTH 32
#endif

typedef struct {
  char *symbol;
  char *code;
} qk_ucis_symbol_t;

typedef struct {
  uint8_t count;
  uint16_t codes[UCIS_MAX_SYMBOL_LENGTH];
  bool in_progress:1;
} qk_ucis_state_t;

extern qk_ucis_state_t qk_ucis_state;

#define UCIS_TABLE(...) {__VA_ARGS__, {NULL, NULL}}
#define UCIS_SYM(name, code) {name, #code}

extern const qk_ucis_symbol_t ucis_symbol_table[];

void qk_ucis_start(void);
void qk_ucis_start_user(void);
void qk_ucis_symbol_fallback (void);
void register_ucis(const char *hex);
bool process_ucis (uint16_t keycode, keyrecord_t *record);

#endif
