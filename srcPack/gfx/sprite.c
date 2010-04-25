#include <SDL.h>
#include <SDL_rwops.h>
#include <SDL_image.h>
#include <GL/gl.h>
#include <windows.h>
#include "../include/main.h"
#include "../include/point.h"
#include "../include/rand.h"
#include "../include/gfx/sprite.h"
#include "../include/gfx/graphic.h"

/*スプライトの取得*/
void getSprite(SPRITE* sprite,SDL_Surface* Image){
	/*サーフェイスが削除される前に、以下の要素は設定する*/
	sprite->Width = Image->w;
	sprite->Height = Image->h;
	sprite->RealWidth = getMinPowerOfTwo(Image->w);
	sprite->RealHeight = getMinPowerOfTwo(Image->h);
	sprite->WidthF=(GLfloat)(Image->w)/sprite->RealWidth;
	sprite->HeightF=(GLfloat)(Image->h)/sprite->RealHeight;
	/*スプライトの取得*/
	sprite->TexID = getTexture(Image,sprite->RealWidth,sprite->RealHeight);
}

/*スプライトの削除*/
void deleteSprite(SPRITE* sprite){
	glDeleteTextures(1,&sprite->TexID);
}

/*二のべき乗で最も小さいのを探す*/
int getMinPowerOfTwo(int num){
	int ret = 1;
	while(ret < num){
		ret = ret << 1;
	}
	return ret;
}

void getSpriteFromOPS(SPRITE *sprite,SDL_RWops* data){
	getSprite(sprite,loadGraphix(data));
}

void drawSprite(const SPRITE* sprite,const glPoint* point,int x,int y, int w, int h , float angle){
	glPushMatrix();
	glTranslatef(point->x, point->y, 0);
	if(angle != 0.0f)glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glColor4f(1.0f,1.0f,1.0f,1.0f);
	glBindTexture(GL_TEXTURE_2D , sprite->TexID);
	float sprite_start_x = sprite->WidthF * x/ sprite->Width;
	float sprite_start_y = sprite->HeightF * y/ sprite->Height;
	float sprite_end_x = sprite->WidthF * (x+w)/ sprite->Width;
	float sprite_end_y = sprite->HeightF * (y+h)/ sprite->Height;
	glBegin(GL_TRIANGLE_FAN);
		glTexCoord2f(sprite_end_x , sprite_start_y);
		glVertex2f(point->width , -point->height);
		
		glTexCoord2f(sprite_end_x , sprite_end_y);
		glVertex2f(point->width , point->height);

		glTexCoord2f(sprite_start_x, sprite_end_y);
		glVertex2f(-point->width , point->height);

		glTexCoord2f(sprite_start_x , sprite_start_y);
		glVertex2f(-point->width , -point->height);
	glEnd();
	glDisable( GL_BLEND );
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
