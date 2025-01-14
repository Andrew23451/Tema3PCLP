#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task1.h"
#define length_of_category 10
#define rounding 0.5f
#define precision 100

float round_at_two_decimals(float x) {
    int nr = (int)(x * precision + rounding);
    return (float)nr / 100.0f;
}

secretariat *citeste_secretariat(const char *nume_fisier) {
    const int kMax_length = 100;
    FILE *f = fopen(nume_fisier, "r");
    if (f == NULL) {
        return NULL;
    }
    secretariat *s = malloc(sizeof(secretariat));
    if (s == NULL) {
        fclose(f);
        return NULL;
    }
    s->studenti = NULL;
    s->nr_studenti = 0;
    s->materii = NULL;
    s->nr_materii = 0;
    s->inrolari = NULL;
    s->nr_inrolari = 0;
    char line[kMax_length];
    int in_studenti = 0, in_materii = 0, in_inrolari = 0;


    int last_id_student = -1;
    float suma_note = 0.0f;
    int cnt_materii = 0;


    while (fgets(line, kMax_length, f)) {
        if (strncmp(line, "[STUDENTI]", length_of_category) == 0) {
            in_studenti = 1;
            continue;
        }
        if (in_studenti && strncmp(line, "[MATERII]", length_of_category - 1) == 0) {
            in_studenti = 0;
        }
        if (in_studenti && line[0] != '[') {
            char *id = strtok(line, ",");
            char *nume = strtok(NULL, ",") + 1;
            char *an_studiu = strtok(NULL, ",") + 1;
            char *statut = strtok(NULL, ",");
            if (id == NULL || nume == NULL || an_studiu == NULL || statut == NULL) {
                continue;
            }
            s->nr_studenti++;
            student *temp = realloc(s->studenti, s->nr_studenti * sizeof(student));
            if (temp == NULL) {
                fclose(f);
                free(s);
                return NULL;
            }
            s->studenti = temp;
            s->studenti[s->nr_studenti - 1].id = atoi(id);
            strncpy(s->studenti[s->nr_studenti - 1].nume, nume, sizeof(s->studenti[s->nr_studenti - 1].nume) - 1);
            s->studenti[s->nr_studenti - 1].nume[sizeof(s->studenti[s->nr_studenti - 1].nume) - 1] = '\0';
            s->studenti[s->nr_studenti - 1].an_studiu = atoi(an_studiu);
            s->studenti[s->nr_studenti - 1].statut = statut[1];
            s->studenti[s->nr_studenti - 1].medie_generala = 0.0f;
        }
        if (strncmp(line, "[MATERII]", length_of_category - 1) == 0) {
            in_materii = 1;
            continue;
        }
        if (in_materii && strncmp(line, "[INROLARI]", length_of_category) == 0) {
            in_materii = 0;
        }
        if (in_materii && line[0] != '[') {
            char *id = strtok(line, ",");
            char *nume = strtok(NULL, ",") + 1;
            char *titular = strtok(NULL, ",") + 1;
            if (id == NULL || nume == NULL || titular == NULL) {
                continue;
            }
            s->nr_materii++;
            titular[strlen(titular) - 1] = '\0';
            materie *temp = realloc(s->materii, s->nr_materii * sizeof(materie));
            if (temp == NULL) {
                fclose(f);
                free(s);
                return NULL;
            }
            s->materii = temp;
            s->materii[s->nr_materii - 1].id = atoi(id);
            s->materii[s->nr_materii - 1].nume = malloc(strlen(nume) + 1);
            if (s->materii[s->nr_materii - 1].nume == NULL) {
                fclose(f);
                free(s);
                return NULL;
            }
            strncpy(s->materii[s->nr_materii - 1].nume, nume, strlen(nume) + 1);
            s->materii[s->nr_materii - 1].nume_titular = malloc(strlen(titular) + 1);
            if (s->materii[s->nr_materii - 1].nume_titular == NULL) {
                fclose(f);
                free(s->materii[s->nr_materii - 1].nume);
                free(s);
                return NULL;
            }
            strncpy(s->materii[s->nr_materii - 1].nume_titular, titular, strlen(titular) + 1);
        }
        if (strncmp(line, "[INROLARI]", length_of_category) == 0) {
            in_inrolari = 1;
            continue;
        }
        if (in_inrolari && line[0] != '[') {
            char *id_student = strtok(line, ",");
            char *id_materie = strtok(NULL, ",");
            char *note1 = strtok(NULL, " ");
            char *note2 = strtok(NULL, " ");
            char *note3 = strtok(NULL, " ");
            if (id_student == NULL || id_materie == NULL || note1 == NULL || note2 == NULL || note3 == NULL) {
                continue;
            }
            int id = atoi(id_student);
            float note_sum = (float)(atof(note1) + atof(note2) + atof(note3));
            if (id != last_id_student && last_id_student != -1) {
                float medie = (float)(suma_note) / (float)(cnt_materii);
                medie = (float)round_at_two_decimals(medie);
                s->studenti[last_id_student].medie_generala = medie;
                suma_note = 0.0f;
                cnt_materii = 0;
            }
            suma_note += note_sum;
            suma_note = (float)round_at_two_decimals(suma_note);
            cnt_materii++;
            last_id_student = id;
            s->nr_inrolari++;
            inrolare *temp = realloc(s->inrolari, s->nr_inrolari * sizeof(inrolare));
            if (temp == NULL) {
                fclose(f);
                free(s);
                return NULL;
            }
            s->inrolari = temp;
            s->inrolari[s->nr_inrolari - 1].id_student = id;
            s->inrolari[s->nr_inrolari - 1].id_materie = atoi(id_materie);
            s->inrolari[s->nr_inrolari - 1].note[0] = (float)atof(note1);
            s->inrolari[s->nr_inrolari - 1].note[1] = (float)atof(note2);
            s->inrolari[s->nr_inrolari - 1].note[2] = (float)atof(note3);
        }
    }
    if (cnt_materii > 0) {
        float medie = (float)(suma_note) / (float)(cnt_materii);
        medie = (float)round_at_two_decimals(medie);
        s->studenti[last_id_student].medie_generala = medie;
    }
    fclose(f);
    return s;
    return NULL;
}

void adauga_student(secretariat *s, int id, char *nume, int an_studiu, char statut, float medie_generala) {
    if (s == NULL) {
        return;
    }
    s->nr_studenti++;
    s->studenti = realloc(s->studenti, s->nr_studenti * sizeof(student));
    if (s->studenti == NULL) {
        return;
    }
    s->studenti[s->nr_studenti - 1].id = id;
    strncpy(s->studenti[s->nr_studenti - 1].nume, nume, sizeof(s->studenti[s->nr_studenti - 1].nume) - 1);
    s->studenti[s->nr_studenti - 1].nume[sizeof(s->studenti[s->nr_studenti - 1].nume) - 1] = '\0';
    s->studenti[s->nr_studenti - 1].an_studiu = an_studiu;
    s->studenti[s->nr_studenti - 1].statut = statut;
    s->studenti[s->nr_studenti - 1].medie_generala = medie_generala;
}

void elibereaza_secretariat(secretariat **s) {
    if (*s == NULL) return;
    free((*s)->studenti);
    (*s)->studenti = NULL;
    if ((*s)->materii != NULL) {
        for (int i = 0; i < (*s)->nr_materii; i++) {
            free((*s)->materii[i].nume);
            (*s)->materii[i].nume = NULL;
            free((*s)->materii[i].nume_titular);
            (*s)->materii[i].nume_titular = NULL;
        }
        free((*s)->materii);
        (*s)->materii = NULL;
    }
    free((*s)->inrolari);
    (*s)->inrolari = NULL;
    free(*s);
    *s = NULL;
}
