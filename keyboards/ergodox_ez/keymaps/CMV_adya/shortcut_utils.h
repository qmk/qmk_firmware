#ifndef _SHORTCUT_UTILS_H_
#define _SHORTCUT_UTILS_H_

#include <stdint.h>
#include <stdarg.h>
#include <quantum.h>

#define VA_ARRAY_UINT16_T(array, argc) va_list valist;                \
                              int i;                                  \
                              va_start(valist, argc);           \
                              for(i = 0; i < argc; i++) {       \
                                array[i] = va_arg(valist, uint16_t);  \
                              }                                       \
                              va_end(valist);

void shortcut_press(int argc_local, ...) {
  uint16_t kcs[argc_local];
  VA_ARRAY_UINT16_T(kcs, argc_local)
  for(i = 0; i < argc_local; i++) {
    register_code16(kcs[i]);
  }
}

void shortcut_release(int argc_local, ...) {
  uint16_t kcs[argc_local];
  VA_ARRAY_UINT16_T(kcs, argc_local)
  for(i = 0; i < argc_local; i++) {
    unregister_code16(kcs[i]);
  }
}

#endif
