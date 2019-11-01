# Configuración de  QMK CLI

Este documento explica como funciona el comando `qmk config`.

# Introducción

La configuración para QMK CLI es un sistema de pares clave/valor. Cada clave consiste de un subcomando y un nombre de argumento separados por punto. Esto permite una traducción sencilla y directa entre las claves de configuración y los argumentos que definen.

## Ejemplo Simple

Como ejemplo veamos el comando `qmk compile --keyboard clueboard/66/rev4 --keymap default`.

Existen dos argumentos que pueden ser leídos desde la configuración en lugar de la línea de comandos:

* `compile.keyboard`
* `compile.keymap`

Vamos a definir esto:

```
$ qmk config compile.keyboard=clueboard/66/rev4 compile.keymap=default
compile.keyboard: None -> clueboard/66/rev4
compile.keymap: None -> default
Ψ Wrote configuration to '/Users/example/Library/Application Support/qmk/qmk.ini'
```

Ahora puedo correr `qmk compile` sin especificar ni mi teclado ni keymap cada vez.

## Definiendo User Defaults

A veces quieres compartir una configuración con multiples comandos. Por ejemplo, multiples comandos toman el argumento `--keyboard`. En lugar de definir este valor para cada comando puedes definir un valor de usuario que será utilizado para cualquier comando que tome ese argumento.

Ejemplo:

```
$ qmk config user.keyboard=clueboard/66/rev4 user.keymap=default
user.keyboard: None -> clueboard/66/rev4
user.keymap: None -> default
Ψ Wrote configuration to '/Users/example/Library/Application Support/qmk/qmk.ini'
```

# Documentación de CLI (`qmk config`)

El comando `qmk config` se utiliza para interactuar con la configuración. Cuando se ejecuta sin argumentos muestra la configuración actual. Cuando hay argumentos presentes se asume que estos son tokens de configuración, los cuales son cadenas sin espacios de la siguiente forma:

    <subcomando|general|default>[.<clave>][=<valor>]

## Definiendo valores de configuración

Puedes definir valores de configuración agregando un signo de igual (=) a la clave de configuración. La clave siempre debe ser en su forma completa `<sección>.<clave>`.

Ejemplo:

```
$ qmk config default.keymap=default
default.keymap: None -> default
Ψ Wrote configuration to '/Users/example/Library/Application Support/qmk/qmk.ini'
```

## Leyendo Valores de Configuración

Puedes leer valores de configuración, puede ser la configuración completa, una sola clave o una sección entera. Siempre puedes especificar múltiples claves para mostrar más de un valor.

### Ejemplo de configuración completa

    qmk config

### Ejemplo de sección completa

    qmk config compile

### Ejemplo de una sola clave

    qmk config compile.keyboard

### Ejemplo de múltiples claves

    qmk config user compile.keyboard compile.keymap

## Eliminando valores de configuración

Puedes eliminar un valor de configuración definiendolo como la cadena especial `None`.

Ejemplo:

```
$ qmk config default.keymap=None
default.keymap: default -> None
Ψ Wrote configuration to '/Users/example/Library/Application Support/qmk/qmk.ini'
```

## Operaciones Múltiples

Puedes combinar múltiples operaciones de lectura y escritura en un solo comando. Estas serán ejecutadas y mostradas en orden:

```
$ qmk config compile default.keymap=default compile.keymap=None
compile.keymap=skully
compile.keyboard=clueboard/66_hotswap/gen1
default.keymap: None -> default
compile.keymap: skully -> None
Ψ Wrote configuration to '/Users/example/Library/Application Support/qmk/qmk.ini'
```

# Opciones de Configuración de Usuario

| Clave | Valor por Defecto | Descripción |
|-------|-------------------|-------------|
| user.keyboard | None | La ruta al teclado (Ejemplo: `clueboard/66/rev4`) |
| user.keymap | None | El nombre del keymap (Ejemplo: `default`) |
| user.name | None | El nombre de usuario en github del usuario. |

# Todas las Opciones de Configuración

| Clave | Valor por Defecto | Descripción |
|-------|-------------------|-------------|
| compile.keyboard | None | La ruta al teclado (Ejemplo: `clueboard/66/rev4`) |
| compile.keymap | None | El nombre del keymap (Ejemplo: `default`) |
| hello.name | None | EL nombre del sauldo al ejecutar. |
| new_keyboard.keyboard | None | La ruta al reclado (Ejemplo: `clueboard/66/rev4`) |
| new_keyboard.keymap | None | El nombre del keymap (Ejemplo: `default`) |
