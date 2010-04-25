/*�X�e�[�W�i�s�Ɋւ��邱�Ƃ��s���܂��B�����I�ɁB*/
#include <SDL.h>
#include <SDL_rwops.h>
#include <SDL_image.h>
#include <GL/gl.h>
#include <windows.h>
#include "../include/load.h"
#include "../include/main.h"
#include "../include/point.h"
#include "../include/data/buf.h"
#include "../include/data/data.h"
#include "../include/gfx/sprite.h"
#include "../include/gfx/spriteArea.h"
#include "../include/gfx/animation.h"
#include "../include/stage/animationManager.h"
#include "../include/stage/stageEngine.h"
#include "../include/stage/stageLoader.h"
#
/**
 * �X�e�[�W�G���W��������������B
 */
#define STAGE_LOAD_FUNC_NUM	1
static LOAD_FUNCS StageLoadFunc[STAGE_LOAD_FUNC_NUM] = {
	{initLoadGraphicManager,loadGraphicManager,finishLoadGraphicManager},
};
int initStageEngine(int stage){
	StageNumber = stage;
	/*���ʃV�X�e���@������*/
	
	/*�X�e�[�W�t�@�C���ǂݍ��݁A�������B*/
	setLoad(STAGE_LOAD_FUNC_NUM,initStageLoader,quitStageLoader,&StageLoadFunc[0],GAME_SCENE_GAME);
	startLoad();
	return TRUE;
}
/**
 * �X�e�[�W�G���W�������ۂɓ�����
 */
void startStageEngine(){
	//���[�h�ǂݍ��݌�A�����ɔ��ł���B
}
/**
 * �G�����A�C�x���g�����Ȃǂ𑍍��I�ɍs���B
 */
void moveStageEngine(){
}
/**
 * �������J���A���̑������������s���B
 * moveStageEngine����̂݁A�Ă΂��B
 */
int quitStageEngine(){
	return TRUE;
}
