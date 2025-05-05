#ifndef LEVEL_PARSER_H
#define LEVEL_PARSER_H

#include "level.h"

// get file extension
const char *get_filename_ext(const char *filename);

// get string content from file
char *get_json_string(const char *file);

// convert json to LevelNode
LevelNode *get_level_from_json(const char *json_str);

// load levels from json from directory
void load_json_levels(LevelNode **head, const char *dir);

#endif