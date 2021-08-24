# Introduction

Votre clavier d'ordinateur contient un processeur, proche de celui dans votre ordinateur. Ce processeur exécute un logiciel responsable de détecter les touches appuyées et envoie des rapports à propos de l'état du clavier lorsque les touches sont appuyées et relâchées. QMK prend le rôle de ce logiciel, détectant les appuis des boutons et passant cette information à l'ordinateur hôte. Lorsque vous construisez votre keymap customisée, vous créez l'équivalent d'un programme exécutable pour votre clavier.

QMK essaie de rendre les choses simples faciles, et les choses difficiles possibles. Vous n'avez pas à savoir programmer pour créer des keymaps puissantes - vous devez seulement suivre quelques règles de syntaxe simples.

# Guide de démarrage

Avant de pouvoir construire des keymaps, vous devez installer quelques logiciels et configurer votre environnement de compilation. Ceci n'a besoin d'être fait seulement une fois, peu importe le nombre de clavier pour lesquels vous compter compiler un firmware.

Si vous préférez une approche plus proche d'une interface graphique, considérez utiliser l'outil en ligne [QMK Configurator](https://config.qmk.fm). Référez-vous à [Construire votre premier firmware en utilisant l'interface graphique en ligne](newbs_building_firmware_configurator.md).

## Logiciels à télécharger

### Editeur de texte

Vous allez avoir besoin d'un programme qui peut éditer et sauvegarder des fichiers **plain text**. Si vous êtes sur Windows, vous pouvez utiliser notepad et sur Linux vous pouvez utiliser gedit. Ces deux options sont des éditeurs de texte simples mais fonctionnels. Sur macOS, faites attention avec l'application par défaut TextEdit: elle ne sauvegardera pas les fichiers en mode "plain text" sauf si vous sélectionnez explicitement _Make Plain Text_ à partir du menu _Format_.

Vous pouvez aussi télécharger et installer un éditeur de texte dédié comme [Sublime Text](https://www.sublimetext.com/) ou [VS Code](https://code.visualstudio.com/). C'est probablement la meilleure solution peu importe la plateforme car ce sont des programmes conçus spécifiquement pour éditer du code.

?> Pas sûr de quel éditeur de texte utiliser? Laurence Bradford a écrit une [excellente introduction](https://learntocodewith.me/programming/basics/text-editors/) au sujet.

### QMK Toolbox

QMK Toolbox est un programme graphique optionnel pour Windows et macOS qui permet à la fois de programmer et débugger votre clavier customisé. Il vous sera probablement très utile pour facilement flasher votre clavier et analyser ses messages de débugage.

[Télécharger la dernière version ici.](https://github.com/qmk/qmk_toolbox/releases/latest)

* Pour Windows: `qmk_toolbox.exe` (portable) or `qmk_toolbox_install.exe` (installeur)
* Pour macOS: `QMK.Toolbox.app.zip` (portable) or `QMK.Toolbox.pkg` (installeur)

## Configurez votre environnement

Nous avons essayé de rendre QMK aussi simple que possible à configurer. Vous avez uniquement à préparer votre environnment Linux ou Unix et laisser QMK installer le reste.

?> Si vous n'avez jamais travaillé avec la ligne de commande Linux/Unix, il y a un certain nombre de concepts basiques et de commandes que vous devriez apprendre. Ces ressources vous apprendrons suffisemment pour travailler avec QMK:<br>
[Commandes Linux à savoir](https://www.guru99.com/must-know-linux-commands.html)<br>
[Commandes Unix de base](https://www.tjhsst.edu/~dhyatt/superap/unixcmd.html)

### Windows

Vous devez installer MSYS2 et Git.

* Suivez les instructions d'installation sur la [page de MSYS2](https://www.msys2.org).
* Fermez tous les terminaux MSYS2 éventuellement ouverts et ouvrez un nouveau terminal MSYS2 MinGW 64-bit.
* Installez Git en lançant la commande: `pacman -S git`.

### macOS

Vous devez installer Homebew. Suivez les instructions sur la [page de Homebrew](https://brew.sh).

Une fois Homebrew installé, continuez avec _Configurer QMK_. Dans cette étape, nous lancerons un script qui va installer d'autres paquets.

### Linux

Vous devez installer Git. Il est très probable que vous l'ayez déjà installé, mais sinon, une des commandes suivantes devrait l'installer:

* Debian / Ubuntu / Devuan: `apt-get install git`
* Fedora / Red Hat / CentOS: `yum install git`
* Arch: `pacman -S git`

?> Docker est aussi une option sur toutes les plateformes. [Appuyez ici pour plus de détail.](getting_started_build_tools.md#docker)

## Configurer QMK

Une fois votre environnement Linux/Unix configuré, vous êtes prêt à télécharger QMK. Nous allons le faire en utilisant Git pour "cloner" le dépôt de QMK. Ouvrez un terminal ou une fenêtre MSYS2 MinGW et gardez le ouvert pour le reste de ce guide. Dans ce terminal, lancez ces deux commandes:

```shell
git clone --recurse-submodules https://github.com/qmk/qmk_firmware.git
cd qmk_firmware
```

?> Si vous savez déjà [comment utiliser GitHub](getting_started_github.md), nous recommandons que vous créez et clonez votre propre fork. Si vous ne savez pas ce que cela veut dire, vous pouvez sans problème ignorer ce message.

QMK vient avec un script pour vous aider à configurer le reste de ce que vous aurez besoin. Vous devez le lancer en tapant la ligne de commande suivante:

    util/qmk_install.sh

## Testez votre environnement de compilation

Maintenant que votre environnement de compilation de QMK est configuré, vous pouvez compiler un firmware pour votre clavier. Démarrez en compilant la keymap par défaut du clavier. Vous devriez pouvoir le faire avec une commande de ce format:

    make <keyboard>:default

Par exemple, pour compiler un firmware pour une Clueboard 66%, vous utiliserez:

    make clueboard/66/rev3:default

Une fois ceci fait, vous devriez avoir beaucoup d'information dans votre sortie qui devrait se terminer par quelque chose de similaire à ça:

```
Linking: .build/clueboard_66_rev3_default.elf                                                       [OK]
Creating load file for flashing: .build/clueboard_66_rev3_default.hex                               [OK]
Copying clueboard_66_rev3_default.hex to qmk_firmware folder                                        [OK]
Checking file size of clueboard_66_rev3_default.hex                                                 [OK]
 * The firmware size is fine - 26356/28672 (2316 bytes free)
```

# Créer votre Keymap

Vous êtes maintenant prêt à créer votre propre keymap! Passez à l'étape [Compiler votre premier firmware](newbs_building_firmware.md) pour ce faire.
