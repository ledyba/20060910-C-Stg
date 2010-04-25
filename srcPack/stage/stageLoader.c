/*ステージデータの読み込みを行います。*/
#include <SDL.h>
#include <SDL_rwops.h>
#include <GL/gl.h>
#include <windows.h>
#include <stdio.h>
#include "../include/data/buf.h"
#include "../include/data/data.h"
#include "../include/stage/stageLoader.h"
#include "../include/main.h"
#include "../include/point.h"
#include "../include/gfx/sprite.h"
#include "../include/gfx/spriteArea.h"
#include "../include/gfx/animation.h"
#include "../include/stage/animationManager.h"
#include "../include/stage/stageEngine.h"

//ステージごとのアーカイブ名
static char* StageArchiveName[STAGE_MAX] = {
	"stage1.arc"
	"stage2.arc"
	"stage3.arc"
	"stage4.arc"
	"stage5.arc"
};
/**
 * ステージローダを初期化する。
 */
void initStageLoader(){
	openArchive(&StageArchive,StageArchiveName[StageNumber]);
}
/**
 * ステージローダを終了する
 */
void quitStageLoader(){
	closeArchive(&StageArchive);
	//ステージエンジンを開始する。
	//ちくしょー、スパゲッティだな。
	startStageEngine();
}
