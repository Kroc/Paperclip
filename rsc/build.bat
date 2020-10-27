@ECHO OFF
PUSHD %~dp0

CMD /C eikrs Paperclip SC deb
CMD /C eikrs Paperclip SC rel

POPD