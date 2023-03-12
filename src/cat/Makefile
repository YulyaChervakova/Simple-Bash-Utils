CC=gcc
RM=rm -rf
CFLAGS= -Wall -Wextra -Werror
LIB=s21_cat

all : $(LIB) test

$(LIB) : s21_cat.c
	$(CC) $(CFLAGS) s21_cat.c -o $(LIB)

test: t_cat.sh
	sh t_cat.sh

clean:
	$(RM) *.o
	rm log.txt s21_cat 
