# Design

## Context

Le keymap `keyboards/crkbd/keymaps/kronann/` (crkbd rev4.1, `LAYOUT_split_3x6_3_ex2`, 46 touches) se compose aujourd'hui de :
- `keymap.c` : 8 couches ;
- `french-unicode.h` : enum des couches, codepoints unicode, keycodes maison ;
- `config/custom.c` : triple taps et `uprintf` de debug alors que la console est désactivée ;
- `config/override.c` : 18 surcharges Shift, inclus par `override_keymap.c` via `INTROSPECTION_KEYMAP_C` ;
- `config/led.c` : couleurs par couche.

Le build actuel passe. Motivation : voir proposal.md, section Why.

Côté OS, c'est la configuration existante qui fixe certains choix :
- Hyprland : le modificateur est `SUPER`. `SUPER+Page_Up/Page_Down` change déjà de workspace (focus -1/+1).
- Karabiner : une règle globale transforme ⌘ gauche en Ctrl+Alt+⌘ (Hyper pour skhd), avec Raycast si la touche est tapée seule.
- macOS : sources de saisie ABC + Kotoeri romaji.

## Goals / Non-Goals

**Goals:**
- Un keymap lisible : `keymap.c`, `config.h`, `rules.mk` et `config/led.c`, sans keycode maison.
- Des mécanismes QMK standards, plutôt que du code maison.

**Non-Goals:**
- Modifier les fichiers de configuration OS (Karabiner, skhd, Hyprland, kitty) : ils sont seulement documentés.
- Le problème des workspaces au-delà de 4 sous yabai : sujet à part.
- Les accents français dans le firmware : c'est l'OS qui les gère (⌥ sur Mac, Compose sur Linux).
- Une couche GAME : la base sans tap-hold sert aussi pour jouer.

## Decisions

### Couches et tri-layer
On garde l'enum `_BASE, _LOWER, _RAISE, _ADJUST`, dans cet ordre (1, 2, 3 pour les couches hautes), et on active `TRI_LAYER_ENABLE = yes` avec les keycodes `TL_LOWR` / `TL_UPPR`. Ainsi ADJUST s'active quand LOWER et RAISE sont tenus ensemble, sans code.
- Écarté : `layer_state_set_user` + `update_tri_layer_state`, du code pour rien.
- Écarté : `TT` / `OSL`, des comportements temporels que l'on veut justement supprimer.

### Codes identiques sur les deux OS
Ni `OS_DETECTION` ni `CG_TOGG`. Le firmware ne peut pas savoir quelle application est au premier plan, alors que Karabiner le sait.
- Écarté : l'échange Ctrl/⌘ dans le firmware, qui casserait Ctrl+C (interruption) dans kitty.

### Modificateurs
- Ctrl : `KC_LCTL` ; Shift : `KC_LSFT`.
- Hyper : `KC_LGUI`. Sous Linux c'est le `SUPER` de Hyprland ; sur Mac, la règle Karabiner existante le transforme en Ctrl+Alt+⌘.
- Alt (pouce droit extérieur) : `KC_LALT` et non `KC_RALT`, parce que sous Linux, Alt droit peut être AltGr ou Compose selon la disposition.

### Touches spéciales
- Workspace précédent/suivant : `LGUI(KC_PGUP)` / `LGUI(KC_PGDN)`.
- Bascule IME : `LCTL(KC_SPC)`.
- Souris : keycodes `MS_*` (`MS_UP`, `MS_LEFT`, `MS_BTN1`, `MS_WHLU`, `MS_ACL0`…), avec `MOUSEKEY_ENABLE = yes` explicite dans `rules.mk`.
- RGB : keycodes `RM_*` (`RM_TOGG`, `RM_HUEU`/`RM_HUED`, `RM_SATU`/`RM_SATD`, `RM_VALU`/`RM_VALD`, `RM_NEXT`/`RM_PREV`), qui remplacent les `RGB_*` dépréciés.
- Boot : `QK_BOOT` sur les deux touches extérieures du bas d'ADJUST, pour pouvoir flasher chaque moitié.

### Surcharge Shift + Bksp
Une seule surcharge, `ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL)`, déclarée directement dans `keymap.c`. Disparaissent alors `override_keymap.c`, `config/override.c` et la ligne `INTROSPECTION_KEYMAP_C`.

### Nettoyage
- Fichiers supprimés : `config/custom.c`, `french-unicode.h`.
- L'enum des couches passe dans un `layers.h` qui ne contient qu'elle, inclus par `keymap.c` et `config/led.c`.
- `rules.mk` : retrait de `UNICODE_*` et `COMBO_ENABLE`.
- `config.h` : retrait de `COMBO_*`, `UNICODE_SELECTED_MODES`, `TAPPING_TOGGLE` et `FLOW_TAP_TERM`.

### Vérification
Le keymap n'a pas de banc de test automatisé. Chaque tâche est donc en `tdd: false`, vérifiée par `qmk compile -kb crkbd/rev4_1/standard -km kronann`. Les scénarios se contrôlent au flash avec `/qa-local`, sur macOS et sur Linux, avec un visualiseur de touches : Karabiner-EventViewer sur Mac, `wev` sous Linux.
- Écarté : un test qui comparerait la sortie de `qmk c2json` à la spec. Il vérifierait les positions mais pas le comportement (surcharge, tri-layer, souris), pour un coût d'outillage disproportionné.

## Maquettes

`mockups/kronann-remap.html` : page qui dessine les 4 couches, chacune sur un Corne complet (deux moitiés de 6 colonnes, une colonne intérieure de 2 touches, 3 pouces). Un bouton Linux / macOS change le libellé des modificateurs. Points visuels à respecter :
- **BASE**
  - Gauche : `Tab Q W E R T`, `Ctrl A S D F G`, `⇧ Z X C V B`.
  - Droite : `Y U I O P Bksp`, `H J K L ; '`, `N M , . / Esc`.
  - Touches intérieures : ← → à gauche, ↑ ↓ à droite.
  - Pouces gauches, de l'extérieur vers l'intérieur : `Hyper LOWER Espace` ; pouces droits, de l'intérieur vers l'extérieur : `Entrée RAISE Alt`.
- **LOWER**
  - Gauche : `` ` 1 2 3 4 5 ``, `Ctrl ! @ # $ %`, `⇧ _ + { } |`.
  - Droite : `6 7 8 9 0 Suppr`, `^ & * ( ) ~`, `- = [ ] \ ▽`.
  - Intérieur droit : WS ← (haut), WS → (milieu).
  - Pouce Espace : ABC⇄あ. LOWER est mis en évidence.
- **RAISE**
  - Gauche : `▽ · · ↑ · ·`, `Ctrl Mol↑ ← ↓ → Lent`, `⇧ Mol↓ ClicM ClicD ClicG ·`. Les pouces gauches deviennent `ClicD LOWER→ADJUST ClicG`.
  - Droite : `Début PgDn PgUp Fin Impr ▽`, `← ↓ ↑ → · ·`, `Muet Vol− Vol+ Lum− Lum+ ▽`.
- **ADJUST**
  - Gauche : `F1–F6`, `RGB Teinte+ Sat+ Lum+ Effet+ ·`, `Boot Teinte− Sat− Lum− Effet− ·`.
  - Droite : `F7–F12`, rangée vide, `· · · · · Boot`.

`▽` = transparent (touche de la couche du dessous) ; `·` = aucune action (`XXXXXXX`).

## Configuration OS (hors dépôt, à documenter dans le README du keymap)

- **Karabiner** : nouvelle règle limitée au Corne (`vendor_id` / `product_id` du crkbd). Ctrl + C V X Z A S F T W N Q R L P → ⌘ + même touche, sauf si l'application au premier plan est kitty (`net.kovidgoyal.kitty`) ou UTM/Parallels. La règle globale « ⌘ gauche → Hyper » doit rester globale.
- **skhd** : `ctrl + alt + cmd - pageup : yabai -m space --focus prev` et `ctrl + alt + cmd - pagedown : yabai -m space --focus next`.
- **Hyprland** : rien à changer.

## Risks / Trade-offs

- [Le vrai ⌃ Ctrl de macOS hors kitty n'existe plus que pour les lettres hors liste] → La liste Karabiner reste courte, et Ctrl+Tab ou les autres combinaisons restent du vrai ⌃.
- [1–5 en jeu demandent de tenir LOWER] → Si ça gêne, on ajoutera une couche GAME dans un changement séparé.
- [Muscle memory Ergo-L perdue] → Assumé, c'est l'objet du changement. L'ancien keymap reste dans l'historique git de `krn`.
- [Le firmware compile, mais une moitié flashée avec l'ancien firmware garde l'ancien comportement] → Flasher les deux moitiés, Boot étant accessible des deux côtés.

## Migration Plan

Flasher la moitié gauche, puis la moitié droite (ADJUST + Boot de chaque côté, puis copie du `.uf2`). Pour revenir en arrière, recompiler depuis le commit précédent de `krn` et reflasher.
