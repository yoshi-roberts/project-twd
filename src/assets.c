#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "assets.h"
#include "map.h"

static Assets assets = {};
static bool initialized = false;

Assets assets_init() {

	map_init(&assets.map);
	_dir_recurse("assets/");

	return assets;
}

void assets_destory() {

	const char *key;
	map_iter_t iter = map_iter(&assets.map);

	while ((key = map_next(&assets.map, &iter))) {

		Asset *asset = map_get(&assets.map, key);

		if (asset->type == ASSET_IMAGE) {
			UnloadTexture(asset->data.texture);
		}
	}

	map_deinit(&assets.map);
}

void assets_add_image(char *path) {

	Asset asset;
	asset.type = ASSET_IMAGE;
	asset.data.texture = LoadTexture(path);

	map_set(&assets.map, path, asset);
}

void _dir_recurse(const char *path) {

	DIR *dp;
    struct dirent *ent;
    if ((dp = opendir(path)) == NULL) {
        perror(path);
        return;
    }

    while ((ent = readdir(dp)) != NULL) {
        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {
            continue;
        }

		// Skip hidden files.
		if (ent->d_name[0] == '.') {
			continue;
		}

        char full_path[ASSET_PATH_MAX];
        snprintf(full_path, ASSET_PATH_MAX, "%s/%s", path, ent->d_name);

        if (ent->d_type == 4) {
            _dir_recurse(full_path);
        } else {

			const char* ext = _get_file_ext(full_path);

			if (strcmp(ext, "png") == 0) {
				assets_add_image(full_path);
			}
        }
    }
    closedir(dp);
}

const char* _get_file_ext(const char *path) {
    const char *dot = strrchr(path, '.');

    if (!dot || dot == path) {
		return "";
	} 

    return dot + 1;
}