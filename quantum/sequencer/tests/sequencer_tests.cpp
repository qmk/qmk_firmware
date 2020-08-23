/* Copyright 2020 Rodolphe Belouin
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

extern "C" {
#include "sequencer.h"
}

class SequencerTest : public ::testing::Test {
   protected:
    void SetUp() override {
        config_copy.enabled = sequencer_config.enabled;

        for (int i = 0; i < SEQUENCER_STEPS; i++) {
            config_copy.steps[i] = sequencer_config.steps[i];
        }

        for (int i = 0; i < SEQUENCER_TRACKS; i++) {
            config_copy.track_notes[i] = sequencer_config.track_notes[i];
        }

        config_copy.tempo      = sequencer_config.tempo;
        config_copy.resolution = sequencer_config.resolution;
        active_tracks_copy     = sequencer_active_tracks;
    }

    void TearDown() override {
        sequencer_config.enabled = config_copy.enabled;

        for (int i = 0; i < SEQUENCER_STEPS; i++) {
            sequencer_config.steps[i] = config_copy.steps[i];
        }

        for (int i = 0; i < SEQUENCER_TRACKS; i++) {
            sequencer_config.track_notes[i] = config_copy.track_notes[i];
        }

        sequencer_config.tempo      = config_copy.tempo;
        sequencer_config.resolution = config_copy.resolution;
        sequencer_active_tracks     = active_tracks_copy;
    }

    sequencer_config_t config_copy;
    uint8_t            active_tracks_copy;
};

TEST_F(SequencerTest, TestOffByDefault) { EXPECT_EQ(is_sequencer_on(), false); }

TEST_F(SequencerTest, TestOn) {
    sequencer_config.enabled = false;

    sequencer_on();
    EXPECT_EQ(is_sequencer_on(), true);

    // sequencer_on is idempotent
    sequencer_on();
    EXPECT_EQ(is_sequencer_on(), true);
}

TEST_F(SequencerTest, TestOff) {
    sequencer_config.enabled = true;

    sequencer_off();
    EXPECT_EQ(is_sequencer_on(), false);

    // sequencer_off is idempotent
    sequencer_off();
    EXPECT_EQ(is_sequencer_on(), false);
}

TEST_F(SequencerTest, TestToggle) {
    sequencer_config.enabled = false;

    sequencer_toggle();
    EXPECT_EQ(is_sequencer_on(), true);

    sequencer_toggle();
    EXPECT_EQ(is_sequencer_on(), false);
}

TEST_F(SequencerTest, TestNoActiveTrackByDefault) {
    for (int i = 0; i < SEQUENCER_TRACKS; i++) {
        EXPECT_EQ(is_sequencer_track_active(i), false);
    }
}

TEST_F(SequencerTest, TestGetActiveTracks) {
    sequencer_active_tracks = (1 << 7) + (1 << 6) + (1 << 3) + (1 << 1) + (1 << 0);

    EXPECT_EQ(is_sequencer_track_active(0), true);
    EXPECT_EQ(is_sequencer_track_active(1), true);
    EXPECT_EQ(is_sequencer_track_active(2), false);
    EXPECT_EQ(is_sequencer_track_active(3), true);
    EXPECT_EQ(is_sequencer_track_active(4), false);
    EXPECT_EQ(is_sequencer_track_active(5), false);
    EXPECT_EQ(is_sequencer_track_active(6), true);
    EXPECT_EQ(is_sequencer_track_active(7), true);
}

TEST_F(SequencerTest, TestGetActiveTracksOutOfBound) {
    sequencer_set_track_activation(-1, true);
    sequencer_set_track_activation(8, true);

    EXPECT_EQ(is_sequencer_track_active(-1), false);
    EXPECT_EQ(is_sequencer_track_active(8), false);
}

TEST_F(SequencerTest, TestToggleTrackActivation) {
    sequencer_active_tracks = (1 << 7) + (1 << 6) + (1 << 3) + (1 << 1) + (1 << 0);

    sequencer_toggle_track_activation(6);

    EXPECT_EQ(is_sequencer_track_active(0), true);
    EXPECT_EQ(is_sequencer_track_active(1), true);
    EXPECT_EQ(is_sequencer_track_active(2), false);
    EXPECT_EQ(is_sequencer_track_active(3), true);
    EXPECT_EQ(is_sequencer_track_active(4), false);
    EXPECT_EQ(is_sequencer_track_active(5), false);
    EXPECT_EQ(is_sequencer_track_active(6), false);
    EXPECT_EQ(is_sequencer_track_active(7), true);
}

TEST_F(SequencerTest, TestToggleSingleTrackActivation) {
    sequencer_active_tracks = (1 << 7) + (1 << 6) + (1 << 3) + (1 << 1) + (1 << 0);

    sequencer_toggle_single_active_track(2);

    EXPECT_EQ(is_sequencer_track_active(0), false);
    EXPECT_EQ(is_sequencer_track_active(1), false);
    EXPECT_EQ(is_sequencer_track_active(2), true);
    EXPECT_EQ(is_sequencer_track_active(3), false);
    EXPECT_EQ(is_sequencer_track_active(4), false);
    EXPECT_EQ(is_sequencer_track_active(5), false);
    EXPECT_EQ(is_sequencer_track_active(6), false);
    EXPECT_EQ(is_sequencer_track_active(7), false);
}

TEST_F(SequencerTest, TestStepOffByDefault) {
    for (int i = 0; i < SEQUENCER_STEPS; i++) {
        EXPECT_EQ(is_sequencer_step_on(i), false);
    }
}

TEST_F(SequencerTest, TestIsStepOffWithNoActiveTracks) {
    sequencer_config.steps[3] = 0xFF;
    EXPECT_EQ(is_sequencer_step_on(3), false);
}

TEST_F(SequencerTest, TestIsStepOffWithGivenActiveTracks) {
    sequencer_set_track_activation(2, true);
    sequencer_set_track_activation(3, true);

    sequencer_config.steps[3] = (1 << 0) + (1 << 1);

    // No active tracks have the step enabled, so it is off
    EXPECT_EQ(is_sequencer_step_on(3), false);
}

TEST_F(SequencerTest, TestIsStepOnWithGivenActiveTracks) {
    sequencer_set_track_activation(2, true);
    sequencer_set_track_activation(3, true);

    sequencer_config.steps[3] = (1 << 2);

    // Track 2 has the step enabled, so it is on
    EXPECT_EQ(is_sequencer_step_on(3), true);
}

TEST_F(SequencerTest, TestIsStepOffForGivenTrack) {
    sequencer_config.steps[3] = 0x00;
    EXPECT_EQ(is_sequencer_step_on_for_track(3, 5), false);
}

TEST_F(SequencerTest, TestIsStepOnForGivenTrack) {
    sequencer_config.steps[3] = (1 << 5);
    EXPECT_EQ(is_sequencer_step_on_for_track(3, 5), true);
}

TEST_F(SequencerTest, TestSetStepOn) {
    sequencer_active_tracks   = (1 << 6) + (1 << 3) + (1 << 2);
    sequencer_config.steps[2] = (1 << 5) + (1 << 2);

    sequencer_set_step(2, true);

    EXPECT_EQ(sequencer_config.steps[2], (1 << 6) + (1 << 5) + (1 << 3) + (1 << 2));
}

TEST_F(SequencerTest, TestSetStepOff) {
    sequencer_active_tracks   = (1 << 6) + (1 << 3) + (1 << 2);
    sequencer_config.steps[2] = (1 << 5) + (1 << 2);

    sequencer_set_step(2, false);

    EXPECT_EQ(sequencer_config.steps[2], (1 << 5));
}

TEST_F(SequencerTest, TestToggleStepOff) {
    sequencer_active_tracks   = (1 << 6) + (1 << 3) + (1 << 2);
    sequencer_config.steps[2] = (1 << 5) + (1 << 2);

    sequencer_toggle_step(2);

    EXPECT_EQ(sequencer_config.steps[2], (1 << 5));
}

TEST_F(SequencerTest, TestToggleStepOn) {
    sequencer_active_tracks   = (1 << 6) + (1 << 3) + (1 << 2);
    sequencer_config.steps[2] = 0;

    sequencer_toggle_step(2);

    EXPECT_EQ(sequencer_config.steps[2], (1 << 6) + (1 << 3) + (1 << 2));
}

TEST_F(SequencerTest, TestSetAllStepsOn) {
    sequencer_active_tracks   = (1 << 6) + (1 << 3) + (1 << 2);
    sequencer_config.steps[2] = (1 << 7) + (1 << 6);
    sequencer_config.steps[4] = (1 << 3) + (1 << 1);

    sequencer_set_all_steps(true);

    EXPECT_EQ(sequencer_config.steps[2], (1 << 7) + (1 << 6) + (1 << 3) + (1 << 2));
    EXPECT_EQ(sequencer_config.steps[4], (1 << 6) + (1 << 3) + (1 << 2) + (1 << 1));
}

TEST_F(SequencerTest, TestSetAllStepsOff) {
    sequencer_active_tracks   = (1 << 6) + (1 << 3) + (1 << 2);
    sequencer_config.steps[2] = (1 << 7) + (1 << 6);
    sequencer_config.steps[4] = (1 << 3) + (1 << 1);

    sequencer_set_all_steps(false);

    EXPECT_EQ(sequencer_config.steps[2], (1 << 7));
    EXPECT_EQ(sequencer_config.steps[4], (1 << 1));
}

TEST_F(SequencerTest, TestSetTempoZero) {
    sequencer_config.tempo = 123;

    sequencer_set_tempo(0);

    EXPECT_EQ(sequencer_config.tempo, 123);
}

TEST_F(SequencerTest, TestIncreaseTempoMax) {
    sequencer_config.tempo = UINT8_MAX;

    sequencer_increase_tempo();

    EXPECT_EQ(sequencer_config.tempo, UINT8_MAX);
}

TEST_F(SequencerTest, TestSetResolutionLowerBound) {
    sequencer_config.resolution = SQ_RES_4;

    sequencer_set_resolution((sequencer_resolution_t)-1);

    EXPECT_EQ(sequencer_config.resolution, SQ_RES_4);
}

TEST_F(SequencerTest, TestSetResolutionUpperBound) {
    sequencer_config.resolution = SQ_RES_4;

    sequencer_set_resolution(SEQUENCER_RESOLUTIONS);

    EXPECT_EQ(sequencer_config.resolution, SQ_RES_4);
}

TEST_F(SequencerTest, TestGetBeatDuration) {
    EXPECT_EQ(get_beat_duration(60), 1000);
    EXPECT_EQ(get_beat_duration(120), 500);
    EXPECT_EQ(get_beat_duration(240), 250);
    EXPECT_EQ(get_beat_duration(0), 1000);
}

TEST_F(SequencerTest, TestGetStepDuration60) {
    /**
     * Resolution cheatsheet:
     * 1/2  => 2 steps per 4 beats
     * 1/2T => 3 steps per 4 beats
     * 1/4  => 4 steps per 4 beats
     * 1/4T => 6 steps per 4 beats
     * 1/8  => 8 steps per 4 beats
     * 1/8T => 12 steps per 4 beats
     * 1/16 => 16 steps per 4 beats
     * 1/16T => 24 steps per 4 beats
     * 1/32 => 32 steps per 4 beats
     *
     * The number of steps for binary resolutions follows the powers of 2.
     * The ternary variants are simply 1.5x faster.
     */
    EXPECT_EQ(get_step_duration(60, SQ_RES_2), 2000);
    EXPECT_EQ(get_step_duration(60, SQ_RES_4), 1000);
    EXPECT_EQ(get_step_duration(60, SQ_RES_8), 500);
    EXPECT_EQ(get_step_duration(60, SQ_RES_16), 250);
    EXPECT_EQ(get_step_duration(60, SQ_RES_32), 125);

    EXPECT_EQ(get_step_duration(60, SQ_RES_2T), 1333);
    EXPECT_EQ(get_step_duration(60, SQ_RES_4T), 666);
    EXPECT_EQ(get_step_duration(60, SQ_RES_8T), 333);
    EXPECT_EQ(get_step_duration(60, SQ_RES_16T), 166);
}

TEST_F(SequencerTest, TestGetStepDuration120) {
    /**
     * Resolution cheatsheet:
     * 1/2  => 2 steps per 4 beats
     * 1/2T => 3 steps per 4 beats
     * 1/4  => 4 steps per 4 beats
     * 1/4T => 6 steps per 4 beats
     * 1/8  => 8 steps per 4 beats
     * 1/8T => 12 steps per 4 beats
     * 1/16 => 16 steps per 4 beats
     * 1/16T => 24 steps per 4 beats
     * 1/32 => 32 steps per 4 beats
     *
     * The number of steps for binary resolutions follows the powers of 2.
     * The ternary variants are simply 1.5x faster.
     */
    EXPECT_EQ(get_step_duration(30, SQ_RES_2), 4000);
    EXPECT_EQ(get_step_duration(30, SQ_RES_4), 2000);
    EXPECT_EQ(get_step_duration(30, SQ_RES_8), 1000);
    EXPECT_EQ(get_step_duration(30, SQ_RES_16), 500);
    EXPECT_EQ(get_step_duration(30, SQ_RES_32), 250);

    EXPECT_EQ(get_step_duration(30, SQ_RES_2T), 2666);
    EXPECT_EQ(get_step_duration(30, SQ_RES_4T), 1333);
    EXPECT_EQ(get_step_duration(30, SQ_RES_8T), 666);
    EXPECT_EQ(get_step_duration(30, SQ_RES_16T), 333);
}
