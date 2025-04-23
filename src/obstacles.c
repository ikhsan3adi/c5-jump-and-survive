#include <stdlib.h>
#include <math.h>
#include "obstacles.h"
#include "level.h"

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

SawManager saw_manager;

Saw *create_saw(float x, float y, float w, float h, float velocity_x, float velocity_y)
{
    Saw *saw = malloc(sizeof(Saw)); // Allocate memory for the saw
    if (saw == NULL)
    {
        SDL_Log("Failed to allocate memory for saw!");
        return NULL;
    }
    saw->transform.x = x;
    saw->transform.y = y;
    saw->transform.w = w;
    saw->transform.h = h;
    saw->physics.velocity_x = velocity_x;
    saw->physics.velocity_y = velocity_y;
    return saw;
}

void update_saw(Saw *saw, float delta_time)
{
    saw->transform.x += saw->physics.velocity_x * delta_time;
    saw->transform.y += saw->physics.velocity_y * delta_time;
}

void render_saw(SDL_Renderer *renderer, Saw *saw, float angle)
{
    int cx = saw->transform.x + saw->transform.w / 2;
    int cy = saw->transform.y + saw->transform.h / 2;
    int radius = saw->transform.w / 2;
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

void add_saw(SawManager *manager, float x, float y, float w, float h, float velocity_x, float velocity_y)
{
    if (manager->count >= MAX_SAWS)
    {
        SDL_Log("Maximum number of saws reached!");
        return;
    }

    manager->saws[manager->count] = create_saw(x, y, w, h, velocity_x, velocity_y);
    if (manager->saws[manager->count] != NULL)
    {
        manager->count++;
    }
}

void update_all_saws(SawManager *manager, float delta_time)
{
    for (int i = 0; i < manager->count; i++)
    {
        Saw *saw = manager->saws[i];

        // Store previous position for collision resolution
        // float prev_x = saw->transform.x;
        // float prev_y = saw->transform.y;

        // Update position based on velocity
        saw->transform.x += saw->physics.velocity_x * delta_time;
        saw->transform.y += saw->physics.velocity_y * delta_time;

        // Boundary handling for level edges
        float level_min_x = 0;
        float level_max_x = MAP_WIDTH * TILE_SIZE;
        float level_min_y = 0;
        float level_max_y = MAP_HEIGHT * TILE_SIZE;

        // Check for boundary collision
        int bounced = 0;

        if (saw->transform.x < level_min_x)
        {
            saw->transform.x = level_min_x;
            saw->physics.velocity_x *= -1; // Reverse horizontal direction
            bounced = 1;
        }
        else if (saw->transform.x + saw->transform.w > level_max_x)
        {
            saw->transform.x = level_max_x - saw->transform.w;
            saw->physics.velocity_x *= -1; // Reverse horizontal direction
            bounced = 1;
        }

        if (saw->transform.y < level_min_y)
        {
            saw->transform.y = level_min_y;
            saw->physics.velocity_y *= -1; // Reverse vertical direction
            bounced = 1;
        }
        else if (saw->transform.y + saw->transform.h > level_max_y)
        {
            saw->transform.y = level_max_y - saw->transform.h;
            saw->physics.velocity_y *= -1; // Reverse vertical direction
            bounced = 1;
        }

        // Check for collision with walls in the map
        if (!bounced)
        {
            // Check corners of the saw for wall collision
            int corners[4][2] = {
                {saw->transform.x, saw->transform.y},                                      // Top-left
                {saw->transform.x + saw->transform.w, saw->transform.y},                   // Top-right
                {saw->transform.x, saw->transform.y + saw->transform.h},                   // Bottom-left
                {saw->transform.x + saw->transform.w, saw->transform.y + saw->transform.h} // Bottom-right
            };

            for (int c = 0; c < 4; c++)
            {
                int tile_x = corners[c][0] / TILE_SIZE;
                int tile_y = corners[c][1] / TILE_SIZE;

                // Make sure we're within map bounds
                if (tile_x >= 0 && tile_x < MAP_WIDTH && tile_y >= 0 && tile_y < MAP_HEIGHT)
                {
                    // Check if we hit a wall (value 1 in level9_map)
                    if (current_level_map[tile_y][tile_x] == 1)
                    {
                        // Determine which direction to bounce
                        if (c == 0 || c == 2)
                        { // Left side corners
                            if (saw->physics.velocity_x < 0)
                            {
                                saw->physics.velocity_x *= -1;
                                saw->transform.x = (tile_x + 1) * TILE_SIZE + 1;
                            }
                        }
                        else
                        { // Right side corners
                            if (saw->physics.velocity_x > 0)
                            {
                                saw->physics.velocity_x *= -1;
                                saw->transform.x = tile_x * TILE_SIZE - saw->transform.w - 1;
                            }
                        }

                        if (c == 0 || c == 1)
                        { // Top side corners
                            if (saw->physics.velocity_y < 0)
                            {
                                saw->physics.velocity_y *= -1;
                                saw->transform.y = (tile_y + 1) * TILE_SIZE + 1;
                            }
                        }
                        else
                        { // Bottom side corners
                            if (saw->physics.velocity_y > 0)
                            {
                                saw->physics.velocity_y *= -1;
                                saw->transform.y = tile_y * TILE_SIZE - saw->transform.h - 1;
                            }
                        }

                        bounced = 1;
                        break; // Found a collision, no need to check other corners
                    }
                }
            }
        }
    }
}

void render_all_saws(SDL_Renderer *renderer, SawManager *manager)
{
    for (int i = 0; i < manager->count; i++)
    {
        render_saw(renderer, manager->saws[i], SDL_GetTicks() / 2 % 360);
    }
}

void cleanup_saw_manager(SawManager *manager)
{
    for (int i = 0; i < manager->count; i++)
    {
        free(manager->saws[i]);
        manager->saws[i] = NULL;
    }
    manager->count = 0;
}

void setup_level_saws(int level)
{
    // cleanup_saw_manager(saw_manager);

    if (level == 7)
    {
        add_saw(&saw_manager, 20 * TILE_SIZE, 5.5 * TILE_SIZE, TILE_SIZE, TILE_SIZE, -(TILE_SIZE * 3), 0);
        add_saw(&saw_manager, 15 * TILE_SIZE, 8.5 * TILE_SIZE, TILE_SIZE, TILE_SIZE, (TILE_SIZE * 3), 0);
        add_saw(&saw_manager, 20 * TILE_SIZE, 11.5 * TILE_SIZE, TILE_SIZE, TILE_SIZE, -(TILE_SIZE * 3), 0);
    }

    if (level == 8)
    {
        add_saw(&saw_manager, 24 * TILE_SIZE, 10 * TILE_SIZE, TILE_SIZE, TILE_SIZE, 0, (TILE_SIZE * 8));
        add_saw(&saw_manager, 20 * TILE_SIZE, 11 * TILE_SIZE, TILE_SIZE, TILE_SIZE, 0, -(TILE_SIZE * 9));
        add_saw(&saw_manager, 16 * TILE_SIZE, 12 * TILE_SIZE, TILE_SIZE, TILE_SIZE, 0, (TILE_SIZE * 10));
    }

    if (level == 9)
    {

        add_saw(&saw_manager, 12 * TILE_SIZE, 4 * TILE_SIZE, TILE_SIZE, TILE_SIZE, (TILE_SIZE * 3), 0);
        add_saw(&saw_manager, 20 * TILE_SIZE, 9.5 * TILE_SIZE, TILE_SIZE, TILE_SIZE, -(TILE_SIZE * 3), 0);
    }

    if (level == 10)
    {
        add_saw(&saw_manager, 25 * TILE_SIZE, 4.5 * TILE_SIZE, TILE_SIZE, TILE_SIZE, -(TILE_SIZE * 3), 0);
        add_saw(&saw_manager, 20 * TILE_SIZE, 7.5 * TILE_SIZE, TILE_SIZE, TILE_SIZE, (TILE_SIZE * 3), 0);
        add_saw(&saw_manager, 25 * TILE_SIZE, 10.5 * TILE_SIZE, TILE_SIZE, TILE_SIZE, -(TILE_SIZE * 3), 0);
        add_saw(&saw_manager, 20 * TILE_SIZE, 13.5 * TILE_SIZE, TILE_SIZE, TILE_SIZE, (TILE_SIZE * 3), 0);
    }
}