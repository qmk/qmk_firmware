# anti-knowledge

Cross-project engineering knowledge base for the `~/AntiGH/` tree. Plain Markdown, version-controlled, tool-agnostic.

**Read [AGENTS.md](AGENTS.md) first** — it is the canonical entry point for both humans and AI tools, and explains the layout, lesson conventions, and how consumers import this repo.

## Quick links

- [Marp / Reveal / iOS / Mermaid deck lessons](lessons/decks/marp-reveal-ios-mermaid/index.md)
- [Parallel agent execution](lessons/process/parallel-agents.md)
- [Live-proof shipping rule](lessons/process/live-proof.md)
- [Lesson template](meta/lesson-template.md)

## Consuming this repo

In any project under `~/AntiGH/`:

```bash
cd ~/AntiGH/<project>
git subtree add --prefix=shared-knowledge/anti-knowledge \
  git@github.com:mockingb1rdblue/anti-knowledge.git main --squash
```

Then add an `AGENTS.md` at the project root pointing at the relevant lesson paths under `shared-knowledge/anti-knowledge/lessons/`.

## Updating lessons

Edit `lessons/<domain>/<slug>/index.md` in this repo, bump `last_reviewed`, commit, push. In each consumer that needs the update:

```bash
git subtree pull --prefix=shared-knowledge/anti-knowledge \
  git@github.com:mockingb1rdblue/anti-knowledge.git main --squash
```
