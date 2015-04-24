"""
mbed SDK
Copyright (c) 2011-2013 ARM Limited

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
"""
import sys
from os.path import join, abspath, dirname, exists, splitext
from subprocess import Popen, PIPE
import csv
from collections import defaultdict

ROOT = abspath(join(dirname(__file__), ".."))
sys.path.insert(0, ROOT)

from workspace_tools.paths import BUILD_DIR, TOOLS_DATA
from workspace_tools.settings import GCC_ARM_PATH
from workspace_tools.tests import TEST_MAP
from workspace_tools.build_api import build_mbed_libs, build_project

SIZE = join(GCC_ARM_PATH, 'arm-none-eabi-size')

def get_size(path):
    out = Popen([SIZE, path], stdout=PIPE).communicate()[0]
    return map(int, out.splitlines()[1].split()[:4])

def get_percentage(before, after):
    if before == 0:
        return 0 if after == 0 else 100.0
    return float(after - before) / float(before) * 100.0

def human_size(val):
    if val>1024:
        return "%.0fKb" % (float(val)/1024.0)
    return "%d" % val

def print_diff(name, before, after):
    print "%s: (%s -> %s) %.2f%%" % (name, human_size(before) , human_size(after) , get_percentage(before , after))

BENCHMARKS = [
    ("BENCHMARK_1", "CENV"),
    ("BENCHMARK_2", "PRINTF"),
    ("BENCHMARK_3", "FP"),
    ("BENCHMARK_4", "MBED"),
    ("BENCHMARK_5", "ALL"),
]
BENCHMARK_DATA_PATH = join(TOOLS_DATA, 'benchmarks.csv')


def benchmarks():
    # CSV Data
    csv_data = csv.writer(open(BENCHMARK_DATA_PATH, 'wb'))
    csv_data.writerow(['Toolchain', "Target", "Benchmark", "code", "data", "bss", "flash"])

    # Build
    for toolchain in ['ARM', 'uARM', 'GCC_CR', 'GCC_CS', 'GCC_ARM']:
        for mcu in ["LPC1768", "LPC11U24"]:
            # Build Libraries
            build_mbed_libs(mcu, toolchain)

            # Build benchmarks
            build_dir = join(BUILD_DIR, "benchmarks", mcu, toolchain)
            for test_id, title in BENCHMARKS:
                # Build Benchmark
                try:
                    test = TEST_MAP[test_id]
                    path = build_project(test.source_dir, join(build_dir, test_id),
                                 mcu, toolchain, test.dependencies)
                    base, ext = splitext(path)
                    # Check Size
                    code, data, bss, flash = get_size(base+'.elf')
                    csv_data.writerow([toolchain, mcu, title, code, data, bss, flash])
                except Exception, e:
                    print "Unable to build %s for toolchain %s targeting %s" % (test_id, toolchain, mcu)
                    print e


def compare(t1, t2, target):
    if not exists(BENCHMARK_DATA_PATH):
        benchmarks()
    else:
        print "Loading: %s" % BENCHMARK_DATA_PATH

    data = csv.reader(open(BENCHMARK_DATA_PATH, 'rb'))

    benchmarks_data = defaultdict(dict)
    for (toolchain, mcu, name, code, data, bss, flash) in data:
        if target == mcu:
            for t in [t1, t2]:
                if toolchain == t:
                    benchmarks_data[name][t] = map(int, (code, data, bss, flash))

    print "%s vs %s for %s" % (t1, t2, target)
    for name, data in benchmarks_data.iteritems():
        try:
            # Check Size
            code_a, data_a, bss_a, flash_a = data[t1]
            code_u, data_u, bss_u, flash_u = data[t2]

            print "\n=== %s ===" % name
            print_diff("code", code_a , code_u)
            print_diff("data", data_a , data_u)
            print_diff("bss", bss_a , bss_u)
            print_diff("flash", flash_a , flash_u)
        except Exception, e:
            print "No data for benchmark %s" % (name)
            print e


if __name__ == '__main__':
    compare("GCC_CR", "GCC_CS", "LPC1768")
