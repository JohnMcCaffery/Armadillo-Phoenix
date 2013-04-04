REM @echo off
set original=..\..\phoenix-firestorm-release
set src=\indra\newview\
set settings=\indra\newview\app_settings\
set messages=\scripts\messages\
set workingDir=%CD%

for /f "delims=" %%a in ('git symbolic-ref HEAD') do set head=%%a
set head=%head:~11%

git commit -m "Saving state before pulling changes."

cd ..\..\phoenix-firestorm-release
REM hg pull -insecure -u
cd %workingDir%

Echo Updating source files

git checkout FirestormHead
xcopy /d /y %original%%src%*.cpp Source%src%
xcopy /d /y %original%%src%*.h Source%src%
xcopy /d /y %original%%settings%*.xml Source%settings%
xcopy /d /y %original%%messages%*.msg Source%messages%
git add Source/*
git commit -m "Latest from Firestorm Trunk"

git checkout WorkingHead
xcopy /y ..%src%*.cpp Source%src%
xcopy /y ..%src%*.h Source%src%
xcopy /y ..%settings%*.xml Source%settings%
xcopy /y ..%messages%*.msg Source%messages%
git add Source/*
git commit -m "Latest from working directory"

git checkout %head%

for /f "delims=" %%l in ('git diff --name-only FirestormHead WorkingHead') do (
	call:subroutine "%%l"
)

xcopy /s /c /e /h /i /r /y /exclude:.copyignore ..%messages%*.msg ..\build-vc100\newview\Release\app_settings\
xcopy /s /c /d /e /h /i /r /y /exclude:.copyignore ..\build-vc100\newview\Release\* Bin\
xcopy /s /c /d /e /h /i /r /y /exclude:.copyignore ..%src%* Bin\
xcopy /s /c /d /e /h /i /r /y /exclude:.copyignore ..%settings%* Bin\app_settings\

goto:eof
:subroutine
	git checkout WorkingHead %1
	git diff FirestormHead WorkingHead %1 > Diff\%~xn1.diff
goto:eof
