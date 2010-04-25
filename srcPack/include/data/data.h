/*�A�[�J�C�o*/

#define ARCHIVE_TITLE "ARCHIVE"

/**�\��
 * "ARCHIVE"
 * �t�@�C����
 * ARCHIVE_HEADER_ITEM * �C��
 * �f�[�^
 */

typedef struct{
	int fileNameSize;			//������
	char* fileName;				//�t�@�C����
	int offset;					//�擪����̃I�t�Z�b�g
	int size;					//�T�C�Y
}ARCHIVE_HEADER_ITEM;

typedef struct{
	FILE* file;
	int fileNum;
	ARCHIVE_HEADER_ITEM* item;
}ARCHIVE;

/* �A�[�J�C�u�t�@�C����W�J����
 * arc	:�A�[�J�C�u�t�@�C���̓W�J��
 * file	:�A�[�J�C�u�t�@�C��
 * */
int openArchive(ARCHIVE* arc,const char *filename);
/* 
 * arc		:�A�[�J�C�ԃt�@�C��
 * filename	:�t�@�C����
 * */
SDL_RWops* getGraphixFile(ARCHIVE* arc, const char* filename);

/* 
 * arc		:�A�[�J�C�ԃt�@�C��
 * filename	:�t�@�C����
 * */
BUF* getFile(ARCHIVE* arc, const char* filename);

/* �A�[�J�C�u�t�@�C�������
 * arc	:�A�[�J�C�u�t�@�C��
 */
int closeArchive(ARCHIVE* arc);
