// Copyright 2026 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// Unit test for qmk/hello_world community module. Run this test with:
// make test:community_module:qmk/hello_world

#include "keyboard_report_util.hpp"
#include "keycode.h"
#include "test_common.hpp"
#include "test_fixture.hpp"
#include "test_keymap_key.hpp"

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::AnyOf;
using ::testing::InSequence;

extern "C" {
#include "community_modules.h"
#include "introspection.h"
}

class HelloWorld : public TestFixture {};

TEST_F(HelloWorld, SendsHelloOnKeypress) {
    TestDriver driver;
    KeymapKey  key_hello(0, 0, 0, COMMUNITY_MODULE_HELLO);
    set_keymap({key_hello});

    EXPECT_CALL(driver, send_keyboard_mock(AnyOf(KeyboardReport(), KeyboardReport(KC_LSFT)))).Times(AnyNumber());

    { // Expect a sequence of reports typing "Hello there."
        InSequence s;
        EXPECT_REPORT(driver, (KC_LSFT, KC_H));
        EXPECT_REPORT(driver, (KC_E));
        EXPECT_REPORT(driver, (KC_L));
        EXPECT_REPORT(driver, (KC_L));
        EXPECT_REPORT(driver, (KC_O));
        EXPECT_REPORT(driver, (KC_SPC));
        EXPECT_REPORT(driver, (KC_T));
        EXPECT_REPORT(driver, (KC_H));
        EXPECT_REPORT(driver, (KC_E));
        EXPECT_REPORT(driver, (KC_R));
        EXPECT_REPORT(driver, (KC_E));
        EXPECT_REPORT(driver, (KC_DOT));
    }

    tap_key(key_hello);

    VERIFY_AND_CLEAR(driver);
}

TEST_F(HelloWorld, Introspection) {
    fprintf(stderr, "Introspection: total_size=%d, layer_count=%d\n", hello_world_introspection().total_size, hello_world_introspection().layer_count);
    EXPECT_GT(hello_world_introspection().total_size, 0);
    EXPECT_GT(hello_world_introspection().layer_count, 0);
}
