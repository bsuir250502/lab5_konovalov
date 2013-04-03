#include "stdlib.h"
#include "string.h"
#include "Optlib.h"
#include "service.h"
#define NAME_SIZE 16
#define MAX_BOOKS_NUMBER 20
#define MAX_STUDENTS_NUMBER 30
#define MAX_PATH_SIZE 255
#define NEW 1
#define EXISTING 2

typedef struct _students {
    char names[NAME_SIZE];
    int books_number;
    char **books;
} studen_t;

char PATH[MAX_PATH_SIZE];
int PATH_USED;

int menu(studen_t *);
void print_menu(void);
void input(studen_t *);
int file_operations(int, studen_t *);
int file_print(char *);
int file_search(char *);
int file_edit(char *, studen_t *);
int _FileSelect(int);

int main(int argc, char **argv)
{
    studen_t *students;
    int i;
    int students_n;
    students = (studen_t *) calloc(MAX_STUDENTS_NUMBER, sizeof(studen_t));
    if (i = options(argc, argv, PATH))
        PATH_USED = 1;
    if (i == 'H')
        return 0;
    if (!menu(students))
        return 0;
    students =
        (studen_t *) realloc(students, students_n * sizeof(studen_t));
    free(students);
    return (0);                 /* I like it */
}

int menu(studen_t * students)
{
    int INPUT_SUCCESS = 0;
    print_menu();
    do
        switch (getchar()) {
        case '1':
            file_operations(1, students);
            INPUT_SUCCESS = 1;
            break;
        case '2':
            file_operations(2, students);
            INPUT_SUCCESS = 1;
            break;
        case '3':
            file_operations(3, students);
            break;
        case '4':
            return 0;
            break;
        default:
            printf("\ntry again\n");
            break;
        }
    while (!INPUT_SUCCESS);
    return 1;
}

void print_menu(void)
{
    printf("1 - Create new list of students\n"
           "2 - Use existing list of students\n"
           "3 - Edit existing list of students\n" "4 - Exit program\n");
    return;
}

int file_operations(int mode, studen_t * students)
{
    char str[NAME_SIZE];
    switch (mode) {
    case 1:
        file_edit("CREATE", students);
        break;
    case 2:
        _FileSelect(EXISTING);
        printf("Print student name\n");
        _fgets(str, NAME_SIZE, stdin);
        //file_search(str);
        break;
    case 3:
        file_edit("EXISTS", students);
        break;
    }
    return 0;
}

int _FileSelect(int mode)
{
    int file_reached = 0;
    if (!PATH_USED) {
        do {
            printf("Print file location\n");
            _fgets(PATH, MAX_PATH_SIZE, stdin);
            switch (mode) {
            case 1:
                if (!fopen(PATH, "r"))
                    printf("File already exists\n");
                else
                    file_reached = 1;
                break;
            case 2:
                if (!fopen(PATH, "r"))
                    printf("File doesn't exist or is inaccessible\n");
                else
                    file_reached = 1;
                break;
            }
        }
        while (!file_reached);
        PATH_USED = 1;
    }
    return 0;
}

int file_edit(char *mode, studen_t * students)
{
    int i;
    if (strcmp(mode, "CREATE") == 0) {
        _FileSelect(NEW);
        input(students);
    }
    return 0;
}

void input(studen_t * students)
{
    return;
}
