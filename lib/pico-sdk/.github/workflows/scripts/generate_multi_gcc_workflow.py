#!/usr/bin/env python3

import os
from collections import OrderedDict
import subprocess
import re

toolchain_dir = "/opt/arm"
toolchains = os.listdir(toolchain_dir)

gcc_versions = OrderedDict()

for toolchain in toolchains:
    fullpath = os.path.join(toolchain_dir, toolchain)
    gcc_path = os.path.join(fullpath, "bin/arm-none-eabi-gcc")
    version = subprocess.run([gcc_path, "--version"], capture_output=True)
    stdout = version.stdout.decode('utf-8')
    stderr = version.stderr.decode('utf-8')
    assert(len(stderr) == 0)
    # Version should be on first line
    version_line = stdout.split("\n")[0]
    m = re.search("(\d+\.\d+\.\d+)", version_line)
    assert(m is not None)
    version = m.group(1)

    if version in gcc_versions:
        raise Exception("Already have version {} in versions current path {}, this path {}".format(version, gcc_versions[version], fullpath))

    gcc_versions[version] = fullpath

# Sort by major version
gcc_versions_sorted = OrderedDict(sorted(gcc_versions.items(), key=lambda item: int(item[0].replace(".", ""))))


# Create output
output = '''
name: Multi GCC
on:
  workflow_dispatch:
  push:
    branches:
      - 'develop'
      - 'master'

jobs:
  build:
    if: github.repository_owner == 'raspberrypi'
    runs-on: [self-hosted, Linux, X64]

    steps:
    - name: Clean workspace
      run: |
        echo "Cleaning up previous run"
        rm -rf "${{ github.workspace }}"
        mkdir -p "${{ github.workspace }}"

    - name: Checkout repo
      uses: actions/checkout@v2

    - name: Checkout submodules
      run: git submodule update --init

    - name: Get core count
      id: core_count
      run : cat /proc/cpuinfo  | grep processor | wc -l
'''

for gcc_version, toolchain_path in gcc_versions_sorted.items():
    for build_type in ["Debug", "Release"]:
        output += "\n"
        output += "    - name: GCC {} {}\n".format(gcc_version, build_type)
        output += "      if: always()\n"
        output += "      shell: bash\n"
        output += "      run: cd ${{{{github.workspace}}}}; mkdir -p build; rm -rf build/*; cd build; cmake ../ -DPICO_SDK_TESTS_ENABLED=1 -DCMAKE_BUILD_TYPE={} -DPICO_TOOLCHAIN_PATH={} -DPICO_BOARD=pico_w; make -j ${{{{steps.core_count.outputs.output}}}}\n".format(build_type, toolchain_path)

print(output)
