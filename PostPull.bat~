@echo off
set src=\indra\newview\

Echo Updating source files

set f1c=%src%llappviewer.cpp
set f1h=%src%llappviewer.h
set f2c=%src%llstartup.cpp
set f2h=%src%llstartup.h
set f3c=%src%llviewercamera.cpp
set f3h=%src%llviewercamera.h
set f4c=%src%llviewermessage.cpp
set f4h=%src%llviewermessage.h
set f5c=%src%llviewernui.cpp
set f5h=%src%llviewernui.h
set f6=scripts\messages\message_template.msg
set f7=%src%\app_settings\settings.xml

call:copyToIndra ..\%f1c%
call:copyToIndra ..\%f1h%
call:copyToIndra ..\%f2c%
call:copyToIndra ..\%f2h%
call:copyToIndra ..\%f3c%
call:copyToIndra ..\%f3h%
call:copyToIndra ..\%f4c%
call:copyToIndra ..\%f4h%
call:copyToIndra ..\%f5c%
call:copyToIndra ..\%f5h%
call:copyToIndra ..\%f6%
call:copyToIndra ..\%f7%

goto:eof

:copyToIndra
xcopy /d /y Source\%~nx1 %~1 
goto:eof

:diff
git diff FirestormHead Source\%~nx1 > Diff\%~nx1.diff
goto:eof
