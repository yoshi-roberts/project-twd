#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "assets.h"
#include "map.h"

static Assets assets = {};
static bool initialized = false;

void assets_init() {

	map_init(&assets.map);
	_dir_recurse("assets");
}

void assets_destory() {

	const char *key;
	map_iter_t iter = map_iter(&assets.map);

	// Loop through all assets and unload any resource data.
	while ((key = map_next(&assets.map, &iter))) {

		Asset *asset = map_get(&assets.map, key);

		if (asset->type == ASSET_IMAGE) {
			UnloadTexture(asset->data.texture);
		}
	}

	map_deinit(&assets.map);
}

void assets_load_resource(Asset *asset, const char *path) {

	if (asset->type == ASSET_IMAGE) {
		asset->data.texture = LoadTexture(path);
	} else if (asset->type == ASSET_AUDIO) {
		// Load audio data.
	}
	
	asset->resource_loaded = true;
}

void assets_add(const char *path) {

	const char* ext = _get_file_ext(path);

	Asset asset;
	asset.resource_loaded = false;

	// Check the asset type based on the file extension.
	if (strcmp(ext, "png") == 0) {
		asset.type = ASSET_IMAGE;
	}

	map_set(&assets.map, path, asset);
}

Asset* assets_get(const char *path) {
	Asset *asset = map_get(&assets.map, path);

	// If it does not exits, load in the assets resource data.
	if (!asset->resource_loaded) {
		assets_load_resource(asset, path);
	}

	return asset;
}

void _dir_recurse(const char *path) {

	DIR *dir;
    struct dirent *ent;
	struct stat sb;

	// Check that the directory can be opened.
    if ((dir = opendir(path)) == NULL) {
        perror(path);
        return;
    }

	// Kepp looping so long as there are more entries.
    while ((ent = readdir(dir)) != NULL) {

		// Skip hidden files and dirs we do not care about.
        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {
            continue;
        }

		if (ent->d_name[0] == '.') {
			continue;
		}

		// Full path of entry from the root asset directory.
        char full_path[ASSET_PATH_MAX];
        snprintf(full_path, ASSET_PATH_MAX, "%s/%s", path, ent->d_name);

		stat(full_path, &sb);

		// Type 4 means entry is a directory.
        if (S_ISDIR(sb.st_mode)) {
            _dir_recurse(full_path);
        } else if (S_ISREG(sb.st_mode)) { // File.
			assets_add(full_path);
        } 
    }

    closedir(dir);
}

const char* _get_file_ext(const char *path) {
    const char *dot = strrchr(path, '.');

    if (!dot || dot == path) {
		return "";
	} 

    return dot + 1;
}

void assets_image_example() {

	Asset *knight = assets_get("assets/Factions/Knights/Troops/Warrior/Purple/Warrior_Purple.png");

	DrawTexture(knight->data.texture, 0, 0, WHITE);
}
