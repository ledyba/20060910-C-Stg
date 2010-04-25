rem ŠÂ‹«•Ï”‚ÌÝ’è
set PATH=F:\path;F:\path\upx125w;%PATH%
rem ƒRƒs[
XCOPY Shooting\*.* srcPack\ /Y /S /EXCLUDE:ex.txt
rem ZIP‚Åˆ³k
zip -g -r src_pack.zip srcPack\* > src-ZIP.log
pause