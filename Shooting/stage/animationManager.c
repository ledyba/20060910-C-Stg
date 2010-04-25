/*�O���t�B�b�N��ǂݍ��񂾂肻�̑����낢��B*/
#include <SDL.h>
#include <SDL_rwops.h>
#include <SDL_image.h>
#include <GL/gl.h>
#include <windows.h>
#include <PGL.h>
#include "../include/main.h"
#include "../include/stage/stageEngine.h"
#include "../include/stage/stageLoader.h"
#include "../include/stage/animationManager.h"
//�A�[�J�C�u���ł̃��\�[�X��`�t�@�C���̃t�@�C����
const static char* FileName[GRAPHIC_MANAGER_RESOURCE_MAX] = {
	"bullet_gfx_list.rc",
	"foe_gfx_list.rc",
	"boss_gfx_list.rc",
	"effect_gfx_list.rc",
	"character_gfx_list.rc",
};
const static int GraphicIndex[GRAPHIC_MANAGER_RESOURCE_MAX] = {
	GRAPHIC_MANAGER_BULLET_INDEX,
	GRAPHIC_MANAGER_FOE_INDEX,
	GRAPHIC_MANAGER_BOSS_INDEX,
	GRAPHIC_MANAGER_EFFECT_INDEX,
	GRAPHIC_MANAGER_CHARACTER_INDEX,
};

void initLoadGraphicManager(){
	/*���ɂ�邱�Ƃ͖����E�E�E�Ǝv���B*/
}
int loadGraphicManager(long end_ticks,ARCHIVE* archive){
	//�O���t�B�b�N�ǂݍ��݁B
	//���\�[�X��`���W���[�����痈�����X�g�́A�����ƊJ������悤�ɁB
	int i=0;
	for(;i<GRAPHIC_MANAGER_RESOURCE_MAX;i++){
		int index = GraphicIndex[i];
		//���\�[�X��`�t�@�C���t�@�C���̃o�b�t�@���쐬�B
		BUF* list_buffer = getFile(archive,FileName[i]);
		RESOURCE_LIST rc_list;
		//���\�[�X���X�g�ǂݍ���
		loadResourceDefine(&rc_list,list_buffer);
		int j;
		int file_num = rc_list.file_num;
		//�O���t�B�b�N�ǂݍ���
		for(j=0;j<file_num;j++){
			int num = rc_list.item[j].num;
			loadAnimation(&Animation[index+num],archive,rc_list.item[i].filename);
		}
		//�������J��
		closeResourceDefine(&rc_list);
		deleteBuf(list_buffer);
	}
	return TRUE;
}
int finishLoadGraphicManager(){
	//���������ɖ������ȁ[�Ȃ�āB
	return TRUE;
}

/*�������J��*/
void quitGraphicManager(){
}
