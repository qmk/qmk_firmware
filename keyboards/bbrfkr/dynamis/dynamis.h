/* Copyright 2022 bbrfkr
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

#include "quantum.h"

#define LAYOUT_ansi( \
      C00, C01, C02, C03, C04, C05, C06, C56, C55, C54, C53, C52, C51, C50, C90, \
      C10, C11, C12, C13, C14, C15, C16, C66, C65, C64, C63, C62, C61, C60, \
      C20, C21, C22, C23, C24, C25, C26, C76, C75, C74, C73, C72,      C70, \
      C30, C31, C32, C33, C34, C35, C36, C86, C85, C84, C83, C82, C81, C80,      C91, \
      C40, C41, C42,      C43,      C44,           C45, C46, C96, C95,      C94, C93, C92 \
    ) \
    { \
        { C00, C01, C02, C03, C04, C05, C06 }, \
        { C10, C11, C12, C13, C14, C15, C16 }, \
        { C20, C21, C22, C23, C24, C25, C26 }, \
        { C30, C31, C32, C33, C34, C35, C36 }, \
        { C40, C41, C42, C43, C44, C45, C46 }, \
        { C50, C51, C52, C53, C54, C55, C56 }, \
        { C60, C61, C62, C63, C64, C65, C66 }, \
        { C70, KC_NO, C72, C73, C74, C75, C76 }, \
        { C80, C81, C82, C83, C84, C85, C86 }, \
        { C90, C91, C92, C93, C94, C95, C96 } \
    }

#define LAYOUT_iso( \
      C00, C01, C02, C03, C04, C05, C06, C56, C55, C54, C53, C52, C51, C50, C90, \
      C10, C11, C12, C13, C14, C15, C16, C66, C65, C64, C63, C62, C61, \
      C20, C21, C22, C23, C24, C25, C26, C76, C75, C74, C73, C72, C71, C70, \
      C30, C31, C32, C33, C34, C35, C36, C86, C85, C84, C83, C82, C81, C80,      C91, \
      C40, C41, C42,      C43,      C44,           C45, C46, C96, C95,      C94, C93, C92 \
    ) \
    { \
        { C00, C01, C02, C03, C04, C05, C06 }, \
        { C10, C11, C12, C13, C14, C15, C16 }, \
        { C20, C21, C22, C23, C24, C25, C26 }, \
        { C30, C31, C32, C33, C34, C35, C36 }, \
        { C40, C41, C42, C43, C44, C45, C46 }, \
        { C50, C51, C52, C53, C54, C55, C56 }, \
        { KC_NO, C61, C62, C63, C64, C65, C66 }, \
        { C70, C71, C72, C73, C74, C75, C76 }, \
        { C80, C81, C82, C83, C84, C85, C86 }, \
        { C90, C91, C92, C93, C94, C95, C96 } \
    }
