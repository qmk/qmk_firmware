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
import re
from os import remove
from os.path import join, exists

from workspace_tools.toolchains import mbedToolchain
from workspace_tools.settings import IAR_PATH
from workspace_tools.settings import GOANNA_PATH
from workspace_tools.hooks import hook_tool

class IAR(mbedToolchain):
    LIBRARY_EXT = '.a'
    LINKER_EXT = '.icf'
    STD_LIB_NAME = "%s.a"

    DIAGNOSTIC_PATTERN = re.compile('"(?P<file>[^"]+)",(?P<line>[\d]+)\s+(?P<severity>Warning|Error)(?P<message>.+)')

    def __init__(self, target, options=None, notify=None, macros=None, silent=False):
        mbedToolchain.__init__(self, target, options, notify, macros, silent)

        c_flags = [
            "--cpu=%s" % target.core, "--thumb",
            "--dlib_config", join(IAR_PATH, "inc", "c", "DLib_Config_Full.h"),
            "-e", # Enable IAR language extension
            "--no_wrap_diagnostics",
            # Pa050: No need to be notified about "non-native end of line sequence"
            # Pa084: Pointless integer comparison -> checks for the values of an enum, but we use values outside of the enum to notify errors (ie: NC).
            # Pa093: Implicit conversion from float to integer (ie: wait_ms(85.4) -> wait_ms(85))
            # Pa082: Operation involving two values from two registers (ie: (float)(*obj->MR)/(float)(LPC_PWM1->MR0))
            "--diag_suppress=Pa050,Pa084,Pa093,Pa082",
        ]

        if "debug-info" in self.options:
            c_flags.append("-r")
            c_flags.append("-On")
        else:
            c_flags.append("-Oh")

        IAR_BIN = join(IAR_PATH, "bin")
        main_cc = join(IAR_BIN, "iccarm")
        self.asm  = [join(IAR_BIN, "iasmarm")] + ["--cpu", target.core]
        if not "analyze" in self.options:
            self.cc   = [main_cc] + c_flags
            self.cppc = [main_cc, "--c++",  "--no_rtti", "--no_exceptions"] + c_flags
        else:
            self.cc   = [join(GOANNA_PATH, "goannacc"), '--with-cc="%s"' % main_cc.replace('\\', '/'), "--dialect=iar-arm", '--output-format="%s"' % self.GOANNA_FORMAT] + c_flags
            self.cppc = [join(GOANNA_PATH, "goannac++"), '--with-cxx="%s"' % main_cc.replace('\\', '/'), "--dialect=iar-arm", '--output-format="%s"' % self.GOANNA_FORMAT] + ["--c++", "--no_rtti", "--no_exceptions"] + c_flags
        self.ld   = join(IAR_BIN, "ilinkarm")
        self.ar = join(IAR_BIN, "iarchive")
        self.elf2bin = join(IAR_BIN, "ielftool")

    def parse_output(self, output):
        for line in output.splitlines():
            match = IAR.DIAGNOSTIC_PATTERN.match(line)
            if match is not None:
                self.cc_info(
                    match.group('severity').lower(),
                    match.group('file'),
                    match.group('line'),
                    match.group('message'),
                    target_name=self.target.name,
                    toolchain_name=self.name
                )
            match = self.goanna_parse_line(line)
            if match is not None:
                self.cc_info(
                    match.group('severity').lower(),
                    match.group('file'),
                    match.group('line'),
                    match.group('message')
                )

    def get_dep_opt(self, dep_path):
        return ["--dependencies", dep_path]

    def cc_extra(self, base):
        return ["-l", base + '.s']

    def parse_dependencies(self, dep_path):
        return [path.strip() for path in open(dep_path).readlines()
                if (path and not path.isspace())]
                
    def assemble(self, source, object, includes):
        return [self.hook.get_cmdline_assembler(self.asm + ['-D%s' % s for s in self.get_symbols() + self.macros] + ["-I%s" % i for i in includes] + ["-o", object, source])]

    def archive(self, objects, lib_path):
        if exists(lib_path):
            remove(lib_path)
        self.default_cmd([self.ar, lib_path] + objects)

    def link(self, output, objects, libraries, lib_dirs, mem_map):
        args = [self.ld, "-o", output, "--config", mem_map, "--skip_dynamic_initialization"]
        self.default_cmd(self.hook.get_cmdline_linker(args + objects + libraries))

    @hook_tool
    def binary(self, resources, elf, bin):
        self.default_cmd(self.hook.get_cmdline_binary([self.elf2bin, '--bin', elf, bin]))
