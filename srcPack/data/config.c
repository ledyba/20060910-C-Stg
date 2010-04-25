#include <SDL.h>
#include <stdio.h>
#include <windows.h>
#include "../include/main.h"
#include "../include/input.h"
#include "../include/data/config.h"

void initConfig(){
	/*設定読み込み*/
	if(!loadConfig())raiseError("failed to load Config File.",NULL);
	/*その設定を、セットする。*/
	if(!setConfig())raiseError("failed to set Config File.",NULL);
}
int setConfig(){
	/*キー設定*/
	return TRUE;
}
int loadConfig(){
	FILE* file  = fopen(CONFIG_FILE, "rb");
	/*ファイルが無ければ作り直し*/
	if(file == NULL){
		makeNewConfigFile();
		/*そして再度読み込み*/
		file  = fopen(CONFIG_FILE, "rb");
	}
	int num = fread(&ConfigData,sizeof(ConfigData),1,file);
	fclose(file);
	if(num == 1){		/*正しく読み込めた*/
		return TRUE;
	}else{				/*ファイルサイズがおかしい場合は作り直し*/
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
