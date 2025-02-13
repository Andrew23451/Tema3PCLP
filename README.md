# Proiect: Secretariat - Implementare și Funcționalități

## Task 1: Inițializare și Calcul Media

Se va deschide fișierul specific pentru citire, se va aloca dinamic o structură de tip `secretariat` și se va accesa cu ajutorul variabilei `s` toate câmpurile din fiecare structură componentă a structurii mari.

Algoritmul va urmări categoriile precizate în fișier și, cu ajutorul funcției `strtok`, va delimita fiecare câmp în parte, după care va inițializa specific fiecare parte a fiecărei structuri.

Pentru calculul mediei, se va urmări `id`-ul fiecărui student din câmpul **„înrolări”**, iar atâta timp cât `id`-ul nu se modifică se însumează notele de la fiecare materie, iar un contor, inițializat cu `0`, va fi incrementat cu câte o unitate de fiecare dată când se va găsi o nouă materie ce aparține aceluiași `id`.

A fost creată și o funcție de **rotunjire a mediei**, care se aplică inclusiv sumei, pentru a nu exista posibilitatea ca sistemul să rețină o medie de genul `6.999` în loc de `6.7`.

La final, pentru ultimul student se calculează separat această medie pentru a asigura calcularea corectă pentru ultimul student din lista de înrolări.

În ceea ce privește funcția `adauga_student()`, se face `realloc` structurii pentru a adăuga un nou student, student ce se va adăuga la finalul structurii existente.

Funcția `eliberare_secretariat()` parcurge câmpurile din structura **`secretariat`** și eliberează memoria alocată dinamic. În cazul în care ajunge la structura **„materii”**, se eliberează inclusiv numele materiei și numele titularului.

---

## Task 2: Operarea asupra Datelor

Pentru fiecare subtask al acestui task s-a creat o matrice de caractere în care s-a extras fiecare cuvânt, ținând cont de separatori (`virgulă`, `spațiu`, `punct` și `punct și virgulă`).

- **Subtask 1:** Se verifică dacă ultimul cuvânt din matrice este unul dintre cuvintele ce definesc una dintre structuri și se rețin toate câmpurile care sunt cerute, pentru ca mai apoi să fie afișate corespunzător.
- **Subtask 2:** Pentru interogări, actualizări și ștergeri s-au creat funcții care ajută la depistarea valorii de adevăr a condițiilor pentru a afișa, actualiza sau șterge câmpurile cerute.

### Detalii Implementare

1. **Interogări:**
    - Se verifică condițiile cu ajutorul funcțiilor auxiliare.
    - Se afișează câmpurile specificate în cerere.

2. **Actualizări:**
    - Se verifică și se aplică modificările necesare.
    - Se folosește o funcție de recalculare a mediilor generale, care se aplică și în cazul ștergerilor.

3. **Ștergeri:**
    - Dacă este șters un student din structura **„studenți”**, acesta va fi eliminat și din **„înrolări”**.
    - Dacă este ștearsă o materie, aceasta va fi eliminată și din structura **„înrolări”**.
    - Se reactualizează mediile studenților afectați.

Au fost create funcții separate pentru fiecare categorie, pentru o mai bună lizibilitate și ușurarea implementării. În funcția `main()` au fost doar inițializate șirurile de citire, ulterior prelucrate de aceste funcții.

---

## Task 3: Criptarea Structurii `secretariat`

Pentru acest task, structura `secretariat` a fost privită ca o zonă continuă de memorie, astfel s-a realizat împărțirea în **patru blocuri** a structurii `studenți` care aparține structurii principale.

### Pași Implementare

1. **Împărțirea în blocuri:**
    - S-a calculat dimensiunea fiecărei structuri împărțită la `4`.
    - Fiecare bloc a avut `ceil(size / 4)`, adică partea întreagă plus `1` dacă restul împărțirii era diferit de zero.

2. **Aplicarea funcțiilor de criptare:**
    - S-au creat funcții pentru aplicarea operației XOR, ținând cont de lungimea fiecărui bloc și de lungimea cheii/vectorului inițializat.
    - S-a aplicat `P-BOX`, o funcție care schimbă ordinea octeților în blocurile de memorie.

3. **Cipher Block Chaining:**
    - Fiecare bloc este criptat în ordinea specificată de acest algoritm.
    - Rezultatul criptării este scris într-un fișier deschis în modul **write**.

4. **Salvarea și închiderea fișierului:**
    - Fișierul este parcurs octet cu octet.
    - Se scriu datele criptate și, la final, fișierul este închis pentru a asigura integritatea datelor.

---

## Concluzii

Implementarea urmărește gestionarea eficientă a datelor dintr-o structură de tip `secretariat`, incluzând:
- **Inițializare dinamică** și calculul mediei studentilor.
- **Interogări, actualizări și ștergeri** cu actualizarea automată a mediilor.
- **Criptarea datelor** folosind o abordare specifică algoritmului de tip **Cipher Block Chaining**.

Codul rezultat este modular, extensibil și respectă cerințele specificate în fișierul de intrare, asigurând o gestionare eficientă a datelor și protecția acestora prin criptare.

