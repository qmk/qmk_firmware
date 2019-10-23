# Introduction

Le but de cette page est d'expliquer les informations de base qui vous serons nécessaire pour travailler sur le projet QMK. Il a pour pré-requis que vous soyez familier à la navigation à l'aide d'un shell Unix, mais ne s'attend pas à ce que vous soyez familier avec C ou la compilation en utilisant make.

## Structure de base de QMK

QMK est un fork du projet [tmk_keyboard](https://github.com/tmk/tmk_keyboard) créé par [Jun Wako](https://github.com/tmk). Le code originel de TMK, avec quelques modifications, se trouve dans le dossier `tmk`. Les additions que QMK amène au projet se trouvent dans le dossier `quantum`. Les projets de clavier se trouvent dans les dossiers `handwired` et `keyboard`.

### Structure du Userspace

Dans le dossier `users` se trouve un répertoire pour chaque utilisateur. C'est un endroit où les utilisateurs peuvent mettre du code qui serait partagé entre plusieurs claviers. Merci de lire la documentation  [Fonctionnalité Userspace](feature_userspace.md) pour plus d'information.

### Structure du projet clavier

Dans le dossier `keyboards`, son sous-dossier `handwired` et ses sous-dossiers pour les revendeurs et fabriquants (par exemple `clueboard`) se trouve un répertoire pour chaque projet clavier. Par exemple `qmk_firmware/keyboards/clueboard/2x1800`.

A l'intérieur, vous trouverez la structure suivante:

* `keymaps/`: différentes keymaps qui peuvent être compilées
* `rules.mk`: Ce fichier définit les options "make" par défaut. Ne modifiez pas ce fichier directement, utilisez à la place un `rules.mk` spécifique à la keymap.
* `config.h`: Ce fichier définit les options de compilation par défaut. Ne modifiez pas ce fichier directement, utilisez à la place un `config.h` spécifique à la keymap.
* `info.json`: Le fichier utilisé pour définir les options de layout de QMK Configurator. Voyez [Support Configurator](reference_configurator_support.md) pour plus d'information.
* `readme.md`: une brève description du clavier.
* `<keyboardName>.h`: Ce fichier définit le layout du fichier par rapport à la matrice de commutation.
* `<keyboardName>.c`: Ce fichier définit du code custom pour le clavier.

Pour plus d'information sur la structure du projet, voyez [Directives clavier QMK](hardware_keyboard_guidelines.md).

### Structure d'une Keymap

Dans chaque dossier keymap, vous allez trouver les fichiers suivants. Seul le fichier `keymap.c` est nécessaire, et si le reste des fichiers n'existent pas, les options par défaut seront choisies.

* `config.h`: les options de configuration de votre keymap
* `keymap.c`: tout le code de votre keymap, requis
* `rules.mk`: les features de QMK qui sont activées
* `readme.md`: une description de votre keymap, comment d'autres l'utiliseront, et des explications des fonctionnalités. Uploadez les images vers un service comme imgur.

# Le fichier `config.h`

Le fichier `config.h` peut être mis à 3 endroits:

* keyboard (`/keyboards/<keyboard>/config.h`)
* userspace (`/users/<user>/config.h`)
* keymap (`/keyboards/<keyboard>/keymaps/<keymap>/config.h`)

Le système de compilation cherche automatiquement les fichiers de configuration dans l'ordre au dessus. Si vous souhaitez surcharger une configuration définie par un `config.h` précédent, vous devrez d'abord ajouter le code suivant.

```
#pragma once
```

Ensuite, pour surcharger l'option du fichier `config.h` précédent, vous devez `#undef` puis `#define` l'option à nouveau.

Voici à quoi l'ensemble du code resemble une fois regroupé:

```
#pragma once

// overrides go here!
#undef MY_SETTING
#define MY_SETTING 4
```
