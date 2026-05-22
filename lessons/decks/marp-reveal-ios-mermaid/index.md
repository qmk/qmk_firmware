---
id: lessons/decks/marp-reveal-ios-mermaid
title: Marp / Reveal / iOS-mobile / Mermaid PDF deck guidelines
tags: [marp, revealjs, ios, pdf, mermaid, decks, slides, mobile, cloudflare-workers]
last_reviewed: 2026-05-22
maturity: stable
audience: solo-engineer
---

# Marp / Reveal / iOS-mobile / Mermaid PDF deck guidelines

## Summary

Hard-won rules for building presentation decks that ship as **(a)** a Reveal.js web deck on Cloudflare Workers and **(b)** a Marp-built PDF with the same content, with Mermaid diagrams in both, and proper portrait-phone UX. Originated in the Erebus deck (`~/AntiGH/rift-root/decks/erebus`, `https://deck.mock1ngbb.com/erebus`) — see the Change log for incident links.

## Key rules

### Reveal portrait sizing — orientation-aware + reflow CSS

- `revealDims()` MUST branch on orientation. Landscape returns fixed `{width:1280, height:720}`; portrait returns viewport-native `{width: innerWidth, height: innerHeight}`. Reconfigure on `orientationchange` with `Reveal.configure(revealDims())` — no page reload.
- Pass `scrollActivationWidth: 0` to `Reveal.initialize()` to suppress Reveal 5.x mobile scroll-view.
- Force sections to fill the canvas in portrait: `.is-portrait .reveal .slides section { height: 100%; min-height: 100%; display: flex; flex-direction: column; justify-content: space-between; }`.
- Reflow content under `.is-portrait`: multi-column → single column, `kpi-grid` → 2 cols, smaller `font-size`, tighter padding, tables to `font-size: 0.55em`. Target: ≥80% viewport fill (slide bbox / viewport height).
- The `.is-portrait` class is toggled on `<html>` by the same handler that reconfigures Reveal.

### iOS Safari dark chrome — all four required

- `<meta name="theme-color" content="#0a0a0a">` — tints Safari's address bar.
- `<meta name="apple-mobile-web-app-status-bar-style" content="black-translucent">` + `apple-mobile-web-app-capable` — covers the home-screen install case.
- `html, body { overscroll-behavior: none; background: #0a0a0a; }` — suppresses the white rubber-band overscroll area.
- `.reveal-viewport, .reveal-viewport .slides { background: #0a0a0a; }` — belt-and-suspenders on Reveal's wrapper element.
- iOS aggressively caches `theme-color`. Force-refresh to verify.

### Mermaid in Reveal — render BEFORE init

- Reveal sets `display: none` on non-active sections. Mermaid's `getBBox()` returns `{NaN, NaN}` for `display:none` nodes → "Syntax error in text" red box.
- Fix: walk all `.mermaid` blocks, promote each to `display: block; visibility: hidden; position: absolute` off-screen, `await mermaid.run({ nodes })`, then restore. Run **before** `Reveal.initialize()`.
- Verify: `document.querySelectorAll('.mermaid svg').length === <expected>` and no "Syntax error" text in any SVG.

### Mermaid double-box inset fix

- Cause: `.mermaid-box` wrapper with `padding: 18px 22px` + `min-height: 340px` + `align-items: center` creates equal empty strips (~37px) top and bottom that read as a second rectangle.
- Fix: `padding: 0` on `.mermaid-box`, remove `min-height`, child `.mermaid` gets `flex: 1 1 auto`, parent `align-items: stretch`. Drop Mermaid `flowchart.padding` from 16 → 8.

### Marp + Mermaid PDF pipeline

- Marp's PDF pipeline does **not** execute scripts. Inline ` ```mermaid ` blocks render as raw text or ASCII fallback.
- Pre-render each block with `@mermaid-js/mermaid-cli` (mmdc) to **both** SVG (vector) and PNG (broadest embed support):
  ```
  npx -y -p @mermaid-js/mermaid-cli mmdc -i /tmp/x.mmd -o assets/mermaid-N.svg -t dark -b transparent
  npx -y -p @mermaid-js/mermaid-cli mmdc -i /tmp/x.mmd -o assets/mermaid-N.png -t dark -b transparent
  ```
- Replace the code blocks with `<img src="assets/mermaid-N.png">` in the Markdown.
- Build with `npx -y @marp-team/marp-cli@latest --pdf --allow-local-files --html erebus.md -o erebus.pdf`.
- Frontmatter MUST include `html: true` (or pass `--html`). Without it, Marp ignores inline `<div>` flex containers — children stack vertically and overflow the 720px slide.
- Verify ASCII art was removed: `pdftotext erebus.pdf - | grep '┌\|└\|│'` must return 0 matches.

### Cloudflare Worker deploys are global

- `wrangler deploy` overwrites the live worker atomically. Multiple parallel worktree agents deploying to the same worker → last deploy wins, intermediate writes lost.
- Coordinate by: (a) keep each agent's edits to non-overlapping CSS/JS regions, (b) plan an explicit merge step on `main` AFTER all agents return, (c) refresh data + rebuild + deploy ONCE from clean main.

### Worktrees lack gitignored data files

- Worktree agents branch from HEAD with a fresh checkout — they do **not** inherit gitignored files like `surface.json`.
- If they run `node build.mjs` without first running `scrape.mjs`, the build inlines `?` / `"never"` placeholders into the worker bundle. Their preflight still passes (must-contain strings match) but live KPI cards read `?`.
- **Always** re-run `scrape.mjs` on the merged main branch (with the real API key) before the final deploy.

### "Shipped" definition

- Shipped = `preflight-ship.sh <target>` exits 0 against the live URL.
- `git push` alone is **not** shipping.
- Hash check is permanently `[WARN]` for data-baked decks because timestamps and counters change every rebuild. `must_contain` / `must_not_contain` strings are the real shipping gate — encode a recent-change string after every deploy.

### Live proof rule (cross-domain)

- Never trust a `200 OK` from a mutation. After any deploy: `curl` the live URL with cache-bust, grep for a string that only exists in the new version. For "remove X", grep the live payload — X must not appear anywhere.
- See also: [process/live-proof](../../process/live-proof.md).

## Patterns and examples

### Pattern: canonical iterate/deploy chain

```bash
cd decks/<deck>
PROXY_API_KEY=$(bf PROXY_API_KEY) node scrape.mjs    # refresh data
$EDITOR worker/index.html
cd worker && node build.mjs                          # inline data into worker bundle
CLOUDFLARE_API_TOKEN=$(bf CF_WORKERS_TOKEN) \
  CLOUDFLARE_ACCOUNT_ID=a62c1c7880b50ac345fc7c2135f6ae84 \
  npx -y wrangler@latest deploy
bash ../scripts/preflight-ship.sh <deck-name>        # MUST exit 0
```

### Pattern: reusable deck file layout

```
decks/<name>/
├── scrape.mjs        # hits data source, writes surface.json (gitignored)
├── surface.json      # gitignored, baked at build time
├── worker/
│   ├── index.html    # template with {{path}} and {{block:name}} placeholders
│   ├── build.mjs     # surface.json + index.html → worker.js
│   └── wrangler.toml
└── marp/
    ├── deck.md       # html: true frontmatter
    ├── deck.css
    ├── assets/       # pre-rendered mermaid-N.{svg,png}
    └── deck.pdf
```

### Pattern: CSP for Cloudflare Insights beacon

If the zone injects `static.cloudflareinsights.com/beacon.min.js` at the edge, the worker's CSP needs to permit it or the script is blocked in every browser (CF Analytics collects no data):

- Add `https://static.cloudflareinsights.com` to `script-src`.
- Add `https://cloudflareinsights.com` to `connect-src`.

### Anti-pattern: pure viewport-native Reveal dims without reflow CSS

Setting `width: innerWidth, height: innerHeight` on portrait WITHOUT `.is-portrait` reflow rules. Slide content authored for 1280px overflows; top and bottom get cut off. Symptom users report: "isn't framing to viewport, a lot is cut off top and bottom."

### Anti-pattern: fixed 1280x720 + auto-scale on portrait

Reveal scales to ~0.30 on a 390x844 viewport → slide rendered at ~382x216px. Content visible but tiny letterbox (~20% viewport fill). Symptom: "letterbox area looks wrong" or "content too small to read on phone."

### Anti-pattern: claiming "shipped" on git push

`git push` does not redeploy a Cloudflare Worker. Always finish with `wrangler deploy` + preflight + grep live bundle for a string that proves the new version is serving.

## Tool-specific notes

- **Claude Code project memory**: should contain a 1-line pointer to this lesson plus a "Claude-Code-cache" marker. Do not duplicate the body. When this lesson updates upstream, the cache pointer remains valid.
- **Cursor**: a `.cursorrules` snippet can auto-attach this file when editing `decks/**/*.{html,mjs,md}` — see consumer repos for the exact glob.
- **Marp + Reveal cohabitation**: keep `worker/index.html` (Reveal) and `marp/deck.md` (Marp) editorially in sync. Mermaid block sources should match between the two — if you edit a diagram, regenerate both the in-browser render and the pre-rendered SVG/PNG.

## Change log

- 2026-05-22 — created; consolidates Erebus deck session lessons (commits `11c3430`, `02c08e6`, `f182793`, `23d7ef6`, `1457d47` in `rift-root`). Covers Mermaid inset, portrait reflow, iOS dark chrome, Marp PDF pipeline, audit follow-ups.
