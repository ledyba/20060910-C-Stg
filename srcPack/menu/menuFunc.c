#include <SDL.h>
#include <GL/gl.h>
#include <stdio.h>
#include <windows.h>
#include "../include/main.h"
#include "../include/point.h"
#include "../include/menu/menuFunc.h"
/**
 * PlayButtonが押された
 */
#include "../include/ship.h"
#include "../include/boss.h"
void MainMenu_PlayGameButtonPressed(){
	/**
	 * 仮設置
	 * ステージ専用のロード、プリペアユニットを用意すること。
	 */
	GameScene = GAME_SCENE_GAME;
	initShip();
	addBoss();
}

/**
 * EndButtonが押された
 */ 
void MainMenu_EndButtonPressed(){
	//終了フラグをセット
	setEndFlag(TRUE);
}
