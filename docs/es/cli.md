# QMK CLI

Esta página describe como configurar y utilizar QMK CLI.

# Sumario

QMK CLI hace la tarea de construir y trabajar con teclados QMK más fácil. Hemos provisto un número de comandos para simplificar y coordinar tareas como obtener y compilar el firmware QMK, crear keymaps y más.

* [Global CLI](#global-cli)
* [Local CLI](#local-cli)
* [Comandos CLI](#cli-commands)

# Requerimientos

La CLI require Python 3.5 o superior. Tratamos de mantener el número de requisitos lo más bajo posible pero también necesitaras instalar los paquetes listados en [`requirements.txt`](https://github.com/qmk/qmk_firmware/blob/master/requirements.txt).

# Global CLI

QMK provee una CLI instalable que puede ser usada para configurar tu entorno de desarrollo QMK, trabajar con QMK, y hace que trabajar con múltiples copias de `qmk_firmware` sea más fácil. Recomendamos instalar y actualizar periódicamente esta herramienta.

## Instalar con Homebrew (macOS, algunos Linux)

Si ya instalaste [Homebrew](https://brew.sh) puedes hacer `tap` e `install` de QMK:

```
brew tap qmk/qmk
brew install qmk
export QMK_HOME='~/qmk_firmware' # Opcional, definir la ubicación de `qmk_firmware`
qmk setup  # Esto clona `qmk/qmk_firmware` y opcionalmente configura tu entorno de desarrollo
```

## Instalar usando easy_install o pip

Si tu sistema no está listado más arriba puedes instalar QMK manualmente. Primero asegurate de tener python 3.5 (o superior) instalado y tener instalado pip. Después instala QMK con este comando:

```
pip3 install qmk
export QMK_HOME='~/qmk_firmware' # Opcional, definir la ubicación de `qmk_firmware`
qmk setup  # Esto clona `qmk/qmk_firmware` y opcionalmente configura tu entorno de desarrollo
```

## Empaquetado para otros Sistemas Operativos

Estamos en búsqueda de gente para crear y mantener un paquete `qmk` para más sistemas operativos. Si deseas crear un paquete para tu SO por favor sigue estos lineamientos:

* Sigue las mejores prácticas para tu SO, cuando entren en conflicto con estos lineamientos
    * Documenta porque en un comentario en donde ocurra
* Instalar utilizando un entorno virtual
* Dile al usuario como definir la variable de entorno `QMK_HOME` para poder descargar el firmware en un lugar diferente a `~/qmk_firmware`.

# Local CLI

Si no quieres usar Global CLI existe una versión local empaquetada con `qmk_firmware`. Puedes encontrarla en `qmk_firmware/bin/qmk`. Puedes correr el comando `qmk` desde cualquier directorio y siempre operará esta copia de `qmk_firmware`.

**Ejemplo**:

```
$ ~/qmk_firmware/bin/qmk hello
Ψ Hello, World!
```

## Limitaciones de Local CLI

Existen ciertas limitaciones de Local CLI comparado con Global CLI:

* Local CLI no soporta los comandos `qmk setup` o `qmk clone`
* Local CLI siempre opera en el mismo árbol `qmk_firmware`, incluso si tienes múltiples repositorios clonados.
* Local CLI no corre en un entorno virtual, por lo tanto es posible que existan conflictos con sus dependencias.

# Comandos CLI

## `qmk compile`

Este comando te permite compilar el firmware de cualquier directorio. Puedes compilar JSON exportados de <https://config.qmk.fm> o compilar keymaps en el repositorio.

**Uso para Exports de Configurator**:

```
qmk compile <configuratorExport.json>
```

**Uso para Keymaps**:

```
qmk compile -kb <keyboard_name> -km <keymap_name>
```

## `qmk cformat`

Este comando da formato a código C usando clang-format. Córrelo sin argumentos para aplicar el formato a todo el código del núcleo, o agrega nombres de archivo en la línea de comandos para correrlo sobre archivos específicos.

**Uso**:

```
qmk cformat [file1] [file2] [...] [fileN]
```

## `qmk config`

Este comando te permite configurar el comportamiento de QMK. Para ver la documentación completa de `qmk config` ir a [CLI Configuration](es/cli_configuration.md)

**Uso**:

```
qmk config [-ro] [config_token1] [config_token2] [...] [config_tokenN]
```

## `qmk docs`

Este comando inicia un servidor local HTTP que puedes utilizar para navegar o mejorar la documentación. El puerto por defecto es 8936


**Uso**:

```
qmk docs [-p PORT]
```

## `qmk doctor`

Este comando examina tu entorno y te alerta acerca de problemas potenciales en el build o el flasheo.

**Uso**:

```
qmk doctor
```

## `qmk list-keyboards`

Este comando enlista todos los teclados que se encuentran actualmente definidos en `qmk_firmware`

**Uso**:

```
qmk list-keyboards
```

## `qmk new-keymap`

Este comando crea un keymap nuevo basado en un keymap de un teclado existente.

**Uso**:

```
qmk new-keymap [-kb KEYBOARD] [-km KEYMAP]
```

## `qmk pyformat`

Este comando da formato a código de python en `qmk_firmware`.

**Uso**:

```
qmk pyformat
```

## `qmk pytest`

Este comando corre el set de pruebas de pyhton. Si realizas algún cambio en código de python debes asegurarte de que este comando corra satisfactoriamente.

**Uso**:

```
qmk pytest
```
