# Proposal

## Why

Le keymap `crkbd/kronann` a été pensé pour apprendre Ergo-L et taper le français par unicode sous Linux. Il compte 8 couches, des homerow mods, des surcharges Shift et du code maison (triple tap). Au quotidien, il faut un clavier QWERTY simple, utilisé au Japon (hôte en ABC + IME romaji), qui se comporte pareil sur macOS (yabai/skhd/Karabiner) et sur Linux (Hyprland), et qui permet de piloter la souris sans bouger les mains.

## What Changes

- **BREAKING** : la base Ergo-L est remplacée par un QWERTY standard, sans homerow mods ni tap-hold.
- **BREAKING** : on passe de 8 couches à 4, `BASE`, `LOWER` (chiffres, symboles, workspaces, IME), `RAISE` (souris à gauche, navigation et média à droite) et `ADJUST` (F1–F12, RGB, Boot), cette dernière s'activant en tenant LOWER et RAISE ensemble. Les couches `NAVIGATION`, `BOOT`, `SYMBOLES`, `CODE`, `MOUSE`, `GAME` et `NUMBERS` disparaissent.
- **BREAKING** : la saisie unicode des accents français, les surcharges Shift (sauf Shift+Bksp = Suppr) et les triple taps vers GAME, BOOT et RESET sont supprimés.
- Le pouce gauche extérieur envoie Super gauche (« Hyper »), et le firmware envoie les mêmes codes quel que soit l'OS. Côté Mac, Karabiner s'occupe du comportement propre à chaque application.
- Des touches dédiées s'ajoutent : workspace précédent/suivant (Super+PgUp/PgDn) et bascule ABC ⇄ japonais (Ctrl+Espace).
- La documentation du keymap est complétée : schéma des couches et configuration OS à prévoir (Karabiner, skhd).

## Capabilities

### New Capabilities

- `kronann-keymap` : disposition et comportement du clavier Corne `kronann` (couches, modificateurs, touches spéciales, indicateurs LED), identiques sur macOS et Linux.

### Modified Capabilities

Aucune.

## Impact

- Code : `keyboards/crkbd/keymaps/kronann/` (`keymap.c`, `config.h`, `rules.mk`, `config/led.c`). Disparaissent `config/custom.c`, `config/override.c`, `override_keymap.c` et `french-unicode.h`.
- Build : `qmk compile -kb crkbd/rev4_1/standard -km kronann`.
- Hors dépôt, documenté seulement : une règle Karabiner (Ctrl → ⌘ hors kitty, limitée au Corne) et deux lignes skhd (workspace précédent/suivant). La configuration Hyprland reste inchangée.
- Maquette : `mockups/kronann-remap.html`.
