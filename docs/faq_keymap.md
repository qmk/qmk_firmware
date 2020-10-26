# Keymap - вопросы и ответы


Вопросы, которые часто возникают в процессе создания раскладок. 
Но для начала лучше прочитать [Keymap Overview](https://docs.qmk.fm/#/keymap).

## Какие коды клавиш(Keycodes) я могу использовать?

См. Раздел [«Keycodes»](https://docs.qmk.fm/#/keycodes) для получения списка доступных вам кодов клавиш. Они содержат ссылки на более обширную документацию, если таковая имеется.
Коды клавиш фактически определены в common/keycode.h.

## Какие коды клавиш используются по умолчанию?

В мире используются 3 стандартные раскладки клавиатуры: ANSI, ISO и JIS. Северная Америка в основном использует ANSI, Европа и Африка в первую очередь используют ISO, а Япония использует JIS. 
Не упомянутые регионы обычно используют ANSI или ISO. Коды клавиш, соответствующие этим раскладкам, показаны здесь:

![стандартные раскладки клавиатуры](https://i.imgur.com/5wsh5wM.png)

## Как назвать свои сложно-составные кей-коды для клавиш?

Иногда для удобства полезно определить собственные имена для некоторых клави-кодов. Люди часто определяют собственные имена с помощью #define. 
Например:
```c
#define FN_CAPS LT(_FL, KC_CAPSLOCK)
#define ALT_TAB LALT(KC_TAB)
```

Это позволит вам использовать FN_CAPS и ALT_TAB в вашей раскладке, делая ее более читаемой.

## Некоторые из моих клавиш "поменялись местами" или не работают. Что делать?

QMK имеет две функции, Bootmagic и Command, которые позволяют вам изменять поведение клавиатуры "на лету". 
Это включает, но не ограничивается, замену Ctrl/Caps, отключение Gui, замену Alt/Gui, замену Backspace/Backslash, отключение всех клавиш и другие поведенческие модификации.
В качестве быстрого решения попробуйте удерживать клавиши Space + Backspace при подключении клавиатуры. 
Это приведет к сбросу сохраненных настроек на вашей клавиатуре, и эти клавиши вернутся к нормальной работе. Если это не сработает, посмотрите здесь:
* [Bootmagic](https://docs.qmk.fm/#/feature_bootmagic)
* [Command](https://docs.qmk.fm/#/feature_command)

## Клавиша "меню" не работает

Клавиша на большинстве современных клавиатур, расположенная между KC_RGUI и KC_RCTL, на самом деле называется KC_APP. 
Это связано с тем, что когда она появилась, в соответствующих стандартах уже был ключ с именем MENU, поэтому MS решила назвать его ключом APP.

## KC_SYSREQ не работает

Используйте для функции PrintScreen кей-код (KC_PSCREEN или KC_PSCR) вместо KC_SYSREQ. Сочетание клавиш «Alt + Print Screen» распознается как «Системный запрос».
См "задачу" #168 и
    <http://en.wikipedia.org/wiki/Magic_SysRq_key>
    <http://en.wikipedia.org/wiki/System_request>

## Клавиши питания не работают

Несколько сбивает с толку то, что в QMK есть два кода клавиш «Power»: KC_POWER на стороне HID-клавиатуры/клавиатуры и KC_SYSTEM_POWER (или KC_PWR) на стороне ОС (проверить!!!).
Первый кей-код распознается только в macOS, в то время как второй, как и KC_SLEP и KC_WAKE поддерживаются всеми тремя основными операционными системами, поэтому рекомендуется использовать именно их. 
В Windows эти клавиши работают непосредственно, однако в macOS их нужно удерживать, пока не появится диалоговое окно.


## Модификатор One Shot

Касается личной "проблемы" автора этих строк. Он часто ошибочно набирал «the» или «THe» вместо «The». One Shot Shift частично решает этот вопрос <https://github.com/tmk/tmk_keyboard/issues/67>


## Модификатор или слой завис

Клавиши-модификаторы или слои могут зависнуть, если переключение слоев не настроено должным образом.
Для клавиш-модификаторов и действий слоя вы должны поместить KC_TRANS в ту же позицию целевого слоя, чтобы отменить регистрацию клавиши-модификатора или вернуться к предыдущему слою при событии выпуска.

При задействовании клавиш-модификаторов и переключении слоёв вы должны поместить кей-код KC_TRANS в соответственные позиции нужного слоя, чтобы оставить этот модификатор доступным для использования.

    <https://github.com/tmk/tmk_core/blob/master/doc/keymap.md#31-momentary-switching>
    <http://geekhack.org/index.php?topic=57008.msg1492604#msg1492604>
    <https://github.com/tmk/tmk_keyboard/issues/248>

## Поддержка Mechanical Lock с помощью свичей (Mechanical Lock ???)

This feature is for mechanical lock switch like this Alps one. You can enable it by adding this to your config.h:
Эта функция доступна для механического включения блокировки(чего?), такого как, на Alps. Вы можете включить это, добавив это в свой config.h:
```c
#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE
```

После включения этой функции используйте коды клавиш KC_LCAP, KC_LNUM и KC_LSCR в вашей таблице клавиш вместо(чего???).
На старых старинных механических клавиатурах иногда есть блокировка (чего???), а на современных их нет. В большинстве случаев эта функция не требуется, просто используйте коды клавиш KC_CAPS, KC_NLCK и KC_SLCK.

## Ввод спецсимволов, которых нет в таблице ASCII, например как Cédille ‘Ç’

Смотрите [функции, связанные с Unicode](https://docs.qmk.fm/#/feature_unicode)

---

untranslated part:


## `Fn` Key on macOS

Unlike most Fn keys, the one on Apple keyboards actually has its own keycode... sort of. It takes the place of the sixth keycode in a basic 6KRO HID report -- so an Apple keyboard is in fact only 5KRO.

It is technically possible to get QMK to send this key. However, doing so requires modification of the report format to add the state of the Fn key.
Even worse, it is not recognized unless the keyboard's VID and PID match that of a real Apple keyboard. The legal issues that official QMK support for this feature may create mean it is unlikely to happen.

See [this issue](https://github.com/qmk/qmk_firmware/issues/2179) for detailed information.

## Keys Supported in Mac OSX?
You can know which keycodes are supported in OSX from this source code.

`usb_2_adb_keymap` array maps Keyboard/Keypad Page usages to ADB scancodes(OSX internal keycodes).

https://opensource.apple.com/source/IOHIDFamily/IOHIDFamily-606.1.7/IOHIDFamily/Cosmo_USB2ADB.c

And `IOHIDConsumer::dispatchConsumerEvent` handles Consumer page usages.

https://opensource.apple.com/source/IOHIDFamily/IOHIDFamily-606.1.7/IOHIDFamily/IOHIDConsumer.cpp


## JIS Keys in Mac OSX
Japanese JIS keyboard specific keys like `無変換(Muhenkan)`, `変換(Henkan)`, `ひらがな(hiragana)` are not recognized on OSX. You can use **Seil** to enable those keys, try following options.

* Enable NFER Key on PC keyboard
* Enable XFER Key on PC keyboard
* Enable KATAKANA Key on PC keyboard

https://pqrs.org/osx/karabiner/seil.html


## RN-42 Bluetooth Doesn't Work with Karabiner
Karabiner - Keymapping tool on Mac OSX - ignores inputs from RN-42 module by default. You have to enable this option to make Karabiner working with your keyboard.
https://github.com/tekezo/Karabiner/issues/403#issuecomment-102559237

See these for the detail of this problem.
https://github.com/tmk/tmk_keyboard/issues/213
https://github.com/tekezo/Karabiner/issues/403


## Esc and <code>&#96;</code> on a Single Key

See the [Grave Escape](feature_grave_esc.md) feature.

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
