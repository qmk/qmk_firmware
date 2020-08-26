# Mejores prácticas

## O, "Cómo aprendí a dejar de preocuparme y amarle a Git."

Este documento procura instruir a los novatos en las mejores prácticas para tener una experiencia más fácil en contribuir a QMK. Te guiaremos por el proceso de contribuir a QMK, explicando algunas maneras de hacerlo más fácilmente, y luego romperemos algunas cosas para enseñarte cómo arreglarlas.

En este documento suponemos un par de cosas:

1. Tienes una cuenta de GitHub, y has hecho un [fork del repo qmk_firmware](getting_started_github.md) en tu cuenta.
2. Has [configurado tu entorno de desarrollo](newbs_getting_started.md?id=environment-setup).


## La rama master de tu fork: Actualizar a menudo, nunca commit

Se recomienda que para desarrollo con QMK, lo que sea que estés haciendo, mantener tu rama `master` actualizada, pero **nunca** commit en ella. Mejor, haz todos tus cambios en una rama de desarrollo y manda pull requests de tus ramas mientras programas.

Para evitar los conflictos de merge &mdash; cuando dos o más usuarios han editado la misma parte de un archivo al mismo tiempo &mdash; mantén tu rama `master` actualizada, y empieza desarrollo nuevo creando una nueva rama.

### Actualizando tu rama master

Para mantener tu rama `master` actualizada, se recomienda agregar el repository ("repo") de Firmware QMK como un repo remoto en git. Para hacer esto, abre tu interfaz de línea de mandatos y ingresa:
```
git remote add upstream https://github.com/qmk/qmk_firmware.git
```

Para verificar que el repo ha sido agregado, ejecuta `git remote -v`, y lo siguiente debe aparecer:

```
$ git remote -v
origin  https://github.com/<your_username>/qmk_firmware.git (fetch)
origin  https://github.com/<your_username>/qmk_firmware.git (push)
upstream        https://github.com/qmk/qmk_firmware.git (fetch)
upstream        https://github.com/qmk/qmk_firmware.git (push)
```

Ya que has hecho esto, puedes buscar actualizaciones del repo ejecutando `git fetch upstream`. Esto busca las ramas y etiquetas &mdash; juntos conocidos como "refs" &mdash; del repo QMK, que ahora tiene el apodo `upstream`. Ahora podemos comparar los archivos en nuestro fork `origin` con los de QMK.

Para actualizar la rama master de tu fork, ejecuta lo siguiente, pulsando Intro después de cada línea:

```
git checkout master
git fetch upstream
git pull upstream master
git push origin master
```

Esto te coloca en tu rama master, busca los refs del repo de QMK, descarga la rama `master` actual a tu computadora, y después lo sube a tu fork.

### Hacer cambios

Para hacer cambios, crea una nueva rama ejecutando:

```
git checkout -b dev_branch
git push --set-upstream origin dev_branch
```

Esto crea una nueva rama llamada `dev_branch`, te coloca en ella, y después guarda la nueva rama a tu fork. El parámetro `--set-upstream` le dice a git que use tu fork y la rama `dev_branch` cada vez que uses `git push` o `git pull` en esta rama. Solo necesitas usarlo la primera que que subes cambios; ya después, puedes usar `git push` o `git pull`, sin usar los demás parámetros.

!> Con `git push`, puedes usar `-u` en vez de `--set-upstream` &mdash; `-u` es un alias de `--set-upstream`.

Puedes nombrar tu rama casi cualquier cosa, pero se recomienda ponerle algo con relación a los cambios que vas a hacer.

Por defecto `git checkout -b` se basará tu nueva rama en la rama en la cual estás actualmente. Puedes basar tu rama en otra rama existente agregando el nombre de la rama al comando:

```
git checkout -b dev_branch master
```

Ahora que tienes una rama development, abre tu editor de texto y haz los cambios que quieres. Se recomienda hacer varios commits pequeños a tu rama; de este modo cualquier cambio que causa problemas puede ser rastreado y deshecho si fuera necesario. Para hacer tus cambios, edita y guarda los archivos que necesitas actualizar, agrégalos al *staging area* de Git, y luego haz un commit a tu rama:

```
git add path/to/updated_file
git commit -m "My commit message."
```
`git add` agrega los archivos que han sido cambiados al *staging area* de Git, lo cual es la "zona de preparación"de Git. Este contiene los cambios que vas a *commit* usando `git commit`, que guarda los cambios en el repo. Usa un mensaje de commit descriptivo para que puedas saber que ha cambiado fácilmente.

!> Si has cambiado muchos archivos, pero todos los archivos son parte del mismo cambio, puedes usar `git add .` para agregar todos los archivos cambiados que están en tu directiro actual, en vez de agregar cada archivo manualmente.

### Publicar tus cambios

El útimo paso es subir tus cambios a tu fork. Para hacerlo, ejecuta `git push`. Ahora Git publicará el estado actual de `dev_branch` a tu fork.


## Resolver los conflictos del merge

A veces cuando el trabajo en una rama tarda mucho tiempo en completarse,  los cambios que han sido hechos por otros chocan con los cambios que has hecho en tu rama cuando abres un pull request. Esto se llama un *merge conflict*, y es algo que ocurre cuando varias personas editan las mismas partes de los mismos archivos.

### Rebase tus cambios

Un *rebase* es la manera de Git de tomar los cambios que se aplicaron en un punto, deshacerlos, y aplicar estos mismos cambios en otro punto. En el caso de un conflicto de merge, puedes hacer un rebase de tu rama para recoger los cambios que has hecho.

Para empezar, ejecuta lo siguiente:

```
git fetch upstream
git rev-list --left-right --count HEAD...upstream/master
```

El comando `git rev-list` ejecutado aquí muestra el número de commits que difieren entre la rama actual y la rama master de QMK. Ejecutamos `git fetch` primero para asegurarnos de que tenemos los refs que representan es estado actual del repo upstream. El output del comando `git rev-list` muestra dos números:

```
$ git rev-list --left-right --count HEAD...upstream/master
7       35
```

El primer número representa el número de commits en la rama actual desde que fue creada, y el segundo número es el número de commits hecho a `upstream/master` desde que la rama actual fue creada, o sea los cambios que no están registrados en la rama actual.

Ahora que sabemos el estado actual de la rama actual y el del repo upstream, podemos empezar una operación rebase:

```
git rebase upstream/master
```
Esto le dice a Git que deshaga los commits en la rama actual, y después los re-aplica en la rama master de QMK.

```
$ git rebase upstream/master
First, rewinding head to replay your work on top of it...
Applying: Commit #1
Using index info to reconstruct a base tree...
M       conflicting_file_1.txt
Falling back to patching base and 3-way merge...
Auto-merging conflicting_file_1.txt
CONFLICT (content): Merge conflict in conflicting_file_1.txt
error: Failed to merge in the changes.
hint: Use 'git am --show-current-patch' to see the failed patch
Patch failed at 0001 Commit #1

Resolve all conflicts manually, mark them as resolved with
"git add/rm <conflicted_files>", then run "git rebase --continue".
You can instead skip this commit: run "git rebase --skip".
To abort and get back to the state before "git rebase", run "git rebase --abort".
```

Esto nos dice que tenemos un conflicto de merge, y nos dice el nombre del archivo con el conflict. Abre el archivo en tu editor de texto, y en alguna parte del archivo verás algo así:

```
<<<<<<< HEAD
<p>For help with any issues, email us at support@webhost.us.</p>
=======
<p>Need help? Email support@webhost.us.</p>
>>>>>>> Commit #1
```
La línea `<<<<<<< HEAD` marca el principio de un conflicto de merge, y la línea `>>>>>>> Commit #1` marca el final, con las secciones de conflicto separadas por `=======`. La parte del lado `HEAD` is de la versión de QMK master del archivo, y la parte marcada con el mensaje de commit es de la rama actual.

Ya que Git rastrea *cambios de archivos* en vez del contenido de los archivos directamente, si Git no puede encontrar el texto que estaba en el archivo antes del último commit, no sabrá cómo editar el archivo. El editar el archivo de nuevo resolverá este conflicto. Haz tus cambios, y guarda el archivo.

```
<p>Need help? Email support@webhost.us.</p>
```

Ahora ejecuta:

```
git add conflicting_file_1.txt
git rebase --continue
```

Git registra los cambios al archivo con conflictos, y sigue aplicando los commits de nuestra rama hasta llegar al final.
