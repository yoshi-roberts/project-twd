#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "assets.h"

static Assets assets = {};
static bool initialized = false;

Assets assets_init() {
	assets.texture_last = 0;

	_dir_recurse("assets/");

	return assets;
}

void assets_destory() {
	for (int i = 0; i <= assets.texture_last; i++) {
		UnloadTexture(assets.textures[i]);
	}
}

void assets_add_image(const char *path) {
	assets.textures[assets.texture_last] = LoadTexture(path);
	assets.texture_last++;
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
            continue; // skip current dir and parent dir
        }

		// Skip hidden files.
		if (ent->d_name[0] == '.') {
			continue;
		}

        char full_path[ASSET_PATH_MAX];
        snprintf(full_path, ASSET_PATH_MAX, "%s/%s", path, ent->d_name);

        if (ent->d_type == 4) {
            _dir_recurse(full_path); // recursive call
        } else {
			const char* ext = _get_file_ext(full_path);
			if (strcmp(ext, "png") == 0) {
				// printf("%s\n", ext); // process file
				// printf("PNG!");
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
