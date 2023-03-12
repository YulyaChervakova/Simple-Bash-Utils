CC=gcc 
RM=rm -rf
CFLAGS= -Wall -Wextra -Werror
LIB=s21_grep

all : s21_grep s21_test_grep

s21_grep : s21_grep.c
	$(CC) $(CFLAGS) s21_grep.c -o $(LIB)

s21_test_grep: t_grep
	sh t_grep.sh

clean:
	$(RM) *.o
	rm s21_grep t_grep log.txt