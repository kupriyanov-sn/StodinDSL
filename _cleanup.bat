
rmdir compile\obj /S /Q

rmdir examples\guesser\stodin-out /S /Q
del examples\guesser\*.exe

rmdir examples\math_coach\stodin-out /S /Q
del examples\math_coach\*.exe

rmdir examples\quadratic\stodin-out /S /Q
del examples\quadratic\*.exe

rmdir examples\prime_sieves\stodin-out /S /Q
del examples\prime_sieves\*.exe

rmdir examples\four_heroes_game\stodin-out /S /Q
del examples\four_heroes_game\*.exe

rmdir examples\sdl_tetris\stodin-out /S /Q
del examples\sdl_tetris\*.exe

del stodin-compiler\compile.exe
del stodin-compiler\config.cfg

rmdir stodin-lib\bin /S /Q
rmdir stodin-lib\obj /S /Q

rmdir stodin-test\stodin-out /S /Q
del stodin-test\*.exe

pause
