# Configuration de QMK CLI

Ce document explique comment fonctionne la commande `qmk config`.

# Introduction

La configuration pour QMK CLI est un système clé/valeur. Chaque clé est composée d'une sous-commande et d'un argument séparé par une virgule. Cela permet une traduction simple et directe entre les clés de configuration et l'argument qu'elle définit.

## Exemple simple

Comme exemple, regardons la commande `qmk compile --keyboard clueboard/66/rev4 --keymap default`.

Il y a deux arguments de ligne de commande qui peuvent être lu de la configuration:

* `compile.keyboard`
* `compile.keymap`

Essayons de les définir:

```shell
$ qmk config compile.keyboard=clueboard/66/rev4 compile.keymap=default
compile.keyboard: None -> clueboard/66/rev4
compile.keymap: None -> default
Ψ Wrote configuration to '/Users/example/Library/Application Support/qmk/qmk.ini'
```

Maintenant, je peux lancer la commande `qmk compile` sans avoir à spécifier mon clavier et keymap à chaque fois.

## Définir les options par défaut

Parfois, il est utile de partager une configuration entre plusieurs commandes. Par exemple, plusieurs commandes prennent un argument `--keyboard`. Plutôt que de devoir définir cette valeur pour chaque commande, vous pouvez définir une valeur d'utilisateur qui sera utilisée par toutes les commandes qui prennent cet argument.

Exemple:

```
$ qmk config user.keyboard=clueboard/66/rev4 user.keymap=default
user.keyboard: None -> clueboard/66/rev4
user.keymap: None -> default
Ψ Wrote configuration to '/Users/example/Library/Application Support/qmk/qmk.ini'
```

# CLI Documentation (`qmk config`)

La commande `qmk config` est utilisée pour interagir avec la configuration sous-jacente. Lancée sans argument, elle affiche la configuration courante. Lorsque des arguments sont définis, ils sont considérés comme étant des jetons de configuration, qui sont des chaînes de caractère ne contenant aucun espace avec le format suivant:

    <subcommand|general|default>[.<key>][=<value>]

## Définir des valeurs de configuration

Vous pouvez définir des valeurs de configuration en mettant le caractère égal (=) dans votre clé de configuration. La clé doit toujours être dans le format complet `<section>.<key>`.

Exemple:

```
$ qmk config default.keymap=default
default.keymap: None -> default
Ψ Wrote configuration to '/Users/example/Library/Application Support/qmk/qmk.ini'
```

## Lire des valeurs de configuration

Vous pouvez lire les valeurs de configuration pour la totalité de la configuration, une seule clé, ou une section entière. Vous pouvez aussi spécifier plusieurs clés pour afficher plus d'une valeur.

### Exemple avec la totalité de la configuration

    qmk config

### Exemple avec une section entière

    qmk config compile

### Exemple avec une clé unique

    qmk config compile.keyboard

### Exemple avec plusieurs clés

    qmk config user compile.keyboard compile.keymap

## Supprimer des valeurs de configuration

Vous pouvez supprimer une valeur de configuration en la définissant avec la chaîne spéciale `None`.

Exemple:

```
$ qmk config default.keymap=None
default.keymap: default -> None
Ψ Wrote configuration to '/Users/example/Library/Application Support/qmk/qmk.ini'
```

## Plusieurs opérations

Vous pouvez combiner plusieurs opérations d'écriture et de lecture en une seule commande. Elles seront exécutées et affichées dans l'ordre:

```
$ qmk config compile default.keymap=default compile.keymap=None
compile.keymap=skully
compile.keyboard=clueboard/66_hotswap/gen1
default.keymap: None -> default
compile.keymap: skully -> None
Ψ Wrote configuration to '/Users/example/Library/Application Support/qmk/qmk.ini'
```

# Options de configuration utilisateur

| Clé | Valeur par défaut | Description |
|-----|---------------|-------------|
| user.keyboard | None | Le chemin d'accès vers le clavier (Exemple: `clueboard/66/rev4`) |
| user.keymap | None | Le nom de la keymap (Exemple: `default`) |
| user.name | None | Le nom d'utilisateur GitHub de l'utilisateur. |

# Toutes les options de configuration

| Clé | Valeur par défaut | Description |
|-----|---------------|-------------|
| compile.keyboard | None | Le chemin d'accès vers le clavier (Exemple: `clueboard/66/rev4`) |
| compile.keymap | None | Le nom de la keymap (Exemple: `default`) |
| hello.name | None | Le nom à saluer lorsque démarré. |
| new_keyboard.keyboard | None | Le chemin d'accès vers le clavier (Exemple: `clueboard/66/rev4`) |
| new_keyboard.keymap | None | Le nom de la keymap (Example: `default`) |
