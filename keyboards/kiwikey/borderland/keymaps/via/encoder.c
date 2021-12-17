// Copyright 2021 KiwiKey (@KiwiKey)
// SPDX-License-Identifier: GPL-2.0-or-later

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
	if (clockwise) {
		tap_code(KC_VOLD);
	} else {
		tap_code(KC_VOLU);
	}
    return true;	
}
#endif
