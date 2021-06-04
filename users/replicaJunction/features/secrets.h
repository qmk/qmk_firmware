#pragma once
#include QMK_KEYBOARD_H

// NOTE: In some implementations of the "secrets" functionality, the
// secrets.h file is the file that actually contains secret text.
//
// This is not the case in my implementation. That file is called
// "secret_definitions.h", and it's in a local .gitignore file so it
// does not get committed.
//
// The inclusion of this file is not an error, and there is no sensitive
// text here.

bool process_record_secrets(uint16_t keycode, const keyrecord_t *record);
