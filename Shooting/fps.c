#include <SDL.h>
#include <SDL_rwops.h>
#include <GL/gl.h>
#include <stdio.h>
#include <windows.h>
#include <PGL.h>

#include "include/fps.h"
#include "include/number.h"
	static int FPS = 0;
	static int FpsCounter = 0;
	static long LastTime = 0;
	static SPRITE FpsTextSprite;
	static SPRITE_AREA FpsTextSpriteArea;

void initFps(){
	//ファイルは共通ファイルに含まれるので、ここで開く必要性はない。
}
int loadFps(long end_ticks,ARCHIVE* archive){
	/*FPS_TEXT*/
	getSpriteFromArchive(&FpsTextSprite,archive,FPS_TEXT_TEXTURE,TRUE);
	makeDefaultSpriteArea(&FpsTextSpriteArea,&FpsTextSprite);
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
		LastTime += 1000;
		FpsCounter = 0;
	}
	FpsCounter++;
	/*FPSの描写*/
	glPoint painted = {580,460,0,0};
	drawNumberA(&painted,0,FPS,2);
	/*FPSっていう文字の描画*/
	painted.x += FpsTextSprite.Width;
	painted.width = FpsTextSprite.Width>>1;
	painted.height = FpsTextSprite.Height>>1;
	drawSpriteArea(&painted,&FpsTextSpriteArea, 0.0f);
}
