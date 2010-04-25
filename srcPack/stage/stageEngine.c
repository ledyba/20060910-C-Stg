/*ステージ進行に関することを行います。総合的に。*/
#include <SDL.h>
#include <SDL_rwops.h>
#include <SDL_image.h>
#include <GL/gl.h>
#include <windows.h>
#include "../include/load.h"
#include "../include/main.h"
#include "../include/point.h"
#include "../include/data/buf.h"
#include "../include/data/data.h"
#include "../include/gfx/sprite.h"
#include "../include/gfx/spriteArea.h"
#include "../include/gfx/animation.h"
#include "../include/stage/animationManager.h"
#include "../include/stage/stageEngine.h"
#include "../include/stage/stageLoader.h"
#
/**
 * ステージエンジンを初期化する。
 */
#define STAGE_LOAD_FUNC_NUM	1
static LOAD_FUNCS StageLoadFunc[STAGE_LOAD_FUNC_NUM] = {
	{initLoadGraphicManager,loadGraphicManager,finishLoadGraphicManager},
};
int initStageEngine(int stage){
	StageNumber = stage;
	/*共通システム　初期化*/
	
	/*ステージファイル読み込み、初期化。*/
	setLoad(STAGE_LOAD_FUNC_NUM,initStageLoader,quitStageLoader,&StageLoadFunc[0],GAME_SCENE_GAME);
	startLoad();
	return TRUE;
}
/**
 * ステージエンジンを実際に動かす
 */
void startStageEngine(){
	//ロード読み込み後、ここに飛んでくる。
}
/**
 * 敵発生、イベント処理などを総合的に行う。
 */
void moveStageEngine(){
}
/**
 * メモリ開放、その他モロモロを行う。
 * moveStageEngineからのみ、呼ばれる。
 */
int quitStageEngine(){
	return TRUE;
}
