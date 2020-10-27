@ECHO OFF
CD %~dp0

ECHO * Cleaning Build Artefacts...

REM # remove shared build artefacts
DEL /F /S /Q "\EPOC32\BUILD\Paperclip\WINSD\DEB\*.*"  >NUL 2>NUL
DEL /F /S /Q "\EPOC32\BUILD\Paperclip\WINSD\REL\*.*"  >NUL 2>NUL
DEL /F /S /Q "\EPOC32\BUILD\Paperclip\WINSD\UDEB\*.*" >NUL 2>NUL
DEL /F /S /Q "\EPOC32\BUILD\Paperclip\WINSD\UREL\*.*" >NUL 2>NUL
DEL /F /S /Q "\EPOC32\BUILD\Paperclip\MARMD\DEB\*.*"  >NUL 2>NUL
DEL /F /S /Q "\EPOC32\BUILD\Paperclip\MARMD\REL\*.*"  >NUL 2>NUL
DEL /F /S /Q "\EPOC32\BUILD\Paperclip\MARMD\UDEB\*.*" >NUL 2>NUL
DEL /F /S /Q "\EPOC32\BUILD\Paperclip\MARMD\UREL\*.*" >NUL 2>NUL
REM # remove local build artefacts
DEL /F /Q "\EPOC32\Release\WINS\Deb\Paperclip.*"  >NUL 2>NUL
DEL /F /Q "\EPOC32\Release\WINS\Rel\Paperclip.*"  >NUL 2>NUL
DEL /F /Q "\EPOC32\Release\WINS\UDEB\Paperclip.*" >NUL 2>NUL
DEL /F /Q "\EPOC32\Release\WINS\UREL\Paperclip.*" >NUL 2>NUL
DEL /F /Q "\EPOC32\Release\MARM\Deb\Paperclip.*"  >NUL 2>NUL
DEL /F /Q "\EPOC32\Release\MARM\Rel\Paperclip.*"  >NUL 2>NUL
DEL /F /Q "\EPOC32\Release\MARM\UDEB\Paperclip.*" >NUL 2>NUL
DEL /F /Q "\EPOC32\Release\MARM\UREL\Paperclip.*" >NUL 2>NUL
REM # remove app from the WINS EPOC "ROM" (Z:)
RMDIR /S /Q "\EPOC32\Release\WINS\Deb\Z\System\Apps\Paperclip\" >NUL 2>NUL

ECHO * Make work directories...
CMD /C makmake -makework Paperclip wins
CMD /C makmake -makework Paperclip marm

ECHO * Generate AIF file...
ECHO -------------------------------------------------------------------------------
CALL ..\aif\build.bat
ECHO -------------------------------------------------------------------------------

ECHO * Genearte Application MBM file...
ECHO -------------------------------------------------------------------------------
CALL ..\mbm\build.bat
ECHO -------------------------------------------------------------------------------

ECHO * Generate Resource file...
ECHO -------------------------------------------------------------------------------
CALL ..\rsc\build.bat
ECHO -------------------------------------------------------------------------------

ECHO * Build WINS Debug...
ECHO ===============================================================================
CMD /C makmake Paperclip wins
nmake /NOLOGO /S /F PAPERCLIP.WINS deb

ECHO:
IF ERRORLEVEL 1 PAUSE & EXIT /B 1

ECHO ===============================================================================
ECHO * Build MARM Release...
ECHO ===============================================================================
CMD /C makmake Paperclip marm
nmake /NOLOGO /S /F PAPERCLIP.MARM rel

IF ERRORLEVEL 1 POPD & PAUSE & EXIT /B 1

START "" \EPOC32\Release\WINS\Deb\EPOC.EXE
