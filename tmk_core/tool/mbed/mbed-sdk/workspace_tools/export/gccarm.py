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


class GccArm(Exporter):
    NAME = 'GccArm'
    TOOLCHAIN = 'GCC_ARM'

    TARGETS = [
        'LPC1768',
        'LPC1549',
        'KL05Z',
        'KL25Z',
        'KL43Z',
        'KL46Z',
        'K64F',
        'K22F',
        'K20D50M',
        'LPC4088',
        'LPC4088_DM',
        'LPC4330_M4',
        'LPC11U24',
        'LPC1114',
        'LPC11U35_401',
        'LPC11U35_501',
        'LPC11U37H_401',
        'LPC824',
        'SSCI824',
        'STM32F407',
        'DISCO_F100RB',
        'DISCO_F051R8',
        'DISCO_F407VG',
        'DISCO_F303VC',
        'UBLOX_C027',
        'ARCH_PRO',
        'NRF51822',
        'HRM1017',
        'RBLAB_NRF51822',
        'LPC2368',
        'LPCCAPPUCCINO',
        'ARCH_BLE',
        'MTS_GAMBIT',
        'ARCH_MAX',
        'NUCLEO_F401RE',
        'NUCLEO_F411RE',
        'ARCH_MAX',
        'DISCO_F429ZI',
        'NUCLEO_F030R8',
        'NUCLEO_F070RB',
        'NUCLEO_F072RB',
        'NUCLEO_F091RC',
        'NUCLEO_F103RB',
        'NUCLEO_F302R8',
        'NUCLEO_F303RE',
        'NUCLEO_F334R8',
        'DISCO_L053C8',
        'NUCLEO_L053R8',
        'NUCLEO_L073RZ',
        'DISCO_F334C8',
        'MAX32600MBED',
        'MAXWSNENV',
        'MTS_MDOT_F405RG',
        'MTS_MDOT_F411RE',
        'NUCLEO_L152RE',
        'NRF51_DK',
        'NRF51_DONGLE',
        'SEEED_TINY_BLE',
        'DISCO_F401VC',
		'DELTA_DFCM_NNN40',
        'RZ_A1H',
        'MOTE_L152RC',
    ]

    DOT_IN_RELATIVE_PATH = True

    def generate(self):
        # "make" wants Unix paths
        self.resources.win_to_unix()

        to_be_compiled = []
        for r_type in ['s_sources', 'c_sources', 'cpp_sources']:
            r = getattr(self.resources, r_type)
            if r:
                for source in r:
                    base, ext = splitext(source)
                    to_be_compiled.append(base + '.o')

        libraries = []
        for lib in self.resources.libraries:
            l, _ = splitext(basename(lib))
            libraries.append(l[3:])

        ctx = {
            'name': self.program_name,
            'to_be_compiled': to_be_compiled,
            'object_files': self.resources.objects,
            'include_paths': self.resources.inc_dirs,
            'library_paths': self.resources.lib_dirs,
            'linker_script': self.resources.linker_script,
            'libraries': libraries,
            'symbols': self.get_symbols()
        }
        self.gen_file('gcc_arm_%s.tmpl' % self.target.lower(), ctx, 'Makefile')
