
#define MENU_ARCHIVE "menu.arc"

typedef struct{
	int MenuItemType;
	char* ItemStr;
}MENU_CHOSE_ITEM_DEFINE;

typedef struct{
	int MenuType;
	char* MenuStr;
	void (*ButtonType_MenuFunc)(void);//関数
	int MenuItemNum;
	MENU_CHOSE_ITEM_DEFINE ItemDefine[MENU_CHOSE_ITEM_MAX];
}MENU_DEFINE;

typedef struct{
	char* bgStr;
	int MenuNum;
	MENU_DEFINE MenuDefine[MENU_MAX];
}MENU_SCENE_DEFINE;

MENU_SCENE_DEFINE MenuSceneDefine[MENU_SCNE_NUM]={
	/*MainMenu*/
	{"MainMenuBG.png",6,
		{
			/*ゲームスタート*/
			{MENU_TYPE_BUTTON,"MainMenuGameStart.png",MainMenu_PlayGameButtonPressed,0,
				{
					{MENU_CHOSE_ITEM_TYPE_NOT_EXIST,NULL},
					{MENU_CHOSE_ITEM_TYPE_NOT_EXIST,NULL},
					{MENU_CHOSE_ITEM_TYPE_NOT_EXIST,NULL},
					{MENU_CHOSE_ITEM_TYPE_NOT_EXIST,NULL},
				}
			},
			/*プラクティス*/
			{MENU_TYPE_BUTTON,"MainMenuPractice.png",MainMenu_PlayGameButtonPressed,0,
				{
					{MENU_CHOSE_ITEM_TYPE_NOT_EXIST,NULL},
					{MENU_CHOSE_ITEM_TYPE_NOT_EXIST,NULL},
					{MENU_CHOSE_ITEM_TYPE_NOT_EXIST,NULL},
					{MENU_CHOSE_ITEM_TYPE_NOT_EXIST,NULL},
				}
			},
			/*ハイスコア*/
			{MENU_TYPE_BUTTON,"MainMenuHiScore.png",MainMenu_PlayGameButtonPressed,0,
				{
					{MENU_CHOSE_ITEM_TYPE_NOT_EXIST,NULL},
					{MENU_CHOSE_ITEM_TYPE_NOT_EXIST,NULL},
					{MENU_CHOSE_ITEM_TYPE_NOT_EXIST,NULL},
					{MENU_CHOSE_ITEM_TYPE_NOT_EXIST,NULL},
				}
			},
			/*リプレイ*/
			{MENU_TYPE_BUTTON,"MainMenuReplay.png",MainMenu_PlayGameButtonPressed,0,
				{
					{MENU_CHOSE_ITEM_TYPE_NOT_EXIST,NULL},
					{MENU_CHOSE_ITEM_TYPE_NOT_EXIST,NULL},
					{MENU_CHOSE_ITEM_TYPE_NOT_EXIST,NULL},
					{MENU_CHOSE_ITEM_TYPE_NOT_EXIST,NULL},
				}
			},
			/*設定*/
			{MENU_TYPE_BUTTON,"MainMenuConfig.png",MainMenu_PlayGameButtonPressed,0,
				{
					{MENU_CHOSE_ITEM_TYPE_NOT_EXIST,NULL},
					{MENU_CHOSE_ITEM_TYPE_NOT_EXIST,NULL},
					{MENU_CHOSE_ITEM_TYPE_NOT_EXIST,NULL},
					{MENU_CHOSE_ITEM_TYPE_NOT_EXIST,NULL},
				}
			},
			/*終了*/
			{MENU_TYPE_BUTTON,"MainMenuEnd.png",MainMenu_EndButtonPressed,0,
				{
					{MENU_CHOSE_ITEM_TYPE_NOT_EXIST,NULL},
					{MENU_CHOSE_ITEM_TYPE_NOT_EXIST,NULL},
					{MENU_CHOSE_ITEM_TYPE_NOT_EXIST,NULL},
					{MENU_CHOSE_ITEM_TYPE_NOT_EXIST,NULL},
				}
			},
			{MENU_TYPE_NOT_EXIST,NULL,NULL,0,
				{
					{MENU_CHOSE_ITEM_TYPE_NOT_EXIST,NULL},
					{MENU_CHOSE_ITEM_TYPE_NOT_EXIST,NULL},
					{MENU_CHOSE_ITEM_TYPE_NOT_EXIST,NULL},
					{MENU_CHOSE_ITEM_TYPE_NOT_EXIST,NULL},
				}
			},
			{MENU_TYPE_NOT_EXIST,NULL,NULL,0,
				{
					{MENU_CHOSE_ITEM_TYPE_NOT_EXIST,NULL},
					{MENU_CHOSE_ITEM_TYPE_NOT_EXIST,NULL},
					{MENU_CHOSE_ITEM_TYPE_NOT_EXIST,NULL},
					{MENU_CHOSE_ITEM_TYPE_NOT_EXIST,NULL},
				}
			},
		},
	}
};

