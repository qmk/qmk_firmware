# Introduction

Votre clavier possède un micro-ordinateur qui comporte un processeur similaire à votre ordinateur. Le processeur fait fonctionner des logiciels qui détectent les différentes touches que vous pressez et relâchez.

QMK remplie le rôle de ce logiciel en détectant les différentes touches pressées et en envoyant ses informations à l’ordinateur hôte.
Quand vous fabriquez votre disposition de clavier personalisée, vous créez l’équivalent d’un programme éxecutable pour votre clavier.

QMK essaie d’offrir beaucoup de puissance en vos mains en rendant simples les choses simples et possible les choses compliquées. Vous n’avez pas besoin de savoir comment programmer pour créer des dispositions de clavier puissantes mais vous avez simplement à suivre quelques règles de syntaxes simples.

# Pour bien commencer

Avant de commencer à créer des disposition de clavier vous devez installer quelques logiciels et les configurer pour construire votre environnement.
Cela ne doit être fait qu’une seule fois peut importe le nombre de clavier dont vous créerez le firmware.

Si vous préférerez utiliser une interface graphique, vous pouvez utiliser l’application web [QMK Configurator](https://config.qmk.fm).
S’il vous plaît, refferez-vous à la section [Créer votre premier firmware avec l’utilitaire graphique](newbs_building_firmware_configurator.md).


## Télechargement des logiciels

### Éditeur de texte

Vous devez télécharger un programme qui permet de modifier et sauvegarder du texte brut. Si vous êtes sur Windows alors vous pouvez utiliser Notepad et sur Linux Gedit. Ces deux logiciels sont simples et fonctionnels. Sur macOS vous pouvez utiliser l’éditeur de texte « TextEdit » mais celui-ci ne sauvegardera pas en texte brut sauf si vous choisissez explicitement l’option « Sauvegarder du texte brut » dans le menu « Format ».

Vous pouvez aussi télécharger et installer un éditeur de texte dédié comme [Sublime Text](https://www.sublimetext.com/) ou [VS Code](https://code.visualstudio.com/). Ces logiciels seront certainement plus apte à répondre à vos besoins car ils sont dédiés spécifiquement à la création et modification de code.

?> Vous ne savez pas quel éditeur choisir ? Laurence Bradford a écrit [une introduction](https://learntocodewith.me/programming/basics/text-editors/) sur le sujet.

### QMK Toolbox

QMK Toolbox est logiciel optionnel prévu pour Windows et macOS qui vous permet de programmer et déboguer votre clavier personnalisé. Vous le trouverez certainement très utile pour flasher votre clavier et voir les messages de debugs que celui-ci envoie.

[Télécharger la dernière version ici](https://github.com/qmk/qmk_toolbox/releases/latest)

* Pour Windows: `qmk_toolbox.exe` (portable) ou `qmk_toolbox_install.exe` (à installer)
* For macOS: `QMK.Toolbox.app.zip` (portable) ou `QMK.Toolbox.pkg` (à installer)

## Mise en place de l’environnement

Nous avons essayé de faire QMK aussi simple à installer que possible. Vous avez juste à préparer votre environnement Linux ou Unix et laisser QMK installer le reste.

?> Si vous n’avez jamais utilisé Linux ou Unix en ligne de commande avant, alors il existe quelques concepts basiques que vous devez apprendre. Ces liens vous en apprendrons assez pour utiliser QMK :<br>
[Commandes Linux à connaître](https://www.guru99.com/must-know-linux-commands.html)<br>
[Quelques commandes UNIX basiques](https://www.tjhsst.edu/~dhyatt/superap/unixcmd.html)

### Windows

Vous allez devoir installer MSYS2 et Git.

* Suivez les instructions d’installations sur la page [d’accueil de MSYS2](http://www.msys2.org).
* Fermez tous les terminaux MSYS2 et ouvrez une nouvelle instance du terminal MSYS2 MinGW 64-bit.
* Installer Git en lançant cette commande : `pacman -S git`.

### macOS

Vous devez installer Homebrew. Suivez les instructionsr sur [La page d’accueil Homebrew](https://brew.sh).

Après qu’Homebrew soit installé, continuez avec la section _Paramétrer QMK_. dans cette étape vous lancerez un script qui installera et configurera les autres paquets dont vous aurez besoin.

### Linux

Vous aller devoir installer Git. Normalement, vous l’avez certainement par défaut. Sinon ces quelques commandes devraient l’installer.

* Debian / Ubuntu / Devuan: `apt-get install git`
* Fedora / Red Hat / CentOS: `yum install git`
* Arch: `pacman -S git`

?> Docker est aussi une solution pour l’ensemble des plateformes [Cliquez ici pour des détails](getting_started_build_tools.md#docker)

## Paramétrer QMK

Une fois que vous avez installé et configuré votre environnement Linux/Unix alors vous êtes prêts pour télecharger QMK. Nous allons utiliser Git pour « cloner » le dépôt QMK. Ouvrez un terminal ou une fenêtre MSYS2 MinGW et laisser-la ouverte pour la suite de ce guide. Dans cette fenêtre, lancez ces deux commandes :

```shell
git clone --recurse-submodules https://github.com/qmk/qmk_firmware.git
cd qmk_firmware
```

?> Si vous savez déjà comment [utiliser Github](getting_started_github.md), nous vous recommandons de créer et cloner votre propre fork. Si vous ne savez pas ce que cela signifie vous pouvez sans problème ignorer cette message.

QMK propose un script qui vas vous aider à installer tout ce qui est nécessaire. Lancez-le avec cette commande :

    util/qmk_install.sh

## Tester votre environnement de compilation

Maintenant que votre environnement de compilation est préparé vous pouvez fabriquer un firmwarke pour votre clavier. Commencez pas la compilation de la disposition par défaut. Vous devrez pouvoir le faire à l’aide d’une commande dans ce format :

    make <keyboard>:default

Par exemple, pour fabriquer le firmware du Clueboard 66% vous pouvez utiliser :

    make clueboard/66/rev3:default

Quand cela est fait, vous devez obtenir une sortie à l’écran qui se termine comme ceci :

```
Linking: .build/clueboard_66_rev3_default.elf                                                       [OK]
Creating load file for flashing: .build/clueboard_66_rev3_default.hex                               [OK]
Copying clueboard_66_rev3_default.hex to qmk_firmware folder                                        [OK]
Checking file size of clueboard_66_rev3_default.hex                                                 [OK]
 * The firmware size is fine - 26356/28672 (2316 bytes free)
```

# Créer votre propre disposition

Vous êtes désormais prêt à créer votre propre disposition ! Rendez-vous à la section [Créer son propre firmware](newbs_building_firmware.md).
