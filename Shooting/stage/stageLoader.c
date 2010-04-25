/*ステージデータの読み込みを行います。*/
#include <SDL.h>
#include <SDL_rwops.h>
#include <GL/gl.h>
#include <windows.h>
#include <stdio.h>
#include <PGL.h>
#include "../include/stage/stageLoader.h"
#include "../include/main.h"
#include "../include/stage/animationManager.h"
#include "../include/stage/stageEngine.h"

/**
 * ステージローダを初期化する。
 */
void initStageLoader(){
}
/**
 * ステージローダを終了する
 */
void quitStageLoader(){
	//ステージエンジンを開始する。
	//ちくしょー、スパゲッティだな。
	startStageEngine();
}
