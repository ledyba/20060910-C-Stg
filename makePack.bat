rem ���ϐ��̐ݒ�
set PATH=F:\path;F:\path\upx125w;%PATH%
rem �R�s�[
copy /Y Release\*.exe pack\
copy /Y Release\*.dll pack\
copy /Y Release\*.arc pack\
rem UPX�ň��k
upx pack\*.exe pack\*.dll > UPX.log
rem ZIP�ň��k
zip -g -r pack.zip pack\* > ZIP.log
