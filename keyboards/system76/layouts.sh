#!/usr/bin/env bash
#
# This script produces layout data for the System76 Keyboard Configurator.
#
# Copyright (C) 2021  System76
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, version 3.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

set -eEuo pipefail

R=$(git rev-parse --show-toplevel)
cd "${R}"
rm -rf .build/layouts
mkdir -p .build/layouts
D="$(realpath .build/layouts)"

binary="${D}/keymap"
source="${binary}.c"
header="quantum/keycode.h"
printf "#include <stdio.h>\n" >"$source"
printf "#include \"%s\"\n\n" "${header}" >>"$source"
echo "int main(int argc, char **argv) {" >>"$source"
grep '^    KC_' "$header" |
  cut -d ' ' -f5 |
  cut -d ',' -f1 |
  while read -r keycode; do
    name=$(echo "${keycode}" | cut -d '_' -f2-)
    printf "    printf(\"%s,0x%%04X\\\n\", $keycode);\n" "${name}" >>"$source"
  done
printf "\n    return 0;\n}\n" >>"$source"
gcc -I. "$source" -o "$binary"
"${binary}" | tee "${D}/keymap.csv"

cd keyboards
for board in system76/launch_*; do
  file="$board/$(basename "$board").h"
  if [ ! -e "$file" ]; then
    continue
  fi
  echo "# ${board}"
  mkdir -p "${D}/${board}"
  cp "${D}/keymap.csv" "${D}/${board}"
  row=0
  rg \
    --multiline \
    --multiline-dotall \
    --regexp '#define LAYOUT\(.*\) \{.*\}' \
    "$file" |
    grep --only-matching '\{.*\}' |
    sed 's/^{ //' |
    sed 's/ }$//' |
    sed 's/, / /g' |
    while read -r line; do
      col=0
      for word in $line; do
        if [[ "${word}" != "___" ]]; then
          echo "${word},${row},${col}"
        fi
        col=$((col + 1))
      done
      row=$((row + 1))
    done |
    sort -n |
    tee "${D}/${board}/layout.csv"
done
