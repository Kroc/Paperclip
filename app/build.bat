@ECHO OFF
CD %~dp0

ECHO Cleaning Build Artefacts...

REM # remove shared build artefacts
DEL /F /S /Q "C:\EPOC32\BUILD\Paperclip\WINSD\DEB\*.*"  >NUL 2>NUL
DEL /F /S /Q "C:\EPOC32\BUILD\Paperclip\WINSD\REL\*.*"  >NUL 2>NUL
DEL /F /S /Q "C:\EPOC32\BUILD\Paperclip\WINSD\UDEB\*.*" >NUL 2>NUL
DEL /F /S /Q "C:\EPOC32\BUILD\Paperclip\WINSD\UREL\*.*" >NUL 2>NUL
DEL /F /S /Q "C:\EPOC32\BUILD\Paperclip\MARMD\DEB\*.*"  >NUL 2>NUL
DEL /F /S /Q "C:\EPOC32\BUILD\Paperclip\MARMD\REL\*.*"  >NUL 2>NUL
DEL /F /S /Q "C:\EPOC32\BUILD\Paperclip\MARMD\UDEB\*.*" >NUL 2>NUL
DEL /F /S /Q "C:\EPOC32\BUILD\Paperclip\MARMD\UREL\*.*" >NUL 2>NUL
REM # remove local build artefacts
DEL /F /Q "C:\EPOC32\Release\WINS\Deb\Paperclip.*"  >NUL 2>NUL
DEL /F /Q "C:\EPOC32\Release\WINS\Rel\Paperclip.*"  >NUL 2>NUL
DEL /F /Q "C:\EPOC32\Release\WINS\UDEB\Paperclip.*" >NUL 2>NUL
DEL /F /Q "C:\EPOC32\Release\WINS\UREL\Paperclip.*" >NUL 2>NUL
DEL /F /Q "C:\EPOC32\Release\MARM\Deb\Paperclip.*"  >NUL 2>NUL
DEL /F /Q "C:\EPOC32\Release\MARM\Rel\Paperclip.*"  >NUL 2>NUL
DEL /F /Q "C:\EPOC32\Release\MARM\UDEB\Paperclip.*" >NUL 2>NUL
DEL /F /Q "C:\EPOC32\Release\MARM\UREL\Paperclip.*" >NUL 2>NUL
REM # remove app from the EPOC "ROM" (Z:)
RMDIR /S /Q "C:\EPOC32\Release\WINS\Deb\Z\System\Apps\Paperclip\" >NUL 2>NUL

ECHO Make work directories...
CMD /C makmake -makework Paperclip wins
CMD /C makmake -makework Paperclip marm

ECHO Generate AIF file...
CALL ..\aif\conv.bat

ECHO Genearte Application MBM file...
CALL ..\mbm\conv.bat

ECHO Generate Resource file...
CMD /C eikrs Paperclip SC deb
CMD /C eikrs Paperclip SC rel

ECHO Generate NMake File...
CMD /C makmake Paperclip wins
CMD /C makmake Paperclip marm

ECHO Build...
nmake -f PAPERCLIP.WINS deb

ECHO:
IF ERRORLEVEL 1 PAUSE & EXIT /B 1

nmake -f PAPERCLIP.MARM rel
IF ERRORLEVEL 1 PAUSE & EXIT /B 1

C:\EPOC32\Release\WINS\Deb\EPOC.EXE
