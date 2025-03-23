#include <stdlib.h>
#include <math.h>
#include "level.h"
#include "obstacle.h"

SawManager saw_manager;

Saw *create_saw(float x, float y, float w, float h, float velocity_x, float velocity_y) {
    Saw* saw = malloc(sizeof(Saw)); // Allocate memory for the saw
    if (saw == NULL) {
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

void update_saw(Saw *saw, float delta_time) {
    saw->transform.x += saw->physics.velocity_x * delta_time;
    saw->transform.y += saw->physics.velocity_y * delta_time;
}

void render_saw(SDL_Renderer *renderer, Saw *saw) {
    // Draw saw blade with rotating effect
    static float rotation = 0;
    rotation += 0.1; // Increase rotation each frame
    
    // Center of the saw
    float center_x = saw->transform.x + saw->transform.w / 2;
    float center_y = saw->transform.y + saw->transform.h / 2;
    float radius = saw->transform.w / 2;
    
    // Draw the circular base of the saw
    SDL_SetRenderDrawColor(renderer, 192, 192, 192, 255); // Silver color
    
    // Draw the circular base using points around the circumference
    const int num_segments = 20;
    for (int i = 0; i < num_segments; i++) {
        float angle1 = (i / (float)num_segments) * 2 * 3.14159;
        float angle2 = ((i + 1) / (float)num_segments) * 2 * 3.14159;
        
        float x1 = center_x + cosf(angle1) * radius;
        float y1 = center_y + sinf(angle1) * radius;
        float x2 = center_x + cosf(angle2) * radius;
        float y2 = center_y + sinf(angle2) * radius;
        
        SDL_RenderLine(renderer, x1, y1, x2, y2);
    }
    
    // Draw the teeth of the saw
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color for teeth
    
    // Number of teeth
    const int num_teeth = 8;
    for (int i = 0; i < num_teeth; i++) {
        float angle = rotation + (i / (float)num_teeth) * 2 * 3.14159;
        
        float inner_x = center_x + cosf(angle) * (radius * 0.7);
        float inner_y = center_y + sinf(angle) * (radius * 0.7);
        
        float outer_x = center_x + cosf(angle) * (radius * 1.3);
        float outer_y = center_y + sinf(angle) * (radius * 1.3);
        
        SDL_RenderLine(renderer, inner_x, inner_y, outer_x, outer_y);
    }
    
    // Draw center of saw
    SDL_FRect center_rect = {center_x - radius * 0.2, center_y - radius * 0.2, radius * 0.4, radius * 0.4};
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); // Dark gray for center
    SDL_RenderFillRect(renderer, &center_rect);
}

void add_saw(SawManager* manager, float x, float y, float w, float h, float velocity_x, float velocity_y) {
    if (manager->count >= MAX_SAWS) {
        SDL_Log("Maximum number of saws reached!");
        return;
    }
    
    manager->saws[manager->count] = create_saw(x, y, w, h, velocity_x, velocity_y);
    if (manager->saws[manager->count] != NULL) {
        manager->count++;
    }
}

void update_all_saws(SawManager* manager, float delta_time) {
    for (int i = 0; i < manager->count; i++) {
        Saw* saw = manager->saws[i];
        
        // Store previous position for collision resolution
        float prev_x = saw->transform.x;
        float prev_y = saw->transform.y;
        
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
        
        if (saw->transform.x < level_min_x) {
            saw->transform.x = level_min_x;
            saw->physics.velocity_x *= -1;  // Reverse horizontal direction
            bounced = 1;
        }
        else if (saw->transform.x + saw->transform.w > level_max_x) {
            saw->transform.x = level_max_x - saw->transform.w;
            saw->physics.velocity_x *= -1;  // Reverse horizontal direction
            bounced = 1;
        }
        
        if (saw->transform.y < level_min_y) {
            saw->transform.y = level_min_y;
            saw->physics.velocity_y *= -1;  // Reverse vertical direction
            bounced = 1;
        }
        else if (saw->transform.y + saw->transform.h > level_max_y) {
            saw->transform.y = level_max_y - saw->transform.h;
            saw->physics.velocity_y *= -1;  // Reverse vertical direction
            bounced = 1;
        }
        
        // Check for collision with walls in the map
        if (!bounced) {
            // Check corners of the saw for wall collision
            int corners[4][2] = {
                {saw->transform.x, saw->transform.y},                       // Top-left
                {saw->transform.x + saw->transform.w, saw->transform.y},    // Top-right
                {saw->transform.x, saw->transform.y + saw->transform.h},    // Bottom-left
                {saw->transform.x + saw->transform.w, saw->transform.y + saw->transform.h} // Bottom-right
            };
            
            for (int c = 0; c < 4; c++) {
                int tile_x = corners[c][0] / TILE_SIZE;
                int tile_y = corners[c][1] / TILE_SIZE;
                
                // Make sure we're within map bounds
                if (tile_x >= 0 && tile_x < MAP_WIDTH && tile_y >= 0 && tile_y < MAP_HEIGHT) {
                    // Check if we hit a wall (value 1 in level9_map)
                    if (current_level_map[tile_y][tile_x] == 1) {
                        // Determine which direction to bounce
                        if (c == 0 || c == 2) {  // Left side corners
                            if (saw->physics.velocity_x < 0) {
                                saw->physics.velocity_x *= -1;
                                saw->transform.x = (tile_x + 1) * TILE_SIZE + 1;
                            }
                        } else {  // Right side corners
                            if (saw->physics.velocity_x > 0) {
                                saw->physics.velocity_x *= -1;
                                saw->transform.x = tile_x * TILE_SIZE - saw->transform.w - 1;
                            }
                        }
                        
                        if (c == 0 || c == 1) {  // Top side corners
                            if (saw->physics.velocity_y < 0) {
                                saw->physics.velocity_y *= -1;
                                saw->transform.y = (tile_y + 1) * TILE_SIZE + 1;
                            }
                        } else {  // Bottom side corners
                            if (saw->physics.velocity_y > 0) {
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

void render_all_saws(SDL_Renderer* renderer, SawManager* manager) {
    for (int i = 0; i < manager->count; i++) {
        render_saw(renderer, manager->saws[i]);
    }
}

void cleanup_saw_manager(SawManager* manager) {
    for (int i = 0; i < manager->count; i++) {
        free(manager->saws[i]);
        manager->saws[i] = NULL;
    }
    manager->count = 0;
}

void setup_level_saws(int level) {
    // cleanup_saw_manager(saw_manager);
    
    if (level == 9) {
        // Level 9 saws - adjust positions and velocities as needed
        // add_saw(&saw_manager, 5 * TILE_SIZE, 4 * TILE_SIZE, TILE_SIZE - 4, TILE_SIZE - 4, 100, 0);     // Horizontal moving saw
        // add_saw(&saw_manager, 15 * TILE_SIZE, 5 * TILE_SIZE, TILE_SIZE - 4, TILE_SIZE - 4, 0, 80);     // Vertical moving saw
        
        // // Saws in the middle open area (rows 8-10, columns 3-27)
        add_saw(&saw_manager, 12 * TILE_SIZE, 4 * TILE_SIZE, TILE_SIZE, TILE_SIZE, 120, 0);    // Horizontal moving saw
        add_saw(&saw_manager, 20 * TILE_SIZE, 9 * TILE_SIZE, TILE_SIZE, TILE_SIZE, -120, 0);   // Horizontal moving saw opposite direction
        
        // // Saws in the bottom section (rows 13-19, columns 25-27)
        // create_vertical_saw_wall(&saw_manager, 26 * TILE_SIZE, 13 * TILE_SIZE, 19 * TILE_SIZE, 80, TILE_SIZE * 2, TILE_SIZE - 4);
    }
    // else if (level == 10) {
        // Level 10 saws - more challenging patterns
        // create_circular_saw_pattern(&saw_manager, 15 * TILE_SIZE, 10 * TILE_SIZE, 60, 6, 80, TILE_SIZE - 6);
        
        // // Add some horizontal moving saws in corridors
        // add_saw(&saw_manager, 5 * TILE_SIZE, 5 * TILE_SIZE, TILE_SIZE - 4, TILE_SIZE - 4, 120, 0);
        // add_saw(&saw_manager, 12 * TILE_SIZE, 8 * TILE_SIZE, TILE_SIZE - 4, TILE_SIZE - 4, -140, 0);
        
        // // Add some vertical moving saws
        // add_saw(&saw_manager, 26 * TILE_SIZE, 12 * TILE_SIZE, TILE_SIZE - 4, TILE_SIZE - 4, 0, 130);
        // add_saw(&saw_manager, 26 * TILE_SIZE, 16 * TILE_SIZE, TILE_SIZE - 4, TILE_SIZE - 4, 0, -130);
        
        // // Add diagonal moving saws for extra challenge
        // add_saw(&saw_manager, 8 * TILE_SIZE, 14 * TILE_SIZE, TILE_SIZE - 4, TILE_SIZE - 4, 100, 100);
        // add_saw(&saw_manager, 20 * TILE_SIZE, 15 * TILE_SIZE, TILE_SIZE - 4, TILE_SIZE - 4, -100, -100);
    // }
}

// int is_wall_at(int level, int tile_x, int tile_y) {
//     return (current_level_map[tile_y][tile_x] == 1);
// }
