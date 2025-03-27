#!/usr/bin/env bash
# Copyright 2025 Nick Brassel (@tzarc)
# SPDX-License-Identifier: GPL-2.0-or-later

{ # this ensures the entire script is downloaded #

set -eu

################################################################################
# This script will install the QMK CLI, toolchains, and flashing utilities.
################################################################################
# Environment variables:
#   YES: Assume "yes" for all prompts. (or: --yes)
#   QMK_DISTRIB_DIR: The directory to install the QMK distribution to. (or: --qmk-distrib-dir=...)
#   UV_INSTALL_DIR: The directory to install `uv` to. (or: --uv-install-dir=...)
#   SKIP_CLEAN: Skip cleaning the distribution directory. (or: --skip-clean)
#   SKIP_PACKAGE_MANAGER: Skip installing the necessary packages for the package manager. (or: --skip-package-manager)
#   SKIP_UV: Skip installing `uv`. (or: --skip-uv)
#   SKIP_QMK_CLI: Skip installing the QMK CLI. (or: --skip-qmk-cli)
#   SKIP_QMK_TOOLCHAINS: Skip installing the QMK toolchains. (or: --skip-qmk-toolchains)
#   SKIP_QMK_FLASHUTILS: Skip installing the QMK flashing utilities. (or: --skip-qmk-flashutils)
#
# Arguments above may be negated by prefixing with `--no-` instead (e.g. `--no-skip-clean`).
################################################################################
# Usage:
#   curl -fsSL https://raw.githubusercontent.com/qmk/qmk_firmware/master/util/env-bootstrap.sh | sh
#
# Help:
#   curl -fsSL https://raw.githubusercontent.com/qmk/qmk_firmware/master/util/env-bootstrap.sh | sh -s -- --help
#
# An example which skips installing `uv` using environment variables:
#   curl -fsSL https://raw.githubusercontent.com/qmk/qmk_firmware/master/util/env-bootstrap.sh | SKIP_UV=1 sh
#
# ...or by using command line arguments:
#   curl -fsSL https://raw.githubusercontent.com/qmk/qmk_firmware/master/util/env-bootstrap.sh | sh -s -- --skip-uv
#
# Any other configurable items listed above may be specified in the same way.
################################################################################

# Work out which `sed` to use
command -v gsed >/dev/null 2>&1 && SED=gsed || SED=sed

script_args() {
    cat <<__EOT__
    --help                    -- Shows this help text
    --yes                     -- Assumes "yes" for all prompts
    --uv-install-dir={path}   -- The directory to install \`uv\` into
    --qmk-distrib-dir={path}  -- The directory to install the QMK distribution into
    --skip-clean              -- Skip cleaning the QMK distribution directory
    --skip-package-manager    -- Skip installing the necessary packages for the package manager
    --skip-uv                 -- Skip installing \`uv\`
    --skip-qmk-cli            -- Skip installing the QMK CLI
    --skip-qmk-toolchains     -- Skip installing the QMK toolchains
    --skip-qmk-flashutils     -- Skip installing the QMK flashing utilities
__EOT__
}

script_help() {
    echo "$(basename ${this_script:-qmk-install.sh}) $(script_args | sort | ${SED} -e 's@^\s*@@g' -e 's@\s\+--.*@@g' -e 's@^@[@' -e 's@$@]@' | tr '\n' ' ')"
    echo
    echo "Arguments:"
    script_args
    echo
    echo "Switch arguments may be negated by prefixing with '--no-' (e.g. '--no-skip-clean')."
}

script_parse_args() {
    local N
    local V
    while [[ ! -z "${1:-}" ]]; do
        case "$1" in
        --help)
            script_help
            exit 0
            ;;
        --*=*)
            N=${1%%=*}
            N=${N##--}
            N=$(echo $N | tr '-' '_' | tr 'a-z' 'A-Z')
            V=${1##*=}
            export $N="$V"
            ;;
        --no-*)
            N=${1##--no-}
            N=$(echo $N | tr '-' '_' | tr 'a-z' 'A-Z')
            unset $N
            ;;
        --*)
            N=${1##--}
            N=$(echo $N | tr '-' '_' | tr 'a-z' 'A-Z')
            export $N=true
            ;;
        *)
            echo "Unknown argument: '$1'" >&2
            echo
            script_help >&2
            exit 1
            ;;
        esac
        shift
        unset N
        unset V
    done
}

download_url() {
    local url=$1
    local filename=${2:-$(basename "$url")}
    local quiet=''
    if [ -n "$(command -v curl 2>/dev/null || true)" ]; then
        [ $filename = "-" ] && quiet='-s' || echo "Downloading '$url' => '$filename'" >&2
        curl -LSf $quiet -o "$filename" "$url"
    elif [ -n "$(command -v wget 2>/dev/null || true)" ]; then
        [ $filename = "-" ] && quiet='-q' || echo "Downloading '$url' => '$filename'" >&2
        wget $quiet "-O$filename" "$url"
    else
        echo "Please install 'curl' or 'wget' to continue." >&2
        exit 1
    fi
}

fn_os() {
    local os_name=$(echo ${1:-} | tr 'A-Z' 'a-z')
    if [ -z "$os_name" ]; then
        os_name=$(uname -s | tr 'A-Z' 'a-z')
    fi
    case "$os_name" in
    *darwin* | *macos* | *apple*)
        echo macos
        ;;
    *windows* | *mingw* | *w64*)
        echo windows
        ;;
    *linux*)
        echo linux
        ;;
    *)
        echo unknown
        ;;
    esac
}

fn_arch() {
    local arch_name=$(echo ${1:-} | tr 'A-Z' 'a-z')
    if [ -z "$arch_name" ]; then
        arch_name=$(uname -m | tr 'A-Z' 'a-z')
    fi
    case "$arch_name" in
    *arm64* | *aarch64*)
        echo ARM64
        ;;
    *riscv64*)
        echo RV64
        ;;
    *x86_64* | *x64*)
        echo X64
        ;;
    *)
        echo unknown
        ;;
    esac
}

check_yesno() {
    [ -z "${YES:-}" ] || return 0
    read -p "Proceed? [y/N] " res </dev/tty # Read from /dev/tty as stdin may not be connected when piping to sh
    case $res in
    [Yy]*) ;;
    *)
        return 1
        ;;
    esac
}

install_package_manager_deps() {
    # Install the necessary packages for the package manager
    case $(fn_os) in
    macos)
        if [ -n "$(command -v brew 2>/dev/null || true)" ]; then
            echo "It will also install the following system packages using 'brew':" >&2
            echo "    zstd clang-format make hidapi libusb" >&2
            check_yesno || exit 1
            brew update && brew upgrade --formulae
            brew install zstd clang-format make hidapi libusb
        else
            echo "Please install 'brew' to continue. See https://brew.sh/ for more information." >&2
            exit 1
        fi
        ;;
    linux)
        case $(grep ID /etc/os-release) in
        *arch* | *manjaro*)
            echo "It will also install the following system packages using 'pacman':" >&2
            echo "    zstd base-devel clang diffutils unzip wget zip hidapi" >&2
            check_yesno || exit 1
            sudo pacman --needed --noconfirm -S zstd base-devel clang diffutils unzip wget zip
            sudo pacman --needed --noconfirm -S hidapi || true # This will fail if the community repo isn't enabled
            ;;
        *debian* | *ubuntu*)
            echo "It will also install the following system packages using 'apt':" >&2
            echo "    zstd build-essential clang-format diffutils unzip wget zip libhidapi-hidraw0" >&2
            check_yesno || exit 1
            sudo apt-get update
            DEBIAN_FRONTEND=noninteractive \
                sudo apt-get --quiet --yes install zstd build-essential clang-format diffutils unzip wget zip libhidapi-hidraw0
            ;;
        *fedora*)
            echo "It will also install the following system packages using 'dnf':" >&2
            echo "    zstd clang diffutils gcc git unzip wget zip hidapi" >&2
            echo "And whichever of the following is available, depending on which packages are provided by the distro:" >&2
            echo "    libusb-devel, libusb1-devel, libusb-compat-0.1-devel, or libusb0-devel" >&2
            check_yesno || exit 1
            sudo dnf -y install zstd clang diffutils gcc git unzip wget zip hidapi libusb-devel libusb1-devel libusb-compat-0.1-devel libusb0-devel --skip-unavailable
            ;;
        *gentoo*)
            echo "It will also the following packages using 'emerge':" >&2
            echo "    app-arch/zstd app-arch/unzip app-arch/zip net-misc/wget llvm-core/clang sys-apps/hwloc dev-libs/hidapi" >&2
            check_yesno || exit 1
            sudo emerge -au --noreplace \
                app-arch/zstd app-arch/unzip app-arch/zip net-misc/wget llvm-core/clang sys-apps/hwloc dev-libs/hidapi
            ;;
        *slackware*)
            echo "It will also the following packages using 'sboinstall':" >&2
            echo "    python3" >&2
            check_yesno || exit 1
            sudo sboinstall python3 # Rest tbd?
            ;;
        *solus*)
            echo "It will also install the following system packages using 'eopkg':" >&2
            echo "    system.devel zstd git wget zip unzip python3" >&2
            check_yesno || exit 1
            sudo eopkg -y update-repo
            sudo eopkg -y upgrade
            sudo eopkg -y install \
                -c system.devel zstd git wget zip unzip python3
            ;;
        *void*)
            echo "It will also the following packages using 'xbps-install':" >&2
            echo "    zstd git make wget unzip zip python3" >&2
            check_yesno || exit 1
            sudo xbps-install -y \
                zstd git make wget unzip zip python3
            ;;
        *)
            echo "Sorry, we don't recognize your distribution. Try using the docker image instead:"
            echo
            echo "https://docs.qmk.fm/#/getting_started_docker"
            exit 1
            ;;
        esac
        ;;
    esac
}

install_uv() {
    # Install `uv` (or update as necessary)
    download_url https://astral.sh/uv/install.sh - | TMPDIR=${TMPDIR:-} UV_INSTALL_DIR=${UV_INSTALL_DIR:-} sh
}

setup_paths() {
    # Set up the paths for any of the locations `uv` expects
    if [ -n "${XDG_BIN_HOME:-}" ]; then
        export PATH="$XDG_BIN_HOME:$PATH"
    fi
    if [ -n "${XDG_DATA_HOME:-}" ]; then
        export PATH="$XDG_DATA_HOME/../bin:$PATH"
    fi
    [ ! -d "$HOME/.local/bin" ] || export PATH="$HOME/.local/bin:$PATH"

    if [ -n "${UV_INSTALL_DIR:-}" ]; then
        export PATH="$UV_INSTALL_DIR/bin:$UV_INSTALL_DIR:$PATH" # cater for both "flat" and "hierarchical" installs of `uv`
    fi
}

install_qmk_cli() {
    # Install the QMK CLI
    uv tool install --force --with pip --upgrade --python 3.13 qmk

    # QMK is installed to...
    local qmk_tooldir="$(uv tool dir)/qmk"

    # Convert it to a unix-style path if we're on Windows/Msys2
    if [ "$(uname -o 2>/dev/null || true)" = "Msys" ]; then
        qmk_tooldir="$(cygpath -u "$qmk_tooldir")"
    fi

    # Activate the environment
    if [ -e "$qmk_tooldir/bin" ]; then
        . "$qmk_tooldir/bin/activate"
    elif [ -e "$qmk_tooldir/Scripts" ]; then
        . "$qmk_tooldir/Scripts/activate"
    else
        echo "Could not find the QMK environment to activate." >&2
        exit 1
    fi

    # Install the QMK dependencies
    uv pip install --upgrade -r https://raw.githubusercontent.com/qmk/qmk_firmware/refs/heads/master/requirements.txt
    uv pip install --upgrade -r https://raw.githubusercontent.com/qmk/qmk_firmware/refs/heads/master/requirements-dev.txt

    # Deactivate the environment
    deactivate
}

install_toolchains() {
    # Get the latest toolchain release from https://github.com/qmk/qmk_toolchains
    local latest_toolchains_release=$(download_url https://api.github.com/repos/qmk/qmk_toolchains/releases/latest - | grep -oE '"tag_name": "[^"]+' | grep -oE '[^"]+$')
    # Download the specific release asset with a matching keyword
    local toolchain_url=$(download_url https://api.github.com/repos/qmk/qmk_toolchains/releases/tags/$latest_toolchains_release - | grep -oE '"browser_download_url": "[^"]+"' | grep -oE 'https://[^"]+' | grep $(fn_os)$(fn_arch))
    if [ -z "$toolchain_url" ]; then
        echo "No toolchain found for this OS/Arch combination." >&2
        exit 1
    fi

    # Download the toolchain release to the toolchains location
    echo "Downloading compiler toolchain..." >&2
    local target_file="$QMK_DISTRIB_DIR/$(basename "$toolchain_url")"
    download_url "$toolchain_url" "$target_file"

    # Extract the toolchain
    echo "Extracting compiler toolchain..." >&2
    tar xf "$target_file" -C "$QMK_DISTRIB_DIR" --strip-components=1
}

install_flashing_tools() {
    # Get the latest flashing tools release from https://github.com/qmk/qmk_flashutils
    local latest_flashutils_release=$(download_url https://api.github.com/repos/qmk/qmk_flashutils/releases/latest - | grep -oE '"tag_name": "[^"]+' | grep -oE '[^"]+$')
    # Download the specific release asset with a matching keyword
    local flashutils_url=$(download_url https://api.github.com/repos/qmk/qmk_flashutils/releases/tags/$latest_flashutils_release - | grep -oE '"browser_download_url": "[^"]+"' | grep -oE 'https://[^"]+' | grep $(fn_os)$(fn_arch))
    if [ -z "$flashutils_url" ]; then
        echo "No flashing tools found for this OS/Arch combination." >&2
        exit 1
    fi

    # Download the flashing tools release to the toolchains location
    echo "Downloading flashing tools..." >&2
    local target_file="$QMK_DISTRIB_DIR/$(basename "$flashutils_url")"
    download_url "$flashutils_url" "$target_file"

    # Extract the flashing tools
    echo "Extracting flashing tools..." >&2
    tar xf "$target_file" -C "$QMK_DISTRIB_DIR/bin"
}

clean_tarballs() {
    # Clean up the tarballs
    rm -f "$QMK_DISTRIB_DIR"/*.tar.zst || true
}

# Windows/MSYS doesn't like `/tmp` so we need to set a different temporary directory.
# Also set the default `UV_INSTALL_DIR` and `QMK_DISTRIB_DIR` to locations which don't pollute the user's home directory, keeping the installation internal to MSYS.
if [ "$(uname -o 2>/dev/null || true)" = "Msys" ]; then
    export TMPDIR="$(cygpath -w "$TMP")"
    export UV_INSTALL_DIR=${UV_INSTALL_DIR:-/opt/uv}
    export QMK_DISTRIB_DIR=${QMK_DISTRIB_DIR:-/opt/qmk}
fi

# Work out where we want to install the distribution
export QMK_DISTRIB_DIR=${QMK_DISTRIB_DIR:-$HOME/.local/share/qmk}

script_parse_args "$@"

echo "This script will install \`uv\` to ${UV_INSTALL_DIR:-the default location}, and the QMK CLI, toolchains, and flashing utilities to ${QMK_DISTRIB_DIR}."
[ -z "${SKIP_PACKAGE_MANAGER:-}" ] || { check_yesno || exit 1; }
[ -n "${SKIP_PACKAGE_MANAGER:-}" ] || install_package_manager_deps
[ -n "${SKIP_UV:-}" ] || install_uv
setup_paths
[ -n "${SKIP_QMK_CLI:-}" ] || install_qmk_cli

# Clear out the distrib directory if necessary
if [ -z "${SKIP_CLEAN:-}" ] || [ -z "${SKIP_QMK_TOOLCHAINS:-}" -a -z "${SKIP_QMK_FLASHUTILS:-}" ]; then
    if [ -d "$QMK_DISTRIB_DIR" ]; then
        echo "Removing old QMK distribution..." >&2
        rm -rf "$QMK_DISTRIB_DIR"
    fi
fi
mkdir -p "$QMK_DISTRIB_DIR"

[ -n "${SKIP_QMK_TOOLCHAINS:-}" ] || install_toolchains
[ -n "${SKIP_QMK_FLASHUTILS:-}" ] || install_flashing_tools
clean_tarballs

# Notify the user that they may need to restart their shell to get the `qmk` command
hash -r
echo
echo "You may need to restart your shell to gain access to the 'qmk' command."
echo "Alternatively, add "$(dirname "$(command -v qmk)")" to your \$PATH:"
echo "    export PATH=\"$(dirname "$(command -v qmk)"):\$PATH\""

} # this ensures the entire script is downloaded #
