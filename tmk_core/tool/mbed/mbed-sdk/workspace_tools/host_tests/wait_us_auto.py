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

from time import time

class WaitusTest():
    """ This test is reading single characters from stdio
        and measures time between their occurrences.
    """
    TICK_LOOP_COUNTER = 13
    TICK_LOOP_SUCCESSFUL_COUNTS = 10
    DEVIATION = 0.10    # +/-10%

    def test(self, selftest):
        test_result = True
        # First character to start test (to know after reset when test starts)
        if selftest.mbed.set_serial_timeout(None) is None:
            return selftest.RESULT_IO_SERIAL
        c = selftest.mbed.serial_read(1)
        if c is None:
            return selftest.RESULT_IO_SERIAL
        if c == '$': # target will printout TargetID e.g.: $$$$1040e649d5c09a09a3f6bc568adef61375c6
            #Read additional 39 bytes of TargetID
            if selftest.mbed.serial_read(39) is None:
                return selftest.RESULT_IO_SERIAL
            c = selftest.mbed.serial_read(1) # Re-read first 'tick'
            if c is None:
                return selftest.RESULT_IO_SERIAL
        start_serial_pool = time()
        start = time()

        success_counter = 0

        for i in range(0, self.TICK_LOOP_COUNTER):
            c = selftest.mbed.serial_read(1)
            if c is None:
                return selftest.RESULT_IO_SERIAL
            delta = time() - start
            deviation = abs(delta - 1)
            # Round values
            delta = round(delta, 2)
            deviation = round(deviation, 2)
            # Check if time measurements are in given range
            deviation_ok = True if delta > 0 and deviation <= self.DEVIATION else False
            success_counter = success_counter+1 if deviation_ok else 0
            msg = "OK" if deviation_ok else "FAIL"
            selftest.notify("%s in %.2f sec (%.2f) [%s]"% (c, delta, deviation, msg))
            start = time()
            if success_counter >= self.TICK_LOOP_SUCCESSFUL_COUNTS:
                break
        measurement_time = time() - start_serial_pool
        selftest.notify("Consecutive OK timer reads: %d"% success_counter)
        selftest.notify("Completed in %.2f sec" % (measurement_time))
        test_result = True if success_counter >= self.TICK_LOOP_SUCCESSFUL_COUNTS else False
        return selftest.RESULT_SUCCESS if test_result else selftest.RESULT_FAILURE
