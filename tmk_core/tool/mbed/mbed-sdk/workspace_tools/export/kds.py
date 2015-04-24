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
from exporters import Exporter
from os.path import splitext, basename


class KDS(Exporter):
    NAME = 'Kinetis Design Studio'
    TOOLCHAIN = 'GCC_ARM'

    TARGETS = [
        'K64F',
        'K22F',
    ]

    def generate(self):
        libraries = []
        for lib in self.resources.libraries:
            l, _ = splitext(basename(lib))
            libraries.append(l[3:])

        ctx = {
            'name': self.program_name,
            'include_paths': self.resources.inc_dirs,
            'linker_script': self.resources.linker_script,
            'object_files': self.resources.objects,
            'libraries': libraries,
            'symbols': self.get_symbols()
        }
        self.gen_file('kds_%s_project.tmpl' % self.target.lower(), ctx, '.project')
        self.gen_file('kds_%s_cproject.tmpl' % self.target.lower(), ctx, '.cproject')
        self.gen_file('kds_launch.tmpl', ctx, '%s.launch' % self.program_name)
