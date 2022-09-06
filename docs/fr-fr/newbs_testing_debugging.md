# Test et débugage

Une fois votre clavier configuré avec un firmware custom, vous êtes prêt à le tester. Avec un peu de chance, tout fonctionne parfaitement bien, dans le cas contraire, ce document vous aidera à trouver où se trouve le problème.

## Tester

Tester votre clavier est normalement assez simple. Appuyez chaque touche de votre clavier et assurez-vous qu'il envoie les touches auquel vous vous attendiez. Il existe même des programmes qui vous aideront à vérifier qu'aucune touche ne soit oubliée.

Note: ces programmes ne sont ni fournis ni approuvés par QMK.

* [QMK Configurator](https://config.qmk.fm/#/test/) (Web)
* [Switch Hitter](https://web.archive.org/web/20190413233743/https://elitekeyboards.com/switchhitter.php) (Windows seulement)
* [Keyboard Viewer](https://www.imore.com/how-use-keyboard-viewer-your-mac) (Mac seulement)
* [Keyboard Tester](https://www.keyboardtester.com) (Web)
* [Keyboard Checker](https://keyboardchecker.com) (Web)

## Débuguer

Votre clavier va envoyer des informations de débugage si vous avez `CONSOLE_ENABLE = yes` dans votre fichier `rules.mk`. Par défaut, la sortie est très limitée, mais vous pouvez activer le mode debug pour augmenter la quantité de sortie de débugage. Utilisez le keycode `DEBUG` dans votre keymap, utilisez la fonction [Commande](feature_command.md) pour activer le mode debug ou ajoutez le code suivant à votre keymap.

```c
void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}
```

### Débuguer avec QMK Toolbox

Pour les plateformes compatibles, [QMK Toolbox](https://github.com/qmk/qmk_toolbox) peut être utilisé pour afficher les messages de débugage pour votre clavier.

### Débuguer avec hid_listen

Vous préférez une solution basée sur le terminal? [hid_listen](https://www.pjrc.com/teensy/hid_listen.html), fourni par PJRC, peut aussi être utilisé pour afficher des messages de débugage. Des versions compilées pour Windows, Linux et MacOS sont disponibles.

<!-- FIXME: Describe the debugging messages here. -->

## Envoyer vos propres messages de débugage

Parfois, il est utile d'afficher des messages de débugage depuis votre [code custom](custom_quantum_functions.md). Le faire est assez simple. Commencez par ajouter `print.h` au début de votre fichier:

```c
#include "print.h"
```

Une fois fait, vous pouvez utiliser les fonctions print suivantes:

* `print("string")`: Affiche une simple chaîne de caractères.
* `uprintf("%s string", var)`: Affiche une chaîne de caractères formatée.
* `dprint("string")` Affiche une chaîne de caractère simple, mais uniquement lorsque le mode debug est activé.
* `dprintf("%s string", var)`: Affiche une chaîne de caractère formatée, mais uniquement lorsque le mode debug est activé.

## Exemples de debugage

Si dessous se trouve une liste d'exemples réels de débugage. Pour plus d'information, référez-vous à [Débuguer/Dépanner QMK](faq_debug.md).

### A quelle position de la matrice se trouve cette activation de touche?

Lors du portage ou lorsque vous essayez de diagnostiquer un problème de PCB, il est utile de savoir si une activation de touche est enregistrée correctement. Pour activer le log de ce scénario, ajoutez le code suivant à votre fichier keymaps `keymap.c`.

```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif
  return true;
}
```

Exemple de sortie

```text
Waiting for device:.......
Listening:
KL: kc: 169, col: 0, row: 0, pressed: 1
KL: kc: 169, col: 0, row: 0, pressed: 0
KL: kc: 174, col: 1, row: 0, pressed: 1
KL: kc: 174, col: 1, row: 0, pressed: 0
KL: kc: 172, col: 2, row: 0, pressed: 1
KL: kc: 172, col: 2, row: 0, pressed: 0
```

### Combien de temps cela a pris pour une activation de touche?

Lorsque vous testez des problèmes de performance, il peut être utile de savoir à quelle fréquence la matrice est scannée. Pour activer le log dans ce scénario, ajoutez la ligne suivante à votre fichier `config.h` de votre keymaps.

```c
#define DEBUG_MATRIX_SCAN_RATE
```

Exemple de sortie

```text
  > matrix scan frequency: 315
  > matrix scan frequency: 313
  > matrix scan frequency: 316
  > matrix scan frequency: 316
  > matrix scan frequency: 316
  > matrix scan frequency: 316
```
