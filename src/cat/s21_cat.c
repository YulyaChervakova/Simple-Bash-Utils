#include "s21_cat.h"

int main(int argc, char *argv[]) {
    s21_flagCat *tab = S21_NULL;
    tab = calloc(1, sizeof(s21_flagCat));
    if (tab != S21_NULL && argc > 1) {
        s21_cat(argv, argc, tab);
    }
    free(tab);
return 0;
}

s21_flagCat* s21_tab_null(s21_flagCat* tab) {
    tab->b = 0;
    tab->e = 0;
    tab->E = 0;
    tab->n = 0;
    tab->s = 0;
    tab->t = 0;
    tab->T = 0;
    tab->f = 0;
    tab->error = 0;
    tab->v = 0;
return tab;
}

s21_flagCat* s21_flag_filli(char** argv, int argc, s21_flagCat* tab) {
    int count = 0;
    int countArg = 0;
    #if __linux__
    char *numberNo = "--number-nonblank";
    char *numberflag = "--number";
    char *squeezze = "--squeeze-blank";
    #endif  // __linux__
    for (int i = 1; i < argc; i++) {
        if (tab->f == 0) {
            count = 0;
            countArg = 0;
            while (argv[i][count]) {
                if (argv[i][count] == '-' || countArg == 1) {
                    countArg = 1;
                    if (argv[i][count] == '-')
                    count++;
                    switch (argv[i][count]) {
                        case 'b':
                            tab->b = 1;
                            break;
                        case 'e':
                            tab->e = 1;
                            break;
                        case 'n':
                            tab->n = 1;
                            break;
                        case 's':
                            tab->s = 1;
                            break;
                        case 't':
                            tab->t = 1;
                            break;
                        case 'v':
                            tab->v = 1;
                            break;
                        #if __linux__
                        case 'E':
                            tab->E = 1;
                            break;
                        case 'T':
                            tab->T = 1;
                            break;
                        case '-':
                            if (strcmp(argv[i], numberNo) == 0) {
                                tab->b = 1;
                                count = count+15;
                            } else {
                                if (strcmp(argv[i], numberflag) == 0) {
                                    tab->n = 1;
                                    count = count+6;
                                } else {
                                    if (strcmp(argv[i], squeezze) == 0) {
                                        tab->s = 1;
                                        count = count+13;
                                    } else {
                                        tab->error = tab->error + 1;
                                    }
                                }
                            }
                            break;
                        #endif  // __linux__
                        default:
                            tab->error = tab->error + 1;
                            break;
                    }

                } else {
                    tab->f = tab->f+1;
                    break;
                }
                count++;
            }
        } else {
            tab->f = tab->f+1;
        }
    }
return tab;
}
int s21_flag_b(int numberStr) {
printf("%6d\t", numberStr);
numberStr++;
return numberStr;
}
int s21_flag_n(int numberStr) {
printf("%6d\t", numberStr);
numberStr++;
return numberStr;
}
int s21_flag_t(int number) {
printf("^");
number = 73;
return number;
}

int s21_flag_v(int number) {
    if (number >= 0 && number <= 31 && number != 10 && number != 9) {
        number = number + 64;
        printf("^");
    }
    if (number == 127) {
        number = number - 64;
        printf("^");
    }
return number;
}

void s21_flag_e() {
printf("$\n");
}

void s21_cat(char** argv, int argc, s21_flagCat* tab) {
    s21_tab_null(tab);
    s21_flag_filli(argv, argc, tab);
    int numberStr = 1;
    int next = 0;
    int nextEmpty = 0;
    int number;
    if (tab->f > 0 && tab->error == 0) {
        FILE *file;
        for (int i = argc - tab->f; i < argc; i++) {
            if ((file = fopen(argv[i], "r")) != NULL) {
                #if __APPLE__
                numberStr = 1;
                #endif  // __APPLE__
                while ((number = fgetc(file))!= EOF) {
                    if (tab->s == 1 && next == 0 && number == 10) {
                        if (nextEmpty == 0) {
                            if (tab->b == 0 && tab->n == 1) {
                                numberStr = s21_flag_n(numberStr);
                        if (((tab->e == 1) || tab->E == 1) && number == 10) {
                                        s21_flag_e();
                                    } else {
                                        printf("%c", number);
                                    }
                            } else {
                    if (((tab->e == 1) || tab->E == 1) && number == 10) {
                                    s21_flag_e();
                                } else {
                                    printf("%c", number);
                                }
                            }
                        }
                        nextEmpty++;
                        continue;
                    }
                    if (tab->b == 1 && next == 0 && number != 10)
                       numberStr = s21_flag_b(numberStr);
                    if (tab->b == 0 && tab->n == 1 && next == 0)
                       numberStr = s21_flag_n(numberStr);
                    if (((tab->e == 1 || tab->t == 1)) || tab->v == 1)
                        number = s21_flag_v(number);
                    if (((tab->t == 1) || tab->T == 1) && number == 9)
                        number = s21_flag_t(number);
                    if (((tab->e == 1) || tab->E == 1) && number == 10) {
                        number = s21_flag_v(number);
                        s21_flag_e();
                    } else {
                        printf("%c", number);
                    }
                    if (number != 10) {
                        next++;
                    } else {
                        next = 0;
                    }
                    nextEmpty = 0;
                }
                fclose(file);
            }
        }
    }
}
