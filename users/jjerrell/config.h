// Copyright (C) 2021 Jerrell, Jacob <@jjerrell>
// 
// This file is part of jjerrell.
// 
// jjerrell is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// jjerrell is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with jjerrell.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

#define LEADER_TIMEOUT 250
#define LEADER_PER_KEY_TIMING

#if defined(TAP_CODE_DELAY)
#    undef TAP_CODE_DELAY
#endif
#define TAP_CODE_DELAY 20
