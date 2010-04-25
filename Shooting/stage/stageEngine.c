/*�X�e�[�W�i�s�Ɋւ��邱�Ƃ��s���܂��B�����I�ɁB*/
#include <SDL.h>
#include <SDL_rwops.h>
#include <SDL_image.h>
#include <GL/gl.h>
#include <windows.h>
#include <PGL.h>
#include "../include/main.h"
#include "../include/data/buf.h"
#include "../include/data/data.h"
#include "../include/load.h"
#include "../include/stage/animationManager.h"
#include "../include/stage/stageEngine.h"
#include "../include/stage/stageLoader.h"
#
/**
 * �X�e�[�W�G���W��������������B
 */
//�X�e�[�W���Ƃ̃A�[�J�C�u��
static char* StageArchiveName[STAGE_MAX] = {
	"stage1.arc"
	"stage2.arc"
	"stage3.arc"
	"stage4.arc"
	"stage5.arc"
};
#define STAGE_LOAD_FUNC_NUM	1
static LOAD_FUNCS StageLoadFunc[STAGE_LOAD_FUNC_NUM] = {
	{initLoadGraphicManager,loadGraphicManager,finishLoadGraphicManager,quitGraphicManager},
};
int initStageEngine(int stage){
	StageNumber = stage;
	/*���ʃV�X�e���@������*/
	
	/*�X�e�[�W�t�@�C���ǂݍ��݁A�������B*/
	setLoad(STAGE_LOAD_FUNC_NUM,
			StageArchiveName[stage],
			initStageLoader,
			quitStageLoader,
			&StageLoadFunc[0],
			GAME_SCENE_GAME);
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
