REM @echo off
set src=\indra\newview\

Echo Updating source files

xcopy /y Source\indra\newview\*.cpp ..\indra\newview
xcopy /y Source\indra\newview\*.h ..\indra\newview\
xcopy /y Source\indra\newview\app_settings\*.xml ..\indra\newview\app_settings
xcopy /y Source\scripts\messages\*.msg ..\scripts\messages\
xcopy /y Source\scripts\messages\*.msg ..\build-vc100\newview\Release\app_settings\

goto:eof
