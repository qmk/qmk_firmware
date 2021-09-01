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

TEST_F(DebounceTest, OneKeyShort1) {
    addEvents({ /* Time, Inputs, Outputs */
        {0, {{0, 1, DOWN}}, {{0, 1, DOWN}}},
        {1, {{0, 1, UP}}, {}},

        {5, {}, {{0, 1, UP}}},
        /* Press key again after 1ms delay (debounce has not yet finished) */
        {6, {{0, 1, DOWN}}, {}},
        {10, {}, {{0, 1, DOWN}}}, /* 5ms after UP at time 5 */
    });
    runEvents();
}

TEST_F(DebounceTest, OneKeyShort2) {
    addEvents({ /* Time, Inputs, Outputs */
        {0, {{0, 1, DOWN}}, {{0, 1, DOWN}}},
        {1, {{0, 1, UP}}, {}},

        {5, {}, {{0, 1, UP}}},
        /* Press key again after 2ms delay (debounce has not yet finished) */
        {7, {{0, 1, DOWN}}, {}},
        {10, {}, {{0, 1, DOWN}}}, /* 5ms after UP at time 5 */
    });
    runEvents();
}

TEST_F(DebounceTest, OneKeyShort3) {
    addEvents({ /* Time, Inputs, Outputs */
        {0, {{0, 1, DOWN}}, {{0, 1, DOWN}}},
        {1, {{0, 1, UP}}, {}},

        {5, {}, {{0, 1, UP}}},
        /* Press key again after 3ms delay (debounce has not yet finished) */
        {8, {{0, 1, DOWN}}, {}},
        {10, {}, {{0, 1, DOWN}}}, /* 5ms after UP at time 5 */
    });
    runEvents();
}

TEST_F(DebounceTest, OneKeyShort4) {
    addEvents({ /* Time, Inputs, Outputs */
        {0, {{0, 1, DOWN}}, {{0, 1, DOWN}}},
        {1, {{0, 1, UP}}, {}},

        {5, {}, {{0, 1, UP}}},
        /* Press key again after 4ms delay (debounce has not yet finished) */
        {9, {{0, 1, DOWN}}, {}},
        {10, {}, {{0, 1, DOWN}}}, /* 5ms after UP at time 5 */
    });
    runEvents();
}

TEST_F(DebounceTest, OneKeyShort5) {
    addEvents({ /* Time, Inputs, Outputs */
        {0, {{0, 1, DOWN}}, {{0, 1, DOWN}}},
        {1, {{0, 1, UP}}, {}},

        {5, {}, {{0, 1, UP}}},
        /* Press key again after 5ms delay (debounce has finished) */
        {10, {{0, 1, DOWN}}, {{0, 1, DOWN}}},
    });
    runEvents();
}

TEST_F(DebounceTest, OneKeyShort6) {
    addEvents({ /* Time, Inputs, Outputs */
        {0, {{0, 1, DOWN}}, {{0, 1, DOWN}}},
        {1, {{0, 1, UP}}, {}},

        {5, {}, {{0, 1, UP}}},
        /* Press key after after 6ms delay (debounce has finished) */
        {11, {{0, 1, DOWN}}, {{0, 1, DOWN}}},
    });
    runEvents();
}

TEST_F(DebounceTest, OneKeyBouncing1) {
    addEvents({ /* Time, Inputs, Outputs */
        {0, {{0, 1, DOWN}}, {{0, 1, DOWN}}},
        {1, {{0, 1, UP}}, {}},
        {2, {{0, 1, DOWN}}, {}},
        {3, {{0, 1, UP}}, {}},
        {4, {{0, 1, DOWN}}, {}},
        {5, {{0, 1, UP}}, {{0, 1, UP}}},
        /* Press key again after 1ms delay (debounce has not yet finished) */
        {6, {{0, 1, DOWN}}, {}},
        {10, {}, {{0, 1, DOWN}}}, /* 5ms after UP at time 5 */
    });
    runEvents();
}

TEST_F(DebounceTest, OneKeyBouncing2) {
    addEvents({ /* Time, Inputs, Outputs */
        {0, {{0, 1, DOWN}}, {{0, 1, DOWN}}},
        /* Change twice in the same time period */
        {1, {{0, 1, UP}}, {}},
        {1, {{0, 1, DOWN}}, {}},
        /* Change three times in the same time period */
        {2, {{0, 1, UP}}, {}},
        {2, {{0, 1, DOWN}}, {}},
        {2, {{0, 1, UP}}, {}},
        /* Change three times in the same time period */
        {3, {{0, 1, DOWN}}, {}},
        {3, {{0, 1, UP}}, {}},
        {3, {{0, 1, DOWN}}, {}},
        /* Change twice in the same time period */
        {4, {{0, 1, UP}}, {}},
        {4, {{0, 1, DOWN}}, {}},
        {5, {{0, 1, UP}}, {{0, 1, UP}}},
        /* Press key again after 1ms delay (debounce has not yet finished) */
        {6, {{0, 1, DOWN}}, {}},
        {10, {}, {{0, 1, DOWN}}}, /* 5ms after UP at time 5 */
    });
    runEvents();
}

TEST_F(DebounceTest, OneKeyLong) {
    addEvents({ /* Time, Inputs, Outputs */
        {0, {{0, 1, DOWN}}, {{0, 1, DOWN}}},

        {25, {{0, 1, UP}}, {{0, 1, UP}}},

        {50, {{0, 1, DOWN}}, {{0, 1, DOWN}}},
    });
    runEvents();
}

TEST_F(DebounceTest, TwoKeysShort) {
    addEvents({ /* Time, Inputs, Outputs */
        {0, {{0, 1, DOWN}}, {{0, 1, DOWN}}},
        {1, {{0, 1, UP}}, {}},
        {2, {{0, 2, DOWN}}, {{0, 2, DOWN}}},
        {3, {{0, 2, UP}}, {}},

        {5, {}, {{0, 1, UP}}},
        /* Press key again after 1ms delay (debounce has not yet finished) */
        {6, {{0, 1, DOWN}}, {}},
        {7, {}, {{0, 2, UP}}},

        /* Press key again after 1ms delay (debounce has not yet finished) */
        {9, {{0, 2, DOWN}}, {}},
        {10, {}, {{0, 1, DOWN}}}, /* 5ms after UP at time 5 */

        {12, {}, {{0, 2, DOWN}}}, /* 5ms after UP at time 7 */
    });
    runEvents();
}

TEST_F(DebounceTest, OneKeyDelayedScan1) {
    addEvents({ /* Time, Inputs, Outputs */
        {0, {{0, 1, DOWN}}, {{0, 1, DOWN}}},

        /* Processing is very late but the change will now be accepted */
        {300, {{0, 1, UP}}, {{0, 1, UP}}},
    });
    time_jumps_ = true;
    runEvents();
}

TEST_F(DebounceTest, OneKeyDelayedScan2) {
    addEvents({ /* Time, Inputs, Outputs */
        {0, {{0, 1, DOWN}}, {{0, 1, DOWN}}},

        /* Processing is very late but the change will now be accepted even with a 1 scan delay */
        {300, {}, {}},
        {300, {{0, 1, UP}}, {{0, 1, UP}}},
    });
    time_jumps_ = true;
    runEvents();
}

TEST_F(DebounceTest, OneKeyDelayedScan3) {
    addEvents({ /* Time, Inputs, Outputs */
        {0, {{0, 1, DOWN}}, {{0, 1, DOWN}}},

        /* Processing is very late but the change will now be accepted even with a 1ms delay */
        {300, {}, {}},
        {301, {{0, 1, UP}}, {{0, 1, UP}}},
    });
    time_jumps_ = true;
    runEvents();
}

TEST_F(DebounceTest, OneKeyDelayedScan4) {
    addEvents({ /* Time, Inputs, Outputs */
        {0, {{0, 1, DOWN}}, {{0, 1, DOWN}}},

        /* Processing is a bit late but the change will now be accepted */
        {50, {{0, 1, UP}}, {{0, 1, UP}}},
    });
    time_jumps_ = true;
    runEvents();
}

TEST_F(DebounceTest, OneKeyDelayedScan5) {
    addEvents({ /* Time, Inputs, Outputs */
        {0, {{0, 1, DOWN}}, {{0, 1, DOWN}}},

        /* Processing is very late but the change will now be accepted even with a 1 scan delay */
        {50, {}, {}},
        {50, {{0, 1, UP}}, {{0, 1, UP}}},
    });
    time_jumps_ = true;
    runEvents();
}

TEST_F(DebounceTest, OneKeyDelayedScan6) {
    addEvents({ /* Time, Inputs, Outputs */
        {0, {{0, 1, DOWN}}, {{0, 1, DOWN}}},

        /* Processing is very late but the change will now be accepted even with a 1ms delay */
        {50, {}, {}},
        {51, {{0, 1, UP}}, {{0, 1, UP}}},
    });
    time_jumps_ = true;
    runEvents();
}
