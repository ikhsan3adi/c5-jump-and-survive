#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include <cJSON/cJSON.h>

#include "level_parser.h"

const char *get_filename_ext(const char *filename)
{
  const char *dot = strrchr(filename, '.');
  if (!dot || dot == filename)
    return "";
  return dot + 1;
}

char *get_json_string(const char *file)
{
  FILE *fp;
  long file_size;
  char *buffer;

  fp = fopen(file, "rb");
  if (fp == NULL)
    return NULL;

  fseek(fp, 0, SEEK_END);
  file_size = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  buffer = (char *)malloc(file_size + 1);
  if (buffer == NULL)
  {
    fclose(fp);
    return NULL;
  }

  size_t bytes_read = fread(buffer, 1, file_size, fp);
  if (bytes_read < (size_t)file_size)
  {
    free(buffer);
    fclose(fp);
    return NULL;
  }

  buffer[file_size] = '\0';

  fclose(fp);
  return buffer;
}

/* ==== ACTIONS ==== */

void set_level_name_from_json(LevelNode *node, cJSON *json)
{
  strcpy(node->name, json->valuestring);
}

void set_prev_level_from_json(LevelNode *node, cJSON *json)
{
  strcpy(node->prev_name, json->valuestring);
}

void set_next_level_from_json(LevelNode *node, cJSON *json)
{
  strcpy(node->next_name, json->valuestring);
}

void set_player_spawn_from_json(LevelNode *node, cJSON *json)
{
  node->player_spawn = (Vector){
      .y = cJSON_GetArrayItem(json, 0)->valueint,
      .x = cJSON_GetArrayItem(json, 1)->valueint,
  };
}

void set_fg_color_from_json_array(LevelNode *node, cJSON *json)
{
  node->foreground_color = (SDL_Color){
      .r = cJSON_GetArrayItem(json, 0)->valueint,
      .g = cJSON_GetArrayItem(json, 1)->valueint,
      .b = cJSON_GetArrayItem(json, 2)->valueint,
      .a = cJSON_GetArrayItem(json, 3)->valueint,
  };
}

void set_bg_color_from_json_array(LevelNode *node, cJSON *json)
{
  node->background_color = (SDL_Color){
      .r = cJSON_GetArrayItem(json, 0)->valueint,
      .g = cJSON_GetArrayItem(json, 1)->valueint,
      .b = cJSON_GetArrayItem(json, 2)->valueint,
      .a = cJSON_GetArrayItem(json, 3)->valueint,
  };
}

void set_bg_image_from_json(LevelNode *node, cJSON *json)
{
  strcpy(node->bg_image, json->valuestring);
}

void set_switches_from_json(LevelNode *node, cJSON *json)
{
  int i = 0;                                   // counter
  cJSON *cursor = cJSON_GetArrayItem(json, 0); // pointer untuk looping elemen array (cursor luar)

  while (cursor != NULL)
  {
    int j = 0;                    // counter dalam
    cJSON *inner_cursor = NULL;   // pointer untuk looping elemen array (cursor dalam)
    cJSON *child = cursor->child; // json

    // button
    node->switches[i].button = (Vector){
        .y = cJSON_GetArrayItem(child, 0)->valueint,
        .x = cJSON_GetArrayItem(child, 1)->valueint,
    };

    // switches
    child = child->next;
    inner_cursor = cJSON_GetArrayItem(child, 0);
    while (inner_cursor != NULL)
    {
      node->switches[i].switches[j] = (Vector){
          .y = cJSON_GetArrayItem(inner_cursor, 0)->valueint,
          .x = cJSON_GetArrayItem(inner_cursor, 1)->valueint,
      };

      j++;
      inner_cursor = inner_cursor->next;
    }

    i++;
    cursor = cursor->next;
  }
}

void set_switch_obstacles_from_json(LevelNode *node, cJSON *json)
{
  int i = 0;                                   // counter
  cJSON *cursor = cJSON_GetArrayItem(json, 0); // pointer untuk looping elemen array (cursor luar)

  while (cursor != NULL)
  {
    int j = 0;                    // counter dalam
    cJSON *inner_cursor = NULL;   // pointer untuk looping elemen array (cursor dalam)
    cJSON *child = cursor->child; // json

    // button
    node->switch_obstacles[i].button = (Vector){
        .y = cJSON_GetArrayItem(child, 0)->valueint,
        .x = cJSON_GetArrayItem(child, 1)->valueint,
    };

    // switches
    child = child->next;
    inner_cursor = cJSON_GetArrayItem(child, 0);
    while (inner_cursor != NULL)
    {
      node->switch_obstacles[i].switches[j] = (Vector){
          .y = cJSON_GetArrayItem(inner_cursor, 0)->valueint,
          .x = cJSON_GetArrayItem(inner_cursor, 1)->valueint,
      };

      j++;
      inner_cursor = inner_cursor->next;
    }

    // obstacles
    j = 0;
    child = child->next;
    inner_cursor = cJSON_GetArrayItem(child, 0);
    while (inner_cursor != NULL)
    {
      node->switch_obstacles[i].obstacles[j] = (Vector){
          .y = cJSON_GetArrayItem(inner_cursor, 0)->valueint,
          .x = cJSON_GetArrayItem(inner_cursor, 1)->valueint,
      };

      j++;
      inner_cursor = inner_cursor->next;
    }

    i++;
    cursor = cursor->next;
  }
}

void set_saws_from_json(LevelNode *node, cJSON *json)
{
  int i = 0;                                   // counter
  cJSON *cursor = cJSON_GetArrayItem(json, 0); // pointer untuk looping elemen array (cursor luar)

  while (cursor != NULL)
  {
    cJSON *child = cursor->child; // json

    // pos (x,y) & size (w,h)
    node->saws[i].transform = (Transform){
        .x = cJSON_GetArrayItem(child, 0)->valuedouble,
        .y = cJSON_GetArrayItem(child, 1)->valuedouble,
        .w = cJSON_GetArrayItem(child->next, 1)->valuedouble,
        .h = cJSON_GetArrayItem(child->next, 1)->valuedouble,
    };

    // velocity (x,y)
    child = child->next->next;
    node->saws[i].physics = (Physics){
        .velocity_x = cJSON_GetArrayItem(child, 0)->valuedouble,
        .velocity_y = cJSON_GetArrayItem(child, 1)->valuedouble,
    };

    i++;
    cursor = cursor->next;
  }
}

void set_maps_from_json(LevelNode *node, cJSON *json)
{
  int i = 0;                                   // counter
  cJSON *cursor = cJSON_GetArrayItem(json, 0); // pointer untuk looping elemen array (cursor luar)

  while (cursor != NULL)
  {
    int j = 0;                                           // counter dalam
    cJSON *inner_cursor = cJSON_GetArrayItem(cursor, 0); // pointer untuk looping elemen array (cursor dalam)

    while (inner_cursor != NULL)
    {
      node->map[i][j] = inner_cursor->valueint;
      j++;
      inner_cursor = inner_cursor->next;
    }

    i++;
    cursor = cursor->next;
  }
}

/* ================= */

LevelNode *get_level_from_json(const char *json_str)
{
  // urai json string ke dalam struktur cJSON
  cJSON *json = cJSON_Parse(json_str);
  // alokasi node level baru
  LevelNode *node = malloc(sizeof(LevelNode));

  json = json->child; // point to first child of json object ("name")

  // Array pointer fungsi, berisi aksi yang akan dilakukan pada node level
  // Urutan berdasarkan key pada file JSON
  void (*actions[])(LevelNode *, cJSON *) = {
      set_level_name_from_json,
      set_prev_level_from_json,
      set_next_level_from_json,
      set_player_spawn_from_json,
      set_fg_color_from_json_array,
      set_bg_color_from_json_array,
      set_bg_image_from_json,
      set_switches_from_json,
      set_switch_obstacles_from_json,
      set_saws_from_json,
      set_maps_from_json,
  };

  // total aksi
  int actions_len = sizeof(actions) / sizeof(actions[0]);

  // loop untuk menjalankan semua aksi
  for (int i = 0; i < actions_len; i++)
  {
    if (actions[i] != NULL && json != NULL)
    {
      actions[i](node, json);
      json = json->next; // goto next child of json object
    }
  }

  return node;
}

// void load_json_levels(LevelNode **head, const char *dir)
// {
//   DIR *d;                // directory
//   struct dirent *dirent; // directory entry

//   if (!(d = opendir(dir))) // buka directory `dir`
//   {
//     return;
//   }

//   // loop semua file/directory entry di directory
//   while ((dirent = readdir(d)) != NULL)
//   {
//     const char *filename = dirent->d_name;
//     const char *ext = get_filename_ext(filename);

//     if (strcmp(ext, "json") == 0) // cek file extension adalah .json
//     {
//       // buat full path = dir + filename
//       char full_path[100] = "";
//       strcat(full_path, dir);
//       strcat(full_path, filename);

//       // json string
//       char *json_content = get_json_string(full_path);
//       // buat node level dari json string
//       LevelNode *node = get_level_from_json(json_content);

//       //! TODO: insert to head
//       //! TODO: rearrange by next & prev
//       insert_level(head, node);
//     }
//   }

//   closedir(d);
// }


// Natural order comparator for filenames like "level2" vs "level10"
int natural_compare(const void *a, const void *b)
{
    const char *f1 = *(const char **)a;
    const char *f2 = *(const char **)b;

    while (*f1 && *f2)
    {
        if (isdigit(*f1) && isdigit(*f2))
        {
            int n1 = atoi(f1);
            int n2 = atoi(f2);
            if (n1 != n2)
                return n1 - n2;

            // skip the digits
            while (isdigit(*f1)) f1++;
            while (isdigit(*f2)) f2++;
        }
        else
        {
            if (*f1 != *f2)
                return *f1 - *f2;
            f1++;
            f2++;
        }
    }
    return *f1 - *f2;
}

void load_json_levels(LevelNode **head, const char *dir)
{
    DIR *d;
    struct dirent *dirent;
    char *filenames[MAX_LEVELS];
    int count = 0;

    if (!(d = opendir(dir)))
    {
        perror("Failed to open directory");
        return;
    }

    while ((dirent = readdir(d)) != NULL)
    {
        const char *filename = dirent->d_name;
        const char *ext = get_filename_ext(filename);
        if (strcmp(ext, "json") == 0)
        {
            filenames[count] = strdup(filename); // remember to free later
            count++;
        }
    }
    closedir(d);

    // Sort filenames naturally
    qsort(filenames, count, sizeof(char *), natural_compare);

    // Parse in order
    for (int i = 0; i < count; ++i)
    {
        char full_path[200];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir, filenames[i]);

        char *json_content = get_json_string(full_path);
        LevelNode *node = get_level_from_json(json_content);
        insert_level(head, node);
    }
}