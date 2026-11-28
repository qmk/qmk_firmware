# QMK Firmware Fork Specification

## Project identity

- Project ID: `qmk-docs`
- Repository: QMK Firmware fork (`getkan/getkan-qmk`)
- Purpose: maintain QMK firmware and personal keyboard keymaps in this
  checkout.

## Verified project facts

- QMK is a C-based keyboard firmware project with keyboard definitions under
  `keyboards/`; keymaps are selected with the QMK CLI.
- This fork contains NickGetka keymaps for:
  - Planck rev6 Drop: `planck/rev6_drop`
  - Planck EZ: `zsa/planck_ez/base`
  - ErgoDox EZ: `ergodox_ez/base`
  - Keychron Q8 ANSI encoder: `keychron/q8/ansi_encoder`
- A fork-specific commit removes unused keyboard definitions and consolidates
  local keymaps.
- Planck-family keymaps provide LOWER, RAISE, and combined ADJUST layers,
  symbol overrides, and keyboard-specific indicator/audio behavior.
- The Q8 keymap provides Mac and Windows base layers, transparent function
  layers, and a volume encoder.
- Shared NickGetka userspace rules enable key overrides for all four keymaps;
  the Q8 keymap also enables the encoder map.

## Environment baseline

- The firmware build uses the QMK CLI and its platform-specific compiler and
  build dependencies. Install them according to the
  [QMK getting started guide](https://docs.qmk.fm/#/newbs_getting_started).
- The repository includes Python CLI dependencies in `requirements.txt`.
- QMK's compile command accepts a keyboard and keymap identifier:
  `qmk compile -kb <keyboard> -km <keymap>`.
- The host operating system, installed QMK CLI version, and installed compiler
  versions are not established by repository files.
- The documented target commands are in the root [README](../readme.md).

## Documentation requirements

- Keep root README project context, custom keymap summary, and build/flash
  instructions current.
- Describe only customizations confirmed in the keymap source and keymap
  documentation.
- Keep QMK upstream guidance linked rather than duplicating platform setup
  instructions.
- Do not imply that firmware compilation or keyboard flashing has been tested
  unless it has actually been run.

## Non-goals

- This documentation setup does not change firmware logic or keymap behavior.
- It does not define a new keyboard, add a feature, or claim exhaustive
  compatibility with every upstream QMK target.
- It does not establish a local toolchain version or deployment process.

## Acceptance criteria

- The README lists all four local custom keymap targets and their QMK compile
  commands.
- The README summarizes the keymap customizations without contradicting their
  source or existing keymap notes.
- Project instructions and planning documents identify the actual repository
  and its documentation locations.
- Documentation-only changes are inspected in the final diff. Firmware builds
  are not required for this documentation task.

## Approved changes

### `qmk-docs` — repository setup and README

- Record verified custom keymaps, supported build target identifiers, and
  QMK CLI workflow.
- Add repository instructions and planning documents without modifying
  firmware sources.

## Unresolved questions

- Which host OS and QMK/compiler versions are used for local builds?
