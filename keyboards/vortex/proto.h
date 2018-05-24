/*
 * Copyright (c) 2018 Charlie Waters
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef PROTO_H
#define PROTO_H

// New QMK commands
enum qmk_cmd {
    CMD_CTRL        = 0x81, //!< Firmware info.
    SUB_CT_INFO     = 0,    //!< Firmware info.
    SUB_CT_LAYOUT   = 1,    //!< Set layout.

    CMD_EEPROM      = 0x82, //!< EEPROM commands.
    SUB_EE_INFO     = 0,    //!< EEPROM info (RDID SPI command).
    SUB_EE_READ     = 1,    //!< Read EEPROM data.
    SUB_EE_WRITE    = 2,    //!< Write EEPROM data.
    SUB_EE_ERASE    = 3,    //!< Erase EEPROM page.

    CMD_KEYMAP      = 0x83, //!< Keymap commands.
    SUB_KM_INFO     = 0,    //!< Keymap info (layers, rows, cols, type size).
    SUB_KM_READ     = 1,    //!< Read keymap.
    KM_PAGE_MATRIX  = 0,    //!< Matrix page.
    KM_PAGE_LAYOUT  = 1,    //!< Layout page.
    KM_PAGE_STRS    = 2,    //!< Layout string page.
    SUB_KM_WRITE    = 2,    //!< Write to keymap.
    SUB_KM_COMMIT   = 3,    //!< Commit keymap to EEPROM.
    SUB_KM_RELOAD   = 4,    //!< Load keymap from EEPROM.

    CMD_BACKLIGHT   = 0x84, //!< Backlight commands.
    SUB_BL_INFO     = 0,    //!< Backlight map info (layers, rows, cols, type size).
    SUB_BL_READ     = 1,    //!< Read backlight map.
    SUB_BL_WRITE    = 2,    //!< Write to backlight map.
    SUB_BL_COMMIT   = 3,    //!< Commit backlight map to EEPROM.
};

#endif // PROTO_H
