# BÉPO Keymap with firmware-remapping for software CSA layout

This is a keymap intended to be used with the [BÉPO layout](http://bepo.fr), a French ergonomic layout designed by following Dvorak's principles.

The particularity of this keymap is that it supports using the [Canadian Multilingual Standard layout](https://en.wikipedia.org/wiki/QWERTY#Canadian_Multilingual_Standard) (also known as _ACNOR keyboard_ or _CSA keyboard_, see also the [French page](https://fr.wikipedia.org/wiki/QWERTY#Clavier_canadien_multilingue_standard) which contains more details) on the OS side, by enabling the _CSA_ layer. This is especially useful for operating systems that natively provide CSA, but not BÉPO, like Windows. The CSA layout was chosen because it is probably the standard layout that provides the best character set coverage.

This keymap is based on the [tm2030](../tm2030/) keymap, whose goal was to have a [TypeMatrix™ 2030](http://typematrix.com/2030/features.php) inspired layout for the ErgoDox EZ.

As this keyboard is intended for French people, the rest of this page will be in French.

# Keymap BÉPO avec support en firmware pour utilisation avec la disposition CSA en software

Cette keymap a été conçue pour être utilisée avec la [disposition BÉPO](http://bepo.fr), la disposition francophone, ergonomique et libre basée sure les principes de Dvorak.

La particularité de cette keymap est qu'elle supporte l'utilisation du [clavier canadien multilingue standard](https://fr.wikipedia.org/wiki/QWERTY#Clavier_canadien_multilingue_standard) (aussi appelé _clavier ACNOR_ ou _clavier CSA_) du côté du système d'exploitation, en activant la couche _CSA_. Ceci s'avère particulièrement utile pour les systèmes d'exploitations qui fournissent nativement le CSA, mais pas le BÉPO, comme Windows. Le clavier CSA a été choisi comme base car c'est probablement la disposition standard qui fournit la meilleure couverture en termes de caractères disponibles.

Cette keymap est basée sur la keymap [tm2030](../tm2030/), dont le but est de fournir une disposition inspirée du [TypeMatrix™ 2030](http://typematrix.com/2030/features.php) pour l'ErgoDox EZ.

## Couche de base
C'est la couche par défaut, proche du TypeMatrix, avec les différences suivantes:
- La ligne du haut (les touches `F`) et la colonne de droite sont retirées, les touches correspondantes étant déplacées ailleurs.
- Les touches situés en bas à gauche sont redisposées dans cet ordre: `Ctrl`, `fn`, `Gui`, `num+Alt`, `Alt`
- Les touches `shuffle` (`Alt+Tab`) et `desktop` ne sont pas supportés
- `W` est déplacé à la place de `=`
- `=` est déplacé sous `Tab` (au lieu d'avoir un grand `Shift`)
- `%` et `Ç` sont déplacés à la place de `Home` et `End` respectivement
- Les flèches ainsi que `PgUp`/`PgDown`/`Home`/`End` sont déplacées sur les pouces

À noter que pour `W` et `Ç`, le but a été de ne pas les déplacer trop par rapport à la disposition BÉPO _standard_, afin de pouvoir repasser facilement sur un TypeMatrix ou un clavier traditionnel.


```
,--------------------------------------------------.           ,--------------------------------------------------.
|   $    |   "  |   «  |   »  |   (  |   )  | Del  |           | Del  |   @  |   +  |   -  |   /  |   *  |   W    |
|--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
| Tab    |   B  |   É  |   P  |   O  |   È  |Backsp|           |Backsp|   ^  |   V  |   D  |   L  |   J  |   Z    |
|--------+------+------+------+------+------|ace   |           |ace   |------+------+------+------+------+--------|
|   =    |   A  |   U  |   I  |   E  |   ,  |------|           |------|   C  |   T  |   S  |   R  |   N  |   M    |
|--------+------+------+------+------+------|Enter |           |Enter |------+------+------+------+------+--------|
| LShift |   À  |   Y  |   X  |   .  |   K  |      |           |      |   '  |   Q  |   G  |   H  |   F  | RShift |
`--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
  |LCtrl |  fn  | LGui |numAlt| LAlt |                                       |Alt Gr|   %  |  App |   Ç  | RCtrl|
  `----------------------------------'                                       `----------------------------------'
                                      ,--------------.       ,-------------.
                                      |  Esc  | num  |       | Left |Right |
                               ,------+-------+------|       |------+------+------.
                               |      |       | PgUp |       |  Up  |      |      |
                               |Space | Home  |------|       |------| End  |Space |
                               |      |       | PgDn |       | Down |      |      |
                               `---------------------'       `--------------------'
```

### Changer de couche

- Utilisez `num` pour activer/désactiver [la couche numérique](#couche-numérique)
- Maintenez `fn` pour activer temporairement [les couches numériques et Fn](#couche-fn)
- Maintenez `numAlt` pour activer temporairement la couche numérique combinée avec `Alt` (facilite l'utilisation des raccourcis tels que `Alt`+`F4`)

### Diodes
Les diodes de l'ErgoDox EZ (côté droit) sont utilisées de la façon suivante :

- diode de gauche (rouge) : indique l'activation de [la couche numérique](#couche-numérique)
- diode du milieu (verte) : indique l'activation du [mode CSA](#couche-csa)
- diode de droite (bleue) : indique le verrouillage majuscules

## Couche CSA
La couche _CSA_ est la même que la couche de base, pour une utilisation avec un clavier Canadien Multilingue configuré dans le système d'exploitation.

Pour l'activer, appuyez sur `fn`+`$`. La [diode](#diodes) verte indique que la couche CSA est activée.

### Limitations
Seuls les caractères présents dans le clavier CSA sont parfaitement supportés. De manière générale, il s'agit des caractères suivants :

- toute la couche de base
- tous les caractères accessibles en `Shift`
- tous les caractères de la main gauche accessibles en `AltGr` à l'exception du `≠`
- environ la moitié des caractères de la main droite accessibles en `AltGr` et la moitié des caractères accessibles en `AltGr`+`Shift` (consultez [le fichier source](keymap.c) pour voir les caractères supportés)

En particulier, les caractères suivants sont émulés via le support Unicode (Windows seulement):

- le tiret cadratin (tiret long) : —
- le tiret demi-cadratin (demi tiret) : –
- les points de suspension : …

L'implémentation actuelle ne fonctionne pas dans toutes les applications, en particulier les applications MS Office.

Il est probable que l'utilisation de la couche CSA ne fonctionne pas correctement dans certains jeux vidéos.

Cette fonctionnalité a été conçue et testée essentiellment pour Windows (7).

### Détails techniques
Techniquement, la couche CSA est en réalité composée de 4 couches servant à émuler la couche de base, les appuis sur `Shift` ou `Alt` et la combinaison des deux.

Le changement de couches se fait par des macros afin d'activer ou désactiver plusieurs couches et la touche `Shift` en même temps.

Certains caractères sont également implémentés par des macros, notamment ceux de la couche `Shift` qui n'ont pas besoin de cette touche en CSA, comme les chiffres.

Les caractères Unicode se basent sur une implémentation spécifique et non celle fournie dans QMK — il faudrait sans doute migrer le code. Notez la façon dont ces caractères sont déclarés tels quels dans [le code source](keymap.c) (tableau `unicode_char`).

## Couche numérique
Couche numérique proche du TM lorsqu'on active `num`, avec les différences suivantes :

- Le clavier numérique est déplacés de 1 vers le haut et vers la droite.
- Les flèches sont décalées de 1 vers la gauche.
- Fournit l'accès aux touches `F1` à `F12`, `caps-lock` et `num-lock`.

La couche numérique est indiquée par la [diode](#diodes) de gauche (rouge). Caps-lock est indiqué par la diode de droite (bleue).

La touche `numAlt` de [la couche de base](#couche-de-base) permet d'activer la couche numérique et la touche `Alt` simultanément, afin de faciliter les raccourcis claviers comme `Alt`+`F4`.

```
,--------------------------------------------------.           ,--------------------------------------------------.
|        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |      |      |  Tab |   /  |   *  |   -    |
|--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
|        |  F6  |  F7  |  F8  |  F9  |  F10 |      |           |      |      | Home |   7  |   8  |   9  |   +    |
|--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
|        |  F11 |  F12 |      |      |      |------|           |------|  Up  | End  |   4  |   5  |   6  |   +    |
|--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
|        |      |      |      |      |      |      |           | Left | Down | Right|   1  |   2  |   3  |KpEnter |
`--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
  |      |      |      |      |      |                                       |      |   0  |  00  |   .  |Etr/Ctl|
  `----------------------------------'                                       `-----------------------------------'
                                       ,-------------.       ,-------------.
                                       |      |      |       |n.lock|c.lock|
                                ,------|------|------|       |------+------+------.
                                |      |      |      |       |      |      |      |
                                |      |      |------|       |------|      |      |
                                |      |      |      |       |      |      |      |
                                `--------------------'       `--------------------'
```

## Couche Fn
Activée simultanément avec la couche numérique lorsque l'on maintient la touche `fn`. Comme sur le TM, elle fournit l'accès aux fonctionnalités suivantes :

- `couper`, `copier` et `coller` — attention: ne pas utiliser dans l'explorateur de fichiers.
- monter/baisser/couper le volume — seulement accessible en main gauche, contrairement au TM.
- piste précédente/suivante
- calculatrice, e-mail et page d'accueil du navigateur web
- `insert`, `power`, `sleep`, `wake`, `print screen`, `scroll-lock` et `pause`
- ~CSA: (dés)activation de [la couche CSA](#couche-csa) sur `$`
- RESET: rechargement du firmware avec Teensy-Loader (pour les développeurs)

```
,--------------------------------------------------.           ,--------------------------------------------------.
|  ~CSA  |      |      |      |      |      |Insert|           |Insert|Eject |Power |Sleep | Wake |PrtScr|ScrollLk|
|--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
|        |      |      |      |      |      |VolUp |           |      |      |      |      |      |      | Pause  |
|--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
|  RESET |      |      | Calc | Mail |Browsr|------|           |------|      |      |      |      |      |        |
|--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
|        | App  | cut  | copy |paste | Mute |VolDn |           |      |      |      |      |      |      |        |
`--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
  |      |      |      |      |      |                                       |      |      |      |      |      |
  `----------------------------------'                                       `----------------------------------'
                                       ,-------------.       ,-------------.
                                       |      |      |       |      |      |
                                ,------|------|------|       |------+------+------.
                                |      |      | Next |       |      |      |      |
                                | Mute | play |------|       |------|      |      |
                                |      |      | Prev |       |      |      |      |
                                `--------------------'       `--------------------'
```