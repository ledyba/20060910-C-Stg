#include <SDL.h>
#include <GL/gl.h>
#include <stdio.h>
#include <windows.h>
#include "../include/main.h"
#include "../include/point.h"
#include "../include/menu/menuFunc.h"
/**
 * PlayButton�������ꂽ
 */
#include "../include/ship.h"
#include "../include/boss.h"
void MainMenu_PlayGameButtonPressed(){
	/**
	 * ���ݒu
	 * �X�e�[�W��p�̃��[�h�A�v���y�A���j�b�g��p�ӂ��邱�ƁB
	 */
	GameScene = GAME_SCENE_GAME;
	initShip();
	addBoss();
}

/**
 * EndButton�������ꂽ
 */ 
void MainMenu_EndButtonPressed(){
	//�I���t���O���Z�b�g
	setEndFlag(TRUE);
}
