"""
/* Copyright 2021 JasonRen(biu)
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
"""

import font_user

cur_H = 8
cur_W = 6

aim_H = 6
aim_W = 8

def cvo(one_f):
    new_one_f = []
    cols_old_t = []
    for f_c in one_f:
        c = bin(f_c)[2:].ljust(8, '0')[::-1]
        cols_old_t.append(c)
    for i in range(aim_W):
        cur_str=''
        for j in range(cur_W):
            cur_str += cols_old_t[j][i]
        cur_str += '00'
        new_one_f.append(hex(int(cur_str,2)))
    return new_one_f
# print(','.join(new_one_f))
# new_one_f.append(int(c,2))

f_num = len(font_user.font)//cur_W

new_font=[]
for i in range(f_num):
    one_f = []
    for j in range(cur_W):
        one_f.append(i*cur_W+j)
    st = cvo(one_f)
    st = ','.join(st)+','
    new_font.append(st)
for i in new_font:
    print(i)
