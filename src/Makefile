CC = gcc
CCFL = -Wall -Werror -Wextra --std=c11
BUILD_LIBS = -lcheck

LIB_OBJ_DIR := .obj_lib
LIB_SRC_DIR := .
LIB_SRC_FILES := $(wildcard $(LIB_SRC_DIR)/*.c)
LIB_OBJ_FILES := $(patsubst $(LIB_SRC_DIR)/%.c,$(LIB_OBJ_DIR)/%.o,$(LIB_SRC_FILES))
TESTS_OBJ_DIR := .obj_tests
TESTS_SRC_DIR := tests
TESTS_SRC_FILES := $(wildcard $(TESTS_SRC_DIR)/*.c)
TESTS_OBJ_FILES := $(patsubst $(TESTS_SRC_DIR)/%.c,$(TESTS_OBJ_DIR)/%.o,$(TESTS_SRC_FILES))

OS := $(shell uname -s)
ifeq ($(OS), Darwin)
	CCFL += -DOS_MAC
endif
ifeq ($(OS), Linux)
	CCFL += -DOS_LINUX
	BUILD_LIBS += -lpthread -lm -lsubunit
endif

all: decimal.a

decimal.a: $(LIB_OBJ_FILES)
	rm -f decimal.a
	ar rcs $@ $(LIB_OBJ_FILES)

test: $(TESTS_OBJ_FILES) decimal.a
	$(CC) $(CCFL) -o test.out $^ $(BUILD_LIBS)
	./test.out

gcov_report: clean
	$(CC) $(CCFL) -fprofile-arcs -ftest-coverage ./*.c tests/*.c $(TEST_FLAGS) -o test_report.out -lm $(BUILD_LIBS)
	./test_report.out
	lcov -t test_report -o test.info -c -d .
	genhtml -o report test.info
	open ./report/index.html

$(LIB_OBJ_DIR)/%.o: $(LIB_SRC_DIR)/%.c prepare_l
	$(CC) $(CCFL) -c -o $@ $<

$(TESTS_OBJ_DIR)/%.o: $(TESTS_SRC_DIR)/%.c prepare_t
	$(CC) $(CCFL) -c -o $@ $<

prepare_l:
	mkdir -p $(LIB_OBJ_DIR)

prepare_t:
	mkdir -p $(TESTS_OBJ_DIR)

clean:
	rm -rf .obj* decimal.a test.out
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -f test_report.out
	rm -rf report

rebuild: clean all

format:
	find .. \( -name '*.c' -o -name '*.h' \) -print0 | xargs -0 clang-format -n -Werror --verbose --style=google

format-force:
	find .. \( -name '*.c' -o -name '*.h' \) -print0 | xargs -0 clang-format -i --verbose --style=google
