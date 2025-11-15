
#include "lib/performanceAnalyzer.h"

void loadData(Team*** teams) {
    *teams = malloc(teamCount * sizeof(Team*));

    if (teams == NULL) {
        printf("Unable to Allocate Memory, try again...\n");
        exit(1);
    }

    for (int i = 0; i < teamCount; i++) {
        (*teams)[i] = createTeam(i + 1, teamNames[i]);
        if ((*teams)[i] == NULL) {
            printf("Unable to Allocate Memory, try again...\n");
            exit(1);
        }
    }

    for (int i = 0; i < playerCount; i++) {
        addPlayer(*teams, &data[i]);
    }

    for (int i = 0; i < teamCount; i++) {
        Team* team = (*teams)[i];
        team->avgBattingStrikeRate = calculateAvgBattingStrikeRate(team);
    }
}

void menu(Team** teams) {
    Team** teamsSorted = sortTeamsByAvgStrikeRate(teams);
    int choice;
    while (1) {
        printf("==============================================================================\n");
        printf("ICC ODI Player Performance Analyzer\n");
        printf("==============================================================================\n");
        printf("1. Display Players of a Specific Team\n");
        printf("2. Display Teams by Average Batting Strike Rate\n");
        printf("3. Display Top K Players of a Specific Team by Role\n");
        printf("4. Display all Players of Specific Role Across All Teams by Performance Index\n");
        printf("5. Exit\n");
        printf("==============================================================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: {
                int teamId;
                printf("Enter Team ID: ");
                scanf("%d", &teamId);
                printf("\n");
                displayPlayers(teams, teamId);
                break;
            }
            case 2:
                displayTeamsByAvgBattingStrikeRate(teamsSorted);
                break;
            case 3: {
                int teamId, k;
                Role role;
                printf("Enter Team ID: ");
                scanf("%d", &teamId);
                printf("Enter number of top players to display (K): ");
                scanf("%d", &k);
                printf("Enter Role (0 = All-Rounder, 1 = Batsman, 2 = Bowler): ");
                scanf("%d", (int*)&role);
                printf("\n");
                displayTopKBySpecifiRole(teams, teamId, k, role);
                break;
            }
            case 4: {
                Role role;
                printf("Enter Role (0 = All-Rounder, 1 = Batsman, 2 = Bowler): ");
                scanf("%d", (int*)&role);
                printf("\n");
                displayAllPlayersByRoleByPI(teams, role);
                break;
            }
            case 5:
                freeTeams(teams);
                free(teamsSorted);
                printf("Exiting program...\n");
                exit(0);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        printf("\n");
    }
}

int main() {
    Team** teams;
    loadData(&teams);
    menu(teams);
}