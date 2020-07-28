# Тестирование и отладка

После того, как вы загрузили собственную прошивку в клавиатуру, её нужно протестировать. Если вам повезет, то всё будет работать идеально. Но если что-то пошло не так, то этот раздел поможет вам выяснить причину.

## Тестирование

Тестирование клавиатуры обычно является достаточно тривиальной процедурой. Нажмите на каждую клавишу и убедитесь, что она выдаёт ожидаемый результат. Для этого можно использовать режим тестирования в QMK Configurator](https://config.qmk.fm/#/test/) даже если ваша клавиатура не работает на QMK.

## Отладка :id=debugging

Ваша клавиатура будет выводить отладочную информацию, если вы добавили в `rules.mk` строчку `CONSOLE_ENABLE = yes`. По умолчанию выводимая информация крайне ограничена, но можно включить режим отладки для получения более детальных сведений. Включить его можно при помощи кода `DEBUG` в раскладке, при помощи [Command](ru-ru/feature_command.md) или добавив следующий код в раскладку:

```c
void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}
```

## Отладочные инструменты

Для отладки клавиатуры можно использовать одну из двух утилит.

### Отладка в QMK Toolbox

На поддерживаемых платформах можно использовать [QMK Toolbox](https://github.com/qmk/qmk_toolbox) для вывода отладочной информации.

### Отладка в hid_listen

Если вам нужна консольная утилита, то можно использовать [hid_listen](https://www.pjrc.com/teensy/hid_listen.html), разработанный PJRC. Готовые исполняемые файлы есть для Windows, Linux, и MacOS.

## Отправка собственных отладочных сообщений

Иногда бывает необходимо отправлять отладочные сообщения из [собственных функций](ru-ru/custom_quantum_functions.md). Это достаточно просто. Начните с включения `print.h` в начале вашего файла:

    #include <print.h>

После чего можно будет использовать следующие функции для печати:

* `print("строка")`: вывод простой строки.
* `uprintf("%s строка", var)`: вывод форматированной строки
* `dprint("строка")` вывод строки при включенном режиме отладки
* `dprintf("%s строка", var)`: вывод форматированной строки при включенном режиме отладки

## Примеры отладки

Далее приводятся различные примеры отладки из практики. За дополнительной информацией обращайтесь к разделу «[Отладка и устранение проблем в QMK](ru-ru/faq_debug.md)».

### Положение нажатой клавиши в матрице

При портировании или диагностике проблем с печатной платой бывает необходимо убедиться в том, что нажатие клавиши распознаётся корректно. Для включения логирования для этого сценария в `keymap.c` нужно добавить следующий код:

```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif
  return true;
}
```

Пример вывода:

```text
Waiting for device:.......
Listening:
KL: kc: 169, col: 0, row: 0, pressed: 1
KL: kc: 169, col: 0, row: 0, pressed: 0
KL: kc: 174, col: 1, row: 0, pressed: 1
KL: kc: 174, col: 1, row: 0, pressed: 0
KL: kc: 172, col: 2, row: 0, pressed: 1
KL: kc: 172, col: 2, row: 0, pressed: 0
```

### Сколько времени заняло сканирование нажатой клавиши?

При изучении проблем с производительностью возникает необходимость знать частоту, с которой сканируется матрица. Для логирования соответствующих данных добавьте следующий код в `config.h` своей раскладки:

```c
#define DEBUG_MATRIX_SCAN_RATE
```

Example output
```text
  > matrix scan frequency: 315
  > matrix scan frequency: 313
  > matrix scan frequency: 316
  > matrix scan frequency: 316
  > matrix scan frequency: 316
  > matrix scan frequency: 316
```
