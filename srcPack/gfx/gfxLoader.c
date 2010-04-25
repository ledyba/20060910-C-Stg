#include <SDL.h>
#include <SDL_rwops.h>
#include <SDL_image.h>
#include <GL/gl.h>
#include <windows.h>
#include "../include/gfx/gfxLoader.h"
    /*VRAMにテクスチャをおく*/
    static GLfloat prioritie = 1.0;
GLuint getTexture(SDL_Surface* Image,int width, int height){
	GLuint texID;
	SDL_Surface *tmpImage;
	if( Image != NULL ){
	tmpImage = SDL_CreateRGBSurface( SDL_SWSURFACE, width, height, 32, 
#if SDL_BYTEORDER == SDL_LIL_ENDIAN /* OpenGL RGBA masks */
			0x000000FF, 
			0x0000FF00, 
			0x00FF0000, 
			0xFF000000
#else
			0xFF000000,
			0x00FF0000, 
			0x0000FF00, 
			0x000000FF
#endif
	);

//    Image = SDL_ConvertSurface( Image, tmpImage->format, SDL_SWSURFACE );
//--

	if ( (Image->flags & SDL_SRCALPHA) == SDL_SRCALPHA ) {
		SDL_SetAlpha(Image, 0, 0);
	}

//--

    
	/*サイズを変更する。*/
	SDL_Rect area = {0,0,Image->w,Image->h};
    SDL_BlitSurface(Image,&area,tmpImage,&area);
	/*いらないので開放。*/
    SDL_FreeSurface( Image );
	/*デバッグ用*/
	/*
    unsigned char r,g,b,a;
    SDL_GetRGBA(*((Uint32*)tmpImage->pixels),tmpImage->format,&r,&g,&b,&a);
    fprintf(stdout,"red		:%d\n",r);
    fprintf(stdout,"green	:%d\n",g);
    fprintf(stdout,"blue	:%d\n",b);
    fprintf(stdout,"alpha	:%d\n\n",a);
    */

    /*サーフェイスからテクスチャを製作する*/
    glGenTextures( 1, &texID );
    glBindTexture( GL_TEXTURE_2D, texID );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
								  GL_RGBA, GL_UNSIGNED_BYTE, tmpImage->pixels );

	/*テクスチャの優先度の設定*/
    glPrioritizeTextures(1,&texID,&prioritie);
	/*サーフェイスの開放*/
    SDL_FreeSurface( tmpImage );
	}
	return texID;
}

SDL_Surface* loadGraphix(SDL_RWops* data){
	return IMG_LoadPNG_RW(data);
}
