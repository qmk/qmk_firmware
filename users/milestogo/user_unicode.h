/// Copyright 2022 milestogo

/* 
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


// Unicode 
// Remember to include UNICODMAP_ENABLE=yes is the rules.mk 

#pragma once 

enum unicode_names {
    THUMBU,
    THUMBD,
    EYES,
    HMM,
    SMILE,
    FIRE,
    NAZAR,
    FIREW,
    PCT100,
    NAMASTE,
};

const uint32_t PROGMEM unicode_map[] = {
    [THUMBU] = 0x1F44D,  // 👍
    [THUMBD] = 0x1F44E,  //  
    [EYES]  = 0x1F440,  // 👀
    [HMM]   = 0x1F914,  // 🤔
    [SMILE] = 0x1F600,  // 😀
    [FIRE]  = 0x1F525,  // 🔥
    [NAZAR] = 0x1F9FF,  // 🧿
    [FIREW] = 0x1F387,  // 🎇
    [PCT100] = 0x1F3AF,  // 💯
    [NAMASTE]  = 0x1F64F,  // 🙏 

};


