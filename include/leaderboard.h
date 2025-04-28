#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include "game_stat.h"
#include <stdbool.h>
#include <SDL3/SDL.h>

typedef struct LeaderboardNode {
    GameStat stat;
    struct LeaderboardNode* next;
} LeaderboardNode;

LeaderboardNode* create_node(GameStat stat);
void insert_leaderboard(LeaderboardNode** head, GameStat stat);
/*void save_leaderboard(LeaderboardNode* head, const char* filename);
LeaderboardNode* load_leaderboard(const char* filename);*/
void free_leaderboard(LeaderboardNode* head);


#endif
