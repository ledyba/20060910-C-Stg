/*���\�[�X��`�t�@�C���̓ǂݍ���*/
#include <SDL.h>
#include <SDL_rwops.h>
#include <SDL_image.h>
#include <GL/gl.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/main.h"
#include "../include/point.h"
#include "../include/data/buf.h"
#include "../include/data/data.h"
#include "../include/gfx/sprite.h"
#include "../include/gfx/spriteArea.h"
#include "../include/gfx/animation.h"
#include "../include/stage/animationManager.h"
#include "../include/data/resource_define.h"
/**
 * ���\�[�X�f�[�^��Ԃ��B
 */
void loadResourceDefine(RESOURCE_LIST* list,BUF* buffer){
	//�擪�̕�������΂��B
	seekBuf(buffer,(long)strlen(RESOURCE_DEFINE_HEADER),SEEK_SET);
	//�t�@�C�����[�h�ǂݍ���
	readBuf(buffer,&list->mode,sizeof(list->mode));
	//�ő�t�@�C�����Ƃ���ǂݍ��݁B
	int max_file = 0;
	switch(list->mode){
		case RESOURCE_MODE_GRAHIC:
			max_file = GRAPHIC_MAX;
			break;
		case RESOURCE_MODE_MOTION:
			break;
	}
	//�t�@�C�����ǂݍ���
	int file_num,i;
	readBuf(buffer,&file_num,sizeof(file_num));
	list->file_num = file_num;
	if(file_num >= max_file)	raiseError("file reading error in loadResourceDefine.\n","->resource num is invalid.");
	//�t�@�C�����ǂݍ��݂̂��߂̃������m�ہB
	list->item = malloc(sizeof(RESOURCE_LIST_ITEM) * file_num);
	for(i=0;i<file_num;i++){
		RESOURCE_LIST_ITEM* item = &list->item[i];
		//ID�ǂݍ���
		readBuf(buffer,&item->num,sizeof(item->num));
		if(item->num >= max_file)	raiseError("file reading error in loadResourceDefine.\n","->item id is invalid.");
		//�t�@�C�����ǂݍ���
		int length;
		readBuf(buffer,&length,sizeof(length));
		item->filename = malloc(length + 1);
		readBuf(buffer,item->filename,length);
		//�I�[�R�[�h
		item->filename[length] = '\0';
	}
}
/**
 * �쐬�������X�g���A�j������B
 */
void closeResourceDefine(RESOURCE_LIST* list){
	int i=0,max=list->file_num;
	for(;i<max;i++){
		free(list->item[i].filename);
	}
	free(list->item);
}

