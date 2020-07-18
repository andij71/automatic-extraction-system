for /f %i in ('python version.py -v %VERSION%' --rc) do set VERSION=%i
git add --all
git commit -m "%VERSION% "
git tag -a "%VERSION%" -m "Release %VERSION%"
git push origin master
git push origin %VERSION%