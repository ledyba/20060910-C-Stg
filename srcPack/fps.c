#include <SDL.h>
#include <SDL_rwops.h>
#include <GL/gl.h>
#include <stdio.h>
#include <windows.h>

#include "include/main.h"
#include "include/point.h"
#include "include/gfx/graphic.h"
#include "include/gfx/sprite.h"
#include "include/fps.h"
#include "include/data/buf.h"
#include "include/data/data.h"
#include "include/screen.h"
#include "include/common.h"
#include "include/number.h"
	static int FPS = 0;
	static int FpsCounter = 0;
	static long LastTime = 0;
void initFps(){
	//ファイルは共通ファイルに含まれるので、ここで開く必要性はない。
}
int loadFps(long end_ticks){
	/*FPS_TEXT*/
	SDL_RWops* fpsTextData = getGraphixFile(&CommonArchive,FPS_TEXT_TEXTURE);
	getSpriteFromOPS(&FpsTextSprite,fpsTextData);
	fpsTextData->close(fpsTextData);					//メモリ開放は忘れずに
	return TRUE;
}
int finishLoadFps(){
	return TRUE;
}

void quitFPS(){
	deleteSprite(&FpsTextSprite);
}

void drawFps(){
	/*FPSのカウント*/
	long nowTime = SDL_GetTicks();
	if(nowTime - LastTime >= 1000){
		FPS = FpsCounter;
		LastTime = nowTime;
		FpsCounter = 0;
	}
	FpsCounter++;
	/*FPSの描写*/
	glPoint painted = {580,460,0,0,0};
	drawNumber(&painted,0,FPS,2);
	/*FPSっていう文字の描画*/
	painted.x += FpsTextSprite.Width;
	painted.width = FpsTextSprite.Width>>1;
	painted.height = FpsTextSprite.Height>>1;
	drawSprite(&FpsTextSprite,&painted,0,0,FpsTextSprite.Width, FpsTextSprite.Height, 0.0f);
}
