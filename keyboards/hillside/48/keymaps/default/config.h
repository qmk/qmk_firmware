// Copyright 2022 Michael McCoyd (@mmccoyd)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Some boards have issues detecting handedness using the vbus voltage,
// such as Elite-C v3, but not v3.1 on, and apparently some ProMicro boards.
// For those boards, use usb detection instead.
// #define SPLIT_USB_DETECT
