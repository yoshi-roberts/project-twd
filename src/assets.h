#ifndef ASSETS_H
#define ASSETS_H

#include "../lib/raylib/src/raylib.h"
#include "map.h"

#define ASSET_PATH_MAX 4096
#define ATLAS_MAX_SIZE 64

typedef enum {
	ASSET_IMAGE,
	ASSET_FONT,
	ASSET_AUDIO,
} AssetType;

typedef struct {
	Rectangle rects[ATLAS_MAX_SIZE];
	int width;
} Atlas;

typedef struct {
	Texture2D texture;
	Atlas atlas;
} Sprite;

typedef union {
	Sprite sprite;
	Font font;
	Music audio;
} AssetData;

typedef struct Asset {
	bool resource_loaded;
	AssetType type;
	AssetData data;
} Asset;

// Custom map type that stores elements of type Asset.
typedef map_t(Asset) asset_map_t;

typedef struct {
	asset_map_t map;
} Assets;

// Initialize the asset system.
void assets_init();
// Deinitialize the asset system and free any allocated memeory.
void assets_destory();
// Load an assets required resource into memory.
void assets_load_resource(Asset *asset, const char *path);
// Create a new asset entry.
void assets_add(const char *path);
// Retrieve an asset by its filepath.
Asset* assets_get(const char *path);
void asset_draw_tile(Asset *asset, int index, int x, int y);
void _generate_atlas(Asset *asset);
void _dir_recurse(const char *path);
const char* _get_file_ext(const char *path);

#endif //ASSETS_H
