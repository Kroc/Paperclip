@ECHO OFF
CD %~dp0

ECHO * Cleaning Build Artefacts...
CALL "app\clean.bat"

ECHO * Generate AIF file...
ECHO -------------------------------------------------------------------------------
CALL "aif\build.bat"
ECHO -------------------------------------------------------------------------------

ECHO * Genearte Application MBM file...
ECHO -------------------------------------------------------------------------------
CALL "mbm\build.bat"
ECHO -------------------------------------------------------------------------------

ECHO * Generate Resource file...
ECHO -------------------------------------------------------------------------------
CALL "rsc\build.bat"
ECHO -------------------------------------------------------------------------------

ECHO * Build WINS Debug...
ECHO ===============================================================================
CALL "app\build_wins.bat" deb
IF ERRORLEVEL 1 PAUSE & EXIT /B 1
ECHO:

ECHO * Build WINS Release...
ECHO ===============================================================================
CALL "app\build_wins.bat" rel
IF ERRORLEVEL 1 PAUSE & EXIT /B 1
ECHO:

ECHO ===============================================================================
ECHO * Build MARM Release...
ECHO ===============================================================================
CALL "app\build_marm.bat" rel
IF ERRORLEVEL 1 PAUSE & EXIT /B 1
ECHO:

START "" \EPOC32\Release\WINS\Deb\EPOC.EXE
