@ECHO OFF
CD %~dp0

ECHO Make work directories:
CMD /C makmake -makework Paperclip wins
ECHO OK
ECHO Make Visual C++ Project:
CMD /C makmake Paperclip vc5
ECHO OK

PAUSE