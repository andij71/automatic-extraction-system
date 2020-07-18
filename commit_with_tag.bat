



for /f %i in ('python version.py -v %VERSION%') do set VERSION=%i

git add --all
git commit -m "%VERSION% "
git push origin master
git push origin %VERSION%