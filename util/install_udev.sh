#!/usr/bin/env sh
# Copyright 2025 Nick Brassel (@tzarc)
# SPDX-License-Identifier: GPL-2.0-or-later

################################################################################
# Installs the latest QMK udev rules and qmk_id helper from
# https://github.com/qmk/qmk_udev
################################################################################

set -e

nsudo() {
    if [ "$(id -u)" -ne 0 ]; then
        if [ -n "$(command -v sudo 2>/dev/null || true)" ]; then
            echo "sudo"
        elif [ -n "$(command -v doas 2>/dev/null || true)" ]; then
            echo "doas"
        else
            echo "Please install 'sudo' or 'doas' to continue." >&2
            exit 1
        fi
    fi
    true
}

download_url() {
    local url=$1
    local filename=${2:-$(basename "$url")}
    if [ -n "$(command -v curl 2>/dev/null || true)" ]; then
        curl -LSf -o "$filename" "$url"
    elif [ -n "$(command -v wget 2>/dev/null || true)" ]; then
        wget "-O$filename" "$url"
    else
        echo "Please install 'curl' or 'wget' to continue." >&2
        exit 1
    fi
}

github_api_call() {
    local url="$1"
    local token="${GITHUB_TOKEN:-${GH_TOKEN:-}}"
    if [ -n "${token:-}" ]; then
        if [ -n "$(command -v curl 2>/dev/null || true)" ]; then
            curl -fsSL -H "Authorization: token $token" -H "Accept: application/vnd.github.v3+json" "https://api.github.com/$url"
        elif [ -n "$(command -v wget 2>/dev/null || true)" ]; then
            wget -q --header="Authorization: token $token" --header="Accept: application/vnd.github.v3+json" "https://api.github.com/$url" -O -
        fi
    else
        download_url "https://api.github.com/$url" -
    fi
}

fn_arch() {
    local arch_name=$(uname -m | tr 'A-Z' 'a-z')
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
        echo "Unsupported architecture: $arch_name" >&2
        exit 1
        ;;
    esac
}

if [ "$(uname -s 2>/dev/null || true)" != "Linux" ]; then
    echo "This script is only intended for Linux." >&2
    exit 1
fi

# Create a temporary directory for downloads
tmpdir=$(mktemp -d)
trap 'rm -rf "$tmpdir"' EXIT

# Get the latest qmk_udev release
echo "Fetching latest qmk_udev release..." >&2
latest_release=$(github_api_call repos/qmk/qmk_udev/releases/latest | grep -oE '"tag_name": "[^"]+' | grep -oE '[^"]+$')
if [ -z "$latest_release" ]; then
    echo "Could not determine latest qmk_udev release." >&2
    exit 1
fi
echo "Using qmk_udev release: $latest_release" >&2

release_base="https://github.com/qmk/qmk_udev/releases/download/$latest_release"

# Download the udev rules file and architecture-appropriate qmk_id binary
download_url "$release_base/50-qmk.rules" "$tmpdir/50-qmk.rules"
download_url "$release_base/qmk_id-linux$(fn_arch)" "$tmpdir/qmk_id"

# Remove existing QMK udev rules and qmk_id helpers from all standard locations
echo "Removing existing QMK udev rules and helpers..." >&2
for dir in /etc/udev/rules.d /run/udev/rules.d /usr/lib/udev/rules.d /usr/local/lib/udev/rules.d /lib/udev/rules.d; do
    if [ -d "$dir" ]; then
        for f in "$dir"/*-qmk.rules; do
            [ -e "$f" ] && echo "Removing $f" >&2 && $(nsudo) rm -f "$f"
        done
    fi
done
for dir in /usr/lib/udev /usr/local/lib/udev /lib/udev; do
    [ -e "$dir/qmk_id" ] && echo "Removing $dir/qmk_id" >&2 && $(nsudo) rm -f "$dir/qmk_id"
done

# Install qmk_id binary and udev rules
echo "Installing /usr/lib/udev/qmk_id ..." >&2
$(nsudo) install -d -m 0755 /usr/lib/udev
$(nsudo) install -m 0755 "$tmpdir/qmk_id" /usr/lib/udev/qmk_id
echo "Installing /etc/udev/rules.d/50-qmk.rules ..." >&2
$(nsudo) install -d -m 0755 /etc/udev/rules.d
$(nsudo) install -m 0644 "$tmpdir/50-qmk.rules" /etc/udev/rules.d/50-qmk.rules

# Reload udev rules
if command -v udevadm >/dev/null 2>&1; then
    echo "Reloading udev rules..." >&2
    $(nsudo) udevadm control --reload-rules || true
    $(nsudo) udevadm trigger || true
else
    echo "udevadm not found, skipping udev rules reload." >&2
fi

echo "Done." >&2
