@ECHO OFF & SETLOCAL ENABLEEXTENSIONS DISABLEDELAYEDEXPANSION
PUSHD %~dp0

makesis -v "Paperclip.pkg" "Paperclip.sis"

REM # return the errorlevel of makesis,
REM # instead of the POPD

POPD & EXIT /B %ERRORLEVEL%