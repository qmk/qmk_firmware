"""
mbed SDK
Copyright (c) 2014 ARM Limited

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
from exporters import Exporter
from os.path import splitext, basename
from workspace_tools.targets import TARGETS

# filter all the GCC_ARM targets out of the target list
gccTargets = []
for t in TARGETS:
    if 'GCC_ARM' in t.supported_toolchains:
        gccTargets.append(t.name)

class IntermediateFile(Exporter):
    NAME = 'EmBlocks'
    TOOLCHAIN = 'GCC_ARM'

    # we support all GCC targets (is handled on IDE side)
    TARGETS = gccTargets

    FILE_TYPES = {
        'headers': 'h',
        'c_sources': 'c',
        's_sources': 'a',
        'cpp_sources': 'cpp'
    }


    def generate(self):
        self.resources.win_to_unix()
        source_files = []
        for r_type, n in IntermediateFile.FILE_TYPES.iteritems():
            for file in getattr(self.resources, r_type):
                source_files.append({
                    'name': file, 'type': n
                })

        libraries = []
        for lib in self.resources.libraries:
            l, _ = splitext(basename(lib))
            libraries.append(l[3:])


        if self.resources.linker_script is None:
            self.resources.linker_script = ''

        ctx = {
            'name': self.program_name,
            'target': self.target,
            'toolchain': self.toolchain.name,
            'source_files': source_files,
            'include_paths': self.resources.inc_dirs,
            'script_file': self.resources.linker_script,
            'library_paths': self.resources.lib_dirs,
            'libraries': libraries,
            'symbols': self.get_symbols(),
            'object_files': self.resources.objects,
            'sys_libs': self.toolchain.sys_libs,
            'cc_org': self.toolchain.cc[1:],
            'ld_org': self.toolchain.ld[1:],
            'cppc_org': self.toolchain.cppc[1:]
        }

        # EmBlocks intermediate file template
        self.gen_file('emblocks.eix.tmpl', ctx, '%s.eix' % self.program_name)
