#include "stdlib.h"
#include "string.h"
#include "optlib.h"             /* fget_str, fgets_c */
#include "service.h"            /* options */
#define NAME_SIZE 20
#define MAX_BOOKS_NUMBER 20
#define MAX_STUDENTS_NUMBER 30
#define MAX_PATH_SIZE 255
#define NEW 1
#define EXISTING 2
#define EDIT 3

typedef struct _students {
    char surname[NAME_SIZE];
    int books_number;
    char books[MAX_BOOKS_NUMBER][NAME_SIZE * 2];
} studen_t;

char PATH[MAX_PATH_SIZE];
int PATH_USED;

int menu(studen_t *);
void print_menu(void);
int students_input(studen_t *, int, int);
int input(studen_t *);
int edit_students(studen_t *, int);
int del_student(char *, studen_t *, int);
int del_book(char *, studen_t *, int);
int add_book(char *, studen_t *, int);
void edit_menu(void);
int file_print(studen_t *);
int file_search(char *, studen_t *, int);
int file_write(FILE *, studen_t *, int);
int file_read(FILE *, studen_t *);
int file_edit(char *, studen_t *);
FILE *_FileSelect(int);
void free_st(studen_t *);

int main(int argc, char **argv)
{
    studen_t students[MAX_STUDENTS_NUMBER];
    int i;
    if (i = options(argc, argv, PATH))
        PATH_USED = 1;
    if (i == 'H')
        return 0;
    menu(&students[0]);
    return (0);                 /* I like it */
}

int menu(studen_t * students)
{
    int INPUT_SUCCESS = 0, i = 0, students_n;
    char str[NAME_SIZE + 1];
    do {
        printf("1 - Create new list of students\n"
               "2 - Use existing list of students\n"
               "3 - Edit existing list of students\n"
               "4 - Exit program\n");
        switch (fgets_c(str, 2, stdin)) {
        case '1':
            students_n = file_edit("CREATE", students);
            break;
        case '2':
            printf("Print student name\n");
            fgets_c(str, NAME_SIZE, stdin);
            students_n = file_read(_FileSelect(EXISTING), students);
            file_print(&students[file_search(str, students, students_n)]);
            INPUT_SUCCESS = 1;
            break;
        case '3':
            students_n = file_edit("EXISTS", students);
            break;
        case '4':
            return 0;
            break;
        default:
            printf("\ntry again\n");
            break;
        }
    }
    while (!INPUT_SUCCESS);
    return 0;
}

int students_input(studen_t * students, int students_n, int mode)
{
    switch (mode) {
    case 1:
        for (students_n = 0; students_n < MAX_STUDENTS_NUMBER;
             students_n++)
            if (!input(&students[students_n]))
                break;
        break;
    case 3:
        students_n = edit_students(students, students_n);
        break;
    }
    return students_n;
}

int input(studen_t * students)
{
    printf("Print surname\n");
    students->books_number = 0;
    if (fgets_c(students->surname, NAME_SIZE, stdin) == '\n')
        return 0;
    while (1) {
        printf("Print book info\n");
        if (fgets_c
            (students->books[students->books_number], NAME_SIZE * 2,
             stdin) == '\n')
            break;
        students->books_number++;
    }
    return 1;
}

int edit_students(studen_t * students, int students_n)
{
    int EXIT = 0;
    char str[NAME_SIZE + 1];
    do {
        printf("1 - Delete student\n"
               "2 - Add student(if possible)\n"
               "3 - Delete book\n"
               "4 - Add book to student\n" "5 - End editing\n");
        switch (fgets_c(str, 2, stdin)) {
        case '1':
            printf("Print student's surname\n");
            fgets_c(str, NAME_SIZE, stdin);
            students_n = del_student(str, students, students_n);
            break;
        case '2':
            if (students_n < MAX_STUDENTS_NUMBER) {
                students_n++;
                input(&students[students_n + 1]);
            } else
                printf("Students limit reached\n");
            break;
        case '3':
            printf("Print student's surname\n");
            fgets_c(str, NAME_SIZE, stdin);
            del_book(str, students, students_n);
            break;
        case '4':
            printf("Print student's surname\n");
            fgets_c(str, NAME_SIZE, stdin);
            add_book(str, students, students_n);
            break;
        case '5':
            EXIT = 1;
            break;
        }
    }
    while (!EXIT);
    fflush(stdin);
    return students_n;
}

int del_student(char *str, studen_t * students, int students_n)
{
    int i;
    if ((i = file_search(str, students, students_n)) != -1) {
        for (; i < students_n - 1; i++)
            students[i] = students[i + 1];
        students_n--;
    } else
        printf("Student not found\n");
    return students_n;
}

int del_book(char *str, studen_t * students, int students_n)
{
    int i, j;
    if ((i = file_search(str, students, students_n)) != -1) {
        file_print(&students[i]);
        printf("Print book number that you see on the left side\n");
        get_posint(&j, stdin);
        if (j >= students[i].books_number || j < 0)
            printf("No such book\n");
        for (; j < students[i].books_number - 1; j++)
            strcpy(students[i].books[j], students[i].books[j + 1]);
        students[i].books_number--;
    } else
        printf("Student not found\n");
    return 0;
}

int add_book(char *str, studen_t * students, int students_n)
{
    int i;
    if ((i = file_search(str, students, students_n)) != -1) {
        if (students[i].books_number != MAX_BOOKS_NUMBER) {
            printf("Print new book info\n");
            fgets_c(students[i].books[students[i].books_number + 1],
                    NAME_SIZE * 2, stdin);
            students[i].books_number++;
        } else
            printf("Books limit reached\n");
    } else
        printf("Student not found\n");
    return 0;
}

FILE *_FileSelect(int mode)
{
    FILE *list;
    int file_reached = 0;
    if (!PATH_USED) {
        do {
            printf("Print file location\n");
            fgets_c(PATH, MAX_PATH_SIZE, stdin);
            switch (mode) {
            case 1:
                if (fopen(PATH, "r"))
                    printf("File already exists\n");
                else {
                    list = fopen(PATH, "w+");
                    file_reached = 1;
                }
                break;
            case 2:
                if (!(list = fopen(PATH, "r+")))
                    printf("File doesn't exist or is inaccessible\n");
                else
                    file_reached = 1;
                break;
            }
        }
        while (!file_reached);
        PATH_USED = 1;
    } else if (!(list = fopen(PATH, "r+"))) {
        printf("File doesn't exist or is inaccessible\n");
        exit(-1);
    }
    return list;
}

int file_edit(char *mode, studen_t * students)
{
    FILE *list;
    int students_n;
    if (strcmp(mode, "CREATE") == 0) {
        list = _FileSelect(NEW);
        students_n = students_input(students, 0, NEW);
        file_write(list, students, students_n);
    } else if (strcmp(mode, "EXISTS") == 0) {
        list = _FileSelect(EXISTING);
        students_n = file_read(list, students);
        students_n = students_input(students, students_n, EDIT);
        file_write(list, students, students_n);
    }
    return students_n;
}

int file_read(FILE * list, studen_t * students)
{
    int i = 0, j = 0;
    char tmp[4];
    while (1) {
        fget_str(list, tmp, 3, ' ', 1, '\n');
        students[i].books_number = atoi(tmp);
        if (students[i].books_number > MAX_BOOKS_NUMBER)
            return 0;
        if (feof(list))
            break;
        fget_str(list, students[i].surname, NAME_SIZE, ':', 2, ' ', '\n');
        for (j = 0; j < students[i].books_number - 1; j++)
            fget_str(list, students[i].books[j], NAME_SIZE * 2, ',', 1,
                     '\n');
        fget_str(list, students[i].books[j], NAME_SIZE * 2, '.', 1, '\n');
        i++;
    }
    fclose(list);
    return i;
}

int file_print(studen_t * students)
{
    int i = 0;
    printf("%-s:\n", students->surname);
    for (i = 0; i < students->books_number; i++)
        printf("%d %-s\n", i, students->books[i]);
    return 0;
}

int file_search(char *keyword, studen_t * students, int students_n)
{
    int i;
    for (i = 0; i < students_n; i++)
        if (strcmp(students[i].surname, keyword) == 0)
            return i;
    return -1;
}

int file_write(FILE * list, studen_t * students, int students_n)
{
    int i = 0, j = 0;
    freopen(PATH, "w", list);
    for (i = 0; i < students_n; i++) {
        if (students[i].books_number < 10)
            fprintf(list, "%2d", students[i].books_number);
        fprintf(list, "%s:\n", students[i].surname);
        for (j = 0; j < students[i].books_number - 1; j++)
            fprintf(list, "%s,\n", students[i].books[j]);
        fprintf(list, "%s.\n", students[i].books[j]);
    }
    fclose(list);
    return 0;
}
