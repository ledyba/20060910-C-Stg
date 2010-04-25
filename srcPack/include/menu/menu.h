
/*MENU_CHOSE_ITEM*/
#define MENU_CHOSE_ITEM_MAX 4
#define MENU_CHOSE_ITEM_TYPE_EXIST 1
#define MENU_CHOSE_ITEM_TYPE_NOT_EXIST 0
typedef struct {
	int MenuItemType;
	SPRITE ItemSprite;					//アイテム
}MENU_CHOSE_ITEM;

#define MENU_TYPE_NOT_EXIST	0	//存在しない
#define MENU_TYPE_BUTTON 		1	//単なるボタン
#define MENU_TYPE_INPUT		2	//入力
#define MENU_TYPE_CHOSE 		3	//選ぶ

typedef struct {
	int MenuType;								//メニューのタイプ
	SPRITE TitleSprite;							//メニューを表すスプライト
	void (*ButtonType_MenuFunc)(void);			//メニューを押したときの関数（TypeButton時）
	int MenuItemNum;							//メニューのアイテム数（TypeChose時）
	int MenuItemIndex;							//メニューの現在選択しているところ（TypeChose時）
	MENU_CHOSE_ITEM Item[MENU_CHOSE_ITEM_MAX];	//メニューのアイテム（TypeChose時）
}MENU;

#define MENU_MAX	8		//一画面のメニュー最大数
typedef struct {
	SPRITE	BGsprite;		//背景テクスチャ
	int MenuNum;			//メニュー数
	MENU menu[MENU_MAX];	//メニュー
}MENU_SCENE;

#define MENU_SCNE_NUM 1

MENU_SCENE MenuSceneArray[MENU_SCNE_NUM];

#define MENU_SCENE_MAIN_MENU 0

int MenuScene;
int MenuIndex;

