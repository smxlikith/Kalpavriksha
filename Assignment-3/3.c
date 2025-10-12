#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 100
#define MAX_SUBJECTS 3

typedef enum {
    A = 'A',
    B = 'B',
    C = 'C',
    D = 'D',
    F = 'F',
    INVALID
} Grade;

typedef struct {
    unsigned int rollNum;
    char name[MAX_CHAR];
    unsigned int marks[MAX_SUBJECTS];
    int totalMarks;
    float averageMarks;
    Grade grade;
} Student;

Grade getGrade(int marks) {
    if (marks < 35) {
        return F;
    } else if (marks < 50) {
        return D;
    } else if (marks < 70) {
        return C;
    } else if (marks < 85) {
        return B;
    } else if (marks <= 100) {
        return A;
    } else {
        return INVALID;
    }
}

void trimNewline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void getMarks(Student *student) {
    int totalMarks = 0;
    printf("Enter the Marks of the Student: \n");

    for (int i = 0; i < MAX_SUBJECTS; i++) {
        printf("\tEnter the Marks of Subject %d: ", i + 1);
        scanf("%d", &student->marks[i]);
        getchar();
        while (student->marks[i] > 100 || student->marks[i] < 0) {
            printf("Entered Invalid Marks for Subject%d[%d], Enter valid Marks:", i, student->marks);
            scanf("%d", &student->marks[i]);
            getchar();
        }
        totalMarks += student->marks[i];
    }

    student->totalMarks = totalMarks;
    student->averageMarks = (float)totalMarks / MAX_SUBJECTS;
    student->grade = getGrade(student->averageMarks);
}

void getUserInput(Student *student) {
    printf("Enter the Roll No. of the Student: ");
    scanf("%d", &student->rollNum);
    getchar();

    printf("Enter the Name of the Student: ");
    fgets(student->name, MAX_CHAR, stdin);
    trimNewline(student->name);

    getMarks(student);
}

int getStudents(Student **students) {
    int N;

    printf("Enter the Number of Students: ");
    scanf("%d", &N);
    if (N <= 0) {
        printf("Invalid Input for Number of Students, N > 0\n");
        exit(0);
    }

    *students = calloc(N, sizeof(Student));
    if (*students == NULL) {
        printf("Unable to Allocate Memory At the Moment Try again Later.\n");
        exit(0);
    }

    for (int i = 0; i < N; i++) {
        getUserInput(&(*students)[i]);
    }

    return N;
}

void printPerformance(Grade grade) {
    if (grade != F) {
        printf("Performance: ");
    }

    if (grade == A) {
        printf("*****\n\n");
    } else if (grade == B) {
        printf("****\n\n");
    } else if (grade == C) {
        printf("***\n\n");
    } else if (grade == D) {
        printf("**\n\n");
    } else if (grade == F) {
        printf("\n");
    }
}

void display(Student *students, int n) {
    for (int i = 0; i < n; i++) {
        Student s = students[i];
        printf("Roll: %u\nName: %s\nTotal: %u\nAverage: %.2f\nGrade: %c\n", s.rollNum, s.name, s.totalMarks, s.averageMarks, s.grade);
        if (s.averageMarks < 35) {
            printf("\n");
            continue;
        }
        printPerformance(s.grade);
    }
}

void displayRollNums(int idx, int N, Student *students) {
    if (idx == N) {
        printf("\n");
        return;
    }
    printf("%d ", students[idx].rollNum);
    displayRollNums(idx + 1, N, students);
}

int main() {
    Student *students;
    int N = getStudents(&students);
    display(students, N);
    printf("List of Roll Numbers (via recursion): ");
    displayRollNums(0, N, students);
    free(students);
    return 0;
}
