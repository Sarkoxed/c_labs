testcase = 20

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

.PHONY: extra
extra: ex_task/*.c ex_task/*.h
	@$(CC) $(ASANFLAGS) $(CFLAGS) $(DEBUGFLAGS) ex_task/*.c -o extra.out $(LIBS)

.PHONY: clean
clean:
	@echo Deleting *.out *.o bin textfiles
	-@rm *.out 2>/dev/null || true
	-@rm *.o 2>/dev/null || true
	-@rm logs/* 2>/dev/null || true
	-@rm core.* 2>/dev/null || true
	-@rm -r fuzzing/sync/* 2>/dev/null || true
	-@rm *_tree* || true
	-@rm *.txt || true
	-@rm Task || true
	-@rm check_extra || true

.PHONY: afl-build
afl-build: src/*.c src/*.h
	afl-gcc $(AFLFLAGS) $(CFLAGS) src/*.c -o fuzz.out $(LIBS)

fuzz.out: afl-build

.PHONY: afl-start
afl-start: fuzz.out
	afl-fuzz -i fuzzing/in -o fuzzing/sync -M fuzz1 -- ./fuzz.out

asan.out: sanitize


.PHONY: extra
extra: ex_task/*.c ex_task/*.h test
	@$(CC) $(ASANFLAGS) $(CFLAGS) $(DEBUGFLAGS) ex_task/*.c -o extra.out $(LIBS)
	@$(CC) -o check_extra check_task.c
.PHONY: test
test:
	@printf "Making binary file with unsigned integers...\n"
	@printf "#!/home/sarkoxedaf/anaconda3/bin/python\nfrom random import randint\nfor i in range($(testcase)):\n    print(randint(0, 100))\nprint(-1)" > test.py
	@printf "#include <stdio.h>\nint main(){\nint n;\nFILE *fp = fopen(\"Task\", \"w+b\");\nFILE *fk = fopen(\"lol\", \"r+t\");\nfscanf(fk,\"" > test.c
	@echo '%d",&n);\n' >> test.c
	@printf "while(n + 1){fwrite(&n, sizeof(unsigned), 1, fp);\nfscanf(fk,\"" >> test.c
	@echo '%d",&n);\n' >> test.c
	@printf "}\n fclose(fp);\nfclose(fk);\nreturn 0;\n}" >> test.c
	@$(CC) -o task test.c
	@chmod +x test.py
	@./test.py > lol
	@cat lol | ./task
	@printf "Done\n"
	@rm test.c test.py task lol
