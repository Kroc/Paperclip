@ECHO OFF
CD %~dp0

CALL "group\clean.bat"

ECHO * Generate AIF file...
CALL "aif\build.bat" bw

ECHO * Genearte Application MBM file...
CALL "mbm\build.bat" bw

ECHO * Generate Resource file...
CALL "rsc\build.bat"
ECHO:

ECHO * Build WINS Release...
ECHO ===============================================================================
CALL "group\build_wins.bat" rel
IF ERRORLEVEL 1 PAUSE & EXIT /B 1
ECHO:

START "" \EPOC32\Release\WINS\Rel\EPOC.EXE

ECHO ===============================================================================
ECHO * Build MARM Release...
ECHO ===============================================================================
ECHO * Generate AIF file (Mono)...
CALL "aif\build.bat" bw

ECHO * Generate Application MBM file (Mono)...
CALL "mbm\build.bat" bw

ECHO * Compile Application (Mono)...
ECHO -------------------------------------------------------------------------------
CALL "group\build_marm.bat" rel
IF ERRORLEVEL 1 PAUSE & EXIT /B 1
ECHO:

ECHO * Build SIS Installer (Mono)...
CALL "sis\build.bat"
IF ERRORLEVEL 1 PAUSE & EXIT /B 1

ECHO:

IF EXIST "sis\Paperclip_mono.sis" DEL /Q "sis\Paperclip_mono.sis" >NUL
REN "sis\Paperclip.sis" "Paperclip_mono.sis" >NUL

ECHO * Generate AIF file (Colour)...
CALL "aif\build.bat" cl

ECHO * Generate Application MBM file (Colour)...
CALL "mbm\build.bat" cl

ECHO * Compile Application (Colour)...
ECHO -------------------------------------------------------------------------------
CALL "group\build_marm.bat" rel
IF ERRORLEVEL 1 PAUSE & EXIT /B 1
ECHO:

ECHO * Build SIS Installer (Colour)...
CALL "sis\build.bat"
IF ERRORLEVEL 1 PAUSE & EXIT /B 1

IF EXIST "sis\Paperclip_color.sis" DEL /Q "sis\Paperclip_color.sis" >NUL
REN "sis\Paperclip.sis" "Paperclip_color.sis" >NUL

ECHO:
ECHO * Make release bundle...

SET "BIN_ZIP=bin\7zip\7za.exe"
ECHO %BIN_ZIP% a "release\Paperclip.zip" -bso0 -bsp1 -bse0 -tzip -r -mx9 -mfb258 -mpass15 -x!Desktop.ini -x!Thumbs.db -x!.* -- *

PUSHD "release"
..\%BIN_ZIP% a "Paperclip.zip" -bso0 -bsp1 -bse0 -tzip -r -mx9 -mfb258 -mpass15 -x!Desktop.ini -x!Thumbs.db -x!.* -- *
POPD

PAUSE