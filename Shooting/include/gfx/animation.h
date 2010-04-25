/*�A�j���[�V������`�A�`��*/

typedef struct{
	int frame_time;
	SPRITE_AREA sprite_area;
}ANIMATION_FRAME;

typedef struct{
	int num;
	int frame_num;
	ANIMATION_FRAME* frame;
}ANIMATION;

typedef struct{
	int filename_size;
	char* filename;
	SPRITE sprite;
	int mode;
	int flag;
	int anime_num;
	ANIMATION** anime;
}ANIME_SET;

/**
 * �A�j���̐i���󋵂��L�^����B
 * ��ɓG�I�u�W�F�N�g�Ɏg�p�B
 */
typedef struct{
	ANIME_SET* graphic;
	int anime;
	int frame;
	int frame_left;
	float angle;
}ANIME_RECORD;


#define ANIME_HEADER "ANIME_DEFINE"
#define ANIME_MODE_BULLET		0x00000001
#define ANIME_MODE_FOE			0x00000002
#define ANIME_MODE_BOSS		0x00000004
#define ANIME_MODE_EFFECT		0x00000008
#define ANIME_MODE_CHARACTER	0x00000016
#define ANIME_FLAG_RORATE		0x00000001	//�e�A�G�̏ꍇ�A�A�j���[�V�������ނ���]���Ďg���B
#define ANIME_FLAG_SYMMETRIC	0x00000002	//�G�A�{�X�̏ꍇ�A���E�̉摜�͂Ђ�����Ԃ������ɂ���B

/**
 * �A�j���[�V������ǂݍ���
 */
void loadAnimation(ANIME_SET* anime,ARCHIVE* archive,const char* file_name);
/**
 * ���������J������B
 */
void deleteAnimation(ANIME_SET* graphic);
/**
 * �A�j���[�V������`�悷��B
 */
void drawAnimation(ANIME_RECORD* record,const glPoint* point);
/**
 * �A�j���̎�ނ�ύX����B
 */
int changeAnimation(ANIME_RECORD* record,int anime);
/**
 * �A�j���[�V�����̊p�x��ύX����B
 */
int changeAnimeAngle(ANIME_RECORD* record,float angle);
