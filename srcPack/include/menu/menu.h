
/*MENU_CHOSE_ITEM*/
#define MENU_CHOSE_ITEM_MAX 4
#define MENU_CHOSE_ITEM_TYPE_EXIST 1
#define MENU_CHOSE_ITEM_TYPE_NOT_EXIST 0
typedef struct {
	int MenuItemType;
	SPRITE ItemSprite;					//�A�C�e��
}MENU_CHOSE_ITEM;

#define MENU_TYPE_NOT_EXIST	0	//���݂��Ȃ�
#define MENU_TYPE_BUTTON 		1	//�P�Ȃ�{�^��
#define MENU_TYPE_INPUT		2	//����
#define MENU_TYPE_CHOSE 		3	//�I��

typedef struct {
	int MenuType;								//���j���[�̃^�C�v
	SPRITE TitleSprite;							//���j���[��\���X�v���C�g
	void (*ButtonType_MenuFunc)(void);			//���j���[���������Ƃ��̊֐��iTypeButton���j
	int MenuItemNum;							//���j���[�̃A�C�e�����iTypeChose���j
	int MenuItemIndex;							//���j���[�̌��ݑI�����Ă���Ƃ���iTypeChose���j
	MENU_CHOSE_ITEM Item[MENU_CHOSE_ITEM_MAX];	//���j���[�̃A�C�e���iTypeChose���j
}MENU;

#define MENU_MAX	8		//���ʂ̃��j���[�ő吔
typedef struct {
	SPRITE	BGsprite;		//�w�i�e�N�X�`��
	int MenuNum;			//���j���[��
	MENU menu[MENU_MAX];	//���j���[
}MENU_SCENE;

#define MENU_SCNE_NUM 1

MENU_SCENE MenuSceneArray[MENU_SCNE_NUM];

#define MENU_SCENE_MAIN_MENU 0

int MenuScene;
int MenuIndex;

