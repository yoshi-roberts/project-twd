#ifndef ASSETS_H
#define ASSETS_H

#include "../lib/raylib/src/raylib.h"
#include "map.h"

#define ASSET_PATH_MAX 4096

typedef enum {
	ASSET_IMAGE,
	ASSET_AUDIO,
} AssetType;

typedef union {
	Texture2D texture;
} AssetData;

typedef struct Asset {
	AssetData data;
	AssetType type;
} Asset;

typedef map_t(Asset) asset_map_t;

typedef struct {
	asset_map_t map;
} Assets;

Assets assets_init();
void assets_destory();
void assets_add_image(char *path);
void _dir_recurse(const char *path);
const char* _get_file_ext(const char *path);

#endif //ASSETS_H
