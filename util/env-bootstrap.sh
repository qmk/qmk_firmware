#!/usr/bin/env sh
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
#   SKIP_UDEV_RULES: Skip installing the udev rules for Linux. (or: --skip-udev-rules)
#   SKIP_WINDOWS_DRIVERS: Skip installing the Windows drivers for the flashing utilities. (or: --skip-windows-drivers)
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

    BOOTSTRAP_TMPDIR="$(mktemp -d /tmp/qmk-bootstrap-failure.XXXXXX)"
    trap 'rm -rf "$BOOTSTRAP_TMPDIR" >/dev/null 2>&1 || true' EXIT
    FAILURE_FILE="${BOOTSTRAP_TMPDIR}/fail"

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
    --skip-udev-rules         -- Skip installing the udev rules for Linux
    --skip-windows-drivers    -- Skip installing the Windows drivers for the flashing utilities
__EOT__
    # Hidden:
    # --wsl-install           -- Installs the WSL variant of qmk_flashutils
    }

    signal_execution_failure() {
        touch "$FAILURE_FILE" >/dev/null 2>&1 || true
    }

    exit_if_execution_failed() {
        if [ -e "$FAILURE_FILE" ]; then
            exit 1
        fi
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
        elif [ $(id -u) -ne 0 ]; then
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
        local quiet=''
        if [ -n "$(command -v curl 2>/dev/null || true)" ]; then
            [ "$filename" = "-" ] && quiet='-s' || echo "Downloading '$url' => '$filename'" >&2
            curl -LSf $quiet -o "$filename" "$url"
        elif [ -n "$(command -v wget 2>/dev/null || true)" ]; then
            [ "$filename" = "-" ] && quiet='-q' || echo "Downloading '$url' => '$filename'" >&2
            wget $quiet "-O$filename" "$url"
        else
            echo "Please install 'curl' to continue." >&2
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

    fn_os() {
        local os_name=$(echo ${1:-} | tr 'A-Z' 'a-z')
        if [ -z "$os_name" ]; then
            os_name=$(uname -s | tr 'A-Z' 'a-z')
        fi
        case "$os_name" in
        *darwin* | *macos* | *apple*)
            echo macos
            ;;
        *windows* | *mingw* | *msys*)
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
        windows) echo "base-devel: zstd:p toolchain:p clang:p hidapi:p dos2unix: git: unzip:" ;;
        linux)
            case $(grep ID /etc/os-release) in
            *arch* | *manjaro* | *cachyos*) echo "zstd base-devel clang diffutils wget unzip zip hidapi dos2unix git" ;;
            *debian* | *ubuntu*) echo "zstd build-essential clang-format diffutils wget unzip zip libhidapi-hidraw0 dos2unix git" ;;
            *fedora*) echo "zstd clang diffutils which gcc git wget unzip zip hidapi dos2unix libusb-devel libusb1-devel libusb-compat-0.1-devel libusb0-devel git epel-release" ;;
            *suse*) echo "zstd clang diffutils wget unzip zip libhidapi-hidraw0 dos2unix git libusb-1_0-devel gzip which" ;;
            *gentoo*) echo "zstd sys-apps/diffutils wget unzip zip dev-libs/hidapi dos2unix dev-vcs/git dev-libs/libusb app-arch/gzip which" ;;
            *)
                echo >&2
                echo "Sorry, we don't recognize your distribution." >&2
                echo >&2
                echo "Proceeding with the installation, however you will need to install at least the following tools manually:" >&2
                echo "  - make, git, curl, zstd, unzip, [lib]hidapi" >&2
                echo "Other tools may be required depending on your distribution." >&2
                echo >&2
                echo "Alternatively, if you prefer Docker, try using the docker image instead:" >&2
                echo "  - https://docs.qmk.fm/#/getting_started_docker" >&2
                ;;
            esac
            ;;
        *)
            # We can only really support macOS, Windows, and Linux at this time due to `uv` requirements.
            echo >&2
            echo "Sorry, we don't recognize your OS. Try using a compatible OS instead:" >&2
            echo "  - https://docs.qmk.fm/newbs_getting_started#set-up-your-environment" >&2
            echo >&2
            echo "If you cannot use a compatible OS, you can try installing the \`qmk\` Python package manually using \`pip\`, most likely requiring a virtual environment:" >&2
            echo "  % python3 -m pip install qmk" >&2
            echo >&2
            echo "All other dependencies will need to be installed manually, such as make, git, AVR and ARM toolchains, and associated flashing utilities." >&2
            echo >&2
            echo "**NOTE**: QMK does not provide official support for your environment. Here be dragons, you are on your own." >&2
            signal_execution_failure
            ;;
        esac
    }

    print_package_manager_deps_and_delay() {
        get_package_manager_deps | tr ' ' '\n' | sort | xargs -I'{}' echo "    - {}" >&2
        exit_if_execution_failed
        preinstall_delay || exit 1
    }

    install_package_manager_deps() {
        # Install the necessary packages for the package manager
        case $(fn_os) in
        macos)
            if [ -n "$(command -v brew 2>/dev/null || true)" ]; then
                echo "It will also install the following system packages using 'brew':" >&2
                print_package_manager_deps_and_delay

                brew update

                local existing=""
                local new=""
                for dep in $(get_package_manager_deps); do
                if brew list --formula | grep -q "^${dep}\$"; then
                    existing="${existing:-} $dep"
                else
                    new="${new:-} $dep"
                fi
                done

                if [ -n "${existing:-}" ]; then
                    brew upgrade $existing
                fi
                if [ -n "${new:-}" ]; then
                    brew install $new
                fi
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
            *arch* | *manjaro* | *cachyos*)
                echo "It will also install the following system packages using 'pacman':" >&2
                print_package_manager_deps_and_delay
                $(nsudo) pacman --needed --noconfirm -S $(get_package_manager_deps)
                ;;
            *debian* | *ubuntu*)
                echo "It will also install the following system packages using 'apt':" >&2
                print_package_manager_deps_and_delay
                $(nsudo) apt-get update
                DEBIAN_FRONTEND=noninteractive \
                    $(nsudo) apt-get --quiet --yes install $(get_package_manager_deps)
                ;;
            *fedora*)
                echo "It will also install the following system packages using 'dnf':" >&2
                print_package_manager_deps_and_delay
                # Some RHEL-likes need EPEL for hidapi
                $(nsudo) dnf -y install epel-release 2>/dev/null || true
                # RHEL-likes have some naming differences in libusb packages, so manually handle those
                $(nsudo) dnf -y install $(get_package_manager_deps | tr ' ' '\n' | grep -v 'epel-release' | grep -v libusb | tr '\n' ' ')
                for pkg in $(get_package_manager_deps | tr ' ' '\n' | grep libusb); do
                    $(nsudo) dnf -y install "$pkg" 2>/dev/null || true
                done
                ;;
            *opensuse* | *suse*)
                echo "It will also install development tools as well as the following system packages using 'zypper':" >&2
                print_package_manager_deps_and_delay
                $(nsudo) zypper --non-interactive refresh
                $(nsudo) zypper --non-interactive install -t pattern devel_basis devel_C_C++
                $(nsudo) zypper --non-interactive install $(get_package_manager_deps)
                ;;
            *gentoo*)
                echo "It will also install the following system packages using 'emerge':" >&2
                print_package_manager_deps_and_delay
                $(nsudo) emerge --sync
                $(nsudo) emerge --noreplace --ask=n $(get_package_manager_deps | tr ' ' '\n') || signal_execution_failure
                exit_if_execution_failed
                ;;
            *)
                print_package_manager_deps_and_delay
                echo "Proceeding with the installation, you will need to ensure prerequisites are installed." >&2
                ;;
            esac
            ;;
        *)
            print_package_manager_deps_and_delay
            ;;
        esac
    }

    install_uv() {
        # Install `uv` (or update as necessary)
        download_url https://astral.sh/uv/install.sh - | TMPDIR="$(windows_ish_path "${TMPDIR:-}")" UV_INSTALL_DIR="$(windows_ish_path "${UV_INSTALL_DIR:-}")" sh
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

        if [ -n "${UV_TOOL_BIN_DIR:-}" ]; then
            export PATH="$UV_TOOL_BIN_DIR:$PATH"
        fi
    }

    uv_command() {
        if [ "$(fn_os)" = "windows" ]; then
            UV_TOOL_DIR="$(windows_ish_path "${UV_TOOL_DIR:-}")" \
            UV_TOOL_BIN_DIR="$(windows_ish_path "${UV_TOOL_BIN_DIR:-}")" \
            uv "$@"
        else
            uv "$@"
        fi
    }

    install_qmk_cli() {
        # Install the QMK CLI
        uv_command tool install --force --with pip --upgrade --python $PYTHON_TARGET_VERSION qmk

        # QMK is installed to...
        local qmk_tooldir="$(posix_ish_path "$(uv_command tool dir)/qmk")"

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
        uv_command pip install --upgrade -r https://raw.githubusercontent.com/qmk/qmk_firmware/refs/heads/master/requirements.txt
        uv_command pip install --upgrade -r https://raw.githubusercontent.com/qmk/qmk_firmware/refs/heads/master/requirements-dev.txt

        # Deactivate the environment
        deactivate
    }

    install_toolchains() {
        # Get the latest toolchain release from https://github.com/qmk/qmk_toolchains
        local latest_toolchains_release=$(github_api_call repos/qmk/qmk_toolchains/releases/latest - | grep -oE '"tag_name": "[^"]+' | grep -oE '[^"]+$')
        # Download the specific release asset with a matching keyword
        local toolchain_url=$(github_api_call repos/qmk/qmk_toolchains/releases/tags/$latest_toolchains_release - | grep -oE '"browser_download_url": "[^"]+"' | grep -oE 'https://[^"]+' | grep $(fn_os)$(fn_arch))
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
        zstdcat "$target_file" | tar xf - -C "$QMK_DISTRIB_DIR" --strip-components=1
    }

    install_flashing_tools() {
        local osarchvariant="$(fn_os)$(fn_arch)"

        # Special case for WSL
        if [ -n "${WSL_INSTALL:-}" ] ||  [ -n "${WSL_DISTRO_NAME:-}" ] || [ -f /proc/sys/fs/binfmt_misc/WSLInterop ]; then
            osarchvariant="windowsWSL"
        fi

        # Get the latest flashing tools release from https://github.com/qmk/qmk_flashutils
        local latest_flashutils_release=$(github_api_call repos/qmk/qmk_flashutils/releases/latest - | grep -oE '"tag_name": "[^"]+' | grep -oE '[^"]+$')
        # Download the specific release asset with a matching keyword
        local flashutils_url=$(github_api_call repos/qmk/qmk_flashutils/releases/tags/$latest_flashutils_release - | grep -oE '"browser_download_url": "[^"]+"' | grep -oE 'https://[^"]+' | grep "$osarchvariant")
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
        zstdcat "$target_file" | tar xf - -C "$QMK_DISTRIB_DIR/bin"
        # Move the release file to etc
        mv "$QMK_DISTRIB_DIR/bin/flashutils_release"* "$QMK_DISTRIB_DIR/etc"
    }

    install_linux_udev_rules() {
        # Download the udev rules to the toolchains location
        echo "Downloading QMK udev rules file..." >&2
        local qmk_rules_target_file="$QMK_DISTRIB_DIR/50-qmk.rules"
        download_url "https://raw.githubusercontent.com/qmk/qmk_firmware/refs/heads/master/util/udev/50-qmk.rules" "$qmk_rules_target_file"

        # Install the udev rules -- path list is aligned with qmk doctor's linux.py
        local udev_rules_paths="
            /usr/lib/udev/rules.d
            /usr/local/lib/udev/rules.d
            /run/udev/rules.d
            /etc/udev/rules.d
        "
        for udev_rules_dir in $udev_rules_paths; do
            if [ -d "$udev_rules_dir" ]; then
                echo "Installing udev rules to $udev_rules_dir/50-qmk.rules ..." >&2
                $(nsudo) mv "$qmk_rules_target_file" "$udev_rules_dir"
                $(nsudo) chown 0:0 "$udev_rules_dir/50-qmk.rules"
                $(nsudo) chmod 644 "$udev_rules_dir/50-qmk.rules"
                break
            fi
        done

        # Reload udev rules
        if command -v udevadm >/dev/null 2>&1; then
            echo "Reloading udev rules..." >&2
            $(nsudo) udevadm control --reload-rules || true
            $(nsudo) udevadm trigger || true
        else
            echo "udevadm not found, skipping udev rules reload." >&2
        fi
    }

    install_windows_drivers() {
        # Get the latest driver installer release from https://github.com/qmk/qmk_driver_installer
        local latest_driver_installer_release=$(github_api_call repos/qmk/qmk_driver_installer/releases/latest - | grep -oE '"tag_name": "[^"]+' | grep -oE '[^"]+$')
        # Download the specific release asset
        local driver_installer_url=$(github_api_call repos/qmk/qmk_driver_installer/releases/tags/$latest_driver_installer_release - | grep -oE '"browser_download_url": "[^"]+"' | grep -oE 'https://[^"]+' | grep '\.exe')
        if [ -z "$driver_installer_url" ]; then
            echo "No driver installer found." >&2
            exit 1
        fi
        # Download the driver installer release to the toolchains location
        echo "Downloading driver installer..." >&2
        local target_file="$QMK_DISTRIB_DIR/$(basename "$driver_installer_url")"
        download_url "$driver_installer_url" "$target_file"
        # Download the drivers list
        download_url "https://raw.githubusercontent.com/qmk/qmk_firmware/refs/heads/master/util/drivers.txt" "$QMK_DISTRIB_DIR/drivers.txt"
        # Execute the driver installer
        cd "$QMK_DISTRIB_DIR"
        cmd.exe //c "qmk_driver_installer.exe --all --force drivers.txt"
        cd -
        # Remove the temporary files
        rm -f "$QMK_DISTRIB_DIR/qmk_driver_installer.exe" "$QMK_DISTRIB_DIR/drivers.txt" || true
    }

    clean_tarballs() {
        # Clean up the tarballs
        rm -f "$QMK_DISTRIB_DIR"/*.tar.zst || true
    }

    windows_ish_path() {
        [ -n "$1" ] || return 0
        [ "$(uname -o 2>/dev/null || true)" = "Msys" ] && cygpath -w "$1" || echo "$1"
    }

    posix_ish_path() {
        [ -n "$1" ] || return 0
        [ "$(uname -o 2>/dev/null || true)" = "Msys" ] && cygpath -u "$1" || echo "$1"
    }

    # Set the Python version we want to use with the QMK CLI
    export PYTHON_TARGET_VERSION=${PYTHON_TARGET_VERSION:-3.14}

    # Windows/MSYS doesn't like `/tmp` so we need to set a different temporary directory.
    # Also set the default `UV_INSTALL_DIR` and `QMK_DISTRIB_DIR` to locations which don't pollute the user's home directory, keeping the installation internal to MSYS.
    if [ "$(uname -o 2>/dev/null || true)" = "Msys" ]; then
        export TMPDIR="$(posix_ish_path "$TMP")"
        export UV_INSTALL_DIR="$(posix_ish_path "${UV_INSTALL_DIR:-/opt/uv}")"
        export QMK_DISTRIB_DIR="$(posix_ish_path "${QMK_DISTRIB_DIR:-/opt/qmk}")"
        export UV_TOOL_DIR="$(posix_ish_path "${UV_TOOL_DIR:-"$UV_INSTALL_DIR/tools"}")"
        export UV_TOOL_BIN_DIR="$(posix_ish_path "$UV_TOOL_DIR/bin")"
    fi

    script_parse_args "$@"

    echo "This QMK CLI installation script will install \`uv\`, the QMK CLI, as well as QMK-supplied toolchains and flashing utilities." >&2
    [ -z "${SKIP_PACKAGE_MANAGER:-}" ] || { preinstall_delay || exit 1; }
    [ -n "${SKIP_PACKAGE_MANAGER:-}" ] || install_package_manager_deps
    [ -n "${SKIP_UV:-}" ] || install_uv

    # Make sure the usual `uv` and other associated directories are on the $PATH
    setup_paths

    # Work out where we want to install the distribution and tools now that `uv` is installed
    export QMK_DISTRIB_DIR="$(posix_ish_path "${QMK_DISTRIB_DIR:-$(printf 'import platformdirs\nprint(platformdirs.user_data_dir("qmk"))' | uv_command run --quiet --python $PYTHON_TARGET_VERSION --with platformdirs -)}")"

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
    if [ "$(uname -s 2>/dev/null || true)" = "Linux" ]; then
        [ -n "${SKIP_UDEV_RULES:-}" ] || install_linux_udev_rules
    fi
    if [ "$(uname -o 2>/dev/null || true)" = "Msys" ]; then
        [ -n "${SKIP_WINDOWS_DRIVERS:-}" ] || install_windows_drivers
    fi
    clean_tarballs

    # Notify the user that they may need to restart their shell to get the `qmk` command
    echo >&2
    echo "QMK CLI installation complete." >&2
    echo "The QMK CLI has been installed to '$(posix_ish_path "$(dirname "$(command -v qmk)")")'." >&2
    echo "The QMK CLI venv has been created at '$(posix_ish_path "$(uv_command tool dir)/qmk")'." >&2
    echo "Toolchains and flashing utilities have been installed to '$QMK_DISTRIB_DIR'." >&2
    echo >&2
    echo "You may need to restart your shell to gain access to the 'qmk' command." >&2
    echo "Alternatively, add "$(posix_ish_path "$(dirname "$(command -v qmk)")")" to your \$PATH:" >&2
    echo "    export PATH=\"$(posix_ish_path "$(dirname "$(command -v qmk)")"):\$PATH\"" >&2

} # this ensures the entire script is downloaded #
