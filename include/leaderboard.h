#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#define MAX_LEADERBOARD 10

#define LEADERBOARD_FILE "leaderboard.dat"

#include "game_stat.h"
#include <stdbool.h>
#include <SDL3/SDL.h>

typedef struct LeaderboardNode
{
    GameStat stat;
    struct LeaderboardNode *next;
} LeaderboardNode;

extern LeaderboardNode *leaderboard_head;

LeaderboardNode *create_node(GameStat stat);
bool is_greater(GameStat a, GameStat b);
void insert_leaderboard(LeaderboardNode **head, GameStat stat);
void free_leaderboard(LeaderboardNode *head);
void print_leaderboard(const LeaderboardNode *head);
void save_leaderboard(const char *filename, LeaderboardNode *head);
LeaderboardNode *load_leaderboard(const char *filename);

#endif
