#include <SDL.h>
#include <GL/gl.h>
#include <windows.h>
#include "include/main.h"
#include "include/point.h"
#include "include/data/buf.h"
#include "include/data/data.h"
#include "include/gfx/sprite.h"
#include "include/gfx/graphic.h"
#include "include/common.h"
#include "include/number.h"


static SPRITE NumberSprite[NUMBER_MAX];
static char* NumberGraphicName[NUMBER_MAX] = {
	"number0.png"
};

void initNumber(){
	//ファイルは共通ファイルに含まれるので、ここで開く必要性はない。
}
int loadNumber(long end_ticks){
	static int i=0;
	for(;i<NUMBER_MAX;i++){
		/*FPS*/
		SDL_RWops* tmpData = getGraphixFile(&CommonArchive,NumberGraphicName[i]);
		getSpriteFromOPS(&NumberSprite[i],tmpData);
		tmpData->close(tmpData);					//メモリ開放は忘れずに
		if(end_ticks < SDL_GetTicks()){
			return FALSE;
		}
	}
	return TRUE;
}
int finishLoadNumber(){
	return TRUE;
}

void quitNumber(){
	int i=0;
	for(;i<NUMBER_MAX;i++){
		deleteSprite(&NumberSprite[i]);
	}
}


/**
 * 数字を描画します。
 */
void drawNumber(const glPoint* point,int graphic,unsigned int num,unsigned int digit){
	SPRITE* sprite = &NumberSprite[graphic];
	int width = sprite->Width / 10;
	int height = sprite->Height;

	glPoint painted;
	painted.x = point->x;
	painted.y = point->y;
	painted.radius = 0;
	painted.width = width>>1;
	painted.height = height>>1;
	
	int digit_count=0;
	while(num > 0){
		digit_count++;
		unsigned int d = num%10;
		num /= 10;
		drawSprite(sprite,&painted,d*width,0,width,height,0.0f);
		painted.x -= width;
	}
	int i=digit_count;
	for(;i<digit;i++){
		drawSprite(sprite,&painted,0*width,0,width,height,0.0f);
		painted.x -= width;
	}
}
