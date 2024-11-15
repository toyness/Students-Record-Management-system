#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 50
#define PASSING_THRESHOLD 40

typedef struct {
    char name[MAX_NAME_LENGTH];
    int roll_number;
    float marks;
} Student;

// Function prototypes
void displayWelcomeMessage(char *username);
Student *createStudent();
void addStudent(Student *students, int *student_count);
void modifyStudent(Student *students, int student_count);
void displayStudents(Student *students, int student_count);
void saveStudentsToFile(Student *students, int student_count);
void loadStudentsFromFile(Student **students, int *student_count);
Student *searchStudent(Student *students, int student_count, int roll_number);
float calculateAverageMarks(Student *students, int student_count);
void sortStudentsByMarks(Student *students, int student_count);

int main() {
    char username[MAX_NAME_LENGTH];
    printf("Enter your name: ");
    fgets(username, MAX_NAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = 0; 

    displayWelcomeMessage(username);

    Student *students = (Student *)calloc(MAX_STUDENTS, sizeof(Student));
    int student_count = 0;

    int choice;
    while (1) {
        printf("\nStudent Record System\n");
        printf("1. Add Student\n");
        printf("2. Modify Student\n");
        printf("3. Display Students\n");
        printf("4. Save to File\n");
        printf("5. Load from File\n");
        printf("6. Search Student\n");
        printf("7. Calculate Average Marks\n");
        printf("8. Sort Students by Marks\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear the newline character left by scanf

        switch (choice) {
            case 1:
                addStudent(students, &student_count);
                break;
            case 2:
                modifyStudent(students, student_count);
                break;
            case 3:
                displayStudents(students, student_count);
                break;
            case 4:
                saveStudentsToFile(students, student_count);
                break;
            case 5:
                loadStudentsFromFile(&students, &student_count);
                break;
            case 6:
                {
                    int roll_number;
                    printf("Enter roll number to search: ");
                    scanf("%d", &roll_number);
                    Student *found_student = searchStudent(students, student_count, roll_number);
                    if (found_student != NULL) {
                        printf("Student found:\n");
                        printf("Name: %s\n", found_student->name);
                        printf("Roll Number: %d\n", found_student->roll_number);
                        printf("Marks: %.2f\n", found_student->marks);
                    } else {
                        printf("Student not found.\n");
                    }
                }
                break;
            case 7:
                printf("Average marks: %.2f\n", calculateAverageMarks(students, student_count));
                break;
            case 8:
                sortStudentsByMarks(students, student_count);
                break;
            case 9:
                free(students);
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void displayWelcomeMessage(char *username) {
    printf("Welcome, %s!\n", username);
}

Student *createStudent() {
    Student *new_student = (Student *)malloc(sizeof(Student));
    printf("Enter student name: ");
    fgets(new_student->name, MAX_NAME_LENGTH, stdin);
    new_student->name[strcspn(new_student->name, "\n")] = 0; 
    printf("Enter roll number: ");
    scanf("%d", &new_student->roll_number);
    printf("Enter marks: ");
    scanf("%f", &new_student->marks);
    getchar(); // Clear the newline character left by scanf
    return new_student;
}

void addStudent(Student *students, int *student_count) {
    if (*student_count < MAX_STUDENTS) {
        students[*student_count] = *createStudent();
        (*student_count)++;
        printf("Student added successfully.\n");
    } else {
        printf("Maximum student limit reached.\n");
    }
}

void modifyStudent(Student *students, int student_count) {
    int roll_number;
    printf("Enter roll number to modify: ");
    scanf("%d", &roll_number);
    getchar(); // Clear the newline character left by scanf
    for (int i = 0; i < student_count; i++) {
        if (students[i].roll_number == roll_number) {
            printf("Enter new name: ");
            fgets(students[i].name, MAX_NAME_LENGTH, stdin);
            students[i].name[strcspn(students[i].name, "\n")] = 0; 
            printf("Enter new roll number: ");
            scanf("%d", &students[i].roll_number);
            printf("Enter new marks: ");
            scanf("%f", &students[i].marks);
            getchar(); // Clear the newline character
            printf("Student modified successfully.\n");
            return;
        }
    }
    printf("Student not found.\n");
}

void displayStudents(Student *students, int student_count) {
    printf("Student Records:\n");
    for (int i = 0; i < student_count; i++) {
        printf("Name: %s\n", students[i].name);
        printf("Roll Number: %d\n", students[i].roll_number);
        printf("Marks: %.2f\n", students[i].marks);
        if (students[i].marks >= PASSING_THRESHOLD) {
            printf("Status: Passed\n");
        } else {
            printf("Status: Failed\n");
        }
        printf("\n");
    }
}

void saveStudentsToFile(Student *students, int student_count) {
    FILE *file = fopen("student_records.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    for (int i = 0; i < student_count; i++) {
        fprintf(file, "%s,%d,%.2f\n", students[i].name, students[i].roll_number, students[i].marks);
    }
    fclose(file);
    printf("Students saved to file successfully.\n");
}

void loadStudentsFromFile(Student **students, int *student_count) {
    FILE *file = fopen("student_records.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    *student_count = 0;
    char line[100];
    while (fgets(line, sizeof(line), file)) {
        Student new_student;
        sscanf(line, "%[^,],%d,%f", new_student.name, &new_student.roll_number, &new_student.marks);
        (*students)[*student_count] = new_student;
        (*student_count)++;
    }
    fclose(file);
    printf("Students loaded from file successfully.\n");
}

Student *searchStudent(Student *students, int student_count, int roll_number) {
    for (int i = 0; i < student_count; i++) {
        if (students[i].roll_number == roll_number) {
            return &students[i];
        }
    }
    return NULL;
}

float calculateAverageMarks(Student *students, int student_count) {
    float sum = 0;
    for (int i = 0; i < student_count; i++) {
        sum += students[i].marks;
    }
    return sum / student_count;
}

void sortStudentsByMarks(Student *students, int student_count) {
    for (int i = 0; i < student_count - 1; i++) {
        for (int j = i + 1; j < student_count; j++) {
            if (students[i].marks > students[j].marks) {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
    printf("Students sorted by marks successfully.\n");
}