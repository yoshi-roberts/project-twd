#ifndef ASSETS_H
#define ASSETS_H

#include "../lib/raylib/src/raylib.h"

#define ASSET_PATH_MAX 4096
#define ASSET_TEXTURE_MAX 4096

typedef struct {
	Texture2D textures[ASSET_TEXTURE_MAX];	
	int texture_last;
} Assets;

Assets assets_init();
void assets_destory();
void assets_add_image(const char *path);
void _dir_recurse(const char *path);
const char* _get_file_ext(const char *path);

#endif //ASSETS_H
