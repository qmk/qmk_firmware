// Created/amended by OleVoip 2024.
// SPDX-License-Identifier: GPL-2.0-or-later

#include "../databus.h"
#define extern
#include "../databus-kb.h"
#undef extern

// clang-format off
/*
 * Map for LAYOUT_all, with all positions foreseen on the PCB.
 * ST1 is a jumper beside the space bar, AL1 and AL2 are keylocks
 * (actually in the top right corner), both could be used as
 * dip switches.
 *
 *  0   1   2   3   4   5   6   7   8   9  10  11  12  13  14      47  48  49      51  52  53  54
 *┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬─────┐ ┌───┬───┬───┐ ─ ┌───┬───┬───┬───┐
 *│G00│G01│G02│G03│G04│G05│G05│G07│G08│G09│G10│G11│G12│G13│G14  │ │G47│G48│G49│G50│G51│G52│G53│G54│ G
 *└───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴─────┘ ├───┼───┼───┤ ─ ├───┼───┼───┼───┤
 *                                                                │F47│F48│F49│F50│F51│F52│F53│F54│ F
 *┌─────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐ ├───┼───┼───┤ ─ ├───┼───┼───┼───┤
 *│  E00│E01│E02│E03│E04│E05│E06│E07│E08│E09│E10│E11│E12│E13│E14│ │E47│E48│E49│E50│E51│E52│E53│E54│ E
 *├───┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤ ├───┼───┼───┤ ─ ├───┼───┼───┼───┤
 *│D99│D00│D01│D02│D03│D04│D05│D06│D07│D08│D09│D10│D11│D12│D13  │ │D47│D48│D49│D50│D51│D52│D53│D54│ D
 *├───┼───┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴───┴┬──┴┬──┴┬──┴┬──┴─┬───┤ ├───┼───┼───┤ ─ ├───┼───┼───┼───┤
 *│C99│ C00│C01│C02│C03│C04│C05│C06│C07│C08│C09│C10│C11│C12 │C13│ │C47│C48│C49│C50│C51│C52│C53│C54│ C
 *├───┴──┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┤   │ ├───┼───┼───┤ ─ ├───┼───┼───┼───┤
 *│  B99 │B00│B01│B02│B03│B04│B05│B06│B07│B08│B09│B10│ B11  │   │ │B47│B48│B49│B50│B51│B52│B53│B54│ B
 *└──────┴───┴───┼───┴───┴───┴───┴───┴───┴───┴───┼┬──┴─┬───┬┴──┬┘ ├───┼───┼───┤ ─ ├───┴───┼───┤   │
 *               │              A05              │ST1   AL1 AL2   │A47│A48│A49│A50│  A51  │A53│   │ A
 *               └───────────────────────────────┘┘    └ ─ ┴ ─ ┘  └───┴───┴───┘ ─ └───────┴───┴───┘
 */

FCONST labelmap_t key_position_labels = {
    //  0(A)   1(B)   2(C)   3(D)   4(E)   5(F)   6(G)   7(H)
    {"G00", "E01", "D01", "C01", "B00", "F50", "C54", "x07"}, // 0
    {"G01", "E02", "D02", "C02", "B01", "F49", "B53", "x0F"}, // 1
    {"G02", "E03", "D03", "C03", "B02", "F53", "C53", "x17"}, // 2
    {"G03", "E04", "D04", "C04", "B03", "F52", "B52", "A50"}, // 3
    {"G04", "E05", "D05", "C05", "B04", "F51", "B51", "A49"}, // 4
    {"G05", "E06", "D06", "C06", "B05", "F54", "B50", "A48"}, // 5
    {"G06", "E07", "D07", "C07", "B06", "G54", "C51", "A47"}, // 6
    {"G07", "E08", "D08", "C08", "B07", "G53", "D54", "C49"}, // 7
    {"G08", "E09", "D09", "C09", "B08", "D49", "D51", "D48"}, // 8
    {"G09", "E10", "D10", "C10", "B09", "F48", "E52", "E48"}, // 9
    {"G10", "E11", "D11", "C11", "B10", "G52", "C52", "B49"}, // A
    {"G47", "A53", "D50", "B54", "A51", "G48", "E53", "G50"}, // B
    {"G14", "E47", "D47", "C48", "A05", "F47", "E54", "x67"}, // C
    {"G13", "E14", "D99", "C47", "B48", "E49", "D52", "x6F"}, // D
    {"G12", "E13", "D13", "C99", "B47", "G49", "E51", "E50"}, // E
    {"G11", "E12", "D12", "C12", "C13", "G51", "D53", "C50"}, // F
    {"ST1", "E00", "D00", "C00", "B99", "AL1", "AL2", "B11"}  // G
};

// clang-format on

union {
    uint8_t all;
    struct {
        uint8_t
            error:1,
            wait:1,
            line:1,
            car:1,
            l4:1,
            l3:1,
            l2:1,
            l1:1;
    };
} indicators;

// Port B: 8-bit data bus; it has a write-only latch that sinks
// the currents of 8 LED indicators and a read-only buffer for reading
// the keyboard sense lines. Normally, the bus port has input direction
// as the system is mostly busy scanning the keyboard, ie, reading the
// sense lines.

// Port C: 2 extra LEDs, beeper and chip enable flags for the keyboard bus
// driver and indicator latch Beeper needs to be pin 4 or higher since it
// needs PWM.

static inline void update_indicators(void) {
    write_bus_strobing(indicators.all, INDICATORS_LE_PIN, INDICATORS_LE_ACTIVE);
}

void init_bus(void) {
    set_bus_idle();
    init_pin(SENSE_OE_PIN, !SENSE_OE_ACTIVE);

    // toggle indicator latch to switch the indicators off
    indicators.wait = 1;
    update_indicators();
}

void keyboard_pre_init_kb(void) {
    init_pin(POWER_LED_PIN, !POWER_LED_ACTIVE);
    init_pin(PIEZO_PIN, !PIEZO_ACTIVE);
    init_pin(LOCK_LED_PIN, !LOCK_LED_ACTIVE);
    init_pin(CAPS_LED_PIN, !CAPS_LED_ACTIVE);

    keyboard_pre_init_user();
}

bool shutdown_kb(bool jump_to_bootloader) {
    xprintf("Shutdown user!\n");
    if (!shutdown_user(jump_to_bootloader)) {
        return false;
    }
    xprintf("Shutdown keyboard!\n");
    write_pin(POWER_LED_PIN, !POWER_LED_ACTIVE);
    write_pin(LOCK_LED_PIN, !LOCK_LED_ACTIVE);
    write_pin(CAPS_LED_PIN, !CAPS_LED_ACTIVE);
    indicators.all = 0;
    update_indicators();
    return true;
}

#ifdef CAPS_WORD_ENABLE
void caps_word_set_user(bool active) {
    if (active) {
        write_pin(CAPS_LED_PIN, CAPS_LED_ACTIVE);
    } else {
        write_pin(CAPS_LED_PIN, !CAPS_LED_ACTIVE);
    }
}
#endif

/*
MASTER CROSS REFERENCE LIST (MCRL) | NSN 7025-12-318-4235
Manufacturer Part Number	RNCC	RNVC	Manufacturer Name	CAGE
726 02595 CAAA	3 - Design Control Reference	2 - Production Item
THALESELECTRONIC SYSTEMS GMBH	  D8385  	  CAGE D8385 TASTATUR FUER
TANDBERG TDV 2242	6 - Informative Reference	9 - No Longer Used
LOGISTIKKOMMANDO DER	  D2222

7025-12-318-4235
TASTATUR, DATENEING
7025-12-318-4235 (7025123184235, 123184235)
Part Numbers (2 listings): 72602595CAAA | TASTATURFUERTANDBERGTDV2242 |
Summary
FSG 70 / FSC 7025
DEMIL:
DEMIL INT:
HMIC:
Date Created: 13 Jul 1989

Automatisches Führungsfernmeldenetz Luftwaffe, AutoFüFmNLw, kurz AutoFü:
Das gesamte Richtfunknetz, einschl. der digitalen Vermittlungen (System 12)
wurde 2003 an die Streitkräftebasis abgegeben, ab 2006 zurückgebaut und 2010
abgeschaltet.

Tandberg TDV-2200 series (TDV-2242) standard terminal with S12 (SEL
Stuttgart) since 1984.

TDV also used for AXE10 (Ericsson)

 */

// .
