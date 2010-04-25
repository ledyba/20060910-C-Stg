/*リソース定義ファイルの読み込み*/

typedef struct{
	int num;
	char* filename;
}RESOURCE_LIST_ITEM;

typedef struct{
	int mode;
	int file_num;
	RESOURCE_LIST_ITEM* item;
}RESOURCE_LIST;
#define RESOURCE_MODE_GRAHIC 1
#define RESOURCE_MODE_MOTION 2

#define RESOURCE_DEFINE_HEADER "RESOURCE_DEFINE"
void loadResourceDefine(RESOURCE_LIST* list,BUF* buffer);
void closeResourceDefine(RESOURCE_LIST* list);
