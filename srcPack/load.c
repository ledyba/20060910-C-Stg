#include <SDL.h>
#include <SDL_rwops.h>
#include <GL/gl.h>
#include <stdio.h> 
#include <windows.h>
#include "include/main.h"
#include "include/point.h"
#include "include/load.h"
#include "include/data/buf.h"
#include "include/data/data.h"
#include "include/gfx/sprite.h"
#include "include/gfx/graphic.h"
	static LOAD_FUNCS* LoadFuncs;
	static void (*initFunc)();
	static void (*finishFunc)();
	static int Funcs = 0;
	static int LoadIndex = 0;
	static int NextMode;
	/*���[�h��ʂ̔w�i�X�v���C�g*/
	static SPRITE LoadBGSprite;

void initLoad(){
	/*�t�@�C���I�[�v��*/
	ARCHIVE archive;
	openArchive(&archive,LOAD_ARCHIVE);
	/*�w�i�擾*/
	SDL_RWops* bgData = getGraphixFile(&archive,LOAD_BG);
	getSpriteFromOPS(&LoadBGSprite,bgData);
	bgData->close(bgData);					//�������J���͖Y�ꂸ��
	closeArchive(&archive);
	
}
/*���[�h��ʂ̏����E�I��*/
void setLoad(int funcs,void (*init_func)(),void (*finish_func)(),LOAD_FUNCS* load_funcs, int next_mode){
	LoadIndex = 0;
	/*�ϐ��Z�b�g*/
	initFunc = init_func;
	finishFunc = finish_func;
	Funcs = funcs;					//�֐���
	LoadFuncs = load_funcs;
	NextMode = next_mode;
	//�ŏ��̊֐��ǂݍ���
	if(initFunc != NULL)	initFunc();
	//�v���y�A
	startLoad();
	/*��ʐ؂�ւ�*/
	GameScene = GAME_SCENE_LOADING;
	/*��񂾂��`��*/
	drawLoad();
	SDL_GL_SwapBuffers();
}
void quitLoad(){
	/*�e�N�X�`���̍폜*/
	glDeleteTextures(1,&LoadBGSprite.TexID);
}
void startLoad(){
	/*���[�h�̏���*/
	LoadFuncs[LoadIndex].init();
}
/*������*/
void moveLoad(){
	int isLoadFinished = LoadFuncs[LoadIndex].load(NextTick);
	if(isLoadFinished == TRUE){
		LoadFuncs[LoadIndex].finish();
		LoadIndex++;
		if(LoadIndex >= Funcs){
			if(finishFunc != NULL)	finishFunc();
			/*���[�h���I�������V�[����ς���*/
			GameScene = NextMode;
		}else{
			startLoad();
		}
	}
}
/*�`�ʂ���*/
void drawLoad(){
	drawSprite(&LoadBGSprite,&BG_AREA,0,0,LoadBGSprite.Width,LoadBGSprite.Height,0.0f);
}

