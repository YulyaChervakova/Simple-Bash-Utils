#ifndef _S21_GREP_H_
#define _S21_GREP_H_
#define S21_NULL ((void*)0)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<regex.h>
typedef struct s_grep {
  int ePost[1024];
  int eNext[1024];
  int eP;
  int eN;
  int i;
  int v;
  int l;
  int c;
  int n;
  int f;
  int file[100];
  int tempLate;
  int error;
} s21_flagGrep;

typedef struct s_coincidences {
  int strNumber[10000];
  int strMax;
  int strMin;
} s21_struct;

s21_struct* s21_save_null(s21_struct* save);
s21_flagGrep* s21_tab_null(s21_flagGrep* tab);
int s21_tab_No_Null(s21_flagGrep* tab);

void s21_flag_fillin(char** argv, int argc, s21_flagGrep* tab);
int s21_i(char c, char m, s21_flagGrep* tab);
int s21_coincidences(char** argv, s21_flagGrep* tab, FILE* file, s21_struct* save);
int s21_overlap(s21_struct* save, s21_flagGrep* tab, char** argv, char* mas, int number);
void s21_chenge_arg(char** argv, int number);
void tab_v(s21_struct* save, FILE* file, int fileNumber, char* nameFile);
void tab_c(s21_struct* save, int fileNumber, char* nameFile, int invert);
void tab_i(s21_struct* save, FILE* file, int fileNumber, char* nameFile);
void tab_n(s21_struct* save, FILE* file, int fileNumber, char* nameFile);
void tab_l(s21_struct* save, int fileNumber, char* nameFile);
void s21_grep(char** argv, int argc, s21_flagGrep* tab);
void searchIzi(s21_struct* save, s21_flagGrep* tab,  FILE* file, char** argv, int i);
void searchNotIzi(s21_struct* save, s21_flagGrep* tab,  FILE* file, char** argv, int i);
#endif  // _S21_GREP_H_