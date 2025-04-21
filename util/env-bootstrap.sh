#!/usr/bin/env bash
# Copyright 2025 Nick Brassel (@tzarc)
# SPDX-License-Identifier: GPL-2.0-or-later

################################################################################
# This script will install the QMK CLI, toolchains, and flashing utilities.
################################################################################
# Environment variables:
#   CONFIRM: Skip the pre-install delay. (or: --confirm)
#   QMK_DISTRIB_DIR: The directory to install the QMK distribution to. (or: --qmk-distrib-dir=...)
#   UV_INSTALL_DIR: The directory to install `uv` to. (or: --uv-install-dir=...)
#   UV_TOOL_DIR: The directory to install `uv` tools to. (or: --uv-tool-dir=...)
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

{ # this ensures the entire script is downloaded #
    set -eu

    # Work out which `sed` to use
    command -v gsed >/dev/null 2>&1 && SED=gsed || SED=sed

    script_args() {
        cat <<__EOT__
    --help                    -- Shows this help text
    --confirm                 -- Skips the delay before installation
    --uv-install-dir={path}   -- The directory to install \`uv\` into
    --uv-tool-dir={path}      -- The directory to install \`uv\` tools into
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
        while [ ! -z "${1:-}" ]; do
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

    nsudo() {
        if [ "$(fn_os)" = "windows" ]; then
            # No need for sudo under QMK MSYS
            return
        elif [ ${EUID:-} -ne 0 ]; then
            echo "sudo"
        fi
        true
    }

    download_url() {
        local url=$1
        local filename=${2:-$(basename "$url")}
        local quiet=''
        if [ -n "$(command -v curl 2>/dev/null || true)" ]; then
            [ "$filename" = "-" ] && quiet='-s' || echo "Downloading '$url' => '$filename'" >&2
            curl -LSf $quiet -o "$filename" "$url"
        elif [ -n "$(command -v wget 2>/dev/null || true)" ]; then
            [ "$filename" = "-" ] && quiet='-q' || echo "Downloading '$url' => '$filename'" >&2
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

    preinstall_delay() {
        [ -z "${CONFIRM:-}" ] || return 0
        echo >&2
        echo "Waiting 10 seconds before proceeding. Press Ctrl+C to cancel installation." >&2
        sleep 10
    }

    get_package_manager_deps() {
        case $(fn_os) in
        macos) echo "zstd clang-format make hidapi libusb dos2unix git" ;;
        windows) echo "base-devel: zstd:x toolchain:x clang:x hidapi:x dos2unix: git:" ;;
        linux)
            case $(grep ID /etc/os-release) in
            *arch* | *manjaro*) echo "zstd base-devel clang diffutils unzip wget zip hidapi dos2unix git" ;;
            *debian* | *ubuntu*) echo "zstd build-essential clang-format diffutils unzip wget zip libhidapi-hidraw0 dos2unix git" ;;
            *fedora*) echo "zstd clang diffutils gcc git unzip wget zip hidapi dos2unix libusb-devel libusb1-devel libusb-compat-0.1-devel libusb0-devel git" ;;
            *gentoo*) echo "app-arch/zstd app-arch/unzip app-arch/zip net-misc/wget llvm-core/clang sys-apps/hwloc dev-libs/hidapi app-text/dos2unix dev-vcs/git" ;;
            *slackware*) echo "python3" ;;
            *solus*) echo "system.devel zstd git wget zip unzip python3 dos2unix git" ;;
            *void*) echo "zstd git make wget unzip zip python3 dos2unix git" ;;
            *)
                echo "Sorry, we don't recognize your distribution. Try using the docker image instead:" >&2
                echo >&2
                echo "https://docs.qmk.fm/#/getting_started_docker" >&2
                exit 1
                ;;
            esac
            ;;
        *)
            echo "Sorry, we don't recognize your OS. Try using a compatible OS instead:" >&2
            echo >&2
            echo "https://docs.qmk.fm/newbs_getting_started#set-up-your-environment" >&2
            exit 1
            ;;
        esac
    }

    print_package_manager_deps_and_delay() {
        get_package_manager_deps | tr ' ' '\n' | sort | xargs -I'{}' echo "    - {}" >&2
        preinstall_delay || exit 1
    }

    install_package_manager_deps() {
        # Install the necessary packages for the package manager
        case $(fn_os) in
        macos)
            if [ -n "$(command -v brew 2>/dev/null || true)" ]; then
                echo "It will also install the following system packages using 'brew':" >&2
                print_package_manager_deps_and_delay
                brew update && brew upgrade --formulae
                brew install $(get_package_manager_deps)
            else
                echo "Please install 'brew' to continue. See https://brew.sh/ for more information." >&2
                exit 1
            fi
            ;;
        windows)
            echo "It will also install the following packages using 'pacman'/'pacboy':" >&2
            print_package_manager_deps_and_delay
            $(nsudo) pacman --needed --noconfirm --disable-download-timeout -S pactoys
            $(nsudo) pacboy sync --needed --noconfirm --disable-download-timeout $(get_package_manager_deps)
            ;;
        linux)
            case $(grep ID /etc/os-release) in
            *arch* | *manjaro*)
                echo "It will also install the following system packages using 'pacman':" >&2
                print_package_manager_deps_and_delay
                $(nsudo) pacman --needed --noconfirm -S $(get_package_manager_deps)
                ;;
            *debian* | *ubuntu*)
                echo "It will also install the following system packages using 'apt':" >&2
                print_package_manager_deps_and_delay
                $(nsudo) apt-get update
                DEBIAN_FRONTEND=noninteractive \
                    $(nsudo) apt-get --quiet --yes $(get_package_manager_deps)
                ;;
            *fedora*)
                echo "It will also install the following system packages using 'dnf':" >&2
                print_package_manager_deps_and_delay
                $(nsudo) dnf -y install $(get_package_manager_deps) --skip-unavailable
                ;;
            *gentoo*)
                echo "It will also the following packages using 'emerge':" >&2
                print_package_manager_deps_and_delay
                $(nsudo) emerge -au --noreplace $(get_package_manager_deps)
                ;;
            *slackware*)
                echo "It will also the following packages using 'sboinstall':" >&2
                print_package_manager_deps_and_delay
                $(nsudo) sboinstall $(get_package_manager_deps)
                ;;
            *solus*)
                echo "It will also install the following system packages using 'eopkg':" >&2
                print_package_manager_deps_and_delay
                $(nsudo) eopkg -y update-repo
                $(nsudo) eopkg -y upgrade
                $(nsudo) eopkg -y install $(get_package_manager_deps)
                ;;
            *void*)
                echo "It will also the following packages using 'xbps-install':" >&2
                print_package_manager_deps_and_delay
                $(nsudo) xbps-install -y $(get_package_manager_deps)
                ;;
            *)
                echo "Sorry, we don't recognize your distribution. Try using the docker image instead:" >&2
                echo >&2
                echo "https://docs.qmk.fm/#/getting_started_docker" >&2
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
        uv tool install --force --with pip --upgrade --python $PYTHON_TARGET_VERSION qmk

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
        echo "Downloading compiler toolchains..." >&2
        local target_file="$QMK_DISTRIB_DIR/$(basename "$toolchain_url")"
        download_url "$toolchain_url" "$target_file"

        # Extract the toolchain
        echo "Extracting compiler toolchains to '$QMK_DISTRIB_DIR'..." >&2
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
        echo "Extracting flashing tools to '$QMK_DISTRIB_DIR'..." >&2
        tar xf "$target_file" -C "$QMK_DISTRIB_DIR/bin"
    }

    clean_tarballs() {
        # Clean up the tarballs
        rm -f "$QMK_DISTRIB_DIR"/*.tar.zst || true
    }

    # Set the Python version we want to use with the QMK CLI
    export PYTHON_TARGET_VERSION=3.13

    # Windows/MSYS doesn't like `/tmp` so we need to set a different temporary directory.
    # Also set the default `UV_INSTALL_DIR` and `QMK_DISTRIB_DIR` to locations which don't pollute the user's home directory, keeping the installation internal to MSYS.
    if [ "$(uname -o 2>/dev/null || true)" = "Msys" ]; then
        export TMPDIR="$(cygpath -w "$TMP")"
        export UV_INSTALL_DIR=${UV_INSTALL_DIR:-/opt/uv}
        export QMK_DISTRIB_DIR=${QMK_DISTRIB_DIR:-/opt/qmk}
        export UV_TOOL_DIR=${UV_TOOL_DIR:-"$QMK_DISTRIB_DIR/tools"}
    fi

    script_parse_args "$@"

    echo "This QMK CLI installation script will install \`uv\`, the QMK CLI, as well as QMK-supplied toolchains and flashing utilities." >&2
    [ -z "${SKIP_PACKAGE_MANAGER:-}" ] || { preinstall_delay || exit 1; }
    [ -n "${SKIP_PACKAGE_MANAGER:-}" ] || install_package_manager_deps
    [ -n "${SKIP_UV:-}" ] || install_uv

    # Work out where we want to install the distribution and tools now that `uv` is installed
    export QMK_DISTRIB_DIR=${QMK_DISTRIB_DIR:-$(printf 'import platformdirs\nprint(platformdirs.user_data_dir("qmk"))' | uv run --quiet --python $PYTHON_TARGET_VERSION --with platformdirs -)}

    # Make sure the usual `uv` and other associated directories are on the $PATH
    setup_paths

    # Clear out the distrib directory if necessary
    if [ -z "${SKIP_CLEAN:-}" ] || [ -z "${SKIP_QMK_TOOLCHAINS:-}" -a -z "${SKIP_QMK_FLASHUTILS:-}" ]; then
        if [ -d "$QMK_DISTRIB_DIR" ]; then
            echo "Removing old QMK distribution..." >&2
            rm -rf "$QMK_DISTRIB_DIR"
        fi
    fi
    mkdir -p "$QMK_DISTRIB_DIR"

    [ -n "${SKIP_QMK_CLI:-}" ] || install_qmk_cli
    [ -n "${SKIP_QMK_TOOLCHAINS:-}" ] || install_toolchains
    [ -n "${SKIP_QMK_FLASHUTILS:-}" ] || install_flashing_tools
    clean_tarballs

    # Notify the user that they may need to restart their shell to get the `qmk` command
    hash -r
    echo >&2
    echo "QMK CLI installation complete." >&2
    echo "The QMK CLI has been installed to '$(dirname "$(command -v qmk)")'." >&2
    echo "The QMK CLI venv has been created at '$(uv tool dir)/qmk'." >&2
    echo "Toolchains and flashing utilities have been installed to '$QMK_DISTRIB_DIR'." >&2
    echo >&2
    echo "You may need to restart your shell to gain access to the 'qmk' command." >&2
    echo "Alternatively, add "$(dirname "$(command -v qmk)")" to your \$PATH:" >&2
    echo "    export PATH=\"$(dirname "$(command -v qmk)"):\$PATH\"" >&2

} # this ensures the entire script is downloaded #
