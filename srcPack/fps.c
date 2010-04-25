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
	//�t�@�C���͋��ʃt�@�C���Ɋ܂܂��̂ŁA�����ŊJ���K�v���͂Ȃ��B
}
int loadFps(long end_ticks){
	/*FPS_TEXT*/
	SDL_RWops* fpsTextData = getGraphixFile(&CommonArchive,FPS_TEXT_TEXTURE);
	getSpriteFromOPS(&FpsTextSprite,fpsTextData);
	fpsTextData->close(fpsTextData);					//�������J���͖Y�ꂸ��
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
		LastTime = nowTime;
		FpsCounter = 0;
	}
	FpsCounter++;
	/*FPS�̕`��*/
	glPoint painted = {580,460,0,0,0};
	drawNumber(&painted,0,FPS,2);
	/*FPS���Ă��������̕`��*/
	painted.x += FpsTextSprite.Width;
	painted.width = FpsTextSprite.Width>>1;
	painted.height = FpsTextSprite.Height>>1;
	drawSprite(&FpsTextSprite,&painted,0,0,FpsTextSprite.Width, FpsTextSprite.Height, 0.0f);
}
