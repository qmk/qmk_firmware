#!/usr/bin/env python3

import os
import re
import shlex
import subprocess
from pathlib import Path

from ansi2html import Ansi2HTMLConverter
from jinja2 import Environment, FileSystemLoader, select_autoescape

orig_cwd = os.getcwd()
qmk_firmware_dir = Path(os.path.realpath(__file__)).parents[2]
build_dir = qmk_firmware_dir / ".build"

KEYBOARD_PATTERN = re.compile("CI Metadata: KEYBOARD=(?P<keyboard>.*)\r?\n")
KEYMAP_PATTERN = re.compile("CI Metadata: KEYMAP=(?P<keymap>.*)\r?\n")

env = Environment(
    loader=FileSystemLoader(Path(os.path.realpath(__file__)).parent / "templates"),
    autoescape=select_autoescape(),
)


def _run(command, capture_output=True, combined_output=False, text=True, **kwargs):
    if isinstance(command, str):
        command = shlex.split(command)
    if capture_output:
        kwargs["stdout"] = subprocess.PIPE
        kwargs["stderr"] = subprocess.PIPE
    if combined_output:
        kwargs["stderr"] = subprocess.STDOUT
    if "stdin" in kwargs and kwargs["stdin"] is None:
        del kwargs["stdin"]
    if text:
        kwargs["universal_newlines"] = True
    return subprocess.run(command, **kwargs)


def _ansi2html(value):
    return Ansi2HTMLConverter().convert(value, full=False)


def _ansi2html_styles():
    from ansi2html.style import get_styles

    styles = get_styles(scheme="dracula")
    return "\n".join([str(s) for s in styles])


def _git_log(count = 4):
    os.chdir(qmk_firmware_dir)
    ret = _run(f"git log -n {count} --color=always --no-merges --topo-order --stat").stdout.strip()
    os.chdir(orig_cwd)
    return ret

def _git_describe():
    os.chdir(qmk_firmware_dir)
    ret = _run("git describe --tags --always --dirty").stdout.strip()
    os.chdir(orig_cwd)
    return ret

def _git_revision():
    os.chdir(qmk_firmware_dir)
    ret = _run("git rev-parse HEAD").stdout.strip()
    os.chdir(orig_cwd)
    return ret


env.filters["ansi2html"] = _ansi2html

binaries = []
binaries.extend(qmk_firmware_dir.glob("*.bin"))
binaries.extend(qmk_firmware_dir.glob("*.hex"))
binaries.extend(qmk_firmware_dir.glob("*.uf2"))
binaries = list(sorted(binaries))

failures = []
for mdfile in list(sorted(build_dir.glob("failed.log.*"))):
    txt = Path(mdfile).read_text()

    m_kb = KEYBOARD_PATTERN.search(txt)
    if not m_kb:
        raise Exception("Couldn't determine the keyboard from the failure output")
    m_km = KEYMAP_PATTERN.search(txt)
    if not m_km:
        raise Exception("Couldn't determine the keymap from the failure output")

    txt = KEYBOARD_PATTERN.sub("", KEYMAP_PATTERN.sub("", txt)).strip()

    failures.append(
        {
            "stdout": txt,
            "keyboard": m_kb.group("keyboard"),
            "keymap": m_km.group("keymap"),
        }
    )

template = env.get_template("index.html.j2")
print(
    template.render(
        ansi2html_styles=_ansi2html_styles(),
        git_log=_git_log(),
        git_describe=_git_describe(),
        git_revision=_git_revision(),
        binaries=binaries,
        failures=failures,
    )
)
