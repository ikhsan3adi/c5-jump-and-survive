#include <stdlib.h>
#include <math.h>
#include "obstacles.h"

Obstacle *create_obstacle(double x, double y, double w, double h, int type) {
    Obstacle *obstacle = (Obstacle *)malloc(sizeof(Obstacle));

    // Inisialisasi posisi & ukuran
    obstacle->entity.transform.x = x;
    obstacle->entity.transform.y = y;
    obstacle->entity.transform.w = w;
    obstacle->entity.transform.h = h;

    // Warna berbeda untuk Saw & Spike
    if (type == SAWS) {
        obstacle->entity.render.color = (SDL_Color){255, 0, 0, 255};  // Merah
        obstacle->rotationSpeed = 480.0f; // 180 derajat per detik
    } else if (type == SPIKE) {
        obstacle->entity.render.color = (SDL_Color){255, 165, 0, 255};  // Hijau
        obstacle->rotationSpeed = 0;  // Spike tidak berputar
    } else if (type == FAKE_COINS) {
        obstacle->entity.render.color = (SDL_Color){255, 215, 0, 255}; // Warna emas
        obstacle->rotationSpeed = 0; // Tidak berputar
    }

    obstacle->rotation = 0;
    return obstacle;
}

void update_obstacle(Obstacle *obstacle, float delta_time) {
    if (obstacle->rotationSpeed != 0) {
        obstacle->rotation += obstacle->rotationSpeed * delta_time;
        if (obstacle->rotation >= 360.0f) {
            obstacle->rotation -= 360.0f;
        }
    }
}

void render_obstacle(SDL_Renderer *renderer, const Obstacle *obstacle) {
    SDL_FRect rect = {
        obstacle->entity.transform.x,
        obstacle->entity.transform.y,
        obstacle->entity.transform.w,
        obstacle->entity.transform.h
    };

    if (obstacle->rotationSpeed != 0) {
        draw_rotating_saw(renderer, rect, obstacle->rotation);
    } else if (obstacle->entity.render.color.r == 255 && 
               obstacle->entity.render.color.g == 215 && 
               obstacle->entity.render.color.b == 0) {
        draw_coin(renderer, rect); // Jika warnanya emas, dianggap Fake Coin
    } else {
        draw_triangle(renderer, rect);
    }
    
}

void destroy_obstacle(Obstacle *obstacle) {
    free(obstacle);
}

// Menggambar Saw (Lingkaran dengan gigi)
void draw_rotating_saw(SDL_Renderer *renderer, SDL_FRect rect, float angle) {
    int cx = rect.x + rect.w / 2;
    int cy = rect.y + rect.h / 2;
    int radius = rect.w / 1.5;
    int innerRadius = radius / 3; // Ukuran lubang tengah
    int spikeLength = radius / 2; // Panjang duri diperbesar
    int spikeCount = 8; // Jumlah duri dikurangi

    // Warna dasar lingkaran hitam
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // Menggambar lingkaran dengan lubang di tengah
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            int dist2 = x * x + y * y;
            if (dist2 <= radius * radius && dist2 >= innerRadius * innerRadius) {
                SDL_FRect pixel = {cx + x, cy + y, 1, 1}; // Kotak kecil 1x1 pixel
                SDL_RenderFillRect(renderer, &pixel);
            }
        }
    }

    // Warna untuk duri
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // Menggambar duri berbentuk segitiga
    for (int i = 0; i < spikeCount; i++) {
        float theta = (angle + i * (360.0 / spikeCount)) * M_PI / 180.0;
        float nextTheta = (angle + (i + 1) * (360.0 / spikeCount)) * M_PI / 180.0;

        // Titik pangkal kiri
        int x1 = cx + cos(theta) * radius;
        int y1 = cy + sin(theta) * radius;

        // Titik pangkal kanan
        int x2 = cx + cos(nextTheta) * radius;
        int y2 = cy + sin(nextTheta) * radius;

        // Titik ujung lancip (lebih keluar)
        int x3 = cx + cos((theta + nextTheta) / 2) * (radius + spikeLength);
        int y3 = cy + sin((theta + nextTheta) / 2) * (radius + spikeLength);

        // Menggambar segitiga duri
        SDL_RenderLine(renderer, x1, y1, x3, y3);
        SDL_RenderLine(renderer, x2, y2, x3, y3);
        SDL_RenderLine(renderer, x1, y1, x2, y2);
    }
}
void draw_triangle(SDL_Renderer *renderer, SDL_FRect rect) {
    float scale = 1.5;
    float newW = rect.w * scale;
    float newH = rect.h * scale;
    
    float centerX = rect.x + (rect.w / 2) - (newW / 2);
    float centerY = rect.y + (rect.h / 2) - (newH / 2);

    // Menyempitkan alas segitiga (misalnya, 70% dari lebar awal)
    float baseFactor = 0.5;
    float baseWidth = newW * baseFactor;

    // Titik-titik segitiga lancip
    int x1 = centerX + newW / 2;  // Titik atas
    int y1 = centerY;
    int x2 = centerX + (newW - baseWidth) / 2; // Kiri bawah (lebih ke tengah)
    int y2 = centerY + newH;
    int x3 = x2 + baseWidth; // Kanan bawah (lebih ke tengah)
    int y3 = y2;

    SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255);
    for (int y = y1; y <= y2; y++) {
        float startX = x1 + (x2 - x1) * ((float)(y - y1) / (y2 - y1));
        float endX = x1 + (x3 - x1) * ((float)(y - y1) / (y3 - y1));
        SDL_RenderLine(renderer, startX, y, endX, y);
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderLine(renderer, x1, y1, x2, y2);
    SDL_RenderLine(renderer, x2, y2, x3, y3);
    SDL_RenderLine(renderer, x3, y3, x1, y1);
}

void draw_coin(SDL_Renderer *renderer, SDL_FRect rect) {
    int cx = rect.x + rect.w / 2;
    int cy = rect.y + rect.h / 2;
    int radius = rect.w / 3; // Pastikan width = height agar lingkaran sempurna

    SDL_SetRenderDrawColor(renderer, 255, 215, 0, 255); // Warna emas

    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w; // Jarak dari titik tengah ke x
            int dy = radius - h; // Jarak dari titik tengah ke y
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderPoint(renderer, cx + dx, cy + dy);
            }
        }
    }
}

