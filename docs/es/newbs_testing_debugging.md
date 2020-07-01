# Testeando y depurando

Una vez que hayas flasheado tu teclado con un firmware personalizado estarás listo para probarlo. Con un poco de suerte todo funcionará a la primera, pero si no es así, este documento te ayudará a averiguar qué está mal.

## Probando

Probar tu teclado es generalmente bastante sencillo. Persiona cada una de las teclas y asegúrate de que envía la tecla correcta. Existen incluso programas que te ayudarán a asegurarte de que no te dejas ninguna tecla sin comprobar.

Nota: Estos programas no los provée ni están relacionados con QMK.

* [Switch Hitter](https://elitekeyboards.com/switchhitter.php) (Sólo Windows)
* [Keyboard Viewer](https://www.imore.com/how-use-keyboard-viewer-your-mac) (Sólo Mac)
* [Keyboard Tester](http://www.keyboardtester.com) (Aplicación web)
* [Keyboard Checker](http://keyboardchecker.com) (Aplicación web)

## Depurando

Tu teclado mostrará información de depuración si tienes `CONSOLE_ENABLE = yes` en tu `rules.mk`. Por defecto la información de salida es muy limitada, pero puedes encender el modo de depuración para incrementar la información de salida. Utiliza el keycode `DEBUG` de tu keymap, usa la característica [Comando](feature_command.md) para activar el modo depuración, o añade el siguiente código a tu keymap.

```c
void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}
```

### Depurando con QMK Toolbox

Para plataformas compatibles, [QMK Toolbox](https://github.com/qmk/qmk_toolbox) se puede usar para mostrar mensajes de depuración de tu teclado.

### Depurando con hid_listen

¿Prefieres una solución basada en una terminal? [hid_listen](https://www.pjrc.com/teensy/hid_listen.html), provista por PJRC, se puede usar también para mostrar mensajes de depuración. Hay binarios preconstruídos para Windows,Linux,y MacOS.

<!-- FIXME: Describe the debugging messages here. -->

## Enviando tus propios mensajes de depuración

A veces, es útil imprimir mensajes de depuración desde tu [código personalizado](custom_quantum_functions.md). Hacerlo es bastante simple. Comienza incluyendo `print.h` al principio de tu fichero:

    #include <print.h>

Después de eso puedes utilzar algunas funciones print diferentes:

* `print("string")`: Imprime un string simple
* `uprintf("%s string", var)`: Imprime un string formateado
* `dprint("string")` Imprime un string simple, pero sólo cuando el modo de depuración está activo
* `dprintf("%s string", var)`: Imprime un string formateado, pero sólo cuando el modo de depuración está activo

## Ejemplos de depuración

Debajo hay una colección de ejemplos de depuración del mundo real. Para información adicional, Dirígete a [Depurando/Encontrando problemas en QMK](faq_debug.md).

### ¿Que posición en la matriz tiene esta pulsación de tecla?

Cuando estés portando, o intentando diagnosticar problemas en la pcb, puede ser útil saber si la pulsación de una tecla es escaneada correctamente. Para hablitar la información de registro en este escenario, añade el siguiente código al `keymap.c` de tus keymaps

```c
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif 
  return true;
}
```

Ejemplo de salida
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

### ¿Cuanto tiempo tardó en escanear la pulsación de una tecla?

Cuando estés probando problemas en el rendimiento, puede ser útil saber la frecuenta a la cual la matríz de pulsadores se está escaneando. Para hablitar la información de registro en este escenario, añade el siguiente código al `config.h` de tus keymaps

```c
#define DEBUG_MATRIX_SCAN_RATE
```

Ejemplo de salida
```text
  > matrix scan frequency: 315
  > matrix scan frequency: 313
  > matrix scan frequency: 316
  > matrix scan frequency: 316
  > matrix scan frequency: 316
  > matrix scan frequency: 316
```
