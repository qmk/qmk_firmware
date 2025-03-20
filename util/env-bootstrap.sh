#!/usr/bin/env bash
# Copyright 2025 Nick Brassel (@tzarc)
# SPDX-License-Identifier: GPL-2.0-or-later
set -eu

################################################################################
# This script will install the QMK CLI, toolchains, and flashing utilities.
################################################################################
# Configurables:
#   QMK_DISTRIB_DIR: The directory to install the QMK distribution to.
#   UV_INSTALL_DIR: The directory to install `uv` to.
#   SKIP_CLEAN: Skip cleaning the distribution directory.
#   SKIP_UV: Skip installing `uv`.
#   SKIP_QMK_CLI: Skip installing the QMK CLI.
#   SKIP_QMK_TOOLCHAINS: Skip installing the QMK toolchains.
#   SKIP_QMK_FLASHUTILS: Skip installing the QMK flashing utilities.
################################################################################
# Usage:
#   curl -fsSL https://raw.githubusercontent.com/qmk/qmk_firmware/master/util/env-bootstrap.sh | sh
#
# An example which skips installing `uv`:
#   curl -fsSL https://raw.githubusercontent.com/qmk/qmk_firmware/master/util/env-bootstrap.sh | SKIP_UV=1 sh
#
# Any other configurable items listed above may be specified in the same way.
################################################################################

# Windows/MSYS doesn't like `/tmp` so we need to set a different temporary directory.
# Also set the default `UV_INSTALL_DIR` and `QMK_DISTRIB_DIR` to locations which don't pollute the user's home directory, keeping the installation internal to MSYS.
if [ "$(uname -o 2>/dev/null || true)" = "Msys" ]; then
    export TMPDIR="$(cygpath -w "$TMP")"
    export UV_INSTALL_DIR=${UV_INSTALL_DIR:-/opt/uv}
    export QMK_DISTRIB_DIR=${QMK_DISTRIB_DIR:-/opt/qmk}
fi

# Work out where we want to install the distribution
export QMK_DISTRIB_DIR=${QMK_DISTRIB_DIR:-$HOME/.local/share/qmk}
# Clear out the target directory if necessary
if [ -z "${SKIP_CLEAN:-}" ] || [ -z "${SKIP_QMK_TOOLCHAINS:-}" -a -z "${SKIP_QMK_FLASHUTILS:-}" ]; then
    if [ -d "$QMK_DISTRIB_DIR" ]; then
        echo "Removing old QMK distribution..." >&2
        rm -rf "$QMK_DISTRIB_DIR"
    fi
fi
mkdir -p "$QMK_DISTRIB_DIR"

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

install_uv() {
    # Install `uv` (or update as necessary)
    download_url https://astral.sh/uv/install.sh - | TMPDIR=${TMPDIR:-} UV_INSTALL_DIR=${UV_INSTALL_DIR:-} sh

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

[ -n "${SKIP_UV:-}" ] || install_uv
[ -n "${SKIP_QMK_CLI:-}" ] || install_qmk_cli
[ -n "${SKIP_QMK_TOOLCHAINS:-}" ] || install_toolchains
[ -n "${SKIP_QMK_FLASHUTILS:-}" ] || install_flashing_tools
clean_tarballs

# Notify the user that they may need to restart their shell to get the `qmk` command
hash -r
echo
echo "You may need to restart your shell to gain access to the 'qmk' command."
echo "Alternatively, add "$(dirname "$(command -v qmk)")" to your \$PATH:"
echo "    export PATH=\"$(dirname "$(command -v qmk)"):\$PATH\""
