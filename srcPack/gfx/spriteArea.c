#include <SDL.h>
#include <SDL_rwops.h>
#include <GL/gl.h>
#include <windows.h>
#include "../include/main.h"
#include "../include/point.h"
#include "../include/gfx/sprite.h"
#include "../include/gfx/spriteArea.h"

/*スプライトエリアを設定する。*/
void makeSpriteArea(SPRITE_AREA* sprite_area,SPRITE* sprite,int x,int y,int w,int h){
	sprite_area->sprite = sprite;
	sprite_area->x = x;
	sprite_area->y = y;
	sprite_area->width = w;
	sprite_area->height = h;
}

/*スプライトのエリアを描写する*/
void drawSpriteArea(const glPoint* point,const SPRITE_AREA* sprite_area,float angle){
	drawSprite(sprite_area->sprite,point,sprite_area->x,sprite_area->y,sprite_area->width,sprite_area->height, angle);
}
