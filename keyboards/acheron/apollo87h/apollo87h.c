/*
 Copyright 2022 Álvaro "Gondolindrim" Volpato <alvaro.volpato@usp.br>

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

#include "apollo87h.h"

void board_init(void) {
    setPinInput(B9);
    setPinInput(B10);
}

led_config_t g_led_config = { {
	{ 15       , 14         , 13         , 12         , 11         , 10         , 9          , 8          , 7          , 6          , 5          , 4          , 3          , NO_LED     , 2          , 1          , 0         },
	{ 16       , 17         , 18         , 19         , 20         , 21         , 22         , 23         , 24         , 25         , 26         , 27         , 28         , 29         , 30         , 31         , 32        },
	{ 49       , 48         , 47         , 46         , 45         , 44         , 43         , 42         , 41         , 40         , 39         , 38         , 37         , 36         , 35         , 34         , 33        },
	{ 50       , 51         , 52         , 53         , 54         , 55         , 56         , 57         , 58         , 59         , 60         , 61         , 62         , NO_LED     , NO_LED     , NO_LED     , NO_LED    },
	{ 75       , NO_LED     , 74         , 73         , 72         , 71         , 70         , 69         , 68         , 67         , 66         , 65         , 64         , NO_LED     , NO_LED     , 63         , NO_LED    },
	{ 76       , 77         , 78         , NO_LED     , NO_LED     , NO_LED     , 79         , NO_LED     , NO_LED     , 80         , 81         , 82         , 83         , NO_LED     , 84         , 85         , 86        },
},{                                    
	{   0,   0}, {  14,   0}, {  28,   0}, {  42,   0}, {  64,   0}, {  70,   0}, {  84,   0}, {  98,   0}, { 112,   0}, { 126,   0}, { 140,   0}, { 154,   0}, { 168,   0},              { 196,   0}, { 210,   0}, { 224,   0},
	{   0,  45}, {  14,  45}, {  28,  45}, {  42,  45}, {  64,  45}, {  70,  45}, {  84,  45}, {  98,  45}, { 112,  45}, { 126,  45}, { 140,  45}, { 154,  45}, { 168,  45}, { 184,  45}, { 196,  45}, { 210,  45}, { 224,  45},
	{   0,  90}, {  14,  90}, {  28,  90}, {  42,  90}, {  64,  90}, {  70,  90}, {  84,  90}, {  98,  90}, { 112,  90}, { 126,  90}, { 140,  90}, { 154,  90}, { 168,  90}, { 184,  90}, { 196,  90}, { 210,  90}, { 224,  90},
	{   0, 134}, {  14, 134}, {  28, 134}, {  42, 134}, {  64, 134}, {  70, 134}, {  84, 134}, {  98, 134}, { 112, 134}, { 126, 134}, { 140, 134}, { 154, 134}, { 168, 134},
	{   0, 179},              {  28, 179}, {  42, 179}, {  64, 179}, {  70, 179}, {  84, 179}, {  98, 179}, { 112, 179}, { 126, 179}, { 140, 179}, { 154, 179}, { 168, 179},                           { 210, 179},
	{   0, 224}, {  14, 224}, {  28, 224},                                        {  84, 224},                           { 126, 224}, { 140, 224}, { 154, 224}, { 168, 224},              { 196, 224}, { 210, 224}, { 224, 224}
}, {
	1          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          ,              4          , 4          , 4          ,
	4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 
	4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          ,
	4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 1          ,
	1                       , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 4          , 1                                    , 1          ,
	1          , 1          , 1          ,                                        4          ,                           1          , 1          , 1          , 1                       , 1          , 1          , 1          
} };
