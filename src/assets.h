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
	bool resource_loaded;
	AssetType type;
	AssetData data;
} Asset;

typedef map_t(Asset) asset_map_t;

typedef struct {
	asset_map_t map;
} Assets;

void assets_init();
void assets_destory();
void assets_load_resource(Asset *asset, const char *path);
void assets_add(const char *path);
Asset* assets_get(const char *path);
void _dir_recurse(const char *path);
const char* _get_file_ext(const char *path);

void assets_image_example();

#endif //ASSETS_H
