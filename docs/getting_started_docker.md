# Docker Quick Start

This project includes a Docker workflow that will allow you to build a new firmware for your keyboard very easily without major changes to your primary operating system. This also ensures that when you clone the project and perform a build, you have the exact same environment as anyone else and the QMK build infrastructure. This makes it much easier for people to help you troubleshoot any issues you encounter.

## Requirements

The main prerequisite is a working `docker` or `podman` install.

* [Docker CE](https://docs.docker.com/install/#supported-platforms)
* [Podman](https://podman.io/getting-started/installation)

## Usage

Acquire a local copy of the QMK's repository (including submodules):

```
git clone --recurse-submodules https://github.com/qmk/qmk_firmware.git
cd qmk_firmware
```

Run the following command to build a keymap:

```
util/docker_build.sh <keyboard>:<keymap>
# For example: util/docker_build.sh planck/rev6:default
```

This will compile the desired keyboard/keymap and leave the resulting `.hex` or `.bin` file in the QMK directory for you to flash. If `:keymap` is omitted, all keymaps are used. Note that the parameter format is the same as when building with `make`.

There is also support for building _and_ flashing the keyboard straight from Docker by specifying the `target` as well:

```
util/docker_build.sh keyboard:keymap:target
# For example: util/docker_build.sh planck/rev6:default:flash
```

Note that mass storage bootloaders are not supported by the `flash` target. In this case you will have to manually copy the firmware file to the keyboard.

You can also start the script without any parameters, in which case it will ask you to input the build parameters one by one, which you may find easier to use:

```
util/docker_build.sh
# Reads parameters as input (leave blank for all keyboards/keymaps)
```

You can manually set which container runtime you want to use by setting the `RUNTIME` environment variable to it's name or path.
By default docker or podman are automatically detected and docker is preferred over podman.

```
RUNTIME="podman" util/docker_build.sh keyboard:keymap:target
```

If flashing is not required, it's possible to run the container as unprivileged (on Linux), and without docker-machine (on Windows/macOS):

```
SKIP_FLASHING_SUPPORT=1 util/docker_build.sh keyboard:keymap:target
```


## FAQ

### Why can't I flash on Windows/macOS

On Windows and macOS, it requires [Docker Machine](http://gw.tnode.com/docker/docker-machine-with-usb-support-on-windows-macos/) to be running. This is tedious to set up, so it's not recommended; use [QMK Toolbox](https://github.com/qmk/qmk_toolbox) instead.

::: warning
Docker for Windows requires [Hyper-V](https://docs.microsoft.com/en-us/virtualization/hyper-v-on-windows/quick-start/enable-hyper-v) to be enabled. This means that it cannot work on versions of Windows which don't have Hyper-V, such as Windows 7, Windows 8 and **Windows 10 Home**.
:::
