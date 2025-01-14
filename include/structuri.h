#pragma once

#define MAX_STUDENT_NAME 40
#define NUMBER_OF_GRADES 3

typedef struct secretariat secretariat;
typedef struct student student;
typedef struct materie materie;
typedef struct inrolare inrolare;

struct secretariat {
    student *studenti;     // Vector de studenti
    int nr_studenti;       // Numarul total de studenti

    materie *materii;      // Vector de materii
    int nr_materii;        // Numarul total de materii

    inrolare *inrolari;    // Vector de inscrieri (relatii student-materie)
    int nr_inrolari;       // Numarul total de inscrieri
};

struct student {
    int id;                              // ID unic al studentului
    char nume[MAX_STUDENT_NAME];         // Nume complet
    int an_studiu;                       // Anul de studiu
    char statut;                         // 'b' (buget) sau 't' (taxă)
    float medie_generala;                // Media generală
}__attribute__((packed));

struct materie {
    int id;                // ID unic al materiei
    char *nume;            // Nume materie
    char *nume_titular;    // Profesor titular
};

struct inrolare {
    int id_student;                       // ID-ul studentului
    int id_materie;                       // ID-ul materiei
    float note[NUMBER_OF_GRADES];         // Notele studentului (laborator, parțial, final)
};

