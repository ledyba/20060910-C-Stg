rem ŠÂ‹«•Ï”‚ÌÝ’è
set PATH=F:\path;F:\path\upx125w;%PATH%
rem ƒRƒs[
copy /Y Release\*.exe pack\
copy /Y Release\*.dll pack\
copy /Y Release\*.arc pack\
rem UPX‚Åˆ³k
upx pack\*.exe pack\*.dll > UPX.log
rem ZIP‚Åˆ³k
zip -g -r pack.zip pack\* > ZIP.log
