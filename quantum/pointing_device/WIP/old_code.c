
    if (pointing_mode.id >= POINTING_MODE_MAP_START && pointing_mode.id <= (POINTING_MODE_MAP_START + POINTING_MODE_MAP_COUNT - 1)) {
        pointing_tap_codes(POINTING_MODE_MAP(pointing_mode.id - POINTING_MODE_MAP_START));
        return mouse_report;
    }