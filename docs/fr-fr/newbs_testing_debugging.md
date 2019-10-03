# Tester et débogguer

Une fois que vous avez flashé votre clavier vous êtes prêt pour le tester. Avec un peu de chance to fonctionnera à merveille, mais sinon, ce document vous aidera à comprendre ce qui ne fonctionne pas.

## Tester

Tester votre clavier est habituellement un procédé très simple et consiste en presser chacunes des touches en verifiant que les signaux sont bien reçu par votre ordinateur. Ces programmes vous aideront à vérifier que vos touches fonctionnent bien.

Note :  Ces logiciels ne sont pas proposé ni maintenu par QMK.

* [Switch Hitter](https://elitekeyboards.com/switchhitter.php) (Windows seulement)
* [Keyboard Viewer](https://www.imore.com/how-use-keyboard-viewer-your-mac) (Mac seulement)
* [Keyboard Tester](http://www.keyboardtester.com) (Application web)
* [Keyboard Checker](http://keyboardchecker.com) (Application web)

## Déboguer

Votre clavier affichera des informations de debug si vous avez le paramètre `CONSOLE_ENABLE = yes` dans votre fichier `rules.mk`. Par défaut, il y aura peu d'informations affichées. Cependant, il est possible de passer en mode debug pour augmenter le nombre d'informations affichées. Utilisez le keycode `DEBUG`dans votre keymap. Vous pourrez utiliser la feature [Command](feature_command.md) pour activer le mode debug, ou encore en ajoutant le code suivante à votre clavier.

```c
void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}
```

### Déboguer avec QMK Toolbox

Pour les plateformes compatibles, [QMK Toolbox](https://github.com/qmk/qmk_toolbox) peut être utilisé pour afficher des informations de debug de votre clavier.

### Déboguer avec hid_listen

Vous préferez une solution de debogue par terminal ? [hid_listen](https://www.pjrc.com/teensy/hid_listen.html), proposé par PJRC, permet d'afficher des messages de debug. Des fichiers éxecutables sont disponibles pour Windows, Linux et MacOS.

<!-- FIXME: Describe the debugging messages here. -->

## Envoyer vos propre messages de debug

Parfois il est utile d'afficher ses propres messages de debug grace à du [code personalisé](custom_quantum_functions.md). C'est plutôt simple. Commencez par ajouter `print.h` en haut de votre fichier.

    #include <print.h>

Après ça, vous pourrez utiliser différentes techniques d'impression de messages :

* `print("string")`: Afficher une chaîne de caractère simple.
* `uprintf("%s string", var)`: Afficher une chaîne de caractère formattée.
* `dprint("string")` Afficher une chaîne simple, mais seulement si le mode debug est activée.
* `dprintf("%s string", var)`: Afficher une chaîne formattée, mais seulement si le mode debug est activée.

## Examples de debug

La suite de cette rubrique vous montrera des exemples réèls d'usage du debug. Pour avoir plusieurs d'informations, réferrez vous à la section [Déboguer / Dépanner QMK](faq_debug.md).

### Trouver la position d'une pression de touche sur la matrice

Lors d'une conversion d'un pcb QMK (opération appelée « porting ») ou en tentant de diagnostiquer un problème de pcb, il peut être utile de savoir si une pression de touche est détectée correctement. Afin de déboguer de la sorte, ajoutez le code suivant à votre `keymap.c`.

```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif
  return true;
}
```

Exemple d'affichage : 

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

### Combien de temps prend le scan d'une activation de touche

Quand on teste des problèmes de performances, il peut être utile de savoir à quelle fréquence la matrice est scannée. Pour activer les logs pour ce scénario, ajoutez le code suivant au fichier de configuration `config.h` de votre keymap.

```c
#define DEBUG_MATRIX_SCAN_RATE
```

Example output
```text
  > matrix scan frequency: 315
  > matrix scan frequency: 313
  > matrix scan frequency: 316
  > matrix scan frequency: 316
  > matrix scan frequency: 316
  > matrix scan frequency: 316
```
