#ifndef TEAM_H
#define TEAM_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../data/Players_data.h"

typedef struct Player Player;

typedef enum {
    AllRounder,
    Batsman,
    Bowler
} Role;

static const char roles[3][20] = {"All-Rounder", "Batsman", "Bowler"};

struct Player {
    const PlayerData* data;
    Role role;
    float performanceIndex;
    Player* prev;
    Player* next;
};

typedef struct Team Team;
struct Team {
    int id;
    char* name;
    Player** Players;
    int totalPlayers;
    float avgBattingStrikeRate;
};

typedef struct {
    Player** heap;
    int size;
} Heap;

Player* createPlayer(const PlayerData* data);
void addPlayer(Team** teams, const PlayerData* data);

Team* createTeam(int id, const char* name);
float calculateAvgBattingStrikeRate(Team* team);
Team** sortTeamsByAvgStrikeRate(Team** src);
void freeTeams(Team** teams);

void displayPlayers(Team** teams, int teamId);
void displayTeamsByAvgBattingStrikeRate(Team** teams);
void displayTopKBySpecifiRole(Team** teams, int teamId, int k, Role role);
void displayAllPlayersByRoleByPI(Team** teams, Role role);

Heap* initHeap(Team** teams, Role role);
void heapify(Heap* heap);
Player* push(Heap* heap, Player* player);
Player* pop(Heap* heap);

#endif