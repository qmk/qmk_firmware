#!/usr/bin/env bash

_qmk_install_prepare() {

    echo "Determine system architecture"

    case $(brew config) in
        *x86_64*)
            echo "x86_brew"
            brew update && brew upgrade --formulae --ignore-pinned
            QMK_BREW="default"
            ;;
        *arm64*)
            if [ -f "/usr/local/bin/brew" ]; then
                echo "You have x86 Homebrew installation at /usr/local/bin/brew."
                if ! arch -x86_64 /usr/local/bin/brew --version >/dev/null 2>&1; then
                    echo "Error! X86 homebrew is broken."
                    echo "Please run \`/usr/local/bin/brew doctor\` or follow the installation instructions at https://brew.sh/, then re-run this script."
                    return 1
                fi
                QMK_BREW="ibrew_default"
                arch -x86_64 /usr/local/bin/brew update
                arch -x86_64 /usr/local/bin/brew upgrade --formulae --ignore-pinned
                else
                    echo "You dont have x86_64 homebrew install in your mac or it's not locate at /usr/local/bin/brew. Please follow the installation instructions at https://docs.brew.sh/Installation and re-run this script"
                    return 1
            fi;;
        *)
            echo "Error! Homebrew is broken or not installed."
            echo "Please run \`brew doctor\` or follow the installation instructions at https://brew.sh/, then re-run this script."
            return 1
            ;;
    esac
}

_qmk_install() {
    echo "Installing dependencies"

    # All macOS dependencies are managed in the Homebrew package:
    # https://github.com/qmk/homebrew-qmk
    if [ "$QMK_BREW" == "default" ];then
        brew install qmk/qmk/qmk
        brew link --force avr-gcc@8
        brew link --force arm-gcc-bin@8
        else
        arch -x86_64 /usr/local/bin/brew install qmk/qmk/qmk
        arch -x86_64 /usr/local/bin/brew link --force avr-gcc@8
        arch -x86_64 /usr/local/bin/brew link --force arm-gcc-bin@8
    fi
    python3 -m pip install -r $QMK_FIRMWARE_DIR/requirements.txt
}
