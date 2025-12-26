#include "performanceAnalyzer.h"

void calculatePerformanceIndex(Player* p) {
    if (p->role == 0) {
        p->performanceIndex = ((p->data->battingAverage * p->data->strikeRate) / 100) + (p->data->wickets * 2);
    } else if (p->role == 1) {
        p->performanceIndex = ((p->data->battingAverage * p->data->strikeRate) / 100);
    } else if (p->role == 2) {
        p->performanceIndex = (p->data->wickets * 2) + (100 - p->data->economyRate);
    }
}

Player* createPlayer(const PlayerData* data) {
    Player* p = malloc(sizeof(Player));
    if (p == NULL) {
        return NULL;
    }
    p->data = data;
    if (strcmp(data->role, "All-rounder") == 0) {
        p->role = AllRounder;
    } else if (strcmp(data->role, "Batsman") == 0) {
        p->role = Batsman;
    } else if (strcmp(data->role, "Bowler") == 0) {
        p->role = Bowler;
    }
    calculatePerformanceIndex(p);
    return p;
}

void addPlayer(Team** teams, const PlayerData* data) {
    Player* p = createPlayer(data);
    if (p == NULL) {
        printf("Unalbe to Create Player, Try Again Later...");
        exit(1);
    }
    for (int i = 0; i < teamCount; i++) {
        if (strcmp(teams[i]->name, p->data->team) == 0) {
            Team* team = teams[i];
            team->totalPlayers++;

            Player* head = team->Players[p->role];

            if (head == NULL) {
                team->Players[p->role] = p;
                p->next = NULL;
                p->prev = NULL;
                return;
            }

            Player* curr = head;

            while (curr->next != NULL && curr->performanceIndex > p->performanceIndex) {
                curr = curr->next;
            }

            if (curr->performanceIndex < p->performanceIndex) {
                p->next = curr;
                p->prev = curr->prev;
                if (curr->prev != NULL) {
                    curr->prev->next = p;
                } else {
                    team->Players[p->role] = p;
                }
                curr->prev = p;
            } else {
                p->prev = curr;
                p->next = curr->next;
                if (curr->next != NULL) {
                    curr->next->prev = p;
                }
                curr->next = p;
            }
            break;
        }
    }
}