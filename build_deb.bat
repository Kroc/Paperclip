@ECHO OFF
CD %~dp0

ECHO * Cleaning Build Artefacts...
CALL "group\clean.bat"

ECHO * Generate AIF file...
ECHO -------------------------------------------------------------------------------
CALL "aif\build.bat" cl
ECHO -------------------------------------------------------------------------------

ECHO * Genearte Application MBM file...
ECHO -------------------------------------------------------------------------------
CALL "mbm\build.bat" cl
ECHO -------------------------------------------------------------------------------

ECHO * Generate Resource file...
ECHO -------------------------------------------------------------------------------
CALL "rsc\build.bat"
ECHO -------------------------------------------------------------------------------

ECHO * Build WINS Debug...
ECHO ===============================================================================
CALL "group\build_wins.bat" deb
IF ERRORLEVEL 1 PAUSE & EXIT /B 1
ECHO:

START "" \EPOC32\Release\WINS\Deb\EPOC.EXE