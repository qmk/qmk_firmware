// Copyright 2022 Daniel Osipishin (@subrezon)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#ifdef OLED_ENABLE

enum layer_id {
    _QWE = 0,
    _NUM,
    _SYM,
    _OPT
};

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
       oled_write_P(PSTR("Layer:\n"), false);

       switch (get_highest_layer(layer_state)) {
              case _QWE :
                     oled_write_P(PSTR("QWERTY\n"), false);
                     break;

              case _NUM :
                     oled_write_P(PSTR("Numbers\n"), false);
                     break;

              case _SYM :
                     oled_write_P(PSTR("Symbols\n"), false);
                     break;

              case _OPT :
                     oled_write_P(PSTR("Options\n"), false);
                     break;

              default :
                     oled_write_P(PSTR("Undefined\n"), false);
       }

       return false;
};

#endif
