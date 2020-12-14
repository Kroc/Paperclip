@ECHO OFF
PUSHD %~dp0

REM # colour mode, either "cl" for colour
REM # or "bw" for black & white

SET "CMODE=%~1"
IF [%CMODE%] == [] SET "CMODE=cl"

REM # build the application icon first
CALL "m%CMODE%\build.bat"

REM # create the application manifest (and embedded icon)
REM # for the given colour-mode

CMD /C aiftool Paperclip "m%CMODE%\Paperclip.mbm" >NUL

REM # copy the generated application manifest
REM # to the working directories
REM # TODO: unicode versions have to be built with a different switch

COPY /Y /B "Paperclip.aif" "\EPOC32\Release\WINS\Deb\Z\System\Apps\Paperclip\" >NUL
COPY /Y /B "Paperclip.aif" "\EPOC32\Release\WINS\Rel\Z\System\Apps\Paperclip\" >NUL
COPY /Y /B "Paperclip.aif" "\EPOC32\Release\MARM\Rel\" >NUL

POPD