@ECHO OFF
PUSHD %~dp0

REM CMD /C eikrs Paperclip SC udeb
REM CMD /C eikrs Paperclip SC urel
CMD /C eikrs Paperclip SC deb
CMD /C eikrs Paperclip SC rel

POPD