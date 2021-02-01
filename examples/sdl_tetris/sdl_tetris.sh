#!/bin/bash
REAL_PATH=$(realpath "sdl_tetris.stdn")
../../stodin-compiler/compile ${REAL_PATH} -run
