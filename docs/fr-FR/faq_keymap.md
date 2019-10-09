# FAQ Keymap

Cette page couvre les questions souvent posées à propos des keymaps. Si vous ne l'avez pas encore fait, vous devriez lire d'abord [Aperçu des Keymap](keymap.md).

## Quels Keycodes puis-je utiliser ?

Regardez [Keycodes](keycodes.md) pour une liste des keycodes disponibles. Ils sont liés à des documentations plus complète lorsque diponible.

Les keycodes sont définies dans [common/keycode.h](https://github.com/qmk/qmk_firmware/blob/master/tmk_core/common/keycode.h).

## Quels sont les keycodes par défaut ?

Il existe 3 configurations de clavier standard utilisées dans le monde: ANSI, ISO et JIS. L'Amérique du Nord utilise principalement l'ANSI, l'Europe et l'Afrique l'ISO et le Japon utilise JIS. Les régions non mentionnées utilisent généralement ANSI ou ISO. Les codes de touches correspondant à ces dispositions sont affichés ici :

<!-- Source for this image: http://www.keyboard-layout-editor.com/#/gists/bf431647d1001cff5eff20ae55621e9a -->
![Keyboard Layout Image](https://i.imgur.com/5wsh5wM.png)

## Certaines de mes touches sont échangées ou ne fonctionnent pas

QMK possède deux fonctionnalités, Bootmagic et Command, qui vous permettent de modifier le comportement de votre clavier à la volée. Cela inclut, sans toutefois s'y limiter, l'échange de Ctrl / Majuscules, la désactivation de l'interface graphique, le basculement de Alt/Gui, le basculement de barre d'espacement arrière/barre oblique inversée, la désactivation de toutes les touches et d'autres modifications comportementales.

Pour résoudre rapidement le problème, essayez de maintenir les touches Espace + Retour arrière enfoncées pendant que vous branchez votre clavier. Cela réinitialisera les paramètres stockés sur votre clavier, ramenant ces touches à un fonctionnement normal. Si cela ne fonctionne pas, regardez ici:

* [Bootmagic](feature_bootmagic.md)
* [Command](feature_command.md)

## La touche de menu ne fonctionne pas

La touche trouvée sur la plupart des claviers modernes située entre `KC_RGUI` et` KC_RCTL` est en réalité appelée `KC_APP`. En effet, lorsque cette touche a été inventée, il existait déjà une clé nommée `MENU` dans les normes correspondantes. MS a donc choisi de l'appeler la touche` APP`.

## `KC_SYSREQ` ne fonctionne pas

Utilisez le keycode pour Print Screen (`KC_PSCREEN` or `KC_PSCR`) à la place de `KC_SYSREQ`. La combinaison de touche 'Alt + Print Screen' est reconnue comme 'System request'.

Voir [issue #168](https://github.com/tmk/tmk_keyboard/issues/168) et
* http://en.wikipedia.org/wiki/Magic_SysRq_key
* http://en.wikipedia.org/wiki/System_request

## Les touches alimentation ne fonctionnent pas

Un peu déroutant, il y a deux codes de touche "Alimentation" dans QMK: `KC_POWER` dans la page d'utilisation du clavier / keypad, et `KC_SYSTEM_POWER` (ou `KC_PWR`) dans la page Consumer.

Le premier n'est reconnu que sur macOS, alors que le dernier, `KC_SLEP` et `KC_WAKE` sont supportés par les trois principaux systèmes d'exploitation. Il est donc recommandé de les utiliser à la place. Sous Windows, ces touches prennent effet immédiatement, mais sur macOS, elles doivent être maintenues enfoncées jusqu'à ce qu'une boîte de dialogue apparaisse.

## Modificateur "One Shot"

Corrige mon problème personnel lié à 'the'. J'écris souvent 'the' ou 'THe' à la place de 'The?. "One shot" shift corrige cela pour moi.

https://github.com/tmk/tmk_keyboard/issues/67

## Modificateur / calque bloqué

Les touches de modification ou les calques peuvent être bloquées si la commutation de calque n'est pas configurée correctement.
Pour les touches de modification et les actions de calque, vous devez placer `KC_TRANS` sur la même position du calque de destination afin de désenregistrer la clé de modificateur ou de revenir au calque précédent lors de la libération.

* https://github.com/tmk/tmk_core/blob/master/doc/keymap.md#31-momentary-switching
* http://geekhack.org/index.php?topic=57008.msg1492604#msg1492604
* https://github.com/tmk/tmk_keyboard/issues/248

## Support de touche à verrouillage mécanique

Cette fonctionnalité est pour *les touches à verrouillage mécanique* comme [celles-ci de chez Alps](http://deskthority.net/wiki/Alps_SKCL_Lock). Vous pouvez l'activer en ajoutant ceci à votre `config.h`:

```
#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE
```

Une fois la fonction activée, utilisez les keycodes `KC_LCAP`, `KC_LNUM` et `KC_LSCR` dans votre keymap.

Des vieux claviers mécaniques ont parfois des touches à vérouillage, mais ls claviers modernes n'en sont pas équipés. ***Vous n'avez pas besoin de cette fonction dans la majorité des cas et devez utiliser les keycodes `KC_CAPS`, `KC_NLCK` et `KC_SLCK`.***

## Ajouter des caractères spéciaux autres que ASCII comme la cédille 'Ç'

IL N'EXISTE AUCUNE METHODE UNIVERSELLE POUR LES AJOUTER QUI FONCTIONNE SUR TOUS LES SYSTEMES. Vous devez définir une **MACRO** d'une manière spécifique à votre OS ou layout.

Voir ce post pour un exemple de code **MACRO**.

http://deskthority.net/workshop-f7/tmk-keyboard-firmware-collection-t4478-120.html#p195620

Sous **Windows** vous pouvez utiliser la touche `AltGr` ou **Alt code**.
* http://en.wikipedia.org/wiki/AltGr_key
* http://en.wikipedia.org/wiki/Alt_code

Sous **Mac OS** définissez une compinaison de touche `Option`.
* http://en.wikipedia.org/wiki/Option_key#Alternative_keyboard_input

Sous **Xorg** vous pouvez utiliser une touche `compose` à la place.
* http://en.wikipedia.org/wiki/Compose_key

Et voir ceci pour une entrée **Unicode**.
* http://en.wikipedia.org/wiki/Unicode_input

## Touche `Fn` sur macOS

Contrairement à la plupart des touches Fn, celle des claviers Apple a son propre code d'activation... en quelque sorte. Il remplace le sixième code d'activation dans un rapport de base 6KRO HID - de sorte qu'un clavier Apple ne contient en réalité que 5KRO.

Il est techniquement possible de demander à QMK d’envoyer cette clé. Cependant, cela nécessite une modification du format du rapport pour ajouter l'état de la touche Fn.
Pire encore, il n'est reconnu que si les VID et PID du clavier correspondent à ceux d'un vrai clavier Apple. Les problèmes juridiques que la prise en charge officielle de QMK pour cette fonctionnalité peuvent créer signifient qu'il est peu probable que cela se produise.

Voir [cette issue](https://github.com/qmk/qmk_firmware/issues/2179) pour des informations détaillées.

## Touches Media sous Mac OSX

#### KC_MNXT et KC_MPRV ne fonctionnent pas sous Mac

Utilisez `KC_MFFD`(`KC_MEDIA_FAST_FORWARD`) et `KC_MRWD`(`KC_MEDIA_REWIND`) à la place de `KC_MNXT` et `KC_MPRV`.
Voir https://github.com/tmk/tmk_keyboard/issues/195

## Touches supportées sous Mac OSX?

Vous pouvez connaître les keycodes supportés par OSX en lisant ce code source.

`usb_2_adb_keymap` contient les tableaux des page Keyboard/Keypad vers les scancodes ADB (keycodes interne à OSX).

https://opensource.apple.com/source/IOHIDFamily/IOHIDFamily-606.1.7/IOHIDFamily/Cosmo_USB2ADB.c

Et `IOHIDConsumer::dispatchConsumerEvent` s'occupe des utilisations Consumer page.

https://opensource.apple.com/source/IOHIDFamily/IOHIDFamily-606.1.7/IOHIDFamily/IOHIDConsumer.cpp

## Touches JIS dans Mac OSX

Les touches de clavier spécifiques JIS comme `無変換(Muhenkan)`, `変換(Henkan)`, `ひらがな(hiragana)` ne sont pas reconnues par OSX. Vous pouvez utiliser **Seil** pour les activer, esssayez les options suivantes.

* Activer la touche NFER sur clavier PC
* Activer la touche XFER sur clavier PC
* Activer la touche KATAKANA sur clavier PC

https://pqrs.org/osx/karabiner/seil.html

## RN-42 Bluetooth Doesn't Work with Karabiner

Karabiner - Keymapping tool on Mac OSX - ignores inputs from RN-42 module by default. You have to enable this option to make Karabiner working with your keyboard.
https://github.com/tekezo/Karabiner/issues/403#issuecomment-102559237

See these for the detail of this problem.
https://github.com/tmk/tmk_keyboard/issues/213
https://github.com/tekezo/Karabiner/issues/403


## Esc and <code>&#96;</code> on a Single Key

See the [Grave Escape](feature_grave_esc.md) feature.

## Arrow on Right Modifier Keys with Dual-Role
This turns right modifier keys into arrow keys when the keys are tapped while still modifiers when the keys are hold. In TMK the dual-role function is dubbed **TAP**.
```

#include "keymap_common.h"


/* Arrow keys on right modifier keys with TMK dual role feature
 *
 *  https://github.com/tmk/tmk_core/blob/master/doc/keymap.md#213-modifier-with-tap-keydual-role
 *  https://en.wikipedia.org/wiki/Modifier_key#Dual-role_keys
 */
const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: qwerty */
    [0] = LAYOUT( \
        ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, NUHS,BSPC, \
        TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS, \
        LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,ENT,  \
        LSFT,NUBS,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,FN0, ESC, \
        FN4, LGUI,LALT,          SPC,                     APP, FN2, FN1, FN3),
    [1] = LAYOUT( \
        GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,\
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,FN5, TRNS, \
        TRNS,TRNS,TRNS,          TRNS,                    TRNS,FN7, FN6, FN8),
};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_MODS_TAP_KEY(MOD_RSFT, KC_UP),
    [1] = ACTION_MODS_TAP_KEY(MOD_RGUI, KC_DOWN),
    [2] = ACTION_MODS_TAP_KEY(MOD_RALT, KC_LEFT),
    [3] = ACTION_MODS_TAP_KEY(MOD_RCTL, KC_RIGHT),
    [4] = ACTION_LAYER_MOMENTARY(1),
    [5] = ACTION_MODS_TAP_KEY(MOD_RSFT, KC_PGUP),
    [6] = ACTION_MODS_TAP_KEY(MOD_RGUI, KC_PGDN),
    [7] = ACTION_MODS_TAP_KEY(MOD_RALT, KC_HOME),
    [8] = ACTION_MODS_TAP_KEY(MOD_RCTL, KC_END),
};

```

Dual-role key: https://en.wikipedia.org/wiki/Modifier_key#Dual-role_keys


## Eject on Mac OSX
`KC_EJCT` keycode works on OSX. https://github.com/tmk/tmk_keyboard/issues/250
It seems Windows 10 ignores the code and Linux/Xorg recognizes but has no mapping by default.

Not sure what keycode Eject is on genuine Apple keyboard actually. HHKB uses `F20` for Eject key(`Fn+f`) on Mac mode but this is not same as Apple Eject keycode probably.


## What's `weak_mods` and `real_mods` in `action_util.c`
___TO BE IMPROVED___

real_mods is intended to retains state of real/physical modifier key state, while
weak_mods retains state of virtual or temporary modifiers which should not affect state real modifier key.

Let's say you hold down physical left shift key and type ACTION_MODS_KEY(LSHIFT, KC_A),

with weak_mods,
* (1) hold down left shift: real_mods |= MOD_BIT(LSHIFT)
* (2) press ACTION_MODS_KEY(LSHIFT, KC_A): weak_mods |= MOD_BIT(LSHIFT)
* (3) release ACTION_MODS_KEY(LSHIFT, KC_A): weak_mods &= ~MOD_BIT(LSHIFT)
real_mods still keeps modifier state.

without weak mods,
* (1) hold down left shift: real_mods |= MOD_BIT(LSHIFT)
* (2) press ACTION_MODS_KEY(LSHIFT, KC_A): real_mods |= MOD_BIT(LSHIFT)
* (3) release ACTION_MODS_KEY(LSHIFT, KC_A): real_mods &= ~MOD_BIT(LSHIFT)
here real_mods lost state for 'physical left shift'.

weak_mods is ORed with real_mods when keyboard report is sent.
https://github.com/tmk/tmk_core/blob/master/common/action_util.c#L57
