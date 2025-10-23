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

#include "debounce_test_common.h"

#include <algorithm>
#include <iomanip>
#include <sstream>

extern "C" {
#include "debounce.h"
#include "timer.h"

void     simulate_async_tick(uint32_t t);
void     reset_access_counter(void);
uint32_t current_access_counter(void);
uint32_t timer_read_internal(void);
void     set_time(uint32_t t);
void     advance_time(uint32_t ms);
}

void DebounceTest::addEvents(std::initializer_list<DebounceTestEvent> events) {
    events_.insert(events_.end(), events.begin(), events.end());
}

void DebounceTest::runEvents() {
    /* Run the test multiple times, from 1kHz to 10kHz scan rate */
    for (extra_iterations_ = 0; extra_iterations_ < 10; extra_iterations_++) {
        if (time_jumps_) {
            /* Don't advance time smoothly, jump to the next event (some tests require this) */
            auto_advance_time_ = false;
            runEventsInternal();
        } else {
            /* Run the test with both smooth and irregular time; it must produce the same result */
            auto_advance_time_ = true;
            runEventsInternal();
            auto_advance_time_ = false;
            runEventsInternal();
        }
    }
}

void DebounceTest::runEventsInternal() {
    fast_timer_t previous = 0;
    bool         first    = true;

    /* Initialise keyboard with start time (offset to avoid testing at 0) and all keys UP */
    debounce_init();
    set_time(time_offset_);
    simulate_async_tick(async_time_jumps_);
    std::fill(std::begin(input_matrix_), std::end(input_matrix_), 0);
    std::fill(std::begin(output_matrix_), std::end(output_matrix_), 0);

    for (auto &event : events_) {
        if (!auto_advance_time_) {
            /* Jump to the next event */
            set_time(time_offset_ + event.time_);
        } else if (!first && event.time_ == previous + 1) {
            /* This event immediately follows the previous one, don't make extra debounce() calls */
            advance_time(1);
        } else {
            /* Fast forward to the time for this event, calling debounce() with no changes */
            ASSERT_LT((time_offset_ + event.time_) - timer_read_internal(), 60000) << "Test tries to advance more than 1 minute of time";

            while (timer_read_internal() != time_offset_ + event.time_) {
                runDebounce(false);
                checkCookedMatrix(false, "debounce() modified cooked matrix");
                advance_time(1);
            }
        }

        first    = false;
        previous = event.time_;

        /* Prepare input matrix */
        for (auto &input : event.inputs_) {
            matrixUpdate(input_matrix_, "input", input);
        }

        /* Call debounce */
        runDebounce(!event.inputs_.empty());

        /* Prepare output matrix */
        for (auto &output : event.outputs_) {
            matrixUpdate(output_matrix_, "output", output);
        }

        /* Check output matrix has expected change events */
        for (auto &output : event.outputs_) {
            EXPECT_EQ(!!(cooked_matrix_[output.row_] & (1U << output.col_)), directionValue(output.direction_)) << "Missing event at " << strTime() << " expected key " << output.row_ << "," << output.col_ << " " << directionLabel(output.direction_) << "\ninput_matrix: changed=" << !event.inputs_.empty() << "\n" << strMatrix(input_matrix_) << "\nexpected_matrix:\n" << strMatrix(output_matrix_) << "\nactual_matrix:\n" << strMatrix(cooked_matrix_);
        }

        /* Check output matrix has no other changes */
        checkCookedMatrix(!event.inputs_.empty(), "debounce() cooked matrix does not match expected output matrix");

        /* Perform some extra iterations of the matrix scan with no changes */
        for (int i = 0; i < extra_iterations_; i++) {
            runDebounce(false);
            checkCookedMatrix(false, "debounce() modified cooked matrix");
        }
    }

    /* Check that no further changes happen for 1 minute */
    for (int i = 0; i < 60000; i++) {
        runDebounce(false);
        checkCookedMatrix(false, "debounce() modified cooked matrix");
        advance_time(1);
    }
}

void DebounceTest::runDebounce(bool changed) {
    std::copy(std::begin(input_matrix_), std::end(input_matrix_), std::begin(raw_matrix_));
    std::copy(std::begin(output_matrix_), std::end(output_matrix_), std::begin(cooked_matrix_));

    reset_access_counter();

    bool cooked_changed = debounce(raw_matrix_, cooked_matrix_, changed);

    if (!std::equal(std::begin(input_matrix_), std::end(input_matrix_), std::begin(raw_matrix_))) {
        FAIL() << "Fatal error: debounce() modified raw matrix at " << strTime() << "\ninput_matrix: changed=" << changed << "\n" << strMatrix(input_matrix_) << "\nraw_matrix:\n" << strMatrix(raw_matrix_);
    }

    if (std::equal(std::begin(output_matrix_), std::end(output_matrix_), std::begin(cooked_matrix_)) == cooked_changed) {
        FAIL() << "Fatal error: debounce() reported a wrong cooked matrix change result at " << strTime() << "\noutput_matrix: cooked_changed=" << cooked_changed << "\n" << strMatrix(output_matrix_) << "\ncooked_matrix:\n" << strMatrix(cooked_matrix_);
    }

    if (current_access_counter() > 1) {
        FAIL() << "Fatal error: debounce() read the timer multiple times, which is not allowed, at " << strTime() << "\ntimer: access_count=" << current_access_counter() << "\noutput_matrix: cooked_changed=" << cooked_changed << "\n" << strMatrix(output_matrix_) << "\ncooked_matrix:\n" << strMatrix(cooked_matrix_);
    }
}

void DebounceTest::checkCookedMatrix(bool changed, const std::string &error_message) {
    if (!std::equal(std::begin(output_matrix_), std::end(output_matrix_), std::begin(cooked_matrix_))) {
        FAIL() << "Unexpected event: " << error_message << " at " << strTime() << "\ninput_matrix: changed=" << changed << "\n" << strMatrix(input_matrix_) << "\nexpected_matrix:\n" << strMatrix(output_matrix_) << "\nactual_matrix:\n" << strMatrix(cooked_matrix_);
    }
}

std::string DebounceTest::strTime() {
    std::stringstream text;

    text << "time " << (timer_read_internal() - time_offset_) << " (extra_iterations=" << extra_iterations_ << ", auto_advance_time=" << auto_advance_time_ << ")";

    return text.str();
}

std::string DebounceTest::strMatrix(matrix_row_t matrix[]) {
    std::stringstream text;

    text << "\t" << std::setw(3) << "";
    for (int col = 0; col < MATRIX_COLS; col++) {
        text << " " << std::setw(2) << col;
    }
    text << "\n";

    for (int row = 0; row < MATRIX_ROWS; row++) {
        text << "\t" << std::setw(2) << row << ":";
        for (int col = 0; col < MATRIX_COLS; col++) {
            text << ((matrix[row] & (1U << col)) ? " XX" : " __");
        }

        text << "\n";
    }

    return text.str();
}

bool DebounceTest::directionValue(Direction direction) {
    switch (direction) {
        case DOWN:
            return true;

        case UP:
            return false;
    }
}

std::string DebounceTest::directionLabel(Direction direction) {
    switch (direction) {
        case DOWN:
            return "DOWN";

        case UP:
            return "UP";
    }
}

/* Modify a matrix and verify that events always specify a change */
void DebounceTest::matrixUpdate(matrix_row_t matrix[], const std::string &name, const MatrixTestEvent &event) {
    ASSERT_NE(!!(matrix[event.row_] & (1U << event.col_)), directionValue(event.direction_)) << "Test " << name << " at " << strTime() << " sets key " << event.row_ << "," << event.col_ << " " << directionLabel(event.direction_) << " but it is already " << directionLabel(event.direction_) << "\n" << name << "_matrix:\n" << strMatrix(matrix);

    switch (event.direction_) {
        case DOWN:
            matrix[event.row_] |= (1U << event.col_);
            break;

        case UP:
            matrix[event.row_] &= ~(1U << event.col_);
            break;
    }
}

DebounceTestEvent::DebounceTestEvent(fast_timer_t time, std::initializer_list<MatrixTestEvent> inputs, std::initializer_list<MatrixTestEvent> outputs) : time_(time), inputs_(inputs), outputs_(outputs) {}

MatrixTestEvent::MatrixTestEvent(int row, int col, Direction direction) : row_(row), col_(col), direction_(direction) {}
