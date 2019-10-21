# Instructions pour flasher et informations sur les bootloader

Les claviers utilisent différents types de bootloaders et certains doivent être flashés différement. Heureusement, certains projets comme la [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) ont pour objectifs de permettre de flasher les différents bootloader sans trop se faire de soucis et ça peut importe les manières de les flasher.

Si vous avez un bootloader sélectionné avec la variable `BOOTLOADER` dans votre fichier `rules.mk` alors QMK vas automatiquement calculer si votre fichier .hex n'est pas trop grand pour être flashé sur votre appareil, et il affichera la taille finale du firmware. Pour vérifier la taille manuellement, vous pouvez aussi compiler le firmware avec l'option `check-size`. Exemple : `make planck/rev4:default:check-size`.

## DFU

Le bootloader pour les processeurs Atmel DFU est fourni par défaut sur tous les processeurs atmega32u4. Celui-ci est utilisé par beaucoup de claviers plus vieux que les OLKB et Clueboard qui ont leur propre ICs sur leurs PCBs. D'autres claviers utilisent le bootloader DFU de LUFA (ou son fork QMK), notamment les nouveaux claviers OLKB. Ce dernier ajoute des fonctionnalités spécifiques sur le matériel.

Pour vérifier la compatibilité avec le bootloader DFU, vérifiez que ce bloc de code est présent dans votre fichier `rules.mk`. Parfois il peut être inscrit `lufa-dfu` ou `qmk-dfu` à la place.

```make
# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = atmel-dfu
```

Méthodes de flash compatibles :

* [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) (interface graphique recommandé)
* [dfu-programmer](https://github.com/dfu-programmer/dfu-programmer) / `:dfu` avec QMK (outil en ligne de commande recommandé)
* [Atmel's Flip](http://www.microchip.com/developmenttools/productdetails.aspx?partno=flip) (non recommandé)

Ordre des actions :

1. Pressez le keycode `RESET`, ou appuyez sur le bouton physique RESET ou alors créez un contact entre RST et GND.
2. Attendez que l'OS detecte l'appareil.
3. Éffacez la mémoire, cela peut être fait automatiquement.
4. Flasher le fichier .hex.
5. Redémarrez l'appareil en mode « application », cela peut être fait automatiquement.

Alternativement :

    make <keyboard>:<keymap>:dfu

### DFU QMK

QMK a un fork du bootloader LUFA DFU qui vous permet de faire un simple scan de la matrice pour quitter le bootloader et retourner à l'application. En même temps que le flash se produira, il est possible de faire flasher un led ou de produire un son via un haut parleur. Pour activer ces fonctionnalités, vous pouvez utiliser ce bloc dans votre fichier `config.h` (La touche permettant de quitter le bootloader a besoin d'être reliée entre les ports définis en INPUT et OUTPUT ici):

    #define QMK_ESC_OUTPUT F1 // usually COL
    #define QMK_ESC_INPUT D5 // usually ROW
    #define QMK_LED E6
    #define QMK_SPEAKER C6

Le fabriquant et le nom du produit proviennent de vos définitions dans fichier  `config.h`, et la chaîne de caractère « bootloader » est ajoutée au nom du prodruit.

Pour génerer le bootloader, utilisez la cible `bootloader`. Exemple : `make planck/rev4:default:bootloader`.

Pour génerer un fichier .hex prêt pour la production qui contiendra tant l'application que le bootloader, utilisez la cible `production`. Exemple : `make planck/rev4:default:production`.

### Commandes DFU

Il y a plusieurs commandes DFU que vous pouvez utiliser pour flasher le firmware sur un appareil DFU.

* `:dfu` - C'est l'option normale qui attend qu'un appareil DFU soit disponible et qui flashe le firmware dès que c'est le cas. La vérification sera faite toutes les 5 secondes.
* `:dfu-ee` - Cette option flash un fichier `.eep` à la place d'un fichier `.hex`. Ce cas est plutôt rare.
* `:dfu-split-left` - Cette option flashe le firmware normal comme avec l'option (`:dfu`). Mais cela aussi flash le coté gauche du fichier EEPROM pour les claviers scindés. _C'est l'option idéale pour un clavier scindé basé sur le Elite C_
* `:dfu-split-right` - Cette option flashe le firmware normal comme avec l'option (`:dfu`).  Mais cela aussi flash le coté droite du fichier EEPROM pour les claviers scindés. _C'est l'option idéale pour un clavier scindé basé sur le Elite C_

## Caterina

Les cartes arduinos et leurs clones utilisent le [bootloader Caterina](https://github.com/arduino/ArduinoCore-avr/tree/master/bootloaders/caterina) (tous les claviers utilisant un Pro Micro, ou un clone). Ils utilisent aussi le protocole avr109 pour communiquer en virtuellement en série (serial en Anglais). Les bootloaders comme le [A-Star](https://www.pololu.com/docs/0J61/9) sont basés sur Caterina.

Pour vérifier la compatibilité avec un bootloader Caterina, vérifiez que ce bloc est présent dans votre fichier `rules.mk` :

```make
# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = caterina
```

Flashers compatibles :

* [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) (Interface graphique recomandée)
* [avrdude](http://www.nongnu.org/avrdude/) avec avr109 / `:avrdude` (Outil en ligne de commande recomandé)
* [AVRDUDESS](https://github.com/zkemble/AVRDUDESS)

Séquence de flash : 

1. Pressez la touche avec le keycode `RESET`, ou reliez les ports GND et RST. Vous n'avez que 7 secondes pour flasher une fois que l'opération a été faite.
2. Attendez que l'OS détecte l'appareil.
3. Flasher le fichier .hex.
4. Attendez que l'appareil redémarre automatiquement.

ou, utilisez :

    make <keyboard>:<keymap>:avrdude

ou, si vous vous voulez flasher plusieurs claviers, utilisez la commande suivante :

    make <keyboard>:<keymap>:avrdude-loop

Quand vous avez fini de flasher vos claviers, vous aurez besoin d'utiliser Ctrl + C ou alors la touche ayant la fonction similaire sur votre OS pour sortir de la boucle.

## Halfkay

Halfkay est un protocole ultra-simple développé par PJRC qui utilise HID et qui est fourni avec tous les Teensys après le modèle 2.0.

Pour vérifier la compatibilité avec le booloader Halfkay, vérifiez que ce bloc est présent dans votre fichier `rules.mk` :

```make
# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = halfkay
```

Flasher compatibles :

* [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) (Interface graphique recomandée)
* [Teensy Loader](https://www.pjrc.com/teensy/loader.html) (petit utilitaire ultra simple)
 [Teensy Loader en ligne de commande](https://www.pjrc.com/teensy/loader_cli.html) (Outil en ligne de commande recommandé)

Séquence de flash :

1. Pressez la touche du keycode `RESET`, ou reliez les ports RST et GND rapidement. Vous avez ensuite 7 secondes pour réaliser le flash.
2. Attendez que l'OS détecte l'appareil.
3. Flasher le fichier .hex.
4. Redémarrez l'appareil en mode « application ». Cela peut être fait automatiquement.

## USBasploader

USBasploader est un bootloader développé par matrixstorm. Il est utilisé sur des processeurs AVR non-USB comme le ATmega328P, qui fonctionne grâce à V-USB.

Pour vérifier la compatibilité avec le booloader USBasploader, vérifiez que ce bloc est présent dans votre fichier `rules.mk` :

```make
# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = USBasp
```

Flashers compatibles :

* [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) (Interface graphique recommandé)
* [avrdude](http://www.nongnu.org/avrdude/) avec le programmeur `usbasp`.
* [AVRDUDESS](https://github.com/zkemble/AVRDUDESS)

Séquence de flash :

1. Pressez la touche du keycode `RESET`, ou reliez le port de boot pendant que RST et GND snt reliés. Cela doit être fait très rapidement.
2. Attendez que l'OS détecte l'appareil.
3. Flasher le fichier .hex.
4. Redémarrez l'appareil en mode « application ». Cela peut être fait automatiquement.

## BootloadHID

BootloadHID est un bootloader pour les microcontroleurs AVR. L'utilitaire de téleversement ne demande pas de drivers au niveau du kernel et peut être lancé sans installer aucune DLLs.

Pour vérifier la compatibilité avec le bootloader bootloadHID, vérifiez que ce bloc existe dans votre fichier `rules.mk` : 

```make
# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = bootloadHID
```

Utilitaires de flash compatibles :

* [HIDBootFlash](http://vusb.wikidot.com/project:hidbootflash) (Utilitaire avec interface graphique recommandé)
* [bootloadhid Command Line](https://www.obdev.at/products/vusb/bootloadhid.html) / `:BootloadHID` avec QMK (utilitaire en ligne de commande recommandé)

Séquence de flash

1. Entrez dans le bootloader en utilisant l'une de ces méthodes :
    * Pressez la touche du keycode `RESET` (Cela ne fonctionnera pas sur certains appareils).
    * Verouillez la touche « Salt » tout en branchant le clavier (Géneralement ce principe est documenté dans le fichier readme du clavier)
2. Attendez que l'OS détecte l'appareil.
3. Flasher le fichier .hex.
4. Redémarrez l'appareil en mode « application ». Cela peut être fait automatiquement.

Ou alors :

    make <keyboard>:<keymap>:bootloadHID

## STM32

Tous les processeurs STM32 contiennent un bootloader installé en usine qui ne peut pas être modifié ou supprimé. Certains processeurs STM32 ont des bootloaders qui ne peuvent pas être programmés par USB (ex : STM32F103) mais le processus reste le même.

Pour le moment, aucune variable `BOOTLOADER` n'est nécessaire dans le fichier `rules.mk`.

Flashers compatibles :

* [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) (interface graphique recommandé)
* [dfu-util](https://github.com/Stefan-Schmidt/dfu-util) / `:dfu-util` (utilitaire en ligne de commande recommandé)

Séquence pour flasher:

1. Entrez dans le bootloader en utilisant l'une de ces méthodes :
    * Utilisez une touche sur laquelle le keycode `RESET` (Cela peut ne pas fonctionner sur les appareils STM32F042)
    * Si un circuit de réinitialisation (Reset) est présent alors utilisé le bouton qui lui est dédié.
    * Autrement, vous devez réaliser une liaison entre BOOT0 et VCC (en appuyant sur le bouton ou à l'aide d'un pont) puis faire un pont entre RESET et GND et enfin relacher le pont BOOT0.
2. Attendre que l'os détecte l'appareil.
3. Flasher un fichier `.bin`.h
    * Vous allez recevoir un avertissement à propos de la signature DFU. Ignorez-la.
4. Réinitialisez l'appareil en mode « application ». Cela peut être fait automatiquement.
    * Si vous êtes en train de travailler en ligne de commande, par exemple avec un `make planck/rev6:default:dfu-util` alors soyez bien sur que l'argument `:leave` est passé aux argument DFU grâce à la variable `DFU_ARGS` à l'intérieur de votre fichier `rules.mk` (Ex : `DFU_ARGS = -d 0483:df11 -a 0 -s 0x08000000:leave`) afin que votre appareil redémarre après avoir été flashé.

### Commandes STM32

Il y a différentes commandes que vous pouvez utiliser pour flasher un firmware dans un appareil STM32  :

* `:dfu-util` - La commande par défaut pour flasher un appareil STM32.
* `:dfu-util-split-left` - Permet de flasher un firmware normalement, tout comme l'option précedente mais permet de configurer le coté gauche des paramètres EEPROM sur un clavier scindé.
* `:dfu-util-split-right` - Permet de flasher un firmware normalement, tout comme l'option précedente mais permet de configurer le coté droit des paramètres EEPROM sur un clavier scindé.
* `:st-link-cli` - Cela permet de flasher le firmware avec l'utilitaire en ligne de commande ST-LINK's plutôt que d'utiliser dfu-util.
