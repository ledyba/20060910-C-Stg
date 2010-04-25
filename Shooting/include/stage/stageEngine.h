/*ステージ進行に関することを行います。総合的に。*/

#define STAGE_MAX	5			//ステージ数
int StageNumber;				//現在のステージ数

/**
 * ステージエンジンを初期化する。
 */
int initStageEngine(int stage);
/**
 * ステージエンジンを実際に動かす
 */
void startStageEngine();
/**
 * 敵発生、イベント処理などを総合的に行う。
 */
void moveStageEngine();
/**
 * メモリ開放、その他モロモロを行う。
 * moveStageEngineからのみ、呼ばれる。
 */
int quitStageEngine();
