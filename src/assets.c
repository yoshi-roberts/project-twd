#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "assets.h"
#include "map.h"
#include "log.h"
#include "audio.h"

static Assets assets = {};
static bool initialized = false;

void assets_init() {

	if (initialized) {
		log_error("Asset system already initialized");
		return;
	}

	initialized = true;

	map_init(&assets.map);
	_dir_recurse("assets");

	log_info("Asset system initialized.");
}

void assets_destory() {

	if (!initialized) {
		log_error("Asset system not initialized.");
		return;
	}

	const char *key;
	map_iter_t iter = map_iter(&assets.map);

	// Loop through all assets and unload any resource data.
	while ((key = map_next(&assets.map, &iter))) {

		Asset *asset = map_get(&assets.map, key);

		if (asset->type == ASSET_IMAGE) {
			UnloadTexture(asset->data.sprite.texture);
		} else if (asset->type == ASSET_IMAGE) {
			UnloadFont(asset->data.font);
		} else if (asset->type == ASSET_AUDIO) {
    		if (IsMusicStreamPlaying(asset->data.audio)) {
       		StopMusicStream(asset->data.audio);
    		}
    	UnloadMusicStream(asset->data.audio); 
		}
	}

	map_deinit(&assets.map);
	initialized = false;

	log_info("Asset system shutdown.");
}

void assets_load_resource(Asset *asset, const char *path) {

	if (!initialized) {
		log_error("Asset system not initialized.");
		return;
	}

	if (asset->type == ASSET_IMAGE) {
		asset->data.sprite.texture = LoadTexture(path);
		SetTextureFilter(asset->data.sprite.texture, TEXTURE_FILTER_POINT);
		_generate_atlas(asset);
	} else if (asset->type == ASSET_FONT) {
		asset->data.font = LoadFontEx(path, 12 * 4, NULL, 0);
		SetTextureFilter(asset->data.font.texture, TEXTURE_FILTER_POINT);
	} else if (asset->type == ASSET_AUDIO) {
		asset->data.audio = LoadMusicStream(path);
    	if (asset->data.audio.stream.buffer) { 
        	log_info("Audio file loaded successfully: %s", path);
        	SetMusicVolume(asset->data.audio, 1.0f);
        	PlayMusicStream(asset->data.audio);
        	log_info("Playback started for: %s", path);
    	} else {
        	log_error("Failed to load audio stream for: %s", path);
		}
	asset->resource_loaded = true;
	}
}

void assets_add(const char *path) {

	if (!initialized) {
		log_error("Asset system not initialized.");
		return;
	}

	const char* ext = _get_file_ext(path);

	Asset asset;
	asset.resource_loaded = false;

	// Check the asset type based on the file extension.
	if (strcmp(ext, "png") == 0) {
		asset.type = ASSET_IMAGE;
	} else if (strcmp(ext, "ttf") == 0) {
		asset.type = ASSET_FONT;
	} else if (strcmp(ext, "ogg") == 0) {
		asset.type = ASSET_AUDIO;
	}

	map_set(&assets.map, path, asset);
}

Asset* assets_get(const char *path) {

	if (!initialized) {
		log_error("Asset system not initialized.");
		return NULL;
	}

	Asset *asset = map_get(&assets.map, path);

	if (!asset) {
		log_error("Could not find asset '%s'", path);
		return NULL;
	}

	// If it does not exit, load in the assets resource data.
	if (!asset->resource_loaded) {
		assets_load_resource(asset, path);
	}

	return asset;
}

void asset_draw_tile(Asset *asset, int index, int x, int y) {

	Texture2D texture = asset->data.sprite.texture;
	Rectangle rect = asset->data.sprite.atlas.rects[index];

	DrawTextureRec(texture, rect, (Vector2){x, y}, WHITE);
}

void _generate_atlas(Asset *asset) {

	int xtiles = asset->data.sprite.texture.width / 16;
	int ytiles = asset->data.sprite.texture.height / 16;
	int i = 0;

	for (int y = 0; y < ytiles; y++) {
		for (int x = 0; x < xtiles; x++) {

			asset->data.sprite.atlas.rects[i] = (Rectangle){
				16 * x, 16 * y,
				16,     16
			};

			asset->data.sprite.atlas.width = x;
			i++;
		}
	}
}

void _dir_recurse(const char *path) {

	DIR *dir;
    struct dirent *ent;
	struct stat sb;

	// Check that the directory can be opened.
    if ((dir = opendir(path)) == NULL) {
		log_error("Error reading directory %s", path);
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
