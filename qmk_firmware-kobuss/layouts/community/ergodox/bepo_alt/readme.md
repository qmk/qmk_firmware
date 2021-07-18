![layer0](https://i.imgur.com/vd4QLBf.png)

![layer1](https://i.imgur.com/eo101eD.png)

# BEPO keymap for the ErgoDox (alternate version)

This keymap has been made for the BEPO layout (https://bepo.fr), which is an ergonomic french keyboard layout based on Dvorak rules. As it's made for french people, the following of this readme will be in french.

Keyboard Maintainer: [Nicolas CARPi](https://github.com/NicolasCARPi)

Hardware Supported: Ergodox EZ

## Disposition BÉPO pour l'ErgoDox

Cette keymap a été adaptée de la keymap "bepo_csa" présente dans le dossier parent.

Certaines modifications ont été apportées pour ressembler un peu plus à une clavier traditionel:

* entrée sur la touche tout en bas à droite (comme la touche entrée du pavé numérique sur un clavier traditionnel)
* plusieurs touches "Super" pour faciliter son accès

Il y a deux layers, celui de base, et celui avec les flèches, les touches fonction et la souris (main gauche).

## Particularités

* Touches de repos des pouces : "espace" à gauche et "entrée" à droite.
* Touche Ctrl gauche accessible avec la paume de la main.
* Touche "w" placée sur la main gauche (j'ai toujours trouvé le "w" difficle d'accès sur un clavier bépo classique.
* Plusieurs touches F12.
* Les flèches sont disposées avec un déplacement à la VIM.
* Un mode souris permet d'utiliser la souris avec le clavier.
* Possibilité de changer de mode de manière temporaire ou permanente.
* Les leds s'allument avec SHIFT, ALT ou la touche function.

J'ai fait cette disposition pour mes besoins, à vous de la modifier pour les vôtres ;)

## Utilisation

### Pré-requis

Pour Archlinux, il est nécessaire d'installer ces paquets au préalable:

~~~bash
sudo pacman -S avr-gcc avr-libc teensy-loader-cli
~~~

Les paquets "avr" permettent de compiler le firmware, et teensy-loader permet de le charger sur le clavier.

### Compilation

~~~bash
# clone the repo
git clone https://github.com/qmk/qmk_firmware
# install submodules
make git-submodule
# compile this layout
make ergodox_ez:bepo_alt
~~~

### Chargement

~~~bash
teensy-loader-cli -w -mmcu=atmega32u4 -v ergodox_ez_bepo_alt.hex && sleep 6 && setxkbmap fr bepo
~~~

J'ai ajouté un sleep avant la commande pour remettre en bépo afin de laisser au clavier le temps de rebooter.
