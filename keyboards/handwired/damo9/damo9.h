#pragma once

#include "quantum.h"
#include <stdio.h>
#include "oled_driver.h"
#include "quantum_keycodes.h"
#include "string.h"

#ifdef OLED_ENABLE
    // Function declarations
    void render_status(void);
    void render_logo(void);
    bool oled_task_user(void);
    void display_text(const char *text) ;
#endif