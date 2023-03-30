#!/usr/bin/env python3
#
# Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
#
# SPDX-License-Identifier: BSD-3-Clause
#
#
# Little script to check that every \ingroup has a matching \defgroup
#
# Usage:
#
# Run from the root of the tree to check


import subprocess
import re
import sys
import os

groups = {}
any_errors = False

res = subprocess.run(['git', 'grep', '\\defgroup'], check=True, stdout=subprocess.PIPE)
for line in res.stdout.decode('utf8').split('\n'):
    m = re.match(r'^(\S+):.*\\defgroup\s+(\w+)', line)
    if m:
        filename = m.group(1)
        group = m.group(2)
        if os.path.basename(filename) in ('check_doxygen_groups.py', 'index.h'):
            continue
        if group in groups:
            any_errors = True
            print("{} uses \\defgroup {} but so does {}".format(groups[group], group, filename))
        else:
            groups[group] = filename

res = subprocess.run(['git', 'grep', '\\ingroup'], check=True, stdout=subprocess.PIPE)
for line in res.stdout.decode('utf8').split('\n'):
    m = re.match(r'^(\S+):.*\\ingroup\s+(\w+)', line)
    if m:
        filename = m.group(1)
        group = m.group(2)
        if os.path.basename(filename) in ('check_doxygen_groups.py', 'index.h'):
            continue
        if group not in groups:
            any_errors = True
            print("{} uses \\ingroup {} which was never defined".format(filename, group))

sys.exit(any_errors)
