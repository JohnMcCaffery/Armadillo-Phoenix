REM @echo off
set original=..\..\phoenix-firestorm-release
set src=\indra\newview\
set settings=\indra\newview\app_settings\
set messages=\scripts\messages\
set workingDir=%CD%

for /f "delims=" %%a in ('git symbolic-ref HEAD') do set head=%%a
set head=%head:~11%

cd ..\..\phoenix-firestorm-release
REM hg pull -insecure -u
cd %workingDir%

Echo Updating source files

set files=%src%llappviewer.cpp %src%llappviewer.h %src%llstartup.cpp %src%llstartup.h %src%llviewercamera.cpp %src%llviewercamera.h %src%llviewermessage.cpp %src%llviewermessage.h %src%llviewernui.cpp %src%llviewernui.h scripts\messages\message_template.msg %src%\app_settings\settings.xml 

echo %files%

git checkout FirestormHead
xcopy /d /y %original%%src%*.cpp Source%src%
xcopy /d /y %original%%src%*.h Source%src%
xcopy /d /y %original%%settings%*.xml Source%settings%
xcopy /d /y %original%%messages%*.msg Source%messages%
git add Source/*
git commit -m "Latest from Firestorm Trunk"

git checkout WorkingHead
xcopy /d /y ..%src%*.cpp Source%src%
xcopy /d /y ..%src%*.h Source%src%
xcopy /d /y ..%settings%*.xml Source%settings%
xcopy /d /y ..%messages%*.msg Source%messages%
git add Source/*
git commit -m "Latest from working directory"

git checkout %head%
for /f "delims=" %%l in ('git diff --name-only FirestormHead WorkingHead') do (
	call:subroutine "%%l"
)
REM call:diffFolder ..%src% *.cpp
REM call:diffFolder ..%src% *.h
REM call:diffFolder ..%settings% *.xml
REM call:diffFolder ..%messages% *.msg

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
