# Project instructions

## Purpose

This repository is a QMK Firmware fork. Its local customizations include
NickGetka keymaps for the Planck rev6 Drop, Planck EZ, ErgoDox EZ, and Keychron
Q8 ANSI encoder. The root [README](./readme.md) documents those keymaps and
their build commands.

## Working boundaries

- Preserve unrelated work and keep firmware changes within the requested
  scope.
- Treat upstream QMK code and local keymaps as distinct; avoid changing
  upstream behavior when a keymap-level change is sufficient.
- Do not flash a connected keyboard unless explicitly requested.
- Do not remove keyboard definitions or modify shared QMK behavior without
  explicit scope.

## Keymap layer diagrams

- Keep a readable comment diagram immediately above each layer definition in
  `keymap.c`.
- When adding a layer, add its diagram. When changing a layer's name, key
  positions, or keycodes, update the diagram in the same change.
- Ensure each diagram matches the actual layout and key assignments, including
  transparent and unassigned keys. Follow the keymap's existing diagram style.

## Build

Install the QMK CLI and platform build dependencies using the official
[getting started guide](https://docs.qmk.fm/#/newbs_getting_started). From the
repository root, compile the local keymaps with:

```sh
qmk compile -kb planck/rev6_drop -km NickGetka
qmk compile -kb zsa/planck_ez/base -km NickGetka
qmk compile -kb ergodox_ez/base -km NickGetka
qmk compile -kb keychron/q8/ansi_encoder -km NickGetka
```

## Project documentation

- `docs/SPEC.md` records repository facts and documentation requirements.
- `docs/ROADMAP.md` tracks project outcomes and their status.
- `docs/TASKS.md` tracks work and validation evidence.
- The [QMK project documentation](./docs/) is specific to this checkout; use
  upstream QMK documentation for general firmware behavior.
