# La CLI de QMK

Cette page décrit comment configurer et utiliser la CLI QMK.

# Vue d'ensemble

La CLI de QMK permet de simplifier la compilation et l'intéraction avec les clavier QMK. Nous avons définis plusieurs commandes pour simplifier et rationaliser les tâches telles qu'obtenir et compiler le firmware QMK, créer de nouvelles keymaps, et plus.

* [CLI globale](#global-cli)
* [CLI locale](#local-cli)
* [Les commandes CLI](#cli-commands)

# Pré-requis

La CLI nécessite Python 3.5 ou plus récent. Nous essayons de limiter le nombre de pré-requis, mais vous allez aussi devoir installer les paquets listés dans le fichier [`requirements.txt`](https://github.com/qmk/qmk_firmware/blob/master/requirements.txt).

# CLI globale

QMK met à disposition une CLI installable qui peut être utilisée pour configurer votre environnement de compilation QMK, fonctionne avec QMK, et qui rend l'utilisation de plusieurs copies de `qmk_firmware` plus simple. Nous recommandons d'installer et de mettre à jour ceci régulièrement.

## Installer en utilisant Homebrew (macOS, quelques Linux)

Si vous avez installé [Homebrew](https://brew.sh) vous pouvez entrer ce qui suit et installer QMK:

```
brew tap qmk/qmk
brew install qmk
export QMK_HOME='~/qmk_firmware' # Optional, set the location for `qmk_firmware`
qmk setup  # This will clone `qmk/qmk_firmware` and optionally set up your build environment
```

## Installer en utilisant easy_install ou pip

Si votre système n'est pas listé ci-dessus, vous pouvez installer QMK manuellement. Premièrement, vérifiez que vous avez bien installé Python 3.5 (ou plus récent) et pip. Ensuite, installez QMK avec cette commande:

```
pip3 install qmk
export QMK_HOME='~/qmk_firmware' # Optional, set the location for `qmk_firmware`
qmk setup  # This will clone `qmk/qmk_firmware` and optionally set up your build environment
```

## Paquets pour d'autres systèmes d'exploitation

Nous recherchons des gens pour créer et maintenir un paquet `qmk` pour plus de systèmes d'exploitation. Si vous voulez créer un paquet pour votre système d'exploitation, suivez ces directives:

* Suivez les bonnes pratiques pour votre système d'exploitation lorsqu'elles entrent en conflit avec ces directives
    * Documentez pourquoi dans un commentaire lorsque vous ne les suivez pas
* Installez en utilisant un virtualenv
* Expliquez à l'utilisateur de définir la variable d'environnement `QMK_Home` pour "check out" les sources du firmware à un autre endroit que `~/qmk_firmware`.

# CLI locale

Si vous ne voulez pas utiliser la CLI globale, il y a une CLI locale empaquetée avec `qmk_firmware`. Vous pouvez le trouver dans `qmk_firmware/bin/qmk`. Vous pouvez lancer la commande `qmk` depuis n'importe quel répertoire et elle fonctionnera toujours sur cette copie de `qmk_firmware`.

**Exemple**:

```
$ ~/qmk_firmware/bin/qmk hello
Ψ Hello, World!
```

## Limitations de la CLI locale

Il y a quelques limitations à la CLI locale comparé à la globale:

* La CLI locale ne supporte pas `qmk setup` ou `qmk clone`
* La CLI locale n'opère pas sur le même arbre `qmk_firmware`, même si vous avez plusieurs dépôts clonés.
* La CLI locale ne s'exécute pas dans un virtualenv, donc il y a des risques que des dépendances seront en conflit

# Les commandes CLI

## `qmk compile`

Cette commande permet de compiler le firmware de n'importe quel répertoire. Vous pouvez compiler des exports JSON de <https://config.qmk.fm> ou compiler des keymaps du dépôt.

**Utilisation pour les exports de configuration**:

```
qmk compile <configuratorExport.json>
```

**Utilisation pour les Keymaps**:

```
qmk compile -kb <keyboard_name> -km <keymap_name>
```

## `qmk cformat`

Cette commande formatte le code C en utilisant clang-format. Lancez-la sans arguments pour formatter tout le code core, ou passez les noms de fichiers à la ligne de commande pour la lancer sur des fichiers spécifiques.

**Utilisation**:

```
qmk cformat [file1] [file2] [...] [fileN]
```

## `qmk config`

Cette commande vous permet de configurer le comportement de QMK. Pour la documentation complète de `qmk config`, regardez [Configuration de CLI](cli_configuration.md).

**Utilisation**:

```
qmk config [-ro] [config_token1] [config_token2] [...] [config_tokenN]
```

## `qmk doctor`

Cette commande examine votre environnement et vous alertes des potentiels problèmes de compilation ou de flash.

**Utilisation**:

```
qmk doctor
```

## `qmk new-keymap`

Cette commande crée une nouvelle keymap basée sur une keymap par défaut d'un clavier existant.

**Utilisation**:

```
qmk new-keymap [-kb KEYBOARD] [-km KEYMAP]
```

## `qmk pyformat`

Cette commande formatte le code python dans `qmk_firmware`.

**Utilisation**:

```
qmk pyformat
```

## `qmk pytest`

Cette commande démarre la suite de test python. Si vous faites des changements dans le code Python, assurez vous que les tests se lancent avec succès.

**Utilisation**:

```
qmk pytest
```
