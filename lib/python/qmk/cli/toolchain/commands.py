"""This script sets up the QMK-provided toolchains.
"""
import platform
import shutil
import subprocess
import os
from milc import cli
from pathlib import Path

from qmk.constants import QMK_TOOLCHAINS_PATH, QMK_TOOLCHAINS_TAG
from qmk.util import download_with_progress, cached_get


def _os_prefix():
    os = platform.system().lower()
    if "linux" in os:
        return "linux"
    elif "darwin" in os or "mac" in os or "macos" in os or "osx" in os or "macosx" in os:
        return "macos"
    elif "windows" in os or "cygwin" in os or "msys" in os or "win32" in os or "win64" in os or "nt" in os:
        return "windows"
    return "unknown"


def _arch_suffix():
    arch = platform.machine().lower()
    if "amd64" in arch or "x86_64" in arch or "x64" in arch or "x86-64" in arch:
        return "X64"
    elif "arm64" in arch or "aarch64" in arch:
        return "ARM64"
    return "unknown"


def _os_arch():
    return f'{_os_prefix()}{_arch_suffix()}'


def _gcc_version_str(gcc_exe):
    lines = cli.run([gcc_exe, '-v'], check=True, capture_output=True, combined_output=True, stdin=subprocess.DEVNULL).stdout.strip().splitlines()
    return list(filter(lambda x: x.startswith('gcc version'), lines))[0].strip()


@cli.argument('-t', '--tag', default=QMK_TOOLCHAINS_TAG, help=f'The tag of the QMK-provided toolchains to download. Defaults to `{QMK_TOOLCHAINS_TAG}`.')
@cli.subcommand('Set up the QMK-provided toolchains.', hidden=False if cli.config.user.developer else True)
def toolchain_setup(cli):
    """Set up the QMK-provided toolchains.
    """

    # Remove the toolchains directory if it exists already
    if QMK_TOOLCHAINS_PATH.exists():
        cli.log.info(f'Removing existing toolchains at `{QMK_TOOLCHAINS_PATH}`...')
        shutil.rmtree(QMK_TOOLCHAINS_PATH)

    url = f'https://api.github.com/repos/qmk/qmk_toolchains/releases/tags/{cli.args.tag}'
    payload = cached_get(url)
    if payload.status_code != 200:
        cli.log.error(f'Failed to fetch toolchain metadata from `{url}`.')
        return
    downloadables = filter(lambda x: _os_arch() in x['name'], payload.json()['assets'])
    for downloadable in downloadables:
        if not Path(downloadable["name"]).exists():
            download_with_progress(downloadable['browser_download_url'], downloadable["name"])
        cli.log.info(f'Extracting `{downloadable["name"]}` to `{QMK_TOOLCHAINS_PATH}`...')
        QMK_TOOLCHAINS_PATH.mkdir(parents=True, exist_ok=True)
        cli.run(['tar', 'xf', downloadable["name"], '-C', QMK_TOOLCHAINS_PATH, '--strip-components=1'], capture_output=False, check=True, stdin=subprocess.DEVNULL)

    os.environ['PATH'] = f'{QMK_TOOLCHAINS_PATH}/bin{os.pathsep}{os.environ["PATH"]}'

    for gcc_exe in ['avr-gcc', 'arm-none-eabi-gcc', 'riscv32-unknown-elf-gcc']:
        cli.log.info(f'{gcc_exe:24s}: {_gcc_version_str(gcc_exe)}')
