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

#define X_NAME(name, code)    X_ ## name,
#define X_ENTRY(name, code)   [X_ ## name] = code,
#define X_KEYCODE(name, code) name = X(X_ ## name),

#if defined(UNICODE_ENABLE)
  enum unicode_keycodes {
    FOREACH_UNICODE(UC_KEYCODE)
  };
#elif defined(UNICODEMAP_ENABLE)
  enum unicode_names {
    FOREACH_UNICODE(X_NAME)
  };

  extern const uint32_t PROGMEM unicode_map[];

  enum unicode_keycodes {
    FOREACH_UNICODE(X_KEYCODE)
  };
#endif
