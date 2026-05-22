---
id: lessons/process/live-proof
title: Live-proof shipping rule
tags: [shipping, verification, ci, cloudflare-workers, preflight]
last_reviewed: 2026-05-22
maturity: stable
audience: solo-engineer
---

# Live-proof shipping rule

## Summary

Nothing is done until proven done on the live system. Build success, push success, and `200 OK` from a mutation API are not evidence of shipping — they are intermediate steps. Every "done" claim must include one line of live proof: a fresh read of the live resource showing the new state.

## Key rules

- **Deploy**: `curl -s <live-url>` and grep for a string that only exists in the new version. If the string is missing, deploy again.
- **Remove X**: grep the live payload for X. If X appears anywhere, X is not removed.
- **CF / DNS / WAF change**: re-query the API and show the returned value. Never trust the `200 OK` from a mutation.
- **File served over HTTP**: `curl` the URL and confirm the content is what was written.
- **External system change**: query the system after the action and show its current state.
- **"Shipped" definition**: for Worker/Fly/Vercel projects, shipped = preflight script exits 0 against the live URL. `git push` is necessary but not sufficient.
- If live proof is impossible for some reason (e.g., destructive op, no observable side-effect), say so **explicitly** instead of waving the claim through.

## Patterns and examples

### Pattern: must_contain + must_not_contain preflight

Encode the rule as automation. The preflight script:
1. `curl` the live URL with cache-bust.
2. Assert N `must_contain` strings (recent changes that prove new bundle is serving).
3. Assert N `must_not_contain` strings (regressed-out content, removed features).
4. Optional hash check for non-data-baked outputs.

For data-baked outputs (timestamps, counters in the bundle), the hash check is permanently `[WARN]`; must_contain is the real gate.

### Pattern: one-liner live grep after deploy

```bash
curl -s "https://example.com/page?cb=$(date +%s)" | grep -oE "<unique-new-string>"
```

If output is empty, the deploy did not propagate — check CDN cache, then redeploy.

### Anti-pattern: claiming done on "push pushed cleanly"

`git push` puts code on the remote. It does not deploy. For Worker/Fly/Vercel, the deploy is a separate step. Pushing without deploying ships nothing.

### Anti-pattern: trusting wrangler/fly/vercel exit code

Deploy CLIs can return 0 while CDN propagation is incomplete or while the deploy uploaded to the wrong target. Always finish with the live grep.

### Anti-pattern: showing the local file instead of the live URL

`cat worker/index.html | grep ...` proves nothing about what is serving. The live URL is the only source of truth.

## Tool-specific notes

- **Claude Code**: a hook in `~/.claude/hooks/` can intercept commit/push and remind about live proof. Hooks are tool-specific; the rule itself is not.
- **Cron / scheduled deploys**: a scheduled job's success metric must be a follow-up curl, not the deploy CLI exit code.

## Change log

- 2026-05-22 — created; long-standing global rule, codified after Erebus deck deploy/regression incident where a worker shipped with `?` placeholders despite `wrangler deploy` returning 0 and preflight passing locally.
