/**
 * テキストを描画して、スプライトに変換します。
 * 流れは、
 * SDL_ttfでサーフェイスを作成→スプライトに使える形式に変換
 * →スプライト（テクスチャ）化
 */
 
 /**
  * 初期化します。
  */
int initTextRenderer();
/**
 * 終了します。
 */
int quitTextRenderer();
SPRITE* getTextSprite(SPRITE* sprite);
