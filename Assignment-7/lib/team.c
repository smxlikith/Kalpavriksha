#include "performanceAnalyzer.h"

Team* createTeam(int id, const char* name) {
    Team* t = malloc(sizeof(Team));
    if (t == NULL) {
        return NULL;
    }
    t->id = id;
    t->name = malloc(sizeof(strlen(name)));
    t->Players = malloc(3 * sizeof(Player*));
    t->totalPlayers = 0;
    t->avgBattingStrikeRate = 0;
    for (int i = 0; i < 3; i++) {
        t->Players[i] = NULL;
    }
    strcpy(t->name, name);
    return t;
}

Team** sortTeamsByAvgStrikeRate(Team** src) {
    Team** teams = malloc(teamCount * sizeof(Team*));
    if (teams == NULL) {
        printf("Unalbe to allocate Memory, Try Again Later...");
        exit(1);
    }
    for (int i = 0; i < teamCount; i++) {
        teams[i] = src[i];
    }
    for (int i = 0; i < teamCount; i++) {
        for (int j = 0; j < teamCount - i - 1; j++) {
            if (teams[j]->avgBattingStrikeRate < teams[j + 1]->avgBattingStrikeRate) {
                Team* temp = teams[j];
                teams[j] = teams[j + 1];
                teams[j + 1] = temp;
            }
        }
    }
    return teams;
}

float calculateAvgBattingStrikeRate(Team* team) {
    int totalBatters = 0;
    float totalStrikeRate = 0;
    for (int i = 0; i < 2; i++) {
        Player* curr = team->Players[i];
        while (curr != NULL) {
            totalStrikeRate += curr->data->strikeRate;
            totalBatters++;
            curr = curr->next;
        }
    }
    return (float)totalStrikeRate / totalBatters;
}

void freeTeams(Team** teams) {
    for (int i = 0; i < teamCount; i++) {
        Player** players = teams[i]->Players;
        for (int j = 0; j < 3; j++) {
            if (players[i] != NULL) {
                Player *curr = players[j], *temp;
                curr = curr->next;
                while (curr != NULL) {
                    temp = curr;
                    if (curr != NULL) {
                        curr = curr->next;
                    }
                    free(temp);
                }
            }
            players[j] = NULL;
        }
        free(players);
    }
    free(teams);
}