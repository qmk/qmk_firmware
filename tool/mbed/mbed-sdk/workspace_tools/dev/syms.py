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


Utility to find which libraries could define a given symbol
"""
from argparse import ArgumentParser
from os.path import join, splitext
from os import walk
from subprocess import Popen, PIPE


OBJ_EXT = ['.o', '.a', '.ar']


def find_sym_in_lib(sym, obj_path):
    contain_symbol = False

    out = Popen(["nm", "-C", obj_path], stdout=PIPE, stderr=PIPE).communicate()[0]
    for line in out.splitlines():
            tokens = line.split()
            n = len(tokens)
            if n == 2:
                sym_type = tokens[0]
                sym_name = tokens[1]
            elif n == 3:
                sym_type = tokens[1]
                sym_name = tokens[2]
            else:
                continue

            if sym_type == "U":
                # This object is using this symbol, not defining it
                continue

            if sym_name == sym:
                contain_symbol = True

    return contain_symbol


def find_sym_in_path(sym, dir_path):
    for root, _, files in walk(dir_path):
        for file in files:

            _, ext = splitext(file)
            if ext not in OBJ_EXT: continue

            path = join(root, file)
            if find_sym_in_lib(sym, path):
                print path


if __name__ == '__main__':
    parser = ArgumentParser(description='Find Symbol')
    parser.add_argument('-s', '--sym',  required=True,
                        help='The symbol to be searched')
    parser.add_argument('-p', '--path',  required=True,
                        help='The path where to search')
    args = parser.parse_args()

    find_sym_in_path(args.sym, args.path)
