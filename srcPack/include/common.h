/*共通ファイルの読み込み*/
#define COMMON_ARCHIVE "common.arc"

ARCHIVE CommonArchive;

void initCommon();
int loadCommon(long end_ticks);
int finishLoadCommon();
void quitCommon();



