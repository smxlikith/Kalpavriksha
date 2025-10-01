#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "users.txt"

struct User {
    int id;
    char name[100];
    int age;
};

void trimNewline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void createUser();
void readUsers();
void updateUser();
void deleteUser();

int main() {
    int choice;
    while (1) {
        printf("\n===== User Management System =====\n");
        printf("1. Create User\n");
        printf("2. Read Users\n");
        printf("3. Update User\n");
        printf("4. Delete User\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: createUser(); break;
            case 2: readUsers(); break;
            case 3: updateUser(); break;
            case 4: deleteUser(); break;
            case 5: printf("Exiting...\n"); exit(0);
            default: printf("Invalid choice, try again!\n");
        }
    }
    return 0;
}

void createUser() {
    FILE *fp = fopen(FILE_NAME, "a+");
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    struct User user;
    printf("Enter ID: ");
    scanf("%d", &user.id);
    getchar();

    printf("Enter Name: ");
    fgets(user.name, sizeof(user.name), stdin);
    trimNewline(user.name);

    printf("Enter Age: ");
    scanf("%d", &user.age);

    struct User temp;
    rewind(fp);
    while (fscanf(fp, "%d,%99[^,],%d\n", &temp.id, temp.name, &temp.age) == 3) {
        if (temp.id == user.id) {
            printf("User with ID %d already exists!\n", user.id);
            fclose(fp);
            return;
        }
    }

    fprintf(fp, "%d,%s,%d\n", user.id, user.name, user.age);
    fclose(fp);
    printf("User added successfully!\n");
}

void readUsers() {
    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) {
        printf("No users found.\n");
        return;
    }

    struct User user;
    printf("\n--- User Records ---\n");
    while (fscanf(fp, "%d,%99[^,],%d\n", &user.id, user.name, &user.age) == 3) {
        printf("ID: %d, Name: %s, Age: %d\n", user.id, user.name, user.age);
    }
    fclose(fp);
}

void updateUser() {
    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) {
        printf("No users found.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (!tempFile) {
        printf("Error creating temp file.\n");
        fclose(fp);
        return;
    }

    int id, found = 0;
    struct User user;
    printf("Enter ID to update: ");
    scanf("%d", &id);
    getchar();

    while (fscanf(fp, "%d,%99[^,],%d\n", &user.id, user.name, &user.age) == 3) {
        if (user.id == id) {
            found = 1;
            printf("Enter new Name: ");
            fgets(user.name, sizeof(user.name), stdin);
            trimNewline(user.name);

            printf("Enter new Age: ");
            scanf("%d", &user.age);
            getchar();
        }
        fprintf(tempFile, "%d,%s,%d\n", user.id, user.name, user.age);
    }

    fclose(fp);
    fclose(tempFile);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found) {
        printf("User updated successfully!\n");
    } else {
        printf("No user found with ID %d\n", id);
    }
}

void deleteUser() {
    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) {
        printf("No users found.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (!tempFile) {
        printf("Error creating temp file.\n");
        fclose(fp);
        return;
    }

    int id, found = 0;
    struct User user;
    printf("Enter ID to delete: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d,%99[^,],%d\n", &user.id, user.name, &user.age) == 3) {
        if (user.id == id) {
            found = 1;
            continue;
        }
        fprintf(tempFile, "%d,%s,%d\n", user.id, user.name, user.age);
    }

    fclose(fp);
    fclose(tempFile);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found) {
        printf("User deleted successfully!\n");
    } else {
        printf("No user found with ID %d\n", id);
    }
}
