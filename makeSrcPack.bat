rem ���ϐ��̐ݒ�
set PATH=F:\path;F:\path\upx125w;%PATH%
rem �R�s�[
XCOPY Shooting\*.* srcPack\ /Y /S /EXCLUDE:ex.txt
rem ZIP�ň��k
zip -g -r src_pack.zip srcPack\* > src-ZIP.log
pause