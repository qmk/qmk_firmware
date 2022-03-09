/* Copyright 2021 Simon Arlott
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

#include "gtest/gtest.h"

#include <initializer_list>
#include <list>
#include <string>

extern "C" {
#include "quantum.h"
#include "timer.h"
}

enum Direction {
    DOWN,
    UP,
};

class MatrixTestEvent {
   public:
    MatrixTestEvent(int row, int col, Direction direction);

    const int       row_;
    const int       col_;
    const Direction direction_;
};

class DebounceTestEvent {
   public:
    // 0, {{0, 1, DOWN}}, {{0, 1, DOWN}})
    DebounceTestEvent(fast_timer_t time, std::initializer_list<MatrixTestEvent> inputs, std::initializer_list<MatrixTestEvent> outputs);

    const fast_timer_t               time_;
    const std::list<MatrixTestEvent> inputs_;
    const std::list<MatrixTestEvent> outputs_;
};

class DebounceTest : public ::testing::Test {
   protected:
    void addEvents(std::initializer_list<DebounceTestEvent> events);
    void runEvents();

    fast_timer_t time_offset_ = 7777;
    bool         time_jumps_  = false;

   private:
    static bool        directionValue(Direction direction);
    static std::string directionLabel(Direction direction);

    void runEventsInternal();
    void runDebounce(bool changed);
    void checkCookedMatrix(bool changed, const std::string &error_message);
    void matrixUpdate(matrix_row_t matrix[], const std::string &name, const MatrixTestEvent &event);

    std::string strTime();
    std::string strMatrix(matrix_row_t matrix[]);

    std::list<DebounceTestEvent> events_;

    matrix_row_t input_matrix_[MATRIX_ROWS];
    matrix_row_t raw_matrix_[MATRIX_ROWS];
    matrix_row_t cooked_matrix_[MATRIX_ROWS];
    matrix_row_t output_matrix_[MATRIX_ROWS];

    int  extra_iterations_;
    bool auto_advance_time_;
};
