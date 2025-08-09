# Refactor of `keyboards/helix`

This series of PRs aims to align this keyboard's configuration with current standards, and also remove unnecessary contents.

### Refactor `helix/pico` [#25428](https://github.com/qmk/qmk_firmware/pull/25428)
    - Removes redundant `back`, `base`, `sc`, `under`, & `qmk_conf` revisions
    - Migrates legacy defines and configuration to JSON
    - Migrates `default` keymap to JSON
    - Fixes RGB configuration to illuminate 25 LEDs per half
    - Enables standard features like Bootmagic, extrakey, etc.
    - Updates keyboard aliases accordingly

### Refactor `helix/rev2` [#25429](https://github.com/qmk/qmk_firmware/pull/25429)
    - Removes redundant `back`, `base`, `sc`, `under`, & `qmk_conf` revisions
    - Renames `rev2` to `beta`, as the only PCB sources in the official Helix GitHub repository are named "[beta](https://github.com/MakotoKurauchi/helix/tree/master/PCB/beta)", this keyboard's name in QMK Firmware was already "beta", and this PCB is sold under the name "[beta](https://shop.yushakobo.jp/products/oss_pcb?variant=39452554231969)" on the Yushakobo store
    - Migrates legacy defines and configuration to JSON
    - Migrates `default` keymap to JSON
    - Fixes RGB configuration to illuminate 32 LEDs per half
    - Enables standard features like Bootmagic, extrakey, etc.
    - Updates keyboard aliases accordingly
    - Tidy's up OLED code
    - Adds alternate 4 row layout, as this PCB allows users to snap off the bottom row

### Refactor `helix/rev3_{4,5}rows` [#25430](https://github.com/qmk/qmk_firmware/pull/25430)
    - The `rev3_4rows` and `rev3_5rows` firmwares are identical, except for the extra row users can snap off. The 4 row PCB is not sold anywhere as an individual product, only the [5 row PCB](https://shop.yushakobo.jp/products/2143). Thus, this PR removes the aforementioned two build targets and adds a single `rev3` revision
    - Migrates legacy defines and configuration to JSON
    - Migrates `default` keymap to JSON
    - Removes RGB Light configuration
    - Updates keyboard aliases accordingly
    - Tidy's up OLED code
    - Adds alternate 4 row layout, as this PCB allows users to snap off the bottom row

### Migrate helix common configuration [#25433](https://github.com/qmk/qmk_firmware/pull/25433)
    - Migrates common configuration shared between revisions to the top-level keyboard directory
    - Improves `readme.md` to provide more detail regarding PCB revisions
    - Removes unnecessary top-level `rules.mk` file and other general tidying
    - Migrates `beta` and `pico` revisions to use RGB Matrix, which is more appropriate as these PCBs are fit with per-key RGB LEDs
