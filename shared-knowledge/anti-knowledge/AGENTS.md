# AGENTS.md — anti-knowledge

This repository is the **canonical, tool-agnostic engineering knowledge base** for the `~/AntiGH/` project tree. It is consumed by other repos via Git subtree under `shared-knowledge/anti-knowledge/`.

## What this is

A plain-Markdown, version-controlled, single-source-of-truth (SSOT) for cross-project lessons. **Lives in Git. Loads in any editor. Survives any AI harness.** Designed so the same content powers:

- Claude Code (loads via per-project `AGENTS.md` and project memory pointers)
- Cursor (loads via `AGENTS.md` + `.cursorrules` pointers)
- Aider (loads via context-file config)
- ChatGPT desktop / Gemini CLI / any future tool (loads via explicit file attach)
- Plain humans reading Markdown
- A future docs MCP server (front-matter is MCP-friendly)

## Layout

```
anti-knowledge/
├── AGENTS.md              ← this file (cross-tool front door)
├── README.md              ← human entry point
├── lessons/
│   ├── decks/
│   │   └── marp-reveal-ios-mermaid/
│   │       └── index.md   ← canonical lesson; one topic = one dir + index.md
│   └── process/
│       ├── parallel-agents.md
│       └── live-proof.md
└── meta/
    └── lesson-template.md
```

One lesson per directory, named `index.md`. Examples and snippets go alongside in the same dir.

## Lesson file conventions

Every `index.md` has YAML front-matter:

```yaml
---
id: lessons/decks/marp-reveal-ios-mermaid
title: Marp / Reveal / iOS-mobile / Mermaid PDF deck guidelines
tags: [marp, revealjs, ios, pdf, mermaid, decks, slides, mobile]
last_reviewed: 2026-05-22
maturity: stable      # draft | stable | deprecated
audience: solo-engineer
---
```

And these sections (in this order):

1. **Summary** — 1-2 paragraphs: what this lesson is and when to use it.
2. **Key rules** — bullet list of must-follow rules; safe for AI to load verbatim.
3. **Patterns and examples** — code snippets, templates, anti-patterns.
4. **Tool-specific notes** — how this lesson interacts with specific harnesses (only if non-obvious).
5. **Change log** — high-level only; Git carries the detail.

## How agents should use this repo

When working in a consuming repo with `shared-knowledge/anti-knowledge/` present:

1. **Before starting work** in a domain that has a lesson, read the relevant `lessons/<topic>/index.md`.
2. **Treat Key rules as binding** unless the consuming repo's own `AGENTS.md` explicitly overrides for a documented reason.
3. **Do not copy lesson content** into the consuming repo, CLAUDE.md, .cursorrules, project memory, or skills. Reference the path instead.
4. **Updating a lesson**: edit `anti-knowledge/lessons/.../index.md` directly, bump `last_reviewed`, commit, push, then run `git subtree pull --prefix=shared-knowledge/anti-knowledge ...` in consumer repos.
5. **A lesson contradicts what you observe live** — trust live observation, then update the lesson (don't blindly follow stale knowledge).

## Anti-patterns (do not do)

- Duplicating lesson text into CLAUDE.md / .cursorrules / project memory.
- Treating `~/.claude/projects/*/memory/` or `~/.claude/skills/*/` as canonical. They are caches and triggers, not SSOT.
- Mixing scratch notes / session transcripts into lesson files. Promote stable patterns deliberately.
- Storing canonical content only as PDF, slide deck, or other binary output.
- Inconsistent directory names across consumers (always `shared-knowledge/anti-knowledge/`).

## Current lessons

| Lesson | Tags | Maturity |
|---|---|---|
| [decks/marp-reveal-ios-mermaid](lessons/decks/marp-reveal-ios-mermaid/index.md) | marp, revealjs, ios, pdf, mermaid, decks, mobile | stable |
| [process/parallel-agents](lessons/process/parallel-agents.md) | agents, parallelism, worktrees, merging | stable |
| [process/live-proof](lessons/process/live-proof.md) | shipping, verification, ci | stable |

## Adding a new lesson

1. `cp -r meta/lesson-template.md lessons/<domain>/<slug>/index.md` (or create the dir + file).
2. Fill in front-matter + the 5 sections.
3. Add a row to the **Current lessons** table above.
4. Commit, push. Run `git subtree pull` in each consumer that needs it.
