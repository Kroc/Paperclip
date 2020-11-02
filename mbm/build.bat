@ECHO OFF
PUSHD %~dp0

REM # colour mode, either "cl" for colour
REM # or "bw" for black & white

SET "CMODE=%~1"
IF [%CMODE%] == [] SET "CMODE=cl"

bmconv "Paperclip_%CMODE%.mbl"

COPY /Y /B "Paperclip.mbm" "\EPOC32\Release\WINS\Deb\Z\System\Apps\Paperclip\"
COPY /Y /B "Paperclip.mbm" "\EPOC32\Release\WINS\Rel\Z\System\Apps\Paperclip\"
COPY /Y /B "Paperclip.mbm" "\EPOC32\Release\MARM\Rel\"

POPD