# Fabriquez votre premier firmware

Maintenant que vous avez installé et configuré votre environnement vous êtes désormais prêt à créer votre premier firmware personalisé. Pour cette section du guide nous allons naviguer entre trois différents logiciels : votre éditeur de texte, votre explorateur de fichiers et votre terminal de ligne de commande. Gardez-les ouverts tant que vous n’avez pas terminé et que vous n’êtes pas heureux de votre résultat.

Si vous avez férmé et réouvert votre terminal alors n’oubliez pas de vous repositionner sur le dossier `qmk_firmware` grâce à la commande `cd qmk_firmware` afin que les commandes décrites ci-dessous fonctionnent.

## Naviguez dans le dossier des keymaps

Commencez par naviguer dans le dossier `keymaps` de votre clavier.

?> Si vous êtes sur macOS ou Windows il y a quelques commandes qui vous permettront d’ouvrir facilement le dossier des keymaps.

?> macOS:

    open keyboards/<keyboard_folder>/keymaps

?> Windows:

    start .\\keyboards\\<keyboard_folder>\\keymaps

## Créez une copie de la keymap `default`

Une fois que vous avez le dossier `keymap` d’ouvert vous allez pouvoir créer une copie du dossier `default` afin de partir d’une base saine et simple. Nous recommandons fortement de nommer votre dossier de la même manière que votre nom d’utilisateur Github mais vous pouvez utiliser le nom que vous voulez tant qu’il contient uniquement des minuscules, des nombres et des underscores.

Pour automatiser le processus, vous pouvez aussi lancer la commande `new_keymap.sh`.

Naviguez dans le dossier `qmk_firmware/util` et saisissez :

```
./new_keymap.sh <keyboard path> <username>
```

Par exemple, un utilisateur nommé Jean qui souhaite créer une nouvelle keymap pour le clavier 1up60hse devra saisir :

```
./new_keymap.sh 1upkeyboards/1up60hse jean
```

## Ouvrez `keymap.c` dans votre éditeur de texte favori

Ouvrez votre fichier `keymap.c`. À l’intérieur, vous trouverez la structure qui permet de contrôler le comportement de votre disposition de clavier. En haut du fichier se trouvent quelques définitions et énumérations rendant la disposition compréhensible. En dessous, vous trouverez une ligne qui ressemble à ça:

    const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

Cette ligne indique le début de la liste des layers. Un layer est une couche de caractères. Le premier contiendra certainement les codes du clavier « Qwerty » car ce sont les codes de qwerty qui sont utilisés dans la norme keyboard_hid. Les autres layers proposeront toutes sortes de fonctions comme les touches médias ou des macros. On y accéde generalement par des touches modificatrices comme `Fn`.
En dessous vous trouverez des lignes contenant `LAYOUT` ou `KEYMAP`. Ces lignes indiquent le début d’un layer. En dessous de ces lignes se trouvent les différents codes de caractères de ce layer.

!> En éditant votre disposition (keymap), attention à ne pas ajouter ou supprimer des virgules. Si vous le faite, vous allez empêcher votre clavier de compiler et il peut être délicat de comprendre ou se trouve les virgules manquantes ou en trop.

## Modifiez la disposition selon vos besoins

La manière dont vous pouvez compléter cette étape est très personnelle. Réalisez les changements qui vous plaisent. Vous pouvez supprimer des layers si vous n'en avez pas besoin ou en ajouter de nouveaux jusqu'à un nombre de 32. Vous pouvez vous diriger sur ces différentes sections pour comprendre comment paramétrer votre keymap :

* [Keycodes](keycodes.md)
* [Fonctionnalités](features.md)
* [FAQ](faq.md)

?> Modifiez votre keymap tant que vous le souhaitez mais réalisez des petits changements. De gros changements seront plus compliqués à débugger si des problèmes se manifestent.

## Fabriquez votre firmware

Quand vos changements seront complets vous aurez besoin de compiler votre firmware. Pour ceci, rendez vous sur votre terminal et lancez les commandes suivantes :

    make <my_keyboard>:<my_keymap>

Par exemple si votre keymap est nommée "xyverz" et qu'elle se destine à un clavier planck de révision 5 vous pouvez utiliser cette commande :

    make planck/rev5:xyverz

Lors de la compilation, le terminal affichera de nombreuses informations vous informant de quels fichiers sont actuellement en train d'être compilés. Les dèrnières lignes affichées doivent se terminer de la sorte :

```
Linking: .build/planck_rev5_xyverz.elf                                                              [OK]
Creating load file for flashing: .build/planck_rev5_xyverz.hex                                      [OK]
Copying planck_rev5_xyverz.hex to qmk_firmware folder                                               [OK]
Checking file size of planck_rev5_xyverz.hex                                                        [OK]
 * File size is fine - 18392/28672
```

Le fichier `planck_rev5_xyverz.hex` copié dans le dossier qmk_firmware est en réalité le fichier éxecutable que le controleur de votre clavier pourra éxecuter.

## Flasher votre firmware

Dirigez-vous vers la section [Flashing Firmware](newbs_flashing.md) pour apprendre comment installer le firmware sur votre clavier.
