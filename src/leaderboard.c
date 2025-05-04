#include "leaderboard.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL3/SDL.h>

// Fungsi pembanding: apakah a lebih unggul dari b?
bool is_greater(GameStat a, GameStat b) {
    return (a.score > b.score) ||
           (a.score == b.score && a.elapsed_time < b.elapsed_time);
}
// Buat node leaderboard baru
LeaderboardNode* create_node(GameStat stat) {
    LeaderboardNode* new_node = (LeaderboardNode*)malloc(sizeof(LeaderboardNode));
    if (!new_node) return NULL;
    new_node->stat = stat;
    new_node->next = NULL;
    return new_node;
}

// Masukkan node ke leaderboard (urut + maksimal 10 entri)
void insert_leaderboard(LeaderboardNode** head, GameStat stat) {
    if (!head) return;

    LeaderboardNode* new_node = create_node(stat);
    if (!new_node) return;

    // Cek jika harus jadi head
    if (*head == NULL || is_greater(stat, (*head)->stat)) {
        new_node->next = *head;
        *head = new_node;
    } else {
        LeaderboardNode* current = *head;

        while (current->next && !is_greater(stat, current->next->stat)) {
            current = current->next;
        }

        new_node->next = current->next;
        current->next = new_node;
    }

    // Hapus node ke-11 jika ada
    LeaderboardNode* current = *head;
    int count = 1;
    while (current && current->next) {
        if (++count == MAX_LEADERBOARD && current->next->next) {
            // Hapus node ke-11
            free(current->next->next);
            current->next->next = NULL;
            break;
        }
        current = current->next;
    }
}

// Bebaskan semua node leaderboard
void free_leaderboard(LeaderboardNode* head) {
    while (head) {
        LeaderboardNode* temp = head;
        head = head->next;
        free(temp);
    }
}

// (Opsional) Tampilkan leaderboard ke konsol
void print_leaderboard(const LeaderboardNode* head) {
    int rank = 1;
    while (head) {
        printf("#%d - Score: %d | Time: %d sec\n", rank++, head->stat.score, head->stat.elapsed_time);
        head = head->next;
    }
}

void save_leaderboard(const char* filename, LeaderboardNode* head) {
    FILE* file = fopen(filename, "wb");
    if (!file) return;

    int count = 0;
    while (head && count++ < MAX_LEADERBOARD) {
        fwrite(&head->stat, sizeof(GameStat), 1, file);
        head = head->next;
    }

    fclose(file);
}

LeaderboardNode* load_leaderboard(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) return NULL;

    LeaderboardNode* head = NULL;
    GameStat temp_stat;

    while (fread(&temp_stat, sizeof(GameStat), 1, file) == 1) {
        insert_leaderboard(&head, temp_stat);
    }

    fclose(file);
    return head;
}

