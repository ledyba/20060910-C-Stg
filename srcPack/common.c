/**
 * 共通ファイルを読むためのモジュール。一回だけ実行する。
 * 例：FPSのフォント。
 * 例：自機関係のグラフィック
 */
#include <windows.h>
#include <SDL.h>
#include <SDL_rwops.h>
#include <GL/gl.h>
#include <stdio.h> 
#include "include/main.h"
#include "include/point.h"
#include "include/data/buf.h"
#include "include/data/data.h"
#include "include/gfx/sprite.h"
#include "include/fps.h"
#include "include/number.h"
#include "include/load.h"
#include "include/common.h"
static int LoadIndex = 0;
#define COMMON_LOAD_FUNCS_NUM 2
static LOAD_FUNCS CommonLoadFuncs[COMMON_LOAD_FUNCS_NUM] = {
			{initFps,	loadFps,	finishLoadFps,		quitFPS},
			{initNumber,loadNumber,	finishLoadNumber,	quitNumber},
};
 void initCommon(){
 	openArchive(&CommonArchive,COMMON_ARCHIVE);
 	int i=0;
 	for(;i<COMMON_LOAD_FUNCS_NUM;i++){
 		CommonLoadFuncs[i].init();
 	}
 	LoadIndex = 0;
 }
 int loadCommon(long end_ticks){
 	int i= LoadIndex;
 	for(;i<COMMON_LOAD_FUNCS_NUM;i++){
	 	if(CommonLoadFuncs[i].load(end_ticks)){
	 	}else{
	 		LoadIndex = i;
	 		return FALSE;
	 	}
 	}
 	return TRUE;
 }
 int finishLoadCommon(){
 	int i = 0;
 	int ret = TRUE;
 	for(;i<COMMON_LOAD_FUNCS_NUM;i++){
 		ret &= CommonLoadFuncs[i].finish();
 	}
 	closeArchive(&CommonArchive);
 	return ret;
 }
 void quitCommon(){
 	int i = 0;
 	for(;i<COMMON_LOAD_FUNCS_NUM;i++){
 		CommonLoadFuncs[i].quit();
 	}
 }
