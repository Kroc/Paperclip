@ECHO OFF
PUSHD %~dp0

bmconv conv.txt

COPY /Y /B "Paperclip.mbm" "\EPOC32\Release\WINS\Deb\Z\System\Apps\Paperclip\"
COPY /Y /B "Paperclip.mbm" "\EPOC32\Release\WINS\Deb\"

POPD