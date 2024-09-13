#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assets.h"

void assets_init() {
	_dir_recurse("assets/");
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
            printf("%s\n", full_path); // process file
        }
    }
    closedir(dp);
}
