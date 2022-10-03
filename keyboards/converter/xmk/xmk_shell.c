// Copyright 2022 Manna Harbour (@manna-harbour)
// https://github.com/manna-harbour/xmk

// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include <stdio.h>
#include <string.h>

#include "xmk_matrix.h"

#define XMK_SHELL_LINE_LEN 64

#define XMK_SHELL_KEY "key "
#define XMK_SHELL_KEY_PRESS "press "
#define XMK_SHELL_KEY_RELEASE "release "
#define XMK_SHELL_BOOT "boot"
#define XMK_SHELL_RESET "reset"

void xmk_shell(char *line) {
  dprintf("xmk_shell: line: '%s'\n", line);
  if (strncmp(line, XMK_SHELL_KEY, strlen(XMK_SHELL_KEY)) == 0) {
    dprintf("xmk_shell: XMK_SHELL_KEY\n");
    if (strncmp(line + strlen(XMK_SHELL_KEY), XMK_SHELL_KEY_PRESS, strlen(XMK_SHELL_KEY_PRESS)) == 0) {
      uint8_t key = strtol(line + strlen(XMK_SHELL_KEY) + strlen(XMK_SHELL_KEY_PRESS), NULL, 10);
      dprintf("xmk_shell: XMK_SHELL_KEY_PRESS: key: %u\n", key);
      xmk_matrix_key(true, key);
    } else if (strncmp(line + strlen(XMK_SHELL_KEY), XMK_SHELL_KEY_RELEASE, strlen(XMK_SHELL_KEY_RELEASE)) == 0) {
      uint8_t key = strtol(line + strlen(XMK_SHELL_KEY) + strlen(XMK_SHELL_KEY_RELEASE), NULL, 10);
      dprintf("xmk_shell: XMK_SHELL_KEY_RELEASE: key: %u\n", key);
      xmk_matrix_key(false, key);
    }
  } else if (strcmp(line, XMK_SHELL_BOOT) == 0) {
    dprintf("xmk_shell: XMK_SHELL_BOOT\n");
    reset_keyboard();
  } else if (strcmp(line, XMK_SHELL_RESET) == 0) {
    dprintf("xmk_shell: XMK_SHELL_RESET\n");
    soft_reset_keyboard();
  }
}

void virtser_recv(const uint8_t ch) {
  static char line[XMK_SHELL_LINE_LEN];
  static uint8_t line_index = 0;
  if (ch == '\r') {
    dprintf("virtser_recv: i: %3u, ch: %3u '\\r' \n", line_index, ch);
    line[line_index] = '\0';
    xmk_shell(line);
    line_index = 0;
  } else if (ch == '\n') {
    dprintf("virtser_recv: i: %3u, ch: %3u '\\n' \n", line_index, ch);
  } else {
    dprintf("virtser_recv: i: %3u, ch: %3u '%c'\n", line_index, ch, ch);
    if (line_index < (XMK_SHELL_LINE_LEN - 1)) {
      line[line_index] = ch;
      line_index++;
    }
  }
}
