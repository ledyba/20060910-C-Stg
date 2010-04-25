/*アニメーション定義、描画*/

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
 * アニメの進捗状況を記録する。
 * 主に敵オブジェクトに使用。
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
#define ANIME_FLAG_RORATE		0x00000001	//弾、敵の場合、アニメーション一種類を回転して使う。
#define ANIME_FLAG_SYMMETRIC	0x00000002	//敵、ボスの場合、左右の画像はひっくり返すだけにする。

/**
 * アニメーションを読み込む
 */
void loadAnimation(ANIME_SET* anime,ARCHIVE* archive,const char* file_name);
/**
 * メモリを開放する。
 */
void deleteAnimation(ANIME_SET* graphic);
/**
 * アニメーションを描画する。
 */
void drawAnimation(ANIME_RECORD* record,const glPoint* point);
/**
 * アニメの種類を変更する。
 */
int changeAnimation(ANIME_RECORD* record,int anime);
/**
 * アニメーションの角度を変更する。
 */
int changeAnimeAngle(ANIME_RECORD* record,float angle);
