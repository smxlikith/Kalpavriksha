#include "performanceAnalyzer.h"

void displayPlayers(Team** teams, int teamId) {
    if (teamId > teamCount || teamId <= 0) {
        printf("Error: No team with Id: %d\n", teamId);
        return;
    }
    Team* team = teams[teamId - 1];
    printf("Players of Team %s:\n", team->name);

    printf("====================================================================================\n");
    printf(" %-4s  %-25s %-12s %-6s %-5s %-5s %-6s %-4s %-12s\n",
           "ID", "Name", "Role", "Runs", "Avg", "SR", "Wkts", "ER", "Perf.Index");
    printf("====================================================================================\n");

    for (int i = 0; i < 3; i++) {
        Player* curr = team->Players[i];
        while (curr != NULL) {
            printf(" %-4d  %-25s %-12s %-6d %-5.1f %-5.1f %-6d %-4.1f %-12.2f\n",
                   curr->data->id, curr->data->name, roles[curr->role],
                   curr->data->totalRuns, curr->data->battingAverage, curr->data->strikeRate,
                   curr->data->wickets, curr->data->economyRate, curr->performanceIndex);
            curr = curr->next;
        }
    }
    printf("\nTotal Players: %d\n", team->totalPlayers);
    printf("Average Batting Strike Rate: %.2f\n", team->avgBattingStrikeRate);
}

void displayTeamsByAvgBattingStrikeRate(Team** teams) {
    printf(" =========================================================\n");
    printf(" %-4s %-15s %-12s %-14s\n", "ID", "Team Name", "Avg.Bat SR", "Total Players");
    printf(" =========================================================\n");
    for (int i = 0; i < teamCount; i++) {
        printf(" %-4d %-15s %-12.2f %-14d\n", teams[i]->id, teams[i]->name, teams[i]->avgBattingStrikeRate, teams[i]->totalPlayers);
    }
}

void displayTopKBySpecifiRole(Team** teams, int teamId, int k, Role role) {
    if (teamId > teamCount || teamId <= 0) {
        printf("Error: No team with Id: %d\n", teamId);
        return;
    }
    Player* curr = teams[teamId - 1]->Players[role];
    printf("Top %d %s of Team %s\n", k, roles[role], teams[teamId - 1]->name);
    printf("====================================================================================\n");
    printf(" %-4s  %-25s %-12s %-6s %-5s %-5s %-6s %-4s %-12s\n",
           "ID", "Name", "Role", "Runs", "Avg", "SR", "Wkts", "ER", "Perf.Index");
    printf("====================================================================================\n");
    while (curr != NULL && k > 0) {
        printf(" %-4d  %-25s %-12s %-6d %-5.1f %-5.1f %-6d %-4.1f %-12.2f\n",
               curr->data->id, curr->data->name, roles[curr->role],
               curr->data->totalRuns, curr->data->battingAverage, curr->data->strikeRate,
               curr->data->wickets, curr->data->economyRate, curr->performanceIndex);
        curr = curr->next;
        k--;
    }
}

void displayAllPlayersByRoleByPI(Team** teams, Role role) {
    Heap* heap = initHeap(teams, role);
    Player** players = heap->heap;
    int size = heap->size;
    Player* curr = pop(heap);

    printf("====================================================================================\n");
    printf(" %-4s  %-25s %-12s %-6s %-5s %-5s %-6s %-4s %-12s\n",
           "ID", "Name", "Role", "Runs", "Avg", "SR", "Wkts", "ER", "Perf.Index");
    printf("====================================================================================\n");

    while (curr != NULL) {
        printf(" %-4d  %-25s %-12s %-6d %-5.1f %-5.1f %-6d %-4.1f %-12.2f\n",
               curr->data->id, curr->data->name, roles[curr->role],
               curr->data->totalRuns, curr->data->battingAverage, curr->data->strikeRate,
               curr->data->wickets, curr->data->economyRate, curr->performanceIndex);
        if (curr->next != NULL) {
            push(heap, curr->next);
        }
        curr = pop(heap);
    }
}
