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

// Compatibility commands
enum pok3r_cmd {
#if defined(UPDATE_PROTO_POK3R)
    CMD_RESET       = 4,    //!< Reset command.
    SUB_RESET_BL    = 1,    //!< Reset to bootloader.
    SUB_RESET_FW    = 2,    //!< Reset firmware.
#elif defined(UPDATE_PROTO_CYKB)
    CMD_RESET       = 0x11, //!< Reset command.
    SUB_RESET_BL    = 0,    //!< Reset to bootloader.
    SUB_RESET_FW    = 1,    //!< Reset firmware.
#endif

#if defined(UPDATE_PROTO_POK3R)
    CMD_FLASH       = 1,    //!< Internal flash command.
    SUB_WRITE       = 1,    //!< Write 52 bytes to internal flash.
    SUB_READ        = 2,    //!< Read 64 bytes from internal flash.
#elif defined(UPDATE_PROTO_CYKB)
    CMD_READ        = 0x12, //!< Read internal flash command.
    SUB_READ_400    = 0,
    SUB_READ_3C00   = 1,
    SUB_READ_MODE   = 2,    //!< Get firmware mode. 0 is bootloader, 1 is firmware.
    SUB_READ_VER1   = 0x20, //!< Read version string.
    SUB_READ_VER2   = 0x22, //!< Read version data.
    SUB_READ_ADDR   = 0xff, //!< Patched command, read arbitrary address.
#endif
};

// New QMK commands
enum qmk_cmd {
    CMD_CTRL        = 0x81, //!< Control command.
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
    SUB_KM_RESET    = 5,    //!< Load default keymap.

    CMD_BACKLIGHT   = 0x84, //!< Backlight commands.
    SUB_BL_INFO     = 0,    //!< Backlight map info (layers, rows, cols, type size).
    SUB_BL_READ     = 1,    //!< Read backlight map.
    SUB_BL_WRITE    = 2,    //!< Write to backlight map.
    SUB_BL_COMMIT   = 3,    //!< Commit backlight map to EEPROM.

    CMD_FLASH_QMK   = 0x85, //!< Flash commands.
    SUB_FL_READ     = 0,    //!< Read flash data.
};

#endif // PROTO_H
