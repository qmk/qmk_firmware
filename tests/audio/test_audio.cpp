// Copyright 2023 Google LLC
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <cmath>
#include <random>

#include "gtest/gtest.h"
#include "keyboard_report_util.hpp"
#include "test_common.hpp"

namespace {

class AudioTest : public TestFixture {
   public:
    uint16_t infer_tempo() {
        return audio_ms_to_duration(1875) / 2;
    }
};

TEST_F(AudioTest, OnOffToggle) {
    audio_on();
    EXPECT_TRUE(audio_is_on());

    audio_off();
    EXPECT_FALSE(audio_is_on());

    audio_toggle();
    EXPECT_TRUE(audio_is_on());

    audio_toggle();
    EXPECT_FALSE(audio_is_on());
}

TEST_F(AudioTest, ChangeTempo) {
    for (int tempo = 50; tempo <= 250; tempo += 50) {
        audio_set_tempo(tempo);
        EXPECT_EQ(infer_tempo(), tempo);
    }

    audio_set_tempo(10);
    audio_increase_tempo(25);
    EXPECT_EQ(infer_tempo(), 35);

    audio_decrease_tempo(4);
    EXPECT_EQ(infer_tempo(), 31);

    audio_increase_tempo(250);
    EXPECT_EQ(infer_tempo(), 255);

    audio_set_tempo(9);
    EXPECT_EQ(infer_tempo(), 10);

    audio_decrease_tempo(100);
    EXPECT_EQ(infer_tempo(), 10);
}

TEST_F(AudioTest, BpmConversion) {
    const int tol = 1;

    audio_set_tempo(120);
    // At 120 bpm, there are 2 beats per second, and a whole note is 500 ms.
    EXPECT_NEAR(audio_duration_to_ms(64 /* whole note */), 500, tol);
    EXPECT_NEAR(audio_ms_to_duration(500), 64, tol);
    EXPECT_EQ(audio_duration_to_ms(0), 0);
    EXPECT_EQ(audio_ms_to_duration(0), 0);

    audio_set_tempo(10);
    // At 10 bpm, UINT16_MAX ms corresponds to 699/64 beats and is the longest
    // duration that can be converted without overflow.
    EXPECT_NEAR(audio_ms_to_duration(UINT16_MAX), 699, tol);
    EXPECT_NEAR(audio_duration_to_ms(699), 65531, tol);

    audio_set_tempo(255);
    // At 255 bpm, UINT16_MAX ms corresponds to 17825/64 beats and is the longest
    // duration that can be converted without overflow.
    EXPECT_NEAR(audio_ms_to_duration(UINT16_MAX), 17825, tol);
    EXPECT_NEAR(audio_duration_to_ms(17825), 65533, tol);

    std::mt19937                       rng(0 /*seed*/);
    std::uniform_int_distribution<int> dist_tempo(10, 255);
    std::uniform_int_distribution<int> dist_ms(0, UINT16_MAX);

    // Test bpm <-> ms conversions for random tempos and durations.
    for (int trial = 0; trial < 50; ++trial) {
        const int tempo       = dist_tempo(rng);
        const int duration_ms = dist_ms(rng);
        SCOPED_TRACE("tempo " + testing::PrintToString(tempo) + ", duration " + testing::PrintToString(duration_ms) + " ms");

        audio_set_tempo(tempo);
        int duration_bpm = std::round((64.0f / (60.0f * 1000.0f)) * duration_ms * tempo);
        ASSERT_NEAR(audio_ms_to_duration(duration_ms), duration_bpm, tol);

        int roundtrip_ms = std::round((60.0f * 1000.0f / 64.0f) * duration_bpm / tempo);
        // Because of round-off error, duration_ms and roundtrip_ms may differ by
        // about (60 * 1000 / 64) / tempo.
        int roundtrip_tol = tol * (60.0f * 1000.0f / 64.0f) / tempo;
        ASSERT_NEAR(roundtrip_ms, duration_ms, roundtrip_tol);

        // Only test converting back to ms if the result would be in uint16_t range.
        if (roundtrip_ms <= UINT16_MAX) {
            ASSERT_NEAR(audio_duration_to_ms(duration_bpm), roundtrip_ms, tol);
        }
    }
}

} // namespace
