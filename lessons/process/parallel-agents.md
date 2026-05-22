---
id: lessons/process/parallel-agents
title: Parallel agent execution
tags: [agents, parallelism, worktrees, merging, claude-code]
last_reviewed: 2026-05-22
maturity: stable
audience: solo-engineer
---

# Parallel agent execution

## Summary

When 2+ independent work items exist, fan out parallel agents instead of doing them serially or deferring. This applies to coding tasks, audits, screenshots, and any work the harness can supervise in the background. The mistakes that turn parallel into chaos are all merge-time and data-freshness issues — manage those explicitly.

## Key rules

- 2+ independent items → spawn agents in parallel in a single message. Mix model tiers: Sonnet for write paths, Haiku for read-only audits/screenshots.
- Write-path agents go in **isolated worktrees**. Read-only agents do not need worktrees.
- Treat worktrees as ephemeral: they branch from HEAD with a fresh checkout. **They do not inherit gitignored files** (data caches, secrets files, build outputs). If the work depends on such a file, refresh it on the merged branch BEFORE the final build/deploy.
- For deploys: the deploy target is **global** (Cloudflare Worker, Fly app, Vercel project, npm package). Multiple agents deploying to the same target race; last write wins. Defer all deploys to the merge step OR confine each agent's deploy window tightly.
- Plan an explicit merge step on the integrating branch (usually `main`) AFTER all agents return. Re-run live verification AFTER the merge — agent-local preflights are not enough.
- Agent claims are not evidence. Verify their findings against live state before logging follow-ups or shipping.
- Audit findings are **time-stamped against the live state at audit start**. If subsequent fixes ship during the audit, re-verify each P0/P1 finding against current live before acting.

## Patterns and examples

### Pattern: 4-agent deck iteration

For a single deck improvement cycle:
- Sonnet A — fix bug class X (worktree, write path)
- Sonnet B — fix bug class Y (worktree, write path, independent files)
- Haiku C — cross-engine parity screenshots (read-only)
- Haiku D — data freshness audit against live API (read-only)

Spawn all four in one tool-call. When they return, merge worktrees sequentially with conflict resolution, re-run data refresh, rebuild, deploy, preflight.

### Pattern: merge protocol after parallel agents

1. Detect which worktrees have changes vs main (`git log main..worktree-branch`).
2. Merge with `--no-ff` so the merge commit captures the agent attribution.
3. Re-run any data-generation step (e.g. `scrape.mjs`) on the merged main — agents' worktrees lacked the gitignored data file.
4. Rebuild from main.
5. Deploy once.
6. Preflight against live.
7. Push.
8. Prune worktree dirs and branches.

### Anti-pattern: trusting agent self-reported preflight

An agent reports `preflight PASS` in its worktree. Its preflight may have run against a worker bundle built **without** the gitignored data file → KPI cards inlined as `?`. Always re-run preflight from main after the final merge+deploy.

### Anti-pattern: serial when parallel works

Doing items one-at-a-time "to keep things simple" wastes wall-clock time and loses the velocity that makes solo engineering competitive. If items are independent, parallelize. The merge complexity is fixed cost per cycle.

## Tool-specific notes

- **Claude Code**: use `Agent` with `isolation: "worktree"` for write paths. Background them with `run_in_background: true` so you get completion notifications. The harness tracks them and re-invokes you on completion — do **not** poll.
- Worktree dirs land under `.claude/worktrees/agent-<id>/` and may need `--force --force` to remove if still locked.

## Change log

- 2026-05-22 — created; consolidates Erebus deck session experience with parallel Sonnet/Haiku agents.
