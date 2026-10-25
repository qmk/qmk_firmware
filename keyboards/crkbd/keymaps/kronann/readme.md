# Keymap kronann (Corne)

QWERTY US standard, 4 couches, mêmes codes sur macOS et Linux. L'hôte est réglé en US/ABC ; le japonais passe par l'IME (Ctrl+Espace).

Chaque couche se lit : 6 touches gauches, `[intérieure gauche]`, `[intérieure droite]`, 6 touches droites. `▽` = transparente, `·` = aucune action.

## Couches

### BASE

```
Tab   Q W E R T  [←] [↑]  Y U I O P Bksp
Ctrl  A S D F G  [→] [↓]  H J K L ; '
⇧     Z X C V B           N M , . / Esc
        Hyper LOWER Espace   Entrée RAISE Alt
```

Hyper = Super gauche. Shift + Bksp = Suppr.

### LOWER (pouce gauche central)

```
`     1 2 3 4 5  ▽ [WS←]  6 7 8 9 0 Suppr
Ctrl  ! @ # $ %  ▽ [WS→]  ^ & * ( ) ~
⇧     _ + { } |           - = [ ] \ ▽
        ▽ ▽ ABC⇄あ         ▽ ▽ ▽
```

WS←/WS→ = Super+PgUp / Super+PgDn. ABC⇄あ = Ctrl+Espace.

### RAISE (pouce droit central)

```
▽     · · ↑ · ·       ▽ ▽  Début PgDn PgUp Fin Impr ▽
Ctrl  Mol↑ ← ↓ → Lent ▽ ▽  ← ↓ ↑ → · ·
⇧     Mol↓ ClicM ClicD ClicG ·   Muet Vol− Vol+ Lum− Lum+ ▽
        ClicD LOWER ClicG      ▽ ▽ ▽
```

Les flèches et les clics de la main gauche pilotent la souris.

### ADJUST (LOWER + RAISE ensemble)

```
F1    F2 F3 F4 F5 F6  ·  ·  F7 F8 F9 F10 F11 F12
RGB   Teinte+ Sat+ Lum+ Effet+ ·   ·  ·  · · · · · ·
Boot  Teinte− Sat− Lum− Effet− ·   ·  ·  · · · · · Boot
```

Boot est sur les deux coins du bas, pour flasher chaque moitié.

## Compiler et flasher

```bash
qmk compile -kb crkbd/rev4_1/standard -km kronann
```

Flasher chaque moitié : ADJUST + Boot, puis copier `crkbd_rev4_1_standard_kronann.uf2` sur le volume qui apparaît.

## Configuration OS (hors dépôt)

- **Karabiner** : règle limitée au Corne (`vendor_id` / `product_id` du crkbd) qui transforme Ctrl + C V X Z A S F T W N Q R L P en ⌘ + la même touche, sauf si l'application au premier plan est kitty (`net.kovidgoyal.kitty`) ou UTM/Parallels. La règle globale « ⌘ gauche → Hyper » reste globale.
- **skhd** :
  ```
  ctrl + alt + cmd - pageup : yabai -m space --focus prev
  ctrl + alt + cmd - pagedown : yabai -m space --focus next
  ```
- **Hyprland** : rien à changer.
