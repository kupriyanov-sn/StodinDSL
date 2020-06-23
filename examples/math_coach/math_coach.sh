#!/bin/bash
REAL_PATH=$(realpath "math_coach.stdn")
../../stodin-compiler/compile ${REAL_PATH} -run
