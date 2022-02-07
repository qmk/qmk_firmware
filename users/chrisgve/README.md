Copyright 2022 Christian C. Berclaz @chrisgve

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see http://www.gnu.org/licenses/.


# Definitions and code for various keyboards

This snippet serves two main purposes

- It helps managing keyboard lighting (matrix or backlight) to indicate the state of certain layers or to indicate the state of Caps Lock
- It provide definitions necessary to build consistent layouts across different type of keyboards (Ortho, 45%, 60%, etc.) with a focus on the middle row and its neighbourghs

## Concept

- Overall layout
The base concept is to work around a HHKB format or a close derivative as below

| --- |:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| Esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |  \  |  `  |
| Tab |  Q  |  W  |  E  |  R  |  T  |  Y  |  U  |  I  |  O  |  P  |  [  |  ]  |   Bkspc   |
| Ctl |  A  |  S  |  D  |  F  |  G  |  H  |  J  |  K  |  L  |  ;  |  '  |      Return     |
| Sft |  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |       Shift     | Fn  |
| Ctl | Alt | Gui |                     Space                           | Alt | Gui | Ctl |

## Color management based on layer or Key caps state



## Reusable definitions and code

