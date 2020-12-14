@ECHO OFF
PUSHD %~dp0

CMD /C eikrs Paperclip SC deb >NUL
CMD /C eikrs Paperclip SC rel >NUL

POPD