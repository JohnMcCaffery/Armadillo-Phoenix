for /f "delims=" %%a in ('git symbolic-ref HEAD') do set head=%%a
set head=%head:~11%

git add .
git commit -m "About to update PrepPush"

git checkout FirestormHead
git checkout %head% PrepPush.bat
git add .
git commit -m "Updated PrepPush."

git checkout WorkingHead
git checkout %head% PrepPush.bat
git add .
git commit -m "Updated PrepPush."

git checkout %head%
