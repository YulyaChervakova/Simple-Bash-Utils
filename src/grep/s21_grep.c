#include "s21_grep.h"

int main(int argc, char *argv[]) {
    s21_flagGrep* tab = S21_NULL;
    tab = calloc(1, sizeof(s21_flagGrep));
    if (tab != S21_NULL && argc > 2) {
        tab = s21_tab_null(tab);
        s21_grep(argv, argc, tab);
    }
        free(tab);
return 0;
}

s21_flagGrep* s21_tab_null(s21_flagGrep* tab) {
    for (int i = 0; i < 1024; i++) {
        tab->ePost[i] = 0;
        tab->eNext[i] = 0;
        if (i < 100)
        tab->file[i] = 1;
    }
    tab->eP = 0;
    tab->eN = 0;
    tab->i = 0;
    tab->v = 0;
    tab->l = 0;
    tab->c = 0;
    tab->n = 0;
    tab->f = 0;
    tab->tempLate = 0;
    tab->error = 0;
return tab;
}

s21_struct* s21_save_null(s21_struct* save ) {
    for (int i = 0; i < 1000; i++) {
        save->strNumber[i] = -1;
    }
    save->strMax = 0;
    save->strMin = 0;
return save;
}

int s21_tab_No_Null(s21_flagGrep* tab) {
int i = 0;
if (tab->error == 0) {
    i = 1;
}
return i;
}
void s21_flag_fillin(char** argv, int argc, s21_flagGrep* tab) {
    size_t count = 0;
    int count2 = 0;
    int j = 0;
    int countArg = 0;
    for (int i = 1; i < argc; i++) {
        count = 0;
        countArg = 0;
            while (argv[i][count] && countArg != 2 && tab->error == 0) {
                if ((argv[i][count] == '-' || countArg == 1) && count == 0) {
                    countArg = 1;
                    if (argv[i][count] == '-')
                    count++;
                    switch (argv[i][count]) {
                        case 'i':
                            tab->i = 1;
                            break;
                        case 'v':
                            tab->v = 1;
                            break;
                        case 'l':
                            tab->l = 1;
                            break;
                        case 'c':
                            tab->c = 1;
                            break;
                        case 'n':
                            tab->n = 1;
                            break;
                        case 'e':
                            if (count + 1 < strlen(argv[i])) {
                                tab->ePost[tab->eP] = i;
                                s21_chenge_arg(argv, tab->ePost[tab->eP]);
                                tab->eP = tab->eP +1;
                                countArg = 2;
                            } else {
                                if (i + 2 < argc || i + 1 < argc) {
                                    tab->eNext[tab->eN] = i+1;
                                    if (i+2 < argc) {
                                        tab->eNext[tab->eN] = i+1;
                                        i = i + 1;
                                    } else {
                                      i = i + 1;
                                    }
                                    countArg = 2;
                                    tab->eN = tab->eN + 1;
                                } else {
                                    tab->error = tab->error + 1;
                                    countArg = 2;
                                }
                            }
                            break;
                        default:
                            tab->error = tab->error + 1;
                            break;
                    }
                } else {
                    if (tab->eP == 0 && tab->eN == 0 && tab->tempLate == 0) {
                        if (tab->f == 0) {
                            if (argv[i+1][0] != '-') {
                                    j = i+1;
                                while (j < argc && argv[j][0] != '-') {
                                    j++;
                                }
                                if (j == argc) {
                                    tab->tempLate = i;
                                    countArg = 2;
                                } else {
                                    j = i+1;
                                    while (j < argc && count2 != -1) {
                                        count2 = 0;
                while (argv[j][count2] && count2 != -1 && argv[j][0] == '-') {
                                            if (argv[j][count2] == 'e') {
                                                count2 = -2;
                                            }
                                            count2++;
                                        }
                                        j++;
                                    }
                                    if (count2 == -1) {
                                        for (; i < j-1; i++) {
                                            tab->file[tab->f] = i;
                                            tab->f = tab->f + 1;
                                        }
                                        i--;
                                        countArg = 2;
                                    } else {
                                        tab->tempLate = i;
                                        countArg = 2;
                                    }
                                }
                            } else {
                                j = i+1;
                                    while (j < argc && count2 != -1) {
                                        count2 = 0;
                while (argv[j][count2] && count2 != -1 && argv[j][0] == '-') {
                                            count2++;
                                            if (argv[j][count2] == 'e') {
                                                count2 = -1;
                                            }
                                        }
                                        j++;
                                    }
                                    if (count2 == -1) {
                                        tab->file[tab->f] = i;
                                        tab->f = tab->f + 1;
                                        countArg = 2;
                                    } else {
                                        tab->tempLate = i;
                                        countArg = 2;
                                    }
                            }
                        }

                    } else {
                    if ((tab->eP >= 1 || tab->eN >= 1) && tab->tempLate != 0) {
                            tab->file[tab->f] = tab->tempLate;
                            tab->f = tab->f + 1;
                            tab->tempLate = 0;
                            countArg = 2;
                        } else {
                            tab->file[tab->f] = i;
                            tab->f = tab->f + 1;
                            countArg = 2;
                        }
                    }
                }
                count++;
            }
    }
}

int s21_i(char c, char m, s21_flagGrep* tab) {
    int flag = 0;
    if (tab->i == 1) {
        if (c > m) {
            if ( m+64 == c ) {
                flag = 1;
            }
        } else {
            if (c < m) {
                if (c+64 == m) {
                    flag = 1;
                }
            } else {
                flag = 1;
            }
        }
    } else {
        if (c == m) {
            flag = 1;
        }
    }
return flag;
}

int s21_coincidences(char** argv, s21_flagGrep* tab, FILE* file,
s21_struct* save) {
int flag = 0;
char * mas = S21_NULL;
size_t i = 0;
int j = 0;
mas = calloc(1, sizeof(char));
    if (mas != S21_NULL) {
        while ((getline(&mas, &i, file))!= EOF) {
                save->strMax = save->strMax + 1;
                    if (tab->tempLate > 0) {
                        s21_overlap(save, tab, argv , mas, tab->tempLate);
                    } else {
                        if ( tab->eP != 0 ) {
                            j = 0;
                            flag = 0;
                            while (j < tab->eP && flag == 0) {
                    flag = s21_overlap(save, tab, argv, mas, tab->ePost[j]);
                                j++;
                            }
                            if ( tab->eN != 0 && flag == 0 ) {
                                j = 0;
                                flag = 0;
                                while (j < tab->eN && flag == 0) {
                    flag = s21_overlap(save, tab, argv, mas, tab->eNext[j]);
                                    j++;
                                }
                            }
                        } else {
                            if ( tab->eN != 0 ) {
                                j = 0;
                                flag = 0;
                                while (j < tab->eN && flag == 0) {
                        flag = s21_overlap(save, tab, argv, mas, tab->eNext[j]);
                                    j++;
                                }
                            }
                        }
                    }
        }
    }
if (save->strMin > 0) {
    flag = 1;
} else {
    flag = 0;
}
        free(mas);
return flag;
}

int s21_overlap(s21_struct* save, s21_flagGrep* tab, char** argv,
char* mas, int number) {
    int flag = 0;
    regex_t preg;
    regmatch_t pm;
        if (tab->i == 0 && regcomp(&preg, argv[number], REG_EXTENDED) == 0) {
            if (regexec(&preg, mas, 0, &pm, 0) == 0) {
                save->strNumber[save->strMin] = save->strMax-1;
                save->strMin++;
                flag = 1;
            }
        } else {
            if (tab->i == 1 && regcomp(&preg, argv[number], REG_ICASE) == 0) {
                if (regexec(&preg, mas, 0, &pm, 0) == 0) {
                    save->strNumber[save->strMin] = save->strMax-1;
                    save->strMin++;
                    flag = 1;
                }
            } else {
                if (strstr(mas, argv[number])) {
                    flag = 1;
                }
            }
        }
    regfree(&preg);
    return flag;
}

void s21_chenge_arg(char** argv, int number) {
    int i = 0;
    int j = 0;
    char* mas = S21_NULL;
    mas = calloc(100, sizeof(char));
    while (argv[number][i] != 'e') {
        i++;
    }
    i++;
    while (argv[number][i]) {
        mas[j] = argv[number][i];
        i++;
        j++;
    }
    argv[number] = mas;
    if (mas != S21_NULL)
    free(mas);
}

void s21_grep(char** argv, int argc, s21_flagGrep* tab) {
    s21_flag_fillin(argv, argc, tab);
    s21_struct* save = S21_NULL;
    save = calloc(1, sizeof(s21_struct));
    s21_save_null(save);
    if (s21_tab_No_Null(tab) && save != S21_NULL) {
        FILE *file = S21_NULL;
        for (int i = 0; i < tab->f; i++) {
            if ((file = fopen(argv[tab->file[i]], "r")) != NULL) {
                if (s21_coincidences(argv, tab, file, save)) {
                    rewind(file);
                    searchIzi(save, tab, file, argv, i);
                } else {
                    rewind(file);
                    searchNotIzi(save, tab, file, argv, i);
                }
                s21_save_null(save);
                fclose(file);
            }
        }
    }
    free(save);
}

void tab_v(s21_struct* save, FILE* file, int fileNumber, char* nameFile) {
    int number = 0;
    char* mas = S21_NULL;
    size_t i = 0;
    int j = 0;
    int k = 0;
    mas = calloc(1, sizeof(char));
    if (mas != S21_NULL) {
        while ((getline(&mas, &i, file))!= EOF) {
            if (fileNumber > 1) {
                if (number != save->strNumber[j]) {
                    k++;
                    printf("%s:%s", nameFile, mas);
                } else {
                    if (j < save->strMin) {
                        j++;
                    }
                }
            } else {
                if (number != save->strNumber[j]) {
                    k++;
                    printf("%s", mas);
                } else {
                    if (j < save->strMin) {
                        j++;
                        }
                    }
            }
            number++;
        }
    }
    free(mas);
    if (k > 0)
    printf("\n");
}

void tab_c(s21_struct* save, int fileNumber, char* nameFile, int invert) {
    if (fileNumber > 1) {
        if (invert == 0) {
            printf("%s:%d", nameFile, save->strMin);
        }  else {
            printf("%s:%d", nameFile, save->strMax-save->strMin);
        }
    } else {
        if (invert == 0) {
            printf("%d", save->strMin);
        } else {
            printf("%d", save->strMax-save->strMin);
        }
    }
}

void tab_i(s21_struct* save, FILE* file, int fileNumber, char* nameFile) {
    int number = 0;
    char* mas = S21_NULL;
    size_t i = 0;
    int j = 0;
    mas = calloc(1, sizeof(char));
    if (mas != S21_NULL) {
        while ((getline(&mas, &i, file))!= EOF) {
            if (fileNumber > 1) {
                if (number == save->strNumber[j] && j < save->strMin) {
                    printf("%s:%s", nameFile, mas);
                    j++;
                }
            } else {
              if (number == save->strNumber[j] && j < save->strMin) {
                    printf("%s",  mas);
                    j++;
                }
            }
            number++;
        }
    }
    free(mas);
}
void tab_n(s21_struct* save, FILE* file, int fileNumber, char* nameFile) {
    int number = 0;
    char* mas = S21_NULL;
    size_t i = 0;
    int j = 0;
    mas = calloc(1, sizeof(char));
    if (mas != S21_NULL) {
        while ((getline(&mas, &i, file))!= EOF) {
            if (fileNumber > 1) {
                if (number == save->strNumber[j] && j < save->strMin) {
                    printf("%s:%d:%s", nameFile, save->strNumber[j]+1, mas);
                    j++;
                }
            } else {
              if (number == save->strNumber[j] && j < save->strMin) {
                    printf("%d:%s", save->strNumber[j]+1, mas);
                    j++;
                }
            }
            number++;
        }
    }
    free(mas);
}

void tab_l(s21_struct* save, int fileNumber, char* nameFile) {
    if (fileNumber >= 1 && save->strMin > 0) {
        printf("%s\n", nameFile);
    }
}

void searchIzi(s21_struct* save, s21_flagGrep* tab,
FILE* file, char** argv, int i) {
     if (tab->l == 1) {
        if (tab->c == 1) {
            if (save->strMin > 0) {
                if (tab->f > 1) {
                    printf("%s:1\n", argv[tab->file[i]]);
                } else {
                        printf("1\n");
                        }
            } else {
                if (tab->f > 1) {
                    printf("%s:0\n", argv[tab->file[i]]);
                } else {
                    printf("0\n");
                    }
                }
        }
        tab_l(save, tab->f, argv[tab->file[i]]);
    } else {
            if (tab->v == 1) {
                if (tab->c == 1) {
                    tab_c(save, tab->f, argv[tab->file[i]], 1);
                        printf("\n");
                } else {
                    tab_v(save, file, tab->f, argv[tab->file[i]]);
                }
            } else {
                    if (tab->n == 1) {
                        tab_n(save, file, tab->f, argv[tab->file[i]]);
                    } else {
                            if (tab->c == 1) {
                                tab_c(save, tab->f, argv[tab->file[i]], 0);
                                printf("\n");
                            } else {
                                tab_i(save, file, tab->f, argv[tab->file[i]]);
                            }
                    }
            }
    }
}

void searchNotIzi(s21_struct* save, s21_flagGrep* tab,
FILE* file, char** argv, int i) {
int k = 0;
    if (tab->l == 1) {
        if (tab->c == 1) {
            if (tab->v == 1)
            k = 1;
            if (k == 1) {
                if (tab->f > 1) {
                    printf("%s:1\n", argv[tab->file[i]]);
                } else {
                        printf("1\n");
                        }
            } else {
                    if (tab->f > 1) {
                        printf("%s:0\n", argv[tab->file[i]]);
                    } else {
                            printf("0\n");
                    }
            }
        }
    if (tab->v == 1)
    printf("%s\n", argv[tab->file[i]]);
    } else {
        if (tab->c == 1) {
            tab_c(save, tab->f, argv[tab->file[i]], 1);
            printf("\n");
        } else {
                if (tab->v == 1) {
                    tab_v(save, file, tab->f, argv[tab->file[i]]);
                }
                if (tab->i == 1 || tab->eP == 1 || tab->eN == 1) {
                    tab_i(save, file, tab->f, argv[tab->file[i]]);
                }
                if (tab->n == 1) {
                    tab_n(save, file, tab->f, argv[tab->file[i]]);
                }
        }
    }
}
