CC=g++
#CFLAGS=-Wall -Werror -Wextra -std=c11
CFLAGS= -Wall -Werror -Wextra -std=c++17 -fsanitize=address
GCOVFLAGS =--coverage
LIBS=-lgtest -lstdc++
#TEST_LIBS = -lcheck -lm -lpthread
OS = $(shell uname)
#TEST_FILE_NAME = test.c
ifeq ($(OS), Darwin)
	LIBS=-lgtest
else
	LIBS=-lgtest -lrt -lm -lpthread 
endif
TEST_FUNC =model/s21_credits.cc model/s21_val.cc model/s21_sort.cc model/s21_calc.cc model/s21_deposid.cc

all: clean s21_calc.a

s21_calc.a:

	$(CC) $(CFLAGS) -c $(TEST_FUNC)
	ar rc s21_calc.a *.o
	ranlib s21_calc.a

tests: s21_calc.a

	$(CC) $(CFLAGS) $(LIBS) s21_calc.a tests.cc -o ./s21_calc
	./s21_calc

gcov_report: tests
	$(CC) $(CFLAGS) $(GCOVFLAGS) $(LIBS) $(TEST_FUNC) tests.cc -o gcov_test
	rm -rf u*.gcno
	rm -rf u*.gcda
	rm -rf u*.gcov
	chmod +x *
	./gcov_test
	gcov s21_*.gcda
	rm -rf u*.gcda
	gcovr -b
	gcovr
	gcovr --html-details -o report.html
	lcov -t "test_calc"  -o report.info -c -d .
	genhtml -o report report.info
	open ./report/index.html

clean:
	rm -rf s21_calc
	rm -rf *.o
	rm -rf *.a
	rm -rf *.gcno
	rm -rf *.gcda
	rm -rf *.gcov
	rm -rf *.info
	rm -rf *.html
	rm -rf *.css
	rm -rf test
	rm -rf gcov_test

style:
	clang-format -style=google -n */*.cpp
	clang-format -style=google -n */*.cc
	clang-format -style=google -n */*.h
	clang-format -style=google -n *.cc
style_i:
	clang-format -style=google -i */*.cpp
	clang-format -style=google -i */*.cc
	clang-format -style=google -i */*.h
	clang-format -style=google -i *.cc
valgrind: s21_calc.a
	CK=FORK=no valgrind --trace-children=yes --track-origins=yes --show-leak-kinds=all --verbose --log-file=RESULT_VALGRIND.txt ./s21_calc
lik: s21_calc.a
	CK_FORK=no leaks -fullStacks -atExit -- ./s21_calc
rebuild: clean all
install:
	mkdir build
	cd untitled && qmake && make && make clean && mv untitled.app ../build/SmartCalc.app && rm -rf untitled.app
uninstall:
	rm -rf build
open:
	cd build && open SmartCalc.app
dist:
	rm -rf Archive_SmartCalc_v1.0/
	mkdir Archive_SmartCalc_v1.0/
	mkdir Archive_SmartCalc_v1.0/src
	mv ./build/SmartCalc.app Archive_SmartCalc_v1.0/src/
	tar cvzf Archive_SmartCalc_v1.0.tgz Archive_SmartCalc_v1.0/
	rm -rf Archive_SmartCalc_v1.0/


dvi: description.md
ifeq ($(OS), Darwin)
	open description.md
else
	cat description.md
endif

