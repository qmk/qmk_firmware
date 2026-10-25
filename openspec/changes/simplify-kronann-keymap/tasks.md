# Tasks

Vérification commune à chaque tâche : `qmk compile -kb crkbd/rev4_1/standard -km kronann` passe. Le scénario nommé se contrôle au flash avec `/qa-local`.

## 1. Socle

- [x] 1.1 Remplacer les 8 couches par `_BASE, _LOWER, _RAISE, _ADJUST` dans `layers.h`, avec `TRI_LAYER_ENABLE` et `TL_LOWR` / `TL_UPPR` (LOWER, RAISE et ADJUST encore vides). Supprimer `config/custom.c`, `french-unicode.h`, l'unicode, les combos et les options devenues inutiles de `config.h` / `rules.mk` ; vérifier que la compilation passe (tdd: false, nettoyage préalable sans scénario propre)

## 2. Base QWERTY

- [x] 2.1 Scénario « Lettres QWERTY » : écrire les trois rangées de BASE (design.md, Maquettes, BASE) ; maquette `mockups/kronann-remap.html` (tdd: false, firmware sans banc de test)
- [x] 2.2 Scénario « Pas de tap-hold sur la base » : vérifier qu'aucun `*_T()`/`LT()` ne subsiste sur BASE et retirer le réglage de tap-hold restant (tdd: false, firmware sans banc de test)
- [x] 2.3 Scénario « Ctrl identique sur macOS et Linux » : Ctrl et Shift en `KC_LCTL`/`KC_LSFT`, Alt pouce en `KC_LALT`, sans `OS_DETECTION` ni `CG_TOGG` (tdd: false, firmware sans banc de test)
- [x] 2.4 Scénario « Hyper envoie Super gauche » : pouces BASE `KC_LGUI TL_LOWR KC_SPC` / `KC_ENT TL_UPPR KC_LALT` (tdd: false, firmware sans banc de test)
- [x] 2.5 Scénario « Flèches intérieures » : ← → à gauche, ↑ ↓ à droite (tdd: false, firmware sans banc de test)
- [x] 2.6 Scénario « Shift + Bksp = Suppr » : une seule surcharge dans `keymap.c`, suppression de `config/override.c`, `override_keymap.c` et `INTROSPECTION_KEYMAP_C` (tdd: false, firmware sans banc de test)
- [x] 2.7 Scénario « Shift sur la ponctuation » : vérifier qu'aucune autre surcharge ne subsiste (`,` `.` `-` `[` `]` chiffres) (tdd: false, firmware sans banc de test)

## 3. LOWER

- [x] 3.1 Scénario « Chiffres sur LOWER » : chiffres et symboles de LOWER (design.md, Maquettes, LOWER) (tdd: false, firmware sans banc de test)
- [x] 3.2 Scénario « Workspace suivant » : `LGUI(KC_PGUP)` / `LGUI(KC_PGDN)` sur les touches intérieures droites (tdd: false, firmware sans banc de test)
- [ ] 3.3 Scénario « Bascule ABC / japonais » : `LCTL(KC_SPC)` sur Espace dans LOWER (tdd: false, firmware sans banc de test)

## 4. RAISE

- [ ] 4.1 Scénario « Déplacer et cliquer » : souris main gauche et clics aux pouces, `MOUSEKEY_ENABLE = yes` (tdd: false, firmware sans banc de test)
- [ ] 4.2 Scénario « Flèches vim » : navigation et média main droite (tdd: false, firmware sans banc de test)

## 5. ADJUST et LED

- [ ] 5.1 Scénario « Touches de fonction » : F1–F12 sur la rangée du haut d'ADJUST (tdd: false, firmware sans banc de test)
- [ ] 5.2 Scénario « Passage en mode flash » : `QK_BOOT` aux deux coins bas et réglages `RM_*` à gauche (tdd: false, firmware sans banc de test)
- [ ] 5.3 Scénario « LED sur RAISE » : `config/led.c` réduit aux 4 couches (BASE éteinte, une couleur pour chacune des autres) (tdd: false, firmware sans banc de test)

## 6. Documentation

- [ ] 6.1 Créer `keyboards/crkbd/keymaps/kronann/readme.md` : schéma texte des 4 couches, compilation et flash, configuration OS à prévoir (règle Karabiner limitée au Corne, deux lignes skhd) ; vérifier que la commande documentée compile (tdd: false, documentation)
