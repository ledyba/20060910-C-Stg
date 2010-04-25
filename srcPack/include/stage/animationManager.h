/*グラフィックを読み込んだりその他いろいろ。*/


#define GRAPHIC_MAX	64
#define GRAPHIC_MANAGER_RESOURCE_MAX		5
#define GRAPHIC_MANAGER_BULLET_INDEX		(0)
#define GRAPHIC_MANAGER_FOE_INDEX			(GRAPHIC_MAX * 1)
#define GRAPHIC_MANAGER_BOSS_INDEX			(GRAPHIC_MAX * 2)
#define GRAPHIC_MANAGER_EFFECT_INDEX		(GRAPHIC_MAX * 3)
#define GRAPHIC_MANAGER_CHARACTER_INDEX	(GRAPHIC_MAX * 4)
/*グラフィックをここで一元管理*/
ANIME_SET Animation[GRAPHIC_MAX * GRAPHIC_MANAGER_RESOURCE_MAX];

void initLoadGraphicManager();
int loadGraphicManager(long end_ticks);
int finishLoadGraphicManager();
