@ECHO OFF
CD %~dp0

CALL "group\clean.bat"

ECHO * Generate AIF file...
CALL "aif\build.bat" cl

ECHO * Genearte Application MBM file...
CALL "mbm\build.bat" cl

ECHO * Generate Resource file...
CALL "rsc\build.bat"
ECHO:

ECHO * Build WINS Debug...
ECHO ===============================================================================
CALL "group\build_wins.bat" deb
IF ERRORLEVEL 1 PAUSE & EXIT /B 1
ECHO:

START "" \EPOC32\Release\WINS\Deb\EPOC.EXE