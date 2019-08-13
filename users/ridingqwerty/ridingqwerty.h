#pragma once

#include "quantum.h"
//#include "version.h"
//#include "eeprom.h"
//#include "wrappers.h"
#include "process_records.h"
/*
//#ifdef TAP_DANCE_ENABLE
//  #include "tap_dance.h"
//#endif // TAP_DANCE_ENABLE
*/

enum userspace_layers
{
    _QWERTY = 0,
    _EDITOR,
    _NUMBER,
    _SYMBOL,
    _F_KEYS,
    _DEBUG,
    _SECRET,
    _FINAL
};

/*
typedef union {
  uint32_t raw;
  struct {
    uint8_t os_target :2;
  };
} userspace_config_t;
*/
