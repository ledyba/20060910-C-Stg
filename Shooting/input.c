#include <SDL.h>
#include <windows.h>

#include "include/main.h"
#include "include/input.h"

int initInput(){
	/*キー設定*/
	PadShotKey = PAD_BUTTON1;
	PadBombKey = PAD_BUTTON2;
	AnalogKey[PAD_UP_INDEX]=PAD_UP;
	AnalogKey[PAD_DOWN_INDEX]=PAD_DOWN;
	AnalogKey[PAD_LEFT_INDEX]=PAD_LEFT;
	AnalogKey[PAD_RIGHT_INDEX]=PAD_RIGHT;
	/*ジョイスティックが最低1本ある場合*/
	if(SDL_NumJoysticks() > 0){
		Joystick = SDL_JoystickOpen(0);
		if(Joystick){
			/*Joystickが存在するならば*/
			return 1;
		}else{
			//Joystick取得エラー
			fprintf(stderr,"failed to open joystick.\n");
		}
		return 0;
	}
	//無くてもキーボードって事で＾＾；
	return 1;
}
void updateInput(){
	/*インプットのリセット*/
	PrevInput = Input;//昔の保存
	Input = 0;
	Input |= getKeyBoardInput();
	Input |= getJoystickInput();
}
int getKeyBoardInput(){
	int input = 0;
	Keys = SDL_GetKeyState(NULL);
	if(Keys[SDLK_ESCAPE] == SDL_PRESSED){
		input |= KEY_ESCAPE;
	}
	if(Keys[SDLK_UP] == SDL_PRESSED){
		input |= PAD_UP;
	}
	if(Keys[SDLK_DOWN] == SDL_PRESSED){
		input |= PAD_DOWN;
	}
	if(Keys[SDLK_RIGHT] == SDL_PRESSED){
		input |= PAD_RIGHT;
	}
	if(Keys[SDLK_LEFT] == SDL_PRESSED){
		input |= PAD_LEFT;
	}
	if(Keys[SDLK_z] == SDL_PRESSED){
		input |= PAD_BUTTON0;
	}
	if(Keys[SDLK_x] == SDL_PRESSED){
		input |= PAD_BUTTON1;
	}
	if(Keys[SDLK_c] == SDL_PRESSED){
		input |= PAD_BUTTON2;
	}
	if(Keys[SDLK_v] == SDL_PRESSED){
		input |= PAD_BUTTON3;
	}

	
	return input;
}
int getJoystickInput(){
	Sint16 axis = 0;
	int i=0;
	int input = 0;
	int pad = PAD_BUTTON0;
	/*十字キー用*/

	/*ジョイスティック情報のアップデート*/
	SDL_JoystickUpdate();

	/*ボタン用ループ*/
	for(;i<PAD_BUTTON_MAX;i++){
		/*パッドが押されているならば*/
		if(SDL_JoystickGetButton(Joystick,i)==SDL_PRESSED){
			input |= pad;
		}
		/*パッドの識別用コードを自動生成*/
		pad <<= 1;
	}

	/*十字キー処理*/
	
	/* 軸0 (X) */
	axis=SDL_JoystickGetAxis(Joystick,0);
	if(axis >= 1024){
		input |= PAD_RIGHT;
	}else if(axis <= -1024){
		input |= PAD_LEFT;
	}

	/* 軸1 (Y) */
	axis=SDL_JoystickGetAxis(Joystick,1);
	if(axis >= 1024){
		input |= PAD_DOWN;
	}else if(axis <= -1024){
		input |= PAD_UP;
	}
	
	return input;
}
int quitInput(){
	SDL_JoystickClose(0);
	return 1;
}
