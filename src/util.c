#include <stdio.h>
#include <stdlib.h>
#include "util.h"

char *get_time_string(unsigned int time) {
    // Alokasi memori untuk string waktu
    char *time_string = (char *)malloc(20 * sizeof(char));
    
    if (time_string == NULL) {
        return NULL; // Jika gagal mengalokasi memori
    }

    unsigned int hours = time / 3600;        // Menghitung jam
    unsigned int minutes = (time % 3600) / 60; // Menghitung menit
    unsigned int seconds = time % 60;       // Menghitung detik

    // Formatkan string berdasarkan waktu
    if (hours > 0) {
        sprintf(time_string, "%uh %um %us", hours, minutes, seconds);
    } else if (minutes > 0) {
        sprintf(time_string, "%um %us", minutes, seconds);
    } else {
        sprintf(time_string, "%us", seconds);
    }

    return time_string;
}
