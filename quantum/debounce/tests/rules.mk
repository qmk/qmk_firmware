# Copyright 2021 Simon Arlott
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

DEBOUNCE_COMMON_DEFS := -DMATRIX_ROWS=4 -DMATRIX_COLS=10 -DDEBOUNCE=5

DEBOUNCE_COMMON_SRC := $(QUANTUM_PATH)/debounce/tests/debounce_test_common.cpp \
	$(PLATFORM_PATH)/timer.c \
	$(PLATFORM_PATH)/$(PLATFORM_KEY)/timer.c

debounce_none_DEFS := $(DEBOUNCE_COMMON_DEFS)
debounce_none_SRC := $(DEBOUNCE_COMMON_SRC) \
	$(QUANTUM_PATH)/debounce/none.c \
	$(QUANTUM_PATH)/debounce/tests/none_tests.cpp

debounce_sym_defer_g_DEFS := $(DEBOUNCE_COMMON_DEFS)
debounce_sym_defer_g_SRC := $(DEBOUNCE_COMMON_SRC) \
	$(QUANTUM_PATH)/debounce/sym_defer_g.c \
	$(QUANTUM_PATH)/debounce/tests/sym_defer_g_tests.cpp

debounce_sym_defer_pk_DEFS := $(DEBOUNCE_COMMON_DEFS)
debounce_sym_defer_pk_SRC := $(DEBOUNCE_COMMON_SRC) \
	$(QUANTUM_PATH)/debounce/sym_defer_pk.c \
	$(QUANTUM_PATH)/debounce/tests/sym_defer_pk_tests.cpp

debounce_sym_defer_pr_DEFS := $(DEBOUNCE_COMMON_DEFS)
debounce_sym_defer_pr_SRC := $(DEBOUNCE_COMMON_SRC) \
	$(QUANTUM_PATH)/debounce/sym_defer_pr.c \
	$(QUANTUM_PATH)/debounce/tests/sym_defer_pr_tests.cpp

debounce_sym_eager_pk_DEFS := $(DEBOUNCE_COMMON_DEFS)
debounce_sym_eager_pk_SRC := $(DEBOUNCE_COMMON_SRC) \
	$(QUANTUM_PATH)/debounce/sym_eager_pk.c \
	$(QUANTUM_PATH)/debounce/tests/sym_eager_pk_tests.cpp

debounce_sym_eager_pr_DEFS := $(DEBOUNCE_COMMON_DEFS)
debounce_sym_eager_pr_SRC := $(DEBOUNCE_COMMON_SRC) \
	$(QUANTUM_PATH)/debounce/sym_eager_pr.c \
	$(QUANTUM_PATH)/debounce/tests/sym_eager_pr_tests.cpp

debounce_asym_eager_defer_pk_DEFS := $(DEBOUNCE_COMMON_DEFS)
debounce_asym_eager_defer_pk_SRC := $(DEBOUNCE_COMMON_SRC) \
	$(QUANTUM_PATH)/debounce/asym_eager_defer_pk.c \
	$(QUANTUM_PATH)/debounce/tests/asym_eager_defer_pk_tests.cpp
