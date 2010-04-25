#include <SDL.h>
#include <GL/gl.h>
#include <windows.h>
#include <PGL.h>

#include "include/number.h"


static SPRITE NumberSprite[NUMBER_MAX];
static SPRITE_AREA NumberSpriteArea[NUMBER_MAX][10];
static int LoadIndex=0;
static char* NumberGraphicName[NUMBER_MAX] = {
	"number0.png"
};

void initNumber(){
	//ファイルは共通ファイルに含まれるので、ここで開く必要性はない。
	LoadIndex = 0;
}
int loadNumber(long end_ticks,ARCHIVE* archive){
	int i=LoadIndex;
	for(;i<NUMBER_MAX;i++){
		if(end_ticks < SDL_GetTicks()){
			LoadIndex = i;
			return FALSE;
		}
		SPRITE* sprite = &NumberSprite[i];
		getSpriteFromArchive(sprite,archive,NumberGraphicName[i],TRUE);
		int x = 0;
		int y = 0;
		int w = sprite->Width / 10;
		int h = sprite->Height;
		int j;
		SPRITE_AREA* area = NumberSpriteArea[i];
		for(j=0;j<10;j++){
			makeSpriteArea(area,sprite,x,y,w,h);
			x+=w;
			area++;
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
	SPRITE_AREA* area = NumberSpriteArea[graphic];
	glPoint painted = *point;
	ufloat width = point->width * 2;
	int digit_count=0;
	while(num > 0){
		digit_count++;
		unsigned int d = num%10;
		num /= 10;
		drawSpriteArea(&painted,&area[d],0.0f);
		painted.x -= width;
	}
	int i=digit_count;
	for(;i<digit;i++){
		drawSpriteArea(&painted,&area[0],0.0f);
		painted.x -= width;
	}
}
//サイズは自動で補正してくれます。
void drawNumberA(const glPoint* point,int graphic,unsigned int num,unsigned int digit){
	ufloat width = NumberSprite[graphic].Width / 10;
	ufloat height = NumberSprite[graphic].Height;
	glPoint painted;
	painted.x = point->x;
	painted.y = point->y;
	painted.width = width/2;
	painted.height = height/2;
	drawNumber(&painted,graphic,num,digit);
}
