#ifndef ASSETS_H
#define ASSETS_H

#define ASSET_PATH_MAX 4096

typedef struct {
	
} Assets;

void assets_init();
void _dir_recurse(const char *path);

#endif //ASSETS_H
