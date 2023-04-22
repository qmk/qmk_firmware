/*
A driver for the Azoteq ProxSense iq5xx touchpad controller

Copyright 2018 Wez Furlong

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct TrackpadData {
  uint8_t buttons;
  int16_t xDelta;
  int16_t yDelta;
  int8_t yWheel;
  int8_t xWheel;
};

#ifdef __cplusplus
extern "C" {
#endif
bool trackpad_init(void);
bool trackpad_get_data(struct TrackpadData *data);
#ifdef __cplusplus
}

class ProxSense {
public:
  bool init();
  bool dataIsReady();
  bool getData(struct TrackpadData *result);

private:
  bool endCommunicationWindow();

  bool hadState_{true};
};

#endif
