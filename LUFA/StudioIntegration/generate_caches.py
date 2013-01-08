"""
             LUFA Library
     Copyright (C) Dean Camera, 2013.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
"""

import sys
import os
sys.path.append("ProjectGenerator")

try:
	from asf_avrstudio5_interface import PythonFacade
except ImportError:
	print "The ASF project generator is missing."

p = PythonFacade(os.path.abspath(__file__))
p.check_extension_database_sanity(sys.argv[1])
p.generate_extension_cache_files(sys.argv[1])
