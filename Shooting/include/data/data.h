/*アーカイバ*/

#define ARCHIVE_TITLE "ARCHIVE"

/**構造
 * "ARCHIVE"
 * ファイル数
 * ARCHIVE_HEADER_ITEM * 任意
 * データ
 */

typedef struct{
	int fileNameSize;			//文字数
	char* fileName;				//ファイル名
	int offset;					//先頭からのオフセット
	int size;					//サイズ
}ARCHIVE_HEADER_ITEM;

typedef struct{
	FILE* file;
	int fileNum;
	ARCHIVE_HEADER_ITEM* item;
}ARCHIVE;

/* アーカイブファイルを展開する
 * arc	:アーカイブファイルの展開先
 * file	:アーカイブファイル
 * */
int openArchive(ARCHIVE* arc,const char *filename);
/* 
 * arc		:アーカイぶファイル
 * filename	:ファイル名
 * */
SDL_RWops* getGraphixFile(ARCHIVE* arc, const char* filename);

/* 
 * arc		:アーカイぶファイル
 * filename	:ファイル名
 * */
BUF* getFile(ARCHIVE* arc, const char* filename);

/* アーカイブファイルを閉じる
 * arc	:アーカイブファイル
 */
int closeArchive(ARCHIVE* arc);
