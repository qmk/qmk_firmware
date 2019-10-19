/* Copyright 2019 Arda Kilicdagi
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

void initLeds(void) {
  setPinOutput(F6); // anodes
  setPinOutput(F7); // anodes

  setPinOutput(F4); // cathodes
  setPinOutput(F5); // cathodes
}

void setLedsOn(void) {
  writePinHigh(F6);
  writePinHigh(F7);
}

void setLedsLod(void) {
  writePinLow(F6);
  writePinLow(F7);
}