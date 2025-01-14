#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "../src/task1.h"
#include "../src/task3.h"
#include "../checker/helper.h"
#define TEST_DB "tests/db/small.db"
#define EPSILON 0.001

int eps_eq(float a, float b) {
    return fabs(a - b) < EPSILON;
}

int check_alocare_secretariat() {
    secretariat *s = citeste_secretariat(TEST_DB);
    if (s == NULL) {
        printf("Alocare secretariat esuata\n");
        return 0;
    }
    if (s->nr_studenti != 10) {
        printf("Numar studenti gresit\n");
        return 0;
    }

    if (s->nr_materii != 9) {
        printf("Numar materii gresit\n");
        return 0;
    }

    if (s->nr_inrolari != 25) {
        printf("Numar inrolari gresit\n");
        return 0;
    }

    if (strcmp(s->studenti[4].nume, "Popescu Adrian") != 0 || s->studenti[4].id != 4 
                    || s->studenti[4].an_studiu != 3 || s->studenti[4].statut != 'b' || !eps_eq(s->studenti[4].medie_generala, 7.74)) {
        printf("Studentii au fost salvati gresit!\n");
        return 0;
    }

    if (strcmp(s->materii[3].nume, "Fizica") != 0 || s->materii[3].id != 3 
                    || strcmp(s->materii[3].nume_titular, "Petrescu Cristina") != 0) {
        printf("Materiile au fost salvate gresit!\n");
        return 0;
    }

    if (s->inrolari[5].id_student != 2 || s->inrolari[5].id_materie != 0 
                    || !eps_eq(s->inrolari[5].note[0], 2.22)  || !eps_eq(s->inrolari[5].note[1], 1.50) || !eps_eq(s->inrolari[5].note[2], 3.08)) {
        printf("Inrolarile au fost salvate gresit!\n");
        return 0;
    }
    return 1;
}

int check_adauga_student() {
    secretariat *s = citeste_secretariat_helper(TEST_DB);
    if (s == NULL) {
        printf("Alocare secretariat esuata\n");
        return 0;
    }
    adauga_student(s, 11, "Popescu Adrian", 3, 'b', 9.99);
    if (s->nr_studenti != 11) {
        printf("Numar studenti gresit\n");
        return 0;
    }

    if (strcmp(s->studenti[10].nume, "Popescu Adrian") != 0 || s->studenti[10].id != 11 
                    || s->studenti[10].an_studiu != 3 || s->studenti[10].statut != 'b') {
        printf("Studentii au fost salvati gresit!\n");
        return 0;
    }
    return 1;
}

int check_elibereaza_secretariat() {
    secretariat *s = citeste_secretariat_helper(TEST_DB);
    elibereaza_secretariat(&s);
    if (s != NULL) {
        printf("Eliberare secretariat esuata\n");
        return 0;
    }
    return 1;
}

void run_task3() {
    secretariat *s1 = citeste_secretariat_helper("tests/db/task3/test1.db");
    cripteaza_studenti(s1, "pclp1", 5, "aa", 2, "tests/output/task3/test1.db.enc");

    secretariat *s2 = citeste_secretariat_helper("tests/db/task3/test2.db");
    cripteaza_studenti(s2, "pclp1", 5, "aa", 2, "tests/output/task3/test2.db.enc");

    secretariat *s3 = citeste_secretariat_helper("tests/db/task3/test3.db");
    cripteaza_studenti(s3, "pclp1", 5, "aa", 2, "tests/output/task3/test3.db.enc");

    secretariat *s4 = citeste_secretariat_helper("tests/db/task3/test4.db");
    cripteaza_studenti(s4, "pclp1", 5, "aa", 2, "tests/output/task3/test4.db.enc");

    secretariat *s5 = citeste_secretariat_helper("tests/db/task3/test5.db");
    cripteaza_studenti(s5, "pclp1", 5, "aa", 2, "tests/output/task3/test5.db.enc");
}

int main(int argc, char *argv[]) {
    int task = 0;

    if (argc != 1) {
        task = atoi(argv[1]);
    }

    if (task == 3) {
        if (check_elibereaza_secretariat()) {
            return 5;
        } else {
            printf("Task 1.3 incorect!\n");
        }
        return 0;
    }

    if (task == 1) {
        if (check_alocare_secretariat()) {
            printf("Task 1.1 trecut cu succes!\n");
            return 3;
        } else 
            printf("Task 1.1 incorect!\n");
        
        return 0;
    }

    if (task == 2) {
        if (check_adauga_student()) {
            printf("Task 1.2 trecut cu succes!\n");
            return 2;
        } else
            printf("Task 1.2 incorect!\n");
        
        return 0;
    }

    if (task == 4) {
        run_task3();
    }
    return 0;
}
