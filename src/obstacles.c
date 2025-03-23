#include <stdlib.h>
#include <math.h>
#include "obstacles.h"

// Menggambar Saw (Lingkaran dengan gigi)
void draw_rotating_saw(SDL_Renderer *renderer, SDL_FRect rect, float angle)
{
    int cx = rect.x + rect.w / 2;
    int cy = rect.y + rect.h;
    int radius = rect.w / 2;
    int innerRadius = radius / 3; // Ukuran lubang tengah
    int spikeLength = radius / 2; // Panjang duri diperbesar
    int spikeCount = 8;           // Jumlah duri dikurangi

    // Warna dasar lingkaran hitam
    // SDL_SetRenderDrawColor(renderer, 10, 55, 58, 255);

    // Menggambar lingkaran dengan lubang di tengah
    for (int y = -radius; y <= radius; y++)
    {
        for (int x = -radius; x <= radius; x++)
        {
            int dist2 = x * x + y * y;
            if (dist2 <= radius * radius && dist2 >= innerRadius * innerRadius)
            {
                SDL_FRect pixel = {cx + x, cy + y, 1, 1}; // Kotak kecil 1x1 pixel
                SDL_RenderFillRect(renderer, &pixel);
            }
        }
    }

    // Warna untuk duri
    // SDL_SetRenderDrawColor(renderer, 10, 55, 58, 255);

    SDL_FColor color;
    SDL_GetRenderDrawColorFloat(renderer, &color.r, &color.g, &color.b, &color.a);
    // Menggambar duri berbentuk segitiga
    for (int i = 0; i < spikeCount; i++)
    {
        float theta = (angle + i * (360.0 / spikeCount)) * PI / 180.0;
        float nextTheta = (angle + (i + 1) * (360.0 / spikeCount)) * PI / 180.0;
        // Titik pangkal kiri
        double x1 = cx + cos(theta) * radius;
        double y1 = cy + sin(theta) * radius;

        // Titik pangkal kanan
        double x2 = cx + cos(nextTheta) * radius;
        double y2 = cy + sin(nextTheta) * radius;

        // Titik ujung lancip (lebih keluar)
        double x3 = cx + cos((theta + nextTheta) / 2) * (radius + spikeLength);
        double y3 = cy + sin((theta + nextTheta) / 2) * (radius + spikeLength);

        // ambil warna draw color saat ini

        // Menggambar segitiga duri

        SDL_Vertex vertexes[3] = {
            {{x1, y1}, {color.r, color.g, color.b, color.a}},
            {{x2, y2}, {color.r, color.g, color.b, color.a}},
            {{x3, y3}, {color.r, color.g, color.b, color.a}},
        };

        SDL_RenderGeometry(renderer, NULL, vertexes, 3, NULL, 0);
    }
}

void draw_triangle(SDL_Renderer *renderer, SDL_FRect rect)
{
    float scale = 1;
    float newW = rect.w * scale;
    float newH = rect.h * scale;

    float centerX = rect.x + (rect.w / 2) - (newW / 2);
    float centerY = rect.y + (rect.h / 2) - (newH / 2);

    // Menyempitkan alas segitiga (misalnya, 70% dari lebar awal)
    float baseFactor = 1;
    float baseWidth = newW * baseFactor;

    // Titik-titik segitiga lancip
    double x1 = centerX + newW / 2; // Titik atas
    double y1 = centerY;
    double x2 = centerX + (newW - baseWidth) / 2; // Kiri bawah (lebih ke tengah)
    double y2 = centerY + newH;
    double x3 = x2 + baseWidth; // Kanan bawah (lebih ke tengah)
    double y3 = y2;

    // ambil warna draw color saat ini
    SDL_FColor color;
    SDL_GetRenderDrawColorFloat(renderer, &color.r, &color.g, &color.b, &color.a);

    // Menggambar segitiga duri

    SDL_Vertex vertexes[3] = {
        {{x1, y1}, {color.r, color.g, color.b, color.a}},
        {{x2, y2}, {color.r, color.g, color.b, color.a}},
        {{x3, y3}, {color.r, color.g, color.b, color.a}},
    };

    SDL_RenderGeometry(renderer, NULL, vertexes, 3, NULL, 0);
}

void draw_coin(SDL_Renderer *renderer, SDL_FRect rect, int type)
{
    int cx = rect.x + rect.w / 2;
    int cy = rect.y + rect.h / 2;
    int radius = rect.w / 3; // Pastikan width = height agar lingkaran sempurna

    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w; // Jarak dari titik tengah ke x
            int dy = radius - h; // Jarak dari titik tengah ke y
            if ((dx * dx + dy * dy) <= (radius * radius))
            {
                SDL_RenderPoint(renderer, cx + dx, cy + dy);
            }
        }
    }
}

void draw_gate(SDL_Renderer *renderer, SDL_FRect exit_rect)
{
    int frame_thickness = 8;          // Ketebalan bingkai
    int arc_height = exit_rect.h / 3; // Tinggi lengkungan

    // Warna bingkai pintu (Cokelat tua)
    SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255);

    // Kotak bingkai samping kiri
    SDL_FRect left_pillar = {
        exit_rect.x - frame_thickness,
        exit_rect.y,
        frame_thickness,
        exit_rect.h * 2};
    SDL_RenderFillRect(renderer, &left_pillar);

    // Kotak bingkai samping kanan
    SDL_FRect right_pillar = {
        exit_rect.x + exit_rect.w * 2,
        exit_rect.y,
        frame_thickness,
        exit_rect.h * 2};
    SDL_RenderFillRect(renderer, &right_pillar);

    // Kotak bingkai atas (melengkung)
    SDL_FRect top_frame = {
        exit_rect.x, // Mulai dari posisi x pintu, bukan dari bingkai kiri
        exit_rect.y - arc_height,
        exit_rect.w * 2, // Lebar hanya sebesar pintu, tidak termasuk bingkai kiri dan kanan
        arc_height};
    SDL_RenderFillRect(renderer, &top_frame);
}