#!/bin/bash
REAL_PATH=$(realpath "sdl_four_heroes_game.stdn")
../../stodin-compiler/compile ${REAL_PATH} -run
