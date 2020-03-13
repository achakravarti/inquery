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
#
# This code is released under the GPLv3 License. See the accompanying 
# inquery/LICENSE.md file or <http://opensource.org/licenses/GPL-3.0> for 
# complete licensing details.
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
# The directory where the source code kept.
#
DIR_SRC = src


#
# The directory where the test code is kept.
#
DIR_TEST = test


#
# The list of source files required to build the executable binary.
#
EXE_SRC = $(sort $(shell find $(DIR_SRC)/ -type f -name '*.c'))


#
# The list of test source files.
#
TEST_SRC = $(sort $(wildcard $(DIR_TEST)/*.c))


#
# The list of object files for the executable binary generated from the list of
# source files.
#
EXE_OBJ = $(patsubst $(DIR_SRC)/%.c, $(DIR_BLD)/%.o, $(LIB_SRC))


#
# The executable binary to be built.
#
EXE_BIN = bld/inquery


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
$(EXE_BIN): $(EXE_OBJ)
	$(LINK.c) $^ -o $@


#
# The rule to build the test runner.
#
$(TEST_BIN): $(EXE_OBJ) $(TEST_SRC)
	$(LINK.c) $^ -o $@


#
# The rule to build the objects from source.
#
$(DIR_BLD)/%.o: $(DIR_SRC)/%.c | $(DIR_BLD)
	$(COMPILE.c) $^ -o $@


#
# The rule to create the build directory.
#
$(DIR_BLD):
	mkdir -p $@ # Add subdirectories as required


#
# The default build target.
#
all: $(EXE_BIN)


#
# The clean target.
#
clean:
	rm -rfv $(DIR_BLD)


#
# The target to run the executable binary.
#
run: $(EXE_BIN)
	./$(EXE_BIN)


#
# The target to run the unit tests.
#
test: $(TEST_BIN)
	./$(TEST_BIN)


#
# The target to run the Valgrind checks.
#
check: $(EXE_BIN)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all \
		--track-origins=yes --log-file=$(DIR_BLD)/valgrind.log   \
		$(TEST_BIN)


#
# The list of phony targets.
#
.PHONY: all clean run check

