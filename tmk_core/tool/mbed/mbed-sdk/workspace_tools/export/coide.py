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


class CoIDE(Exporter):
    NAME = 'CoIDE'
    TOOLCHAIN = 'GCC_ARM'

    TARGETS = [
        'KL25Z',
        'KL05Z',
        'LPC1768',
        'ARCH_PRO',
        'ARCH_MAX',
        'UBLOX_C027',
        'NUCLEO_L053R8',
        'NUCLEO_L152RE',
        'NUCLEO_F030R8',
        'NUCLEO_F070RB',
        'NUCLEO_F072RB',
        'NUCLEO_F091RC',
        'NUCLEO_F103RB',
        'NUCLEO_F302R8',
        'NUCLEO_F303RE',
        'NUCLEO_F334R8',
        'NUCLEO_F401RE',
        'NUCLEO_F411RE',
        'DISCO_L053C8',
        'DISCO_F051R8',
        'DISCO_F100RB',
        'DISCO_F303VC',
        'DISCO_F334C8',
        'DISCO_F401VC',
        'DISCO_F407VG',
        'DISCO_F429ZI',
        'MTS_MDOT_F405RG',
        'MTS_MDOT_F411RE',
        'MOTE_L152RC',
    ]

    # seems like CoIDE currently supports only one type
    FILE_TYPES = {
        'c_sources':'1',
        'cpp_sources':'1',
        's_sources':'1'
    }
    FILE_TYPES2 = {
        'headers':'1'
    }

    def generate(self):
        self.resources.win_to_unix()
        source_files = []
        for r_type, n in CoIDE.FILE_TYPES.iteritems():
            for file in getattr(self.resources, r_type):
                source_files.append({
                    'name': basename(file), 'type': n, 'path': file
                })
        header_files = []
        for r_type, n in CoIDE.FILE_TYPES2.iteritems():
            for file in getattr(self.resources, r_type):
                header_files.append({
                    'name': basename(file), 'type': n, 'path': file
                })

        libraries = []
        for lib in self.resources.libraries:
            l, _ = splitext(basename(lib))
            libraries.append(l[3:])

        if self.resources.linker_script is None:
            self.resources.linker_script = ''
            
        ctx = {
            'name': self.program_name,
            'source_files': source_files,
            'header_files': header_files,
            'include_paths': self.resources.inc_dirs,
            'scatter_file': self.resources.linker_script,
            'library_paths': self.resources.lib_dirs,
            'object_files': self.resources.objects,
            'libraries': libraries,
            'symbols': self.get_symbols()
        }
        target = self.target.lower()

        # Project file
        self.gen_file('coide_%s.coproj.tmpl' % target, ctx, '%s.coproj' % self.program_name)
