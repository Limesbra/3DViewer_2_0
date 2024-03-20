CC = g++
CC_FLAGS = --std=c++17 -Wall -Werror -Wextra -g
TEST_FLAGS = -lgtest -pthread
COVERAGE_FLAGS = --coverage -fprofile-arcs -ftest-coverage
FILES = ../app_src/model/*.cc

UNAME := $(shell uname -s)
ifeq ($(UNAME), Darwin)
	RUN = ./build/s21_3D_viewer_2_0.app/Contents/MacOS/s21_3D_viewer_2_0
endif
ifeq ($(UNAME), Linux)
	RUN = ./build/s21_3D_viewer_2_0
endif

all: install test

install:
	cd app_src && qmake . && make 
	make clean_up

run:
	$(RUN)

uninstall:
	rm -rf build

dist:
	@rm -rf 3DViewer2
	@rm -rf 3DViewer2.tar
	@mkdir 3DViewer2
	@cp -r app_src tests doc samples Makefile 3DViewer2
	@tar -cvzf 3dviewer2.tar  3DViewer2
	@rm -rf 3DViewer2


dvi:
	open doc/html/index.html

test: clean
	cd tests && $(CC) $(CC_FLAGS) $(COVERAGE_FLAGS) *.cc $(FILES) -o test $(TEST_FLAGS)
	./tests/test

gcov_report : test
	gcovr -r . --html-details -o tests/test_list.html
	open tests/test_list.html

clang:
	clang-format -style="{BasedOnStyle: Google}" -i app_src/model/* app_src/controller/* app_src/view/*.cc app_src/view/*.h tests/*.cc app_src/external/*.h app_src/main.cc

check_clang:
	clang-format -style="{BasedOnStyle: Google}" -n app_src/model/* app_src/controller/* app_src/view/*.cc app_src/view/*.h tests/*.cc app_src/external/*.h app_src/main.cc

val: clean
	cd tests && $(CC) $(CC_FLAGS) $(COVERAGE_FLAGS) *.cc $(FILES) -o test $(TEST_FLAGS)
	valgrind --tool=memcheck --leak-check=yes ./tests/test

clean_up:
	cd app_src && make clean && rm -f .qmake.stash && rm -f Makefile
	rm -rf objects

clean:
	- find . -name '*.o' -type f -delete
	- find . -name '*.pro.user*' -type f -delete
	- find . -name '*.gcda*' -type f -delete
	- find . -name '*.gcno*' -type f -delete
	- find . -name '*.a*' -type f -delete
	- find ./tests/ -name '*.css*' -type f -delete
	rm -rf tests/*.html 3dviewer2.tar 3DViewer2 tests/test

cpp_check:
	$(eval SOURCES := $(shell find ./../ -type f \( -name "*.cc" -o -name "*.h" \)))
	cppcheck --enable=all --std=c++17 --language=c++ --suppress=unusedFunction --suppress=missingInclude --suppress=noCopyConstructor --suppress=syntaxError --suppress=knownConditionTrueFalse --suppress=stlOutOfBounds --suppress=noOperatorEq ${SOURCES}
