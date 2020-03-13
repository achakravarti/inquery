################################################################################
#                      ___                                   
#                     |_ _|_ __   __ _ _   _  ___ _ __ _   _ 
#                      | || '_ \ / _` | | | |/ _ \ '__| | | |
#                      | || | | | (_| | |_| |  __/ |  | |_| |
#                     |___|_| |_|\__, |\__,_|\___|_|   \__, |
#                                   |_|                |___/ 
#
################################################################################


DIR_BLD = bld
DIR_SRC = src
DIR_TEST = test
LIB_SRC = $(sort $(shell find $(DIR_SRC)/ -type f -name '*.c'))
LIB_OBJ = $(patsubst $(DIR_SRC)/%.c, $(DIR_BLD)/%.o, $(LIB_SRC))
TEST_SRC = $(sort $(wildcard $(DIR_TEST)/*.c))
TEST_BIN = bld/inquery-runner
CC = ccache gcc
CFLAGS = -g -Wall -Wextra
LDFLAGS = 


$(TEST_BIN): $(LIB_OBJ) $(TEST_SRC)
	$(LINK.c) $^ -o $@

$(DIR_BLD)/%.o: $(DIR_SRC)/%.c | $(DIR_BLD)
	$(COMPILE.c) $^ -o $@

$(DIR_BLD):
	mkdir -p $@ # Add subdirectories as required

all: $(TEST_BIN)

clean:
	rm -rfv $(DIR_BLD)

run: $(TEST_BIN)
	./$(TEST_BIN)

check: $(TEST_BIN)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all \
		--track-origins=yes --log-file=$(DIR_BLD)/valgrind.log   \
		$(TEST_BIN)

.PHONY: all clean run

