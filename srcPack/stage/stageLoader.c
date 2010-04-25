/*�X�e�[�W�f�[�^�̓ǂݍ��݂��s���܂��B*/
#include <SDL.h>
#include <SDL_rwops.h>
#include <GL/gl.h>
#include <windows.h>
#include <stdio.h>
#include "../include/data/buf.h"
#include "../include/data/data.h"
#include "../include/stage/stageLoader.h"
#include "../include/main.h"
#include "../include/point.h"
#include "../include/gfx/sprite.h"
#include "../include/gfx/spriteArea.h"
#include "../include/gfx/animation.h"
#include "../include/stage/animationManager.h"
#include "../include/stage/stageEngine.h"

//�X�e�[�W���Ƃ̃A�[�J�C�u��
static char* StageArchiveName[STAGE_MAX] = {
	"stage1.arc"
	"stage2.arc"
	"stage3.arc"
	"stage4.arc"
	"stage5.arc"
};
/**
 * �X�e�[�W���[�_������������B
 */
void initStageLoader(){
	openArchive(&StageArchive,StageArchiveName[StageNumber]);
}
/**
 * �X�e�[�W���[�_���I������
 */
void quitStageLoader(){
	closeArchive(&StageArchive);
	//�X�e�[�W�G���W�����J�n����B
	//��������[�A�X�p�Q�b�e�B���ȁB
	startStageEngine();
}
