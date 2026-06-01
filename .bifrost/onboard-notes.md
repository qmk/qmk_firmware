# Charon-Cicada Onboarding Notes — qmk_firmware

## No-deploy classification

qmk_firmware is a QMK keyboard firmware fork (C/Python, embedded). No Cloudflare
Worker deploy targets. No wrangler.toml.

## GitHub Actions workflows — RETAINED

All .github/workflows/*.yml files are QMK upstream CI workflows (firmware builds,
linting, format checks, PR automation). None deploy Cloudflare Workers. Per constitution
§4, only workflows that deploy or race with Charon-Cicada must be deleted. These are
firmware CI — they coexist safely.

KNOWN DEFICIENCY: Formal allow-list file (docs/constitutions/cicd/charon-cicada-allow-list.json)
does not exist yet. Once it does, these workflows should be formally registered there.

Charon-Cicada onboarding: only .namespace verification applies. All CD steps N/A.
