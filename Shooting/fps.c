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
	//�t�@�C���͋��ʃt�@�C���Ɋ܂܂��̂ŁA�����ŊJ���K�v���͂Ȃ��B
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
	/*FPS�̃J�E���g*/
	long nowTime = SDL_GetTicks();
	if(nowTime - LastTime >= 1000){
		FPS = FpsCounter;
		LastTime += 1000;
		FpsCounter = 0;
	}
	FpsCounter++;
	/*FPS�̕`��*/
	glPoint painted = {580,460,0,0};
	drawNumberA(&painted,0,FPS,2);
	/*FPS���Ă��������̕`��*/
	painted.x += FpsTextSprite.Width;
	painted.width = FpsTextSprite.Width>>1;
	painted.height = FpsTextSprite.Height>>1;
	drawSpriteArea(&painted,&FpsTextSpriteArea, 0.0f);
}
