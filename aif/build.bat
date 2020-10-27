@ECHO OFF
PUSHD %~dp0

CMD /C aiftool Paperclip WORD.MBM

COPY /Y /B "Paperclip.aif" "\EPOC32\Release\WINS\Deb\Z\System\Apps\Paperclip\"

POPD