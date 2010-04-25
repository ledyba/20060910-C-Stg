#include <SDL.h>
#include <stdio.h>
#include <windows.h>
#include "../include/main.h"
#include "../include/input.h"
#include "../include/data/config.h"

void initConfig(){
	/*�ݒ�ǂݍ���*/
	if(!loadConfig())raiseError("failed to load Config File.",NULL);
	/*���̐ݒ���A�Z�b�g����B*/
	if(!setConfig())raiseError("failed to set Config File.",NULL);
}
int setConfig(){
	/*�L�[�ݒ�*/
	return TRUE;
}
int loadConfig(){
	FILE* file  = fopen(CONFIG_FILE, "rb");
	/*�t�@�C����������΍�蒼��*/
	if(file == NULL){
		makeNewConfigFile();
		/*�����čēx�ǂݍ���*/
		file  = fopen(CONFIG_FILE, "rb");
	}
	int num = fread(&ConfigData,sizeof(ConfigData),1,file);
	fclose(file);
	if(num == 1){		/*�������ǂݍ��߂�*/
		return TRUE;
	}else{				/*�t�@�C���T�C�Y�����������ꍇ�͍�蒼��*/
		makeNewConfigFile();
		return TRUE;
	}
}
int saveConfig(){
	FILE* file  = fopen(CONFIG_FILE, "wb");
	int num = fwrite(&ConfigData, sizeof(ConfigData), 1, file);
	fclose(file);
	if(num == 1)	return TRUE;
	else			return FALSE;
}
int makeNewConfigFile(){
		fprintf(stdout,"Making new config file...");
		FILE* file  = fopen(CONFIG_FILE, "wb");
		int tmp = 0x00;
		fwrite(&tmp, sizeof(ConfigData), 1, file);
		fclose(file);
		fprintf(stdout,"done.\n");
		return TRUE;
}
