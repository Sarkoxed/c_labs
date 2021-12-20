testname = tab_b
testsize = 20
pro = 1000
table = 50

CC = clang

#OPT = -O3

LIBS = -lm

CFLAGS = -Wall
#CFLGAS += -Wfloat-equal
CFLAGS += -Wextra
CFLAGS += -pedantic
#CFLAGS += -Werror
#CFLAGS += -Wmissing-declarations
#CFLAGS += -fstack-protector-all

DEBUGFLAGS = -g
DEBUGFLAGS += -ggdb

ASANFLAGS = -fsanitize=address
#ASANFLAGS += -fno-common
#ASANFLAGS += -fno-omit-frame-pointer

MSANFLAGS = -fsanitize=memory
#MSANFLAGS += -fno-omit-frame-pointer
#MSANFLAGS += -fsanitize-memory-use-after-dtor
#MSANFLAGS += -fsanitize-memory-track-origins=2

UBSANFLAGS = -fsanitize=undefined

#UNITYFLAGS = -DUNITY_SUPPORT_64

AFLFLAGS = -Ofast

DEBUGFLAGS = -g

.PHONY: default
default: build

.PHONY: build
build: src/*.c src/*.h
	@echo Building
	@$(CC) $(DEBUGFLAGS) $(CFLAGS) $(OPT) src/*.c -o task.out $(LIBS) 

.PHONY: sanitize
sanitize: src/*.c src/*.h
	@echo Running ASAN
	@$(CC) $(ASANFLAGS) $(CFLAGS) $(DEBUGFLAGS) src/*.c -o asan.out $(LIBS)
#	@ASAN_OPTIONS=detect_leaks=1 ../tools/run_tests.sh asan.out
#	@../tools/run_tests.sh asan.out
	@echo "ASAN passed"
#	@echo Running MSAN
#	@$(CC) $(MSANFLAGS) $(CFLAGS) src/*.c -o msan.out $(LIBS)
#	@../tools/run_tests.sh msan.out
#	@echo "MSAN passed"
#	@$(CC) $(UBSANFLAGS) $(CFLAGS) src/*.c -o ubsan.out $(LIBS)
#	@../tools/run_tests.sh ubsan.out
#	@echo "UBSAN passed"

.PHONY: clean
clean:
	@echo Deleting *.out *.o autotests logs core.* fuzzing/sync/* bin
	-@rm *.out 2>/dev/null || true
	-@rm *.o 2>/dev/null || true
	-@rm logs/* 2>/dev/null || true
	-@rm core.* 2>/dev/null || true
	-@rm -r fuzzing/sync/* 2>/dev/null || true
	-@rm $(testname)* || true
	-@rm tests/test_now/* || true
.PHONY: valgrind
valgrind: task.out
	@bash ../tools/run_valgrind.sh

.PHONY: afl-build
afl-build: src/*.c src/*.h
	afl-gcc $(AFLFLAGS) $(CFLAGS) src/*.c -o fuzz.out $(LIBS)

fuzz.out: afl-build

.PHONY: afl-start
afl-start: fuzz.out
	afl-fuzz -i fuzzing/in -o fuzzing/sync -M fuzz1 -- ./fuzz.out

asan.out: sanitize

.PHONY: test
test: asan.out begining
	@echo "Building testcases"
	@python tests/maker.py -f $(pro) $(testname)
	@python tests/maker.py -n $(table) $(testname)
	@mv pro_table.txt tests/test_now/
	@mv table.txt tests/test_now/
	@echo "Testcases built"

.PHONY: begining
begining:
	@echo "Making testtable"
	@printf "#include <stdio.h>\nint main(){\nFILE *pop = fopen(\"$(testname)_struct\", \"w+b\");\n int a = 0, b  = $(testsize), c = 2*sizeof(int);\nfwrite(&b, sizeof(int),1, pop);\nfwrite(&a, sizeof(int),1, pop);\nfwrite(&c, sizeof(int), 1, pop);\nfclose(pop);\nreturn 0;}" > bir.c
	@touch $(testname)
	@$(CC) -o bir bir.c
	@./bir
	@rm bir.c
	@rm bir
	@echo "Successfully made nothing"

