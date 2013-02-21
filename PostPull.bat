REM @echo off
set src=\indra\newview\

Echo Updating source files

xcopy /d /y Source\indra\newview\*.cpp ..\indra\newview
xcopy /d /y Source\indra\newview\*.h ..\indra\newview\
xcopy /d /y Source\app_settings\*.xml ..\indra\newview\app_settings\
xcopy /d /y Source\messages\*.msg ..\scripts\messages\

goto:eof
