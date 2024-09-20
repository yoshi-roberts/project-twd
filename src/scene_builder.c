#define MAXWIDTH=128
#define MAXHEIGHT=128

#ifndef SCENE_BUILDER_H
#define SCENE_BUILDER_H
#endif


typedef struct {
	Asset* tileset;
	int tile_size;
	int tiles[128][128];
} Tilemap ;

typedef struct {
	int difficulty;
	int waves;
	Tilemap tilemap;
} Scene;

void scene_initialize(int difficulty, int waves) {
	Scene newScene;
	newScene.difficulty = difficulty;
	newScene.waves = waves;
	scene_populate(newScene);
}

void scene_populate(Scene newScene)
{
int traverse = 0;
for(int i; i<MAXHEIGHT; i++)
	{
	for(int j; j<MAXWIDTH; j++)
		{
		//Find value set at [i][j]
		//go into assets folder and yoink image
		//render image based on which part we want
	

		}
	}




}
