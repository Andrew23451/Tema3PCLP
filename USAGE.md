# Tema 3 - ACSQL - Schelet de cod

Scheletul cuprinde următoarele directoare:
- `checker/`, `tests/` - necesare pentru validarea temei
- `src/` - conține fișierele în care trebuie să implementați cele 3 task-uri
- `include/` - conține definițiile structurilor folosite la temă

De asemenea, următoarele instrumente:

- `setup.sh` - instalează pachetele necesare pentru celelalte scripturi
- `checker.py` - rulează checkerul local
- `archive.sh` - arhivează tema în vederea trimiterii pe Moodle

Și un fișier `Makefile` pentru a compila fișierele din `src/`.

**Important!** Înainte de a folosi alte instrumente, trebuie să instalați pachetele necesare executând scriptul `setup.sh`:

```bash
./setup.sh
```

Scriptul de setup cere parolă pentru `sudo`.

## Utilizare checker

Puteți valida local toate taskurile folosind comanda:

```bash
python3 checker.py
```

## Fișiere binare
În cadrul taskului 3, atât fișierele produse de implementarea voastră cât și fișierele din directorul `tests/ref/task3` vor fi în format binar. Puteți vizualiza conținutul lor astfel:
```bash
xxd tests/ref/task3/test1.db.enc.ref
```
Puteți verifica diferențele între două fișiere folosind următoarele comenzi:
```bash
xxd tests/ref/task3/test1.db.enc.ref > t1
xxd tests/output/task3/test1.db.enc > t2
diff t1 t2
```

## Utilizare arhivator

Pentru a trimite tema, puteți genera arhiva executând:

```bash
./archive.sh
```

Va fi creată o arhivă ZIP numită `tema3.zip` pe care o puteți încărca direct pe Moodle, conform instrucțiunilor din cerință.