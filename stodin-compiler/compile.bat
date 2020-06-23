"C:\Program Files\CodeBlocks\MinGW\bin\mingw32-make.exe" -f MakefileWin all
del *.o
copy ..\compile\config_win.cfg config.cfg
pause