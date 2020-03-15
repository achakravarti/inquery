################################################################################
#                      ___                                   
#                     |_ _|_ __   __ _ _   _  ___ _ __ _   _ 
#                      | || '_ \ / _` | | | |/ _ \ '__| | | |
#                      | || | | | (_| | |_| |  __/ |  | |_| |
#                     |___|_| |_|\__, |\__,_|\___|_|   \__, |
#                                   |_|                |___/ 
#
# Inquery - India Query RESTful microservice
# Copyright (c) 2020 Abhishek Chakravarti <abhishek@taranjali.org>. 
# See the accompanying inquery/AUTHORS file for the full list of contributors.
#
# This is the inquery/Makefile file; it defines the rules to build the Inquery
# microservice daemon and unit tests.
#
# This code is released under the GPLv3 License. See the accompanying 
# inquery/LICENSE file or <http://opensource.org/licenses/GPL-3.0> for complete
# licensing details.
#
# BY CONTINUING TO USE AND/OR DISTRIBUTE THIS FILE, YOU ACKNOWLEDGE THAT YOU
# HAVE UNDERSTOOD THESE LICENSE TERMS AND ACCEPT THEM.
################################################################################


#
# The directory where build artefacts are saved. This is generated on the fly at
# build-time, and is set to be ignored by Git.
#
DIR_BLD = bld


#
# The directory where the library source code kept.
#
DIR_LIB = lib


#
# The directory where the source code for the executable is kept.
#
DIR_EXE = exe


#
# The directory where the test code is kept.
#
DIR_TEST = test


#
# The list of source files required to build the library.
#
SRC_LIB = $(sort $(shell find $(DIR_LIB)/ -type f -name '*.c'))


#
# The list of source files required to build the executable.
#
SRC_EXE = $(sort $(wildcard $(DIR_EXE)/*.c))


#
# The list of test source files.
#
SRC_TEST = $(sort $(wildcard $(DIR_TEST)/*.c))


#
# The list of object files for the executable binary generated from the list of
# source files.
#
OBJ_LIB = $(patsubst $(DIR_LIB)/%.c, $(DIR_BLD)/%.o, $(SRC_LIB))


#
# The executable binary to be built.
#
BIN_EXE = bld/inquery


#
# The test runner binary.
#
BIN_TEST = bld/inquery-tests


#
# The compiler to use. We run gcc in tandem with ccache to improve build times.
#
CC = ccache gcc


#
# The compilation flags.
#
CFLAGS = -g -Wall -Wextra


#
# The link flags.
#
LDFLAGS = 


#
# The rule to build the executable binary.
#
$(BIN_EXE): $(OBJ_LIB) $(SRC_EXE)
	$(LINK.c) $^ -o $@


#
# The rule to build the test runner.
#
$(BIN_TEST): $(OBJ_LIB) $(SRC_TEST)
	$(LINK.c) $^ -o $@


#
# The rule to build the objects from source.
#
$(DIR_BLD)/%.o: $(DIR_LIB)/%.c | $(DIR_BLD)
	$(COMPILE.c) $^ -o $@


#
# The rule to create the build directory.
#
$(DIR_BLD):
	mkdir -p $@ $@/core


#
# The default build target.
#
all: $(BIN_EXE) $(BIN_TEST)


#
# The clean target.
#
clean:
	rm -rfv $(DIR_BLD)


#
# The target to run the executable binary.
#
run: $(BIN_EXE)
	./$(BIN_EXE)


#
# The target to run the unit tests.
#
test: $(BIN_TEST)
	./$(BIN_TEST)


#
# The target to run the Valgrind checks.
#
check: $(BIN_TEST) $(BIN_EXE)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all \
		--track-origins=yes --log-file=$(BIN_TEST).vglog         \
		$(BIN_TEST)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all \
		--track-origins=yes --log-file=$(BIN_EXE).vglog          \
		$(BIN_EXE)

#
# The target to build the compile database for LLVM using BEAR
#
compiledb: clean
	bear make all


#
# The list of phony targets.
#
.PHONY: all clean run check

