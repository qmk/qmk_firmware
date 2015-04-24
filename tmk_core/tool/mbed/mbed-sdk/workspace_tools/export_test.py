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
from os.path import join, abspath, dirname, exists
ROOT = abspath(join(dirname(__file__), ".."))
sys.path.insert(0, ROOT)

from shutil import move

from workspace_tools.paths import *
from workspace_tools.utils import mkdir, cmd
from workspace_tools.export import export, setup_user_prj


USR_PRJ_NAME = "usr_prj"
USER_PRJ = join(EXPORT_WORKSPACE, USR_PRJ_NAME)
USER_SRC = join(USER_PRJ, "src")


def setup_test_user_prj():
    if exists(USER_PRJ):
        print 'Test user project already generated...'
        return

    setup_user_prj(USER_PRJ, join(TEST_DIR, "rtos", "mbed", "basic"), [join(LIB_DIR, "rtos")])

    # FAKE BUILD URL
    open(join(USER_SRC, "mbed.bld"), 'w').write("http://mbed.org/users/mbed_official/code/mbed/builds/976df7c37ad5\n")


def fake_build_url_resolver(url):
    # FAKE BUILD URL: Ignore the URL, always return the path to the mbed library
    return {'path':MBED_LIBRARIES, 'name':'mbed'}


def test_export(toolchain, target, expected_error=None):
    if toolchain is None and target is None:
        base_dir = join(EXPORT_TMP, "zip")
    else:
        base_dir = join(EXPORT_TMP, toolchain, target)
    temp_dir = join(base_dir, "temp")
    mkdir(temp_dir)

    zip_path, report = export(USER_PRJ, USR_PRJ_NAME, toolchain, target, base_dir, temp_dir, False, None, fake_build_url_resolver)

    if report['success']:
        move(zip_path, join(EXPORT_DIR, "export_%s_%s.zip" % (toolchain, target)))
        print "[OK]"
    else:
        if expected_error is None:
            print '[ERRROR] %s' % report['errormsg']
        else:
            if (zip_path is None) and (expected_error in report['errormsg']):
                print '[OK]'
            else:
                print '[ERROR]'
                print '    zip:', zip_path
                print '    msg:', report['errormsg']


if __name__ == '__main__':
    setup_test_user_prj()

    for toolchain, target in [
            ('zip', 'LPC1768'),
            
            ('emblocks', 'LPC1768'),
            ('emblocks', 'LPC1549'),
            ('emblocks', 'LPC1114'),
            ('emblocks', 'LPC11U35_401'),
            ('emblocks', 'LPC11U35_501'),
            ('emblocks', 'LPCCAPPUCCINO'),
            ('emblocks', 'LPC2368'),
            ('emblocks', 'STM32F407'),
            ('emblocks', 'DISCO_F100RB'),
            ('emblocks', 'DISCO_F051R8'),
            ('emblocks', 'DISCO_F407VG'),
            ('emblocks', 'DISCO_F303VC'),
            ('emblocks', 'NRF51822'),
            ('emblocks', 'NUCLEO_F401RE'),
            ('emblocks', 'NUCLEO_F411RE'),
            ('emblocks', 'MTS_MDOT_F405RG'),
            ('emblocks', 'MTS_MDOT_F411RE'),

            ('coide', 'KL05Z'),
            ('coide', 'KL25Z'),
            ('coide', 'LPC1768'),
            ('coide', 'ARCH_PRO'),
            ('coide', 'DISCO_F407VG'),
            ('coide', 'NUCLEO_F401RE'),
            ('coide', 'NUCLEO_F411RE'),
            ('coide', 'DISCO_F429ZI'),
            ('coide', 'NUCLEO_F334R8'),
            ('coide', 'MTS_MDOT_F405RG'),
            ('coide', 'MTS_MDOT_F411RE'),

            ('uvision', 'LPC1768'),
            ('uvision', 'LPC11U24'),
            ('uvision', 'KL25Z'),
            ('uvision', 'LPC1347'),
            ('uvision', 'LPC1114'),
            ('uvision', 'LPC4088'),
            ('uvision', 'LPC4088_DM'),
            ('uvision', 'LPC4337'),
            ('uvision', 'HRM1017'),

            ('uvision', 'NUCLEO_F030R8'),
            ('uvision', 'NUCLEO_F070RB'),
            ('uvision', 'NUCLEO_F072RB'),
            ('uvision', 'NUCLEO_F091RC'),
            ('uvision', 'NUCLEO_F103RB'),
            ('uvision', 'NUCLEO_F302R8'),
            ('uvision', 'NUCLEO_F303RE'),
            ('uvision', 'NUCLEO_F334R8'),
            ('uvision', 'NUCLEO_F401RE'),
            ('uvision', 'NUCLEO_F411RE'),
            ('uvision', 'NUCLEO_L053R8'),
            ('uvision', 'NUCLEO_L073RZ'),
            ('uvision', 'NUCLEO_L152RE'),
            ('uvision', 'MTS_MDOT_F405RG'),
            ('uvision', 'MAXWSNENV'),
            ('uvision', 'MAX32600MBED'),

            ('lpcxpresso', 'LPC1768'),
            ('lpcxpresso', 'LPC4088'),
            ('lpcxpresso', 'LPC4088_DM'),
            ('lpcxpresso', 'LPC1114'),
            ('lpcxpresso', 'LPC11U35_401'),
            ('lpcxpresso', 'LPC11U35_501'),
            ('lpcxpresso', 'LPCCAPPUCCINO'),
            ('lpcxpresso', 'LPC1549'),
            ('lpcxpresso', 'LPC11U68'),
            # Linux path: /home/emimon01/bin/gcc-cs/bin/
            # Windows path: "C:/Program Files (x86)/CodeSourcery/Sourcery_CodeBench_Lite_for_ARM_EABI/bin/"
            ('codesourcery', 'LPC1768'),

            # Linux path: /home/emimon01/bin/gcc-arm/bin/
            # Windows path: C:/arm-none-eabi-gcc-4_7/bin/
            ('gcc_arm', 'LPC1768'),
            ('gcc_arm', 'LPC4088_DM'),
            ('gcc_arm', 'LPC1549'),
            ('gcc_arm', 'LPC1114'),
            ('gcc_arm', 'LPC11U35_401'),
            ('gcc_arm', 'LPC11U35_501'),
            ('gcc_arm', 'LPCCAPPUCCINO'),
            ('gcc_arm', 'LPC2368'),
            ('gcc_arm', 'LPC824'),
            ('gcc_arm', 'SSCI824'),

            ('gcc_arm', 'STM32F407'),
            ('gcc_arm', 'DISCO_F100RB'),
            ('gcc_arm', 'DISCO_F051R8'),
            ('gcc_arm', 'DISCO_F407VG'),
            ('gcc_arm', 'DISCO_F303VC'),
            ('gcc_arm', 'NRF51822'),
            ('gcc_arm', 'HRM1017'),
            ('gcc_arm', 'NUCLEO_F401RE'),
            ('gcc_arm', 'NUCLEO_F411RE'),
            ('gcc_arm', 'DISCO_F429ZI'),
            ('gcc_arm', 'NUCLEO_F334R8'),
            ('gcc_arm', 'MAX32600MBED'),
            ('gcc_arm', 'MTS_MDOT_F405RG'),
            ('gcc_arm', 'MTS_MDOT_F411RE'),
            ('gcc_arm', 'RZ_A1H'),
            ('gcc_arm', 'MAXWSNENV'),
            ('gcc_arm', 'MAX32600MBED'),

            ('ds5_5', 'LPC1768'), ('ds5_5', 'LPC11U24'),

            ('iar', 'LPC1768'),
            ('iar', 'LPC4088_DM'),
            ('iar', 'LPC1347'),

            ('iar', 'NUCLEO_F030R8'),
            ('iar', 'NUCLEO_F070RB'),
            ('iar', 'NUCLEO_F072RB'),
            ('iar', 'NUCLEO_F091RC'),
            ('iar', 'NUCLEO_F302R8'),
            ('iar', 'NUCLEO_F303RE'),
            ('iar', 'NUCLEO_F334R8'),
            ('iar', 'NUCLEO_F401RE'),
            ('iar', 'NUCLEO_F411RE'),
            ('iar', 'NUCLEO_L053R8'),
            ('iar', 'NUCLEO_L073RZ'),
            ('iar', 'NUCLEO_L152RE'),
            ('iar', 'STM32F407'),
            ('iar', 'MTS_MDOT_F405RG'),
            ('iar', 'MTS_MDOT_F411RE'),
            ('iar', 'MAXWSNENV'),
            ('iar', 'MAX32600MBED'),

            # Removed following item to avoid script error
            #(None, None),
        ]:
        print '\n=== Exporting to "%s::%s" ===' % (toolchain, target)
        test_export(toolchain, target)

    print "\n=== Test error messages ==="
    test_export('lpcxpresso', 'LPC11U24', expected_error='lpcxpresso')
