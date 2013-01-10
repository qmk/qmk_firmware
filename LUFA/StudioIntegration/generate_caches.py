"""
             LUFA Library
     Copyright (C) Dean Camera, 2013.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
"""

import sys
import os
sys.path.append("ProjectGenerator")


def main():
	try:
		from asf_avrstudio5_interface import PythonFacade
	except ImportError:
		print "Fatal Error: The ASF project generator is missing."
		sys.exit()

	p = PythonFacade(os.path.abspath(__file__))

	print "[Project Generator] Checking database sanity..."
	sys.stdout.flush()
	p.check_extension_database_sanity(sys.argv[1])

	print "[Project Generator] Building cache files..."
	sys.stdout.flush()
	p.generate_extension_cache_files(sys.argv[1])

	print "[Project Generator] Cache files created."


if __name__ == "__main__":
    sys.exit(main())
