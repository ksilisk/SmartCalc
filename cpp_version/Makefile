CC := g++
FLAGS := -Wall -Wextra -Werror -std=c++17
DEBUG_FLAGS := -g -fsanitize=address
SOURCE_PATH := backend
GCOVFLAGS := -fprofile-arcs -ftest-coverage
LFLAGS ?= $(shell pkg-config --cflags --libs gtest)

.PHONY: clean

all: clean lib_calc.a

tests:
	$(CC) $(SOURCE_PATH)/*.cpp test/*.cpp $(FLAGS) $(LFLAGS)
	./a.out

lib_calc.a:
	$(CC) $(FLAGS) -c $(SOURCE_PATH)/*.cpp
	ar rc lib_calc.a *.o
	ranlib lib_calc.a
	mv *.o *.a build/

install: uninstall
	@mkdir build
	@make && cd build && cmake ../ui && make
	@open build/SmartCalc.app

uninstall: clean
	rm -rf build

dist: clean
	mkdir Archive_SmartCalc_v1.0
	cp Makefile backend/*.cpp backend/*.hpp ui/*.cpp ui/*.h ui/*.h ui/*.ui Archive_SmartCalc_v1.0/
	tar cvzf Archive_SmartCalc_v1.0.tgz Archive_SmartCalc_v1.0/
	
gcov_report: clean
	$(CC) $(FLAGS) $(LFLAGS) $(GCOVFLAGS) $(SOURCE_PATH)/*.cpp test/*.cpp -o gcov_main
	./gcov_main
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory gcov_report
	open gcov_report/index.html

clean:
	rm -rf *.o *.html *.gcda *.gcno *.a *.css *.gcov *.info *.tgz
	rm -rf *.out *.cfg *.txt gcov_main test_build gcov_report Archive*

dvi:
	doxygen Doxyfile
	open html/index.html
