/* Copyright 2020 Albert Diserholt (Drauthius)
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

#pragma once

/*
 * This module adds support for controlling the content of the OLED
 * screen(s) from the operating system via raw HID.
 * Add "OLED_CONTROL_ENABLE=yes" to your rules.mk to build the support
 * needed to send commands from the operating system to the firmware.
 *
 * See docs/feature_oledctrl.md for more information about the protocol.
 */

#include <stdint.h>
#include <stdbool.h>

#include "usb_descriptor.h" // For RAW_EPSIZE

// Maximum length of a HID message
#ifndef OLEDCTRL_MSG_MAX_LEN
#    define OLEDCTRL_MSG_MAX_LEN RAW_EPSIZE
#endif

// The type of a message understood by the OLED controlling code.
// The IDs must not clash with VIA.
enum oledctrl_message_id {
    OLEDCTRL_MSG_FIRST    = 0xC0,
    OLEDCTRL_MSG_COMMAND  = OLEDCTRL_MSG_FIRST,
    OLEDCTRL_MSG_EVENT    = 0xC1,
    OLEDCTRL_MSG_LAST,
};

// Result codes for the commands.
// First byte in responses from the firmware.
enum oledctrl_result_id {
    OLEDCTRL_RES_SUCCESS = 0x00,
    OLEDCTRL_RES_FAILURE = 0x01,
};

/*
 * The commands that are recognised to control the OLEDs.
 * OLEDCTRL_CMD_SET_UP:
 *   This is equivalent to clear, but also returns the number of characters
 *   that can be written to the screen in the fourth and fifth bytes of the
 *   response (columns and rows, respectively).
 *
 * OLEDCTRL_CMD_CLEAR:
 *   Clear the entire screen. Depending on how oled_task_user() looks, this might
 *   revert the screen to its "default" (uncontrolled) state.
 *
 * OLEDCTRL_CMD_SET_LINE:
 *   Set the content of a line (row) of the screen. The fourth byte should be which
 *   line to modify, and the fifth byte and onwards should be content that is
 *   desired on that line. Will replace everything on that line, and will not
 *   wrap to the next one.
 *
 * OLEDCTRL_CMD_SET_CHARS:
 *   Set a portion of the screen. The fourth byte should be the offset, the fifth byte
 *   the length of the string, and the sixth byte and onwards should be the string to
 *   set. Will replace only until the length, and will wrap if it goes over a line.
 *
 * OLEDCTRL_CMD_PRESENT:
 *   Show the changes to the screen. This has to be called after the desired
 *   number of OLEDCTRL_CMD_SET_LINE commands have been issued. Think of it as double
 *   buffering, where this command will present the content of the back buffer.
 */
enum oledctrl_command_id {
    OLEDCTRL_CMD_SET_UP    = 0x00,
    OLEDCTRL_CMD_CLEAR     = 0x01,
    OLEDCTRL_CMD_SET_LINE  = 0x02,
    OLEDCTRL_CMD_SET_CHARS = 0x03,
    OLEDCTRL_CMD_PRESENT   = 0x04,
};

/*
 * The events that the firmware might send, triggered by keyboard-level code.
 * They are the second byte in messages sent from the firmware.
 * OLEDCTRL_EVENT_SET_TAG:
 *   A specific tag is requested to be shown on a specific screen. The third
 *   byte is the screen (oledctrl_screen_id below), and the fourth is the tag ID.
 *   Note that KC_1 => tag ID 1.
 *
 * OLEDCTRL_EVENT_INCREMENT_TAG:
 *   Go to the next tag for a specific screen. The third byte is the screen
 *   (oledctrl_screen_id below).
 *
 * OLEDCTRL_EVENT_DECREMENT_TAG:
 *   Go to the previous tag for a specific screen. The third byte is the
 *   screen (oledctrl_screen_id below).
 */
enum oledctrl_event_id {
    OLEDCTRL_EVENT_SET_TAG       = 0x00,
    OLEDCTRL_EVENT_INCREMENT_TAG = 0x01,
    OLEDCTRL_EVENT_DECREMENT_TAG = 0x02,
};

// Which OLED screen to control.
// Typically the third byte in messages to and from the firmware.
enum oledctrl_screen_id {
    OLEDCTRL_SCR_MASTER = 0x00,
    OLEDCTRL_SCR_SLAVE  = 0x01,
};

bool oledctrl_has_content(void);
bool oledctrl_draw(void);

void oledctrl_handle_cmd(uint8_t *data, uint8_t length);
void oledctrl_send_event(enum oledctrl_event_id event, uint8_t *args, uint8_t args_len);

#ifdef OLEDCTRL_SPLIT

typedef struct _oledctrl_syncinfo_t {
    uint8_t msg[OLEDCTRL_MSG_MAX_LEN];
} oledctrl_syncinfo_t;

/* for split keyboard master side */
void oledctrl_send_msg(const uint8_t *msg, uint8_t len);
bool oledctrl_is_msg_pending(void);
void oledctrl_clear_msg_pending(void);
void oledctrl_get_syncinfo(oledctrl_syncinfo_t *syncinfo);
/* for split keyboard slave side */
void oledctrl_update_sync(oledctrl_syncinfo_t *syncinfo);
void oledctrl_receive_msg(uint8_t *msg, uint8_t len);

#endif // OLEDCTRL_SPLIT
