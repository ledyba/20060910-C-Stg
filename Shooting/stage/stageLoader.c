/*�X�e�[�W�f�[�^�̓ǂݍ��݂��s���܂��B*/
#include <SDL.h>
#include <SDL_rwops.h>
#include <GL/gl.h>
#include <windows.h>
#include <stdio.h>
#include <PGL.h>
#include "../include/stage/stageLoader.h"
#include "../include/main.h"
#include "../include/stage/animationManager.h"
#include "../include/stage/stageEngine.h"

/**
 * �X�e�[�W���[�_������������B
 */
void initStageLoader(){
}
/**
 * �X�e�[�W���[�_���I������
 */
void quitStageLoader(){
	//�X�e�[�W�G���W�����J�n����B
	//��������[�A�X�p�Q�b�e�B���ȁB
	startStageEngine();
}
