/*グラフィックを読み込んだりその他いろいろ。*/
#include <SDL.h>
#include <SDL_rwops.h>
#include <SDL_image.h>
#include <GL/gl.h>
#include <windows.h>
#include "../include/main.h"
#include "../include/point.h"
#include "../include/data/buf.h"
#include "../include/data/data.h"
#include "../include/data/resource_define.h"
#include "../include/gfx/sprite.h"
#include "../include/gfx/spriteArea.h"
#include "../include/gfx/graphic.h"
#include "../include/stage/stageEngine.h"
#include "../include/stage/stageLoader.h"
#include "../include/stage/graphicManager.h"
//アーカイブ内でのリソース定義ファイルのファイル名
const static char* FileName[GRAPHIC_MANAGER_RESOURCE_MAX] = {
	"bullet_gfx_list.rc",
	"foe_gfx_list.rc",
	"boss_gfx_list.rc",
	"effect_gfx_list.rc",
};
const static int GraphicIndex[GRAPHIC_MANAGER_RESOURCE_MAX] = {
	GRAPHIC_MANAGER_BULLET_INDEX,
	GRAPHIC_MANAGER_FOE_INDEX,
	GRAPHIC_MANAGER_BOSS_INDEX,
	GRAPHIC_MANAGER_EFFECT_INDEX,
};

void initLoadGraphicManager(){
	/*特にやることは無い・・・と思う。*/
}
int loadGraphicManager(long end_ticks){
	//グラフィック読み込み。
	//リソース定義モジュールから来たリストは、ちゃんと開放するように。
	int i=0;
	for(;i<GRAPHIC_MANAGER_RESOURCE_MAX;i++){
		int index = GraphicIndex[i];
		//リソース定義ファイルファイルのバッファを作成。
		BUF* list_buffer = getFile(&StageArchive,FileName[i]);
		RESOURCE_LIST rc_list;
		//リソースリスト読み込み
		loadResourceDefine(&rc_list,list_buffer);
		int j;
		int file_num = rc_list.file_num;
		//グラフィック読み込み
		for(j=0;j<file_num;j++){
			int num = rc_list.item[j].num;
			loadAnimation(&Graphic[index+num],&StageArchive,rc_list.item[i].filename);
		}
		//メモリ開放
		closeResourceDefine(&rc_list);
		deleteBuf(list_buffer);
	}
	return TRUE;
}
int finishLoadGraphicManager(){
	//ここも特に無いかなーなんて。
	return TRUE;
}
