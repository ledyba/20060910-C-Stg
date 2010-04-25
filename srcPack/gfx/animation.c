#include <SDL.h>
#include <SDL_rwops.h>
#include <SDL_image.h>
#include <GL/gl.h>
#include <windows.h>
#include "../include/main.h"
#include "../include/point.h"
#include "../include/data/buf.h"
#include "../include/data/data.h"
#include "../include/gfx/sprite.h"
#include "../include/gfx/spriteArea.h"
#include "../include/gfx/animation.h"

/**
 * アニメーションを読み込む
 */
void loadAnimation(ANIME_SET* graphic,ARCHIVE* archive,const char* file_name){
	BUF* gfx_file = getFile(archive,file_name);
	//ヘッダを飛ばす。
	seekBuf(gfx_file,(long)strlen(ANIME_HEADER),SEEK_SET);
	//ファイル名取得
	int filename_size;
	readBuf(gfx_file,&filename_size,sizeof(filename_size));
	graphic->filename_size = filename_size;
	graphic->filename = malloc(filename_size+1);
	readBuf(gfx_file,graphic->filename,filename_size);
	graphic->filename[filename_size] = '\0';
	//スプライト取得
	SDL_RWops* frame_ops = getGraphixFile(archive,graphic->filename);
	getSpriteFromOPS(&graphic->sprite,frame_ops);
	frame_ops->close(frame_ops);					//メモリ開放は忘れずに
	//スプライトエリア用スプライト
	SPRITE* anime_sprite = &graphic->sprite;
	//モード、フラグ、アニメ数。
	readBuf(gfx_file,&graphic->mode,sizeof(graphic->mode));
	readBuf(gfx_file,&graphic->flag,sizeof(graphic->flag));
	readBuf(gfx_file,&graphic->anime_num,sizeof(graphic->anime_num));
	int anime_num = graphic->anime_num;
	graphic->anime = malloc( sizeof(ANIMATION*) * anime_num );
	int i=0;
	for(;i<anime_num;i++){
		//アニメ番号
		int num = 0;
		readBuf(gfx_file,&num,sizeof(num));
		if(anime_num < num) raiseError("invalid animation file:",file_name);
		//メモリ確保。
		graphic->anime[num] = malloc(sizeof(ANIMATION));
		ANIMATION* anime = graphic->anime[num];
		anime->num = num;
		//フレーム番号取得
		int frame_num;
		readBuf(gfx_file,&frame_num,sizeof(frame_num));
		anime->frame_num = frame_num;
		anime->frame = malloc(sizeof(ANIMATION_FRAME)*frame_num);
		int j;
		for(j=0;i<frame_num;j++){
			//フレームへのポインタの設定
			ANIMATION_FRAME* frame = &anime->frame[j];
			//持続時間
			readBuf(gfx_file,&frame->frame_time,sizeof(frame->frame_time));
			//スプライトの設定
			frame->sprite_area.sprite = anime_sprite;
			readBuf(gfx_file,&frame->sprite_area.x,sizeof(frame->sprite_area.x));
			readBuf(gfx_file,&frame->sprite_area.y,sizeof(frame->sprite_area.y));
			readBuf(gfx_file,&frame->sprite_area.width,sizeof(frame->sprite_area.width));
			readBuf(gfx_file,&frame->sprite_area.height,sizeof(frame->sprite_area.height));
		}
	}
	deleteBuf(gfx_file);
}
/**
 * メモリを開放する。
 */
void deleteAnimation(ANIME_SET* graphic){
	int i=0,anime_num = graphic->anime_num;
	for(;i<anime_num;i++){
		ANIMATION* anime = graphic->anime[i];
		free(anime->frame);
		free(anime);
	}
	free(graphic->anime);
	deleteSprite(&graphic->sprite);
	free(graphic->filename);
	free(graphic);
}
/**
 * アニメーションを描画する。
 */
void drawAnimation(ANIME_RECORD* record,const glPoint* point){
	ANIMATION* anime = record->graphic->anime[record->anime];
	SPRITE_AREA* sprite_area = &anime->frame[record->frame].sprite_area;
	drawSpriteArea(point,sprite_area,record->angle);
	int* frame_left = &record->frame_left;
	*frame_left--;
	if(!(*frame_left > 0)){
		int* frame = &record->frame;
		*frame++;
		*frame %= anime->frame_num;
		*frame_left = anime->frame[*frame].frame_time;
	}
}
int changeAnimation(ANIME_RECORD* record,int anime){
	if(record->graphic->anime_num >= anime){
		return FALSE;
	}
	record->anime = anime;
	record->frame = 0;
	record->frame_left = record->graphic->anime[anime]->frame[0].frame_time;
	return TRUE;
}
int changeAnimeAngle(ANIME_RECORD* record,float angle){
	if((record->graphic->flag & ANIME_FLAG_RORATE) != 0){
		record->angle = angle;
		return TRUE;
	}else{
		return FALSE;
	}
}

