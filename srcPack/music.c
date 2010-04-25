#include <windows.h>
#include <pxtone.h>

int initMusic(){
	int result = 0;
 	result = pxtone_Ready(
	NULL,	// ウインドウハンドルを渡してください
	2,		// チャンネル数を指定してください。( 1:モノラル / 2:ステレオ )
	44100,	// 秒間サンプリングレートです。      ( 11025 / 22050 / 44100 )
	16,		// １サンプルを表現するビット数です。( 8 / 16 )
	0.1,   	// 曲を再生するのに使用するバッファサイズを秒で指定します。( 推奨 0.1 )
	FALSE,	// TRUE: DirectSound を使用します / FALSE: WAVEMAPPER を使用します。
	NULL	// サンプリング舞に呼ばれる関数です。NULL でかまいません。
); // pxtone の準備
	return result;
}
int loadMusic(char* name){
	int result = 0;
	result = pxtone_Tune_Load(
		NULL,       // リソースから読む場合はモジュールハンドルを指定します。NULL でも問題ないかも。
		NULL, // リソースから読む場合はリソースの種類名。外部ファイルを読む場合は NULL。
		name  // ファイルパスもしくはリソース名。
	);
	return result;
}

int playMusic(long start_sample,long fade_msec){
int result =  pxtone_Tune_Start(
	start_sample,     // 開始位置です。主に Stop や Fadeout で取得した値を設定します。0 で最初から。
	fade_msec         // フェードインする場合はここに時間（ミリ秒）を指定します。
	);
	return result;
}
