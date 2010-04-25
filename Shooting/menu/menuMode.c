#include <SDL.h>
#include <SDL_rwops.h>
#include <GL/gl.h>
#include <stdio.h> 
#include <windows.h>
#include <PGL.h>
#include "../include/main.h"
#include "../include/input.h"
#include "../include/load.h"
#include "../include/menu/menu.h"
#include "../include/menu/menuMode.h"
#include "../include/menu/menuFunc.h"
#include "../include/menu/menuDefine.h"
#include "../include/fps.h"

/*
 * ���j���[��`�����߂̃\�[�X
 * */
	static int SceneCnt;
	static int MenuCnt;
void initMenu(){
	SceneCnt = 0;
	MenuCnt = 0;
}
void quitMenu(){
	/*���j���[�֌W�Ŋm�ۂ����������̊J��*/
	int i=0;
	for(;i<MENU_SCNE_NUM;i++){
		MENU_SCENE *scene = &MenuSceneArray[i];
		//���j���[�̔w�i�X�v���C�g�폜
		deleteSprite(&scene->BGsprite);
		int j=0;
		for(;j<MENU_MAX;j++){
			MENU *menu = &scene->menu[j];
			if(menu->MenuType == MENU_TYPE_NOT_EXIST) continue;
			//���j���[�̕�����X�v���C�g�̍폜
			deleteSprite(&menu->TitleSprite);
			switch(menu->MenuType){
				case MENU_TYPE_BUTTON:
					break;
				case MENU_TYPE_INPUT:
					break;
				case MENU_TYPE_CHOSE:
					{
						int k=0;
						for(;k<menu->MenuItemNum;k++){
							MENU_CHOSE_ITEM *item = &menu->Item[k];
							if(item->MenuItemType == MENU_CHOSE_ITEM_TYPE_EXIST){
								//Choose�́A�I�ԑI�����̍폜
								deleteSprite(&item->ItemSprite);
							}
						}
					}
					break;
				default:
					break;
			}
		}
	}
	
}
int loadMenu(long next_frame,ARCHIVE* archive){
	/*���[�v�J�n*/
	int i= SceneCnt;
	for(;i<MENU_SCNE_NUM;i++){
		MENU_SCENE_DEFINE *scene_define = &MenuSceneDefine[i];
		MENU_SCENE *scene = &MenuSceneArray[i];
		scene->MenuNum = scene_define->MenuNum;
		int j=MenuCnt;
		for(;j<MENU_MAX;j++){
			MENU_DEFINE *menu_define = &scene_define->MenuDefine[j];
			MENU *menu = &scene->menu[j];
			//type
			menu->MenuType = menu_define->MenuType;
			if(menu->MenuType == MENU_TYPE_NOT_EXIST) continue;
			//TitleTexID
			SDL_RWops* titleData = getGraphixFile(archive,menu_define->MenuStr);
			getSpriteFromOPS(&menu->TitleSprite,titleData);
			titleData->close(titleData);					//�������J���͖Y�ꂸ��
			switch(menu->MenuType){
				case MENU_TYPE_BUTTON:
					//�֐�
					menu->ButtonType_MenuFunc = menu_define->ButtonType_MenuFunc;
					break;
				case MENU_TYPE_INPUT:
					break;
				case MENU_TYPE_CHOSE:
					//�A�C�e����
					menu->MenuItemNum = menu_define->MenuItemNum;
					{
						int k=0;
						for(;k<menu->MenuItemNum;k++){
							MENU_CHOSE_ITEM_DEFINE *item_define = &menu_define->ItemDefine[k];
							MENU_CHOSE_ITEM *item = &menu->Item[k];
							if(item_define->MenuItemType == MENU_CHOSE_ITEM_TYPE_EXIST){
								//ItemType
								item->MenuItemType = MENU_CHOSE_ITEM_TYPE_EXIST;
								//TitleTexID
								SDL_RWops* itemData = getGraphixFile(archive,item_define->ItemStr);
								getSpriteFromOPS(&item->ItemSprite,itemData);
								itemData->close(itemData);					//�������J���͖Y�ꂸ��
							}
						}
					}
					break;
				default:
					break;
			}
			MenuCnt++;
			//�^�C�����~�b�g
			long left = next_frame-SDL_GetTicks();
			if(left <= LOAD_TIME_LIMIT){
				return FALSE;
			}
		}
		//���j���[�w�i�̎擾
		//�����ɂ����Ȃ��ƁA���x���m�ۂ��ă�������n���H������B
		SDL_RWops* bgData = getGraphixFile(archive,scene_define->bgStr);
		getSpriteFromOPS(&scene->BGsprite,bgData);
		bgData->close(bgData);					//�������J���͖Y�ꂸ��
		SceneCnt++;
	}
	return TRUE;
}
int finishLoadMenu(){
	return TRUE;
}
/**/
void changeMenuScene(int scene){
	 MenuScene = scene;
}
#define PRESS_LIMIT 30
void moveMenu(){
	static int limit[4] = {0,0,0,0};
	static int can_move[4] = {0,0,0,0};
	int i;
	/*�����邩�ǂ����̃`�F�b�N*/
	for(i=0;i<4;i++){
		int analog_key = AnalogKey[i];
		if((Input & analog_key) != 0){
			limit[i]++;
		}else{
			limit[i]=0;
		}
		if(limit[i] > PRESS_LIMIT)	limit[i] = PRESS_LIMIT-4;
		can_move[i] = ((Input & analog_key) != 0 && (PrevInput & analog_key) == 0)
					|| (limit[i] >= PRESS_LIMIT);
	}
	MENU_SCENE *scene = &MenuSceneArray[MenuScene];
	/*�����L�[*/
	if(can_move[PAD_UP_INDEX]){
		if(MenuIndex > 0){
			MenuIndex--;
		}else{
			MenuIndex = scene->MenuNum-1;
		}
	}else if(can_move[PAD_DOWN_INDEX]){
		if(MenuIndex < scene->MenuNum-1){
			MenuIndex++;
		}else{
			MenuIndex = 0;
		}
	}
	MENU *menu = &scene->menu[MenuIndex];
	switch(menu->MenuType){
		case MENU_TYPE_BUTTON:
			if((Input & PadShotKey) != 0){
				/*�o�^����Ă���֐����Ăяo��*/
				menu->ButtonType_MenuFunc();
			}
			break;
		case MENU_TYPE_INPUT:
			break;
		case MENU_TYPE_CHOSE:
			/*�C���f�b�N�X�̈ړ�*/
			if(can_move[PAD_LEFT_INDEX]){
				if(menu->MenuItemIndex > 0){
					menu->MenuItemIndex--;
				}else{
					menu->MenuItemIndex = menu->MenuItemNum-1;
				}
			}else if(can_move[PAD_RIGHT_INDEX]){
				if(menu->MenuItemIndex < menu->MenuItemNum-1){
					menu->MenuItemIndex++;
				}else{
					menu->MenuItemIndex = 0;
				}
			}
			break;
		default:
			break;
	}
}
#define MAIN_MENU_WIDTH 180.0f
#define MAIN_MENU_HEIGHT 24.0f
#define MENU_WIDTH 120.0f
#define MENU_HEIGHT 18.0f
#define MENU_CURSOR_SIZE 15.0f
const glPoint MenuStartPoint={(SCREEN_WIDTH>>4)*3,(SCREEN_HEIGHT>>3)*3,0,0,0};
const float CursorColor[] = {1.0f,0.7f,1.0f,1.0f};
void drawMenu(){
	glPoint menu_draw_point = MenuStartPoint;
	MENU_SCENE *scene = &MenuSceneArray[MenuScene];
	/*�w�i�`��*/
	drawSprite(&scene->BGsprite,&BG_AREA,0,0,scene->BGsprite.Width,scene->BGsprite.Height,0.0f);
	/*���j���[�̕����̑傫���́A���C�����j���[���ۂ��ŕς��*/
	if(MenuScene == MENU_SCENE_MAIN_MENU){
		menu_draw_point.width = MAIN_MENU_WIDTH/2;
		menu_draw_point.height= MAIN_MENU_HEIGHT/2;
	}else{
		menu_draw_point.width = MENU_WIDTH/2;
		menu_draw_point.height= MENU_HEIGHT/2;
	}
	int i=0;
	for(;i<scene->MenuNum;i++){
		MENU *menu = &scene->menu[i];
		/*���j���[�̕`��ꏊ����i�߂�*/
		menu_draw_point.y += menu_draw_point.height*2;
		if(menu->MenuType == MENU_TYPE_NOT_EXIST) continue;
		if(i == MenuIndex){
			/*�J�[�\���̕`��*/
			glPoint cursor_point = {
				menu_draw_point.x-menu_draw_point.width-MENU_CURSOR_SIZE,
				menu_draw_point.y,
				0,0,0};
				drawCursor(&cursor_point,MENU_CURSOR_SIZE ,CursorColor,TRUE);
		}
		/*���j���[�e�L�X�g�̕\��*/
		drawSprite(&menu->TitleSprite,&menu_draw_point,0,0,menu->TitleSprite.Width,menu->TitleSprite.Height,0.0f);
		switch(menu->MenuType){
			case MENU_TYPE_BUTTON:
				break;
			case MENU_TYPE_INPUT:
				break;
			case MENU_TYPE_CHOSE:
				{
					int j=0;
					/*�|�C���g�̐ݒ�*/
					glPoint menu_item_draw_point = {
							menu_draw_point.x + menu_draw_point.width*2,
							menu_draw_point.y,
							0,
							menu_draw_point.width,
							menu_draw_point.height,
							};
					MENU_CHOSE_ITEM *item = menu->Item;
					for(;j<menu->MenuItemNum;j++){
						/*�A�C�e���I�����̕\��*/
						if(item->MenuItemType == MENU_CHOSE_ITEM_TYPE_EXIST){
							/*�`��*/
							drawSprite(
										&item->ItemSprite,
										&menu_item_draw_point,
										0,
										0,
										item->ItemSprite.Width,
										item->ItemSprite.Height,
										0.0f
										);
							/*���I�𒆂�Item���ۂ�*/
							if(menu->MenuItemIndex == j){
								/*����ɑI�������ƕ�����悤�Ȏl�p�`��\��*/
								drawBox(&menu_item_draw_point,FALSE,2,CursorColor);
							}
							menu_item_draw_point.x += menu_draw_point.width*2;
						}
						item++;
					}
				}
				break;
			default:
				break;
		}
	}
}
