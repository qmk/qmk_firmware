#pragma once

#include "quantum.h"

#define FOREACH_UNICODE(M) \
  M(COMMA,   0x002C)       \
  M(L_PAREN, 0x0028)       \
  M(R_PAREN, 0x0029)       \
  M(EQUALS,  0x003D)       \
  M(TIMES,   0x00D7)       \
  M(DIVIDE,  0x00F7)       \
  M(MINUS,   0x2212)

#define UC_KEYCODE(name, code)  name = UC(code),

#define UCM_NAME(name, code)    UCM_ ## name,
#define UCM_ENTRY(name, code)   [UCM_ ## name] = code,
#define UCM_KEYCODE(name, code) name = X(UCM_ ## name),

#if defined(UNICODE_ENABLE)
enum unicode_keycodes {
  FOREACH_UNICODE(UC_KEYCODE)
};
#elif defined(UNICODEMAP_ENABLE)
enum unicode_names {
  FOREACH_UNICODE(UCM_NAME)
};

extern const uint32_t PROGMEM unicode_map[];

enum unicode_keycodes {
  FOREACH_UNICODE(UCM_KEYCODE)
};
#endif
