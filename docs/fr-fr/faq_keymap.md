# FAQ Keymap

Cette page couvre les questions souvent posées à propos des keymaps. Si vous ne l'avez pas encore fait, vous devriez commencer par là [Aperçu des Keymap](keymap.md).

## Quels Keycodes puis-je utiliser ?

Regardez [Keycodes](keycodes.md) pour une liste des keycodes disponibles. Certains keycodes spécifiques ont des documentations plus complètes de disponible.

Les keycodes sont définies dans [common/keycode.h](https://github.com/qmk/qmk_firmware/blob/master/quantum/keycode.h).

## Quels sont les keycodes par défaut ?

Il existe 3 configurations de clavier standard utilisées dans le monde: ANSI, ISO et JIS. L'Amérique du Nord utilise principalement l'ANSI, l'Europe et l'Afrique l'ISO et le Japon utilise JIS. Les autres régions utilisent généralement ANSI ou ISO. Les keycodes correspondant à ces dispositions spécifiques sont affichés ici :

<!-- Source for this image: https://www.keyboard-layout-editor.com/#/gists/bf431647d1001cff5eff20ae55621e9a -->
![Keyboard Layout Image](https://i.imgur.com/5wsh5wM.png)

## Certaines de mes touches sont permutées ou ne fonctionnent pas

QMK possède deux fonctionnalités, Bootmagic et Command, qui vous permettent de modifier le comportement de votre clavier à la volée. Cela inclut, sans toutefois s'y limiter, l'échange de Ctrl / Majuscules, la désactivation de l'interface graphique, le basculement de Alt/Gui, le basculement de barre d'espacement arrière/barre oblique inversée, la désactivation de toutes les touches et d'autres modifications comportementales.

Pour résoudre rapidement le problème, essayez de maintenir les touches Espace + Retour arrière enfoncées pendant que vous branchez votre clavier. Cela réinitialisera les paramètres stockés sur votre clavier, ramenant ces touches à un fonctionnement normal. Si cela ne fonctionne pas, regardez ici:

* [Bootmagic](feature_bootmagic.md)
* [Command](feature_command.md)

## La touche de menu ne fonctionne pas

La touche trouvée sur la plupart des claviers modernes située entre `KC_RGUI` et` KC_RCTL` est en réalité appelée `KC_APP`. En effet, lorsque cette touche a été inventée, il existait déjà une clé nommée `MENU` dans les normes correspondantes. MS a donc choisi de l'appeler la touche` APP`.

## `KC_SYSREQ` ne fonctionne pas

Utilisez le keycode pour Print Screen (`KC_PSCREEN` or `KC_PSCR`) à la place de `KC_SYSREQ`. La combinaison de touche 'Alt + Print Screen' est reconnue comme 'System request'.

Voir [issue #168](https://github.com/tmk/tmk_keyboard/issues/168) et
* https://en.wikipedia.org/wiki/Magic_SysRq_key
* https://en.wikipedia.org/wiki/System_request

## Les touches alimentation ne fonctionnent pas

Un peu déroutant, il y a deux codes de touche "Alimentation" dans QMK: `KC_POWER` dans la page d'utilisation du clavier / keypad, et `KC_SYSTEM_POWER` (ou `KC_PWR`) dans la page Consumer.

Le premier n'est reconnu que sur macOS, alors que le dernier, `KC_SLEP` et `KC_WAKE` sont supportés par les trois principaux systèmes d'exploitation. Il est donc recommandé de les utiliser à la place. Sous Windows, ces touches prennent effet immédiatement, mais sur macOS, elles doivent être maintenues enfoncées jusqu'à ce qu'une boîte de dialogue apparaisse.

## Modificateur "One Shot"

Cette fonctionnalité permet de corriger un problème avec la touche Shift. En effet, il arrive de saisir plusieurs majuscules en ne voulant en saisir qu'une sur un mot. Ex: `CEtte` à la place de `Cette`. La fonctionnalité «One shot» shift permet de corriger ça.

https://github.com/tmk/tmk_keyboard/issues/67

## Le modificateur d'un calque reste bloqué

Les touches de modification ou les calques peuvent être bloquées si la commutation de calque n'est pas configurée correctement.
Pour les touches de modification et les actions de calque, vous devez placer `KC_TRANS` sur la même position du calque de destination afin de désenregistrer la clé de modificateur ou de revenir au calque précédent lors de la libération.

* https://github.com/tmk/tmk_core/blob/master/doc/keymap.md#31-momentary-switching
* https://geekhack.org/index.php?topic=57008.msg1492604#msg1492604
* https://github.com/tmk/tmk_keyboard/issues/248

## Support de touche à verrouillage mécanique

Cette fonctionnalité permet l'usage de *touches à verrouillage mécanique* comme [ces interrupteurs Alps](https://deskthority.net/wiki/Alps_SKCL_Lock). Vous pouvez l'activer en ajoutant ceci à votre `config.h`:

```
#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE
```

Une fois la fonction activée, utilisez les keycodes `KC_LCAP`, `KC_LNUM` et `KC_LSCR` dans votre keymap.

Des vieux claviers mécaniques ont parfois des touches à verrouillage, mais les claviers modernes n'en sont pas équipés. ***Vous n'avez pas besoin de cette fonction dans la majorité des cas et devez utiliser les keycodes `KC_CAPS`, `KC_NLCK` et `KC_SLCK`.***

## Ajouter des caractères spéciaux autres que ASCII comme la cédille 'Ç'

Voir la fonctionnalité [Unicode](feature_unicode.md).

## Touche `Fn` sur macOS

Contrairement à la plupart des touches Fn, celle des claviers Apple a son propre code d'activation... en quelque sorte. Il remplace le sixième code d'activation dans un rapport de base 6KRO HID - de sorte qu'un clavier Apple ne contient en réalité que 5KRO.

Il est techniquement possible de demander à QMK d’envoyer ce keycode. Cependant, cela nécessite une modification du format du rapport pour ajouter l'état de la touche Fn.
Pire encore, ce keycode n'est reconnu que si les identifiants du clavier VID et PID correspondent à ceux d'un vrai clavier Apple. Malheureusement QMK ne peut juridiquement prendre en charge cette fonctionnalité et il y a peu de chance que la situation s'améliore.

Voir [cette issue](https://github.com/qmk/qmk_firmware/issues/2179) pour des informations détaillées.

## Touches Media sous Mac OSX

#### KC_MNXT et KC_MPRV ne fonctionnent pas sous Mac

Utilisez `KC_MFFD`(`KC_MEDIA_FAST_FORWARD`) et `KC_MRWD`(`KC_MEDIA_REWIND`) à la place de `KC_MNXT` et `KC_MPRV`.
Voir https://github.com/tmk/tmk_keyboard/issues/195

## Touches supportées sous Mac OSX?

Vous pouvez connaître les keycodes supportés par OSX en lisant ce code source.

`usb_2_adb_keymap` contient les tableaux des pages Keyboard/Keypad vers les scancodes ADB (keycodes interne à OSX).

https://opensource.apple.com/source/IOHIDFamily/IOHIDFamily-606.1.7/IOHIDFamily/Cosmo_USB2ADB.c

Et `IOHIDConsumer::dispatchConsumerEvent` s'occupe des utilisations Consumer page.

https://opensource.apple.com/source/IOHIDFamily/IOHIDFamily-606.1.7/IOHIDFamily/IOHIDConsumer.cpp

## Touches JIS dans Mac OSX

Les touches de clavier spécifiques JIS comme `無変換(Muhenkan)`, `変換(Henkan)`, `ひらがな(hiragana)` ne sont pas reconnues par OSX. Vous pouvez utiliser **Seil** pour les activer, esssayez les options suivantes.

* Activer la touche NFER sur clavier PC
* Activer la touche XFER sur clavier PC
* Activer la touche KATAKANA sur clavier PC

https://pqrs.org/osx/karabiner/seil.html

## RN-42 Bluetooth ne fonctionne pas avec Karabiner

Karabiner - Outil de Keymapping sous Mac OSX - Ignore les entrées du module RN-42. Vous devez activer cette option pour rendre Karabiner compatible avec votre clavier.
https://github.com/tekezo/Karabiner/issues/403#issuecomment-102559237

Plus de détails sur ce problème sur les liens suivants.
https://github.com/tmk/tmk_keyboard/issues/213
https://github.com/tekezo/Karabiner/issues/403

## Esc et <code>&#96;</code> sur une touche simple.

Cette fonctionnalité permet d'utiliser une touche à la fois comme touche Échap ou une touche  `§` (En Azerty) selon le cas d’utilisation. Cela est très utile sur un clavier de petite taille.

Voir la fonctionnalité [Grave Escape](feature_grave_esc.md).

## Eject sur Mac OSX

Le keycode`KC_EJCT` fonctionne sous OSX. https://github.com/tmk/tmk_keyboard/issues/250

Il semble que Windows 10 ignore le code et Linux/Xorg le reconnaît mais n'a pas de mapping par défaut.

Nous ne sommes pas sûr quel keycode est utilisé pour la touche Eject sur les claviers Apple officiels. HHKB utilise `F20` pour la touche Eject (`Fn+f`) lorsqu'il est en mode Mac, mais ce n'est probablement pas la même chose que le keycode Eject d'Apple.

## Qu'est-ce que `weak_mods` et `real_mods` dans `action_util.c`

___TO BE IMPROVED___

real_mods est prévu pour retenir l'état des touches modificateur réelles/physiques, alors que weak_mods ne retient l'état que des modificateurs temporaires ou virtuels qui ne devraient pas affecter l'état des touches modificaterus réelles.

Par exemple, disons que vous maintenez la touche physique "shift gauche" et tapez ACTION_MODS_KEY(LSHIFT, KC_A),

en weak_mods,

* (1) maintenir shift gauche : real_mods |= MOD_BIT(LSHIFT)
* (2) appuyer ACTION_MODS_KEY(LSHIFT, KC_A): weak_mods |= MOD_BIT(LSHIFT)
* (3) lâcher ACTION_MODS_KEY(LSHIFT, KC_A): weak_mods &= ~MOD_BIT(LSHIFT)
real_mods garde sur état modificateur.

sans weak_mods,

* (1) maintenir shift gauche : real_mods |= MOD_BIT(LSHIFT)
* (2) appuyer ACTION_MODS_KEY(LSHIFT, KC_A): real_mods |= MOD_BIT(LSHIFT)
* (3) lâcher ACTION_MODS_KEY(LSHIFT, KC_A): real_mods &= ~MOD_BIT(LSHIFT)
ici real_mods a perdu son état pour 'shift gauche physique'.

weak_mods est ORed avec real_mods lorsque le rapport du clavier est envoyé.
https://github.com/tmk/tmk_core/blob/master/common/action_util.c#L57
