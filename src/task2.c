#include "task2.h"
#define kMAX_COMMAND_SIZE 100
#define KMAX_CHARACTERS 256
#define position_words 5
#define position_second_name 6
#define position_first_note 5
#define position_second_note 6
#define position_third_note 7
#define position_camp 7
#define position_operator 6
#define position_valoare 5
#define position_category 9
#define precision 100
#define rounding 0.5f
#define kMAX_STUDENTS 201

float rotunjire(float x) {
    int nr = (int)(x * precision + rounding);
    return (float)nr / 100.0f;
}

void recalculeaza_medii_generale(secretariat *s) {
    float suma_note[kMAX_STUDENTS] = {0};
    int cnt_materii[kMAX_STUDENTS] = {0};
    int studenti_activi[kMAX_STUDENTS] = {0};
    for (int i = 0; i < s->nr_studenti; i++) {
        studenti_activi[s->studenti[i].id] = 1;
    }
    for (int i = 0; i < s->nr_inrolari; i++) {
        int id_student = s->inrolari[i].id_student;
        suma_note[id_student] += s->inrolari[i].note[0] + s->inrolari[i].note[1] + s->inrolari[i].note[2];
        cnt_materii[id_student]++;
    }
    for (int i = 0; i < s->nr_studenti; i++) {
        suma_note[i] = rotunjire(suma_note[i]);
    }
    for (int i = 0; i < s->nr_studenti; i++) {
        if (studenti_activi[s->studenti[i].id]) {
            if (cnt_materii[s->studenti[i].id] > 0) {
                s->studenti[i].medie_generala = (float)suma_note[s->studenti[i].id] /
                (float)cnt_materii[s->studenti[i].id];
            } else {
                s->studenti[i].medie_generala = (float)0.00;
            }
            s->studenti[i].medie_generala = rotunjire(s->studenti[i].medie_generala);
        }
    }
}



int verifica_int(int valoare1, int valoare2, const char *operator) {
    if (strcmp(operator, "=") == 0) return valoare1 == valoare2;
    if (strcmp(operator, "<") == 0) return valoare1 < valoare2;
    if (strcmp(operator, ">") == 0) return valoare1 > valoare2;
    if (strcmp(operator, "<=") == 0) return valoare1 <= valoare2;
    if (strcmp(operator, ">=") == 0) return valoare1 >= valoare2;
    if (strcmp(operator, "!=") == 0) return valoare1 != valoare2;
    return 0;
}

int verifica_float(float valoare1, float valoare2, const char *operator) {
    if (strcmp(operator, "=") == 0) return valoare1 == valoare2;
    if (strcmp(operator, "<") == 0) return valoare1 < valoare2;
    if (strcmp(operator, ">") == 0) return valoare1 > valoare2;
    if (strcmp(operator, "<=") == 0) return valoare1 <= valoare2;
    if (strcmp(operator, ">=") == 0) return valoare1 >= valoare2;
    if (strcmp(operator, "!=") == 0) return valoare1 != valoare2;
    return 0;
}

int verifica_char(const char *valoare1, const char *valoare2, const char *operator) {
    if (strcmp(operator, "=") == 0) return strcmp(valoare1, valoare2) == 0;
    if (strcmp(operator, "!=") == 0) return strcmp(valoare1, valoare2) != 0;
    return 0;
}

void apply_simple_select(secretariat *s, char selected_words[][KMAX_CHARACTERS],
                         const char *entity_type, int selected_count) {
    int j = 0, m = 0;
    if (strcmp(entity_type, "studenti") == 0) {
        for (j = 0; j < s->nr_studenti; j++) {
            if (strcmp(selected_words[0], "*") == 0) {
                printf("%d %s %d %c %.2f\n", s->studenti[j].id, s->studenti[j].nume,
                       s->studenti[j].an_studiu, s->studenti[j].statut, s->studenti[j].medie_generala);
            } else {
                int first = 1;
                for (m = 0; m < selected_count; m++) {
                    if (!first) printf(" ");
                    first = 0;
                    if (strcmp(selected_words[m], "nume") == 0)
                        printf("%s", s->studenti[j].nume);
                    else if (strcmp(selected_words[m], "id") == 0)
                        printf("%d", s->studenti[j].id);
                    else if (strcmp(selected_words[m], "an_studiu") == 0)
                        printf("%d", s->studenti[j].an_studiu);
                    else if (strcmp(selected_words[m], "statut") == 0)
                        printf("%c", s->studenti[j].statut);
                    else if (strcmp(selected_words[m], "medie_generala") == 0)
                        printf("%.2f", s->studenti[j].medie_generala);
                }
                printf("\n");
            }
        }
    } else if (strcmp(entity_type, "materii") == 0) {
        for (j = 0; j < s->nr_materii; j++) {
            if (strcmp(selected_words[0], "*") == 0) {
                printf("%d %s %s\n", s->materii[j].id, s->materii[j].nume, s->materii[j].nume_titular);
            } else {
                int first = 1;
                for (m = 0; m < selected_count; m++) {
                    if (!first) printf(" ");
                    first = 0;

                    if (strcmp(selected_words[m], "id") == 0)
                        printf("%d", s->materii[j].id);
                    else if (strcmp(selected_words[m], "nume") == 0)
                        printf("%s", s->materii[j].nume);
                    else if (strcmp(selected_words[m], "nume_titular") == 0)
                        printf("%s", s->materii[j].nume_titular);
                }
                printf("\n");
            }
        }
    } else if (strcmp(entity_type, "inrolari") == 0) {
        for (j = 0; j < s->nr_inrolari; j++) {
            if (strcmp(selected_words[0], "*") == 0) {
                printf("%d %d %.2f %.2f %.2f\n", s->inrolari[j].id_student,
                       s->inrolari[j].id_materie, s->inrolari[j].note[0],
                       s->inrolari[j].note[1], s->inrolari[j].note[2]);
            } else {
                int first = 1;
                for (m = 0; m < selected_count; m++) {
                    if (!first) printf(" ");
                    first = 0;
                    if (strcmp(selected_words[m], "id_student") == 0)
                        printf("%d", s->inrolari[j].id_student);
                    else if (strcmp(selected_words[m], "id_materie") == 0)
                        printf("%d", s->inrolari[j].id_materie);
                    else if (strcmp(selected_words[m], "note") == 0)
                        printf("%.2f %.2f %.2f", s->inrolari[j].note[0],
                               s->inrolari[j].note[1], s->inrolari[j].note[2]);
                }
                printf("\n");
            }
        }
    } else {
        printf("Entitate necunoscuta: %s\n", entity_type);
    }
}

void apply_simple_filter(secretariat *s, char selected_words[][KMAX_CHARACTERS],
                         const char *entity_type, int selected_count, const char *camp,
                         const char *operator, const char *valoare) {
    int j = 0, m = 0;

    if (strcmp(entity_type, "studenti") == 0) {
        for (j = 0; j < s->nr_studenti; j++) {
            int se_afiseaza = 0;

            if (strcmp(camp, "id") == 0)
                se_afiseaza = verifica_int(s->studenti[j].id, atoi(valoare), operator);
            else if (strcmp(camp, "medie_generala") == 0)
                se_afiseaza = verifica_float(s->studenti[j].medie_generala, (float)atof(valoare), operator);
            else if (strcmp(camp, "an_studiu") == 0)
                se_afiseaza = verifica_int(s->studenti[j].an_studiu, atoi(valoare), operator);
            else if (strcmp(camp, "nume") == 0)
                se_afiseaza = verifica_char(s->studenti[j].nume, valoare, operator);
            else if (strcmp(camp, "statut") == 0)
                se_afiseaza = verifica_char(&s->studenti[j].statut, valoare, operator);

            if (se_afiseaza) {
                if (strcmp(selected_words[0], "*") == 0) {
                    printf("%d %s %d %c %.2f\n", s->studenti[j].id, s->studenti[j].nume,
                           s->studenti[j].an_studiu, s->studenti[j].statut, s->studenti[j].medie_generala);
                } else {
                    int first = 1;
                    for (m = 0; m < selected_count; m++) {
                        if (!first) printf(" ");
                        first = 0;

                        if (strcmp(selected_words[m], "id") == 0)
                            printf("%d", s->studenti[j].id);
                        else if (strcmp(selected_words[m], "nume") == 0)
                            printf("%s", s->studenti[j].nume);
                        else if (strcmp(selected_words[m], "an_studiu") == 0)
                            printf("%d", s->studenti[j].an_studiu);
                        else if (strcmp(selected_words[m], "statut") == 0)
                            printf("%c", s->studenti[j].statut);
                        else if (strcmp(selected_words[m], "medie_generala") == 0)
                            printf("%.2f", s->studenti[j].medie_generala);
                    }
                    printf("\n");
                }
            }
        }
    } else if (strcmp(entity_type, "materii") == 0) {
        for (j = 0; j < s->nr_materii; j++) {
            int se_afiseaza = 0;

            if (strcmp(camp, "id") == 0)
                se_afiseaza = verifica_int(s->materii[j].id, atoi(valoare), operator);
            else if (strcmp(camp, "nume") == 0)
                se_afiseaza = verifica_char(s->materii[j].nume, valoare, operator);
            else if (strcmp(camp, "nume_titular") == 0)
                se_afiseaza = verifica_char(s->materii[j].nume_titular, valoare, operator);

            if (se_afiseaza) {
                if (strcmp(selected_words[0], "*") == 0) {
                    printf("%d %s %s\n", s->materii[j].id, s->materii[j].nume, s->materii[j].nume_titular);
                } else {
                    int first = 1;
                    for (m = 0; m < selected_count; m++) {
                        if (!first) printf(" ");
                        first = 0;

                        if (strcmp(selected_words[m], "id") == 0)
                            printf("%d", s->materii[j].id);
                        else if (strcmp(selected_words[m], "nume") == 0)
                            printf("%s", s->materii[j].nume);
                        else if (strcmp(selected_words[m], "nume_titular") == 0)
                            printf("%s", s->materii[j].nume_titular);
                    }
                    printf("\n");
                }
            }
        }
    } else if (strcmp(entity_type, "inrolari") == 0) {
        for (j = 0; j < s->nr_inrolari; j++) {
            int se_afiseaza = 0;

            if (strcmp(camp, "id_student") == 0)
                se_afiseaza = verifica_int(s->inrolari[j].id_student, atoi(valoare), operator);
            else if (strcmp(camp, "id_materie") == 0)
                se_afiseaza = verifica_int(s->inrolari[j].id_materie, atoi(valoare), operator);

            if (se_afiseaza) {
                if (strcmp(selected_words[0], "*") == 0) {
                    printf("%d %d %.2f %.2f %.2f\n", s->inrolari[j].id_student, s->inrolari[j].id_materie,
                           s->inrolari[j].note[0], s->inrolari[j].note[1], s->inrolari[j].note[2]);
                } else {
                    int first = 1;
                    for (m = 0; m < selected_count; m++) {
                        if (!first) printf(" ");
                        first = 0;
                        if (strcmp(selected_words[m], "id_student") == 0)
                            printf("%d", s->inrolari[j].id_student);
                        else if (strcmp(selected_words[m], "id_materie") == 0)
                            printf("%d", s->inrolari[j].id_materie);
                        else if (strcmp(selected_words[m], "note") == 0)
                            printf("%.2f %.2f %.2f", s->inrolari[j].note[0],
                               s->inrolari[j].note[1], s->inrolari[j].note[2]);
                    }
                    printf("\n");
                }
            }
        }
    }
}

void apply_complex_filter(secretariat *s, char selected_words[][KMAX_CHARACTERS],
                          const char *entity_type, int selected_count, const char *camp1,
                          const char *operator1, const char *valoare1, const char *camp2,
                          const char *operator2, const char *valoare2) {
    int j = 0, m = 0;
    if (strcmp(entity_type, "studenti") == 0) {
        for (j = 0; j < s->nr_studenti; j++) {
            int se_verifica = 0;
            if (strcmp(camp1, "id") == 0)
                se_verifica = verifica_int(s->studenti[j].id, atoi(valoare1), operator1);
            else if (strcmp(camp1, "medie_generala") == 0)
                se_verifica = verifica_float(s->studenti[j].medie_generala, (float)atof(valoare1), operator1);
            else if (strcmp(camp1, "an_studiu") == 0)
                se_verifica = verifica_int(s->studenti[j].an_studiu, atoi(valoare1), operator1);
            else if (strcmp(camp1, "nume") == 0)
                se_verifica = verifica_char(s->studenti[j].nume, valoare1, operator1);
            else if (strcmp(camp1, "statut") == 0)
                se_verifica = verifica_char(&s->studenti[j].statut, valoare1, operator1);
            if (se_verifica == 1) {
                int se_afiseaza = 0;
                if (strcmp(camp2, "id") == 0) {
                    se_afiseaza = verifica_int(s->studenti[j].id, atoi(valoare2), operator2);
                } else if (strcmp(camp2, "medie_generala") == 0) {
                    se_afiseaza = verifica_float(s->studenti[j].medie_generala, (float)atof(valoare2), operator2);
                } else if (strcmp(camp2, "an_studiu") == 0) {
                    se_afiseaza = verifica_int(s->studenti[j].an_studiu, atoi(valoare2), operator2);
                } else if (strcmp(camp2, "nume") == 0) {
                    se_afiseaza = verifica_char(s->studenti[j].nume, valoare2, operator2);
                } else if (strcmp(camp2, "statut") == 0) {
                     if (s->studenti[j].statut == valoare2[0]) {
                         se_afiseaza = 1;
                     }
                }
                if (se_afiseaza) {
                    int first = 1;
                    for (m = 0; m < selected_count; m++) {
                        if (first) {
                            first = 0;
                        } else {
                            printf(" ");
                        }
                        if (selected_words[0][0] == '*') {
                            printf("%d %s %d %c %.2f", s->studenti[j].id, s->studenti[j].nume,
                                   s->studenti[j].an_studiu, s->studenti[j].statut, s->studenti[j].medie_generala);
                            break;
                        }
                        if (strcmp(selected_words[m], "id") == 0) {
                            printf("%d", s->studenti[j].id);
                        } else if (strcmp(selected_words[m], "nume") == 0) {
                            printf("%s", s->studenti[j].nume);
                        } else if (strcmp(selected_words[m], "an_studiu") == 0) {
                            printf("%d", s->studenti[j].an_studiu);
                        } else if (strcmp(selected_words[m], "statut") == 0) {
                            printf("%c", s->studenti[j].statut);
                        } else if (strcmp(selected_words[m], "medie_generala") == 0) {
                            printf("%.2f", s->studenti[j].medie_generala);
                        }
                    }
                    printf("\n");
                }
            }
        }
    } else if (strcmp(entity_type, "materii") == 0) {
        for (j = 0; j < s->nr_materii; j++) {
            int se_verifica = 0;

            if (strcmp(camp1, "id") == 0)
                se_verifica = verifica_int(s->materii[j].id, atoi(valoare1), operator1);
            else if (strcmp(camp1, "nume") == 0)
                se_verifica = verifica_char(s->materii[j].nume, valoare1, operator1);
            else if (strcmp(camp1, "nume_titular") == 0)
                se_verifica = verifica_char(s->materii[j].nume_titular, valoare1, operator1);

            if (se_verifica) {
                int se_afiseaza = 0;

                if (strcmp(camp2, "id") == 0)
                    se_afiseaza = verifica_int(s->materii[j].id, atoi(valoare2), operator2);
                else if (strcmp(camp2, "nume") == 0)
                    se_afiseaza = verifica_char(s->materii[j].nume, valoare2, operator2);
                else if (strcmp(camp2, "nume_titular") == 0)
                    se_afiseaza = verifica_char(s->materii[j].nume_titular, valoare2, operator2);

                if (se_afiseaza) {
                    int first = 1;
                    for (m = 0; m < selected_count; m++) {
                        if (first) {
                            first = 0;
                        } else {
                            printf(" ");
                        }
                        if (strcmp(selected_words[0], "*") == 0) {
                            printf("%d %s %s", s->materii[j].id, s->materii[j].nume, s->materii[j].nume_titular);
                            break;
                        }
                        if (strcmp(selected_words[m], "id") == 0) {
                            printf("%d", s->materii[j].id);
                        } else if (strcmp(selected_words[m], "nume") == 0) {
                            printf("%s", s->materii[j].nume);
                        } else if (strcmp(selected_words[m], "nume_titular") == 0) {
                            printf("%s", s->materii[j].nume_titular);
                        }
                    }
                    printf("\n");
                }
            }
        }
    } else if (strcmp(entity_type, "inrolari") == 0) {
        for (j = 0; j < s->nr_inrolari; j++) {
            int se_verifica = 0;

            if (strcmp(camp1, "id_student") == 0)
                se_verifica = verifica_int(s->inrolari[j].id_student, atoi(valoare1), operator1);
            else if (strcmp(camp1, "id_materie") == 0)
                se_verifica = verifica_int(s->inrolari[j].id_materie, atoi(valoare1), operator1);

            if (se_verifica) {
                int se_afiseaza = 0;

                if (strcmp(camp2, "id_student") == 0)
                    se_afiseaza = verifica_int(s->inrolari[j].id_student, atoi(valoare2), operator2);
                else if (strcmp(camp2, "id_materie") == 0)
                    se_afiseaza = verifica_int(s->inrolari[j].id_materie, atoi(valoare2), operator2);

                if (se_afiseaza) {
                    int first = 1;
                    for (m = 0; m < selected_count; m++) {
                        if (first) {
                            first = 0;
                        } else {
                            printf(" ");
                        }
                        if (strcmp(selected_words[0], "*") == 0) {
                            printf("%d %d %.2f %.2f %.2f", s->inrolari[j].id_student, s->inrolari[j].id_materie,
                                   s->inrolari[j].note[0], s->inrolari[j].note[1], s->inrolari[j].note[2]);
                            break;
                        }
                        if (strcmp(selected_words[m], "id_student") == 0) {
                            printf("%d", s->inrolari[j].id_student);
                        } else if (strcmp(selected_words[m], "id_materie") == 0) {
                            printf("%d", s->inrolari[j].id_materie);
                        } else if (strcmp(selected_words[m], "note") == 0) {
                            printf("%.2f %.2f %.2f", s->inrolari[j].note[0], s->inrolari[j].note[1],
                                   s->inrolari[j].note[2]);
                        }
                    }
                    printf("\n");
                }
            }
        }
    }
}

void apply_simple_update(secretariat *s, const char *entity_type, char words[][KMAX_CHARACTERS], const char *camp,
                  const char *operator, const char *valoare) {
    int j = 0;
    if (strcmp(entity_type, "studenti") == 0) {
        for (j = 0; j < s->nr_studenti; j++) {
            if (strcmp(camp, "id") == 0) {
                if (verifica_int(s->studenti[j].id, atoi(valoare), operator)) {
                    if (strcmp(words[3], "medie_generala") == 0) {
                        s->studenti[j].medie_generala = (float)atof(words[position_words]);
                    } else if (strcmp(words[3], "an_studiu") == 0) {
                        s->studenti[j].an_studiu = atoi(words[position_words]);
                    } else if (strcmp(words[3], "nume") == 0) {
                        snprintf(s->studenti[j].nume, strlen(words[position_words] + 1) + 1, "%s ",
                        words[position_words] + 1);
                        words[position_second_name][strlen(words[position_second_name]) - 1] = '\0';
                        snprintf(s->studenti[j].nume + strlen(s->studenti[j].nume),
                                 sizeof(s->studenti[j].nume) - strlen(s->studenti[j].nume),  " ");
                        snprintf(s->studenti[j].nume + strlen(s->studenti[j].nume),
                                sizeof(s->studenti[j].nume) - strlen(s->studenti[j].nume), "%s",
                                words[position_second_name]);
                    } else if (strcmp(words[3], "statut") == 0) {
                        s->studenti[j].statut = words[position_words][0];
                    }
                }
            } else if (strcmp(camp, "an_studiu") == 0) {
                if (verifica_int(s->studenti[j].an_studiu, atoi(valoare), operator)) {
                    if (strcmp(words[3], "medie_generala") == 0) {
                        s->studenti[j].medie_generala = (float)atof(words[position_words]);
                    } else if (strcmp(words[3], "an_studiu") == 0) {
                        s->studenti[j].an_studiu = atoi(words[position_words]);
                    } else if (strcmp(words[3], "nume") == 0) {
                        snprintf(s->studenti[j].nume, strlen(words[position_words]) + 1, "%s", words[position_words]);
                    } else if (strcmp(words[3], "statut") == 0) {
                        s->studenti[j].statut = words[position_words][0];
                    }
                }
            } else if (strcmp(camp, "medie_generala") == 0) {
                if (verifica_float(s->studenti[j].medie_generala, (float)atof(valoare), operator)) {
                    if (strcmp(words[3], "medie_generala") == 0) {
                        s->studenti[j].medie_generala = (float)atof(words[position_words]);
                    } else if (strcmp(words[3], "an_studiu") == 0) {
                        s->studenti[j].an_studiu = atoi(words[position_words]);
                    } else if (strcmp(words[3], "nume") == 0) {
                        snprintf(s->studenti[j].nume, strlen(words[position_words]) + 1, "%s", words[position_words]);
                    } else if (strcmp(words[3], "statut") == 0) {
                        s->studenti[j].statut = words[position_words][0];
                    }
                }
            } else if (strcmp(camp, "nume") == 0) {
                if (verifica_char(s->studenti[j].nume, valoare, operator)) {
                    if (strcmp(words[3], "medie_generala") == 0) {
                        s->studenti[j].medie_generala = (float)atof(words[position_words]);
                    } else if (strcmp(words[3], "an_studiu") == 0) {
                        s->studenti[j].an_studiu = atoi(words[position_words]);
                    } else if (strcmp(words[3], "nume") == 0) {
                        snprintf(s->studenti[j].nume, strlen(words[position_words]) + 1, "%s", words[position_words]);
                    } else if (strcmp(words[3], "statut") == 0) {
                        s->studenti[j].statut = words[position_words][0];
                    }
                }
            } else if (strcmp(camp, "statut") == 0) {
                if (verifica_char(&s->studenti[j].statut, valoare, operator)) {
                    if (strcmp(words[3], "medie_generala") == 0) {
                        s->studenti[j].medie_generala = (float)atof(words[position_words]);
                    } else if (strcmp(words[3], "an_studiu") == 0) {
                        s->studenti[j].an_studiu = atoi(words[position_words]);
                    } else if (strcmp(words[3], "nume") == 0) {
                        snprintf(s->studenti[j].nume, strlen(words[position_words]) + 1, "%s", words[position_words]);
                    } else if (strcmp(words[3], "statut") == 0) {
                        s->studenti[j].statut = words[position_words][0];
                    }
                }
            }
        }
    } else if (strcmp(entity_type, "materii") == 0) {
        for (j = 0; j < s->nr_materii; j++) {
            if (strcmp(camp, "id") == 0) {
                if (verifica_int(s->materii[j].id, atoi(valoare), operator)) {
                    if (strcmp(words[3], "nume") == 0) {
                        snprintf(s->materii[j].nume, strlen(words[position_words]) + 1,
                        "%s", words[position_words]);
                    } else if (strcmp(words[3], "nume_titular") == 0) {
                        snprintf(s->materii[j].nume_titular, strlen(words[position_words]) + 1,
                        "%s", words[position_words]);
                    }
                }
            } else if (strcmp(camp, "nume_titular") == 0) {
                if (verifica_char(s->materii[j].nume_titular, valoare, operator)) {
                    if (strcmp(words[3], "nume") == 0) {
                        snprintf(s->materii[j].nume, strlen(words[position_words]) + 1, "%s",
                        words[position_words]);
                    } else if (strcmp(words[3], "nume_titular") == 0) {
                        snprintf(s->materii[j].nume_titular, strlen(words[position_words]) + 1,
                        "%s", words[position_words]);
                    }
                }
            }
        }
    } else if (strcmp(entity_type, "inrolari") == 0) {
        for (j = 0; j < s->nr_inrolari; j++) {
            if (strcmp(camp, "id_student") == 0) {
                if (verifica_int(s->inrolari[j].id_student, atoi(valoare), operator)) {
                    if (strcmp(words[3], "id_materie") == 0) {
                        s->inrolari[j].id_materie = atoi(words[position_words]);
                    } else if (strcmp(words[3], "note") == 0) {
                        s->inrolari[j].note[0] = (float)atof(words[position_first_note]);
                        s->inrolari[j].note[1] = (float)atof(words[position_second_note]);
                        s->inrolari[j].note[2] = (float)atof(words[position_third_note]);
                    }
                }
            } else if (strcmp(camp, "id_materie") == 0) {
                if (verifica_int(s->inrolari[j].id_materie, atoi(valoare), operator)) {
                    if (strcmp(words[3], "id_student") == 0) {
                        s->inrolari[j].id_student = atoi(words[position_words]);
                    } else if (strcmp(words[3], "note") == 0) {
                        s->inrolari[j].note[0] = (float)atof(words[position_first_note]);
                        s->inrolari[j].note[1] = (float)atof(words[position_second_note]);
                        s->inrolari[j].note[2] = (float)atof(words[position_third_note]);
                        recalculeaza_medii_generale(s);
                    }
                }
            }
        }
    }
}

void apply_complex_update(secretariat *s, char words[][KMAX_CHARACTERS],
                          const char *entity_type, const char *camp1,
                          const char *operator1, const char *valoare1, const char *camp2,
                          const char *operator2, const char *valoare2) {
    int j = 0;
    if (strcmp(entity_type, "studenti") == 0) {
        for (j = 0; j < s->nr_studenti; j++) {
            int se_verifica = 0;
            if (strcmp(camp1, "id") == 0) {
                se_verifica = verifica_int(s->studenti[j].id, atoi(valoare1), operator1);
            } else if (strcmp(camp1, "medie_generala") == 0) {
                se_verifica = verifica_float(s->studenti[j].medie_generala, (float)atof(valoare1), operator1);
            } else if (strcmp(camp1, "an_studiu") == 0) {
                se_verifica = verifica_int(s->studenti[j].an_studiu, atoi(valoare1), operator1);
            } else if (strcmp(camp1, "nume") == 0) {
                se_verifica = verifica_char(s->studenti[j].nume, valoare1, operator1);
            } else if (strcmp(camp1, "statut") == 0) {
                if (s->studenti[j].statut == valoare1[0]) {
                    se_verifica = 1;
                }
            }
            if (se_verifica) {
                int se_afiseaza = 0;
                if (strcmp(camp2, "id") == 0) {
                    se_afiseaza = verifica_int(s->studenti[j].id, atoi(valoare2), operator2);
                } else if (strcmp(camp2, "medie_generala") == 0) {
                    se_afiseaza = verifica_float(s->studenti[j].medie_generala,
                    rotunjire((float)atof(valoare2)), operator2);
                } else if (strcmp(camp2, "an_studiu") == 0) {
                    se_afiseaza = verifica_int(s->studenti[j].an_studiu, atoi(valoare2), operator2);
                } else if (strcmp(camp2, "nume") == 0) {
                    se_afiseaza = verifica_char(s->studenti[j].nume, valoare2, operator2);
                } else if (strcmp(camp2, "statut") == 0) {
                    if (s->studenti[j].statut == valoare2[0]) {
                        se_afiseaza = 1;
                    }
                }
                if (se_afiseaza) {
                    if (strcmp(words[3], "medie_generala") == 0) {
                        s->studenti[j].medie_generala = (float)atof(words[position_words]);
                    } else if (strcmp(words[3], "an_studiu") == 0) {
                        s->studenti[j].an_studiu = atoi(words[position_words]);
                    } else if (strcmp(words[3], "nume") == 0) {
                        snprintf(s->studenti[j].nume, strlen(words[position_words]) + 1, "%s", words[position_words]);
                    } else if (strcmp(words[3], "statut") == 0) {
                        s->studenti[j].statut = words[position_words][0];
                    }
                }
            }
        }
    } else if (strcmp(entity_type, "materii") == 0) {
        for (j = 0; j < s->nr_materii; j++) {
            int se_verifica = 0;
            if (strcmp(camp1, "id") == 0) {
                se_verifica = verifica_int(s->materii[j].id, atoi(valoare1), operator1);
            } else if (strcmp(camp1, "nume") == 0) {
                se_verifica = verifica_char(s->materii[j].nume, valoare1, operator1);
            } else if (strcmp(camp1, "nume_titular") == 0) {
                se_verifica = verifica_char(s->materii[j].nume_titular, valoare1, operator1);
            }
            if (se_verifica) {
                int se_afiseaza = 0;
                if (strcmp(camp2, "id") == 0) {
                    se_afiseaza = verifica_int(s->materii[j].id, atoi(valoare2), operator2);
                } else if (strcmp(camp2, "nume") == 0) {
                    se_afiseaza = verifica_char(s->materii[j].nume, valoare2, operator2);
                } else if (strcmp(camp2, "nume_titular") == 0) {
                    se_afiseaza = verifica_char(s->materii[j].nume_titular, valoare2, operator2);
                }
                if (se_afiseaza) {
                    if (strcmp(words[3], "nume") == 0) {
                        snprintf(s->materii[j].nume, strlen(words[position_words]) + 1, "%s",
                        words[position_words]);
                    } else if (strcmp(words[3], "nume_titular") == 0) {
                        snprintf(s->materii[j].nume_titular, strlen(words[position_words]) + 1,
                        "%s", words[position_words]);
                    }
                }
            }
        }
    } else if (strcmp(entity_type, "inrolari") == 0) {
        for (j = 0; j < s->nr_inrolari; j++) {
            int se_verifica = 0;
            if (strcmp(camp1, "id_student") == 0) {
                se_verifica = verifica_int(s->inrolari[j].id_student, atoi(valoare1), operator1);
            } else if (strcmp(camp1, "id_materie") == 0) {
                se_verifica = verifica_int(s->inrolari[j].id_materie, atoi(valoare1), operator1);
            }
            if (se_verifica) {
                int se_afiseaza = 0;
                if (strcmp(camp2, "id_student") == 0) {
                    se_afiseaza = verifica_int(s->inrolari[j].id_student, atoi(valoare2), operator2);
                } else if (strcmp(camp2, "id_materie") == 0) {
                    se_afiseaza = verifica_int(s->inrolari[j].id_materie, atoi(valoare2), operator2);
                }
                if (se_afiseaza) {
                    if (strcmp(words[3], "id_materie") == 0) {
                        s->inrolari[j].id_materie = atoi(words[position_words]);
                    } else if (strcmp(words[3], "note") == 0) {
                        s->inrolari[j].note[0] = (float)atof(words[position_first_note]);
                        s->inrolari[j].note[1] = (float)atof(words[position_second_note]);
                        s->inrolari[j].note[2] = (float)atof(words[position_third_note]);
                    }
                }
            }
        }
    }
    recalculeaza_medii_generale(s);
}

void apply_simple_delete(secretariat *s, const char *entity_type,
                         const char *camp, const char *operator, const char *valoare) {
    int j = 0;
    if (strcmp(entity_type, "studenti") == 0) {
        for (j = 0; j < s->nr_studenti; j++) {
            if (strcmp(camp, "id") == 0) {
                if (verifica_int(s->studenti[j].id, atoi(valoare), operator)) {
                    int student_id = s->studenti[j].id;
                    for (int k = 0; k < s->nr_inrolari; k++) {
                        if (s->inrolari[k].id_student == student_id) {
                            for (int l = k; l < s->nr_inrolari - 1; l++) {
                                s->inrolari[l] = s->inrolari[l + 1];
                            }
                            s->nr_inrolari--;
                            k--;
                        }
                    }
                    for (int k = j; k < s->nr_studenti - 1; k++) {
                        s->studenti[k] = s->studenti[k + 1];
                    }
                    s->nr_studenti--;
                    j--;
                }
            } else if (strcmp(camp, "medie_generala") == 0) {
                if (verifica_float(s->studenti[j].medie_generala, (float)atof(valoare), operator)) {
                    for (int k = j; k < s->nr_studenti - 1; k++) {
                        s->studenti[k] = s->studenti[k + 1];
                    }
                    s->nr_studenti--;
                    j--;
                }
            } else if (strcmp(camp, "an_studiu") == 0) {
                if (verifica_int(s->studenti[j].an_studiu, atoi(valoare), operator)) {
                    for (int k = j; k < s->nr_studenti - 1; k++) {
                        s->studenti[k] = s->studenti[k + 1];
                    }
                    s->nr_studenti--;
                    j--;
                }
            } else if (strcmp(camp, "nume") == 0) {
                if (verifica_char(s->studenti[j].nume, valoare, operator)) {
                    for (int k = j; k < s->nr_studenti - 1; k++) {
                        s->studenti[k] = s->studenti[k + 1];
                    }
                    s->nr_studenti--;
                    j--;
                }
            } else if (strcmp(camp, "statut") == 0) {
                if (verifica_char(&s->studenti[j].statut, valoare, operator)) {
                    for (int k = j; k < s->nr_studenti - 1; k++) {
                        s->studenti[k] = s->studenti[k + 1];
                    }
                }
            }
        }
    } else if (strcmp(entity_type, "materii") == 0) {
        for (j = 0; j < s->nr_materii; j++) {
            if (strcmp(camp, "id") == 0) {
                if (verifica_int(s->materii[j].id, atoi(valoare), operator)) {
                    for (int k = j; k < s->nr_materii - 1; k++) {
                        s->materii[k] = s->materii[k + 1];
                    }
                    s->nr_materii--;
                    j--;
                }
            } else if (strcmp(camp, "nume") == 0) {
                if (verifica_char(s->materii[j].nume, valoare, operator)) {
                    for (int k = j; k < s->nr_materii - 1; k++) {
                        s->materii[k] = s->materii[k + 1];
                    }
                    s->nr_materii--;
                    j--;
                }
            } else if (strcmp(camp, "nume_titular") == 0) {
                if (verifica_char(s->materii[j].nume_titular, valoare, operator)) {
                    for (int k = j; k < s->nr_materii - 1; k++) {
                        s->materii[k] = s->materii[k + 1];
                    }
                    s->nr_materii--;
                    j--;
                }
            }
        }
    } else if (strcmp(entity_type, "inrolari") == 0) {
        for (j = 0; j < s->nr_inrolari; j++) {
            if (strcmp(camp, "id_student") == 0) {
                if (verifica_int(s->inrolari[j].id_student, atoi(valoare), operator)) {
                    for (int k = j; k < s->nr_inrolari - 1; k++) {
                        s->inrolari[k] = s->inrolari[k + 1];
                    }
                    s->nr_inrolari--;
                    j--;
                }
            } else if (strcmp(camp, "id_materie") == 0) {
                if (verifica_int(s->inrolari[j].id_materie, atoi(valoare), operator)) {
                    for (int k = j; k < s->nr_inrolari - 1; k++) {
                        s->inrolari[k] = s->inrolari[k + 1];
                    }
                    s->nr_inrolari--;
                    j--;
                }
            }
        }
    }
    recalculeaza_medii_generale(s);
}

void apply_complex_delete(secretariat *s, const char *entity_type, const char *camp1, const char *operator1,
                          const char *valoare1, const char *camp2, const char *operator2, const char *valoare2) {
    int j = 0;
    if (strcmp(entity_type, "studenti") == 0) {
        for (j = 0; j < s->nr_studenti; j++) {
            int se_verifica = 0;
            if (strcmp(camp1, "id") == 0) {
                se_verifica = verifica_int(s->studenti[j].id, atoi(valoare1), operator1);
            } else if (strcmp(camp1, "medie_generala") == 0) {
                se_verifica = verifica_float(s->studenti[j].medie_generala, (float)atof(valoare1), operator1);
            } else if (strcmp(camp1, "an_studiu") == 0) {
                se_verifica = verifica_int(s->studenti[j].an_studiu, atoi(valoare1), operator1);
            } else if (strcmp(camp1, "nume") == 0) {
                se_verifica = verifica_char(s->studenti[j].nume, valoare1, operator1);
            } else if (strcmp(camp1, "statut") == 0) {
                if (s->studenti[j].statut == valoare1[0]) {
                    se_verifica = 1;
                }
            }
            if (se_verifica) {
                int se_afiseaza = 0;
                if (strcmp(camp2, "id") == 0) {
                    se_afiseaza = verifica_int(s->studenti[j].id, atoi(valoare2), operator2);
                } else if (strcmp(camp2, "medie_generala") == 0) {
                    se_afiseaza = verifica_float(s->studenti[j].medie_generala, (float)atof(valoare2), operator2);
                } else if (strcmp(camp2, "an_studiu") == 0) {
                    se_afiseaza = verifica_int(s->studenti[j].an_studiu, atoi(valoare2), operator2);
                } else if (strcmp(camp2, "nume") == 0) {
                    se_afiseaza = verifica_char(s->studenti[j].nume, valoare2, operator2);
                } else if (strcmp(camp2, "statut") == 0) {
                    if (s->studenti[j].statut == valoare2[0]) {
                        se_afiseaza = 1;
                    }
                }
                if (se_afiseaza) {
                    int student_id = s->studenti[j].id;
                    for (int k = 0; k < s->nr_inrolari; k++) {
                        if (s->inrolari[k].id_student == student_id) {
                            for (int l = k; l < s->nr_inrolari - 1; l++) {
                                s->inrolari[l] = s->inrolari[l + 1];
                            }
                            s->nr_inrolari--;
                            k--;
                        }
                    }
                    for (int k = j; k < s->nr_studenti - 1; k++) {
                        s->studenti[k] = s->studenti[k + 1];
                    }
                    s->nr_studenti--;
                    j--;
                }
            }
        }
    } else if (strcmp(entity_type, "materii") == 0) {
        for (j = 0; j < s->nr_materii; j++) {
            int se_verifica = 0;
            if (strcmp(camp1, "id") == 0) {
                se_verifica = verifica_int(s->materii[j].id, atoi(valoare1), operator1);
            } else if (strcmp(camp1, "nume") == 0) {
                se_verifica = verifica_char(s->materii[j].nume, valoare1, operator1);
            } else if (strcmp(camp1, "nume_titular") == 0) {
                se_verifica = verifica_char(s->materii[j].nume_titular, valoare1, operator1);
            }
            if (se_verifica) {
                int se_afiseaza = 0;
                if (strcmp(camp2, "id") == 0) {
                    se_afiseaza = verifica_int(s->materii[j].id, atoi(valoare2), operator2);
                } else if (strcmp(camp2, "nume") == 0) {
                    se_afiseaza = verifica_char(s->materii[j].nume, valoare2, operator2);
                } else if (strcmp(camp2, "nume_titular") == 0) {
                    se_afiseaza = verifica_char(s->materii[j].nume_titular, valoare2, operator2);
                }
                if (se_afiseaza) {
                    for (int k = j; k < s->nr_materii - 1; k++) {
                        s->materii[k] = s->materii[k + 1];
                    }
                    s->nr_materii--;
                    j--;
                }
            }
        }
    } else if (strcmp(entity_type, "inrolari") == 0) {
        for (j = 0; j < s->nr_inrolari; j++) {
            int se_verifica = 0;
            if (strcmp(camp1, "id_student") == 0) {
                se_verifica = verifica_int(s->inrolari[j].id_student, atoi(valoare1), operator1);
            } else if (strcmp(camp1, "id_materie") == 0) {
                se_verifica = verifica_int(s->inrolari[j].id_materie, atoi(valoare1), operator1);
            }
            if (se_verifica) {
                int se_afiseaza = 0;
                if (strcmp(camp2, "id_student") == 0) {
                    se_afiseaza = verifica_int(s->inrolari[j].id_student, atoi(valoare2), operator2);
                } else if (strcmp(camp2, "id_materie") == 0) {
                    se_afiseaza = verifica_int(s->inrolari[j].id_materie, atoi(valoare2), operator2);
                }
                if (se_afiseaza) {
                    for (int k = j; k < s->nr_inrolari - 1; k++) {
                        s->inrolari[k] = s->inrolari[k + 1];
                    }
                    s->nr_inrolari--;
                    j--;
                }
            }
        }
    }
    recalculeaza_medii_generale(s);
}



int main(int argc, char* argv[]) {
    int i = 0, cnt = 0, selected_count = 0,  num_words = 0;
    if (argc != 2) {
        return -1;
    }
    secretariat *s = citeste_secretariat(argv[1]);
    int num_of_commands = 0;
    scanf("%d", &num_of_commands);
    getchar();
    char commands[num_of_commands][kMAX_COMMAND_SIZE];
    for (i = 0; i < num_of_commands; i++) {
        fgets(commands[i], kMAX_COMMAND_SIZE, stdin);
        commands[i][strlen(commands[i]) - 1] = '\0';
    }
    char words[kMAX_COMMAND_SIZE][KMAX_CHARACTERS];
    char selected_words[kMAX_COMMAND_SIZE][KMAX_CHARACTERS];
        for (i = 0; i < num_of_commands; i++) {
            num_words = 0;
            selected_count = 0;
            char *p = strtok(commands[i], " ,;");
            while (p != NULL) {
                snprintf(words[num_words], strlen(p) + 1, "%s", p);
                num_words++;
                p = strtok(NULL, " ,;");
            }
            if (strcmp(words[0], "SELECT") == 0) {
                cnt = 1;
                while (strcmp(words[cnt], "FROM") != 0) {
                    snprintf(selected_words[selected_count], strlen(words[cnt]) + 1, "%s", words[cnt]);
                    selected_count++;
                    cnt++;
                }
                if (strcmp(words[num_words - 1], "studenti") == 0 || strcmp(words[num_words - 1], "materii") == 0
                    || strcmp(words[num_words - 1], "inrolari") == 0) {
                        apply_simple_select(s, selected_words, words[num_words - 1], selected_count);
                } else if (strcmp(words[num_words - 4], "WHERE") == 0) {
                    char* camp = words[num_words - 3];
                    char* operator = words[num_words - 2];
                    char* valoare = words[num_words - 1];
                    apply_simple_filter(s, selected_words, words[num_words - position_words], selected_count,
                    camp, operator, valoare);
                } else if (strcmp(words[num_words - 4], "AND") == 0) {
                    char* camp1 = words[num_words - position_camp];
                    char* operator1 = words[num_words - position_operator];
                    char* valoare1 = words[num_words - position_valoare];
                    char* camp2 = words[num_words - 3];
                    char* operator2 = words[num_words - 2];
                    char* valoare2 = words[num_words - 1];
                    apply_complex_filter(s, selected_words, words[num_words - position_category], selected_count,
                    camp1, operator1, valoare1, camp2, operator2, valoare2);
                }
            } else if (strcmp(words[0], "UPDATE") == 0) {
                if (strcmp(words[num_words - 4], "WHERE") == 0) {
                  char* camp = words[num_words - 3];
                  char* operator = words[num_words - 2];
                  char* valoare = words[num_words - 1];
                  apply_simple_update(s, words[1], words, camp, operator, valoare);
                } else if (strcmp(words[num_words - 4], "AND") == 0) {
                    char* camp1 = words[num_words - position_camp];
                    char* operator1 = words[num_words - position_operator];
                    char* valoare1 = words[num_words - position_valoare];
                    char* camp2 = words[num_words - 3];
                    char* operator2 = words[num_words - 2];
                    char* valoare2 = words[num_words - 1];
                    apply_complex_update(s, words, words[1], camp1, operator1, valoare1, camp2, operator2, valoare2);
                }
            } else if (strcmp(words[0], "DELETE") == 0) {
                if (strcmp(words[num_words - 4], "WHERE") == 0) {
                    char* camp = words[num_words - 3];
                    char* operator = words[num_words - 2];
                    char* valoare = words[num_words - 1];
                    apply_simple_delete(s, words[2], camp, operator, valoare);
                } else if (strcmp(words[num_words - 4], "AND") == 0) {
                    char* camp1 = words[num_words - position_camp];
                    char* operator1 = words[num_words - position_operator];
                    char* valoare1 = words[num_words - position_valoare];
                    char* camp2 = words[num_words - 3];
                    char* operator2 = words[num_words - 2];
                    char* valoare2 = words[num_words - 1];
                    apply_complex_delete(s, words[2], camp1, operator1, valoare1, camp2, operator2, valoare2);
                }
            }
        }
    elibereaza_secretariat(&s);
    return 0;
}

