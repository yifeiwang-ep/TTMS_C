#!Makefile

PROGRAM = TTMS

C_SOURCES = $(shell find . -name "*.c")
C_OBJECTS = $(patsubst %.c, %.o, $(C_SOURCES))

CC = gcc

C_FLAGS = -DDEBUG -c -Wall -Wextra -ggdb -I.

all: $(C_OBJECTS) 
	@echo compile...
	$(CC) $(C_OBJECTS) -lm -o   $(PROGRAM) `pkg-config --cflags --libs gtk+-2.0`

.c.o:
	@echo link$< ...
	$(CC) $(C_FLAGS) $< -o $@ `pkg-config --cflags --libs gtk+-2.0` 

.PHONY:clean
clean:
	$(RM) $(C_OBJECTS) TTMS

