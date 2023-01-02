/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>
   Copyright 2021 Tomas Guinan

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


const uint16_t GAME_TIMER[] = { 
	400, 350, 300, 250, 400, 350, 300, 250, 225, 200, 175, 150
};

bool game_start = false;
HSV last_hsv;
static uint8_t paddle_pos_full;
static uint8_t paddle_lives;
static uint8_t level_number;
static uint8_t bounce_count;
static uint8_t damage_count;
static uint16_t damage_timer;
static uint16_t ball_timer;

struct BallStruct
{
	uint8_t x;
	uint8_t y;
	bool on;
	bool up;
	bool left;
	bool enemy;
};
	
struct BallStruct ball[2];

void init_ball(uint8_t i);
void hurt_paddle(void);