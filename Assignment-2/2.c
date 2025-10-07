#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "users.txt"

typedef enum{
    SUCCESS,
    FAILURE, 
} Status;

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

void getUserID(struct User *user){
    printf("\tEnter ID: ");
    scanf("%d", &user->id);
    getchar();
}

void getUserInfo(struct User *user){
    printf("\tEnter Name: ");
    fgets(user->name, sizeof(user->name), stdin);
    trimNewline(user->name);

    printf("\tEnter Age: ");
    scanf("%d", &user->age);
}

Status createUser();
Status readUsers();
Status updateUser();
Status deleteUser();

int main() {

    system("clear");

    int choice;
    Status status;

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
            case 1: status = createUser(); break;
            case 2: status = readUsers(); break;
            case 3: status = updateUser(); break;
            case 4: status = deleteUser(); break;
            case 5: printf("Exiting...\n"); exit(0);
            default: printf("Invalid choice, try again!\n");
        }

        if(status == FAILURE){
            exit(0);
        }
    }
    return 0;
}

Status createUser() {

    system("clear");

    FILE *fp = fopen(FILE_NAME, "a+");
    if (!fp) {
        printf("Error opening file!\n");
        return FAILURE;
    }

    struct User user;
    printf("Creating a User:\n");
    getUserID(&user);
    getUserInfo(& user);

    struct User temp;
    rewind(fp);
    while (fscanf(fp, "%d,%99[^,],%d\n", &temp.id, temp.name, &temp.age) == 3) {
        if (temp.id == user.id) {
            printf("User with ID %d already exists!\n", user.id);
            fclose(fp);
            return FAILURE;
        }
    }

    fprintf(fp, "%d,%s,%d\n", user.id, user.name, user.age);
    fclose(fp);
    printf("User added successfully!\n");
    return SUCCESS;
}

Status readUsers() {

    system("clear");

    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) {
        printf("No users found.\n");
        return FAILURE;
    }

    struct User user;
    printf("\n--- User Records ---\n");
    while (fscanf(fp, "%d,%99[^,],%d\n", &user.id, user.name, &user.age) == 3) {
        printf("ID: %d, Name: %s, Age: %d\n", user.id, user.name, user.age);
    }
    fclose(fp);

    return SUCCESS;
}

Status updateUser() {

    system("clear");

    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) {
        printf("No users found.\n");
        return FAILURE;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (!tempFile) {
        printf("Error creating temp file.\n");
        fclose(fp);
        return FAILURE;
    }

    int id, found = 0;
    struct User user;
    printf("Enter ID to update: ");
    scanf("%d", &id);
    getchar();

    while (fscanf(fp, "%d,%99[^,],%d\n", &user.id, user.name, &user.age) == 3) {
        if (user.id == id) {
            found = 1;
            printf("Enter the New Info:\n");
            getUserInfo(&user);
        }
        fprintf(tempFile, "%d,%s,%d\n", user.id, user.name, user.age);
    }

    fclose(fp);
    fclose(tempFile);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found) {
        printf("User updated successfully!\n");
        return SUCCESS;
    } else {
        printf("No user found with ID %d\n", id);
    }
    return FAILURE;
}

Status deleteUser() {

    system("clear");

    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) {
        printf("No users found.\n");
        return FAILURE;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (!tempFile) {
        printf("Error creating temp file.\n");
        fclose(fp);
        return FAILURE;
    }

    int id, found = 0;
    struct User user;
    printf("Enter ID to Delete: ");
    scanf("%d", &id);
    getchar();

    while (fscanf(fp, "%d,%99[^,],%d\n", &user.id, user.name, &user.age) == 3) {
        if (user.id == id) {
            found = 1;
            printf("\n--- User Records ---\n");
            printf("%d, %s, %d\n\n", user.id, user.name, user.age);
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
        return SUCCESS;
    } else {
        printf("No user found with ID %d\n", id);
    }
    return FAILURE;
}
