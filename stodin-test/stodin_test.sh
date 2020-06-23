#!/bin/bash
REAL_PATH=$(realpath "main.stdn")
../stodin-compiler/compile ${REAL_PATH} -run
