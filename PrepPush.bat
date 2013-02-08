REM @echo off
set src=\indra\newview\
set workingDir=%CD%

for /f "delims=" %%a in ('git symbolic-ref HEAD') do set head=%%a
set head=%head:~11%

cd ..\..\phoenix-firestorm-release
hg pull -u
cd %workingDir%

Echo Updating source files

set files=%src%llappviewer.cpp %src%llappviewer.h %src%llstartup.cpp %src%llstartup.h %src%llviewercamera.cpp %src%llviewercamera.h %src%llviewermessage.cpp %src%llviewermessage.h %src%llviewernui.cpp %src%llviewernui.h scripts\messages\message_template.msg %src%\app_settings\settings.xml 

echo %files%

REM git checkout FirestormHead
REM xcopy /d /y ..\..\Firestorm%src%*.cpp Source\
REM xcopy /d /y ..\..\Firestorm%src%*.h Source\
REM git add Source/*
REM git commit -m "Latest from Firestorm Trunk"
REM 
REM git checkout WorkingHead
REM xcopy /d /y ..%src%*.cpp Source\
REM xcopy /d /y ..%src%*.h Source\
REM git add Source/*
REM git commit -m "Latest from working directory"

REM git checkout %head%
for /f "delims=" %%l in ('git diff --name-only FirestormHead WorkingHead') do (
	call:subroutine "%%l"
)
REM call:diffFolder ..%src% *.cpp
REM call:diffFolder ..%src% *.h

xcopy /s /c /d /e /h /i /r /y /exclude:.copyignore ..\build-vc100\newview\Release\* Bin\
xcopy /s /c /d /e /h /i /r /y /exclude:.copyignore ..\indra\newview\* Bin\
xcopy /s /c /d /e /h /i /r /y /exclude:.copyignore ..\scripts\messages\message_template.msg Bin\app_settings\message_template.msg

goto:eof
:subroutine
	git checkout WorkingHead %1
	git diff FirestormHead WorkingHead %1 > Diff\%~xn1.diff
goto:eof

:diffFolder
	for /f "delims=" %%f in ('dir %1%2 /b') do (
		git diff FirestormHead WorkingHead Source\%%f > Diff\%%f.diff
		call:sizeDel Diff\%%f.diff
	)
goto:eof

:sizeDel
if %~z1 == 0 (
	Del %1
) else (
	git checkout -f WorkingHead Source\%~n1
)
goto:eof
