@ECHO OFF
CD %~dp0

ECHO * Cleaning Build Artefacts...
CALL "group\clean.bat"

ECHO * Generate AIF file...
ECHO -------------------------------------------------------------------------------
CALL "aif\build.bat" bw
ECHO -------------------------------------------------------------------------------

ECHO * Genearte Application MBM file...
ECHO -------------------------------------------------------------------------------
CALL "mbm\build.bat" bw
ECHO -------------------------------------------------------------------------------

ECHO * Generate Resource file...
ECHO -------------------------------------------------------------------------------
CALL "rsc\build.bat"
ECHO -------------------------------------------------------------------------------

ECHO * Build WINS Release...
ECHO ===============================================================================
CALL "group\build_wins.bat" rel
IF ERRORLEVEL 1 PAUSE & EXIT /B 1
ECHO:

START "" \EPOC32\Release\WINS\Rel\EPOC.EXE

ECHO ===============================================================================
ECHO * Build MARM Release...
ECHO ===============================================================================
CALL "group\build_marm.bat" rel
IF ERRORLEVEL 1 PAUSE & EXIT /B 1
ECHO:

ECHO * Build SIS Installer...
ECHO -------------------------------------------------------------------------------
CALL "sis\build.bat"
IF ERRORLEVEL 1 PAUSE & EXIT /B 1
ECHO: