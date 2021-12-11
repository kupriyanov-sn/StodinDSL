#!/bin/bash
REAL_PATH=$(realpath "sdl_pixel_editor.stdn")
../../stodin-compiler/compile ${REAL_PATH} -run
