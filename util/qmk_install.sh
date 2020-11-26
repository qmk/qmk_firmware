#!/bin/bash

QMK_FIRMWARE_DIR=$(cd -P -- "$(dirname -- "$0")/.." && pwd -P)
QMK_FIRMWARE_UTIL_DIR=$QMK_FIRMWARE_DIR/util

case $(uname -a) in
    *Darwin*)
        . "$QMK_FIRMWARE_UTIL_DIR/install/macos.sh";;
    *FreeBSD*)
        . "$QMK_FIRMWARE_UTIL_DIR/install/freebsd.sh";;
    *MINGW64_NT*)
        . "$QMK_FIRMWARE_UTIL_DIR/install/msys2.sh";;
    *MSYS_NT*|*MINGW32_NT*)
        echo "Please open a MinGW64 terminal window and re-run this script."
        exit 1;;
    *Linux*)
        . "$QMK_FIRMWARE_UTIL_DIR/install/linux_shared.sh"

        case $(grep ID /etc/os-release) in
            *arch*|*manjaro*)
                . "$QMK_FIRMWARE_UTIL_DIR/install/arch.sh";;
            *debian*|*ubuntu*)
                . "$QMK_FIRMWARE_UTIL_DIR/install/debian.sh";;
            *fedora*)
                . "$QMK_FIRMWARE_UTIL_DIR/install/fedora.sh";;
            *gentoo*)
                . "$QMK_FIRMWARE_UTIL_DIR/install/gentoo.sh";;
            *opensuse*|*tumbleweed*)
                . "$QMK_FIRMWARE_UTIL_DIR/install/opensuse.sh";;
            *sabayon*)
                . "$QMK_FIRMWARE_UTIL_DIR/install/sabayon.sh";;
            *slackware*)
                . "$QMK_FIRMWARE_UTIL_DIR/install/slackware.sh";;
            *solus*)
                . "$QMK_FIRMWARE_UTIL_DIR/install/solus.sh";;
            *void*)
                . "$QMK_FIRMWARE_UTIL_DIR/install/void.sh";;
            *)
                echo "Sorry, we don't recognize your distribution. Help us by contributing support!"
                echo
                echo "https://docs.qmk.fm/#/contributing"
                exit 1;;
        esac

        if uname -a | grep -qi microsoft; then
            echo "********************************************************************************"
            echo "* Detected Windows Subsystem for Linux.                                        *"
            echo "* Currently, WSL has no access to USB devices and so flashing from within the  *"
            echo "* WSL terminal will not work.                                                  *"
            echo "*                                                                              *"
            echo "* Please install the QMK Toolbox instead:                                      *"
            echo "*    https://github.com/qmk/qmk_toolbox/releases                               *"
            echo "* Then, map your WSL filesystem as a network drive:                            *"
            echo "*    \\\\\\\\wsl$\\<distro>                                                           *"
            echo "********************************************************************************"
            echo
        fi
        ;;
    *)
        echo "Sorry, we don't recognize your environment. Help us by contributing support!"
        echo
        echo "https://docs.qmk.fm/#/contributing"
        exit 1;;
esac

if type _qmk_install_prepare &>/dev/null; then
    _qmk_install_prepare || exit 1
fi

_qmk_install

if type _qmk_install_bootloadhid &>/dev/null; then
    _qmk_install_bootloadhid
fi
