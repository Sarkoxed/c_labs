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
	@echo "ASAN passed"

.PHONY: clean
clean:
	@echo Deleting *.out *.o bin textfiles
	-@rm *.out 2>/dev/null || true
	-@rm *.o 2>/dev/null || true
	-@rm -r fuzzing/sync/* 2>/dev/null || true
	-@rm *graph* || true

.PHONY: afl-build
afl-build: src/*.c src/*.h
	afl-gcc $(AFLFLAGS) $(CFLAGS) src/*.c -o fuzz.out $(LIBS)

fuzz.out: afl-build

.PHONY: afl-start
afl-start: fuzz.out
	afl-fuzz -i fuzzing/in -o fuzzing/sync -M fuzz1 -- ./fuzz.out

asan.out: sanitize

.PHONY: time
time: src/*.c src/*.h profile/time.c
	@echo Building TIME
	@$(CC) $(DEBUGFLAGS) $(CFLAGS) $(OPT) $(ASANFLAGS) src/lib.c src/tools.c profile/time.c -o time $(LIBS)

