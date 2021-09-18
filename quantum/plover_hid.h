#pragma once

void plover_hid_update(uint8_t button, bool pressed);
void plover_hid_task(void);
void plover_hid_send(uint8_t *data, uint8_t length);
