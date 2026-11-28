# QMK Firmware Fork Roadmap

## Project index

| Project ID | Outcome | Status | Dependencies | Next approval |
| --- | --- | --- | --- | --- |
| `qmk-docs` | Add checkout-specific instructions and document custom keymaps/build commands | Complete | None | None |

## Repository documentation setup

- Project ID: `qmk-docs`
- Scope: add project instructions and planning documents, and update the root
  README with local keymap details and build commands.
- Status: Complete.
- Dependencies: none.
- Risks: build commands are documented from repository configuration and QMK
  CLI conventions; compilation and flashing are not validated as part of this
  documentation-only setup.
- Outputs: root `AGENTS.md` and `CLAUDE.md`; `docs/SPEC.md`,
  `docs/ROADMAP.md`, and `docs/TASKS.md`; updated `readme.md`.
- Exit evidence: documentation files added and README changes reviewed for
  target names, keymap descriptions, and CLI command syntax.

### Change record

| Date | Change | Affected outcome | Reason |
| --- | --- | --- | --- |
| 2026-11-28 | Established repository guidance and documented local keymaps/build workflow | `qmk-docs` | Make this fork's customizations and build entry points discoverable |
