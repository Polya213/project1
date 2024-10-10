#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_LENGTH 100

typedef struct {
    char lastName[MAX_LENGTH];
    char firstName[MAX_LENGTH];
    int grade;
    int classroom;
    int bus;
    char teacherLastName[MAX_LENGTH];
    char teacherFirstName[MAX_LENGTH];
} Student;

Student students[MAX_STUDENTS];
int studentCount = 0;

//завантаження студентів з файлу
void loadStudents(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Помилка: Не вдалося відкрити файл %s\n", filename);
        exit(1);
    }

    while (fgets(students[studentCount].lastName, sizeof(students[studentCount].lastName), file)) {
        students[studentCount].lastName[strcspn(students[studentCount].lastName, "\n")] = 0;
        char firstName[MAX_LENGTH];
        int grade, classroom, bus;
        char teacherLastName[MAX_LENGTH], teacherFirstName[MAX_LENGTH];

//зчитування даних з файлу
        if (sscanf(students[studentCount].lastName, "%[^,], %[^,], %d, %d, %d, %[^,], %s",
                   firstName, students[studentCount].lastName, &grade, &classroom, 
                   &bus, teacherLastName, teacherFirstName) == 7) {
            strcpy(students[studentCount].firstName, firstName);
            students[studentCount].grade = grade;
            students[studentCount].classroom = classroom;
            students[studentCount].bus = bus;
            strcpy(students[studentCount].teacherLastName, teacherLastName);
            strcpy(students[studentCount].teacherFirstName, teacherFirstName);
            studentCount++;
        } else {
            printf("Помилка формату у рядку: %s\n", students[studentCount].lastName);
        }

        if (studentCount >= MAX_STUDENTS) {
            break;
        }
    }
    fclose(file);
}

//пошук студентів за прізвищем
void searchByStudentLastName(char* lastName) {
    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (strcasecmp(students[i].lastName, lastName) == 0) {
            printf("Студент: %s %s, Клас: %d, Вчитель: %s %s\n",
                students[i].firstName,
                students[i].lastName,
                students[i].classroom,
                students[i].teacherFirstName,
                students[i].teacherLastName);
            found = 1;
        }
    }
    if (!found) {
        printf("Студента з прізвищем '%s' не знайдено.\n", lastName);
    }
}

//пошук студентів за номером автобуса
void searchByBusNumber(int busNumber) {
    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].bus == busNumber) {
            printf("Студент: %s %s, Клас: %d\n",
                students[i].firstName,
                students[i].lastName,
                students[i].classroom);
            found = 1;
        }
    }
    if (!found) {
        printf("Студентів, що користуються автобусом номер %d, не знайдено.\n", busNumber);
    }
}

//пошук студентів за прізвищем викладача
void searchByTeacherLastName(char* lastName) {
    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (strcasecmp(students[i].teacherLastName, lastName) == 0) {
            printf("Студент: %s %s\n",
                students[i].firstName,
                students[i].lastName);
            found = 1;
        }
    }
    if (!found) {
        printf("Студентів для вчителя '%s' не знайдено.\n", lastName);
    }
}

//пошук студентів за класом
void searchByClassroom(int classroom) {
    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].classroom == classroom) {
            printf("Студент: %s %s\n",
                students[i].firstName,
                students[i].lastName);
            found = 1;
        }
    }
    if (!found) {
        printf("Студентів у класі %d не знайдено.\n", classroom);
    }
}

//додавання нового студента
void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("Помилка: Немає місця для додавання нових студентів.\n");
        return;
    }

    Student newStudent;

//введення даних нового студента
    printf("Введіть прізвище студента: ");
    fgets(newStudent.lastName, sizeof(newStudent.lastName), stdin);
    newStudent.lastName[strcspn(newStudent.lastName, "\n")] = 0;

    printf("Введіть ім'я студента: ");
    fgets(newStudent.firstName, sizeof(newStudent.firstName), stdin);
    newStudent.firstName[strcspn(newStudent.firstName, "\n")] = 0;

    printf("Введіть клас: ");
    scanf("%d", &newStudent.classroom);
    getchar(); //видалення залишків нового рядка

    printf("Введіть номер автобуса: ");
    scanf("%d", &newStudent.bus);
    getchar();

    printf("Введіть оцінку: ");
    scanf("%d", &newStudent.grade);
    getchar();

    printf("Введіть прізвище вчителя: ");
    fgets(newStudent.teacherLastName, sizeof(newStudent.teacherLastName), stdin);
    newStudent.teacherLastName[strcspn(newStudent.teacherLastName, "\n")] = 0;

    printf("Введіть ім'я вчителя: ");
    fgets(newStudent.teacherFirstName, sizeof(newStudent.teacherFirstName), stdin);
    newStudent.teacherFirstName[strcspn(newStudent.teacherFirstName, "\n")] = 0;

//додавання студента до масиву
    students[studentCount] = newStudent;
    studentCount++;

    printf("Студента %s %s додано успішно!\n", newStudent.firstName, newStudent.lastName);
}

//видалення студента за прізвищем
void deleteStudent(char* lastName) {
    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (strcasecmp(students[i].lastName, lastName) == 0) {
            found = 1;
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            studentCount--; 
            printf("Студента %s успішно видалено.\n", lastName);
            break;
        }
    }
    if (!found) {
        printf("Студента з прізвищем '%s' не знайдено.\n", lastName);
    }
}
void interactiveSearch() {
    char command[MAX_LENGTH];
    int choice;

    printf("Меню:\n");
    printf("1 - Пошук студента за прізвищем\n");
    printf("2 - Пошук студентів за номером автобуса\n");
    printf("3 - Пошук студентів за прізвищем вчителя\n");
    printf("4 - Пошук студентів за номером класу\n");
    printf("5 - Додати нового студента\n");
    printf("6 - Видалити студента\n");
    printf("7 - Вихід з програми\n\n");

    while (1) {
        printf("Введіть номер команди (1-7): ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0;

        choice = atoi(command);

        switch (choice) {
            case 1:
                printf("Введіть прізвище студента: ");
                fgets(command, sizeof(command), stdin);
                command[strcspn(command, "\n")] = 0;
                searchByStudentLastName(command);
                break;
            case 2:
                printf("Введіть номер автобуса: ");
                fgets(command, sizeof(command), stdin);
                int busNumber = atoi(command);
                searchByBusNumber(busNumber);
                break;
            case 3:
                printf("Введіть прізвище вчителя: ");
                fgets(command, sizeof(command), stdin);
                command[strcspn(command, "\n")] = 0;
                searchByTeacherLastName(command);
                break;
            case 4:
                printf("Введіть номер класу: ");
                fgets(command, sizeof(command), stdin);
                int classroom = atoi(command);
                searchByClassroom(classroom);
                break;
            case 5:
                addStudent();
                break;
            case 6:
                printf("Введіть прізвище студента для видалення: ");
                fgets(command, sizeof(command), stdin);
                command[strcspn(command, "\n")] = 0;
                deleteStudent(command);
                break;
            case 7:
                printf("Вихід з програми.\n");
                return;
            default:
                printf("Невідома команда.Спробуйте ще раз.\n");
                break;
        }
    }
}

int main() {
//завантаження студентів з файлу
    loadStudents("students.txt");

//запуск пошуку
    interactiveSearch();

    return 0;
}
