#include <SDL.h>
#include <SDL_rwops.h>
#include <GL/gl.h>
#include <stdio.h> 
#include <windows.h>
#include "include/main.h"
#include "include/point.h"
#include "include/data/buf.h"
#include "include/data/data.h"
#include "include/load.h"
#include "include/gfx/sprite.h"
#include "include/gfx/graphic.h"
	static LOAD_FUNCS* LoadFuncs;
	static void (*initFunc)();
	static void (*finishFunc)();
	static int Funcs = 0;
	static int LoadIndex = 0;
	static int NextMode;
	/*ロード画面の背景スプライト*/
	static SPRITE LoadBGSprite;
	static char* ArchiveName;
	static ARCHIVE LoadingArchive;
	

void initLoad(){
	/*ファイルオープン*/
	ARCHIVE archive;
	openArchive(&archive,LOAD_ARCHIVE);
	/*背景取得*/
	SDL_RWops* bgData = getGraphixFile(&archive,LOAD_BG);
	getSpriteFromOPS(&LoadBGSprite,bgData);
	bgData->close(bgData);					//メモリ開放は忘れずに
	closeArchive(&archive);
	
}
/*ロード画面の準備・終了*/
void setLoad(int funcs,char* filename,void (*init_func)(),void (*finish_func)(),LOAD_FUNCS* load_funcs, int next_mode){
	LoadIndex = 0;
	/*ファイル名*/
	ArchiveName = filename;
	/*アーカイブを開く*/
	if(ArchiveName != NULL){
		openArchive(&LoadingArchive,ArchiveName);
	}
	/*ロード用関数*/
	Funcs = funcs;					//関数数
	LoadFuncs = load_funcs;
	/*終わったあとのモード*/
	NextMode = next_mode;
	//最初の関数読み込み
	initFunc = init_func;
	if(initFunc != NULL)	initFunc();
	//最後の関数
	finishFunc = finish_func;
	//プリペア
	startLoad();
	/*場面切り替え*/
	GameScene = GAME_SCENE_LOADING;
	/*一回だけ描画*/
	drawLoad();
	SDL_GL_SwapBuffers();
}
void quitLoad(){
	/*テクスチャの削除*/
	glDeleteTextures(1,&LoadBGSprite.TexID);
}
void startLoad(){
	/*ロードの準備*/
	LoadFuncs[LoadIndex].init();
}
/*動かす*/
void moveLoad(){
	int isLoadFinished = LoadFuncs[LoadIndex].load(NextTick,&LoadingArchive);
	if(isLoadFinished == TRUE){
		LoadFuncs[LoadIndex].finish();
		LoadIndex++;
		if(LoadIndex >= Funcs){
			/*最後の関数の実行*/
			if(finishFunc != NULL)	finishFunc();
			/*アーカイブを閉じる*/
			if(ArchiveName != NULL){
				closeArchive(&LoadingArchive);
			}
			/*ロードが終わったらシーンを変える*/
			GameScene = NextMode;
		}else{
			startLoad();
		}
	}
}
/*描写する*/
void drawLoad(){
	drawSprite(&LoadBGSprite,&BG_AREA,0,0,LoadBGSprite.Width,LoadBGSprite.Height,0.0f);
}

