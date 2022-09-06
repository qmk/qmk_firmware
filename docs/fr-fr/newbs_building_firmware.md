# Compiler Votre Premier Firmware

Maintenant que vous avez configuré votre environnement de build, vous être prêts à compiler un firmware customisé. Pour cette section, nous allons utiliser trois programmes différents: votre explorateur de fichier, votre éditeur de texte et votre fenêtre de terminal. Gardez les 3 ouverts jusqu'à ce que vous ayez terminé et soyez content de votre firmware de clavier.

Si vous avez fermé et rouvert votre fenêtre de terminal depuis le démarrage de ce guide, n'oubliez pas de `cd qmk_firmware` afin que votre terminal soit dans le bon répertoire.

## Naviguez vers votre répertoire keymaps

Démarrez par naviguer dans le répertoire `keymaps` de votre clavier.

?> Si vous êtes sous macOS ou Windows, il y a des commandes que vous pouvez utiliser pour facilement ouvrir le dossier keymaps.

?> macOS:

    open keyboards/<keyboard_folder>/keymaps

?> Windows:

    start .\\keyboards\\<keyboard_folder>\\keymaps

## Créez une copie de la keymap `default`

Une fois le dossier `keymaps` ouvert, créez une copie du répertoire `default`. Nous vous recommandons de nommer ce répertoire de la même manière que votre nom d'utilisateur GitHub. Vous pouvez aussi utiliser le nom que vous voulez, tant qu'il contient uniquement des lettres minuscules, des nombres et le caractère souligné (_).

Afin d'automatiser ce processus, vous avez aussi l'option de lancer le script `new_keymap.sh`.

Naviguez vers le répertoire `qmk_firmware/util` et tapez ce qui suit:

```
./new_keymap.sh <keyboard path> <username>
```

Par exemple, pour un utilisateur s'appeleant John, essayant de créer une nouvelle keymap pour le 1up60hse, il taperait:

```
./new_keymap.sh 1upkeyboards/1up60hse john
```

## Ouvrez `keymap.c` dans votre éditeur de texte préféré

Ouvrez votre fichier `keymap.c`. Dans ce fichier, vous trouverez la structure qui contrôle comment votre clavier se comporte. En haut du fichier `keymap.c` il peut y avoir quelques `defines` et `enums` qui rendent la keymap plus simple à lire. Plus bas, vous trouverez une ligne telle que celle-ci:

    const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

Cette ligne indique le début d'une liste de calques (layers). En dessous, vous trouverez des lignes contenant soit `LAYOUT`, soit `KEYMAP` et ces lignes indiquent le début d'un calque. En dessous de cette ligne se trouve la liste des touches qui comprennent ce calque particulier.

!> Lorsque vous éditez votre fichier keymap, faites attention à ne pas ajouter ou enlever une virgule. Si vous le faites, vous aller empêcher votre firmware de compiler et il ne sera pas facile de trouver où la virgule est manquante ou en trop.

## Customisez le layout à votre goût

Libre à vous de choisir comment compléter cette étape. Faites le petit changement qui vous dérange ou retravaillez tout de zéro. Vous pouvez supprimer des calques si vous ne les utilisez pas tous, ou ajouter des calques jusqu'à un maximum de 32. Vérifiez la documentation suivante pour trouver ce que vous pouvez définir ici:

* [Keycodes](keycodes.md)
* [Fonctionnalités](features.md)
* [FAQ](faq.md)

?> Lorsque vous découvrez comment des keymaps fonctionnent, faites de petits changements. De gros changements rendent le débuggage des problèmes éventuels plus difficile.

## Compilez votre firmware

Lorsque les changements de votre keymap sont complets, vous allez devoir compiler le firmware. Pour ce faire, retournez à votre terminal et lancez la commande de compilation:

    make <my_keyboard>:<my_keymap>

Par exemple, si votre keymap s'appelle "xyverz" et vous compilez une keymap pour une plank rev5, vous allez utiliser cette commande:

    make planck/rev5:xyverz

Durant la compilation, vous allez avoir beaucoup de messages sur l'écran vous informant de quels fichiers sont en train d'être compilés. Il devrait se terminer avec des messages qui ressemblent comme suit:

```
Linking: .build/planck_rev5_xyverz.elf                                                              [OK]
Creating load file for flashing: .build/planck_rev5_xyverz.hex                                      [OK]
Copying planck_rev5_xyverz.hex to qmk_firmware folder                                               [OK]
Checking file size of planck_rev5_xyverz.hex                                                        [OK]
 * File size is fine - 18392/28672
```

## Flasher votre firmware

Allez sur la page [Flasher le firmware](fr-FR/newbs_flashing.md) pour apprendre comment écrire votre nouveau firmware sur votre clavier.
