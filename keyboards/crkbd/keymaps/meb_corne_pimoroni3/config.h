/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

#pragma once                                // [Functions as an include guard]

#define MASTER_LEFT                         // Designate left-side as Master
#define POINTING_DEVICE_ROTATION_90         // Rotate pointing device 90 degrees
#define SPLIT_POINTING_ENABLE               // Enable pointing device on Slave
#define POINTING_DEVICE_RIGHT               // Designate right-side as having pointing device
#define POINTING_DEVICE_TASK_THROTTLE_MS 8  // Throttle pointing device report frequency to 8 ms
#define POINTING_DEVICE_AUTO_MOUSE_ENABLE   // Enable automatically toggling "mouse layer" on pointing device activity
#define AUTO_MOUSE_DEFAULT_LAYER 4          // Set mouse layer to layer index 4
#define AUTO_MOUSE_TIME 2500                // Set auto mouse layer toggle duration to 2500 ms (2.5 seconds)
