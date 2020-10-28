@ECHO OFF & SETLOCAL ENABLEEXTENSIONS DISABLEDELAYEDEXPANSION
PUSHD %~dp0

SET "VARIANT=%~1"
IF [%VARIANT%] == [] SET "VARIANT=rel"

CMD /C makmake Paperclip marm
nmake /NOLOGO /S /F PAPERCLIP.MARM %VARIANT%

REM # return the errorlevel of NMAKE,
REM # instead of the POPD
REM #
POPD & EXIT /B %ERRORLEVEL%