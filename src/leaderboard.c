#include "leaderboard.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>

// Membuat node leaderboard baru
LeaderboardNode* create_node(GameStat stat) {
    LeaderboardNode* new_node = (LeaderboardNode*)malloc(sizeof(LeaderboardNode));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->stat = stat;
    new_node->next = NULL;
    return new_node;
}

// Menyisipkan node ke leaderboard dengan urutan berdasarkan skor dan timer
void insert_leaderboard(LeaderboardNode** head, GameStat stat) {
    LeaderboardNode* new_node = create_node(stat);
    if (!new_node) return;

    if (*head == NULL || 
        stat.score > (*head)->stat.score || 
        (stat.score == (*head)->stat.score && stat.elapsed_time < (*head)->stat.elapsed_time)) {
        new_node->next = *head;
        *head = new_node;
    } else {
        LeaderboardNode* current = *head;
        while (current->next != NULL && 
              (current->next->stat.score > stat.score || 
              (current->next->stat.score == stat.score && current->next->stat.elapsed_time <= stat.elapsed_time))) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

/*void save_leaderboard(LeaderboardNode* head, const char* filename) {
    FILE* file = fopen(filename, "a");  // Mode "a" untuk menambahkan data di akhir file
    if (!file) {
        perror("Save leaderboard error");
        return;
    }

    LeaderboardNode* current = head;
    while (current != NULL) {
        // Menyimpan score dan elapsed_time dalam format teks
        fprintf(file, "%d|%.2f\n", current->stat.score, current->stat.elapsed_time / 1000.0);
        current = current->next;
    }

    fclose(file);
    printf("Leaderboard berhasil disimpan ke file %s\n", filename);
}*/

// Memuat leaderboard dari file biner
/*LeaderboardNode* load_leaderboard(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        return NULL;
    }

    LeaderboardNode* head = NULL;
    GameStat temp_stat;
    while (fread(&temp_stat, sizeof(GameStat), 1, file) == 1) {
        insert_leaderboard(&head, temp_stat);
    }

    fclose(file);
    return head;
}*/

// Menghapus semua node leaderboard
void free_leaderboard(LeaderboardNode* head) {
    while (head != NULL) {
        LeaderboardNode* temp = head;
        head = head->next;
        free(temp);
    }
}

