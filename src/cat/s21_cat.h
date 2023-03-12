#ifndef _S21_CAT_H_
#define _S21_CAT_H_
#define S21_NULL ((void*)0)

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#define S21_NULL ((void*)0)

typedef struct s_cat {
  int b;
  int e;
  int E;
  int n;
  int s;
  int t;
  int T;
  int f;
  int v;
  int error;
} s21_flagCat;

s21_flagCat* s21_tab_null(s21_flagCat* tab);
s21_flagCat* s21_flag_filli(char** argv, int argc, s21_flagCat* tab);
int s21_flag_b(int numberStr);
int s21_flag_n(int numberStr);
int s21_flag_t(int number);
int s21_flag_v(int number);
void s21_flag_e();
void s21_cat(char** argv, int argc, s21_flagCat* tab);

#endif  // _S21_CAT_H_