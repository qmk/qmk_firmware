# AGENTS.md — qmk_firmware (fork)

Cross-tool front door for any AI harness working in this fork.

## Project at a glance

- **What**: Personal fork of [qmk/qmk_firmware](https://github.com/qmk/qmk_firmware). Active work lives in `keyboards/reviung/reviung34/keymaps/mockingbird/` (Reviung34 keymap + companion Marp deck).
- **Upstream**: `qmk/qmk_firmware`. Remote: `upstream`. Default branch: `master`.
- **Fork-only paths**: `keyboards/reviung/reviung34/keymaps/mockingbird/**`, `shared-knowledge/anti-knowledge/**`, this `AGENTS.md`. These do not exist upstream and never PR there.

## Shared knowledge

Cross-project engineering lessons live in `shared-knowledge/anti-knowledge/` (imported via Git subtree from `github.com/mockingb1rdblue/anti-knowledge`). Read its [AGENTS.md](shared-knowledge/anti-knowledge/AGENTS.md) for the layout.

When working in these areas, **load the lesson before touching code**:

| Touching... | Read... |
|---|---|
| `keyboards/reviung/reviung34/keymaps/mockingbird/deck/**` (Marp deck for keyboard), Mermaid diagrams, Reveal previews | `shared-knowledge/anti-knowledge/lessons/decks/marp-reveal-ios-mermaid/index.md` |
| Parallelizing keymap + deck work | `shared-knowledge/anti-knowledge/lessons/process/parallel-agents.md` |
| Any "released a new firmware" or "deck published" claim | `shared-knowledge/anti-knowledge/lessons/process/live-proof.md` |

The lessons there are SSOT. Do not duplicate.

## Upstream-sync safety

This is a fork of QMK. When pulling from `upstream/master`:

- The `shared-knowledge/` subtree, `AGENTS.md`, and `keyboards/reviung/reviung34/keymaps/mockingbird/` are fork-local and should never conflict (they do not exist upstream).
- If a rebase fight emerges, prefer keeping fork-local files. Consider `.gitattributes` with `merge=ours` for `shared-knowledge/**` if QMK ever upstreams that path.

## Updating shared lessons

1. Edit canonical upstream: `cd ../anti-knowledge && $EDITOR lessons/<...>/index.md`.
2. Commit + push upstream.
3. Pull update here: `git subtree pull --prefix=shared-knowledge/anti-knowledge https://github.com/mockingb1rdblue/anti-knowledge.git main --squash`.

Do not edit files under `shared-knowledge/anti-knowledge/` directly here.
