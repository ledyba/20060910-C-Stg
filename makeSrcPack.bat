rem 環境変数の設定
set PATH=F:\path;F:\path\upx125w;%PATH%
rem コピー
XCOPY Shooting\*.* srcPack\ /Y /S /EXCLUDE:ex.txt
rem ZIPで圧縮
zip -g -r src_pack.zip srcPack\* > src-ZIP.log
pause